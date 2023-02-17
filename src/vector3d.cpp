/*********************************************************************/ 
/*                                                                   */ 
/*             Config files library - (C) TGG 2019                   */ 
/*                                                                   */ 
/*********************************************************************/ 
/*                          Warszawa, 2019                           */ 
/*********************************************************************/ 
/*                                                                   */
/* File: vector3d.cpp                                                */
/*                                                                   */
/* Author: F.A.Dul, modif. by T.Grabowski                            */
/*                                                                   */
/* Contents - vector 3d class                                        */
/*                                                                   */ 
/*                                                                   */
/*********************************************************************/
/*                                                                   */
/*                                                                   */

#include "vector3d.h"

using namespace std;

//  Methods of VECTOR_3D class

VECTOR_3D &VECTOR_3D::operator= ( const VECTOR_3D &a )
{
    if( this != &a )
        {
        x = a.x;
        y = a.y;
        z = a.z;
    }

    return *this;
}

double VECTOR_3D::Normalize( void )
{
    double dlg = this->Len();

    if( dlg > 0.0 )
        {
        x /= dlg;
        y /= dlg;
        z /= dlg;
        }

    return dlg;
}

//	roatation functions of VECTOR_3D classs

void VECTOR_3D::rotX( double alfa)
{
    double yy=y;
    double zz=z;
    y = yy*cos(alfa) - zz*sin(alfa);
    z = yy*sin(alfa) + zz*cos(alfa);
}

void VECTOR_3D::rotY( double alfa)
{
    double xx=x;
    double zz=z;
    x = zz*sin(alfa) + xx*cos(alfa);
    z = zz*cos(alfa) - xx*sin(alfa);
}

void VECTOR_3D::rotZ( double alfa)
{
    double xx=x;
    double yy=y;
    x = xx*cos(alfa) - yy*sin(alfa);
    y = xx*sin(alfa) + yy*cos(alfa);
}
	
void VECTOR_3D::rotdX( double alfa )
{
    double yy = y;
    double zz = z;

    if (alfa==0.)
	    {
	    }
    else
	    {
	    if (alfa==90.)
	        {
	        y = -zz;
	        z = yy;
	        }
	    else
	        {
	        if (alfa==180.)
	            {
	            y = -yy;
	            z = -zz;
	            }
	        else
	            {
	            if (alfa==270.)
		            {
		            y = zz;
		            z = -yy;
		            }
	            else
		            {
		            alfa *= M_PI/180.0;
		            y = yy*cos(alfa) - zz*sin(alfa);
		            z = yy*sin(alfa) + zz*cos(alfa);
		            }
	            }
	        }
	    }
}
	
void VECTOR_3D::rotdY( double alfa, double dX )
{
    double xx = x;
    double zz = z;
    
	if (alfa==0.)
	    {
	    }
    else
	    {
	    if (alfa==90.)
	        {
	        x =  zz + dX;
	        z = -xx + dX;
	        }
	    else
	        {
	        if (alfa==180.)
	            {
	            x = -xx + 2.*dX;
	            z = -zz;
	            }
	        else
	            {
	            if (alfa==270.)
		            {
		            x = -zz + dX;
		            z =  xx - dX;
		            }
	            else
		            {
		            alfa *= M_PI/180.0;
		            x = zz*sin(alfa) + (xx-dX)*cos(alfa) + dX;
		            z = zz*cos(alfa) - (xx-dX)*sin(alfa);
		            }
	            }
	        }
	    }
}
	
void VECTOR_3D::rotdZ( double alfa )
{
    double xx = x;
    double yy = y;
	
    if (alfa==0.)
	    {
	    }
    else
	    {
	    if (alfa==90.)
	        {
	        x = -yy;
	        y = xx;
	        }
	    else
	        {
	        if (alfa==180.)
	            {
	            x = -xx;
	            y = -yy;
	            }
	        else
	            {
	            if (alfa==270.)
		            {
		            x = yy;
		            y = -xx;
		            }
	            else
		            {
		            alfa *= M_PI/180.0;
		            x = xx*cos(alfa) - yy*sin(alfa);
		            y = xx*sin(alfa) + yy*cos(alfa);
		            }
	            }
	        }
	    }
}

// VECTOR_3D operators

// dot product

double operator *( const VECTOR_3D &A , const VECTOR_3D &B )
{
  return  ( A.x * B.x  +  A.y * B.y  +  A.z * B.z );
}

// cross product

VECTOR_3D operator %( const VECTOR_3D &A , const VECTOR_3D &B )
{
 VECTOR_3D c;

  c.x = A.y * B.z - A.z * B.y;
  c.y = A.z * B.x - A.x * B.z;
  c.z = A.x * B.y - A.y * B.x;

 return c;
}

// scalar mult

VECTOR_3D operator *( const VECTOR_3D &A , const double &s )
{
 VECTOR_3D c;

  c.x = A.x * s;
  c.y = A.y * s;
  c.z = A.z * s;

 return c;
}

VECTOR_3D operator *( const double &s , const VECTOR_3D &A )
{
 VECTOR_3D c;

  c.x = A.x * s;
  c.y = A.y * s;
  c.z = A.z * s;

 return c;
}

