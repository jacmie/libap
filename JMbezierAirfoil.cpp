#include "JMbezierAirfoil.h"

#ifdef WIN32
//#include "JMconsole.h"
//extern CONSOLE con;
#endif

BEZIER_AIRFOIL::BEZIER_AIRFOIL()
{	
    nBR = 1;
    nBF = 1;
    nTF = 1;
    nTR = 1;
}

void BEZIER_AIRFOIL::Init2b(unsigned int nBF0, unsigned int vBF0)
{
    nBF = nBF0;
    nTF = nBF;

	Init4b(1, 0, nBF, vBF0, nTF, vBF0, 1, 0);
}

void BEZIER_AIRFOIL::Init2b(unsigned int nBF0, unsigned int vBF0, unsigned int nTF0, unsigned int vTF0)
{
    nBF = nBF0;
    nTF = nTF0;

    Init4b(1, 0, nBF, vBF0, nTF, vTF0, 1, 0);
}

void BEZIER_AIRFOIL::Init4b(unsigned int nBR0, unsigned int vBR0, unsigned int nBF0, unsigned int vBF0)
{
    nBR = nBR0;
    nBF = nBF0;
    nTF = nBF;
    nTR = nBR;

    Init4b(nBR, vBR0, nBF, vBF0, nTF, vBF0, nTR, vBR0);
}

void BEZIER_AIRFOIL::Init4b(unsigned int nBR0, unsigned int vBR0, unsigned int nBF0, unsigned int vBF0, unsigned int nTF0, unsigned int vTF0, unsigned int nTR0, unsigned int vTR0)
{
    nBR = nBR0;
    nBF = nBF0;
    nTF = nTF0;
    nTR = nTR0;
    
	vBR = vBR0;
    vBF = vBF0;
    vTF = vTF0;
    vTR = vTR0;

	SplineBR.Init(nBR);
	SplineBF.Init(nBF);
	SplineTF.Init(nTF);
	SplineTR.Init(nTR);

    // All points z coordinates 0
    for(unsigned int p=0; p<SplineBR.P.size(); p++) SplineBR.P[p].z = 0.0;
	for(unsigned int p=0; p<SplineBF.P.size(); p++) SplineBF.P[p].z = 0.0;
	for(unsigned int p=0; p<SplineTF.P.size(); p++) SplineTF.P[p].z = 0.0;
	for(unsigned int p=0; p<SplineTR.P.size(); p++) SplineTR.P[p].z = 0.0;

    if(vBR0 == 0) nBR = 0; 
    if(vTR0 == 0) nTR = 0;
}

void BEZIER_AIRFOIL::SetLEcircle(double x1, double y1, double x2, double y2, double x3, double y3, unsigned int vCircle)
{
    vCirc = vCircle;
    Circle(x1, y1, x2, y2, x3, y3, LEcircX, LEcircY, LEcircR);

	double A, B;
    	
    if(vCirc == 0)
    {
		LinearFunction(x2, y2, LEcircX, LEcircY, A, B);	
        
		if(A == 0)
            sBF = sTF = 0;
        else
            sBF = sTF = -1/A;
        
		SetLEpoint(x2, y2);
    }

    else
    {
		SplineLE.Init(4);
    	for(unsigned int p=0; p<SplineLE.P.size(); p++) 
			SplineLE.P[p].z = 0.0;
       
		LinearFunction(x1, y1, LEcircX, LEcircY, A, B);	

		if(A == 0)
            sBF = 0;
        else
            sBF = -1/A;
       
		SetLEpointB(x1, y1);

        LinearFunction(x3, y3, LEcircX, LEcircY, A, B);	
        
		if(A == 0)
            sTF = 0;
        else
            sTF = -1/A;
        
		SetLEpointT(x3, y3);
    }
}

void BEZIER_AIRFOIL::SetLEpoint(double x, double y)
{
    SetLEpointB(x, y);
    SetLEpointT(x, y);
}

void BEZIER_AIRFOIL::SetLEpointB(double x, double y)
{
    SplineBF.P[nBF-1].x = x;
    SplineBF.P[nBF-1].y = y;
}

void BEZIER_AIRFOIL::SetLEpointT(double x, double y)
{
    SplineTF.P[0].x = x;
    SplineTF.P[0].y = y;
}

void BEZIER_AIRFOIL::SetTEpoint(double x, double y, double slope)
{
    SetTEpointB(x, y, slope);
    SetTEpointT(x, y, slope);
}

