// Part of All Purpose - ap library

#ifndef AP_MATRIX_H
#define AP_MATRIX_H

#include "ap_vector.h"

namespace ap
{
//! \brief Matrix class and functions
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
		/*!
		 * \note MATRIX_3x3 object still has to be initialized by one of the Set() methods.
		 * \sa Set()
		 */
    	MATRIX_3x3() = default;

		//! Fill constructor
		/*!
		 * \param val - value witch initializes the vector
		 * \sa Set(real val)
		 */
    	MATRIX_3x3 (const real &val) { Set(val); } 
		
		//! Copy constructor 
		/*!
		 * Set from 9 values.
		 * \param xx_p - xx element of the MATRIX_3x3 
		 * \param xy_p - xy element of the MATRIX_3x3
		 * \param xz_p - xz element of the MATRIX_3x3 
		 * \param yx_p - yx element of the MATRIX_3x3 
		 * \param yy_p - yy element of the MATRIX_3x3
		 * \param yz_p - yz element of the MATRIX_3x3 
		 * \param zx_p - zx element of the MATRIX_3x3 
		 * \param zy_p - zy element of the MATRIX_3x3
		 * \param zz_p - zz element of the MATRIX_3x3 
		 * \sa Set(const real &xx_p, const real &xy_p, const real &xz_p,
                 const real &yx_p, const real &yy_p, const real &yz_p,
                 const real &zx_p, const real &zy_p, const real &zz_p)
		 */
    	MATRIX_3x3( real xx_p , real xy_p , real xz_p ,
                	real yx_p , real yy_p , real yz_p ,
                	real zx_p , real zy_p , real zz_p ) 
	    { Set(xx_p, xy_p, xz_p, yx_p, yy_p, yz_p, zx_p, zy_p, zz_p); }
		
		//! Copy constructor 
		/*!
		 * \param A - MATRIX_3x3 to copy
		 * \sa Set(const MATRIX_3x3 &A)
		 */
    	MATRIX_3x3(const MATRIX_3x3 &A) { Set(A); } 
		
		//! Copy constructor from std::vector (one dimensional)
		/*!
		 * \param A - std::vector to copy to MATRIX_3x3 by rows
		 * \sa Set(std::vector <real> &A, const bool rFlag=1)
		 */
    	MATRIX_3x3(const std::vector <real> &A) { Set(A); }

		//! Copy constructor from std::vector (two dimensional)
		/*!
		 * \param A - std::vector to copy MATRIX_3x3 
		 * \sa Set(std::vector <real> &A, const bool rFlag=1)
		 */
    	MATRIX_3x3(const std::vector < std::vector <real> > &A) { Set(A); }

		//! Copy constructor from array (one dimensional) 
		/*!
		 * \param n - matrix size 2 or 3
		 * \param A - array to copy
		 * \sa Set(const unsigned int n, real A[], const bool rFlag=1) 
		 */
    	MATRIX_3x3(const unsigned int n, real A[]) { Set(n, A); }

		//! Copy constructor from array (fixed size two dimensional) 
		/*!
		 * \param A - array to copy
		 * \sa Set(const real A[3][3]) 
		 */
    	MATRIX_3x3(const real A[3][3]) { Set(A); }
    	
		//! Copy constructor from array of pointers (two dimensional) 
		/*!
		 * \param n - matrix size 2 or 3
		 * \param A - array to copy
		 * \sa Set(const unsigned int n, real **A, const bool rFlag=1) 
		 */
		MATRIX_3x3(const unsigned int n, real **A) { Set(n, A); }
  
		//! Assignment operator
		/*!
		 * \param A - MATRIX_3x3 to assign
		 * \sa MATRIX_3x3(const MATRIX_3x3 &A)
		 */
    	MATRIX_3x3& operator =(const MATRIX_3x3 &A)
		{
    		if( this != &A ) { Set(A); }
    		return *this;
		}
		
		//! Set global resize flag
		/*!
		 * Size of the MATRIX_3x3 is compared with the input data. If they don't match 
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
		 * The table indicates that resizing of the MATRIX_3x3 with Set() methods will be possible only when both flags are true.\n
		 * \note By default both resizing flags are true.
		 * \param val - value witch is set to the grFlag
		 */
    	void SetGolobalResizeFlag(const bool val) {	grFlag = val; }

