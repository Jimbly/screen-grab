#pragma once

#include <string>
#include <X11/Xlib.h>

typedef unsigned int U32;

class CGrabber
{
public:
	CGrabber();
	~CGrabber();

	//retrieves the latest error
	std::string& GetError() { return m_error; }

	// returns 0xRRGGBB
	U32 sample(int x, int y);
	void getMousePos(int &x, int &y);


	// A full list of available codes can be found in /usr/include/X11/keysymdef.h, e.g. XK_a
	void sendKey(unsigned int keysym);

private:
	void              getRootAttrs();

	std::string       m_error;
	Display*          m_dpy;
	Window            m_rootwin;
	XWindowAttributes m_rootattr;
};
