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
	
    unsigned int nBR, nBF, nTF, nTR;
	BEZIER SplineBR; // Bottom Rear
    BEZIER SplineBF; // Bottom Front
    BEZIER SplineTF; // Top Front
    BEZIER SplineTR; // Top Rear
	
	BEZIER_AIRFOIL();
    void Init2b(unsigned int nBF0, unsigned int vBF0);
    void Init2b(unsigned int nBF0, unsigned int vBF0, unsigned int nTF0, unsigned int vTF0);
    void Init4b(unsigned int nBR0, unsigned int vBR0, unsigned int nBF0, unsigned int vBF0);
	void Init4b(unsigned int nBR0, unsigned int vBR0, unsigned int nBF0, unsigned int vBF0, unsigned int nTF0, unsigned int vTF0, unsigned int nTR0, unsigned int vTR0);

    void LEpointB(double x, double y, double slope);
    void LEpointT(double x, double y, double slope);
	
	int  MaxTh(double x, double y);
	int  MinTh(double x, double y);
    
    void FixPoints();

	void FrontUpConvexityPoint(double x, double y);
	void FrontDownConvexityPoint(double x, double y);
	void RearUpConvexityPoint(double x1, double y1, double x2, double y2);
	void RearDownConvexityPoint(double x1, double y1, double x2, double y2);
	void ComputeFrontUpConvexityPoint();
	void ComputeFrontDownConvexityPoint();
	void MakeVertexSeq();
	void PrintOutVertex(std::string AirfoilFile, std::string AirfoilName);
};

#endif
