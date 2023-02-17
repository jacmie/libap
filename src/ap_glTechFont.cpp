#include "ap_glTechFont.h"

GL_TECH_FONT::GL_TECH_FONT(GLfloat Size, MATRIX_3x3 &RotationMatrix)
{
	Scale 		 = 0.1;
	Scale 		 *= Size;

	MoveOriginWithRotation = 1;
	
	RotMatrix    = RotationMatrix;
	RotMatrixInv = !RotMatrix;
}

void GL_TECH_FONT::LetterOrigin(GLfloat &x_pos, GLfloat &y_pos, GLfloat &z_pos)
{
	if(MoveOriginWithRotation)
	{
 		VECTOR_3D Oinit; 
 		Oinit.GetFrom(x_pos, y_pos, z_pos);
 		Origin = RotMatrix * Oinit;
	}

	else
 		Origin.GetFrom(x_pos, y_pos, z_pos);
}

void GL_TECH_FONT::Vertex(GLfloat x_pos, GLfloat y_pos)
{
 	VECTOR_3D Ver; 
 	VECTOR_3D VerW;
 	
	Ver.GetFrom(x_pos*Scale, y_pos*Scale, 0);
 	Ver += Origin;
 	VerW = RotMatrixInv * Ver;
	glVertex3f (VerW.x, VerW.y, VerW.z);            
}

void GL_TECH_FONT::A(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(4, 10);
	Vertex(4, 10);
	Vertex(8,  0);
	Vertex(2, 5);
	Vertex(6, 5);
}

void GL_TECH_FONT::B(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(6, 10);
	Vertex(6, 10);
	Vertex(8, 8.5);
	Vertex(8, 8.5);
	Vertex(8, 6.5);
	Vertex(8, 6.5);
	Vertex(6, 5);
	Vertex(6, 5);
	Vertex(0, 5);
	Vertex(6, 5);
	Vertex(8, 3.5);
	Vertex(8, 3.5);
	Vertex(8, 1.5);
	Vertex(8, 1.5);
	Vertex(6, 0);
	Vertex(6, 0);
	Vertex(0, 0);
}

void GL_TECH_FONT::C(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(8, 0);
	Vertex(2, 0);
	Vertex(2, 0);
	Vertex(0, 2);
	Vertex(0, 2);
	Vertex(0, 8);
	Vertex(0, 8);
	Vertex(2, 10);
	Vertex(2, 10);
	Vertex(8, 10);
}

void GL_TECH_FONT::D(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(6, 10);
	Vertex(6, 10);
	Vertex(8, 8);
	Vertex(8, 8);
	Vertex(8, 2);
	Vertex(8, 2);
	Vertex(6, 0);
	Vertex(6, 0);
	Vertex(0, 0);
}

void GL_TECH_FONT::E(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(8, 10);
	Vertex(0, 5);
	Vertex(6, 5);
	Vertex(0, 0);
	Vertex(8, 0);
}

void GL_TECH_FONT::F(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(8, 10);
	Vertex(0, 5);
	Vertex(6, 5);
}

void GL_TECH_FONT::G(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(6, 5);
	Vertex(8, 5);
	Vertex(8, 5);
	Vertex(8, 2);
	Vertex(8, 2);
	Vertex(6, 0);
	Vertex(6, 0);
	Vertex(2, 0);
	Vertex(2, 0);
	Vertex(0, 2);
	Vertex(0, 2);
	Vertex(0, 8);
	Vertex(0, 8);
	Vertex(2, 10);
	Vertex(2, 10);
	Vertex(6, 10);
	Vertex(6, 10);
	Vertex(8, 8);
}

void GL_TECH_FONT::H(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(8, 0);
	Vertex(8, 10);
	Vertex(0, 5);
	Vertex(8, 5);
}

void GL_TECH_FONT::I(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(5, 0);
	Vertex(5, 10);
}

void GL_TECH_FONT::J(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 10);
	Vertex(8, 10);
	Vertex(8, 10);
	Vertex(8, 3);
	Vertex(8, 3);
	Vertex(5, 0);
	Vertex(5, 0);
	Vertex(0, 0);
}

