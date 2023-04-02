#ifndef _SPLINE_AIRFOIL_H_
#define _SPLINE_AIRFOIL_H_

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <FL/fl_ask.H>

#include "ap_basicMath.h"
#include "ap_bezier.h"

namespace ap {

//! Creates airfoils based on bezier curves
class BEZIER_AIRFOIL
{
    unsigned int nBR_ = 1;
    unsigned int nBF_ = 1;
    unsigned int nTF_ = 1;
    unsigned int nTR_ = 1;

	unsigned int vBR_, vBF_, vTF_, vTR_, vCirc_;
    double LEcircX_, LEcircY_, LEcircR_, BcircX_, BcircY_;
    double sBR_, sBF_, sTF_, sTR_; // slope tan(a)
    double minThX_, minThY_, maxThX_, maxThY_;
	
	public:
	
	BEZIER <double> splineBR; //!< Bottom Rear vertices
    BEZIER <double> splineBF; //!< Bottom Front vertices
    BEZIER <double> splineTF; //!< Top Front vertices
    BEZIER <double> splineTR; //!< Top Rear vertices
    BEZIER <double> splineLE; //!< LE circle vertices

	//! Default constructor
	BEZIER_AIRFOIL() = default;
	
	//! Initialize airfoil described by two bezier curves
	/*!
 	 * \param n - number of Poles defining bottom and top curves
 	 * \param v - number of Vertexes generated on bottom and top curves
 	 */
    void Init2b(unsigned int n, unsigned int v);
	
	//! Initialize airfoil described by two bezier curves
	/*!
 	 * \param nB - number of Poles defining bottom curve
 	 * \param vB - number of Vertexes generated on bottom curve
 	 * \param nT - number of Poles defining top curve
 	 * \param vT - number of Vertexes generated on top curve
 	 */
    void Init2b(unsigned int nB, unsigned int vB, unsigned int nT, unsigned int vT);
	
	//! Initialize airfoil described by four bezier curves
	/*!
 	 * \param nR - number of Poles defining rear - top and bottom curves
 	 * \param vR - number of Vertexes generated on rear - top and bottom curves
 	 * \param nF - number of Poles defining front - top and bottom curves
 	 * \param vF - number of Vertexes generated on front - top and bottom curves
 	 */
    void Init4b(unsigned int nR, unsigned int vR, unsigned int nF, unsigned int vF);
	
	//! Initialize airfoil described by four bezier curves
	/*!
 	 * \param nBR - number of Poles defining bottom-rear curve
 	 * \param vBR - number of Vertexes generated on bottom-rear curve
 	 * \param nBF - number of Poles defining bottom-front curve
 	 * \param vBF - number of Vertexes generated on bottom-front curve
 	 * \param nTF - number of Poles defining top-front curve
 	 * \param vTF - number of Vertexes generated on top-front curve
 	 * \param nTR - number of Poles defining top-rear curve
 	 * \param vTR - number of Vertexes generated on top-rear curve
 	 */
	void Init4b(unsigned int nBR, unsigned int vBR, unsigned int nBF, unsigned int vBF, unsigned int nTF, unsigned int vTF, unsigned int nTR, unsigned int vTR);

	//! Sets parameters of the LE circle
	/*!
 	 * \param x1 - x coordinate of the first point of the LE arc
 	 * \param y1 - y coordinate of the first point of the LE arc
 	 * \param x2 - x coordinate of the second point of the LE arc
 	 * \param y2 - y coordinate of the second point of the LE arc
 	 * \param x3 - x coordinate of the third point of the LE arc
 	 * \param y3 - y coordinate of the third point of the LE arc
 	 * \param nCircle - number of verices that will be generated on the LE arc
 	 */
	void SetLEcircle(double x1, double y1, double x2, double y2, double x3, double y3, unsigned int nCircle=0);    
   

	//! Sets TE coordinates for top and bottom curves
	/*!
 	 * \param x - x coordinate of the TE
 	 * \param y - y coordinate of the TE
 	 * \param slope - slope of the TE
 	 */
    void SetTEpoint(double x, double y, double slope=0);

	//! Sets TE coordinates for bottom curve
	/*!
 	 * \param x - x coordinate of the TE bottom curve
 	 * \param y - y coordinate of the TE bottom curve
 	 * \param slope - slope of the TE
	 * \note TE of top and bottom curves may be different to create TE gap.
 	 */
    void SetTEpointB(double x, double y, double slope=0);

	//! Sets TE coordinates for top curve
	/*!
 	 * \param x - x coordinate of the TE top curve
 	 * \param y - y coordinate of the TE top curve
 	 * \param slope - slope of the TE
	 * \note TE of top and bottom curves may be different to create TE gap.
 	 */
    void SetTEpointT(double x, double y, double slope=0);

	//! Sets maximum thickness (top curve) coordinates
	/*!
 	 * \param x - x coordinate of the max thickness top curve
 	 * \param y - y coordinate of the max thickness top curve
 	 */
    void SetMaxTh(double x, double y);

	//! Sets minimum thickness (bottom curve) coordinates
	/*!
 	 * \param x - x coordinate of the min thickness top curve
 	 * \param y - y coordinate of the min thickness top curve
 	 */
	void SetMinTh(double x, double y);

	//! Generates curves Vertices 
    void InitAirfoilSplinePoints();

    
	//! Saves to file Poles data 
	/*!
 	 * \param airfoilFile - file to save the data
 	 */
    void PrintOutPoles(std::string airfoilFile);
	
	//! Saves to file Vertexes data 
	/*!
 	 * \param airfoilFile - file to save the data
 	 * \param airfoilName - name of the airfoil saved in the file
 	 */
	void PrintOutVertex(std::string airfoilFile, std::string airfoilName);

	private:

	void SetBezierPoints(double Fi, double dFi, double MinMax, unsigned int N, unsigned int refN, BEZIER <double> &Spline, double RefX);
    
	void SetLEpoint(double x, double y);
    void SetLEpointB(double x, double y);
    void SetLEpointT(double x, double y);
    
	void MakeVertexesSeq();
};

} // namespace ap

#endif
