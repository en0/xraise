#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

Window Window_With_Name(Display *dpy, Window *top, char *name) {
	Window *children, dummy;
	unsigned int nchildren;
	int i;
	Window w=0;
	char *window_name;

	if(XFetchName(dpy, top, &window_name) && (strstr(window_name, name) == window_name))
	      return(top);

    if (!XQueryTree(dpy, top, &dummy, &dummy, &children, &nchildren))
      return(0);

    for (i=0; i<nchildren; i++)
        {
        w = Window_With_Name(dpy, children[i], name);
        if (w)
          break;
    }
    if (children) XFree ((char *)children);
      return(w);
}

int main(int argc, char **argv)
{
    Window window;
    Display *dpy;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s window-name\n", argv[0]);
        exit(1);
    }

    dpy = XOpenDisplay(":0");
    if (!dpy)
    {
        fprintf(stderr, "Cannot open display.\n");
        exit(1);
    }

    window = Window_With_Name(dpy, DefaultRootWindow(dpy), argv[1]);
    if (!window)
    {
        fprintf(stderr, "Cannot find a window by that name.\n");
        exit(1);
    }

    //XSetInputFocus(dpy, window, RevertToPointerRoot, CurrentTime);
    if(!XRaiseWindow(dpy, window))
    {
        fprintf(stderr, "XRaiseWindow error?\n");
        exit(1);
    }

    XCloseDisplay(dpy);
}