void BEZIER_AIRFOIL::SetTEpointB(double x, double y, double slope)
{
    if(nBR != 0 && nTR != 0)
    {
        SplineBR.P[0].x = x;
        SplineBR.P[0].y = y;
    }

    else
    {
        SplineBF.P[0].x = x;
        SplineBF.P[0].y = y;
    }

    sBR = slope;
}

void BEZIER_AIRFOIL::SetTEpointT(double x, double y, double slope)
{
    if(nBR != 0 && nTR != 0)
    {
        SplineTR.P[nTR-1].x = x;
        SplineTR.P[nTR-1].y = y;
    }

    else
    {
        SplineTF.P[nTF-1].x = x;
        SplineTF.P[nTF-1].y = y;
    }
    
    sTR = slope;
}

void BEZIER_AIRFOIL::SetMaxTh(double x, double y)
{	
    if(nTF != 0 && nTR != 0)
    {
	    SplineTF.P[nTF-1].x = x;
	    SplineTR.P[0].x = x;
	
	    SplineTF.P[nTF-1].y = y;
	    SplineTR.P[0].y = y;
    }

    MaxThX = x;
    MaxThY = y;
}

void BEZIER_AIRFOIL::SetMinTh(double x, double y)
{	
    if(nBF != 0 && nBR != 0)
    {
        SplineBR.P[nBR-1].x = x;
	    SplineBF.P[0].x = x;
	
    	SplineBR.P[nBR-1].y = y;
    	SplineBF.P[0].y = y;
    }

    MinThX = x;
    MinThY = y;
}