void GL_TECH_FONT::K(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 5);
	Vertex(8, 10);
	Vertex(0, 5);
	Vertex(8, 0);
}

void GL_TECH_FONT::L(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 0);
	Vertex(8, 0);
}

void GL_TECH_FONT::M(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(4, 5);
	Vertex(4, 5);
	Vertex(8, 10);
	Vertex(8, 10);
	Vertex(8, 0);
}

void GL_TECH_FONT::N(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(8, 0);
	Vertex(8, 0);
	Vertex(8, 10);
}

void GL_TECH_FONT::O(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(2, 0);
	Vertex(0, 2);
	Vertex(0, 2);
	Vertex(0, 8);
	Vertex(0, 8);
	Vertex(2, 10);
	Vertex(2, 10);
	Vertex(6, 10);
	Vertex(6, 10);
	Vertex(8, 8);
	Vertex(8, 8);
	Vertex(8, 2);
	Vertex(8, 2);
	Vertex(6, 0);
	Vertex(6, 0);
	Vertex(2, 0);
}

void GL_TECH_FONT::P(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(6, 10);
	Vertex(6, 10);
	Vertex(8, 8.5);
	Vertex(8, 8.5);
	Vertex(8, 6.5);
	Vertex(8, 6.5);
	Vertex(6, 5);
	Vertex(6, 5);
	Vertex(0, 5);
}

void GL_TECH_FONT::Q(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(2, 0);
	Vertex(0, 2);
	Vertex(0, 2);
	Vertex(0, 8);
	Vertex(0, 8);
	Vertex(2, 10);
	Vertex(2, 10);
	Vertex(6, 10);
	Vertex(6, 10);
	Vertex(8, 8);
	Vertex(8, 8);
	Vertex(8, 2);
	Vertex(8, 2);
	Vertex(6, 0);
	Vertex(6, 0);
	Vertex(2, 0);
	
	Vertex(5.5, 2.5);
	Vertex(8.5, -0.5);
}

void GL_TECH_FONT::R(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(6, 10);
	Vertex(6, 10);
	Vertex(8, 8.5);
	Vertex(8, 8.5);
	Vertex(8, 6.5);
	Vertex(8, 6.5);
	Vertex(6, 5);
	Vertex(6, 5);
	Vertex(0, 5);
	Vertex(0, 5);
	Vertex(8, 0);
}

void GL_TECH_FONT::S(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(8, 10);
	Vertex(2, 10);
	Vertex(2, 10);
	Vertex(0, 8.5);
	Vertex(0, 8.5);
	Vertex(0, 6.5);
	Vertex(0, 6.5);
	Vertex(1.5, 5);
	Vertex(1.5, 5);
	Vertex(6.5, 5);
	Vertex(6.5, 5);
	Vertex(8, 3.5);
	Vertex(8, 3.5);
	Vertex(8, 1.5);
	Vertex(8, 1.5);
	Vertex(6, 0);
	Vertex(6, 0);
	Vertex(0, 0);
}

void GL_TECH_FONT::T(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 10);
	Vertex(8, 10);
	Vertex(4,  0);
	Vertex(4, 10);
}

void GL_TECH_FONT::U(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(8, 10);
	Vertex(8, 2);
	Vertex(8, 2);
	Vertex(6, 0);
	Vertex(6, 0);
	Vertex(2, 0);
	Vertex(2, 0);
	Vertex(0, 2);
	Vertex(0, 2);
	Vertex(0, 10);
}

void GL_TECH_FONT::V(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 10);
	Vertex(4,  0);
	Vertex(4,  0);
	Vertex(8, 10);
}

void GL_TECH_FONT::W(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 10);
	Vertex(2,  0);
	Vertex(2,  0);
	Vertex(4, 10);
	Vertex(4, 10);
	Vertex(6,  0);
	Vertex(6,  0);
	Vertex(8, 10);
}

void GL_TECH_FONT::X(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 10);
	Vertex(8,  0);
	Vertex(0,  0);
	Vertex(8, 10);
}

void GL_TECH_FONT::Y(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 10);
	Vertex(4,  5);
	Vertex(4,  5);
	Vertex(8, 10);
	Vertex(4,  5);
	Vertex(4,  0);
}

