#include "grabber.h"

#include <X11/Xutil.h>
#include <stdlib.h>

using namespace std;

CGrabber::CGrabber()
{
	m_dpy = XOpenDisplay(NULL);  //try to open a dpy connection
	if (m_dpy == NULL)
	{
		m_error = "unable to open display";
		if (getenv("DISPLAY"))
			m_error += " " + string(getenv("DISPLAY"));
		else
			m_error += ", DISPLAY environment variable not set";

		return; //unrecoverable error
	}

	m_rootwin = RootWindow(m_dpy, DefaultScreen(m_dpy));
	getRootAttrs();

	m_error.clear();
}

CGrabber::~CGrabber()
{
	if (m_dpy) //close display connection if opened
	{
		XCloseDisplay(m_dpy);
		m_dpy = NULL;
	}
}

void CGrabber::getRootAttrs() //update size of root window
{
	XGetWindowAttributes(m_dpy, m_rootwin, &m_rootattr);
}


U32 CGrabber::sample(int x, int y)
{
	XImage* xim;
	unsigned long pixel;
	int rgb[3];

    getRootAttrs();

	//get an image of size 1x1 at the location
	xim = XGetImage(m_dpy, m_rootwin, x, y, 1, 1, AllPlanes, ZPixmap);

	//read out pixel
	pixel = XGetPixel(xim, 0, 0);
	XDestroyImage(xim);

	m_error.clear();
  
	return pixel;
}
