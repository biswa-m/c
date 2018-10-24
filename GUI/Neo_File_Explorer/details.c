void stop_preview(struct _data *data)
{
	gst_element_set_state(data->gst_data->playbin, GST_STATE_NULL);

	GList *previewers;
	previewers = gtk_container_get_children(
			GTK_CONTAINER(data->preview_box));
	while (previewers != NULL) {
		//gtk_widget_destroy(previewers->data);
		gtk_widget_hide(previewers->data);
		previewers = previewers->next;
	}

	//gtk_widget_destroy(data->drawing_area);
	//gtk_widget_destroy(data->gst_data->slider);


}

void show_details(struct _data *data)
{
	// Extract file name extension of the selected file
	char *extension = data->path;
	int i = strlen(extension);
	while (extension[i] != '.' && extension[i] != '/' && i)
		--i;
	extension  = (extension[i] == '.') ? &extension[i + 1] : NULL;

	g_print("%s\tstr= %s\n", data->path, extension);

	// Determine the file type based on extension 
	gint file_type = UNKNOWN_FILE;
	gboolean flag = (extension == NULL) ? 0 : 1;

	// search the extension in the video extension list
	for(i = 0; flag 
	&& i < sizeof(video_formats) / sizeof(video_formats[0]); ++i) {
		if (!strcasecmp(video_formats[i], extension)) {
			file_type = VIDEO_FILE;
			flag = 0;
			break;
		}	
	}
	// search the extension in the audio extension list
	for(i = 0; flag 
	&& i < sizeof(audio_formats) / sizeof(audio_formats[0]); ++i) {
		if (!strcasecmp(audio_formats[i], extension)) {
			file_type = AUDIO_FILE;
			flag = 0;
			break;
		}	
	}
	// search the extension in the image extension list
	for(i = 0; flag
	&& i < sizeof(image_formats) / sizeof(image_formats[0]); ++i) {
		if (!strcasecmp(image_formats[i], extension)) {
			file_type = IMAGE_FILE;
			flag = 0;
			break;
		}	
	}
	// search the extension in the plain text extension list
	for(i = 0; flag
	&& i < sizeof(text_formats) / sizeof(text_formats[0]); ++i) {
		if (!strcasecmp(text_formats[i], extension)) {
			file_type = PLAIN_TEXT_FILE;
			flag = 0;
			break;
		}	
	}
	// search the extension in the document extension list
	for(i = 0; flag
	&& i < sizeof(document_formats) / sizeof(document_formats[0]); ++i) {
		if (!strcasecmp(document_formats[i], extension)) {
			file_type = DOCUMENT_FILE;
			flag = 0;
			break;
		}	
	}

	switch (file_type) {
	
	case VIDEO_FILE:
	case AUDIO_FILE:
		g_print("call GStreamer api\n");
		media_preview(data);
		break;
	case IMAGE_FILE:
		g_print("call GStreamer api\n");
		media_preview(data);
		gtk_widget_hide(data->gst_data->slider);
		break;
	case PLAIN_TEXT_FILE:
		stop_preview(data);
		plain_text_preview(data);
		break;
	case DOCUMENT_FILE:
		stop_preview(data);
		pdf_document_preview(data);
		break;
	case UNKNOWN_FILE:
		stop_preview(data);
		g_print("Unknown file type\n");
		break;
	}
}
