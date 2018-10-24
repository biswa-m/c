// Set range of the slider
static void slider_set_range(struct _data *data)
{
	if (!gst_element_query_duration(data->gst_data->playbin,
			GST_FORMAT_TIME, &data->gst_data->duration)) {
		g_printerr("Could not query current duration.\n");
	} else {
		// set range of the slider to clip duration, in sec
		gtk_range_set_range(GTK_RANGE(data->gst_data->slider),
		0, (gdouble)data->gst_data->duration / GST_SECOND);
		g_print("slider refreshed\t");
	}
}

// Synch slider position with playbin
gboolean refresh_slider(struct _data *data) {
        gint64 current = -1;
	
        // If pipeline is not in play or pause state, no need to update
        if (data->gst_data->state < GST_STATE_PAUSED)
                return TRUE;

        if (gst_element_query_position(
                data->gst_data->playbin, GST_FORMAT_TIME, &current)) {

                // block value_changed signal, otherwise slider_cb() will
                // be called which will result an unwanted seek
                g_signal_handler_block(data->gst_data->slider,
                                data->gst_data->slider_update_signal_id);
                // set the slider position
                gtk_range_set_value(GTK_RANGE(data->gst_data->slider),
                                (gdouble)current / GST_SECOND);

                // re-enable the signal
                g_signal_handler_unblock(data->gst_data->slider,
                                data->gst_data->slider_update_signal_id);
        }

	return TRUE;
}


// When error message is posted on the bus
static void error_cb(GstBus *bus, GstMessage *msg, struct _data *data)
{
        GError *err;
        gchar *debug_info;

        gst_message_parse_error(msg, &err, &debug_info);
        g_printerr("Error receiving from element %s: %s\n",
                        GST_OBJECT_NAME(msg->src), err->message);
        g_printerr("Debugging information: %s\n",
                        debug_info ? debug_info : "none");
        g_clear_error(&err);

        gst_element_set_state(data->gst_data->playbin, GST_STATE_NULL);
}

// To keep track of the current state of the pipeline
static void state_changed_cb(
                GstBus *bus,
                GstMessage *msg,
                struct _data *data)
{
	GstState old_state, new_state, pending_state;
        gst_message_parse_state_changed(msg,
                        &old_state, &new_state, &pending_state);

        if (GST_MESSAGE_SRC(msg) == GST_OBJECT(data->gst_data->playbin)) {
                data->gst_data->state = new_state;
                g_print("State set to %s\n",
                                gst_element_state_get_name(new_state));
                if (old_state == GST_STATE_READY
                                && new_state ==  GST_STATE_PAUSED) {
                        // refress GUI, mainly the slider
			slider_set_range(data);	
			refresh_slider(data);
                }
        }
}

void initialize_gst(struct _data *data)
{
	gst_init(0, NULL);

	struct _media_previewer *gst_data;
	gst_data = malloc(sizeof(struct _media_previewer));
        memset(gst_data, 0, sizeof(*gst_data));

        data->gst_data = gst_data;
	
	gst_data->duration = GST_CLOCK_TIME_NONE;

	gst_data->playbin = gst_element_factory_make("playbin", "playbin");
	if (!gst_data->playbin) {
		g_printerr("Playbin could not be created\n");
		return;
	}
	// Instruct the bus to emit signals for each received message
	// and connect to the interesting signals
	GstBus *bus;
	bus = gst_element_get_bus(data->gst_data->playbin);
	gst_bus_add_signal_watch(bus);

	g_signal_connect(G_OBJECT(bus), "message::error",
			(GCallback)error_cb, data);
	g_signal_connect(G_OBJECT(bus), "message::state-changed",
			(GCallback)state_changed_cb, data);
	g_object_unref(bus);

	g_print("GStreamer Initialized\n");
}