void BEZIER_AIRFOIL::InitAirfoilSplinePoints()
{
    double A, B, TE_Fi, LE_Fi, dFi, Fi, y;

    if(nBR == 0 || nTR == 0) //Single spline on Top/Bottom
    {
		// === Bottom surface ===
		std::clog << " === Bottom surface === " << std::endl;
		 
        LinearFunction(SplineBF.P[0].x, SplineBF.P[0].y, MinThX, 0.0, A, B);
        TE_Fi = atan(A);
        LinearFunction(SplineBF.P[nBF-1].x, SplineBF.P[nBF-1].y, MinThX, 0.0, A, B);
        LE_Fi = atan(A);
	    dFi   = (M_PI + TE_Fi - LE_Fi)/(nBF-1);
    	Fi    = 0;
		SetBezierPoints(Fi, dFi, MinThY, nBF, 0, SplineBF, SplineBF.P[nBF-1].x + 0.5*SplineBF.P[0].x);
		
		// --- LE/TE points correction from Slopes ---

        if(sBF == 0) //LE
            SplineBF.P[nBF-2].x = SplineBF.P[nBF-1].x; //x
        else
        {
            B = SplineBF.P[nBF-1].y - sBF*SplineBF.P[nBF-1].x;

			for(unsigned int i=1; i<nBF-1; i++)
			{
            	y = sBF*SplineBF.P[i].x + B;

				if(y > MinThY)
					SplineBF.P[i].y = y; //y
			}
        }
        
		if(sBR != 0) //TE
        {
            B = SplineBF.P[0].y - sBR*SplineBF.P[0].x;

			for(unsigned int i=1; i<2/*nBF-1*/; i++)
			{
            	y = sBR*SplineBF.P[i].x + B;

				if(y > MinThY)
					SplineBF.P[i].y = y; //y
			}
        }
		
		// === LE with Circle ===
    	if(vCirc != 0)
    	{
			double x2, y2, x3, y3;

			Arc2Bezier(SplineBF.P[nBF-1].x, SplineBF.P[nBF-1].y, x2, y2, x3, y3, SplineTF.P[0].x, SplineTF.P[0].y, LEcircX, LEcircY);
			
			SplineLE.P[0].x = SplineBF.P[nBF-1].x;
			SplineLE.P[0].y = SplineBF.P[nBF-1].y;
			
			SplineLE.P[1].x = x2;
			SplineLE.P[1].y = y2;
			
			SplineLE.P[2].x = x3;
			SplineLE.P[2].y = y3;
			
			SplineLE.P[3].x = SplineTF.P[0].x;
			SplineLE.P[3].y = SplineTF.P[0].y;
    	}
		
		// === Top surface ===
		std::clog << " === Top surface === " << std::endl;

        LinearFunction(SplineTF.P[0].x, SplineTF.P[0].y, MaxThX, 0.0, A, B);
        LE_Fi = atan(A);
        LinearFunction(SplineTF.P[nTF-1].x, SplineTF.P[nTF-1].y, MaxThX, 0.0, A, B);
        TE_Fi = atan(A);
	    dFi   = (M_PI + LE_Fi - TE_Fi)/(nTF-1);
    	Fi    = 0;
		SetBezierPoints(Fi, dFi, MaxThY, nTF, 0, SplineTF, SplineTF.P[0].x + 0.5*SplineTF.P[nTF-1].x);
		
		// --- LE/TE points correction from Slopes ---
        
        if(sTF == 0) //LE
            SplineTF.P[1].x = SplineTF.P[0].x; //x
        else
        {
            B = SplineTF.P[0].y - sTF*SplineTF.P[0].x;

			for(unsigned int i=1; i<nTF-1; i++)
			{
            	y = sTF*SplineTF.P[i].x + B;

				if(y < MaxThY)
					SplineTF.P[i].y = y; //y
			}
        }
        
		if(sTR != 0) //TE
        {
            B = SplineTF.P[nTF-1].y - sTR*SplineTF.P[nTF-1].x;

			for(unsigned int i=/*1*/nTF-2; i<nTF-1; i++)
			{
            	y = sTR*SplineTF.P[i].x + B;

				if(y > MinThY)
					SplineTF.P[i].y = y; //y
			}
        }
	}

    else
    {
		// === Bottom Rear surface ===
        LinearFunction(SplineBR.P[0].x, SplineBR.P[0].y, MinThX, 0.0, A, B);
        TE_Fi = atan(A);
	    dFi   = (0.5*M_PI + TE_Fi)/(nBR-1);
    	Fi    = 0;
		std::clog << dFi << "\t" << Fi*180/M_PI << std::endl;
		SetBezierPoints(Fi, dFi, MinThY, nBR, 0, SplineBR, MinThX);
		
		// === Bottom Front surface ===
        LinearFunction(SplineBF.P[nBF-1].x, SplineBF.P[nBF-1].y, MinThX, 0.0, A, B);
        LE_Fi = atan(A);
	    dFi   = (0.5*M_PI - LE_Fi)/(nBF-1);
    	Fi    = M_PI/2 - LE_Fi;
		std::clog << dFi << "\t" << Fi*180/M_PI << std::endl;
		SetBezierPoints(Fi, dFi, MinThY, nBF, nBF-1, SplineBF, MinThX);
		
		// --- LE/TE points correction from Slopes ---
        
		if(sBF == 0) //LE
            SplineBF.P[nBF-2].x = SplineBF.P[nBF-1].x; //x
        else
        {
            B = SplineBF.P[nBF-1].y - sBF*SplineBF.P[nBF-1].x;

			for(unsigned int i=2; i<nBF-1; i++)
			{
            	y = sBF*SplineBF.P[i].x + B;

				if(y > MinThY)
					SplineBF.P[i].y = y; //y
			}
        }

        if(sBR != 0) //TE
        {
            B = SplineBR.P[0].y - sBR*SplineBR.P[0].x;

			for(unsigned int i=1; i<2/*nBR-2*/; i++)
			{
            	y = sBR*SplineBR.P[i].x + B;

				if(y > MinThY)
					SplineBR.P[i].y = y; //y
			}
        }

		// === LE with Circle ===
    	if(vCirc != 0)
    	{
			double x2, y2, x3, y3;

			Arc2Bezier(SplineBF.P[nBF-1].x, SplineBF.P[nBF-1].y, x2, y2, x3, y3, SplineTF.P[0].x, SplineTF.P[0].y, LEcircX, LEcircY);
			
			SplineLE.P[0].x = SplineBF.P[nBF-1].x;
			SplineLE.P[0].y = SplineBF.P[nBF-1].y;
			
			SplineLE.P[1].x = x2;
			SplineLE.P[1].y = y2;
			
			SplineLE.P[2].x = x3;
			SplineLE.P[2].y = y3;
			
			SplineLE.P[3].x = SplineTF.P[0].x;
			SplineLE.P[3].y = SplineTF.P[0].y;
    	}

		// === Top Front surface ===
        LinearFunction(SplineTF.P[0].x, SplineTF.P[0].y, MaxThX, 0.0, A, B);
        LE_Fi = atan(A);
	    dFi   = (0.5*M_PI + LE_Fi)/(nTF-1);
    	Fi    = 0;
		std::clog << dFi << "\t" << Fi << std::endl;
		SetBezierPoints(Fi, dFi, MaxThY, nTF, 0, SplineTF, MaxThX);
		
		// === Top Rear surface ===
        LinearFunction(SplineTR.P[nTR-1].x, SplineTR.P[nTR-1].y, MaxThX, 0.0, A, B);
        TE_Fi = atan(A);
	    dFi   = (0.5*M_PI - TE_Fi)/(nTR-1);
    	Fi    = 0.5*M_PI - TE_Fi;
		std::clog << dFi << "\t" << Fi*180/M_PI << std::endl;
		SetBezierPoints(Fi, dFi, MaxThY, nTR, nTR-1, SplineTR, MaxThX);
		
		// --- LE/TE points correction from Slopes ---
        
		if(sTF == 0) //LE
            SplineTF.P[1].x = SplineTF.P[0].x; //x
        else
        {
            B = SplineTF.P[0].y - sTF*SplineTF.P[0].x;

			for(unsigned int i=1; i<nTF-2; i++)
			{
            	y = sTF*SplineTF.P[i].x + B;

				if(y < MaxThY)
					SplineTF.P[i].y = y; //y
			}
        }

        if(sTR != 0) //TE
        {
            B = SplineTR.P[nTR-1].y - sTR*SplineTR.P[nTR-1].x;

			for(unsigned int i=/*1*/nTR-2; i<nTR-1; i++)
			{
            	y = sTR*SplineTR.P[i].x + B;

				if(y < MaxThY)
					SplineTR.P[i].y = y; //y
			}
        }
    }
}

