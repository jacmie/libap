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

/*! \file vector.h
    \brief Vector 3D class and functions
*/

#ifndef AP_VECTOR_H
#define AP_VECTOR_H

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

namespace ap
{
    //! Vector class
	/*! 
	 * VECTOR originates as part of the Config Lib for Panukl software: 
	 * https://itlims-zsis.meil.pw.edu.pl/software/PANUKL/2020/Config_API/index.html
	 * created by. F.A.Dul, modif. by T.Grabowski.\n
	 * The VECTOR class is header only part of the ap library.
	 * It means that only the header file: ap_vector.h has to be included in the project and linking is not needed.\n
	 * Implementation of the VECTOR class aims at universality and ease of use. 
	 * It is small, easy to understand and with clean code sytax 
	 * resembling as close as possible equations notation.\n
	 */
    template <typename real>
    class VECTOR
    {
	public:
    	real x = 0; //!< first element of the vector
		real y = 0; //!< y coordinate
		real z = 0; //!< z coordinate
		real w = 0; //!< z coordinate
    	std::vector <real> data; //!< public data container

		//! Deafult constructor
		/*!
		 * \note VECTOR object still has to be initialized by one of the methods: Resize, Assigne, or Set.
		 */
    	VECTOR() = default;
		
		//! Set size constructor
		/*!
		 * \param n - size of the vector
		 */
    	VECTOR( unsigned int n ) { Assign(n, 0); }
		
		//! Fill constructor
		/*!
		 * \param n - size of the vector
		 * \param val - value witch initializes the vector
		 * \sa Assign(unsigned int n, real val)
		 */
    	VECTOR( unsigned int n, real val ) { Assign(n, val); }
    	 
		//! Copy constructor 
		/*!
		 * \param v - VECTOR to copy
		 * \sa Assign(unsigned int n, real val)
		 * \sa Set(unsigned int n, real val, bool rFlag)
		 */
    	VECTOR( const VECTOR &v ) { Set(v);	}
		
		//! Copy constructor 
		/*!
		 * \param v - std::vector to copy
		 * \sa Set(const std::vector <real> &v, bool rFlag)
		 */
    	VECTOR( const std::vector <real> &v ) { Set(v); }

		//! Copy constructor 
		/*!
		 * \param a - array to copy
		 * \sa bool Set(unsigned int size, real a[], bool rFlag) 
		 */
    	VECTOR( real a[] ) { Set(a); }
  
		//! Assignment operator
		/*!
		 * \param v - VECTOR to assign
		 * \sa VECTOR(const VECTOR &v)
		 */
    	VECTOR & operator =( const VECTOR &v )
		{
    		if( this != &v )
        	{
        		x = v.x;
        		y = v.y;
        		z = v.z;
    		}

    		return *this;
		}

		//! Resize the VECTOR
		/*!
		 * Method similar to std::vector.resize(n). 
		 * \param n - new size of the VECTOR
		 * \sa VECTOR(const VECTOR &v)
		 */
		void Resize(unsigned int n) { data.resize(n); }

		//! Resize and assign the value to the VECTOR
		/*!
		 * Method similar to std::vector.assign(n, val). 
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param n - new size of the VECTOR
		 * \param val - value assigned to all elements of the VECTOR
		 */
		void Assign(unsigned int n, real val) { data.assign(n, val); Link(); }
		
		//! Resize and assign the value to the VECTOR
		/*!
		 * \return Size of the VECTOR
		 */
		unsigned int Size() const { return data.size(); }

