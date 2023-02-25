/*********************************************************************/ 
/*                                                                   */ 
/*             Config files library - (C) TGG 2019                   */ 
/*                                                                   */ 
/*********************************************************************/ 
/*                          Warszawa, 2019                           */ 
/*********************************************************************/ 
/*                                                                   */
/* File: matr3d.h                                                    */
/*                                                                   */
/* Author: F.A.Dul, modif. by T.Grabowski                            */
/*                                                                   */
/* Contents - matrix 3x3 class                                       */
/*                                                                   */ 
/*                                                                   */
/*********************************************************************/
/*                                                                   */
/*                                                                   */

#ifndef AP_MATRIX_H
#define AP_MATRIX_H

#include "ap_vector.h"

namespace ap
{
///
/// \brief MATRIX_3x3 class and functions
///
/// Matrix elements:
/// <pre>
///    |  xx,   xy,   xz  |
///    |  yx,   yy,   yz  |
///    |  zx,   zy,   zz  |
/// </pre>
///

class  MATRIX_3x3
{
    public:
//  row-column indices, e.g.,  xz -->  0,2
    double xx;  ///< (0,0) element
    double xy;  ///< (0,1) element
    double xz;  ///< (0,2) element
    double yx;  ///< (1,0) element
    double yy;  ///< (1,1) element
    double yz;  ///< (1,2) element
    double zx;  ///< (2,0) element
    double zy;  ///< (2,1) element
    double zz;  ///< (2,2) element

/// default constructor - sets components to zero
    MATRIX_3x3( void ){ SetToZero(); };
/// constructor - sets components values from variables
    MATRIX_3x3( double xx_p , double xy_p , double xz_p ,
                double yx_p , double yy_p , double yz_p ,
                double zx_p , double zy_p , double zz_p ) :
                       xx(xx_p) , xy(xy_p) , xz(xz_p) ,
                       yx(yx_p) , yy(yy_p) , yz(yz_p) ,
                       zx(zx_p) , zy(zy_p) , zz(zz_p)
        {};
/// constructor - sets components values from the array (one dimensional)
    MATRIX_3x3( double M[] ) :
        xx(M[0]) , xy(M[3]) , xz(M[6]) ,
        yx(M[1]) , yy(M[4]) , yz(M[7]) ,
        zx(M[2]) , zy(M[5]) , zz(M[8])
        {};
/// constructor - sets components values from the array (two dimensional)
    MATRIX_3x3( double M[3][3] ) :
        xx(M[0][0]) , xy(M[0][1]) , xz(M[0][2]) ,
        yx(M[1][0]) , yy(M[1][1]) , yz(M[1][2]) ,
        zx(M[2][0]) , zy(M[2][1]) , zz(M[2][2])
        {};
/// copies components values from variables
    void GetFrom ( double xx_p , double xy_p , double xz_p ,
                  double yx_p , double yy_p , double yz_p ,
                  double zx_p , double zy_p , double zz_p )
        {
        xx = xx_p;   xy = xy_p;    xz = xz_p;
        yx = yx_p;   yy = yy_p;    yz = yz_p;
        zx = zx_p;   zy = zy_p;    zz = zz_p;
        };
/// copies components values from the array (one dimensional)
    void  GetFrom( double A[] )
        {
        xx = A[0];   xy = A[1];    xz = A[2];
        yx = A[3];   yy = A[4];    yz = A[5];
        zx = A[6];   zy = A[7];    zz = A[8];
        };
/// copies components values from the array (two dimensional)
    void  GetFrom( double A[3][3] )
        {
        xx = A[0][0];   xy = A[0][1];   xz = A[0][2];
        yx = A[1][0];   yy = A[1][1];   yz = A[1][2];
        zx = A[2][0];   zy = A[2][1];   zz = A[2][2];
        };
/// reset matrix - set all components to zero  
    void  SetToZero( void )
        {
        xx = 0.0;  xy = 0.0;  xz = 0.0;
        yx = 0.0;  yy = 0.0;  yz = 0.0;
        zx = 0.0;  zy = 0.0;  zz = 0.0;
        };
/// set unit matrix  
    void  Unit( void )
        {
        xx = 1.0;  xy = 0.0;  xz = 0.0;
        yx = 0.0;  yy = 1.0;  yz = 0.0;
        zx = 0.0;  zy = 0.0;  zz = 1.0;
        };
/// matrix determinant	
    double Det( void )
        {
        return xz*yy*zx + xx*yz*zy + xy*yx*zz;
        };
};

/////////////////////////////////////////////////////////////////////////////

/// Arithmetic operator - multiplication of 2 matrices
MATRIX_3x3  operator  *( const MATRIX_3x3 &A , const MATRIX_3x3 &B );
/// Arithmetic operator - multiplication of 2 matrices components ( AxxBxx, AxyBxy, ..., AzzBzz )
MATRIX_3x3  operator  &( const MATRIX_3x3 &A , const MATRIX_3x3 &B );
/// Arithmetic operator - matrix transposition ( A^T )
MATRIX_3x3  operator  !( const MATRIX_3x3 &A                       );
/// Arithmetic operator - matrix inversion ( A^(-1) )
MATRIX_3x3  operator  ~( const MATRIX_3x3 &A                       );
/// Arithmetic operator - product of matrix and scalar
MATRIX_3x3  operator  *( const MATRIX_3x3 &A , const double     &s );
/// Arithmetic operator - product of scalar and matrix
MATRIX_3x3  operator  *( const double     &s , const MATRIX_3x3 &A );
/// Arithmetic operator - division of matrix by scalar (product of matrix and 1/s)
MATRIX_3x3  operator  /( const MATRIX_3x3 &A , const double     &s );
/// Arithmetic operator - sum of 2 matrices
MATRIX_3x3  operator  +( const MATRIX_3x3 &A , const MATRIX_3x3 &B );
/// Arithmetic operator - subtraction of 2 matrices (sum of A and -B)
MATRIX_3x3  operator  -( const MATRIX_3x3 &A , const MATRIX_3x3 &B );
/// Arithmetic operator - reverse of matrix (-A)
MATRIX_3x3  operator  -( const MATRIX_3x3 &A                       );
/// Arithmetic operator - division assignment
void        operator /=(       MATRIX_3x3 &A , const double     &s );

/// Arithmetic operator - multiplication of matrix and vector
VECTOR   operator  *( const MATRIX_3x3 &A , const VECTOR  &b );
/// Arithmetic operator - multiplication of vector and matrix
VECTOR   operator  *( const VECTOR  &b , const MATRIX_3x3 &A );
/// Arithmetic operator - multiplication of vector and inverted matrix
VECTOR   operator  /( const VECTOR  &b ,       MATRIX_3x3 &A );

////////////////////////////////////////////////////////////////////////////

/// print to stdout name and matrix components
void  v_printf( char *name , const MATRIX_3x3 &mat );
/// print to stdout name and matrix components according to given format "fmt"
void  v_printf( char *fmt , char *name , const MATRIX_3x3 &mat );
/// print to string "dest" name and matrix components
void  v_sprintf( char *dest , char *name , const MATRIX_3x3 &mat );
/// print to string "dest" name and matrix components according to given format "fmt"
void  v_sprintf( char *dest , char *fmt , char *name , const MATRIX_3x3 &mat );
/// print to stream "dest" name and matrix components
void  v_fprintf( FILE *dest , char *name , const MATRIX_3x3 &mat );
/// print to sstream "dest" name and matrix components according to given format "fmt"
void  v_fprintf( FILE *dest , char *fmt , char *name , const MATRIX_3x3 &mat );
/// print to std:ostream
std::ostream & operator << ( std::ostream & out, const MATRIX_3x3 &mat );
}

/*
MATRIX_3x3 GL_DISP::RotAbout_X(float RotX)
{
	float SX = sin(RotX*M_PI/180);
	float CX = cos(RotX*M_PI/180);

	MATRIX_3x3 MX( 1,  0,   0,
                   0,  CX, -SX,
                   0,  SX,  CX );

	return MX;
}

MATRIX_3x3 GL_DISP::RotAbout_Y(float RotY)
{
	float SY = sin(RotY*M_PI/180);
	float CY = cos(RotY*M_PI/180);

    MATRIX_3x3 MY( CY,  0,  SY,
                    0,  1,  0,
                  -SY,  0,  CY );
    
	return MY;
}

MATRIX_3x3 GL_DISP::RotAbout_Z(float RotZ)
{
	float SZ = sin(RotZ*M_PI/180);
	float CZ = cos(RotZ*M_PI/180);

	MATRIX_3x3 MZ( CZ, -SZ, 0,
                   SZ,  CZ, 0,
                    0,  0,  1 );
	return MZ;
}*/


#endif /*AP_MATRIX_H*/
