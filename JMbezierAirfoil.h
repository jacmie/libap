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

class BEZIERAIRFOIL
{
	public:
	
	BEZIER Spline0, Spline1, Spline2, Spline3;
	
	BEZIERAIRFOIL();
	void Init(int vFront, int vRear);
	
	void FixPoints();
	void MaxTh(double x, double y);
	void MinTh(double x, double y);
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