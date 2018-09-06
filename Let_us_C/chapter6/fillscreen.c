// Fill the screen with smiley face.

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
        Display *dpy;                        /* X connection */
        char *displayname = NULL;            /* server to contact */

        dpy = XOpenDisplay (displayname);
        if (!dpy) {
                fprintf (stderr, "unable to open display \"%s\".\n",
                XDisplayName (displayname));
                exit (1);
        }
        
	int width, height, i, j;

	width = DisplayWidth(dpy, 0);
	height = DisplayHeight(dpy, 0);	
	
	for(i = 1; i <= height/21; i++) 	
	{
		for(j = 0; j <= width/30; j++)
			printf("%c%c ", ':',')');
		printf("\n");
	}
	return 0;
}