		//! Set the MATRIX_3x3 elements the value
		/*!
		 * \param val - value witch is set for all elements of the MATRIX_3x3
		 */
    	void Set(const real val) { xx = xy = xz = yx = yy = yz = zx = zy = zz = val; }
		
		//! Copies components values from variables
		/*! 
		 * Set from 9 values.
		 * \param xx_p - xx element of the MATRIX_3x3 
		 * \param xy_p - xy element of the MATRIX_3x3
		 * \param xz_p - xz element of the MATRIX_3x3 
		 * \param yx_p - yx element of the MATRIX_3x3 
		 * \param yy_p - yy element of the MATRIX_3x3
		 * \param yz_p - yz element of the MATRIX_3x3 
		 * \param zx_p - zx element of the MATRIX_3x3 
		 * \param zy_p - zy element of the MATRIX_3x3
		 * \param zz_p - zz element of the MATRIX_3x3 
		 */
    	void Set(const real &xx_p, const real &xy_p, const real &xz_p,
                 const real &yx_p, const real &yy_p, const real &yz_p,
                 const real &zx_p, const real &zy_p, const real &zz_p)
        {
        	xx = xx_p;   xy = xy_p;    xz = xz_p;
        	yx = yx_p;   yy = yy_p;    yz = yz_p;
        	zx = zx_p;   zy = zy_p;    zz = zz_p;
        };
		
		//! Set values from other MATRIX_3x3 
		/*!
		 * \param A - MATRIX_3x3 witch is assigned to the current MATRIX_3x3
		 */
    	void Set(const MATRIX_3x3 &A) 
		{ 
        	xx = A.xx;   xy = A.xy;    xz = A.xz;
        	yx = A.yx;   yy = A.yy;    yz = A.yz;
        	zx = A.zx;   zy = A.zy;    zz = A.zz;
		}

		//! Copies components values from the std::vector (one dimensional)
		/*!
		 * \param A - std::vector witch is assigned to the MATRIX_3x3 by rows
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the MATRIX_3x3 is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR_3 has same size as the std::vector and the resize flags set. 
		 * In case of failure the std::vector won't be assigned.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set(const std::vector <real> &A, const bool rFlag=1)
        {
			if( !(grFlag && rFlag) )	
			{
				//size unmatched not allowed - compare vector sizes 
				if(9 != A.size()) return 1;
			}

			if(A.size() >= 4 && A.size() < 9)
			{
        		xx = A[0];   xy = A[1];
        		yx = A[2];   yy = A[3];
			}

			if(A.size() >= 9)
			{
        		xx = A[0];   xy = A[1];    xz = A[2];
        		yx = A[3];   yy = A[4];    yz = A[5];
        		zx = A[6];   zy = A[7];    zz = A[8];
			}

			return 0;
        };

		//! Copies components values from the std::vector (two dimensional)
		/*!
		 * \param A - <std::vector <std::vector> > witch is assigned to the MATRIX_3x3
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the MATRIX_3x3 is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR_3 has same size as the std::vector and the resize flags set. 
		 * In case of failure the <std::vector <std::vector> > won't be assigned.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set(const std::vector < std::vector <real> > &A, const bool rFlag=1)
        {
			std::cerr << "Copies components values from the std::vector (two dimensional)" << std::endl;
			if( !(grFlag && rFlag) )	
			{
				//size unmatched not allowed - compare vector sizes 
				if(3 != A.size() && 3 != A[0].size()) return 1;
			}

			if(A.size() == 2 && A[0].size() == 2)
			{
				xx = A[0][0];   xy = A[0][1];
        		yx = A[1][0];   yy = A[1][1];
			}

			if(A.size() >= 3 && A[0].size() >= 3)
			{
				xx = A[0][0];   xy = A[0][1];   xz = A[0][2];
        		yx = A[1][0];   yy = A[1][1];   yz = A[1][2];
        		zx = A[2][0];   zy = A[2][1];   zz = A[2][2];
			}

			return 0;
        };

		//! Copies components values from the array (one dimensional)
		/*!
		 * \param n - matrix size 2 or 3
		 * \param A - one dimensional array witch is assigned to the MATRIX_3x3 by rows
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the MATRIX_3x3 is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the MATRIX_3x3 has same size as the array and the resize flags set. 
		 * In case of failure the array won't be assigned.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set(const unsigned int n, real A[], const bool rFlag=1)
        {
			std::cerr << "Copies components values from the array (one dimensional)" << std::endl;
			if( !(grFlag && rFlag) )	
			{
				//size unmatched not allowed - compare vector sizes 
				if(9 != n) return 1;
			}

			if(n >= 4 && n < 9)
			{
        		xx = A[0];   xy = A[1];
        		yx = A[2];   yy = A[3];
			}

			if(n >= 9)
			{
        		xx = A[0];   xy = A[1];    xz = A[2];
        		yx = A[3];   yy = A[4];    yz = A[5];
        		zx = A[6];   zy = A[7];    zz = A[8];
			}

			return 0;
        };

		//! Copies components values from the array (two dimensional)
		/*!
		 * \param A - fixed size, two dimensional array witch is assigned to the MATRIX_3x3 by rows
		 */
    	void Set(const real A[3][3])
        {
			xx = A[0][0];   xy = A[0][1];   xz = A[0][2];
        	yx = A[1][0];   yy = A[1][1];   yz = A[1][2];
       		zx = A[2][0];   zy = A[2][1];   zz = A[2][2];
        }
		
