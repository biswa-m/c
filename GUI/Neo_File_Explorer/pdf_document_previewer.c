static void update_pdf_statusbar(struct _data *data)
{
	gchar *str;
	str = g_strdup_printf("Page %d / %d",
			data->pdf_data->current_page + 1,
			data->pdf_data->total_page);
	gtk_statusbar_push(GTK_STATUSBAR(data->pdf_data->status_bar),
			gtk_statusbar_get_context_id(
			GTK_STATUSBAR(data->pdf_data->status_bar),str),
			str);
	g_free(str);
}

static void view_set_page(struct _data *data)
{
	int err;
	int w, h;
	double width, height;
	cairo_t *cr;

	PopplerPage *ppage = poppler_document_get_page(
			data->pdf_data->document,
			data->pdf_data->current_page);
	poppler_page_get_size(ppage, &width, &height);
	poppler_page_get_size(ppage, &width, &height);
	w = (int)ceil(width);
	h = (int)ceil(height);

	cairo_surface_destroy(data->pdf_data->surface);
	data->pdf_data->surface = cairo_image_surface_create(
			CAIRO_FORMAT_ARGB32, w, h);

	cr = cairo_create(data->pdf_data->surface);
	
	poppler_page_render(ppage, cr);
	cairo_destroy(cr);

	gtk_widget_queue_draw(data->pdf_data->drawing_area);
	update_pdf_statusbar(data);
}

static void pdf_scroll_cb(GtkWidget *drawing_area,
                GdkEventScroll *event,
                struct _data *data)
{
        switch (event->direction) {
        case GDK_SCROLL_RIGHT:
		if (data->pdf_data->current_page != 0)
			data->pdf_data->current_page -= 1;
		view_set_page(data);
                break;
        case GDK_SCROLL_LEFT:
		if (data->pdf_data->current_page 
				< (data->pdf_data->total_page - 1))
			data->pdf_data->current_page += 1;
		view_set_page(data);
                break;
        }
}

static void pdf_click_cb(
		GtkWidget *widget,
		GdkEventButton *event,
                struct _data *data)
{
	switch (event->button) {
	case 1:
		if (data->pdf_data->current_page 
				< (data->pdf_data->total_page - 1))
			data->pdf_data->current_page += 1;
		break;
	case 3:
		if (data->pdf_data->current_page != 0)
			data->pdf_data->current_page -= 1;
                break;
	}
	view_set_page(data);
}

void drawing_area_expose_cb(
		GtkWidget *drawing_area,
		GdkEventExpose *event,
		struct _data *data)
{
	float window_width = gtk_widget_get_allocated_width(
			data->pdf_data->drawing_area);
	float window_height = gtk_widget_get_allocated_height(
			data->pdf_data->drawing_area);
	float surface_width = cairo_image_surface_get_width(
			data->pdf_data->surface);
	float surface_height = cairo_image_surface_get_height(
			data->pdf_data->surface);

	float scale;
	scale = (window_width * surface_height / surface_width 
			> window_height)
		? (window_height / surface_height)
		: (window_width / surface_width);	       

	cairo_t *cr;
	cr = gdk_cairo_create(gtk_widget_get_window(drawing_area));

	cairo_scale(cr, scale, scale);

	cairo_set_source_surface(cr, data->pdf_data->surface, 0, 0);
	cairo_paint(cr);
	cairo_destroy(cr);
}

void initialize_pdf_preview(struct _data *data)
{
	struct _pdf_previewer *pdf_data;
	pdf_data = malloc(sizeof(struct _pdf_previewer));
	memset(pdf_data, 0, sizeof(*pdf_data));
	data->pdf_data = pdf_data;

	// status bar to show current and total page no.
	pdf_data->status_bar = gtk_statusbar_new();
	gtk_container_add(GTK_CONTAINER(data->preview_box), 
			pdf_data->status_bar);

	// Drawing area for cairo to draw pdf content
	pdf_data->drawing_area = gtk_drawing_area_new();
	gtk_box_pack_start(GTK_BOX(data->preview_box),
			pdf_data->drawing_area, 1, 1, 0);
	
	g_signal_connect(G_OBJECT(pdf_data->drawing_area), "draw",
			G_CALLBACK(drawing_area_expose_cb), data);

	gtk_widget_add_events(GTK_WIDGET(pdf_data->drawing_area),
			GDK_SCROLL_MASK);
        g_signal_connect(pdf_data->drawing_area, "scroll-event",
                        G_CALLBACK(pdf_scroll_cb), data);

        gtk_widget_add_events(GTK_WIDGET(pdf_data->drawing_area),
                        GDK_BUTTON_PRESS_MASK);
        g_signal_connect(pdf_data->drawing_area, "button_press_event",
                        G_CALLBACK(pdf_click_cb), data);
}

void pdf_document_preview(struct _data *data)
{
	g_print("showing pdf preview\n");
	
	gchar temp[2048] = "file://";
	strcat(temp, data->path);
	data->pdf_data->document = poppler_document_new_from_file(
			temp, NULL, NULL);
	if (data->pdf_data->document == NULL) {
		g_print("Unable to read the selected file\n");
		return;
	}
	data->pdf_data->total_page = poppler_document_get_n_pages(
			data->pdf_data->document);

	data->pdf_data->current_page = 0;
	view_set_page(data);

	gtk_widget_show_all(data->pdf_data->status_bar);
	gtk_widget_show_all(data->pdf_data->drawing_area);
}
