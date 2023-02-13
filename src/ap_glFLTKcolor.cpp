#include "glFLTKcolor.h"

using namespace std;

bool ColorIndex2RGB(unsigned int Index, GLubyte &Rcolor, GLubyte &Gcolor, GLubyte &Bcolor)
{
    if(0 > Index || Index > 255)
    {
        clog << "Color Index out of range <0,255> !!!" << endl;
        return 1;
    }

	/*unsigned int rgb = Fl::get_color(val);
	Rcolor = (rgb >> 24)& 0xFF;
	Gcolor = (rgb >> 16)& 0xFF;
	Bcolor = (rgb >> 8)& 0xFF;*/
	Fl::get_color(Index, Rcolor, Gcolor, Bcolor);

    return 0;
}

bool ColorAlfaValue(GLfloat Transparency, GLubyte &Alfa)
{
    if(0.0 > Transparency || Transparency > 1.0)
    {
        clog << "Color Alfa out of range <0,1> !!!" << endl;
        return 1;
    }

    Alfa = static_cast<GLubyte>(Transparency*255.f);

    return 0;
}

bool SetGLdrawColor(unsigned int Index, GLfloat Transparency)
{
    GLubyte r, g, b, a;

    if(ColorIndex2RGB(Index, r, g, b))
    {
        return 1;
    }

    if(ColorAlfaValue(Transparency, a))
    {
        return 1;
    }

    glColor4ub(r, g, b, a);

    return 0;
}