void GL_TECH_FONT::Z(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 10);
	Vertex(8, 10);
	Vertex(8, 10);
	Vertex(0,  0);
	Vertex(0,  0);
	Vertex(8,  0);
}

void GL_TECH_FONT::Num0(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  1.5);
	Vertex(0,  8.5);
	Vertex(0,  8.5);
	Vertex(2, 10);
	Vertex(2, 10);
	Vertex(4, 10);
	Vertex(4, 10);
	Vertex(6,  8.5);
	Vertex(6,  8.5);
	Vertex(6,  1.5);
	Vertex(6,  1.5);
	Vertex(4,  0);
	Vertex(4,  0);
	Vertex(2,  0);
	Vertex(2,  0);
	Vertex(0,  1.5);
	
	Vertex(0,  1.5);
	Vertex(6,  8.5);
}

void GL_TECH_FONT::Num1(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(2,  8);
	Vertex(4, 10);
	Vertex(4, 10);
	Vertex(4,  0);
}

void GL_TECH_FONT::Num2(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  8.5);
	Vertex(1.5, 10);
	Vertex(1.5, 10);
	Vertex(4.5, 10);
	Vertex(4.5, 10);
	Vertex(6,  8.5);
	Vertex(6,  8.5);
	Vertex(6,  6.5);
	Vertex(6,  6.5);
	Vertex(0,  0);
	Vertex(0,  0);
	Vertex(6,  0);
}

void GL_TECH_FONT::Num3(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  8.5);
	Vertex(1.5, 10);
	Vertex(1.5, 10);
	Vertex(4.5, 10);
	Vertex(4.5, 10);
	Vertex(6,  8.5);
	Vertex(6,  8.5);
	Vertex(6,  6.5);
	Vertex(6,  6.5);
	Vertex(4,  5);
	Vertex(4,  5);
	Vertex(6,  3.5);
	Vertex(6,  3.5);
	Vertex(6,  1.5);
	Vertex(6,  1.5);
	Vertex(4.5,  0);
	Vertex(4.5,  0);
	Vertex(1.5,  0);
	Vertex(1.5,  0);
	Vertex(0,  1.5);
}

void GL_TECH_FONT::Num4(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(4, 10);
	Vertex(0, 4);
	Vertex(0, 4);
	Vertex(5, 4);
	Vertex(4, 5);
	Vertex(4, 0);
}

void GL_TECH_FONT::Num5(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(5.5, 10);
	Vertex(0,  10);
	Vertex(0,  10);
	Vertex(0,  5.5);
	Vertex(0,  5.5);
	Vertex(4,  5.5);
	Vertex(4,  5.5);
	Vertex(6,  3.5);
	Vertex(6,  3.5);
	Vertex(6,  1.5);
	Vertex(6,  1.5);
	Vertex(4.5,  0);
	Vertex(4.5,  0);
	Vertex(1.5,  0);
	Vertex(1.5,  0);
	Vertex(0,  1.5);
}

void GL_TECH_FONT::Num6(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(5.5, 10);
	Vertex(1.5, 10);
	Vertex(1.5, 10);
	Vertex(0,  8.5);
	Vertex(0,  8.5);
	Vertex(0,  1.5);
	Vertex(0,  1.5);
	Vertex(1.5,  0);
	Vertex(1.5,  0);
	Vertex(4.5,  0);
	Vertex(4.5,  0);
	Vertex(6,  1.5);
	Vertex(6,  1.5);
	Vertex(6,  3.5);
	Vertex(6,  3.5);
	Vertex(4, 5.5);
	Vertex(4, 5.5);
	Vertex(0,  5.5);
}

void GL_TECH_FONT::Num7(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  10);
	Vertex(6,  10);
	Vertex(6,  10);
	Vertex(0,  0);
}

