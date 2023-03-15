// Part of All Purpose - ap library

#ifndef AP_VECTOR_3_H
#define AP_VECTOR_3_H

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

namespace ap
{
    //! Vector class
	/*! 
	 * VECTOR_3 originates as part of the Config Lib for Panukl software: 
	 * https://itlims-zsis.meil.pw.edu.pl/software/PANUKL/2020/Config_API/index.html
	 * created by. F.A.Dul, modif. by T.Grabowski.\n
	 * The VECTOR_3 class is header only part of the ap library.
	 * It means that only the header file: ap_vector.h has to be included in the project and linking is not needed.\n
	 * Implementation of the VECTOR_3 class aims at universality and ease of use. 
	 * It is small, easy to understand and with clean code sytax 
	 * resembling as close as possible equations notation.\n
	 */
    template <typename real>
    class VECTOR_3
    {
	public:
    	real x = 0; //!< x coordinate
		real y = 0; //!< y coordinate
		real z = 0; //!< z coordinate

		//! Deafult constructor
		/*!
		 * \note VECTOR_3 object still has to be initialized by one of the Set() methods.
		 * \sa Set()
		 */
    	VECTOR_3() = default;
		
		//! Fill constructor
		/*!
		 * \param val - value witch initializes the vector
		 * \sa Set(real val)
		 */
    	VECTOR_3(const real val) { Set(val); }
    	 
		//! Copy constructor 
		/*!
		 * \param x - x element value
		 * \param y - y element value
		 * \param z - z element value
		 * \sa Set(const real &xp, const real &yp, const real &zp)
		 */
    	VECTOR_3(const real &x, const real &y, const real &z) { Set(x, y, z);	}
		
		//! Copy constructor 
		/*!
		 * \param v - VECTOR_3 to copy
		 * \sa Set(const VECTOR_3 &v)
		 */
    	VECTOR_3(const VECTOR_3 &v) { Set(v); }
		
		//! Copy constructor from std::vector
		/*!
		 * \param v - std::vector to copy
		 * \sa Set(const std::vector <real> &v, bool rFlag)
		 */
    	VECTOR_3(const std::vector <real> &v) { Set(v); }

		//! Copy constructor from array 
		/*!
		 * \param a - array to copy
		 * \sa Set(unsigned int size, real a[], bool rFlag) 
		 */
    	VECTOR_3(const unsigned int n, const real a[]) { Set(n, a); }
  
		//! Assignment operator
		/*!
		 * \param v - VECTOR_3 to assign
		 * \sa VECTOR_3(const VECTOR_3 &v)
		 */
    	VECTOR_3& operator =(const VECTOR_3 &v)
		{
    		if( this != &v ) { Set(v.x, v.y, v.z); }
    		return *this;
		}
		
		//! Assignment operator with normalization
		/*!
		 * This is equivalent of making the assigment operation followed by normalization Norm();
		 * \param v - VECTOR_3 to assign and normalize
		 * \sa Norm()
		 */
    	VECTOR_3& operator ^=(const VECTOR_3 &v)
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
		 * Size of the VECTOR_3 is compared with the input data. If they don't match 
		 * the Set() function may return failure value. The behavior depends on the flags set:\n
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
		 * The table indicates that resizing of the VECTOR_3 with Set() methods will be possible only when both flags are true.\n
		 * \note By default both resizing flags are true.
		 * \param val - value witch is set to the grFlag
		 */
    	void SetGolobalResizeFlag(const bool val) {	grFlag = val; }

		//! Set the VECTOR_3 elements the value
		/*!
		 * \param val - value witch is set for all elements of the VECTOR_3
		 */
    	void Set(const real val) 
		{
			x = y = z = val;
		}
		
		//! Set from 3 values
		/*!
		 * \param xp - value assigned to the first VECTOR_3 element
		 * \param yp - value assigned to the second VECTOR_3 element
		 * \param zp - value assigned to the third VECTOR_3 element
		 */
    	void Set(const real &xp, const real &yp, const real &zp) 	
		{ 
			x = xp;
			y = yp;
			z = zp;
		};
		