		//! Copies components values from the array of pointers (two dimensional)
		/*!
		 * \param n - size of matrix 2 or 3
		 * \param A - two dimensional array of pointers witch values are assigned to the MATRIX_3x3 by rows
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the MATRIX_3x3 is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the VECTOR_3 has same size as the array and the resize flags set. 
		 * In case of failure the array won't be assigned.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Set(const unsigned int n, real **A, const bool rFlag=1)
        {
			std::cerr << "Copies components values from the array (two dimensional)" << std::endl;
			for(unsigned int i=0; i<3; i++) {
				for(unsigned int j=0; j<3; j++) { std::clog << A[i][j] << std::endl; }
			}

			if( !(grFlag && rFlag) )	
			{
				//size unmatched not allowed - compare vector sizes 
				if(3 != n) return 1;
			}

			if(n == 2)
			{
				xx = A[0][0];   xy = A[0][1];
        		yx = A[1][0];   yy = A[1][1];
			}

			if(n >= 3)
			{
				xx = A[0][0];   xy = A[0][1];   xz = A[0][2];
        		yx = A[1][0];   yy = A[1][1];   yz = A[1][2];
        		zx = A[2][0];   zy = A[2][1];   zz = A[2][2];
			}

			return 0;
        }

		//! Set all MATRIX_3x3 components to zero  
    	void Zero()
        {
        	xx = 0;  xy = 0;  xz = 0;
        	yx = 0;  yy = 0;  yz = 0;
        	zx = 0;  zy = 0;  zz = 0;
        };
		
		//! Set all MATRIX_3x3 components to one  
    	void Ones()
        {
        	xx = 1;  xy = 1;  xz = 1;
        	yx = 1;  yy = 1;  yz = 1;
        	zx = 1;  zy = 1;  zz = 1;
        };

		//! Set unit matrix  
    	void Unit()
        {
        	xx = 1;  xy = 0;  xz = 0;
        	yx = 0;  yy = 1;  yz = 0;
        	zx = 0;  zy = 0;  zz = 1;
        };

		//! Set rotation MATRIX_3x3 about X axis with radians
		/*!
		 * \param radAng - angle of rotation about X axis in radians  
		 */
		void RotMatX(real radAng)
		{
			real SX = sin(radAng);
			real CX = cos(radAng);

        	xx = 1;  xy = 0;   xz = 0;
        	yx = 0;  yy = CX;  yz = -SX;
        	zx = 0;  zy = SX;  zz = CX;
		}

		//! Set rotation MATRIX_3x3 about Y axis with radians
		/*!
		 * \param radAng - angle of rotation about Y axis in radians  
		 * \return Rotation matrix about Y axis. 
		 */
		void RotMatY(real radAng)
		{
			real SY = sin(radAng);
			real CY = cos(radAng);

        	xx = CY;   xy = 0;   xz = SY;
        	yx = 0;    yy = 1;   yz = 0;
        	zx = -SY;  zy = 0;   zz = CY;
		}

