#ifndef _SPLINE_AIRFOIL_H_
#define _SPLINE_AIRFOIL_H_

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <FL/fl_ask.H>

#include "JMmath.h"
#include "JMbezier.h"

class BEZIER_AIRFOIL
{
	public:
	
    unsigned int nBR, nBF, nTF, nTR, nCirc;
    double LEcircX, LEcircY, LEcircR;
    double sBR, sBF, sTF, sTR; // slope tan(A)
    double MinThX, MinThY, MaxThX, MaxThY;
	BEZIER <double> SplineBR; // Bottom Rear
    BEZIER <double> SplineBF; // Bottom Front
    BEZIER <double> SplineTF; // Top Front
    BEZIER <double> SplineTR; // Top Rear
	
	BEZIER_AIRFOIL();
    void Init2b(unsigned int nBF0, unsigned int vBF0);
    void Init2b(unsigned int nBF0, unsigned int vBF0, unsigned int nTF0, unsigned int vTF0);
    void Init4b(unsigned int nBR0, unsigned int vBR0, unsigned int nBF0, unsigned int vBF0);
	void Init4b(unsigned int nBR0, unsigned int vBR0, unsigned int nBF0, unsigned int vBF0, unsigned int nTF0, unsigned int vTF0, unsigned int nTR0, unsigned int vTR0);

	void SetLEcircle(double x1, double y1, double x2, double y2, double x3, double y3, unsigned int nCircle=0);    
    void SetLEpoint(double x, double y);
    void SetLEpointB(double x, double y);
    void SetLEpointT(double x, double y);
    
    void SetTEpoint(double x, double y, double slope=0);
    void SetTEpointB(double x, double y, double slope=0);
    void SetTEpointT(double x, double y, double slope=0);

    void SetMaxTh(double x, double y);
	void SetMinTh(double x, double y);

    void InitAirfoilSplinePoints();

    void FixPoints();

	void FrontUpConvexityPoint(double x, double y);
	void FrontDownConvexityPoint(double x, double y);
	void RearUpConvexityPoint(double x1, double y1, double x2, double y2);
	void RearDownConvexityPoint(double x1, double y1, double x2, double y2);
	void ComputeFrontUpConvexityPoint();
	void ComputeFrontDownConvexityPoint();
	void MakeVertexesSeq();
    
    void PrintOutPoints(string AirfoilFile);
	void PrintOutVertex(std::string AirfoilFile, std::string AirfoilName);
};

#endif
