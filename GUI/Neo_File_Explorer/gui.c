#include <gtk/gtk.h>
#include <dirent.h>
#include "support.h"

GtkWidget *file_view_area;
GtkWidget *list_box_1;
GtkWidget *add_bar;
GtkTreeSelection *selection;

gchar *dir;

static void add_dir_list(GtkWidget *, gpointer);

static void on_changed(GtkWidget *widget, gpointer add_bar)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	gchar *value;

	if (gtk_tree_selection_get_selected(
			GTK_TREE_SELECTION(widget), &model, &iter)) {
		gtk_tree_model_get(model, &iter, LIST_ITEM, &value, -1);

		g_print("\t%s\t", value);

		gtk_entry_set_text(GTK_ENTRY(add_bar), value);
		
		dir = "/";
		add_dir_list(NULL, NULL);
		
	}
}

static void add_dir_list(GtkWidget *p, gpointer data)
{
	GtkWidget *tree;
	tree = gtk_tree_view_new();
//	gtk_box_pack_start(GTK_BOX(file_view_area), tree, 1, 1, 0);
	gtk_container_add(GTK_CONTAINER(list_box_1), tree);
	
	GtkCellRenderer *renderer;
	renderer = gtk_cell_renderer_text_new();

	GtkTreeViewColumn *column;
	column = gtk_tree_view_column_new_with_attributes("List Items",
			renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree), column);

	GtkListStore *store;
	store = gtk_list_store_new(N_COLUMN, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree), GTK_TREE_MODEL(store));

	GtkTreeIter iter;
	
	int n;
	struct dirent **namelist;
	n = scandir(dir, &namelist, NULL, alphasort);
	if (n > 0) {
		while (n--) {
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, LIST_ITEM, 
					namelist[n]->d_name, -1);
			g_print("%s\t", namelist[n]->d_name);
		}
	}
	g_object_unref(store);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree));
	g_signal_connect(selection, "changed", G_CALLBACK(on_changed), 
			add_bar);

	gtk_widget_show(tree);

	return;
}

static void activate(GtkApplication *app, gpointer data)
{
	GError *error = NULL;

	GtkBuilder *builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, "gui_0.1.glade", &error)) {
		g_warning("%s", error->message);
		g_free(error);
		return;
	}

	GtkWidget *main_window;
	main_window = GTK_WIDGET(gtk_builder_get_object(builder, 
				"main_window"));
	gtk_window_set_application(GTK_WINDOW(main_window), app);

	add_bar = GTK_WIDGET(gtk_builder_get_object(builder, "add_bar"));
	gtk_entry_set_text(GTK_ENTRY(add_bar), "This is address bar");

	GtkWidget *file_view_port;
	file_view_area = GTK_WIDGET(gtk_builder_get_object(builder, 
			"file_view_port"));

	list_box_1 = GTK_WIDGET(gtk_builder_get_object(builder, 
			"list_box_1"));

//	GtkWidget *file_view_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//	gtk_container_add(GTK_CONTAINER(file_view_port), file_view_area);
	
	dir = "/home/neo";
	add_dir_list(NULL, NULL);

	g_object_unref(G_OBJECT(builder));
	gtk_widget_show_all(main_window);
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	app = gtk_application_new("org.gtk.explorer",
					G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

	int status;
	status = g_application_run(G_APPLICATION(app), 0, NULL);

	g_object_unref(app);

	return status;
}