static void realize_cb(GtkWidget *widget, struct _data *data)
{
	GdkWindow *window = gtk_widget_get_window(widget);
	guintptr window_handle;

	if (!gdk_window_ensure_native(window))
		g_error("Couldn't create window for GstVideoOverlay!\n");
	window_handle = GDK_WINDOW_XID(window);

	gst_video_overlay_set_window_handle(
		GST_VIDEO_OVERLAY(data->gst_data->playbin), window_handle);

	g_print("Realized\n");
}

// Function for seek bar
static void slider_cb(GtkRange *range, struct _data *data)
{
        gdouble value = gtk_range_get_value(GTK_RANGE(data->gst_data->slider));

        gst_element_seek_simple(data->gst_data->playbin, GST_FORMAT_TIME, 
                        GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT,
                        (gint64)(value * GST_SECOND));
}

void scroll_cb(GtkWidget *drawing_area, 
		GdkEventScroll *event,
		struct _data *data)
{
	gdouble value = gtk_range_get_value(GTK_RANGE(data->gst_data->slider));

	switch (event->direction) {
	case GDK_SCROLL_LEFT:
		gtk_range_set_value(GTK_RANGE(data->gst_data->slider), 
				++value);
		break;
	case GDK_SCROLL_RIGHT:
		gtk_range_set_value(GTK_RANGE(data->gst_data->slider),
				--value);
		break;
	}
}

static void control_state(GtkWidget *widget, GdkEvent *event,
	       	struct _data *data)
{
	if (data->gst_data->state == GST_STATE_PLAYING){ 
		gst_element_set_state(data->gst_data->playbin, 
				GST_STATE_PAUSED);
		return;
	}
	GstStateChangeReturn ret;
	ret = gst_element_set_state(data->gst_data->playbin, 
			GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to playing state\n");
		gst_object_unref(data->gst_data->playbin);
		return;
	}
}

void initialize_video_preview(struct _data *data)
{
	data->drawing_area = gtk_drawing_area_new();
	gtk_widget_set_double_buffered(data->drawing_area, TRUE);
	gtk_box_pack_start(GTK_BOX(data->preview_box),
		data->drawing_area, 1, 1, 2);

	data->gst_data->slider = gtk_scale_new_with_range(
		GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
	gtk_scale_set_draw_value(GTK_SCALE(data->gst_data->slider), 0);

	data->gst_data->slider_update_signal_id = g_signal_connect(
		G_OBJECT(data->gst_data->slider), "value-changed",
		G_CALLBACK(slider_cb), data);

	gtk_box_pack_start(GTK_BOX(data->preview_box),
		data->gst_data->slider, 0, 0, 2);

	gtk_widget_add_events(GTK_WIDGET(data->drawing_area), GDK_SCROLL_MASK);
	g_signal_connect(data->drawing_area, "scroll-event", 
			G_CALLBACK(scroll_cb), data);

	gtk_widget_add_events(GTK_WIDGET(data->drawing_area), 
			GDK_BUTTON_PRESS_MASK);
	g_signal_connect(data->drawing_area, "button_press_event", 
			G_CALLBACK(control_state), data);

	
//	g_signal_connect(G_OBJECT(data->drawing_area), 
//			"realize", G_CALLBACK(realize_cb), data);
	realize_cb(data->drawing_area, data);
	
	g_timeout_add_seconds(1, (GSourceFunc)refresh_slider, data);
}

void stop_preview(struct _data *);

void media_preview(struct _data *data)
{
	stop_preview(data);

	// Set the GStreamer playbin source path to currently selected file 
	gchar tmp[2048] = "file://";
	strcat(tmp, data->path);
	g_object_set(data->gst_data->playbin, "uri", tmp, NULL);

	// Start Gstreamer previewer
	GstStateChangeReturn ret;
	ret = gst_element_set_state(data->gst_data->playbin, 
			GST_STATE_PAUSED);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to playing state\n");
		gst_object_unref(data->gst_data->playbin);
		return;
	}

	gtk_widget_show_all(data->drawing_area);
	gtk_widget_show_all(data->gst_data->slider);
}
