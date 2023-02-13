#ifndef _GL_GEOMETRY_OBJECT_H_
#define _GL_GEOMETRY_OBJECT_H_

#include <vector>

#include <GL/gl.h>

#include <mass_data.h>

#include "glTextLine.h"
#include "glFLTKcolor.h"

class GL_GEOMETRY_OBJECT : public MASS_OBJECT_DATA
{
	public:

	unsigned int ObjDiv; //divisions for drawing
	
	bool  Edges;
	GLfloat EdgesWidth;
	GLubyte EdgeRcolor, EdgeGcolor, EdgeBcolor;
	
	bool  Surfaces;
	GLfloat PointSize; //if type == M_POINT parameters taken from Surfaces
	GLubyte ObjRcolor, ObjGcolor, ObjBcolor, ObjAlfa;

	bool  CS;
	GLfloat CSsize, CSpointSize;
	
	GL_TEXT_LINE Label;

	MATRIX_3x3 RotMat;
	
	GL_GEOMETRY_OBJECT();

	int RotationMatrix();

	void SetEdgesColor(unsigned int c);
	void SetSurfacesColor(unsigned int c, float Alfa=1.f);
	void SetResolution(unsigned int v);

	void DrawObject();
    void DrawObjCS();
	void Draw_M_POINT();
	void Draw_DISC();
	void Draw_SPHERE();
	void Draw_CUBOID();
	void Draw_TUBE();
	void Draw_CYLINDER();
	void Draw_CONE();
	
	private:

	float ddiv;
	VECTOR_3D v_pos;

    void TransformVertex(GLfloat Vx, GLfloat Vy, GLfloat Vz);
	void CirclePoints(unsigned int i, GLfloat Rx, GLfloat Ry, GLfloat H);
};

#endif
