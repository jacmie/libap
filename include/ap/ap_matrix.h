// Part of All Purpose - ap library

#ifndef AP_MATRIX_H
#define AP_MATRIX_H

#include "ap_vector.h"

namespace ap
{
//! \brief MATRIX_3x3 class and functions
///
/// Matrix elements:
/// <pre>
///    |  xx,   xy,   xz  |
///    |  yx,   yy,   yz  |
///    |  zx,   zy,   zz  |
/// </pre>
///
    template <typename real>
	class  MATRIX_3x3
	{
    public:
	    real xx = 0;  ///< (0,0) element
   	 	real xy = 0;  ///< (0,1) element
    	real xz = 0;  ///< (0,2) element
    	real yx = 0;  ///< (1,0) element
    	real yy = 0;  ///< (1,1) element
   	 	real yz = 0;  ///< (1,2) element
    	real zx = 0;  ///< (2,0) element
    	real zy = 0;  ///< (2,1) element
    	real zz = 0;  ///< (2,2) element

		//! Default constructor - sets components to zero
    	MATRIX_3x3() = default;

		//! constructor - sets components values from variables
    	MATRIX_3x3( real xx_p , real xy_p , real xz_p ,
                	real yx_p , real yy_p , real yz_p ,
                	real zx_p , real zy_p , real zz_p ) :
                       xx(xx_p) , xy(xy_p) , xz(xz_p) ,
                       yx(yx_p) , yy(yy_p) , yz(yz_p) ,
                       zx(zx_p) , zy(zy_p) , zz(zz_p)
        {};
		
		//! copies components values from the array (one dimensional)
    	MATRIX_3x3( std::vector <real> &A ) { Set(A); }

		//! copies components values from the array (two dimensional)
    	MATRIX_3x3( std::vector < std::vector <real> > &A ) { Set(A); }

		//! constructor - sets components values from the array (one dimensional)
    	MATRIX_3x3( real M[] ) { Set(M); }

		//! constructor - sets components values from the array (two dimensional)
    	MATRIX_3x3( real M[3][3] ) { Set(M); }

		//! copies components values from variables
    	void Set( real xx_p , real xy_p , real xz_p ,
                  real yx_p , real yy_p , real yz_p ,
                  real zx_p , real zy_p , real zz_p )
        {
        	xx = xx_p;   xy = xy_p;    xz = xz_p;
        	yx = yx_p;   yy = yy_p;    yz = yz_p;
        	zx = zx_p;   zy = zy_p;    zz = zz_p;
        };

		//! copies components values from the array (one dimensional)
    	void Set( std::vector <real> &A )
        {
        	xx = A[0];   xy = A[1];    xz = A[2];
        	yx = A[3];   yy = A[4];    yz = A[5];
        	zx = A[6];   zy = A[7];    zz = A[8];
        };

		//! copies components values from the array (two dimensional)
    	void Set( std::vector < std::vector <real> > &A )
        {
        	xx = A[0][0];   xy = A[0][1];   xz = A[0][2];
        	yx = A[1][0];   yy = A[1][1];   yz = A[1][2];
        	zx = A[2][0];   zy = A[2][1];   zz = A[2][2];
        };

		//! copies components values from the array (one dimensional)
    	void Set( real A[] )
        {
        	xx = A[0];   xy = A[1];    xz = A[2];
        	yx = A[3];   yy = A[4];    yz = A[5];
        	zx = A[6];   zy = A[7];    zz = A[8];
        };

		//! copies components values from the array (two dimensional)
    	void Set( real A[3][3] )
        {
        	xx = A[0][0];   xy = A[0][1];   xz = A[0][2];
        	yx = A[1][0];   yy = A[1][1];   yz = A[1][2];
        	zx = A[2][0];   zy = A[2][1];   zz = A[2][2];
        };

		//! reset matrix - set all components to zero  
    	void Zero()
        {
        	xx = 0.0;  xy = 0.0;  xz = 0.0;
        	yx = 0.0;  yy = 0.0;  yz = 0.0;
        	zx = 0.0;  zy = 0.0;  zz = 0.0;
        };

		//! Set unit matrix  
    	void Unit()
        {
        	xx = 1.0;  xy = 0.0;  xz = 0.0;
        	yx = 0.0;  yy = 1.0;  yz = 0.0;
        	zx = 0.0;  zy = 0.0;  zz = 1.0;
        };

