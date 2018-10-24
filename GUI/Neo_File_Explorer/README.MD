## File Browser Application using GTK 3.22

## Compile using gcc
	gcc source.c `pkg-config --cflags --libs gtk+-3.0 gstreamer-1.0 gstreamer-video-1.0 poppler-glib` -lm

## Run application
	./a.out <path>
Example: "./a.out /usr"

## API used
GTK+ for creating the gui application.
Glade 3.22.1 to build static gtk windows and container.
GStreamer for video, audio and image preview.
Poppler for pdf preview.

## File Description
### 1. support.h

Contains definations of macros and structures.

### 2. source.c 
Contains main().
Other files are included in the code. So only need to compile this file.
The codes for the main file browsing operations are in here. 

### 3. gui_0.1.glade
This file contains definations for toplevel window and some static containers in xml format.

### 4. details.c
This file contains codes for managing the preview panel. 

### 5. plain_text_previewer.c
Codes to preview plain text file.

### 6. media_previewer.c
Codes to preview image, video and audio files.

### 7. pdf_document_previewer.c
Codes to preview pdf document files.
