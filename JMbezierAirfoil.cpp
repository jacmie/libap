#include "JMbezierAirfoil.h"

#ifdef WIN32
#include "JMconsole.h"
extern CONSOLE con;
#endif

using namespace std;

BEZIER_AIRFOIL::BEZIER_AIRFOIL()
{	
    nBR = 1;
    nBF = 1;
    nTF = 1;
    nTR = 1;
}

void BEZIER_AIRFOIL::Init2b(unsigned int nBF0, unsigned int vBF0)
{
    //nBR = 0;
    nBF = nBF0;
    nTF = nBF;
    //nTR = 0;

	Init4b(1, 0, nBF, vBF0, nTF, vBF0, 1, 0);
}

void BEZIER_AIRFOIL::Init2b(unsigned int nBF0, unsigned int vBF0, unsigned int nTF0, unsigned int vTF0)
{
    //nBR = 0;
    nBF = nBF0;
    nTF = nTF0;
    //nTR = 0;

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

	SplineBR.Init(nBR, vBR0);
	SplineBF.Init(nBF, vBF0);
	SplineTF.Init(nTF, vTF0);
	SplineTR.Init(nTR, vTR0);

    // All points z coordinates 0
    for(unsigned int p=0; p<SplineBR.P.size(); p++) SplineBR.P[p][2] = 0.0;
	for(unsigned int p=0; p<SplineBF.P.size(); p++) SplineBF.P[p][2] = 0.0;
	for(unsigned int p=0; p<SplineTF.P.size(); p++) SplineTF.P[p][2] = 0.0;
	for(unsigned int p=0; p<SplineTR.P.size(); p++) SplineTR.P[p][2] = 0.0;

    if(vBR0 == 0) nBR = 0; 
    if(vTR0 == 0) nTR = 0;

    clog << nBR << "\t" << nTR << endl;
}

void BEZIER_AIRFOIL::SetLEcircle(double x1, double y1, double x2, double y2, double x3, double y3, unsigned int nCircle)
{
	double A, B;
 
    nCirc = nCircle;
    clog << nCirc << endl;
    Circle(x1, y1, x2, y2, x3, y3, LEcircX, LEcircY, LEcircR);
    clog << LEcircX << "\t" << LEcircY << "\t" << LEcircR << endl;

    if(nCirc == 0)
    {
    	LinearFunction(x2, y2, LEcircX, LEcircY, A, B);	
        if(A == 0)
            sBF = sTF = 0;
        else
            sBF = sTF = -1/A;
        clog << A << "\t" << sBF << endl;
        SetLEpoint(x2, y2);
    }

    else
    {
        LinearFunction(x1, y1, LEcircX, LEcircY, A, B);	
        if(A == 0)
            sBF = 0;
        else
            sBF = -1/A;
        clog << A << "\t" << sBF << endl;
        SetLEpointB(x1, y1);

        LinearFunction(x3, y3, LEcircX, LEcircY, A, B);	
        if(A == 0)
            sTF = 0;
        else
            sTF = -1/A;
        clog << A << "\t" << sTF << endl;
        SetLEpointT(x1, y1);
    }
}

void BEZIER_AIRFOIL::SetLEpoint(double x, double y)
{
    SetLEpointB(x, y);
    SetLEpointT(x, y);
}

void BEZIER_AIRFOIL::SetLEpointB(double x, double y)
{
    SplineBF.P[nBF-1][0] = x;
    SplineBF.P[nBF-1][1] = y;
}

void BEZIER_AIRFOIL::SetLEpointT(double x, double y)
{
    SplineTF.P[0][0] = x;
    SplineTF.P[0][1] = y;
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
        SplineBR.P[0][0] = x;
        SplineBR.P[0][1] = y;
    }

    else
    {
        SplineBF.P[0][0] = x;
        SplineBF.P[0][1] = y;
    }

    sBR = slope;
}

void BEZIER_AIRFOIL::SetTEpointT(double x, double y, double slope)
{
    if(nBR != 0 && nTR != 0)
    {
        SplineTR.P[nTR-1][0] = x;
        SplineTR.P[nTR-1][1] = y;
    }

    else
    {
        SplineTF.P[nTF-1][0] = x;
        SplineTF.P[nTF-1][1] = y;
    }
    
    sTR = slope;
}

void BEZIER_AIRFOIL::SetMaxTh(double x, double y)
{	
    if(nTF != 0 && nTR != 0)
    {
	    SplineTF.P[nTF-1][0] = x;
	    SplineTR.P[0][0] = x;
	
	    SplineTF.P[nTF-1][1] = y;
	    SplineTR.P[0][1] = y;
    }

    MaxThX = x;
    MaxThY = y;
}

