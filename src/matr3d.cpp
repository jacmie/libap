/*********************************************************************/ 
/*                                                                   */ 
/*             Config files library - (C) TGG 2019                   */ 
/*                                                                   */ 
/*********************************************************************/ 
/*                          Warszawa, 2019                           */ 
/*********************************************************************/ 
/*                                                                   */
/* File: matr3d.cpp                                                  */
/*                                                                   */
/* Author: F.A.Dul, modif. by T.Grabowski                            */
/*                                                                   */
/* Contents - matrix 3x3 class                                       */
/*                                                                   */ 
/*                                                                   */
/*********************************************************************/
/*                                                                   */
/*                                                                   */

#include "matr3d.h"

using namespace std;

//  Matrix 3x3 and Vector 3D operators 


VECTOR_3D operator *( const MATRIX_3x3 &A , const VECTOR_3D &b )
{
 VECTOR_3D  w;

  w.x = A.xx * b.x  +  A.xy * b.y  +  A.xz * b.z;
  w.y = A.yx * b.x  +  A.yy * b.y  +  A.yz * b.z;
  w.z = A.zx * b.x  +  A.zy * b.y  +  A.zz * b.z;

 return  w;
}


VECTOR_3D operator *( const VECTOR_3D &b , const MATRIX_3x3 &A )
{
 VECTOR_3D  w;

  w.x = b.x * A.xx  +  b.y * A.yx  +  b.z * A.zx;
  w.y = b.x * A.xy  +  b.y * A.yy  +  b.z * A.zy;
  w.z = b.x * A.xz  +  b.y * A.yz  +  b.z * A.zz;

 return  w;
}


MATRIX_3x3 operator &( const MATRIX_3x3 &A , const MATRIX_3x3 &B )
{
 MATRIX_3x3 C;

  C.xx = A.xx * B.xx;     C.xy = A.xy * B.xy;      C.xz = A.xz * B.xz;
  C.yx = A.yx * B.yx;     C.yy = A.yy * B.yy;      C.yz = A.yz * B.yz;
  C.zx = A.zx * B.zx;     C.zy = A.zy * B.zy;      C.zz = A.zz * B.zz;

 return C;
}


MATRIX_3x3 operator +( const MATRIX_3x3 &A , const MATRIX_3x3 &B )
{
 MATRIX_3x3 C;

  C.xx = A.xx + B.xx;     C.xy = A.xy + B.xy;      C.xz = A.xz + B.xz;
  C.yx = A.yx + B.yx;     C.yy = A.yy + B.yy;      C.yz = A.yz + B.yz;
  C.zx = A.zx + B.zx;     C.zy = A.zy + B.zy;      C.zz = A.zz + B.zz;

 return C;
}


MATRIX_3x3 operator -( const MATRIX_3x3 &A , const MATRIX_3x3 &B )
{
 MATRIX_3x3 C;

  C.xx = A.xx - B.xx;     C.xy = A.xy - B.xy;      C.xz = A.xz - B.xz;
  C.yx = A.yx - B.yx;     C.yy = A.yy - B.yy;      C.yz = A.yz - B.yz;
  C.zx = A.zx - B.zx;     C.zy = A.zy - B.zy;      C.zz = A.zz - B.zz;

 return C;
}


MATRIX_3x3 operator -( const MATRIX_3x3 &A )
{
 MATRIX_3x3 C;

  C.xx = -A.xx;     C.xy = -A.xy;      C.xz = -A.xz;
  C.yx = -A.yx;     C.yy = -A.yy;      C.yz = -A.yz;
  C.zx = -A.zx;     C.zy = -A.zy;      C.zz = -A.zz;

 return C;
}



MATRIX_3x3 operator *( const MATRIX_3x3 &A , const double &s )
{
 MATRIX_3x3 C;

  C.xx = A.xx * s;     C.xy = A.xy * s;      C.xz = A.xz * s;
  C.yx = A.yx * s;     C.yy = A.yy * s;      C.yz = A.yz * s;
  C.zx = A.zx * s;     C.zy = A.zy * s;      C.zz = A.zz * s;

 return C;
}


MATRIX_3x3 operator *( const double &s , const MATRIX_3x3 &A )
{
 MATRIX_3x3 C;

  C.xx = A.xx * s;     C.xy = A.xy * s;      C.xz = A.xz * s;
  C.yx = A.yx * s;     C.yy = A.yy * s;      C.yz = A.yz * s;
  C.zx = A.zx * s;     C.zy = A.zy * s;      C.zz = A.zz * s;

 return C;
}


MATRIX_3x3 operator /( const MATRIX_3x3 &A , const double &s )
{
 MATRIX_3x3 C;

  C.xx = A.xx / s;     C.xy = A.xy / s;      C.xz = A.xz / s;
  C.yx = A.yx / s;     C.yy = A.yy / s;      C.yz = A.yz / s;
  C.zx = A.zx / s;     C.zy = A.zy / s;      C.zz = A.zz / s;

 return C;
}