		//! Set rotation MATRIX_3x3 about Z axis with radians
		/*!
		 * \param radAng - angle of rotation about Z axis in radians  
		 * \return Rotation matrix about Z axis. 
		 */
		void RotMatZ(real radAng)
		{
			real SZ = sin(radAng);
			real CZ = cos(radAng);

			MATRIX_3x3 MZ( CZ, -SZ, 0,
            		       SZ,  CZ, 0,
                    		0,  0,  1 );

        	xx = CZ;   xy = -SZ;  xz = 0;
        	yx = SZ;   yy = CZ;   yz = 0;
        	zx = 0;    zy = 0;    zz = 1;
		}

		//! Set rotation MATRIX_3x3 about X axis with degrees
		/*!
		 * \param degAng - angle of rotation about X axis in degrees 
		 * \return Rotation matrix about X axis.
		 */
		void RotMatXdeg(real degAng) { RotMatX(degAng*M_PI/180); }

		//! Set rotation MATRIX_3x3 about Y axis with degrees
		/*!
		 * \param degAng - angle of rotation about Y axis in degrees  
		 * \return Rotation matrix about Y axis. 
		 */
		void RotMatYdeg(real degAng) { RotMatY(degAng*M_PI/180); }

		//! Set rotation MATRIX_3x3 about Z axis with degrees
		/*!
		 * \param degAng - angle of rotation about Z axis in degrees  
		 * \return Rotation matrix about Z axis. 
		 */
		void RotMatZdeg(real degAng) { RotMatZ(degAng*M_PI/180); }

		//! Get to MATRIX_3x3 values
		/*!
		 * \param xx_p - xx value copied from the MATRIX_3x3 
		 * \param xy_p - xy value copied from the MATRIX_3x3
		 * \param xz_p - xz value copied from the MATRIX_3x3 
		 * \param yx_p - xx value copied from the MATRIX_3x3 
		 * \param yy_p - xy value copied from the MATRIX_3x3
		 * \param yz_p - xz value copied from the MATRIX_3x3 
		 * \param zx_p - xx value copied from the MATRIX_3x3 
		 * \param zy_p - xy value copied from the MATRIX_3x3
		 * \param zz_p - xz value copied from the MATRIX_3x3 
		 */
    	void Get(real &xx_p, real &xy_p, real &xz_p, real &yx_p, real &yy_p, real &yz_p, real &zx_p, real &zy_p, real &zz_p) 	
		{ 
        	xx_p = xx;   xy_p = xy;    xz_p = xz;
        	yx_p = yx;   yy_p = yy;    yz_p = yz;
        	zx_p = zx;   zy_p = zy;    zz_p = zz;
		}
		
		//! Get values from the MATRIX_3x3 to other MATRIX_3x3 
		/*!
		 * \param A - MATRIX_3x3 to witch current MATRIX_3x3 is coppied
		 */
		void Get(MATRIX_3x3 <real> &A) { 
			A.xx=xx; A.xy=xy; A.xz=xz;
			A.yx=yx; A.yy=yy; A.yz=yz;
			A.zx=zx; A.zy=zy; A.zz=zz;
		}
		
		//! Get values to standard vector (one dimensional)
		/*!
		 * \param A - std::vector to witch the MATRIX_3x3 values are copied by rows
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the std::vector is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the std::vector had to be resized and the values set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Get(std::vector <real> &A, const bool rFlag=1) 
		{
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(9 != A.size()) return 1;
			}

			std::vector <real> v;
			v.push_back(xx);
			v.push_back(xy);
			v.push_back(xz);
			v.push_back(yx);
			v.push_back(yy);
			v.push_back(yz);
			v.push_back(zx);
			v.push_back(zy);
			v.push_back(zz);
			A = v;
			return 0;
		};

		//! Get values to standard vector (two dimensional)
		/*!
		 * \param A - std::vector to witch the MATRIX_3x3 values are copied
		 * \param rFlag - resize flag, with global resize flag <b>rgFlag</b> indicates if resizing of the std::vector is allowed
		 * \return Returns 0 on success, or 1 on failure. The result depends if the std::vector had to be resized and the values set for the resizing flags.
		 * \sa SetGolobalResizeFlag(bool val)
		 */
    	bool Get(std::vector < std::vector <real> > &A, const bool rFlag=1) 
		{
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(3 != A.size() && 3 != A[0].size()) return 1;
			}

