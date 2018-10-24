void initialize_text_preview(struct _data *data) {
	GtkTextBuffer *text_buffer = gtk_text_buffer_new(NULL);
	GtkWidget *text_view = gtk_text_view_new_with_buffer(text_buffer);

	GtkWidget *scroll_text = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_propagate_natural_height (
                        GTK_SCROLLED_WINDOW(scroll_text), TRUE);

	gtk_container_add(GTK_CONTAINER(data->preview_box), scroll_text);
	gtk_container_add(GTK_CONTAINER(scroll_text), text_view);

	data->text_scroll_window = scroll_text;
}

void plain_text_preview(struct _data *data)
{
	g_print("Preview plain text file\n");

	FILE *file = fopen(data->path, "r");
	
	GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(
			GTK_TEXT_VIEW(
			gtk_container_get_children(GTK_CONTAINER(
			data->text_scroll_window))->data));

	GtkTextIter iter, iter1;

	gtk_text_buffer_get_start_iter(text_buffer, &iter);
	gtk_text_buffer_get_end_iter(text_buffer, &iter1);

	gtk_text_buffer_delete(text_buffer, &iter, &iter1);

	gchar buf[10];	
	while (fgets(buf, sizeof(buf), file) != NULL) {
		gtk_text_buffer_get_end_iter(text_buffer, &iter);
		gtk_text_buffer_insert(text_buffer, &iter, buf, strlen(buf));
	}
	fclose(file);

	gtk_widget_show_all(data->text_scroll_window);
}
