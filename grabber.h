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

private:
	void              getRootAttrs();

	std::string       m_error;
	Display*          m_dpy;
	Window            m_rootwin;
	XWindowAttributes m_rootattr;
};
