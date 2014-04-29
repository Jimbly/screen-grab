#include "grabber.h"

#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <stdlib.h>
#include <unistd.h>

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
	getRootAttrs();

	//get an image of size 1x1 at the location
	XImage* xim = XGetImage(m_dpy, m_rootwin, x, y, 1, 1, AllPlanes, ZPixmap);

	//read out pixel
	unsigned long pixel = XGetPixel(xim, 0, 0);
	XDestroyImage(xim);

	m_error.clear();
  
	return pixel;
}

void CGrabber::getMousePos(int &x, int &y) {
	Window root, child;
	int rootX, rootY, winX, winY;
	unsigned int mask;
	XQueryPointer(m_dpy, DefaultRootWindow(m_dpy), &root, &child, &rootX, &rootY, &winX, &winY, &mask);
	x = rootX;
	y = rootY;
}

void CGrabber::sendKey(unsigned int keysym) {
	// The key code to be sent.

	// Send a fake key press event to the window.
	unsigned int keycode     = XKeysymToKeycode(m_dpy, keysym);
	XTestFakeKeyEvent(m_dpy, keycode, True, CurrentTime);

	usleep(100000);
	// Send a fake key release event to the window.
	XTestFakeKeyEvent(m_dpy, keycode, False, CurrentTime);
	XFlush(m_dpy);
}
