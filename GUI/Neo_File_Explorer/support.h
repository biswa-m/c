#ifndef __SUPPORT_H
#define __SUPPORT_H

enum list_store{
	LIST_ITEM,
	TREE_NO,
	DIR_NAME,
	N_COLUMN
};

enum path_stat{
	NOT_EXIST,
	REGULAR_FILE,
	DIRECTORY,
};

enum file_format {
	VIDEO_FILE,
	AUDIO_FILE,
	IMAGE_FILE,
	PLAIN_TEXT_FILE,
	DOCUMENT_FILE,
	UNKNOWN_FILE
};

struct _media_previewer {
        GstElement *playbin;

        GtkWidget *slider;
        GtkWidget *streams_list;
        gulong slider_update_signal_id;

        GstState state;
        gint64 duration;
};

struct _pdf_previewer {
	GtkWidget *drawing_area;
	GtkWidget *status_bar;
	
	PopplerDocument *document;
	cairo_surface_t *surface;

	int total_page;
	int current_page;
};

struct _data {
	GtkWidget *container;
	GtkWidget *add_bar;
	GtkWidget *drawing_area;
	GtkWidget *text_scroll_window;
	GtkWidget *pdf_scroll_window;
	GtkWidget *preview_box;
	GdkPixbuf *pixbuf;
	GtkWidget **tree_array_pointer;
	GtkTreeSelection *selection;
	gulong changed_select_id;
	char *path;
	char *current_dir;
	gint tree_no;
	struct _media_previewer *gst_data;
	struct _pdf_previewer *pdf_data;
};

char *video_formats[] = {"asf", "avi", "3gp", "mp4", "mov", "wmv",
     			"flv", "mpeg", "mkv", "webm", "mxf", "ogg"};
char *audio_formats[] = {"mp3", "mp4", "wav", "wma", "b-mtp", "spx"};
char *image_formats[] = {"jpg", "jpeg", "jfif", "tiff", "gif", "bmp", "png",
			"ppm", "pgm", "pbm", "pnm", "webp"};
char *text_formats[] = {"txt", "c", "xml", "html", "php"};
char *document_formats[] = {"pdf"};

#define MAX_TREE_NUM 127 
#define PATH_SIZE 2048

#endif
