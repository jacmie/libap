#ifndef _B_SPLINE_H_
#define _B_SPLINE_H_

#include "ap_bezier.h"

namespace ap {

enum bspline_type {UNIFORM, QUASI_UNIFORM, PEACEWISE};

//! Bspline curves class
template <class REAL> class B_SPLINE : public BEZIER <REAL>
{
	unsigned int min_degree;
    
	public:

    unsigned int degree; 	//!< Spline degree
    std::vector < REAL > K; //!< Vector of knots

	//! Default constructor
	B_SPLINE();
	
	//! Constructor with parameters
	/*!
 	 * \param poles_nr - number of Poles
 	 * \param curve_degree - spline degree
 	 * \param type - spline type:
	 * - 0 - UNIFORM
	 * - 1 - QUASI_UNIFORM
	 * - 2 - PEACEWISE
 	 */
    B_SPLINE(unsigned int poles_nr, unsigned int curve_degree, unsigned int type=QUASI_UNIFORM);
	
	//! Sets minimum degree of the spline
	/*!
 	 * \param val - minimum degree value
 	 */
	void SetMinDegree(unsigned int val);
	
	//! Checks if degree is higher or equal minimum degree of the spline
	/*!
 	 * \param degree - degree value
 	 * \return 0 on success.
 	 */
	bool CheckMinDegree(unsigned int degree);
	
	//! Checks condition for minium number of poles
	/*!
 	 * \param poles_nr - number of poles
 	 * \param degree - degree value
 	 * \return 0 on success.
 	 */
	bool CheckMinPolesNr(unsigned int poles_nr, unsigned int degree);
	
	//! Checks condition for knots number
	/*!
 	 * \param degree - degree value
 	 * \param type - spline type:
	 * - 0 - UNIFORM
	 * - 1 - QUASI_UNIFORM
	 * - 2 - PEACEWISE
 	 * \param poles_nr - number of poles
 	 * \param k_nr - number of knots
 	 * \return 0 on success.
 	 */
	bool KnotsNrWithoutMults(unsigned int degree, unsigned int type, unsigned int poles_nr, unsigned int &k_nr);
	
	//! Initializes the Bspline
	/*!
 	 * \param poles_nr - number of poles
 	 * \param curve_degree - degree value
 	 * \param type - spline type:
	 * - 0 - UNIFORM
	 * - 1 - QUASI_UNIFORM
	 * - 2 - PEACEWISE
 	 * \return 0 on success.
 	 */
	bool Init(unsigned int poles_nr, unsigned int curve_degree, unsigned int type=QUASI_UNIFORM);

	//! Findes coordinates of point on the curve for the given t parameter 
	/*!
 	 * \param t - parametric position on curve in range <0, 1>
 	 * \param x - returned x coordinate
 	 * \param y - returned y coordinate
 	 * \param z - returned z coordinate
 	 * \return 0 on success, fails when parameter t is out of range
	 */
    int  Vertex(REAL t, REAL &x, REAL &y, REAL &z);
	
	//! Generates sequence of vertexes on the curve 
	/*!
 	 * \param v_nr - number of vertexes to generate 
	 */
	void VertexesSeq(unsigned int v_nr);
    
	//REAL tVertex(unsigned int XYZ, REAL Value); // Not as easy as in Bezier
    
	private:
    
	void deBoorData(unsigned int k, unsigned int xyz, std::vector <REAL> &d);
	double deBoor(unsigned int k, double x, std::vector <REAL> &d);

	public:

	std::vector < std::vector <REAL> > N; //!< Vector of basis functions coefficients
	
	//! Bspline basis functions 
	/*!
 	 * \param t - parametric position on curve in range <0, 1>
	 */
	void BasisFunctions(REAL t); 
};

} // namespace ap

#endif
