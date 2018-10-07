/*To create a window and get signal for button click
 * 
 * Use following syntex to compile
 * gcc `pkg-config --cflags gtk+-3.0` -o <output filename> \
 * <filename.c> `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

static void print(GtkWidget *, gpointer);
static void activate(GtkApplication *, gpointer);

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.hello_world",
			G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate",
			G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}

static void print(GtkWidget *widget, gpointer data)
{
	g_print("%s\n", (char *)data);
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *button_box;
	GtkWidget *button;
	GtkWidget *button1;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Biswa-M");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(window), button_box);

	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(button, "clicked", 
		G_CALLBACK(print), "Click Siganl Received");
	g_signal_connect_swapped(button, "clicked", 
			G_CALLBACK(gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER(button_box), button);
	
	gtk_widget_show_all(window);
}
