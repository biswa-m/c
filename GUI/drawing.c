#include <gtk/gtk.h>

static cairo_surface_t *surface = NULL;

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	return 0;
}

static void close_window(void)
{
	if (surface)
		cairo_surface_destroy(surface);
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window, *frame, *drawing_area;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Drawing Area");
	g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 8);

	frame = gtk_frame_new(NULL);
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(window), frame);

	drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(drawing_area, 100, 100); //set minimum size
	gtk_container_add(GTK_CONTAINER(frame), drawing_area);

	g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), NULL);

	/* Ask to receive events the drawing area doesn't normally 
	 * subscribe to. In particular, we need to ask for the
	 * button press and motion notify events that want to handle.
	 */
	gtk_widget_set_events(drawing_area, gtk_widget_get_events(drawing_area)
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK);

	gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.drawing", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