void GL_TECH_FONT::Num8(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(1.5,  5);
	Vertex(0,  6.5);
	Vertex(0,  6.5);
	Vertex(0,  8.5);
	Vertex(0,  8.5);
	Vertex(1.5, 10);
	Vertex(1.5, 10);
	Vertex(4.5, 10);
	Vertex(4.5, 10);
	Vertex(6,  8.5);
	Vertex(6,  8.5);
	Vertex(6,  6.5);
	Vertex(6,  6.5);
	Vertex(4.5,  5);
	Vertex(4.5,  5);
	Vertex(6,  3.5);
	Vertex(6,  3.5);
	Vertex(6,  1.5);
	Vertex(6,  1.5);
	Vertex(4.5,  0);
	Vertex(4.5,  0);
	Vertex(1.5,  0);
	Vertex(1.5,  0);
	Vertex(0,  1.5);
	Vertex(0,  1.5);
	Vertex(0,  3.5);
	Vertex(0,  3.5);
	Vertex(1.5,  5);
	Vertex(1.5,  5);
	Vertex(4.5,  5);
}

void GL_TECH_FONT::Num9(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(6,  4.5);
	Vertex(2,  4.5);
	Vertex(2,  4.5);
	Vertex(0,  6.5);
	Vertex(0,  6.5);
	Vertex(0,  8.5);
	Vertex(0,  8.5);
	Vertex(1.5, 10);
	Vertex(1.5, 10);
	Vertex(4.5, 10);
	Vertex(4.5, 10);
	Vertex(6,  8.5);
	Vertex(6,  8.5);
	Vertex(6,  1.5);
	Vertex(6,  1.5);
	Vertex(4.5,  0);
	Vertex(4.5,  0);
	Vertex(0.5,  0);
}

void GL_TECH_FONT::OpenBrace(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(2, 0);
	Vertex(1, 1);
	Vertex(1, 1);
	Vertex(1, 4);
	Vertex(1, 4);
	Vertex(0, 5);
	Vertex(0, 5);
	Vertex(1, 6);
	Vertex(1, 6);
	Vertex(1, 9);
	Vertex(1, 9);
	Vertex(2, 10);
}

void GL_TECH_FONT::OpenSqBracket(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(1, 0);
	Vertex(0, 0);
	Vertex(0, 0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(1, 10);
}

void GL_TECH_FONT::OpenBracket(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(1.5, 0);
	Vertex(0, 3);
	Vertex(0, 3);
	Vertex(0, 7);
	Vertex(0, 7);
	Vertex(1.5, 10);
}

void GL_TECH_FONT::Less(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(6, 8);
	Vertex(0, 5);
	Vertex(0, 5);
	Vertex(6, 2);
}

void GL_TECH_FONT::Tilda(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 5);
	Vertex(1.5, 5.5);
	Vertex(1.5, 5.5);
	Vertex(4.5, 4.5);
	Vertex(4.5, 4.5);
	Vertex(6, 5);
}

void GL_TECH_FONT::ExclamationMark(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0.5, 2);
	Vertex(0.5,  10);
	Vertex(0,  0);
	Vertex(0.5, 0.5);
	Vertex(0.5, 0.5);
	Vertex(1, 0);
	Vertex(1, 0);
	Vertex(0.5, -0.5);
	Vertex(0.5, -0.5);
	Vertex(0,  0);
}

void GL_TECH_FONT::Monkey(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(6.5, 0);
	Vertex(2, 0);
	Vertex(2, 0);
	Vertex(0, 2);
	Vertex(0, 2);
	Vertex(0, 6);
	Vertex(0, 6);
	Vertex(2, 8);
	Vertex(2, 8);
	Vertex(6, 8);
	Vertex(6, 8);
	Vertex(8, 6);
	Vertex(8, 6);
	Vertex(8, 2);
	Vertex(8, 2);
	Vertex(7, 1.5);
	
	Vertex(6, 3);
	Vertex(5, 2);
	Vertex(5, 2);
	Vertex(3, 2);
	Vertex(3, 2);
	Vertex(2, 3);
	Vertex(2, 3);
	Vertex(2, 5);
	Vertex(2, 5);
	Vertex(3, 6);
	Vertex(3, 6);
	Vertex(5, 6);
	Vertex(5, 6);
	Vertex(6, 5);
	Vertex(6, 6);
	Vertex(6, 2);
	Vertex(6, 2);
	Vertex(7, 1.5);
}

void GL_TECH_FONT::Hash(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 4);
	Vertex(6, 4);
	Vertex(0, 6);
	Vertex(6, 6);
	Vertex(1.5, 2);
	Vertex(2.5, 8);
	Vertex(3.5, 2);
	Vertex(4.5, 8);
}

