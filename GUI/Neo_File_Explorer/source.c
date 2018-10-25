#include <sys/stat.h>
#include <math.h>

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <gdk/gdkx.h>
#include <poppler.h>

#include "support.h"
#include "media_previewer.c"
#include "plain_text_previewer.c"
#include "pdf_document_previewer.c"
#include "details.c"

static void main_control(struct _data *);

// Determine the file type
static int stat_of_path(char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	
	if(S_ISREG(path_stat.st_mode))
		return REGULAR_FILE;
	else if(S_ISDIR(path_stat.st_mode))
		return DIRECTORY;
	else
		return NOT_EXIST;
}

// open files in their default apps
void on_row_activated_cb(
		GtkTreeView *tree,
		GtkTreePath *path,
		GtkTreeViewColumn *column,
		struct _data *data)
{
	g_print("activated\n");

	GError *error = NULL;
	if (stat_of_path(data->path) == REGULAR_FILE) {
		gchar tmp[PATH_SIZE] = "file://";
		strcat(tmp, data->path);

		gtk_show_uri(gdk_screen_get_default(),
			tmp,
			GDK_CURRENT_TIME,
			&error);
	}
	if (error) { 
		g_warning("%s", error->message);
	}
}



// update address bar
static void show_address(struct _data *data)
{
	gtk_entry_set_text(GTK_ENTRY(data->add_bar), data->current_dir);
}

static void addbar_activate_cb(GtkWidget *add_bar, struct _data *data)
{
	gchar tmp[PATH_SIZE];
	strcpy(tmp, gtk_entry_get_text(GTK_ENTRY(add_bar)));

	switch (stat_of_path(tmp)) {
	case REGULAR_FILE:
		strcpy(data->path, tmp);
		on_row_activated_cb(NULL, NULL, NULL, data);
		break;
	case DIRECTORY:
		data->current_dir[0] = '\0';
		strcpy(data->path, tmp);
		data->tree_no = 0;
		main_control(data);
		break;
	case NOT_EXIST:
		return;
	};
}

// on new selection retrive selected data and call main_control()
static void on_changed_cb(GtkWidget *widget, struct _data *data)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	gchar *value;
	gchar *dir;
	gint tree_no;

	if (gtk_tree_selection_get_selected
	(GTK_TREE_SELECTION(widget), &model, &iter)) {
		gtk_tree_model_get(model, &iter, 
				LIST_ITEM, &value,
				TREE_NO, &tree_no,
				DIR_NAME, &dir,
					-1);
	}
	strcpy(data->path, value);
	strcpy(data->current_dir, dir);
	data->tree_no = tree_no;

	main_control(data);
}

static void show_list(struct _data *data)
{
	int tree_no = ++data->tree_no;

	// create new gtk widgets to view list 
	GtkWidget *tree = gtk_tree_view_new();

	GtkWidget *tree_scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_propagate_natural_width (
			GTK_SCROLLED_WINDOW(tree_scroll), TRUE);

	gtk_box_pack_start(GTK_BOX(data->container), tree_scroll, 0, 0, 2);
	gtk_container_add(GTK_CONTAINER(tree_scroll), tree);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(tree_scroll),
                        GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

	// store widget pointer so that it can be destroyed later	
	data->tree_array_pointer[tree_no -1] = tree_scroll;

	// Initialize data storing process to gtk tree
	GtkCellRenderer *renderer;
	renderer = gtk_cell_renderer_text_new();

	GtkTreeViewColumn *column;
	column = gtk_tree_view_column_new_with_attributes(
			"Names", renderer, "text", 0, NULL);
	gtk_tree_view_column_set_min_width(
			GTK_TREE_VIEW_COLUMN(column), 200);
	gtk_tree_view_append_column(
			GTK_TREE_VIEW(tree), column);

	// list store holds 2 hidden columns besides filename
	GtkListStore *store = gtk_list_store_new(N_COLUMN, G_TYPE_STRING,
			G_TYPE_INT, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(tree), GTK_TREE_MODEL(store));

	// generate the list of files in current directory
	int n;
	struct dirent **namelist;
	n = scandir(data->current_dir, &namelist, NULL, alphasort);
	printf("total no of items in %s is %d\n", data->current_dir, n);
	
	// append file list to gtk tree along with hidden information
	GtkTreeIter iter;
	for (int i = 0; i < n; i++) {
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, 
				LIST_ITEM, namelist[i]->d_name, 
				TREE_NO, tree_no,
				DIR_NAME, data->current_dir,	
				-1);
	}
	g_object_unref(store);

	data->selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree));

	// Connect callback functions
	g_signal_connect(data->selection, "changed",
			G_CALLBACK(on_changed_cb), data);
	g_signal_connect(tree, "row-activated", 
			G_CALLBACK(on_row_activated_cb), data);

	// Adjusting horizontal scroll bar
	gtk_adjustment_set_value(gtk_scrollable_get_hadjustment(
		data->main_view_port),
		gtk_adjustment_get_upper(
		gtk_scrollable_get_hadjustment(data->main_view_port)));
				
	gtk_widget_show_all(tree_scroll);
}

