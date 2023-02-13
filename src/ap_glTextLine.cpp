#include "glTextLine.h"

using namespace std;

GL_TEXT_LINE::GL_TEXT_LINE()
{
	Sep 		= 2.0;
	Small		= 0.6;
}

GL_TEXT_LINE::GL_TEXT_LINE(GLfloat Size_0, GLfloat Zoom_0, MATRIX_3x3 &RotationMatrix)
{
	Sep 		= 2.0;
	Small		= 0.6; 
	
    Init(Size_0, Zoom_0, RotationMatrix);
	/*Size 		= Size_0;
	Zoom 		= Zoom_0;
	RotMatrix 	= RotationMatrix;*/
}

void GL_TEXT_LINE::Init(GLfloat Size_0, GLfloat Zoom_0, MATRIX_3x3 &RotationMatrix)
{
	Size 		= Size_0;
	Zoom 		= Zoom_0;
	RotMatrix 	= RotationMatrix;
}

void GL_TEXT_LINE::MoveOrigin(GLfloat LetterWidth)
{
	VECTOR_3D NextLetter((LetterWidth + Sep)*0.1*Size, 0, 0); 
 	Origin += NextLetter;
}

void GL_TEXT_LINE::Write(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, string Line)
{
 	VECTOR_3D Oinit; 
 	Oinit.GetFrom(x_pos*Zoom, y_pos*Zoom, z_pos*Zoom);
 	Origin = RotMatrix * Oinit;

	GL_TECH_FONT Letter(Size, RotMatrix);
	Letter.MoveOriginWithRotation = 0;
    
	for(unsigned int i=0; i<Line.size(); i++)
	{
		switch(Line[i])
		{
			case 'a':
				Letter.Scale *= Small;
				Letter.A(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'A':
				Letter.A(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'b':
				Letter.Scale *= Small;
				Letter.B(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'B':
				Letter.B(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'c':
				Letter.Scale *= Small;
				Letter.C(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'C':
				Letter.C(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'd':
				Letter.Scale *= Small;
				Letter.D(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'D':
				Letter.D(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'e':
				Letter.Scale *= Small;
				Letter.E(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'E':
				Letter.E(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'f':
				Letter.Scale *= Small;
				Letter.F(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'F':
				Letter.F(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'g':
				Letter.Scale *= Small;
				Letter.G(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'G':
				Letter.G(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'h':
				Letter.Scale *= Small;
				Letter.H(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'H':
				Letter.H(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'i':
				Letter.Scale *= Small;
				Letter.I(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'I':
				Letter.I(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'j':
				Letter.Scale *= Small;
				Letter.J(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'J':
				Letter.J(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'k':
				Letter.Scale *= Small;
				Letter.K(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'K':
				Letter.K(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'l':
				Letter.Scale *= Small;
				Letter.L(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'L':
				Letter.L(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'm':
				Letter.Scale *= Small;
				Letter.M(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'M':
				Letter.M(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'n':
				Letter.Scale *= Small;
				Letter.N(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'N':
				Letter.N(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'o':
				Letter.Scale *= Small;
				Letter.O(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'O':
				Letter.O(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'p':
				Letter.Scale *= Small;
				Letter.P(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'P':
				Letter.P(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'q':
				Letter.Scale *= Small;
				Letter.Q(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'Q':
				Letter.Q(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'r':
				Letter.Scale *= Small;
				Letter.R(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'R':
				Letter.R(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 's':
				Letter.Scale *= Small;
				Letter.S(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'S':
				Letter.S(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 't':
				Letter.Scale *= Small;
				Letter.T(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'T':
				Letter.T(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'u':
				Letter.Scale *= Small;
				Letter.U(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'U':
				Letter.U(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'v':
				Letter.Scale *= Small;
				Letter.V(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'V':
				Letter.V(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'w':
				Letter.Scale *= Small;
				Letter.W(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'W':
				Letter.W(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'x':
				Letter.Scale *= Small;
				Letter.X(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'X':
				Letter.X(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'y':
				Letter.Scale *= Small;
				Letter.Y(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'Y':
				Letter.Y(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case 'z':
				Letter.Scale *= Small;
				Letter.Z(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8*Small);
				Letter.Scale /= Small;
				break;

			case 'Z':
				Letter.Z(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case '0':
				Letter.Num0(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '1':
				Letter.Num1(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '2':
				Letter.Num2(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '3':
				Letter.Num3(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '4':
				Letter.Num4(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;
			
			case '5':
				Letter.Num5(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;
			
			case '6':
				Letter.Num6(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '7':
				Letter.Num7(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '8':
				Letter.Num8(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '9':
				Letter.Num9(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '{':
				Letter.OpenBrace(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(2);
				break;

			case '[':
				Letter.OpenSqBracket(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '(':
				Letter.OpenBracket(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1.5);
				break;

			case '<':
				Letter.Less(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '~':
				Letter.Tilda(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '!':
				Letter.ExclamationMark(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '@':
				Letter.Monkey(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;

			case '#':
				Letter.Hash(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '$':
				Letter.Dolar(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '%':
				Letter.Percent(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '^':
				Letter.Bird(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '&':
				Letter.And(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '*':
				Letter.Star(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '_':
				Letter.Underscore(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '+':
				Letter.Plus(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '-':
				Letter.Minus(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '=':
				Letter.Equal(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '|':
				Letter.Vline(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '/':
				Letter.Slash(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(3);
				break;

			case '\\':
				Letter.BackSlash(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(3);
				break;

			case ':':
				Letter.Colon(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case ';':
				Letter.SemiColon(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '\"':
				Letter.Quote(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '\'':
				Letter.Apostrophe(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '`':
				Letter.Apostrophe(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '.':
				Letter.Dot(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case ',':
				Letter.Coma(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '?':
				Letter.QuestionMark(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case '>':
				Letter.More(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(6);
				break;

			case ')':
				Letter.CloseBracket(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1.5);
				break;

			case ']':
				Letter.CloseSqBracket(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(1);
				break;

			case '}':
				Letter.CloseBrace(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(2);
				break;

			case ' ':
 				MoveOrigin(8);
				break;

			case '\t':
 				MoveOrigin(20);
				break;

			default:
				Letter.NoChar(Origin.x, Origin.y, Origin.z);
 				MoveOrigin(8);
				break;
		}
	}
}