		//! Matrix determinant	
    	real Det( void )
        {
        	return xz*yy*zx + xx*yz*zy + xy*yx*zz;
        };
/*
		MATRIX RotMat_X(float RotX)
		{
			float SX = sin(RotX*M_PI/180);
			float CX = cos(RotX*M_PI/180);

			MATRIX_3x3 MX( 1,  0,   0,
            		       0,  CX, -SX,
                   		   0,  SX,  CX );

			return MX;
		}

		MATRIX RotMat_Y(float RotY)
		{
			float SY = sin(RotY*M_PI/180);
			float CY = cos(RotY*M_PI/180);

    		MATRIX_3x3 MY( CY,  0,  SY,
                    		0,  1,  0,
                  		  -SY,  0,  CY );
    
			return MY;
		}

		MATRIX RotMat_Z(float RotZ)
		{
			float SZ = sin(RotZ*M_PI/180);
			float CZ = cos(RotZ*M_PI/180);

			MATRIX_3x3 MZ( CZ, -SZ, 0,
            		       SZ,  CZ, 0,
                    		0,  0,  1 );
			return MZ;
		}*/
	};

	/////////////////////////////////////////////////////////////////////////////
/*
	//! Arithmetic operator - multiplication of 2 matrices
    template <typename real>
	MATRIX_3x3  operator  *( const MATRIX_3x3 &A , const MATRIX_3x3 &B );
	
	//! Arithmetic operator - multiplication of 2 matrices components ( AxxBxx, AxyBxy, ..., AzzBzz )
    template <typename real>
	MATRIX_3x3  operator  &( const MATRIX_3x3 &A , const MATRIX_3x3 &B );
	
	//! Arithmetic operator - matrix transposition ( A^T )
    template <typename real>
	MATRIX_3x3  operator  !( const MATRIX_3x3 &A                       );
	
	//! Arithmetic operator - matrix inversion ( A^(-1) )
    template <typename real>
	MATRIX_3x3  operator  ~( const MATRIX_3x3 &A                       );
	
	//! Arithmetic operator - product of matrix and scalar
    template <typename real>
	MATRIX_3x3  operator  *( const MATRIX_3x3 &A , const real     &s );
	
	//! Arithmetic operator - product of scalar and matrix
    template <typename real>
	MATRIX_3x3  operator  *( const real     &s , const MATRIX_3x3 &A );
	
	//! Arithmetic operator - division of matrix by scalar (product of matrix and 1/s)
    template <typename real>
	MATRIX_3x3  operator  /( const MATRIX_3x3 &A , const real     &s );
	
	//! Arithmetic operator - sum of 2 matrices
    template <typename real>
	MATRIX_3x3  operator  +( const MATRIX_3x3 &A , const MATRIX_3x3 &B );
	
	//! Arithmetic operator - subtraction of 2 matrices (sum of A and -B)
    template <typename real>
	MATRIX_3x3  operator  -( const MATRIX_3x3 &A , const MATRIX_3x3 &B );
	
	//! Arithmetic operator - reverse of matrix (-A)
    template <typename real>
	MATRIX_3x3  operator  -( const MATRIX_3x3 &A                       );
	
	//! Arithmetic operator - division assignment
    template <typename real>
	void        operator /=(       MATRIX_3x3 &A , const real     &s );

	//! Arithmetic operator - multiplication of matrix and vector
    template <typename real>
	VECTOR   operator  *( const MATRIX_3x3 &A , const VECTOR  &b );
	//! Arithmetic operator - multiplication of vector and matrix
    template <typename real>
	VECTOR   operator  *( const VECTOR  &b , const MATRIX_3x3 &A );
	//! Arithmetic operator - multiplication of vector and inverted matrix
    template <typename real>
	VECTOR   operator  /( const VECTOR  &b ,       MATRIX_3x3 &A );
*/
	////////////////////////////////////////////////////////////////////////////

	//! Print to std:ostream
    template <typename real>
	std::ostream& operator << ( std::ostream &out, const MATRIX_3x3 <real> &mat )
	{
		out << "["   << mat.xx << " , " << mat.xy << " , " << mat.xz << "]"
      		<< "["   << mat.yx << " , " << mat.yy << " , " << mat.yz << "]"
      		<< "["   << mat.zx << " , " << mat.zy << " , " << mat.zz << "]" << std::endl;
  		return out;
	}
}



#endif /*AP_MATRIX_H*/
