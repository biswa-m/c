/* A basic media player using GStreamer 1.0 and gtk 3.22
 *
 * To compile
 * gcc media_player_01.c $(pkg-config --cflags --libs gtk+-3.0 gstreamer-1.0 gstreamer-video-1.0)
 */

#include <string.h>

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <gdk/gdkx.h>

#define URI "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"

struct custom_data {
	GstElement *playbin;
	
	GtkWidget *slider;
	GtkWidget *streams_list;
	gulong slider_update_signal_id;

	GstState state;
	gint64 duration;
};

static void play_cb(GtkButton *button, struct custom_data *data)
{
	gst_element_set_state(data->playbin, GST_STATE_PLAYING);
}

static void pause_cb(GtkButton *button, struct custom_data *data)
{
	gst_element_set_state(data->playbin, GST_STATE_PAUSED);
}

static void stop_cb(GtkButton *button, struct custom_data *data)
{
	gst_element_set_state(data->playbin, GST_STATE_READY);
}

static void delete_event_cb(
		GtkWidget *widget,
		GdkEvent *event,
		struct custom_data *data)
{
	stop_cb(NULL, data);
	gtk_main_quit();
}

// When error message is posted on the bus
static void error_cb(
		GstBus *bus,
		GstMessage *msg,
		struct custom_data *data)
{
	GError *err;
	gchar *debug_info;

	gst_message_parse_error(msg, &err, &debug_info);
	g_printerr("Error receiving from element %s: %s\n",
			GST_OBJECT_NAME(msg->src), err->message);
	g_printerr("Debugging information: %s\n", 
			debug_info ? debug_info : "none");
	g_clear_error(&err);

	gst_element_set_state(data->playbin, GST_STATE_READY);
}

// When End of stream message is posted on the bus
static void eos_cb(
		GstBus *bus,
		GstMessage *msg,
		struct custom_data *data)
{
	g_print("End-Of-Stream reached.\n");
	gst_element_set_state(data->playbin, GST_STATE_READY);
}

// This function is called periodically to refresh the slider
static gboolean refresh_ui(struct custom_data *data) {
	gint64 current = -1;

	// If pipeline is not in play or pause state, no need to update
	if (data->state < GST_STATE_PAUSED)
		return TRUE;

	// set range of the slider if not set yet
	if (!GST_CLOCK_TIME_IS_VALID(data->duration)) {
		if (!gst_element_query_duration(data->playbin, 
				GST_FORMAT_TIME, &data->duration)) {
			g_printerr("Could not query current duration.\n");
		} else {
			// set range of the slider to clip duration, in sec
			gtk_range_set_range(GTK_RANGE(data->slider), 
				0, (gdouble)data->duration / GST_SECOND);
		}
	}
	
	if (gst_element_query_position(
			data->playbin, GST_FORMAT_TIME, &current)) {

		// block value_changed signal, otherwise slider_cb() will 
		// be called which will result an unwanted seek
		g_signal_handler_block(data->slider,
				data->slider_update_signal_id);
		// set the slider position
		gtk_range_set_value(GTK_RANGE(data->slider),
				(gdouble)current / GST_SECOND);

		// re-enable the signal
		g_signal_handler_unblock(data->slider,
				data->slider_update_signal_id);
	}
	
}

// To keep track of the current state of the pipeline
static void state_changed_cb(
		GstBus *bus, 
		GstMessage *msg, 
		struct custom_data *data)
{
	GstState old_state, new_state, pending_state;
	gst_message_parse_state_changed(msg,
			&old_state, &new_state, &pending_state);

	if (GST_MESSAGE_SRC(msg) == GST_OBJECT(data->playbin)) {
		data->state = new_state;
		g_print("State set to %s\n",
				gst_element_state_get_name(new_state));
		if (old_state == GST_STATE_READY 
				&& new_state ==  GST_STATE_PAUSED) {
			// refress GUI, mainly the slider
			refresh_ui(data);
		}
	}
}

// In pause or play state, Gstreamer will handle window output.
// In other state show a black rectangle instad of garbage value
static gboolean draw_cb(
		GtkWidget *widget, 
		cairo_t *cr, 
		struct custom_data *data)
{
	if (data->state < GST_STATE_PAUSED) {
		GtkAllocation allocation;
		gtk_widget_get_allocation(widget, &allocation);
		cairo_set_source_rgb(cr, 0, 0, 0);
		cairo_rectangle(cr, 0, 0, 
				allocation.width, allocation.height);
		cairo_fill(cr);
	}
	return FALSE;
}

