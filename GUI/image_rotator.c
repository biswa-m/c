// Image viewer and rotator
 
/* Use following command to compile
 * gcc `pkg-config --cflags gtk+-3.0` -o <output filename> \
 * <filename.c> `pkg-config --libs gtk+-3.0`
 *
 * To run the application provide file name as command line arguement.
 */

#include <gtk/gtk.h>

GdkPixbuf *pb;
GtkWidget *image;
GtkWidget *window;

static void activate(GtkApplication *, gpointer);

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Provide file name as command line arguement\n");
	}
	GtkApplication *app;

	app = gtk_application_new("org.gtk.hello_world",
			G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate",
			G_CALLBACK(activate), *(argv + 1));
	int status;
	status = g_application_run(G_APPLICATION(app), 0, NULL);
	g_object_unref(app);

	return status;
}

static void rotate_left(GtkWidget *widget, gpointer data)
{
	pb = gdk_pixbuf_rotate_simple(pb, 90);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pb);

	printf("Rotate_left\n");
}

static void rotate_right(GtkWidget *widget, gpointer data)
{
	pb = gdk_pixbuf_rotate_simple(pb, 270);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pb);

	printf("Rotate_right\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Biswa-M");
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	GtkWidget *s_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(s_window), 10);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(s_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
	gtk_scrolled_window_set_min_content_height(
			GTK_SCROLLED_WINDOW(s_window), 100);

	gtk_box_pack_start(GTK_BOX(box), s_window, 1, 0, 1);

	pb = gdk_pixbuf_new_from_file(user_data, NULL);
	image = gtk_image_new_from_pixbuf(pb);

	gtk_container_add(GTK_CONTAINER(s_window), image);

	GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_box_pack_start(GTK_BOX(box), button_box, 0, 0, 1);
	
	GtkWidget *button1 = gtk_button_new_with_label("Rotate left");
	g_signal_connect(button1, "clicked", 
		G_CALLBACK(rotate_left), NULL);
	gtk_box_pack_start(GTK_BOX(button_box), button1, 1, 0, 1);

	GtkWidget *button2 = gtk_button_new_with_label("Rotate right");
	g_signal_connect(button2, "clicked", 
		G_CALLBACK(rotate_right), NULL);

	gtk_box_pack_start(GTK_BOX(button_box), button2, 1, 0, 1);

	gtk_widget_show_all(window);
}
