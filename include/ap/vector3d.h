/*********************************************************************/ 
/*                                                                   */ 
/*             Config files library - (C) TGG 2019                   */ 
/*                                                                   */ 
/*********************************************************************/ 
/*                          Warszawa, 2019                           */ 
/*********************************************************************/ 
/*                                                                   */
/* File: vector3d.h                                                  */
/*                                                                   */
/* Author: F.A.Dul, modif. by T.Grabowski                            */
/*                                                                   */
/* Contents - vector 3d class                                        */
/*                                                                   */ 
/*                                                                   */
/*********************************************************************/
/*                                                                   */
/*                                                                   */

/*! \file vector3d.h
    \brief Vector 3D class and functions
*/

#ifndef _VECTOR_3D_H_
#define _VECTOR_3D_H_

#include <cmath>
#include <cstdio>
#include <iostream>

/// Vector 3D class - vector manipulation

class VECTOR_3D
{
	public:

//  vector coordinates    
    double  x /**x coordinate*/, y /**y coordinate*/, z /**z coordinate*/;
/// deafult constructor
    VECTOR_3D( void )                            { x = 0.0;  y = 0.0;  z = 0.0; };
/// constructor that copies coordiantes from another vector
    VECTOR_3D( const VECTOR_3D &v )              { x = v.x;  y = v.y;  z = v.z; };
/// constructor that copies coordiantes from three variables
    VECTOR_3D( double xp, double yp, double zp ) { x = xp;   y = yp;   z = zp;  };
/// constructor that copies coordiantes from the array
    VECTOR_3D( double a[] )                      { x = a[0]; y = a[1]; z = a[2];};
  
/// assignment operator
    VECTOR_3D & operator = ( const VECTOR_3D &v );

/// the value of the vector 
    double Len( void )    const { return sqrt( x*x + y*y + z*z ); };
/// the value of the 2D vector in XY plane
    double LenXY( void )  const { return sqrt( x*x + y*y ); };  
/// the value of the 2D vector in XZ plane
    double LenXZ( void )  const { return sqrt( x*x + z*z ); };  
/// the value of the 2D vector in YZ plane
    double LenYZ( void )  const { return sqrt( y*y + z*z ); };  
/// the square of the vector value
    double Square( void ) const { return x*x + y*y + z*z; };

/// normalizes the vector to unit - coordiantes are divided by the vector value, returnes the vector value (length)
    double Normalize( void );
/// sets coordinates from three variables    
    void GetFrom( double xp, double yp, double zp ){ x = xp;   y = yp;   z = zp;  };
/// sets coordinates from the aray
    void GetFrom( double a[] )                     { x = a[0]; y = a[1]; z = a[2];};
                    
/// copies coordinates to three variables    
    void PutTo( double &xp, double &yp, double &zp ){ xp = x; yp = y; zp = z; };
/// copies coordinates to the array  
    void PutTo( double a[] )                   { a[0] = x; a[1] = y; a[2] = z;};
    
/// adds coordinates to three variables    
    void AddTo( double &xp, double &yp, double &zp ){ xp += x; yp += y; zp += z; };
/// adds coordinates to the array 
    void AddTo( double a[] )                   { a[0] += x; a[1] += y; a[2] += z;};
    
/// resets coordinates to zero
    void Set0( void ){ x = 0.0;  y = 0.0;  z = 0.0; }; 

/// determines if any coordinate of given vector is a not-a-number (NaN) value.
    bool Isnan( void ){ return std::isnan( x ) || std::isnan( y ) || std::isnan( z ); };
    
///	Rotating functions
/// rotates the vector relative to the X axis by an alpha[rad] angle 
	void rotX( double alpha);
/// rotates the vector relative to the Y axis by an alpha[rad] angle 
	void rotY( double alpha);
/// rotates the vector relative to the Z axis by an alpha[rad] angle 
	void rotZ( double alpha);
/// rotates the vector relative to the X axis by an alpha[deg] angle (precise values for 0,90,180,270 deg)
	void rotdX( double alfa);
/// rotates the vector relative to the Y  axis (shifted by dX longwise X) by an alpha[deg] angle (precise values for 0,90,180,270 deg)
	void rotdY( double alfa, double dX = 0. );
/// rotates the vector relative to the Z axis by an alpha[deg] angle (precise values for 0,90,180,270 deg)
	void rotdZ( double alfa);

};

