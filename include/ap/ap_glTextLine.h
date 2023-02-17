#ifndef AP_GL_TEXT_LINE_H
#define AP_GL_TEXT_LINE_H

#include "ap_glTechFont.h"

/*
	USE WITHIN:

	glBegin (GL_LINES);
		glTextLine...
	glEnd();
*/

class GL_TEXT_LINE
{
	public:

	GLfloat Sep;	// Separation between letters
	GLfloat Small;	// Scale down Small letters
	GLfloat Size;	// Size of letters

	GL_TEXT_LINE();
	GL_TEXT_LINE(GLfloat Size_0, GLfloat Zoom_0, MATRIX_3x3 &RotationMatrix);
	void Init(GLfloat Size_0, GLfloat Zoom_0, MATRIX_3x3 &RotationMatrix);
	void Write(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, std::string Line);

	private:

	GLfloat 	Zoom;		// For constant size of letters, set 1 if it should scale
 	VECTOR_3D 	Origin;		// Origin of line
	MATRIX_3x3 	RotMatrix; 	// To rotate letters always perpendicular to the Screen
	
	void MoveOrigin(GLfloat LetterWidth);
};

#endif