void BEZIER_AIRFOIL::SetMinTh(double x, double y)
{	
    if(nBF != 0 && nBR != 0)
    {
        SplineBR.P[nBR-1][0] = x;
	    SplineBF.P[0][0] = x;
	
    	SplineBR.P[nBR-1][1] = y;
    	SplineBF.P[0][1] = y;
    }

    MinThX = x;
    MinThY = y;
}

void BEZIER_AIRFOIL::FrontUpConvexityPoint(double x, double y)
{	
	SplineTF.P[1][0] = 0.0;
	SplineTF.P[1][1] = y;
}

void BEZIER_AIRFOIL::FrontDownConvexityPoint(double x, double y)
{	
	SplineBF.P[1][0] = x;
	SplineBF.P[1][1] = y;
}

void BEZIER_AIRFOIL::RearUpConvexityPoint(double x1, double y1, double x2, double y2)
{	
	SplineBR.P[1][0] = x1;
	SplineBR.P[1][1] = y1;
	
    SplineBR.P[2][0] = x2;
	SplineBR.P[2][1] = y2;
}

void BEZIER_AIRFOIL::RearDownConvexityPoint(double x1, double y1, double x2, double y2)
{	
	SplineTR.P[1][0] = x1;
	SplineTR.P[1][1] = y1;
	
    SplineTR.P[2][0] = x2;
    SplineTR.P[2][1] = y2;
	
	double A, B;
	LinearFunction(x1, y1, x2, y2, A, B);
	FrontDownConvexityPoint(0.0, B);
}

void BEZIER_AIRFOIL::ComputeFrontUpConvexityPoint()
{
	//double A, B;
	//LinearFunction(SplineBR.P[3][0], Spline0.P[3][1], Spline0.P[2][0], Spline0.P[2][1], A, B);
	//FrontUpConvexityPoint(0.0, B);
}

void BEZIER_AIRFOIL::ComputeFrontDownConvexityPoint()
{
	//double A, B;
	//LinearFunction(Spline3.P[0][0], Spline3.P[0][1], Spline3.P[1][0], Spline3.P[1][1], A, B);
	//FrontDownConvexityPoint(0.0, B);
}

void BEZIER_AIRFOIL::InitAirfoilSplinePoints()
{
	clog << "*** Init Spline Airfoils ***" << endl << endl;

    double A, B, TE_Fi, LE_Fi, dFi, Fi, x, y;

    if(nCirc != 0)
    {
        
    }

    clog << nBR << "\t" << nTR << endl;

    if(nBR == 0 || nTR == 0) //Single spline on Top/Bottom
    {
        clog << SplineBF.P[0][0] << "\t" << SplineBF.P[0][1] << "\t" << MinThX << "\t" << 0.0 << endl;

        LinearFunction(SplineBF.P[0][0], SplineBF.P[0][1], MinThX, 0.0, A, B);
        TE_Fi = atan(A);

        clog << SplineBF.P[nBF-1][0] << "\t" << SplineBF.P[nBF-1][1] << "\t" << MinThX << "\t" << 0.0 << endl;

        LinearFunction(SplineBF.P[nBF-1][0], SplineBF.P[nBF-1][1], MinThX, 0.0, A, B);
        LE_Fi = atan(A);

        clog << nBF << "\t" << TE_Fi*180/M_PI << "\t" << LE_Fi*180/M_PI << endl;

	    dFi = (M_PI + TE_Fi - LE_Fi)/(nBF-1);
    	Fi  = TE_Fi;
    
        clog << (M_PI + TE_Fi - LE_Fi)*180/M_PI << "\tdFi = " << dFi*180/M_PI << "\tFi = " << Fi*180/M_PI << endl;

        for(unsigned int i=1; i<nBF; i++)
    	{    	
            Fi -= dFi;
	
            x = SplineBF.P[0][0];
            y = SplineBF.P[0][1];

		    RotatePointRefRad(x, y, Fi, SplineBF.P[nBF-1][0] + 0.5*SplineBF.P[0][0], 0);
            
    		SplineBF.P[i][0] = x;
    		SplineBF.P[i][1] = y*(-MinThY)/(SplineBF.P[nBF-1][0] + 0.5*SplineBF.P[0][0]);

            clog << fixed << setprecision(1) << Fi*180/M_PI << setprecision(3) << "\t" << SplineBF.P[i][0] << "\t" << SplineBF.P[i][1] << endl; 		    
	    }
        
        if(sBF == 0)
            SplineBF.P[nBF-2][0] = SplineBF.P[nBF-1][0]; //x
        else
        {
            B = SplineBF.P[nBF-1][1] - sBF*SplineBF.P[nBF-1][0];
            SplineBF.P[nBF-2][1] = sBF*SplineBF.P[nBF-2][0] + B; //y
        }

        if(sBR != 0)
        {
            B = SplineBF.P[0][1] - sBR*SplineBF.P[0][0];
            SplineBF.P[1][1] = sBR*SplineBF.P[1][0] + B; //y
        }

        clog << endl;

        clog << SplineTF.P[0][0] << "\t" << SplineTF.P[0][1] << "\t" << MaxThX << "\t" << 0.0 << endl;

        LinearFunction(SplineTF.P[0][0], SplineTF.P[0][1], MaxThX, 0.0, A, B);
        LE_Fi = atan(A);

        clog << SplineTF.P[nTF-1][0] << "\t" << SplineTF.P[nTF-1][1] << "\t" << MaxThX << "\t" << 0.0 << endl;

        LinearFunction(SplineTF.P[nTF-1][0], SplineTF.P[nTF-1][1], MaxThX, 0.0, A, B);
        TE_Fi = atan(A);

        clog << nTF << "\t" << LE_Fi*180/M_PI << "\t" << TE_Fi*180/M_PI << endl;

	    dFi = (M_PI + LE_Fi - TE_Fi)/(nTF-1);
    	Fi  = M_PI + LE_Fi;
    
        clog << "dFi = " << dFi*180/M_PI << "\tFi = " << Fi*180/M_PI << endl;

        for(unsigned int i=1; i<nTF; i++)
    	{    	
            Fi -= dFi;
	
            x = SplineTF.P[0][0];
            y = SplineTF.P[0][1];

		    RotatePointRefRad(x, y, Fi, SplineTF.P[0][0] + 0.5*SplineTF.P[nTF-1][0], 0);
            
    		SplineTF.P[i][0] = x;
    		SplineTF.P[i][1] = y*MaxThY/(SplineTF.P[0][0] + 0.5*SplineTF.P[nTF-1][0]);

            clog << fixed << setprecision(1) << Fi*180/M_PI << setprecision(3) << "\t" << SplineTF.P[i][0] << "\t" << SplineTF.P[i][1] << endl; 		    
	    }
        
        if(sTF == 0)
            SplineTF.P[1][0] = SplineTF.P[0][0]; //x
        else
        {
            B = SplineTF.P[0][1] - sTF*SplineTF.P[0][0];
            SplineTF.P[1][1] = sTF*SplineTF.P[1][0] + B; //y
        }

        if(sTR != 0)
        {
            B = SplineTF.P[nTF-1][1] - sTR*SplineTF.P[nTF-1][0];
            SplineTF.P[nTF-2][1] = sTR*SplineTF.P[nTF-2][0] + B; //y
        }
	}

    else
    {
    }

	clog << "AAA" << endl;
}

