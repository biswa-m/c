#include <sys/stat.h>

#include <gtk/gtk.h>
#include "support.h"

static void main_control(GtkWidget *, struct _data *);

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

static void show_address(struct _data *data)
{
	gtk_entry_set_text(GTK_ENTRY(data->add_bar), data->current_dir);
}

static void show_details(struct _data *data)
{
	printf("show data on details tab\n");
}

static void on_changed(GtkWidget *widget, struct _data *data)
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

	main_control(NULL, data);
}

static void show_list(struct _data *data)
{
	int tree_no = ++data->tree_no;

	GtkWidget *tree;
	tree = gtk_tree_view_new();
	
	*(data->tree_array_pointer + (tree_no -1)) = tree;

	gtk_container_add(GTK_CONTAINER(data->container), tree);

	GtkCellRenderer *renderer;
	renderer = gtk_cell_renderer_text_new();

	GtkTreeViewColumn *column;
	column = gtk_tree_view_column_new_with_attributes("Names", 
			renderer, "text", 0, NULL);
	gtk_tree_view_column_set_min_width(GTK_TREE_VIEW_COLUMN(column), 200);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree), column);

	GtkListStore *store;
	store = gtk_list_store_new(N_COLUMN, G_TYPE_STRING, 
			G_TYPE_INT, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree), GTK_TREE_MODEL(store));

	GtkTreeIter iter;
	
	int n;
	struct dirent **namelist;
	n = scandir(data->current_dir, &namelist, NULL, alphasort);
	if (n > 0) {
		while (n--) {
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, 
					LIST_ITEM, namelist[n]->d_name, 
					TREE_NO, tree_no,
					DIR_NAME, data->current_dir,	
					-1);
		}
	}
	g_object_unref(store);

	GtkTreeSelection *selection;
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree));
	g_signal_connect(selection, "changed", G_CALLBACK(on_changed), 
			data);
	
	gtk_widget_show(tree);
}

static void main_control(GtkWidget *widget, struct _data *data)
{

	static int tree_count = 0;
	gchar tmp[255];
	tmp[0] = '\0';

	g_print("\nmain_control\t");
	g_print("tree_cot = %d, data->tc = %d, data->cd = %s, data->pth = %s",
		tree_count, data->tree_no, data->current_dir, data->path);

	if (data->tree_no == tree_count) {
		g_print("\t new list\t%s \n", tmp);
	} else {
		for (int i = data->tree_no; i < tree_count; ++i) {
			gtk_widget_destroy(
			*(data->tree_array_pointer + i));	
		}
		tree_count = data->tree_no;
	}

	strcat(tmp, data->current_dir);
	strcat(tmp, data->path);
	
	switch(stat_of_path(tmp)) {
	case NOT_EXIST:
		show_details(data);
		g_print("Not_exist");
		sleep(3);
		exit(11);
	case REGULAR_FILE:
		show_details(data);
		g_print("reg");
		break;
	case DIRECTORY:
		(tmp[strlen(tmp)-1] == '/') 
			? 0 
			: strcat(tmp, "/\0");

		strcpy(data->current_dir, tmp);
		show_address(data);
		show_details(data);
		show_list(data);
		++tree_count;
		break;
	};
}

static void gui_init(GtkApplication *app, char *argv)
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

	GtkWidget *add_bar;
	add_bar = GTK_WIDGET(gtk_builder_get_object(builder, "add_bar"));

	GtkWidget *file_view_port;
	file_view_port = GTK_WIDGET(gtk_builder_get_object(builder, 
				"file_view_port"));

	GtkWidget *hbox;
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	gtk_container_add(GTK_CONTAINER(file_view_port), hbox);

	struct _data *data = malloc(sizeof(struct _data));

	data->container = hbox;

	gchar *current_dir = malloc(sizeof(char) * 255);
	current_dir[0] = '\0';

	gchar *path = malloc(sizeof(char) * 255);
	strcpy(path, argv);
	data->path = path;
	
	GtkWidget *tree_array = malloc(sizeof(GtkWidget *) * MAX_TREE_NUM);
	data->tree_array_pointer = tree_array;

	data->add_bar = add_bar;
	data->current_dir = current_dir;
	data->tree_no = 0;

	main_control(NULL, data);

	g_object_unref(G_OBJECT(builder));
	gtk_widget_show_all(main_window);
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	app = gtk_application_new("org.gtk.explorer", 
					G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(gui_init), argv[1]);

	int status = g_application_run(G_APPLICATION(app), 0, NULL);

	g_object_unref(app);

	return status;
}
