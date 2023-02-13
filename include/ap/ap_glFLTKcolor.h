#ifndef _GL_FLTK_COLOR_H_
#define _GL_FLTK_COLOR_H_

#include <iostream>

#include <FL/gl.h>
#include <FL/Fl.H>
#include <FL/fl_show_colormap.H>

bool ColorIndex2RGB(unsigned int Index, GLubyte &Rcolor, GLubyte &Gcolor, GLubyte &Bcolor);
bool ColorAlfaValue(GLfloat Transparency, GLubyte &Alfa);
bool SetGLdrawColor(unsigned int Index, GLfloat Transparency = 1.f);

#endif