static void main_control(struct _data *data)
{
	// tree_count will hold total no. of file list currently showing
	static int tree_count = 0;

	// If selected row is not from the right most list
	// destroy all the lists to the right side
	if (data->tree_no == tree_count) {
		g_print("new list\n");
	} else {
		for (int i = data->tree_no; i < tree_count; ++i) {
			gtk_widget_destroy(
			*(data->tree_array_pointer + i));	
		}
		tree_count = data->tree_no;
	}

	// store the file path to the selected item in tmp
	gchar tmp[PATH_SIZE];
	tmp[0] = '\0';
	strcat(tmp, data->current_dir);
	strcat(tmp, data->path);

	// handle differnt typs of file accordingly	
	switch(stat_of_path(tmp)) {
	case NOT_EXIST: //must be some runtime error
		g_print("Not_exist");
		sleep(3);
		exit(1);
	case REGULAR_FILE:
		strcpy(data->path, tmp);
		show_details(data);
		show_address(data);
		break;

	case DIRECTORY: 
		stop_preview(data);

		// append '/' to the directory path
		(tmp[strlen(tmp)-1] == '/') 
			? 0 
			: strcat(tmp, "/\0");

		strcpy(data->current_dir, tmp);

		if (tree_count >= MAX_TREE_NUM) { 
			g_print("Limit reached:");	
			g_print(" Could not create more list.\n");
			break;
		}
		++tree_count;
		show_address(data);
		show_list(data);
		break;
	};
}

static void activate_cb(GtkApplication *app, char *argv)
{
	// Initialize GUI
	GError *error = NULL;
	GtkBuilder *builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, "gui_0.1.glade", &error)) {
		g_warning("%s", error->message);
		return;
	}
	GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, 
				"main_window"));
	gtk_window_set_application(GTK_WINDOW(main_window), app);

	GtkWidget *add_bar = GTK_WIDGET(gtk_builder_get_object(builder,
				"add_bar"));

	GtkWidget *file_view_port;
	file_view_port = GTK_WIDGET(gtk_builder_get_object(builder, 
				"file_view_port"));
	gtk_adjustment_set_upper(
			gtk_scrollable_get_hadjustment(file_view_port), 1.);

	GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	gtk_container_add(GTK_CONTAINER(file_view_port), hbox);

	GtkWidget *preview_box = GTK_WIDGET(gtk_builder_get_object(builder,
				"v_box_2"));

	// custom structure to hold all data need to pass to other functions
	struct _data *data = malloc(sizeof(struct _data));
	memset(data, 0, sizeof(struct _data));
	
	data->main_view_port = file_view_port;
	data->container = hbox;
	data->add_bar = add_bar;
	data->preview_box = preview_box;

	GtkWidget **tree_array = malloc(sizeof(GtkWidget *) * MAX_TREE_NUM);
	data->tree_array_pointer = tree_array;

	gchar *path = malloc(sizeof(char) * 255);
	strcpy(path, argv);
	data->path = path;

	gchar *current_dir = malloc(sizeof(char) * 255);
	current_dir[0] = '\0';
	data->current_dir = current_dir;

	// Initialize GStreamer
	initialize_gst(data);	

	// Function for file listing and call for preview
	main_control(data);

	// Show all widget for file listing
	gtk_widget_show_all(main_window);

	// Initialize previews
	initialize_text_preview(data);
	initialize_video_preview(data);
	initialize_pdf_preview(data);

	g_object_unref(G_OBJECT(builder));

	g_signal_connect(GTK_WIDGET(add_bar), "activate",
				G_CALLBACK(addbar_activate_cb), data);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Pass the directory path as arguement\n");
		exit(1);
	}

	// Initialize gtk
	GtkApplication *app;
	app = gtk_application_new("org.gtk.explorer", 
					G_APPLICATION_FLAGS_NONE);

	g_signal_connect(app, "activate", G_CALLBACK(activate_cb), argv[1]);

	// strt the main loop
	int status = g_application_run(G_APPLICATION(app), 0, NULL);

	// Clean ups
	g_object_unref(app);
	
	return status;
}
