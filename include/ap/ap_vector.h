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
    	VECTOR( unsigned int n ) { Assign(n, 1.1); }
		
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
				data = v.data;
				Link();
    		}

    		return *this;
		}
		
		//! Assignment operator
		/*!
		 * \param v - VECTOR to assign
		 * \sa VECTOR(const VECTOR &v)
		 */
		//!!!!!!!!!!!!!!!!!!!!!!!!!
		/*
    	VECTOR.x & operator =( const VECTOR &v.x )
		{
			/ *
    		if( this != &v )
        	{
				data = v.data;
				Link();
    		}* /

    		return *this;
		}*/

		//! Resize the VECTOR
		/*!
		 * Method similar to std::vector.resize(n). 
		 * \param n - new size of the VECTOR
		 * \sa VECTOR(const VECTOR &v)
		 */
		void Resize(const unsigned int n) { data.resize(n); }

		//! Resize and assign the value to the VECTOR
		/*!
		 * Method similar to std::vector.assign(n, val). 
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param n - new size of the VECTOR
		 * \param val - value assigned to all elements of the VECTOR
		 */
		void Assign(const unsigned int n, const real val) { data.assign(n, val); Link(); }
		
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
    	void SetGolobalResizeFlag(const bool val) {	grFlag = val; }

		//! Set the VECTOR elements value
		/*!
		 * Additionaly VECTOR variables [x](@ref x), [y](@ref x), [z](@ref z), [w](@ref w) 
		 * values are assigned matching the first four values of the [data](@ref data).
		 * \param val - value witch is set for all elements of the VECTOR
		 */
    	void Set(const real val) 
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
    	bool Set(const unsigned int n, const real val, const bool rFlag=1 ) 
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
    	bool Set(const VECTOR &v, const bool rFlag=1) 
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
    	bool Set(const std::vector <real> &v, const bool rFlag=1) 
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
    	bool Set(const unsigned int n, const real a[], const bool rFlag=1 ) 
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
    	bool Set2D(const real xp, const real yp, const bool rFlag=1) 	
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
    	bool Set3D(const real xp, const real yp, const real zp, const bool rFlag=1 ) 	
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
    	bool Set4D(const real xp, const real yp, const real zp, const real wp, const bool rFlag=1 ) 	
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
    	real Len(void) const 
		{
			real len=0;
			for(unsigned int i=0; i<Size(); i++) { len += data[i]*data[i]; }
			return sqrt(len); 
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
			real len=0;
			for(unsigned int i=0; i<Size(); i++) { len += data[i]*data[i]; }
			return len; 
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
                   
		//! Get values from the VECTOR to other VECTOR 
		/*!
		 * \param v - VECTOR to witch current VECTOR is coppied
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the VECTOR is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR had to be resized and the value set for the resizing flags
		 * \sa SetGolobalResizeFlag(bool val)
		 */
		bool Get(VECTOR <real> &v, const bool rFlag=1)
		{
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(data.size() != v.Size()) return 1;
			}

			v.data = data;
			v.Link();
			return 0;
		}
		
		//! Get values from standard vector
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
				if(data.size() != v.size()) return 1;
			}

			v = data;
			return 0;
		};
		
		//! Get values to array
		/*!
		 * \param n - size of the array
		 * \param a - array to witch the VECTOR values are copied
		 * \return Returns 0 on success, or 1 on failure if the array and VECTOR size are not equal. 
		 */
    	bool Get(const unsigned int n, real a[]) 
		{ 
			if(data.size() != n) return 1;
			
			for(unsigned int i=0; i<n; i++) { a[i] = data[i]; }
			return 0;
		}

		//! Get to 2D values
		/*!
		 * \param xp - value copied from the first VECTOR element
		 * \param yp - value copied from the second VECTOR element
		 * \return Returns 0 on success, or 1 if the VECTOR size is not equal to 2
		 */
    	bool Get2D(real &xp, real &yp) 	
		{ 
			if(data.size() != 2) return 1;
		
			xp = data[0];
			yp = data[1];
			return 0;
		};

		//! Get to 3D values
		/*!
		 * \param xp - value copied from the first VECTOR element
		 * \param yp - value copied from the second VECTOR element
		 * \param zp - value copied from the third VECTOR element
		 * \return Returns 0 on success, or 1 if the VECTOR size is not equal to 3
		 */
    	bool Get3D(real &xp, real &yp, real &zp) 	
		{ 
			if(data.size() != 3) return 1;
		
			xp = data[0];
			yp = data[1];
			zp = data[2];
			return 0;
		};

		//! Get to 4D values
		/*!
		 * \param xp - value copied from the first VECTOR element
		 * \param yp - value copied from the second VECTOR element
		 * \param zp - value copied from the third VECTOR element
		 * \param wp - value copied from the fourth VECTOR element
		 * \return Returns 0 on success, or 1 if the VECTOR size is not equal to 4
		 */
    	bool Get4D(real &xp, real &yp, real &zp, real &wp) 	
		{ 
			if(data.size() != 4) return 1;
		
			xp = data[0];
			yp = data[1];
			zp = data[2];
			wp = data[3];
			return 0;
		};
    
		//! Determines if any element of the vector is a not-a-number (NaN) value
    	bool IsNan(void)
		{
			for(unsigned int i=0; i<Size(); i++)
			{
				if( std::isnan(data[i]) ) 
				{
					std::clog << "Element: " << i << " of the vector is NaN!!!" << std::endl;
					return 1;
				}
			}

			return 0;
		}
    
        // Member access.  The first operator[] returns a const reference
        // rather than a Real value.  This supports writing via standard file
        // operations that require a const pointer to data.
        real const& operator[](unsigned int i) const { return data[i]; }
        real& operator[](unsigned int i) { return data[i]; }
		
		void Link()
		{
			unsigned int n=data.size();
			if(n>0) x = data[0];
			if(n>1)	y = data[1];
			if(n>2)	z = data[2];
			if(n>3)	w = data[3];
		}

	private:
		bool grFlag = 1; // global resize flag
	};

	//! Arithmetic operator - coordinates products (AxBx, AyBy, AzBz)
    template <typename real>
	VECTOR <real> operator &( const VECTOR <real> &a, const VECTOR <real> &b )
	{
 		VECTOR <real> c;
		if( a.Size()!=b.Size() ) return c;

		c.Resize(a.Size());
		for(unsigned int i=0; i<a.Size(); i++) { c[i] = a[i]*b[i]; }
		c.Link();
		return c;
	}
	
	//! Arithmetic operator - dot (scalar) product of two VECTORS
    template <typename real>
	real operator *( const VECTOR <real> &a , const VECTOR <real> &b )
	{
		real c=0;
		if( a.Size() != b.Size() ) return c;
		for(unsigned int i=0; i<a.Size(); i++) { c += a[i]*b[i]; }
  		return c;
	}

	//! Arithmetic operator - cross (vector) product of two VECTORS
    template <typename real>
	VECTOR <real> operator %( const VECTOR <real> &a , const VECTOR <real> &b )
	{
 		VECTOR <real> c;
		if( a.Size()<3 || b.Size()<3 || a.Size()!=b.Size() ) return c;

		c.Resize(a.Size());
  		c[0] = a.y * b.z - a.z * b.y;
  		c[1] = a.z * b.x - a.x * b.z;
  		c[2] = a.x * b.y - a.y * b.x;
		c.Link();
		return c;
	}
	
	//! Arithmetic operator - product of vector and scalar
    template <typename real>
	VECTOR <real> operator *( const VECTOR <real> &a , const real &s )
	{
 		VECTOR <real> c(a.Size());
		for(unsigned int i=0; i<a.Size(); i++) { c[i] = a[i]*s; }
		c.Link();
		return c;
	}

	//! Arithmetic operator - product of scalar and vector
    template <typename real>
	VECTOR <real> operator *( const real &s , const VECTOR <real> &a ) { return a*s; }


	//! Arithmetic operator - vector divided by scalar (product of vector and reciprocal scalar)
    template <typename real>
	VECTOR <real> operator /( const VECTOR <real> &a , const real &s )
	{
 		VECTOR <real> c(a.Size());
		for(unsigned int i=0; i<a.Size(); i++) { c[i] = a[i]/s; }
		c.Link();
 		return c;
	}

	//! Arithmetic operator - sum of two vectors
    template <typename real>
	VECTOR <real> operator +( const VECTOR <real> &a , const VECTOR <real> &b )
	{
 		VECTOR <real> c;
		if( a.Size() != b.Size() ) return c;

 		c.Resize(a.Size());
		for(unsigned int i=0; i<a.Size(); i++) { c[i] = a[i] + b[i]; }
		c.Link();
 		return c;
	}

	//! Arithmetic operator - subtraction of two vectors (sum of A and -B)
    template <typename real>
	VECTOR <real> operator -( const VECTOR <real> &a , const VECTOR <real> &b )
	{
 		VECTOR <real> c;
		if( a.Size() != b.Size() ) return c;

 		c.Resize(a.Size());
		for(unsigned int i=0; i<a.Size(); i++) { c[i] = a[i] - b[i]; }
		c.Link();
 		return c;
	}

	//! Arithmetic operator - reverse of vector (-A)
    template <typename real>
	VECTOR <real> operator -( const VECTOR <real> &a )
	{
 		VECTOR <real> c(a.Size());
		for(unsigned int i=0; i<a.Size(); i++) { c[i] = -a[i]; }
		c.Link();
 		return c;
	}

	// Shorthand Ops

	//! Arithmetic operator - multiplication assigment (coordiante by coordiante)
    template <typename real>
	void operator &=( VECTOR <real> &a, const VECTOR <real> &b ) {	a = a&b; }

	//! Arithmetic operator - cross product assigment
    template <typename real>
	void operator %=( VECTOR <real> &a, const VECTOR <real> &b ) { a = a%b; }

	//! Arithmetic operator - addition assigment
    template <typename real>
	void operator +=( VECTOR <real> &a, const VECTOR <real> &b ) { a = a+b; }

	//! Arithmetic operator - subtraction assigment
    template <typename real>
	void operator -=( VECTOR <real> &a , const VECTOR <real> &b ) { a = a-b; }

	//! Arithmetic operator - multiplication assigment
    template <typename real>
	void operator *=( VECTOR <real> &a , const real &s ) { a = a*s; }

	//! Arithmetic operator - division assigment
    template <typename real>
	void operator /=( VECTOR <real> &a , const real  &s ) { a = a/s;} 
		
	//! Boolean operator - compares two vectors - true if all appropriate coordinates are equal
    template <typename real>
	bool operator ==( const VECTOR <real> &a, const VECTOR <real> &b )
	{
		if(a.Size() != b.Size()) 
		{
			std::clog << "Vector sizes not equal!!!" << std::endl;
			return 0;
		}

		for(unsigned int i=0; i<a.Size(); i++)
		{
			if(a.data[i] != b.data[i])
			{
				std::clog << "Id of the first element of the vectors which is not equal: " << i << "!!!" << std::endl;
				std::clog << "Element value of the A vector: " << a.data[i] << std::endl;
				std::clog << "Element value of the B vector: " << b.data[i] << std::endl;
				return 0;
			}
		}
		
		unsigned int n=a.Size();
		if(n>0) { if(a.x != b.x) { std::clog << "x is not equal!!!" << std::endl; std::clog << "A.x = " << a.x << "\tB.x = " << b.x << std::endl; return 0; } }
		if(n>1) { if(a.y != b.y) { std::clog << "y is not equal!!!" << std::endl; std::clog << "A.y = " << a.y << "\tB.y = " << b.y << std::endl; return 0; } }
		if(n>2) { if(a.z != b.z) { std::clog << "z is not equal!!!" << std::endl; std::clog << "A.z = " << a.z << "\tB.z = " << b.z << std::endl; return 0; } }
		if(n>3) { if(a.w != b.w) { std::clog << "w is not equal!!!" << std::endl; std::clog << "A.w = " << a.w << "\tB.w = " << b.w << std::endl; return 0; } }
		
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
