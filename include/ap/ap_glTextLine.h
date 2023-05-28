#ifndef AP_GL_TEXT_LINE_H
#define AP_GL_TEXT_LINE_H

#include "ap_glTechFont.h"

namespace ap {

//! Displayes line of text in Open Gl space
/*
	USE WITHIN:

	glBegin (GL_LINES);
		glTextLine...
	glEnd();
*/
class GL_TEXT_LINE
{
	public:

	GLfloat sep_;	//!< Separation between letters
	GLfloat small_;	//!< Scale down Small letters
	GLfloat size_;	//!< Size of letters

	//! Default constructor
	GL_TEXT_LINE();
	
	//! Constructor with parameters
	/*!
	 * \param size_0 - sets size of the characters
	 * \param zoom_0 - current zoom parameter passed, used to keep character size constant while resizing model
	 * \param rotationMatrix - current rotation matrix passed, used to derotate the character perpendicular to the screen 
	 */
	GL_TEXT_LINE(GLfloat size, GLfloat zoom, MATRIX_3x3 <GLfloat> &rotationMatrix);
	
	//! Initializes the object if the default constructor without parameters was used
	/*!
	 * \param size_0 - sets size of the characters
	 * \param zoom_0 - current zoom parameter passed, used to keep character size constant while resizing model
	 * \param rotationMatrix - current rotation matrix passed, used to derotate the character perpendicular to the screen 
	 */
	void Init(GLfloat size, GLfloat zoom, MATRIX_3x3 <GLfloat> &rotationMatrix);
	
	//! Displayes line of the text in the Open Gl space
	/*!
	 * \param x_pos - x position of the origin of the text line 
	 * \param y_pos - y position of the origin of the text line 
	 * \param z_pos - z position of the origin of the text line 
	 * \param line - line of text to be displayed 
	 */
	void Write(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, std::string line);

	private:

	GLfloat 				zoom_;		// For constant size of letters, set 1 if it should scale
 	VECTOR_3 <GLfloat> 		origin_;	// Origin of line
	MATRIX_3x3 <GLfloat>	rotMatrix_;	// To rotate letters always perpendicular to the Screen
	
	void MoveOrigin(GLfloat letterWidth);
};

} // namespace ap

#endif