VECTOR_3D operator /( const VECTOR_3D &A , const double &s )
{
 VECTOR_3D c;

  c.x = A.x / s;
  c.y = A.y / s;
  c.z = A.z / s;

 return c;
}

// sum

VECTOR_3D operator +( const VECTOR_3D &A , const VECTOR_3D &B )
{
 VECTOR_3D c;

  c.x = A.x + B.x;
  c.y = A.y + B.y;
  c.z = A.z + B.z;

 return c;
}
/*
VECTOR_3D operator +( const VECTOR_3D &A )
{
 VECTOR_3D c;

  c.x = A.x;
  c.y = A.y;
  c.z = A.z;

 return c;
}
*/
VECTOR_3D operator -( const VECTOR_3D &A , const VECTOR_3D &B )
{
 VECTOR_3D c;

  c.x = A.x - B.x;
  c.y = A.y - B.y;
  c.z = A.z - B.z;

 return c;
}

VECTOR_3D operator -( const VECTOR_3D &A )
{
 VECTOR_3D c;

  c.x = -A.x;
  c.y = -A.y;
  c.z = -A.z;

 return c;
}

// Shorthand Ops

void operator %=( VECTOR_3D &A , const VECTOR_3D &B )
{
 VECTOR_3D tmp;

  tmp.x = A.y * B.z - A.z * B.y;
  tmp.y = A.z * B.x - A.x * B.z;
  tmp.z = A.x * B.y - A.y * B.x;

  A.x = tmp.x;
  A.y = tmp.y;
  A.z = tmp.z;
}

void operator +=( VECTOR_3D &A , const VECTOR_3D &B )
{
  A.x += B.x;
  A.y += B.y;
  A.z += B.z;
}

void operator -=( VECTOR_3D &A , const VECTOR_3D &B )
{
  A.x -= B.x;
  A.y -= B.y;
  A.z -= B.z;
}

void operator &=( VECTOR_3D &A , const VECTOR_3D &B )
{
  A.x *= B.x;
  A.y *= B.y;
  A.z *= B.z;
}

void operator *=( VECTOR_3D &A , const double &s )
{
  A.x *= s;
  A.y *= s;
  A.z *= s;
}

void operator /=( VECTOR_3D &A , const double  &s )
{
  A.x /= s;
  A.y /= s;
  A.z /= s;
}

// compare two vectors

bool operator ==( const VECTOR_3D &A , const VECTOR_3D &B )
{
 return ( A.x == B.x && A.y == B.y && A.z == B.z );
}

///////////////////////////////////////////////////////////////////

VECTOR_3D  VECTOR_3__E0( void )
{
  return VECTOR_3D( 0.0 , 0.0 , 0.0 );
}

VECTOR_3D  VECTOR_3__E1( void )
{
  return VECTOR_3D( 1.0 , 1.0 , 1.0 );
}

VECTOR_3D  VECTOR_3__Ex( void )
{
  return VECTOR_3D( 1.0 , 0.0 , 0.0 );
}

VECTOR_3D  VECTOR_3__Ey( void )
{
  return VECTOR_3D( 0.0 , 1.0 , 0.0 );
}

VECTOR_3D  VECTOR_3__Ez( void )
{
  return VECTOR_3D( 0.0 , 0.0 , 1.0 );
}

//////////////////////////////////////////////////////////////////////////////

void  v_printf( char *name , const VECTOR_3D &vec )
{
  printf( "%s=[%19.11f,%19.11f,%19.11f]\n", name , vec.x , vec.y , vec.z );
}

void  v_printf( char *fmt , char *name , const VECTOR_3D &vec )
{
  printf( fmt , name , vec.x , vec.y , vec.z );
}

void  v_sprintf( char *dest , char *name , const VECTOR_3D &vec )
{
  sprintf(dest,"%s=[%19.11f,%19.11f %19.11f]", name , vec.x , vec.y , vec.z );
}

void  v_sprintf( char *dest , char *fmt , char *name , const VECTOR_3D &vec )
{
  sprintf(dest , fmt , name , vec.x , vec.y , vec.z );
}

void  v_fprintf( FILE *dest , char *name , const VECTOR_3D &vec )
{
  fprintf(dest,"%s=[%19.11f,%19.11f %19.11f]\n", name , vec.x , vec.y , vec.z );
}

void  v_fprintf( FILE *dest , char *fmt , char *name , const VECTOR_3D &vec )
{
  fprintf( dest , fmt , name , vec.x , vec.y , vec.z );
}

ostream& operator << ( ostream & out, const VECTOR_3D & vec )
{
  out << "["   << vec.x << " , " << vec.y << " , " << vec.z << "]";
  return out;
}

//**************************************************************************

void vout (FILE *ff,VECTOR_3D vec)
{
    fprintf (ff,"% 12.7f % 12.7f % 12.7f",vec.x,vec.y,vec.z);
}

//**************************************************************************

void voutn (FILE *ff,VECTOR_3D vec)
{
    fprintf (ff,"% 12.7f % 12.7f % 12.7f",vec.x,-vec.y,vec.z);
}

//**************************************************************************

void vout0 (FILE *ff,VECTOR_3D vec)
{
    fprintf (ff,"% 12.7f % 12.7f % 12.7f",vec.x,0.,vec.z);
}


