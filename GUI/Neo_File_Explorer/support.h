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

struct _data {
	GtkWidget *container;
	GtkWidget *add_bar;
	GtkWidget **tree_array_pointer;
	char *path;
	char *current_dir;
	gint tree_no;
};
#define MAX_TREE_NUM 127

#endif
