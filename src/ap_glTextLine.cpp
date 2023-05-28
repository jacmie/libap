#include "ap_glTextLine.h"

namespace ap {

GL_TEXT_LINE::GL_TEXT_LINE()
{
	sep_ 		= 2.0;
	small_		= 0.6;
}

GL_TEXT_LINE::GL_TEXT_LINE(GLfloat size, GLfloat zoom, MATRIX_3x3 <GLfloat> &rotationMatrix)
{
	sep_ 		= 2.0;
	small_		= 0.6; 
	
    Init(size, zoom, rotationMatrix);
}

void GL_TEXT_LINE::Init(GLfloat size, GLfloat zoom, MATRIX_3x3 <GLfloat> &rotationMatrix)
{
	size_ 		= size;
	zoom_		= zoom;
	rotMatrix_ 	= rotationMatrix;
}

void GL_TEXT_LINE::MoveOrigin(GLfloat letterWidth)
{
	VECTOR_3 <GLfloat> nextLetter((letterWidth + sep_)*0.1*size_, 0, 0); 
 	origin_ += nextLetter;
}

void GL_TEXT_LINE::Write(GLfloat x_pos, GLfloat y_pos, GLfloat z_pos, std::string line)
{
 	VECTOR_3 <GLfloat> oInit; 
 	oInit.Set(x_pos*zoom_, y_pos*zoom_, z_pos*zoom_);
 	origin_ = rotMatrix_ * oInit;

	GL_TECH_FONT Letter(size_, rotMatrix_);
	Letter.moveOriginWithRotation_ = 0;
    
	for(unsigned int i=0; i<line.size(); i++)
	{
		switch(line[i])
		{
			case 'a':
				Letter.scale_ *= small_;
				Letter.A(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'A':
				Letter.A(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'b':
				Letter.scale_ *= small_;
				Letter.B(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'B':
				Letter.B(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'c':
				Letter.scale_ *= small_;
				Letter.C(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'C':
				Letter.C(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'd':
				Letter.scale_ *= small_;
				Letter.D(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'D':
				Letter.D(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'e':
				Letter.scale_ *= small_;
				Letter.E(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'E':
				Letter.E(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'f':
				Letter.scale_ *= small_;
				Letter.F(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'F':
				Letter.F(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'g':
				Letter.scale_ *= small_;
				Letter.G(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'G':
				Letter.G(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'h':
				Letter.scale_ *= small_;
				Letter.H(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'H':
				Letter.H(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'i':
				Letter.scale_ *= small_;
				Letter.I(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'I':
				Letter.I(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'j':
				Letter.scale_ *= small_;
				Letter.J(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'J':
				Letter.J(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'k':
				Letter.scale_ *= small_;
				Letter.K(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'K':
				Letter.K(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'l':
				Letter.scale_ *= small_;
				Letter.L(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'L':
				Letter.L(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'm':
				Letter.scale_ *= small_;
				Letter.M(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'M':
				Letter.M(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'n':
				Letter.scale_ *= small_;
				Letter.N(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'N':
				Letter.N(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'o':
				Letter.scale_ *= small_;
				Letter.O(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'O':
				Letter.O(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'p':
				Letter.scale_ *= small_;
				Letter.P(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'P':
				Letter.P(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'q':
				Letter.scale_ *= small_;
				Letter.Q(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'Q':
				Letter.Q(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'r':
				Letter.scale_ *= small_;
				Letter.R(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'R':
				Letter.R(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 's':
				Letter.scale_ *= small_;
				Letter.S(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'S':
				Letter.S(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 't':
				Letter.scale_ *= small_;
				Letter.T(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'T':
				Letter.T(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'u':
				Letter.scale_ *= small_;
				Letter.U(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'U':
				Letter.U(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'v':
				Letter.scale_ *= small_;
				Letter.V(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'V':
				Letter.V(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'w':
				Letter.scale_ *= small_;
				Letter.W(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'W':
				Letter.W(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'x':
				Letter.scale_ *= small_;
				Letter.X(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'X':
				Letter.X(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'y':
				Letter.scale_ *= small_;
				Letter.Y(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'Y':
				Letter.Y(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case 'z':
				Letter.scale_ *= small_;
				Letter.Z(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8*small_);
				Letter.scale_ /= small_;
				break;

			case 'Z':
				Letter.Z(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case '0':
				Letter.Num0(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '1':
				Letter.Num1(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '2':
				Letter.Num2(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '3':
				Letter.Num3(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '4':
				Letter.Num4(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;
			
			case '5':
				Letter.Num5(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;
			
			case '6':
				Letter.Num6(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '7':
				Letter.Num7(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '8':
				Letter.Num8(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '9':
				Letter.Num9(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '{':
				Letter.OpenBrace(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(2);
				break;

			case '[':
				Letter.OpenSqBracket(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '(':
				Letter.OpenBracket(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1.5);
				break;

			case '<':
				Letter.Less(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '~':
				Letter.Tilda(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '!':
				Letter.ExclamationMark(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '@':
				Letter.Monkey(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;

			case '#':
				Letter.Hash(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '$':
				Letter.Dolar(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '%':
				Letter.Percent(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '^':
				Letter.Bird(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '&':
				Letter.And(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '*':
				Letter.Star(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '_':
				Letter.Underscore(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '+':
				Letter.Plus(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '-':
				Letter.Minus(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '=':
				Letter.Equal(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '|':
				Letter.Vline(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '/':
				Letter.Slash(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(3);
				break;

			case '\\':
				Letter.BackSlash(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(3);
				break;

			case ':':
				Letter.Colon(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case ';':
				Letter.SemiColon(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '\"':
				Letter.Quote(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '\'':
				Letter.Apostrophe(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '`':
				Letter.Apostrophe(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '.':
				Letter.Dot(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case ',':
				Letter.Coma(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '?':
				Letter.QuestionMark(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case '>':
				Letter.More(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(6);
				break;

			case ')':
				Letter.CloseBracket(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1.5);
				break;

			case ']':
				Letter.CloseSqBracket(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(1);
				break;

			case '}':
				Letter.CloseBrace(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(2);
				break;

			case ' ':
 				MoveOrigin(8);
				break;

			case '\t':
 				MoveOrigin(20);
				break;

			default:
				Letter.NoChar(origin_.x, origin_.y, origin_.z);
 				MoveOrigin(8);
				break;
		}
	}
}

} // namespace ap