		//! Set values from other VECTOR_3 
		/*!
		 * \param v - VECTOR_3 witch is assigned to the current VECTOR_3
		 */
    	void Set(const VECTOR_3 &v) 
		{ 
			x = v.x;
			y = v.y;
			z = v.z;
		}

		//! Set values from standard vector
		/*!
		 * \param v - std::vector witch is assigned to the VECTOR_3
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR_3 is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR_3 has same size as the std::vector and the resize flags set. 
		 * In case of failure the std::vector won't be assigned.
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
		 * \param n - size of the array
		 * \param a - array witch is assigned to the VECTOR_3
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if unmached sizes are allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR_3 has same size as the array and the resize flags set. 
		 * In case of failure the array won't be assigned.
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
	
		//! Set VECTOR_3 (0, 0, 0)
		void Zero()
		{
			x = y = z = 0;
		}

		//! Set VECTOR_3 (1, 1, 1)
		void Ones()
		{
			x = y = z = 1;
		}

		//! Get to 3D values
		/*!
		 * \param xp - value copied from the first VECTOR_3 element
		 * \param yp - value copied from the second VECTOR_3 element
		 * \param zp - value copied from the third VECTOR_3 element
		 */
    	void Get(real &xp, real &yp, real &zp) 	
		{ 
			xp = x;
			yp = y;
			zp = z;
		}
                   
		//! Get values from the VECTOR_3 to other VECTOR_3 
		/*!
		 * \param v - VECTOR_3 to witch current VECTOR_3 is coppied
		 */
		void Get(VECTOR_3 <real> &v) { v.x=x; v.y=y; v.z=z; }
		
		//! Get values to standard vector
		/*!
		 * \param v - std::vector to witch the VECTOR_3 values are copied
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the std::vector is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the std::vector had to be resized and the values set for the resizing flags.
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
		 * \param a - array to witch the VECTOR_3 values are copied
		 * \return Returns 0 on success, or 1 on failure if the array and VECTOR_3 size are not equal. 
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
		 * Computed as: sqrt(x*x + y*y + z*z)
		 */
    	real Len() const 
		{
			return sqrt( x*x + y*y + z*z ); 
		}
		
		//! Length of the 2D vector in the XY plane
		/*!
		 * Computed as: sqrt(x*x + y*y)
		 */
    	real LenXY() const 
		{ 
			return sqrt( x*x + y*y ); 
		}  
		
		//! Length of the 2D vector in the XZ plane
		/*!
		 * Computed as: sqrt(x*x + z*z)
		 */
    	real LenXZ() const 
		{ 
			return sqrt( x*x + z*z ); 
		}  
		
		//! Length of the 2D vector in the YZ plane
		/*!
		 * Computed as: sqrt(y*y + z*z)
		 */
    	real LenYZ() const 
		{ 
			return sqrt( y*y + z*z ); 
		}  
		
		//! Square value of the vector
		/*!
		 * Computed from all VECTOR_3 elements as: (x*x + y*y + z*z + ...)
		 */
    	real Sq() const 
		{ 
			return ( x*x + y*y + z*z ); 
		}

		//! Normalizes the vector to unit 
		/*!
		 * Coordiantes are divided by the vector value.\n
		 * \return vector value (length)
		 */
		real Norm()
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
    	bool IsNan()
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
	VECTOR_3 <real> operator &( const VECTOR_3 <real> &a, const VECTOR_3 <real> &b )
	{
 		VECTOR_3 <real> c;
 		c.x = a.x * b.x;
		c.y = a.y * b.y;
 		c.z = a.z * b.z;
		return c;
	}

	//! Arithmetic operator - dot (scalar) product of two VECTOR_3S
    template <typename real>
	real operator *( const VECTOR_3 <real> &a , const VECTOR_3 <real> &b )
	{
  		return (a.x*b.x + a.y*b.y + a.z*b.z);
	}

	//! Arithmetic operator - cross (vector) product of two VECTOR_3S
    template <typename real>
	VECTOR_3 <real> operator %( const VECTOR_3 <real> &a , const VECTOR_3 <real> &b )
	{
 		VECTOR_3 <real> c;
  		c.x = a.y * b.z - a.z * b.y;
  		c.y = a.z * b.x - a.x * b.z;
  		c.z = a.x * b.y - a.y * b.x;
		return c;
	}
	
