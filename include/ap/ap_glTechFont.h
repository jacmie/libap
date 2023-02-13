#ifndef _GL_TECH_FONT_H_
#define _GL_TECH_FONT_H_

#include <GL/gl.h>

#include <matr3d.h>
#include <vector3d.h>

/*
	USE WITHIN:

	glBegin (GL_LINES);
		glTextLine...
	glEnd();

 w = 8 units (letters)
 w = 6 units (numbers)
 w = 1-6 units (symbols)
<------------------>
         /\          A
        /  \         |
       /    \        |
      /      \       |
     /        \      | h = 10 units
    /__________\     | (normalized to 1.0 in gl before scaling for Big letters)
   /            \    | (normalized to 0.6 in gl before scaling for Small letters)
  /              \   |
 /                \  |
/                  \ V__
                      s = 2 units (separation)

*/

class GL_TECH_FONT
{
	public:

	bool  MoveOriginWithRotation;
	GLfloat Scale;

	GL_TECH_FONT(GLfloat Size, MATRIX_3x3 &RotationMatrix);

	private:

 	VECTOR_3D 	Origin;
    MATRIX_3x3 	RotMatrix;
    MATRIX_3x3 	RotMatrixInv;
	
	void LetterOrigin(GLfloat &x_pos, GLfloat &y_pos, GLfloat &z_pos);
	void Vertex(GLfloat x_pos, GLfloat y_pos);
	
	public:

	void A(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void B(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void C(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void D(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void E(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void F(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void G(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void H(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void I(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void J(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void K(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void L(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void M(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void N(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void O(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void P(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Q(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void R(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void S(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void T(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void U(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void V(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void W(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void X(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Y(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Z(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	
	void Num0(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num1(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num2(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num3(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num4(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num5(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num6(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num7(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num8(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Num9(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	
	void OpenBrace(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void OpenSqBracket(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void OpenBracket(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Less(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Tilda(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void ExclamationMark(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Monkey(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Hash(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Dolar(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Percent(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Bird(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void And(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Star(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Underscore(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Plus(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Minus(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Equal(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Vline(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Slash(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void BackSlash(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Colon(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void SemiColon(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Quote(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Apostrophe(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Dot(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void Coma(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void QuestionMark(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void More(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void CloseBracket(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void CloseSqBracket(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void CloseBrace(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
	void NoChar(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos);
};

#endif
