#include <cmath>
#include <iostream>
#include <fstream>

#include "ap_basicMath.h"

#include "ap_bezierAirfoil.h"

namespace ap {

void BEZIER_AIRFOIL::Init2b(unsigned int n, unsigned int v) {
    nBF_ = n;
    nTF_ = nBF_;

	Init4b(1, 0, nBF_, v, nTF_, v, 1, 0);
}

void BEZIER_AIRFOIL::Init2b(unsigned int nB, unsigned int vB, unsigned int nT, unsigned int vT) {
    nBF_ = nB;
    nTF_ = nT;

    Init4b(1, 0, nBF_, vB, nTF_, vT, 1, 0);
}

void BEZIER_AIRFOIL::Init4b(unsigned int nR, unsigned int vR, unsigned int nF, unsigned int vF) {
    nBR_ = nR;
    nBF_ = nF;
    nTF_ = nBF_;
    nTR_ = nBR_;

    Init4b(nBR_, vR, nBF_, vF, nTF_, vF, nTR_, vR);
}

void BEZIER_AIRFOIL::Init4b(unsigned int nBR, unsigned int vBR, unsigned int nBF, unsigned int vBF, unsigned int nTF, unsigned int vTF, unsigned int nTR, unsigned int vTR) {
    nBR_ = nBR;
    nBF_ = nBF;
    nTF_ = nTF;
    nTR_ = nTR;
       
	vBR_ = vBR;
    vBF_ = vBF;
    vTF_ = vTF;
    vTR_ = vTR;

	splineBR.Init(nBR_);
	splineBF.Init(nBF_);
	splineTF.Init(nTF_);
	splineTR.Init(nTR_);

    // All points z coordinates 0
    for(unsigned int p=0; p<splineBR.P.size(); p++) splineBR.P[p].z = 0.0;
	for(unsigned int p=0; p<splineBF.P.size(); p++) splineBF.P[p].z = 0.0;
	for(unsigned int p=0; p<splineTF.P.size(); p++) splineTF.P[p].z = 0.0;
	for(unsigned int p=0; p<splineTR.P.size(); p++) splineTR.P[p].z = 0.0;

    if(vBR == 0) nBR_ = 0; 
    if(vTR == 0) nTR_ = 0;
}

void BEZIER_AIRFOIL::SetLEcircle(double x1, double y1, double x2, double y2, double x3, double y3, unsigned int vCircle) {
    vCirc_ = vCircle;
    Circle(x1, y1, x2, y2, x3, y3, LEcircX_, LEcircY_, LEcircR_);

	double A, B;
    	
    if(vCirc_ == 0) {
		LinearFunction(x2, y2, LEcircX_, LEcircY_, A, B);	
        
		if(A == 0) 	sBF_ = sTF_ = 0;
        else		sBF_ = sTF_ = -1/A;
        
		SetLEpoint(x2, y2);
    }

    else {
		splineLE.Init(4);
    	for(unsigned int p=0; p<splineLE.P.size(); p++) 
			splineLE.P[p].z = 0.0;
       
		LinearFunction(x1, y1, LEcircX_, LEcircY_, A, B);	

		if(A == 0)	sBF_ = 0;
        else        sBF_ = -1/A;
       
		SetLEpointB(x1, y1);

        LinearFunction(x3, y3, LEcircX_, LEcircY_, A, B);	
        
		if(A == 0)	sTF_ = 0;
        else        sTF_ = -1/A;
        
		SetLEpointT(x3, y3);
    }
}

void BEZIER_AIRFOIL::SetLEpoint(double x, double y) {
    SetLEpointB(x, y);
    SetLEpointT(x, y);
}

void BEZIER_AIRFOIL::SetLEpointB(double x, double y) {
    splineBF.P[nBF_-1].x = x;
    splineBF.P[nBF_-1].y = y;
}

void BEZIER_AIRFOIL::SetLEpointT(double x, double y) {
    splineTF.P[0].x = x;
    splineTF.P[0].y = y;
}

void BEZIER_AIRFOIL::SetTEpoint(double x, double y, double slope) {
    SetTEpointB(x, y, slope);
    SetTEpointT(x, y, slope);
}

void BEZIER_AIRFOIL::SetTEpointB(double x, double y, double slope) {
    if(nBR_ != 0 && nTR_ != 0) {
        splineBR.P[0].x = x;
        splineBR.P[0].y = y;
    }

    else {
        splineBF.P[0].x = x;
        splineBF.P[0].y = y;
    }

    sBR_ = slope;
}

void BEZIER_AIRFOIL::SetTEpointT(double x, double y, double slope)
{
    if(nBR_ != 0 && nTR_ != 0) {
        splineTR.P[nTR_-1].x = x;
        splineTR.P[nTR_-1].y = y;
    }

    else {
        splineTF.P[nTF_-1].x = x;
        splineTF.P[nTF_-1].y = y;
    }
    
    sTR_ = slope;
}

void BEZIER_AIRFOIL::SetMaxTh(double x, double y)
{	
    if(nTF_ != 0 && nTR_ != 0) {
	    splineTF.P[nTF_-1].x = x;
	    splineTR.P[0].x = x;
	
	    splineTF.P[nTF_-1].y = y;
	    splineTR.P[0].y = y;
    }

    maxThX_ = x;
    maxThY_ = y;
}

void BEZIER_AIRFOIL::SetMinTh(double x, double y)
{	
    if(nBF_ != 0 && nBR_ != 0) {
        splineBR.P[nBR_-1].x = x;
	    splineBF.P[0].x = x;
	
    	splineBR.P[nBR_-1].y = y;
    	splineBF.P[0].y = y;
    }

    minThX_ = x;
    minThY_ = y;
}

void BEZIER_AIRFOIL::InitAirfoilSplinePoints()
{
    double A, B, TE_Fi, LE_Fi, dFi, Fi, y;

	if(nBR_ == 0 || nTR_ == 0) { //Single spline on Top/Bottom
		// === Bottom surface ===
		std::clog << " === Bottom surface === " << std::endl;
		 
        LinearFunction(splineBF.P[0].x, splineBF.P[0].y, minThX_, 0.0, A, B);
        TE_Fi = atan(A);
        LinearFunction(splineBF.P[nBF_-1].x, splineBF.P[nBF_-1].y, minThX_, 0.0, A, B);
        LE_Fi = atan(A);
	    dFi   = (M_PI + TE_Fi - LE_Fi)/(nBF_-1);
    	Fi    = 0;
		SetBezierPoints(Fi, dFi, minThY_, nBF_, 0, splineBF, splineBF.P[nBF_-1].x + 0.5*splineBF.P[0].x);
		
		// --- LE/TE points correction from Slopes ---

        if(sBF_ == 0) splineBF.P[nBF_-2].x = splineBF.P[nBF_-1].x; // LE x
        else {
            B = splineBF.P[nBF_-1].y - sBF_*splineBF.P[nBF_-1].x;

			for(unsigned int i=1; i<nBF_-1; i++) {
            	y = sBF_*splineBF.P[i].x + B;

				if(y > minThY_)	splineBF.P[i].y = y; //y
			}
        }
        
		if(sBR_ != 0) { // TE
            B = splineBF.P[0].y - sBR_*splineBF.P[0].x;

			for(unsigned int i=1; i<2/*nBF-1*/; i++) {
            	y = sBR_*splineBF.P[i].x + B;

				if(y > minThY_)	splineBF.P[i].y = y; //y
			}
        }
		
		// === LE with Circle ===
    	if(vCirc_ != 0) {
			double x2, y2, x3, y3;

			Arc2Bezier(splineBF.P[nBF_-1].x, splineBF.P[nBF_-1].y, x2, y2, x3, y3, splineTF.P[0].x, splineTF.P[0].y, LEcircX_, LEcircY_);
			
			splineLE.P[0].x = splineBF.P[nBF_-1].x;
			splineLE.P[0].y = splineBF.P[nBF_-1].y;
			
			splineLE.P[1].x = x2;
			splineLE.P[1].y = y2;
			
			splineLE.P[2].x = x3;
			splineLE.P[2].y = y3;
			
			splineLE.P[3].x = splineTF.P[0].x;
			splineLE.P[3].y = splineTF.P[0].y;
    	}
		
		// === Top surface ===
		std::clog << " === Top surface === " << std::endl;

        LinearFunction(splineTF.P[0].x, splineTF.P[0].y, maxThX_, 0.0, A, B);
        LE_Fi = atan(A);
        LinearFunction(splineTF.P[nTF_-1].x, splineTF.P[nTF_-1].y, maxThX_, 0.0, A, B);
        TE_Fi = atan(A);
	    dFi   = (M_PI + LE_Fi - TE_Fi)/(nTF_-1);
    	Fi    = 0;
		SetBezierPoints(Fi, dFi, maxThY_, nTF_, 0, splineTF, splineTF.P[0].x + 0.5*splineTF.P[nTF_-1].x);
		
		// --- LE/TE points correction from Slopes ---
        
        if(sTF_ == 0) splineTF.P[1].x = splineTF.P[0].x; // LE x
        else {
            B = splineTF.P[0].y - sTF_*splineTF.P[0].x;

			for(unsigned int i=1; i<nTF_-1; i++) {
            	y = sTF_*splineTF.P[i].x + B;

				if(y < maxThY_)
					splineTF.P[i].y = y; //y
			}
        }
        
		if(sTR_ != 0) { //TE
            B = splineTF.P[nTF_-1].y - sTR_*splineTF.P[nTF_-1].x;

			for(unsigned int i=/*1*/nTF_-2; i<nTF_-1; i++) {
            	y = sTR_*splineTF.P[i].x + B;

				if(y > minThY_) splineTF.P[i].y = y; //y
			}
        }
	}

    else {
		// === Bottom Rear surface ===
        LinearFunction(splineBR.P[0].x, splineBR.P[0].y, minThX_, 0.0, A, B);
        TE_Fi = atan(A);
	    dFi   = (0.5*M_PI + TE_Fi)/(nBR_-1);
    	Fi    = 0;
		std::clog << dFi << "\t" << Fi*180/M_PI << std::endl;
		SetBezierPoints(Fi, dFi, minThY_, nBR_, 0, splineBR, minThX_);
		
		// === Bottom Front surface ===
        LinearFunction(splineBF.P[nBF_-1].x, splineBF.P[nBF_-1].y, minThX_, 0.0, A, B);
        LE_Fi = atan(A);
	    dFi   = (0.5*M_PI - LE_Fi)/(nBF_-1);
    	Fi    = M_PI/2 - LE_Fi;
		std::clog << dFi << "\t" << Fi*180/M_PI << std::endl;
		SetBezierPoints(Fi, dFi, minThY_, nBF_, nBF_-1, splineBF, minThX_);
		
		// --- LE/TE points correction from Slopes ---
        
		if(sBF_ == 0) splineBF.P[nBF_-2].x = splineBF.P[nBF_-1].x; // LE x
        else {
            B = splineBF.P[nBF_-1].y - sBF_*splineBF.P[nBF_-1].x;

			for(unsigned int i=2; i<nBF_-1; i++) {
            	y = sBF_*splineBF.P[i].x + B;

				if(y > minThY_)	splineBF.P[i].y = y; //y
			}
        }

        if(sBR_ != 0) { //TE
            B = splineBR.P[0].y - sBR_*splineBR.P[0].x;

			for(unsigned int i=1; i<2/*nBR-2*/; i++) {
            	y = sBR_*splineBR.P[i].x + B;

				if(y > minThY_)	splineBR.P[i].y = y; //y
			}
        }

		// === LE with Circle ===
    	if(vCirc_ != 0) {
			double x2, y2, x3, y3;

			Arc2Bezier(splineBF.P[nBF_-1].x, splineBF.P[nBF_-1].y, x2, y2, x3, y3, splineTF.P[0].x, splineTF.P[0].y, LEcircX_, LEcircY_);
			
			splineLE.P[0].x = splineBF.P[nBF_-1].x;
			splineLE.P[0].y = splineBF.P[nBF_-1].y;
			
			splineLE.P[1].x = x2;
			splineLE.P[1].y = y2;
			
			splineLE.P[2].x = x3;
			splineLE.P[2].y = y3;
			
			splineLE.P[3].x = splineTF.P[0].x;
			splineLE.P[3].y = splineTF.P[0].y;
    	}

		// === Top Front surface ===
        LinearFunction(splineTF.P[0].x, splineTF.P[0].y, maxThX_, 0.0, A, B);
        LE_Fi = atan(A);
	    dFi   = (0.5*M_PI + LE_Fi)/(nTF_-1);
    	Fi    = 0;
		std::clog << dFi << "\t" << Fi << std::endl;
		SetBezierPoints(Fi, dFi, maxThY_, nTF_, 0, splineTF, maxThX_);
		
		// === Top Rear surface ===
        LinearFunction(splineTR.P[nTR_-1].x, splineTR.P[nTR_-1].y, maxThX_, 0.0, A, B);
        TE_Fi = atan(A);
	    dFi   = (0.5*M_PI - TE_Fi)/(nTR_-1);
    	Fi    = 0.5*M_PI - TE_Fi;
		std::clog << dFi << "\t" << Fi*180/M_PI << std::endl;
		SetBezierPoints(Fi, dFi, maxThY_, nTR_, nTR_-1, splineTR, maxThX_);
		
		// --- LE/TE points correction from Slopes ---
        
		if(sTF_ == 0) splineTF.P[1].x = splineTF.P[0].x; // LE x
        else {
            B = splineTF.P[0].y - sTF_*splineTF.P[0].x;

			for(unsigned int i=1; i<nTF_-2; i++) {
            	y = sTF_*splineTF.P[i].x + B;

				if(y < maxThY_)	splineTF.P[i].y = y; //y
			}
        }

        if(sTR_ != 0) { //TE
            B = splineTR.P[nTR_-1].y - sTR_*splineTR.P[nTR_-1].x;

			for(unsigned int i=/*1*/nTR_-2; i<nTR_-1; i++) {
            	y = sTR_*splineTR.P[i].x + B;

				if(y < maxThY_)	splineTR.P[i].y = y; //y
			}
        }
    }
}

void BEZIER_AIRFOIL::SetBezierPoints(double Fi, double dFi, double MinMax, unsigned int N, unsigned int refN, BEZIER <double> &Spline, double RefX) {
	double x, y;
	std::clog << std::endl;
	for(unsigned int i=1; i<N-1; i++) {    	
        Fi -= dFi;

        x = Spline.P[refN].x;
        y = Spline.P[refN].y;

		std::clog << x << "\t" << y << "\t";

	    RotatePointRefRad(Fi, RefX, 0, x, y);
	
		std::clog << Fi*180/M_PI << "\t" << RefX << "\t" << x << "\t" << y << std::endl;
        
		Spline.P[i].x = x;
		Spline.P[i].y = MinMax;
    }
	std::clog << std::endl;
}

void BEZIER_AIRFOIL::MakeVertexesSeq() {
	splineBR.VertexesSeq(vBR_);
	splineBF.VertexesSeq(vBF_);
	splineTF.VertexesSeq(vTF_);
	splineTR.VertexesSeq(vTR_);
    
	if(vCirc_ != 0) splineLE.VertexesSeq(vCirc_);
}

void BEZIER_AIRFOIL::PrintOutPoles(std::string airfoilFile) {
	std::ofstream out(airfoilFile);
	out << std::fixed << std::setprecision(6);
	
    if(nBR_) {
    	splineBR.PrintPolesFormat(0, 0, 12, 2);
    	splineBR.PrintPoles(out);
        out << std::endl;
	}

    splineBF.PrintPolesFormat(0, 0, 12, 2);
    splineBF.PrintPoles(out);
    out << std::endl;
    
	if(vCirc_ != 0) {
		splineLE.PrintPolesFormat(0, 0, 12, 2);
    	splineLE.PrintPoles(out);
		out << std::endl;
	}

	splineTF.PrintPolesFormat(0, 0, 12, 2);
    splineTF.PrintPoles(out);
	out << std::endl;

    if(nTR_) {
		splineTR.PrintPolesFormat(0, 0, 12, 2);
    	splineTR.PrintPoles(out);
	}

	out.close();
}

void BEZIER_AIRFOIL::PrintOutVertex(std::string airfoilFile, std::string airfoilName) {
	MakeVertexesSeq();
	
	std::ofstream out(airfoilFile);

	out << airfoilName << std::fixed << std::setprecision(6) << std::endl;
	
    if(nBR_) {
    	splineBR.PrintVertexesFormat(0, 0, 12, 2);
    	splineBR.PrintVertexes(out);
	}

	splineBF.PrintVertexesFormat(0, 0, 12, 2);
    splineBF.PrintVertexes(out);
	
	if(vCirc_ != 0) {
		splineLE.PrintVertexesFormat(0, 0, 12, 2);
    	splineLE.PrintVertexes(out);
	}
	
	splineTF.PrintVertexesFormat(0, 0, 12, 2);
    splineTF.PrintVertexes(out);

    if(nTR_) {
		splineTR.PrintVertexesFormat(0, 0, 12, 2);
    	splineTR.PrintVertexes(out);
    }
	
	out.close();
}

} // namespace ap