/// Arithmetic operator - dot (scalar) product of two vectors
double      operator  *( const VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - cross (vector) product of two vectors
VECTOR_3D   operator  %( const VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - product of vector and scalar
VECTOR_3D   operator  *( const VECTOR_3D &A, const double    &s );
/// Arithmetic operator - product of scalar and vector
VECTOR_3D   operator  *( const double    &s, const VECTOR_3D &A );
/// Arithmetic operator - vector divided by scalar (product of vector and reciprocal scalar)
VECTOR_3D   operator  /( const VECTOR_3D &A, const double    &s );
/// Arithmetic operator - sum of two vectors
VECTOR_3D   operator  +( const VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - sum of two vectors
VECTOR_3D   operator  +( const VECTOR_3D &A                     );
/// Arithmetic operator - subtraction of two vectors (sum of A and -B)
VECTOR_3D   operator  -( const VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - reverse of vector (-A)
VECTOR_3D   operator  -( const VECTOR_3D &A                     );
/// Arithmetic operator - coordinates products (AxBx, AyBy, AzBz)
VECTOR_3D   operator  &( const VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - cross product assigment
void        operator %=(       VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - addition assigment
void        operator +=(       VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - subtraction assigment
void        operator -=(       VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - multiplication assigment (coordiante by coordiante)
void        operator &=(       VECTOR_3D &A, const VECTOR_3D &B );
/// Arithmetic operator - multiplication assigment
void        operator *=(       VECTOR_3D &A, const double    &s );
/// Arithmetic operator - division assigment
void        operator /=(       VECTOR_3D &A, const double    &s );
/// Boolean operator - compares two vectors - true if all appropriate coordinates are equal
bool        operator ==( const VECTOR_3D &A, const VECTOR_3D &B );

////////////////////////////////////////////////////////////////////////////

/// print to stdout name and vector components
void  v_printf( char *name , const VECTOR_3D &vec );
/// print to stdout name and vector components according to given format "fmt"
void  v_printf( char *fmt , char *name , const VECTOR_3D &vec );
/// print to string "dest" name and vector components
void  v_sprintf( char *dest , char *name , const VECTOR_3D &vec );
/// print to string "dest" name and vector components according to given format "fmt"
void  v_sprintf( char *dest , char *fmt , char *name , const VECTOR_3D &vec );
/// print to stream "dest" name and vector components
void  v_fprintf( FILE *dest , char *name , const VECTOR_3D &vec );
/// print to sstream "dest" name and vector components according to given format "fmt"
void  v_fprintf( FILE *dest , char *fmt , char *name , const VECTOR_3D &vec );
/// print to std:ostream
std::ostream & operator << ( std::ostream & out, const VECTOR_3D & v );

/// printf vector components (x,y,z) to stream ff
void vout  (FILE *ff, VECTOR_3D vec);
/// printf vector components (x,-y,z) to stream ff
void voutn (FILE *ff, VECTOR_3D vec);
/// printf vector components (x,0,z) to stream ff
void vout0 (FILE *ff, VECTOR_3D vec);

/// returns vector (0,0,0)
VECTOR_3D  VECTOR_3__E0( void );
/// returns vector (1,1,1)
VECTOR_3D  VECTOR_3__E1( void );
/// returns vector (1,0,0)
VECTOR_3D  VECTOR_3__Ex( void );
/// returns vector (0,1,0)
VECTOR_3D  VECTOR_3__Ey( void );
/// returns vector (0,0,1)
VECTOR_3D  VECTOR_3__Ez( void );

#endif /*_VECTOR_3D_H_*/
