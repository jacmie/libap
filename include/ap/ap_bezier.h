#ifndef BEZIER_H
#define BEZIER_H

#include <vector>

#include "ap_bezierPoint.h"

namespace ap {

template <class REAL> class BEZIER
{
    public:
    
	// Parameters for vertex search on the curve for given coordinate 
    unsigned int iter = 50; //!< Number of maximum iterations
    REAL eps = 1e-6; 		//!< Tolerance of acceptance
	REAL relax = 1;			//!< Relaxation paramiter in range (0, 1) for the search algorithm 
							/*! Smaller improves convergence, but increases computations time */
	
	std::vector < BEZIER_POINT <REAL> > P;  //!< Vector of Poles
	std::vector < BEZIER_POINT <REAL> > V;  //!< Vector of Vertexes
	std::vector <REAL> tV; 				    //!< t parameter of the Vertexes

	//! Default constructor
	BEZIER() = default;
	
	//! Constructor with declaration of number of Poles
	/*!
 	 * \param n - number of Poles
 	 */
    BEZIER(unsigned int n) { Init(n); }
	
	//! Initilizer needed when the default constructor was used
	/*!
 	 * \param nmax - number of Poles
 	 */
	void Init(unsigned int nmax);
	
	//! Findes coordinates of point on the curve for the given t parameter 
	/*!
 	 * \param t - parametric position on curve in range <0, 1>
 	 * \param x - returned x coordinate
 	 * \param y - returned y coordinate
 	 * \param z - returned z coordinate
 	 * \return 0 on success, fails when parameter t is out of range
	 */
    virtual int  Vertex(REAL t, REAL &x, REAL &y, REAL &z);
	
	//! Generates sequence of vertexes on the curve 
	/*!
 	 * \param v_nr - number of vertexes to generate 
	 */
    virtual void VertexesSeq(unsigned int v_nr);
	
	//! Returns t parameter value for given coordinate 
	/*!
 	 * \param xyz - specifies which coordinate is given:
	 * - 0 - x
	 * - 1 - y
	 * - 2 - z
 	 * \param value - value of the coordinate
	 * \return t parameter value
	 */
    virtual REAL tVertex(unsigned int xyz, REAL value);
	
	REAL Length(); 		/*!< \return Length of the curve by integrating distances between vertexes. */
	REAL LengthX(); 	/*!< \return Length of the curve after projection on the X axis by integrating distances between vertexes. */  
	REAL LengthY();		/*!< \return Length of the curve after projection on the Y axis by integrating distances between vertexes. */
	REAL LengthZ();		/*!< \return Length of the curve after projection on the Z axis by integrating distances between vertexes. */
	REAL LengthXY();	/*!< \return Length of the curve projected on the XY plane by integrating distances between vertexes. */
	REAL LengthYZ();	/*!< \return Length of the curve projected on the YZ plane by integrating distances between vertexes. */
	REAL LengthXZ();	/*!< \return Length of the curve projected on the XZ plane by integrating distances between vertexes. */
	
	//! Derives Poles min and max values 
	/*!
 	 * \param xyz - specifies which coordinate is used:
	 * - 0 - x
	 * - 1 - y
	 * - 2 - z
 	 * \param min - returned minimum value
 	 * \param max - returned maximum value
	 */
	void PMinMax(unsigned int xyz, REAL &min, REAL &max);

	//! Sets printing format for Poles 
	/*!
     * \param brackets  	- flag to use brackets when the point is printed in the output stream, default - false 
     * \param comas 		- flag to use comas when the point is printed in the output stream, default - false
     * \param separator - space reserved to print point coordinate when the point is printed in the output stream
     * \param no_print_xyz - index of the point coordinate to ommit when the point is printed in the output stream, egz.: 2 - z coordinate not printed
	 */
    void PrintPolesFormat(bool brackets, bool comas, unsigned int separator, unsigned int no_print_xyz);
	
	//! Sets printing format for Vertexes 
	/*!
     * \param brackets  	- flag to use brackets when the point is printed in the output stream, default - false 
     * \param comas 		- flag to use comas when the point is printed in the output stream, default - false
     * \param separator - space reserved to print point coordinate when the point is printed in the output stream
     * \param no_print_xyz - index of the point coordinate to ommit when the point is printed in the output stream, egz.: 2 - z coordinate not printed
	 */
    void PrintVertexesFormat(bool brackets, bool comas, unsigned int separator, unsigned int no_print_xyz);
	
	//! Prints Poles on the output stream
    void PrintPoles(std::ostream &out);
	
	//! Prints Vertexes on the output stream
	void PrintVertexes(std::ostream &out);

    private:
    
	std::vector <REAL> C;
    
	REAL Length(bool xflag, bool yflag, bool zflag);
	void BinomialCoef();
};

} // namespace ap

#endif
