#ifdef WIN32
#include <X11/Xwindows.h>
#endif

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Display *dpy;                        /* X connection */
	char *displayname = NULL;            /* server to contact */
	int i;

	dpy = XOpenDisplay (displayname);
    	if (!dpy) {
        	fprintf (stderr, "unable to open display \"%s\".\n",
                XDisplayName (displayname));
        	exit (1);
    	}
	
	printf ("name of display:    %s\n", DisplayString (dpy));
    	printf ("default screen number:    %d\n", DefaultScreen (dpy));
    	printf ("number of screens:    %d\n", ScreenCount (dpy));	
	printf ("display width:    %d\n", DisplayWidth (dpy, 0));
	printf ("display height:     %d\n", DisplayHeight (dpy, 0));
}