void BEZIER_AIRFOIL::MakeVertexSeq()
{
	SplineBR.VertexSeq();
	SplineBF.VertexSeq();
	SplineTF.VertexSeq();
	SplineTR.VertexSeq();
}

void BEZIER_AIRFOIL::PrintOutPoints(string AirfoilFile)
{
	ofstream out(AirfoilFile.c_str());

	out << fixed << setprecision(6);
	
    if(nBR)
    {
	    for(unsigned int i=0; i<SplineBR.P.size(); i++)
            out << nBR << "\t" << SplineBR.P[i][0] << "    " << SplineBR.P[i][1] << endl;
        out << endl;
	}

	for(unsigned int i=0; i<SplineBF.P.size(); i++)
        out << SplineBF.P[i][0] << "    " << SplineBF.P[i][1] << endl;
    out << endl;
	
	for(unsigned int i=0; i<SplineTF.P.size(); i++)
        out << SplineTF.P[i][0] << "    " << SplineTF.P[i][1] << endl;
	out << endl;

    if(nTR)
    {
	    for(unsigned int i=0; i<SplineTR.P.size(); i++)
            out << SplineTR.P[i][0] << "    " << SplineTR.P[i][1] << endl;
	}

	out.close();
}

void BEZIER_AIRFOIL::PrintOutVertex(string AirfoilFile, string AirfoilName)
{
	MakeVertexSeq();
	
	ofstream out(AirfoilFile.c_str());

	out << AirfoilName << fixed << setprecision(6) << endl;
	
    if(nBR)
    {
    	for(unsigned int i=0; i<SplineBR.V.size()-1; i++)
            out << SplineBR.V[i][0] << "    " << SplineBR.V[i][1] << endl;
	}

	for(unsigned int i=0; i<SplineBF.V.size()-1; i++)
        out << SplineBF.V[i][0] << "    " << SplineBF.V[i][1] << endl;
	
	for(unsigned int i=0; i<SplineTF.V.size()-1; i++)
        out << SplineTF.V[i][0] << "    " << SplineTF.V[i][1] << endl;
	
    if(nTR)
    {
    	for(unsigned int i=0; i<SplineTR.V.size(); i++)
            out << SplineTR.V[i][0] << "    " << SplineTR.V[i][1] << endl;
    }
		
	out.close();
}