			if(A.size() == 2 && A[0].size() == 2)
			{
				A[0][0] = xx;   A[0][1] = xy;
        		A[1][0] = yx;   A[1][1] = yy;
			}

			if(A.size() >= 3 && A[0].size() >= 3)
			{
				A[0][0] = xx;   A[0][1] = xy;   A[0][2] = xz;
        		A[1][0] = yx;   A[1][1] = yy;   A[1][2] = yz;
        		A[2][0] = zx;   A[2][1] = zy;   A[2][2] = zz;
			}
			
			return 0;
		};

		//! Get values to array (one dimensional)
		/*!
		 * \param n - size of the array
		 * \param A - array to witch the MATRIX_3x3 values are copied
		 * \param rFlag - resize flag
		 * \return Returns 0 on success, or 1 on failure if the array and MATRIX_3x3 sizes don't match. 
		 */
    	bool Get(const unsigned int n, real A[], const bool rFlag=1) 
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(9 != n) return 1;
			}
			
			if(n >= 4 && n < 9)
			{
        		A[0] = xx;   A[1] = xy;
        		A[2] = yx;   A[3] = yy;
			}

			if(n >= 9)
			{
        		A[0] = xx;   A[1] = xy;    A[2] = xz;
        		A[3] = yx;   A[4] = yy;    A[5] = yz;
        		A[6] = zx;   A[7] = zy;    A[8] = zz;
			}

			return 0;
		}
		
		//! Get values to fixed size array (two dimensional)
		/*!
		 * \param A - array to witch the MATRIX_3x3 values are copied
		 */
    	void Get(real A[3][3])
        {
			A[0][0] = xx;   A[0][1] = xy;   A[0][2] = xz;
        	A[1][0] = yx;   A[1][1] = yy;   A[1][2] = yz;
       		A[2][0] = zx;   A[2][1] = zy;   A[2][2] = zz;
        }

		//! Get values to array of pointers (two dimensional)
		/*!
		 * \param n - size of the array
		 * \param A - array of pointers to witch the MATRIX_3x3 values are copied
		 * \param rFlag - resize flag
		 * \return Returns 0 on success, or 1 on failure if the array and MATRIX_3x3 sizes don't match. 
		 */
    	bool Get(const unsigned int n, real **A, const bool rFlag=1) 
		{ 
			if( !(grFlag && rFlag) )	
			{
				//resizing not allowed - compare vector sizes 
				if(3 != n) return 1;
			}
			
			if(n == 2)
			{
				A[0][0] = xx;   A[0][1] = xy;
        		A[1][0] = yx;   A[1][1] = yy;
			}

			if(n >= 3)
			{
				A[0][0] = xx;   A[0][1] = xy;   A[0][2] = xz;
        		A[1][0] = yx;   A[1][1] = yy;   A[1][2] = yz;
        		A[2][0] = zx;   A[2][1] = zy;   A[2][2] = zz;
			}

			return 0;
		}

		//! Matrix determinant	
		/*!
		 * \return Value of the MATRIX_3x3 determinant. 
		 */
    	real Det()
        {
        	return xx*(yy*zz - yz*zy) - xy*(yx*zz - yz*zx) + xz*(yx*zy - yy*zx);
        }

	private:
		bool grFlag = 1; // global resize flag
	};

	//! Arithmetic operator - multiplication of 2 matrices
    template <typename real>
	MATRIX_3x3 <real> operator *(const MATRIX_3x3 <real> &A, const MATRIX_3x3 <real> &B)
	{
  		MATRIX_3x3 <real> C;

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
	
	//! Arithmetic operator - multiplication of 2 matrices components ( AxxBxx, AxyBxy, ..., AzzBzz )
    template <typename real>
	MATRIX_3x3 <real> operator &(const MATRIX_3x3 <real> &A, const MATRIX_3x3 <real> &B)
	{
 		MATRIX_3x3 <real> C;

  		C.xx = A.xx * B.xx;     C.xy = A.xy * B.xy;      C.xz = A.xz * B.xz;
  		C.yx = A.yx * B.yx;     C.yy = A.yy * B.yy;      C.yz = A.yz * B.yz;
  		C.zx = A.zx * B.zx;     C.zy = A.zy * B.zy;      C.zz = A.zz * B.zz;

 		return C;
	}
	
	//! Arithmetic operator - product of matrix and scalar
    template <typename real>
	MATRIX_3x3 <real> operator *(const MATRIX_3x3 <real> &A, const real &s)
	{
 		MATRIX_3x3 <real> C;

  		C.xx = A.xx * s;     C.xy = A.xy * s;      C.xz = A.xz * s;
  		C.yx = A.yx * s;     C.yy = A.yy * s;      C.yz = A.yz * s;
  		C.zx = A.zx * s;     C.zy = A.zy * s;      C.zz = A.zz * s;

 		return C;
	}
	
	//! Arithmetic operator - product of scalar and matrix
    template <typename real>
	MATRIX_3x3 <real> operator *(const real &s, const MATRIX_3x3 <real> &A)
	{
 		return A*s;
	}

	//! Arithmetic operator - division of matrix by scalar (product of matrix and 1/s)
    template <typename real>
	MATRIX_3x3 <real> operator /(const MATRIX_3x3 <real> &A, const real &s)
	{
 		MATRIX_3x3 <real> C;

  		C.xx = A.xx / s;     C.xy = A.xy / s;      C.xz = A.xz / s;
  		C.yx = A.yx / s;     C.yy = A.yy / s;      C.yz = A.yz / s;
  		C.zx = A.zx / s;     C.zy = A.zy / s;      C.zz = A.zz / s;

 		return C;
	}
	
	//! Arithmetic operator - sum of 2 matrices
    template <typename real>
	MATRIX_3x3 <real> operator +(const MATRIX_3x3 <real> &A, const MATRIX_3x3 <real> &B)
	{
 		MATRIX_3x3 <real> C;

  		C.xx = A.xx + B.xx;     C.xy = A.xy + B.xy;      C.xz = A.xz + B.xz;
  		C.yx = A.yx + B.yx;     C.yy = A.yy + B.yy;      C.yz = A.yz + B.yz;
  		C.zx = A.zx + B.zx;     C.zy = A.zy + B.zy;      C.zz = A.zz + B.zz;

 		return C;
	}
	
	//! Arithmetic operator - subtraction of 2 matrices (sum of A and -B)
    template <typename real>
	MATRIX_3x3 <real> operator -(const MATRIX_3x3 <real> &A, const MATRIX_3x3 <real> &B)
	{
 		MATRIX_3x3 <real> C;

  		C.xx = A.xx - B.xx;     C.xy = A.xy - B.xy;      C.xz = A.xz - B.xz;
  		C.yx = A.yx - B.yx;     C.yy = A.yy - B.yy;      C.yz = A.yz - B.yz;
  		C.zx = A.zx - B.zx;     C.zy = A.zy - B.zy;      C.zz = A.zz - B.zz;

 		return C;
	}

	//! Arithmetic operator - reverse of matrix (-A)
    template <typename real>
	MATRIX_3x3 <real> operator -(const MATRIX_3x3 <real> &A)
	{
 		MATRIX_3x3 <real> C;

  		C.xx = -A.xx;     C.xy = -A.xy;      C.xz = -A.xz;
  		C.yx = -A.yx;     C.yy = -A.yy;      C.yz = -A.yz;
  		C.zx = -A.zx;     C.zy = -A.zy;      C.zz = -A.zz;

 		return C;
	}

	//! Arithmetic operator - multiplication of matrix and vector
    template <typename real>
	VECTOR_3 <real> operator *(const MATRIX_3x3 <real> &A, const VECTOR_3 <real> &v)
	{
 		VECTOR_3 <real> w;

  		w.x = A.xx * v.x  +  A.xy * v.y  +  A.xz * v.z;
  		w.y = A.yx * v.x  +  A.yy * v.y  +  A.yz * v.z;
  		w.z = A.zx * v.x  +  A.zy * v.y  +  A.zz * v.z;

 		return w;
	}
	
	//! Arithmetic operator - multiplication of vector and matrix
    template <typename real>
	VECTOR_3 <real> operator *(const VECTOR_3 <real> &v, const MATRIX_3x3 <real> &A)
	{
 		VECTOR_3 <real> w;

  		w.x = v.x * A.xx  +  v.y * A.yx  +  v.z * A.zx;
  		w.y = v.x * A.xy  +  v.y * A.yy  +  v.z * A.zy;
  		w.z = v.x * A.xz  +  v.y * A.yz  +  v.z * A.zz;

 		return w;
	}
	
	//! Arithmetic operator - multiplication of vector and inverted matrix
    template <typename real>
	VECTOR_3 <real> operator /(const VECTOR_3 <real> &v, const MATRIX_3x3 <real> &A)
	{
		return v * ~A;
	}

	//! Arithmetic operator - matrix transposition ( A^T )
    template <typename real>
	MATRIX_3x3 <real> operator !(const MATRIX_3x3 <real> &A) // A^T
	{
  		return MATRIX_3x3 <real> (
                          A.xx, A.yx, A.zx,
                          A.xy, A.yy, A.zy,
                          A.xz, A.yz, A.zz
                       	  );
	}
	
	//! Arithmetic operator - matrix inversion ( A^(-1) )
    template <typename real>
	MATRIX_3x3 <real> operator ~(const MATRIX_3x3 <real> &A) // A^(-1)
	{
  		MATRIX_3x3 <real> C = A;
  		real w;
		w = C.Det();
  
  		C.xx = A.yy * A.zz  -  A.zy * A.yz;
  		C.xy = A.xz * A.zy  -  A.xy * A.zz;
  		C.xz = A.xy * A.yz  -  A.xz * A.yy;

  		C.yx = A.yz * A.zx  -  A.yx * A.zz;
  		C.yy = A.xx * A.zz  -  A.xz * A.zx;
  		C.yz = A.xz * A.yx  -  A.xx * A.yz;

  		C.zx = A.yx * A.zy  -  A.yy * A.zx;
  		C.zy = A.xy * A.zx  -  A.xx * A.zy;
  		C.zz = A.xx * A.yy  -  A.xy * A.yx;
  
  		if(w != 0.0) C /= w;
  
  		return C;
	}
	
	// Shorthand Ops

	//! Arithmetic operator - multiplication of 2 matrices
    template <typename real>
	void operator *=(MATRIX_3x3 <real> &A, const MATRIX_3x3 <real> &B) { A = A*B; }
	
	//! Arithmetic operator - multiplication of 2 matrices components ( AxxBxx, AxyBxy, ..., AzzBzz )
    template <typename real>
	void operator &=(MATRIX_3x3 <real> &A, const MATRIX_3x3 <real> &B) { A = A&B; }
	
	//! Arithmetic operator - product of matrix and scalar
    template <typename real>
	void operator *=(MATRIX_3x3 <real> &A, const real &s) { A = A*s; }
	
	//! Arithmetic operator - division assignment
    template <typename real>
	void operator /=(MATRIX_3x3 <real> &A, const real &s) { A = A/s; }
	
	//! Arithmetic operator - sum of 2 matrices
    template <typename real>
	void operator +=(MATRIX_3x3 <real> &A, const MATRIX_3x3 <real> &B) { A = A+B; }
	
	//! Arithmetic operator - subtraction of 2 matrices (sum of A and -B)
    template <typename real>
	void operator -=(MATRIX_3x3 <real> &A, const MATRIX_3x3 <real> &B) { A = A-B; }

	//! Arithmetic operator - multiplication of vector and matrix
    template <typename real>
	void operator *=(VECTOR_3 <real> &v, const MATRIX_3x3 <real> &A) { v = v*A; }
	
	//! Arithmetic operator - multiplication of vector and inverted matrix
    template <typename real>
	void operator /=(VECTOR_3 <real> &v, const MATRIX_3x3 <real> &A) { v = v/A; }
	
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