void GL_TECH_FONT::Dolar(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(5.5, 9);
	Vertex(1.5, 9);
	Vertex(1.5, 9);
	Vertex(0.5, 8);
	Vertex(0.5, 8);
	Vertex(0.5, 6);
	Vertex(0.5, 6);
	Vertex(1.5, 5);
	Vertex(1.5, 5);
	Vertex(4.5, 5);
	Vertex(4.5, 5);
	Vertex(5.5, 4);
	Vertex(5.5, 4);
	Vertex(5.5, 2);
	Vertex(5.5, 2);
	Vertex(4.5, 1);
	Vertex(4.5, 1);
	Vertex(0.5, 1);
	
	Vertex(2.5, 0);
	Vertex(2.5, 10);
	Vertex(3.5, 0);
	Vertex(3.5, 10);
}

void GL_TECH_FONT::Percent(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0.5, 10);
	Vertex(1.5, 10);
	Vertex(1.5, 10);
	Vertex(2, 9.5);
	Vertex(2, 9.5);
	Vertex(2, 8.5);
	Vertex(2, 8.5);
	Vertex(1.5, 8);
	Vertex(1.5, 8);
	Vertex(0.5, 8);
	Vertex(0.5, 8);
	Vertex(0, 8.5);
	Vertex(0, 8.5);
	Vertex(0, 9.5);
	Vertex(0, 9.5);
	Vertex(0.5, 10);
	
	Vertex(0, 0);
	Vertex(6, 10);
	
	Vertex(4.5, 2);
	Vertex(5.5, 2);
	Vertex(5.5, 2);
	Vertex(6, 1.5);
	Vertex(6, 1.5);
	Vertex(6, 0.5);
	Vertex(6, 0.5);
	Vertex(5.5, 0);
	Vertex(5.5, 0);
	Vertex(4.5, 0);
	Vertex(4.5, 0);
	Vertex(4, 0.5);
	Vertex(4, 0.5);
	Vertex(4, 1.5);
	Vertex(4, 1.5);
	Vertex(4.5, 2);
}

void GL_TECH_FONT::Bird(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(1, 7);
	Vertex(3, 10);
	Vertex(3, 10);
	Vertex(5, 7);
}

void GL_TECH_FONT::And(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(6,  3);
	Vertex(4,  0);
	Vertex(4,  0);
	Vertex(1.5,  0);
	Vertex(1.5,  0);
	Vertex(0,  1.5);
	Vertex(0,  1.5);
	Vertex(0,  3.5);
	Vertex(0,  3.5);
	Vertex(4.5,  7);
	Vertex(4.5,  7);
	Vertex(4.5,  9);
	Vertex(4.5,  9);
	Vertex(3,  10);
	Vertex(3,  10);
	Vertex(2,  10);
	Vertex(2,  10);
	Vertex(0.5,  9);
	Vertex(0.5,  9);
	Vertex(0.5,  7);
	Vertex(0.5,  7);
	Vertex(6,  1.5);
}

void GL_TECH_FONT::Star(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(1.5, 3.5);
	Vertex(4.5, 6.5);
	Vertex(1.5, 6.5);
	Vertex(4.5, 3.5);
	Vertex(3, 3);
	Vertex(3, 7);
	Vertex(1, 5);
	Vertex(5, 5);
}

void GL_TECH_FONT::Underscore(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(6, 0);
}

void GL_TECH_FONT::Plus(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 5);
	Vertex(6, 5);
	Vertex(3, 2);
	Vertex(3, 8);
}

void GL_TECH_FONT::Minus(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 5);
	Vertex(6, 5);
}

void GL_TECH_FONT::Equal(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 4);
	Vertex(6, 4);
	Vertex(0, 6);
	Vertex(6, 6);
}

void GL_TECH_FONT::Vline(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0.5, 10);
	Vertex(0.5, 0);
}

void GL_TECH_FONT::Slash(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(3, 10);
	Vertex(0, 0);
}

void GL_TECH_FONT::BackSlash(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 10);
	Vertex(3, 0);
}

