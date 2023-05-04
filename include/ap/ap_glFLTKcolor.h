#ifndef AP_GL_FLTK_COLOR_H
#define AP_GL_FLTK_COLOR_H

#include <iostream>

#ifdef _MSC_VER          
	#include <windows.h>
#endif

#if defined(__APPLE__)
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <FL/Fl.H>
#include <FL/fl_show_colormap.H>

bool ColorIndex2RGB(unsigned int Index, GLubyte &Rcolor, GLubyte &Gcolor, GLubyte &Bcolor);
bool ColorAlfaValue(GLfloat Transparency, GLubyte &Alfa);
bool SetGLdrawColor(unsigned int Index, GLfloat Transparency = 1.f);

#endif //AP_GL_FLTK_COLOR_H