void BEZIER_AIRFOIL::SetBezierPoints(double Fi, double dFi, double MinMax, unsigned int N, unsigned int refN, BEZIER <double> &Spline, double RefX)
{
	double x, y;
	std::clog << std::endl;
	for(unsigned int i=1; i<N-1; i++)
	{    	
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

void BEZIER_AIRFOIL::MakeVertexesSeq()
{
	SplineBR.VertexesSeq(vBR);
	SplineBF.VertexesSeq(vBF);
	SplineTF.VertexesSeq(vTF);
	SplineTR.VertexesSeq(vTR);
    
	if(vCirc != 0)
		SplineLE.VertexesSeq(vCirc);
}

void BEZIER_AIRFOIL::PrintOutPoints(std::string AirfoilFile)
{
	std::ofstream out(AirfoilFile.c_str());

	out << std::fixed << std::setprecision(6);
	
    if(nBR)
    {
    	SplineBR.PrintPointsFormat(0, 0, 12, 2);
    	SplineBR.PrintPoints(out);
        out << std::endl;
	}

    SplineBF.PrintPointsFormat(0, 0, 12, 2);
    SplineBF.PrintPoints(out);
    out << std::endl;
    
	if(vCirc != 0)
	{
		SplineLE.PrintPointsFormat(0, 0, 12, 2);
    	SplineLE.PrintPoints(out);
		out << std::endl;
	}

	SplineTF.PrintPointsFormat(0, 0, 12, 2);
    SplineTF.PrintPoints(out);
	out << std::endl;

    if(nTR)
    {
		SplineTR.PrintPointsFormat(0, 0, 12, 2);
    	SplineTR.PrintPoints(out);
	}

	out.close();
}

void BEZIER_AIRFOIL::PrintOutVertex(std::string AirfoilFile, std::string AirfoilName)
{
	MakeVertexesSeq();
	
	std::ofstream out(AirfoilFile.c_str());

	out << AirfoilName << std::fixed << std::setprecision(6) << std::endl;
	
    if(nBR)
    {
    	SplineBR.PrintVertexesFormat(0, 0, 12, 2);
    	SplineBR.PrintVertexes(out);
	}

	SplineBF.PrintVertexesFormat(0, 0, 12, 2);
    SplineBF.PrintVertexes(out);
	
	if(vCirc != 0)
	{
		SplineLE.PrintVertexesFormat(0, 0, 12, 2);
    	SplineLE.PrintVertexes(out);
	}
	
	SplineTF.PrintVertexesFormat(0, 0, 12, 2);
    SplineTF.PrintVertexes(out);

    if(nTR)
    {
		SplineTR.PrintVertexesFormat(0, 0, 12, 2);
    	SplineTR.PrintVertexes(out);
    }
	
	out.close();
}