		//! Set global resize flag
		/*!
		 * Resize flags provide control over the VECTOR resizing. 
		 * Most of the Set() methods can resize the resulting vector basing on the input data.
		 * Size of the VECTOR is compared with the input data. If they don't match the VECTOR can be resized, 
		 * or the Set() function may return failure value. The behavior depends on the flags set:\n
		 * 
		 * - **grFlag** - global resize flag
		 * -  **rFlag** - local resize flag of the particular Set() operation
		 *
		 * Set() methods perform boolean operations as in the following table:
		 *
		 * | grFlag | grFlag | Result |
		 * | :----: | :----: | :----: |
		 * | 1      | 1      | 1      |
		 * | 1      | 0      | 0      |
		 * | 0      | 1      | 0      |
		 * | 0      | 0      | 0      |
		 *
		 * The table indicates that resizing of the VECTOR with Set() methods will be possible only when both flags are true.\n
		 * By default both resizing flags are true.
		 * \note Resize() and Assign() methods don't depend on the resizing flags.
		 * \param val - value witch is set to the grFlag
		 */
    	void SetGolobalResizeFlag( bool val ) {	grFlag = val; }

		//! Set the VECTOR elements value
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param val - value witch is set for all elements of the VECTOR
		 */
    	void Set( real val ) 
		{ 
			data.assign(data.size(), val); 
			Link();
		}
		
		//! Resize the VECTOR and set elements value
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param n - size of the VECTOR
		 * \param val - value witch is assigned to the elements of the VECTOR
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 * \sa Assign(unsigned int n, real val)
		 */
    	bool Set( unsigned int n, real val, bool rFlag=1 ) 
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(data.size() != n) return 1;
			}