// Function for seek bar
static void slider_cb(GtkRange *range, struct custom_data *data)
{
	gdouble value = gtk_range_get_value(GTK_RANGE(data->slider));
	gst_element_seek_simple(data->playbin, GST_FORMAT_TIME, 
			GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT,
			(gint64)(value * GST_SECOND));
}

// When window is realized, pass handler for GStreamer through VideoOverlay
static void realize_cb(GtkWidget *widget, struct custom_data *data)
{
	GdkWindow *window = gtk_widget_get_window(widget);
	guintptr window_handle;

	if (!gdk_window_ensure_native(window))
		g_error("Couldn't create window for GstVideoOverlay!\n");
	window_handle = GDK_WINDOW_XID(window);

	gst_video_overlay_set_window_handle(
			GST_VIDEO_OVERLAY(data->playbin), window_handle);
}

static void create_ui(struct custom_data *data)
{
	GtkWidget *main_window;
	GtkWidget *video_window;
	GtkWidget *main_box;
	GtkWidget *main_hbox;
	GtkWidget *controls;
	GtkWidget *play_button, *pause_button, *stop_button;

	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(main_window), "delete-event",
			G_CALLBACK(delete_event_cb), data);

	video_window = gtk_drawing_area_new();
	gtk_widget_set_double_buffered(video_window, FALSE);
	g_signal_connect(G_OBJECT(video_window), "realize",
			G_CALLBACK(realize_cb), data);	
	g_signal_connect(G_OBJECT(video_window), "draw",
			G_CALLBACK(draw_cb), data);	

	play_button = gtk_button_new_from_icon_name("media-playback-start",
			GTK_ICON_SIZE_SMALL_TOOLBAR);
	g_signal_connect(G_OBJECT(play_button), "clicked", 
			G_CALLBACK(play_cb), data);

	pause_button = gtk_button_new_from_icon_name("media-playback-pause",
			GTK_ICON_SIZE_SMALL_TOOLBAR);
	g_signal_connect(G_OBJECT(pause_button), "clicked", 
			G_CALLBACK(pause_cb), data);
	
	stop_button = gtk_button_new_from_icon_name("media-playback-stop",
			GTK_ICON_SIZE_SMALL_TOOLBAR);
	g_signal_connect(G_OBJECT(stop_button), "clicked", 
			G_CALLBACK(stop_cb), data);

	data->slider = gtk_scale_new_with_range(
			GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
	gtk_scale_set_draw_value(GTK_SCALE(data->slider), 0);
	data->slider_update_signal_id = g_signal_connect(
			G_OBJECT(data->slider), "value-changed",
			G_CALLBACK(slider_cb), data);

	controls = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(controls), play_button, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(controls), pause_button, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(controls), stop_button, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(controls), data->slider, TRUE, TRUE, 2);

	main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(main_box), video_window, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(main_box), controls, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(main_window), main_box);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 640, 480);

	gtk_widget_show_all(main_window);
}

int main(int argc, char *argv[])
{
	struct custom_data data;
	GstStateChangeReturn ret;
	GstBus *bus;

	// initializations
	gtk_init(&argc, &argv);
	gst_init(&argc, &argv);

	memset(&data, 0, sizeof(data));
	data.duration = GST_CLOCK_TIME_NONE;

	// Create the elements
	data.playbin = gst_element_factory_make("playbin", "playbin");
	if(!data.playbin) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}
	
	// Set the URI to play
	g_object_set(data.playbin, "uri", URI, NULL); 
	

	// Create the GUI
	create_ui(&data);

	// Instruct the bus to emit signals for each received message
	// and connect to the interesting signals
	bus = gst_element_get_bus(data.playbin);
	gst_bus_add_signal_watch(bus);

	g_signal_connect(G_OBJECT(bus), "message::error", 
			(GCallback)error_cb, &data);
	g_signal_connect(G_OBJECT(bus), "message::eos", 
			(GCallback)eos_cb, &data);
	g_signal_connect(G_OBJECT(bus), "message::state-changed", 
			(GCallback)state_changed_cb, &data);
	g_object_unref(bus);

	// Start playing
	ret = gst_element_set_state(data.playbin, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to playing state\n");
		gst_object_unref(data.playbin);
		return -1;
	}

	// Register a function that Glib will call every second
	g_timeout_add_seconds(1, (GSourceFunc)refresh_ui, &data);

	// Start gtk main loop
	gtk_main();

	// Free resources
	gst_element_set_state(data.playbin, GST_STATE_NULL);
	gst_object_unref(data.playbin);

	return 0;
}