	//! Arithmetic operator - product of vector and scalar
    template <typename real>
	VECTOR_3 <real> operator *( const VECTOR_3 <real> &a , const real &s )
	{
 		VECTOR_3 <real> c;
  		c.x = a.x * s;
  		c.y = a.y * s;
  		c.z = a.z * s;
		return c;
	}

	//! Arithmetic operator - product of scalar and vector
    template <typename real>
	VECTOR_3 <real> operator *( const real &s , const VECTOR_3 <real> &a ) { return a*s; }


	//! Arithmetic operator - vector divided by scalar (product of vector and reciprocal scalar)
    template <typename real>
	VECTOR_3 <real> operator /( const VECTOR_3 <real> &a , const real &s )
	{
 		VECTOR_3 <real> c;
  		c.x = a.x / s;
  		c.y = a.y / s;
  		c.z = a.z / s;
 		return c;
	}

	//! Arithmetic operator - sum of two vectors
    template <typename real>
	VECTOR_3 <real> operator +( const VECTOR_3 <real> &a , const VECTOR_3 <real> &b )
	{
 		VECTOR_3 <real> c;
  		c.x = a.x + b.x;
  		c.y = a.y + b.y;
  		c.z = a.z + b.z;
		return c;
	}

	//! Arithmetic operator - subtraction of two vectors (sum of A and -B)
    template <typename real>
	VECTOR_3 <real> operator -( const VECTOR_3 <real> &a , const VECTOR_3 <real> &b )
	{
 		VECTOR_3 <real> c;
  		c.x = a.x - b.x;
  		c.y = a.y - b.y;
  		c.z = a.z - b.z;
		return c;
	}

	//! Arithmetic operator - reverse of vector (-A)
    template <typename real>
	VECTOR_3 <real> operator -( const VECTOR_3 <real> &a )
	{
 		VECTOR_3 <real> c;
  		c.x = -a.x;
  		c.y = -a.y;
  		c.z = -a.z;
 		return c;
	}

	// Shorthand Ops

	//! Arithmetic operator - multiplication assigment (coordiante by coordiante)
    template <typename real>
	void operator &=( VECTOR_3 <real> &a, const VECTOR_3 <real> &b ) {	a = a&b; }

	//! Arithmetic operator - cross product assigment
    template <typename real>
	void operator %=( VECTOR_3 <real> &a, const VECTOR_3 <real> &b ) { a = a%b; }

	//! Arithmetic operator - multiplication assigment
    template <typename real>
	void operator *=( VECTOR_3 <real> &a , const real &s ) { a = a*s; }
	
	//! Arithmetic operator - division assigment
    template <typename real>
	void operator /=( VECTOR_3 <real> &a , const real  &s ) { a = a/s;} 

	//! Arithmetic operator - addition assigment
    template <typename real>
	void operator +=( VECTOR_3 <real> &a, const VECTOR_3 <real> &b ) { a = a+b; }

	//! Arithmetic operator - subtraction assigment
    template <typename real>
	void operator -=( VECTOR_3 <real> &a , const VECTOR_3 <real> &b ) { a = a-b; }

	//! Boolean operator - compares two vectors - true if all appropriate coordinates are equal
    template <typename real>
	bool operator ==( const VECTOR_3 <real> &a, const VECTOR_3 <real> &b )
	{
		if(a.x != b.x) { std::clog << "x is not equal!!!" << std::endl; std::clog << "A.x = " << a.x << "\tB.x = " << b.x << std::endl; return 0; }
		if(a.y != b.y) { std::clog << "y is not equal!!!" << std::endl; std::clog << "A.y = " << a.y << "\tB.y = " << b.y << std::endl; return 0; }
		if(a.z != b.z) { std::clog << "z is not equal!!!" << std::endl; std::clog << "A.z = " << a.z << "\tB.z = " << b.z << std::endl; return 0; }
		
		return 1;
	}

	//! print to std:ostream
	template <typename real>
	std::ostream& operator << ( std::ostream &out, const VECTOR_3 <real> &vec )
	{
  		out << "[" << std::setw(12) << vec.x << std::setw(12) << vec.y << std::setw(12) << vec.z << "]";
  		return out;
	}
}

#endif /*AP_VECTOR_3_H*/