			data.assign(n, val);
			Link();
			return 0;
		}
		
		//! Set values from other other VECTOR 
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param v - VECTOR witch is assigned to the current VECTOR
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set( const VECTOR &v, bool rFlag=1 ) 
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(data.size() != v.Size()) return 1;
			}

			data = v.data;
			Link();
			return 0;
		}

		//! Set values from standard vector
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param v - std::vector witch is assigned to the VECTOR, values are stored in the [data](@ref data) container
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set( const std::vector <real> &v, bool rFlag=1 ) 
		{
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(data.size() != v.size()) return 1;
			}

			data = v;
			Link();
			return 0;
		};
		
		//! Set values from array
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param n - size of the VECTOR
		 * \param a - array witch is assigned to the VECTOR, values are stored in the [data](@ref data) container
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set( unsigned int n, real a[], bool rFlag=1 ) 
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(data.size() != n) return 1;
			}
			
			data.resize(0);
			for(unsigned int i=0; i<n; i++) { data.push_back(a[i]); }
			Link();
			return 0;
		}

		//! Set from 2D values
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x) 
		 * values are assigned matching the first two values of the [data](@ref data).
		 * \param xp - value assigned to the first VECTOR element
		 * \param yp - value assigned to the second VECTOR element
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set2D( real xp, real yp, bool rFlag=1 ) 	
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(data.size() != 2) return 1;
			}
			
			data.resize(0);
			data.push_back(xp);
			data.push_back(yp);
			Link();
			return 0;
		};
		
		//! Set from 3D values
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z) 
		 * values are assigned matching the first three values of the [data](@ref data).
		 * \param xp - value assigned to the first VECTOR element
		 * \param yp - value assigned to the second VECTOR element
		 * \param zp - value assigned to the third VECTOR element
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set3D( real xp, real yp, real zp, bool rFlag=1 ) 	
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(data.size() != 3) return 1;
			}
			
			data.resize(0);
			data.push_back(xp);
			data.push_back(yp);
			data.push_back(zp);
			Link();
			return 0;
		};
	
		//! Set from 4D values
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param xp - value assigned to the first VECTOR element
		 * \param yp - value assigned to the second VECTOR element
		 * \param zp - value assigned to the third VECTOR element
		 * \param wp - value assigned to the fourth VECTOR element
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set4D( real xp, real yp, real zp, real wp, bool rFlag=1 ) 	
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(data.size() != 4) return 1;
			}
			
			data.resize(0);
			data.push_back(xp);
			data.push_back(yp);
			data.push_back(zp);
			data.push_back(wp);
			Link();
			return 0;
		};

		//! Length of the vector 
		/*!
		 * Computed from all VECTOR elements as: sqrt(x*x + y*y + z*z + ...)
		 */
    	real Len( void ) const 
		{
			real len=0;
			for(unsigned int i=0; i<Size(); i++) { len += data[i]*data[i]; }
			return sqrt(len); 
		}
		
		//! Length of the 2D vector in the XY plane
		/*!
		 * Computed as: sqrt(x*x + y*y)
		 */
    	real LenXY( void ) const 
		{ 
			return sqrt( x*x + y*y ); 
		}  
		
		//! Length of the 2D vector in the XZ plane
		/*!
		 * Computed as: sqrt(x*x + z*z)
		 */
    	real LenXZ( void ) const 
		{ 
			return sqrt( x*x + z*z ); 
		}  
		
		//! Length of the 2D vector in the YZ plane
		/*!
		 * Computed as: sqrt(y*y + z*z)
		 */
    	real LenYZ( void ) const 
		{ 
			return sqrt( y*y + z*z ); 
		}  
		
		//! Square value of the vector
		/*!
		 * Computed from all VECTOR elements as: (x*x + y*y + z*z + ...)
		 */
    	real Sq( void ) const 
		{ 
			real len=0;
			for(unsigned int i=0; i<Size(); i++) { len += data[i]*data[i]; }
			return len; 
		}

		//! Normalizes the vector to unit 
		/*!
		 * Coordiantes are divided by the vector value.\n
		 * /return vector value (length)
		 */
		real Normalize( void )
		{
    		real dlg = this->Len();

    		if( dlg > 0.0 )
        	{
        		x /= dlg;
        		y /= dlg;
        		z /= dlg;
        	}

    		return dlg;
		}
                    
		//! copies coordinates to three variables    
    	void Get( real &xp, real &yp, real &zp ){ xp = x; yp = y; zp = z; };
		//! copies coordinates to the array  
    	void Get( real a[] )                   { a[0] = x; a[1] = y; a[2] = z;};
    
		//! determines if any coordinate of given vector is a not-a-number (NaN) value.
    	bool Isnan( void ){ return std::isnan( x ) || std::isnan( y ) || std::isnan( z ); };
    
		//!	Rotating functions
		//! rotates the vector relative to the X axis by an alpha[rad] angle 
		void rotX( real alpha)
		{
    		real yy=y;
    		real zz=z;
    		y = yy*cos(alpha) - zz*sin(alpha);
    		z = yy*sin(alpha) + zz*cos(alpha);
		}

		//! rotates the vector relative to the Y axis by an alpha[rad] angle 
		void rotY( real alpha)
		{
    		real xx=x;
    		real zz=z;
    		x = zz*sin(alpha) + xx*cos(alpha);
    		z = zz*cos(alpha) - xx*sin(alpha);
		}

		//! rotates the vector relative to the Z axis by an alpha[rad] angle 
		void rotZ( real alpha)
		{
    		real xx=x;
    		real yy=y;
    		x = xx*cos(alpha) - yy*sin(alpha);
    		y = xx*sin(alpha) + yy*cos(alpha);
		}

		//! rotates the vector relative to the X axis by an alpha[deg] angle (precise values for 0,90,180,270 deg)
		void rotdX( real alfa)
		{
    		real yy = y;
    		real zz = z;

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

		//! rotates the vector relative to the Y  axis (shifted by dX longwise X) by an alpha[deg] angle (precise values for 0,90,180,270 deg)
		void rotdY( real alfa, real dX = 0. )
		{
    		real xx = x;
    		real zz = z;
    
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

		//! rotates the vector relative to the Z axis by an alpha[deg] angle (precise values for 0,90,180,270 deg)
		void rotdZ( real alfa)
		{
    		real xx = x;
    		real yy = y;
	
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

        // Member access.  The first operator[] returns a const reference
        // rather than a Real value.  This supports writing via standard file
        // operations that require a const pointer to data.
        real const& operator[](unsigned int i) const { return data[i]; }
        real& operator[](unsigned int i) { return data[i]; }

	private:
		bool grFlag = 1; // global resize flag
		
		void Link()
		{
			unsigned int n=data.size();
			if(n>0) x = data[0];
			if(n>1)	y = data[1];
			if(n>2)	z = data[2];
			if(n>3)	w = data[3];
		}
	};

/*
/// Arithmetic operator - dot (scalar) product of two vectors
real      operator  *( const VECTOR &A, const VECTOR &B );
/// Arithmetic operator - cross (vector) product of two vectors
VECTOR   operator  %( const VECTOR &A, const VECTOR &B );
/// Arithmetic operator - product of vector and scalar
VECTOR   operator  *( const VECTOR &A, const real    &s );
/// Arithmetic operator - product of scalar and vector
VECTOR   operator  *( const real    &s, const VECTOR &A );
/// Arithmetic operator - vector divided by scalar (product of vector and reciprocal scalar)
VECTOR   operator  /( const VECTOR &A, const real    &s );
/// Arithmetic operator - sum of two vectors
VECTOR   operator  +( const VECTOR &A, const VECTOR &B );
/// Arithmetic operator - sum of two vectors
VECTOR   operator  +( const VECTOR &A                     );
/// Arithmetic operator - subtraction of two vectors (sum of A and -B)
VECTOR   operator  -( const VECTOR &A, const VECTOR &B );
/// Arithmetic operator - reverse of vector (-A)
VECTOR   operator  -( const VECTOR &A                     );
/// Arithmetic operator - coordinates products (AxBx, AyBy, AzBz)
VECTOR   operator  &( const VECTOR &A, const VECTOR &B );
/// Arithmetic operator - cross product assigment
void        operator %=(       VECTOR &A, const VECTOR &B );
/// Arithmetic operator - addition assigment
void        operator +=(       VECTOR &A, const VECTOR &B );
/// Arithmetic operator - subtraction assigment
void        operator -=(       VECTOR &A, const VECTOR &B );
/// Arithmetic operator - multiplication assigment (coordiante by coordiante)
void        operator &=(       VECTOR &A, const VECTOR &B );
/// Arithmetic operator - multiplication assigment
void        operator *=(       VECTOR &A, const real    &s );
/// Arithmetic operator - division assigment
void        operator /=(       VECTOR &A, const real    &s );

	// dot product
	real operator *( const VECTOR &A , const VECTOR &B )
	{
  		return  ( A.x * B.x  +  A.y * B.y  +  A.z * B.z );
	}

	// cross product
	VECTOR operator %( const VECTOR &A , const VECTOR &B )
	{
 		VECTOR c;

  		c.x = A.y * B.z - A.z * B.y;
  		c.y = A.z * B.x - A.x * B.z;
  		c.z = A.x * B.y - A.y * B.x;

 		return c;
	}

	// scalar mult
	VECTOR operator *( const VECTOR &A , const real &s )
	{
 		VECTOR c;

  		c.x = A.x * s;
  		c.y = A.y * s;
  		c.z = A.z * s;

 		return c;
	}

	VECTOR operator *( const real &s , const VECTOR &A )
	{
 		VECTOR c;

  		c.x = A.x * s;
  		c.y = A.y * s;
  		c.z = A.z * s;

 		return c;
	}

	VECTOR operator /( const VECTOR &A , const real &s )
	{
 		VECTOR c;

  		c.x = A.x / s;
  		c.y = A.y / s;
  		c.z = A.z / s;

 		return c;
	}

	// sum
	VECTOR operator +( const VECTOR &A , const VECTOR &B )
	{
 		VECTOR c;

  		c.x = A.x + B.x;
  		c.y = A.y + B.y;
  		c.z = A.z + B.z;

 		return c;
	}

	VECTOR operator +( const VECTOR &A )
	{
 		VECTOR c;

  		c.x = A.x;
  		c.y = A.y;
  		c.z = A.z;

 		return c;
	}

	VECTOR operator -( const VECTOR &A , const VECTOR &B )
	{
 		VECTOR c;

  		c.x = A.x - B.x;
  		c.y = A.y - B.y;
  		c.z = A.z - B.z;

 		return c;
	}

	VECTOR operator -( const VECTOR &A )
	{
 		VECTOR c;

  		c.x = -A.x;
  		c.y = -A.y;
  		c.z = -A.z;

 		return c;
	}

	// Shorthand Ops

	void operator %=( VECTOR &A , const VECTOR &B )
	{
 		VECTOR tmp;

  		tmp.x = A.y * B.z - A.z * B.y;
  		tmp.y = A.z * B.x - A.x * B.z;
  		tmp.z = A.x * B.y - A.y * B.x;

  		A.x = tmp.x;
  		A.y = tmp.y;
  		A.z = tmp.z;
	}

	void operator +=( VECTOR &A , const VECTOR &B )
	{
  		A.x += B.x;
  		A.y += B.y;
  		A.z += B.z;
	}

	void operator -=( VECTOR &A , const VECTOR &B )
	{
  		A.x -= B.x;
  		A.y -= B.y;
  		A.z -= B.z;
	}

	void operator &=( VECTOR &A , const VECTOR &B )
	{
  		A.x *= B.x;
  		A.y *= B.y;
  		A.z *= B.z;
	}

	void operator *=( VECTOR &A , const real &s )
	{
  		A.x *= s;
  		A.y *= s;
  		A.z *= s;
	}

	void operator /=( VECTOR &A , const real  &s )
	{
  		A.x /= s;
  		A.y /= s;
  		A.z /= s;
	}
	*/
		
	//! Boolean operator - compares two vectors - true if all appropriate coordinates are equal
    template <typename real>
	bool operator ==( const VECTOR <real> &A, const VECTOR <real> &B )
	{
		if(A.Size() != B.Size()) 
		{
			std::clog << "Vector sizes not equal!!!" << std::endl;
			return 0;
		}

		for(unsigned int i=0; i<A.Size(); i++)
		{
			if(A.data[i] != B.data[i])
			{
				std::clog << "Id of the first element of the vectors which is not equal: " << i << "!!!" << std::endl;
				std::clog << "Element value of the A vector: " << A.data[i] << std::endl;
				std::clog << "Element value of the B vector: " << B.data[i] << std::endl;
				return 0;
			}
		}

		//return ( A.x == B.x && A.y == B.y && A.z == B.z );
		return 1;
	}

	//! print to std:ostream
	template <typename real>
	std::ostream& operator << ( std::ostream &out, const VECTOR <real> &vec )
	{
  		//out << "["   << vec.x << " , " << vec.y << " , " << vec.z << "]";
		out << "[";
		for(unsigned int i=0; i<vec.Size(); i++)
		{
			out << std::setw(12) << vec[i];
		}
		out << "]";
  		return out;
	}

	/*
	//! returns vector (0,0,0)
	VECTOR  VECTOR_3__E0( void )
	{
  		return VECTOR( 0.0 , 0.0 , 0.0 );
	}

	//! returns vector (1,1,1)
	VECTOR  VECTOR_3__E1( void )
	{
  		return VECTOR( 1.0 , 1.0 , 1.0 );
	}

	//! returns vector (1,0,0)
	VECTOR  VECTOR_3__Ex( void )
	{
  		return VECTOR( 1.0 , 0.0 , 0.0 );
	}

	//! returns vector (0,1,0)
	VECTOR  VECTOR_3__Ey( void )
	{
  		return VECTOR( 0.0 , 1.0 , 0.0 );
	}

	//! returns vector (0,0,1)
	VECTOR  VECTOR_3__Ez( void )
	{
  		return VECTOR( 0.0 , 0.0 , 1.0 );
	}
	*/
}

#endif /*AP_VECTOR_H*/