void GL_TECH_FONT::Colon(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  5);
	Vertex(0.5, 5.5);
	Vertex(0.5, 5.5);
	Vertex(1, 5);
	Vertex(1, 5);
	Vertex(0.5, 4.5);
	Vertex(0.5, 4.5);
	Vertex(0,  5);
	
	Vertex(0,  0);
	Vertex(0.5, 0.5);
	Vertex(0.5, 0.5);
	Vertex(1, 0);
	Vertex(1, 0);
	Vertex(0.5, -0.5);
	Vertex(0.5, -0.5);
	Vertex(0,  0);
}

void GL_TECH_FONT::SemiColon(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  5);
	Vertex(0.5, 5.5);
	Vertex(0.5, 5.5);
	Vertex(1, 5);
	Vertex(1, 5);
	Vertex(0.5, 4.5);
	Vertex(0.5, 4.5);
	Vertex(0,  5);
	
	Vertex(0,  0);
	Vertex(0.5, 0.5);
	Vertex(0.5, 0.5);
	Vertex(1, 0);
	Vertex(1, 0);
	Vertex(0, -1);
	Vertex(0.5, -0.5);
	Vertex(0,  0);
}

void GL_TECH_FONT::Quote(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 8);
	Vertex(0, 10);
	Vertex(1, 8);
	Vertex(1, 10);
}

void GL_TECH_FONT::Apostrophe(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0.5, 8);
	Vertex(0.5, 10);
}

void GL_TECH_FONT::Dot(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  0);
	Vertex(0.5, 0.5);
	Vertex(0.5, 0.5);
	Vertex(1, 0);
	Vertex(1, 0);
	Vertex(0.5, -0.5);
	Vertex(0.5, -0.5);
	Vertex(0,  0);
}

void GL_TECH_FONT::Coma(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  0);
	Vertex(0.5, 0.5);
	Vertex(0.5, 0.5);
	Vertex(1, 0);
	Vertex(1, 0);
	Vertex(0, -1);
	Vertex(0.5, -0.5);
	Vertex(0,  0);
}

void GL_TECH_FONT::QuestionMark(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  8.5);
	Vertex(1.5, 10);
	Vertex(1.5, 10);
	Vertex(4.5, 10);
	Vertex(4.5, 10);
	Vertex(6,  8.5);
	Vertex(6,  8.5);
	Vertex(6,  6.5);
	Vertex(6,  6.5);
	Vertex(3,  4.5);
	Vertex(3,  4.5);
	Vertex(3,  2);
	
	Vertex(2.5,  0);
	Vertex(3, 0.5);
	Vertex(3, 0.5);
	Vertex(3.5, 0);
	Vertex(3.5, 0);
	Vertex(3, -0.5);
	Vertex(3, -0.5);
	Vertex(2.5,  0);
}

void GL_TECH_FONT::More(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 8);
	Vertex(6, 5);
	Vertex(6, 5);
	Vertex(0, 2);
}

void GL_TECH_FONT::CloseBracket(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(1.5, 3);
	Vertex(1.5, 3);
	Vertex(1.5, 7);
	Vertex(1.5, 7);
	Vertex(0, 10);
}

void GL_TECH_FONT::CloseSqBracket(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(1, 0);
	Vertex(1, 0);
	Vertex(1, 10);
	Vertex(1, 10);
	Vertex(0, 10);
}

void GL_TECH_FONT::CloseBrace(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0, 0);
	Vertex(1, 1);
	Vertex(1, 1);
	Vertex(1, 4);
	Vertex(1, 4);
	Vertex(2, 5);
	Vertex(2, 5);
	Vertex(1, 6);
	Vertex(1, 6);
	Vertex(1, 9);
	Vertex(1, 9);
	Vertex(0, 10);
}

void GL_TECH_FONT::NoChar(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos)
{
	LetterOrigin(x_pos, y_pos, z_pos);
	
	Vertex(0,  0);
	Vertex(0, 10);
	Vertex(0, 10);
	Vertex(8, 10);
	Vertex(8, 10);
	Vertex(8,  0);
	Vertex(8,  0);
	Vertex(0,  0);
	
	Vertex(0, 10);
	Vertex(8,  0);
	Vertex(0,  0);
	Vertex(8, 10);
}