void operator /=( MATRIX_3x3 &A , const double &s )
{
  A.xx /= s;     A.xy /= s;      A.xz /= s;
  A.yx /= s;     A.yy /= s;      A.yz /= s;
  A.zx /= s;     A.zy /= s;      A.zz /= s;
}

MATRIX_3x3 operator !( const MATRIX_3x3 &A )    // A^T
{
  return  MATRIX_3x3  (
                          A.xx , A.yx , A.zx ,
                          A.xy , A.yy , A.zy ,
                          A.xz , A.yz , A.zz
                       );
}


MATRIX_3x3 operator *( const MATRIX_3x3 &A , const MATRIX_3x3 &B )
{
  MATRIX_3x3 C;

  C.xx = A.xx * B.xx  +  A.xy * B.yx  + A.xz * B.zx;
  C.yx = A.yx * B.xx  +  A.yy * B.yx  + A.yz * B.zx;
  C.zx = A.zx * B.xx  +  A.zy * B.yx  + A.zz * B.zx;

  C.xy = A.xx * B.xy  +  A.xy * B.yy  + A.xz * B.zy;
  C.yy = A.yx * B.xy  +  A.yy * B.yy  + A.yz * B.zy;
  C.zy = A.zx * B.xy  +  A.zy * B.yy  + A.zz * B.zy;

  C.xz = A.xx * B.xz  +  A.xy * B.yz  + A.xz * B.zz;
  C.yz = A.yx * B.xz  +  A.yy * B.yz  + A.yz * B.zz;
  C.zz = A.zx * B.xz  +  A.zy * B.yz  + A.zz * B.zz;

 return  C;
}

MATRIX_3x3 operator ~( const MATRIX_3x3 &A )    // A^(-1)
{
//	C = A^(-1)

  MATRIX_3x3 C = A;
  double w = C.Det();
  C.SetToZero();
  
  C.xx = A.yy * A.zz  -  A.zy * A.yz;
  C.xy = A.xz * A.zy  -  A.xy * A.zz;
  C.xz = A.xy * A.yz  -  A.xz * A.yy;

  C.yx = A.yz * A.zx  -  A.yx * A.zz;
  C.yy = A.xx * A.zz  -  A.xz * A.zx;
  C.yz = A.xz * A.yx  -  A.xx * A.yz;

  C.zx = A.yx * A.zy  -  A.yy * A.zx;
  C.zy = A.xy * A.zx  -  A.xx * A.zy;
  C.zz = A.xx * A.yy  -  A.xy * A.yx;
  
  if( w != 0.0 ) C /= w;
  
  return C;
}

VECTOR_3D operator / ( const VECTOR_3D &b , MATRIX_3x3 &B )
{
	return b * ~B;
}

//////////////////////////////////////////////////////////////////////////////

void  v_printf( char *name , const MATRIX_3x3 &mat )
{
  printf( "%s=[%19.11f,%19.11f,%19.11f]\n[%19.11f,%19.11f,%19.11f]\n[%19.11f,%19.11f,%19.11f]\n",
  name , mat.xx , mat.xy , mat.xz, mat.yx , mat.yy , mat.yz, mat.zx , mat.zy , mat.zz );
}

void  v_printf( char *fmt , char *name , const MATRIX_3x3 &mat )
{
  printf( fmt , name , mat.xx , mat.xy , mat.xz, mat.yx , mat.yy , mat.yz, mat.zx , mat.zy , mat.zz );
}

void  v_sprintf( char *dest , char *name , const MATRIX_3x3 &mat )
{
  sprintf(dest,"%s=[%19.11f,%19.11f %19.11f][%19.11f,%19.11f,%19.11f][%19.11f,%19.11f,%19.11f]", 
  name , mat.xx , mat.xy , mat.xz, mat.yx , mat.yy , mat.yz, mat.zx , mat.zy , mat.zz );
}

void  v_sprintf( char *dest , char *fmt , char *name , const MATRIX_3x3 &mat )
{
  sprintf(dest , fmt , name , mat.xx , mat.xy , mat.xz, mat.yx , mat.yy , mat.yz, mat.zx , mat.zy , mat.zz );
}

void  v_fprintf( FILE *dest , char *name , const MATRIX_3x3 &mat )
{
  fprintf(dest,"%s=[%19.11f,%19.11f %19.11f]\n[%19.11f,%19.11f,%19.11f]\n[%19.11f,%19.11f,%19.11f]\n", 
  name , mat.xx , mat.xy , mat.xz, mat.yx , mat.yy , mat.yz, mat.zx , mat.zy , mat.zz );
}

void  v_fprintf( FILE *dest , char *fmt , char *name , const MATRIX_3x3 &mat )
{
  fprintf( dest , fmt , name , mat.xx , mat.xy , mat.xz, mat.yx , mat.yy , mat.yz, mat.zx , mat.zy , mat.zz );
}

ostream & operator << ( ostream & out, const MATRIX_3x3 & mat )
{
  out << "["   << mat.xx << " , " << mat.xy << " , " << mat.xz << "]"
      << "["   << mat.yx << " , " << mat.yy << " , " << mat.yz << "]"
      << "["   << mat.zx << " , " << mat.zy << " , " << mat.zz << "]";
  return out;
}


