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
    	real x = 0; //!< x coordinate
		real y = 0; //!< y coordinate
		real z = 0; //!< z coordinate

		//! Deafult constructor
		/*!
		 * \note VECTOR object still has to be initialized by one of the methods: Resize, Assigne, or Set.
		 */
    	VECTOR() = default;
		
		//! Fill constructor
		/*!
		 * \param val - value witch initializes the vector
		 * \sa Set(real val)
		 */
    	VECTOR( real val ) { Set(val); }
    	 
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
    	VECTOR& operator =( const VECTOR &v )
		{
    		if( this != &v ) { Set(v.x, v.y, v.z); }
    		return *this;
		}
		
		//! Assignment operator with normalization
		/*!
		 * \param v - VECTOR to assign and normalize
		 */
    	VECTOR& operator ^=( const VECTOR &v )
		{
    		if( this != &v ) 
			{ 
				Set(v.x, v.y, v.z); 
				Norm();
			}
    		return *this;
		}

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
    	void SetGolobalResizeFlag(const bool val) {	grFlag = val; }

		//! Set the VECTOR elements value
		/*!
		 * \param val - value witch is set for all elements of the VECTOR
		 */
    	void Set(const real val) 
		{
			x = y = z = val;
		}
		
		//! Set from 3 values
		/*!
		 * \param xp - value assigned to the first VECTOR element
		 * \param yp - value assigned to the second VECTOR element
		 * \param zp - value assigned to the third VECTOR element
		 */
    	void Set(const real &xp, const real &yp, const real &zp) 	
		{ 
			x = xp;
			y = yp;
			z = zp;
		};
		
		//! Set values from other other VECTOR 
		/*!
		 * \param v - VECTOR witch is assigned to the current VECTOR
		 */
    	void Set(const VECTOR &v) 
		{ 
			x = v.x;
			y = v.y;
			z = v.z;
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
    	bool Set(const std::vector <real> &v, const bool rFlag=1) 
		{
			if( !(grFlag && rFlag) )	
			{
				//size unmatched not allowed - compare vector sizes 
				if(3 != v.size()) return 1;
			}

			if(v.size() > 0) x = v[0];
			if(v.size() > 1) y = v[1];
			if(v.size() > 2) z = v[2];
			return 0;
		};
		
		//! Set values from array
		/*!
		 * \param n - size of the VECTOR
		 * \param a - array witch is assigned to the VECTOR, values are stored in the [data](@ref data) container
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set(const unsigned int n, const real a[], const bool rFlag=1 ) 
		{ 
			if( !(grFlag && rFlag) )	
			{
				//size unmatched not allowed - compare vector sizes 
				if(3 != n) return 1;
			}
			
			if(n > 0) x = a[0];
			if(n > 1) y = a[1];
			if(n > 2) z = a[2];
			return 0;
		}

		//! Get to 3D values
		/*!
		 * \param xp - value copied from the first VECTOR element
		 * \param yp - value copied from the second VECTOR element
		 * \param zp - value copied from the third VECTOR element
		 */
    	void Get(real &xp, real &yp, real &zp) 	
		{ 
			xp = x;
			yp = y;
			zp = z;
		}
                   
		//! Get values from the VECTOR to other VECTOR 
		/*!
		 * \param v - VECTOR to witch current VECTOR is coppied
		 */
		void Get(VECTOR <real> &v) { v.x=x; v.y=y; v.z=z; }
		
		//! Get values to standard vector
		/*!
		 * \param v - std::vector to witch the VECTOR values are copied
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the std::vector is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Get(std::vector <real> &v, const bool rFlag=1) 
		{
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(3 != v.size()) return 1;
			}

			std::vector <real> w;
			w.push_back(x);
			w.push_back(y);
			w.push_back(z);
			v = w;
			return 0;
		};
		
		//! Get values to array
		/*!
		 * \param n - size of the array
		 * \param a - array to witch the VECTOR values are copied
		 * \return Returns 0 on success, or 1 on failure if the array and VECTOR size are not equal. 
		 */
    	bool Get(const unsigned int n, real a[], const bool rFlag=1) 
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(3 != n) return 1;
			}
			
			if(n > 0) a[0] = x;
			if(n > 1) a[1] = y;
			if(n > 2) a[2] = z;
			return 0;
		}

		//! Length of the vector 
		/*!
		 * Computed from all VECTOR elements as: sqrt(x*x + y*y + z*z + ...)
		 */
    	real Len(void) const 
		{
			return sqrt( x*x + y*y + z*z ); 
		}
		
		//! Length of the 2D vector in the XY plane
		/*!
		 * Computed as: sqrt(x*x + y*y)
		 */
    	real LenXY(void) const 
		{ 
			return sqrt( x*x + y*y ); 
		}  
		
		//! Length of the 2D vector in the XZ plane
		/*!
		 * Computed as: sqrt(x*x + z*z)
		 */
    	real LenXZ(void) const 
		{ 
			return sqrt( x*x + z*z ); 
		}  
		
		//! Length of the 2D vector in the YZ plane
		/*!
		 * Computed as: sqrt(y*y + z*z)
		 */
    	real LenYZ(void) const 
		{ 
			return sqrt( y*y + z*z ); 
		}  
		
		//! Square value of the vector
		/*!
		 * Computed from all VECTOR elements as: (x*x + y*y + z*z + ...)
		 */
    	real Sq(void) const 
		{ 
			return ( x*x + y*y + z*z ); 
		}

		//! Normalizes the vector to unit 
		/*!
		 * Coordiantes are divided by the vector value.\n
		 * /return vector value (length)
		 */
		real Norm(void)
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
    
		//! Determines if any element of the vector is a not-a-number (NaN) value
    	bool IsNan(void)
		{
			if( std::isnan(x) ) { std::clog << "x is NaN!!!" << std::endl; return 1; }
			if( std::isnan(y) ) { std::clog << "y is NaN!!!" << std::endl; return 1; }
			if( std::isnan(z) ) { std::clog << "z is NaN!!!" << std::endl; return 1; }
			return 0;
		}

	private:
		bool grFlag = 1; // global resize flag
	};

	//! Arithmetic operator - coordinates products (AxBx, AyBy, AzBz)
    template <typename real>
	VECTOR <real> operator &( const VECTOR <real> &a, const VECTOR <real> &b )
	{
 		VECTOR <real> c;
 		c.x = a.x * b.x;
		c.y = a.y * b.y;
 		c.z = a.z * b.z;
		return c;
	}

	//! Arithmetic operator - dot (scalar) product of two VECTORS
    template <typename real>
	real operator *( const VECTOR <real> &a , const VECTOR <real> &b )
	{
  		return (a.x*b.x + a.y*b.y + a.z*b.z);
	}

	//! Arithmetic operator - cross (vector) product of two VECTORS
    template <typename real>
	VECTOR <real> operator %( const VECTOR <real> &a , const VECTOR <real> &b )
	{
 		VECTOR <real> c;
  		c.x = a.y * b.z - a.z * b.y;
  		c.y = a.z * b.x - a.x * b.z;
  		c.z = a.x * b.y - a.y * b.x;
		return c;
	}
	
	//! Arithmetic operator - product of vector and scalar
    template <typename real>
	VECTOR <real> operator *( const VECTOR <real> &a , const real &s )
	{
 		VECTOR <real> c;
  		c.x = a.x * s;
  		c.y = a.y * s;
  		c.z = a.z * s;
		return c;
	}

	//! Arithmetic operator - product of scalar and vector
    template <typename real>
	VECTOR <real> operator *( const real &s , const VECTOR <real> &a ) { return a*s; }


	//! Arithmetic operator - vector divided by scalar (product of vector and reciprocal scalar)
    template <typename real>
	VECTOR <real> operator /( const VECTOR <real> &a , const real &s )
	{
 		VECTOR <real> c;
  		c.x = a.x / s;
  		c.y = a.y / s;
  		c.z = a.z / s;
 		return c;
	}

	//! Arithmetic operator - sum of two vectors
    template <typename real>
	VECTOR <real> operator +( const VECTOR <real> &a , const VECTOR <real> &b )
	{
 		VECTOR <real> c;
  		c.x = a.x + b.x;
  		c.y = a.y + b.y;
  		c.z = a.z + b.z;
		return c;
	}

	//! Arithmetic operator - subtraction of two vectors (sum of A and -B)
    template <typename real>
	VECTOR <real> operator -( const VECTOR <real> &a , const VECTOR <real> &b )
	{
 		VECTOR <real> c;
  		c.x = a.x - b.x;
  		c.y = a.y - b.y;
  		c.z = a.z - b.z;
		return c;
	}

	//! Arithmetic operator - reverse of vector (-A)
    template <typename real>
	VECTOR <real> operator -( const VECTOR <real> &a )
	{
 		VECTOR <real> c;
  		c.x = -a.x;
  		c.y = -a.y;
  		c.z = -a.z;
 		return c;
	}

	// Shorthand Ops

	//! Arithmetic operator - multiplication assigment (coordiante by coordiante)
    template <typename real>
	void operator &=( VECTOR <real> &a, const VECTOR <real> &b ) {	a = a&b; }

	//! Arithmetic operator - cross product assigment
    template <typename real>
	void operator %=( VECTOR <real> &a, const VECTOR <real> &b ) { a = a%b; }

	//! Arithmetic operator - multiplication assigment
    template <typename real>
	void operator *=( VECTOR <real> &a , const real &s ) { a = a*s; }
	//! Arithmetic operator - division assigment
    template <typename real>
	void operator /=( VECTOR <real> &a , const real  &s ) { a = a/s;} 

	//! Arithmetic operator - addition assigment
    template <typename real>
	void operator +=( VECTOR <real> &a, const VECTOR <real> &b ) { a = a+b; }

	//! Arithmetic operator - subtraction assigment
    template <typename real>
	void operator -=( VECTOR <real> &a , const VECTOR <real> &b ) { a = a-b; }

	//! Boolean operator - compares two vectors - true if all appropriate coordinates are equal
    template <typename real>
	bool operator ==( const VECTOR <real> &a, const VECTOR <real> &b )
	{
		if(a.x != b.x) { std::clog << "x is not equal!!!" << std::endl; std::clog << "A.x = " << a.x << "\tB.x = " << b.x << std::endl; return 0; }
		if(a.y != b.y) { std::clog << "y is not equal!!!" << std::endl; std::clog << "A.y = " << a.y << "\tB.y = " << b.y << std::endl; return 0; }
		if(a.z != b.z) { std::clog << "z is not equal!!!" << std::endl; std::clog << "A.z = " << a.z << "\tB.z = " << b.z << std::endl; return 0; }
		
		return 1;
	}

	//! print to std:ostream
	template <typename real>
	std::ostream& operator << ( std::ostream &out, const VECTOR <real> &vec )
	{
  		out << "[" << std::setw(12) << vec.x << std::setw(12) << vec.y << std::setw(12) << vec.z << "]";
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
