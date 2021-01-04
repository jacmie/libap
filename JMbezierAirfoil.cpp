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
    nBR = 0;
    nBF = nBF0;
    nTF = nBF;
    nTR = 0;

	Init4b(1, 0, nBF, vBF0, nTF, vBF0, 1, 0);
}

void BEZIER_AIRFOIL::Init2b(unsigned int nBF0, unsigned int vBF0, unsigned int nTF0, unsigned int vTF0)
{
    nBR = 0;
    nBF = nBF0;
    nTF = nTF0;
    nTR = 0;

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
}

void LEpointB(double x, double y, double slope)
{
}
//void LEpointT(double x, double y, double slope);
//void TEpointB(double x, double y, double slope);
//void TEpointT(double x, double y, double slope);
//LEcircle....

void BEZIER_AIRFOIL::FixPoints()
{
	//=== X axis ===
	/*
    if(nBR == 0)
	Spline0.P[0][0] = 1.0;
	Spline1.P[2][0] = 0.0;
	Spline2.P[0][0] = 0.0;
	Spline3.P[3][0] = 1.0;
	
	//=== Y axis ===
	
	Spline0.P[0][1] = 0.0;
	Spline1.P[2][1] = 0.0;
	Spline2.P[0][1] = 0.0;
	Spline3.P[3][1] = 0.0;
	*/
	//=== Z axis not used ===
	
    for(unsigned int p=0; p<SplineBR.P.size(); p++) SplineBR.P[p][2] = 0.0;
	for(unsigned int p=0; p<SplineBF.P.size(); p++) SplineBF.P[p][2] = 0.0;
	for(unsigned int p=0; p<SplineTF.P.size(); p++) SplineTF.P[p][2] = 0.0;
	for(unsigned int p=0; p<SplineTR.P.size(); p++) SplineTR.P[p][2] = 0.0;
}

int BEZIER_AIRFOIL::MaxTh(double x, double y)
{	
    if(nTR != 0)
    {
	    SplineTF.P[nTR][0] = x;
	    SplineTR.P[0][0] = x;
	
	    SplineTF.P[nTR][1] = y;
	    SplineTR.P[0][1] = y;
    }

    else
        return 1;

    return 0;
}

int BEZIER_AIRFOIL::MinTh(double x, double y)
{	
    if(nBR != 0)
    {
        SplineBR.P[nBR][0] = x;
	    SplineBF.P[0][0] = x;
	
    	SplineBR.P[nBR][1] = y;
    	SplineBF.P[0][1] = y;
    }

    else
        return 1;

    return 0;
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
	double A, B;
	//LinearFunction(SplineBR.P[3][0], Spline0.P[3][1], Spline0.P[2][0], Spline0.P[2][1], A, B);
	FrontUpConvexityPoint(0.0, B);
}

void BEZIER_AIRFOIL::ComputeFrontDownConvexityPoint()
{
	double A, B;
	//LinearFunction(Spline3.P[0][0], Spline3.P[0][1], Spline3.P[1][0], Spline3.P[1][1], A, B);
	FrontDownConvexityPoint(0.0, B);
}
/*
void IV_FIT_AIRFOIL::InitSplineAirfoils(int pUp, int vUp, int pDown, int vDown)
{
	clog << "*** Init Spline Airfoils ***" << endl;

   	SplineUp.Init(pUp, vUp);
	SplineDown.Init(pDown, vDown);

	double dFiUp = (M_PI)/(pUp-1);
	double FiUp  = M_PI + dFiUp;

	clog << fixed << setprecision(3) << endl;

	for(int i=0; i<pUp; i++)
	{
		FiUp -= dFiUp;
		
		SplineUp.P[i][0] = 0.5*(1*cos(FiUp)+1);
		SplineUp.P[i][1] = 0.06*sin(FiUp);
		SplineUp.P[i][2] = 0;

		//clog << FiUp << "\t" << 0.5*(1*cos(FiUp)+1) << "\t" << 0.12*sin(FiUp) << endl;
		clog << FiUp << "\t" << SplineUp.P[i][0] << "\t" << SplineUp.P[i][1] << endl;
	}
	
	clog << endl;
	
	double dFiDown = (M_PI)/(pDown-1);
	double FiDown  = M_PI + dFiDown;

	clog << fixed << setprecision(3) << endl;

	for(int i=0; i<pDown; i++)
	{
		FiDown -= dFiDown;
		
		SplineDown.P[i][0] = 0.5*(1*cos(FiDown)+1);
		SplineDown.P[i][1] = -0.06*sin(FiDown);
		SplineDown.P[i][2] = 0;

		//clog << FiDownUp << "\t" << 0.5*(1*cos(FiDownUp)+1) << "\t" << 0.12*sin(FiDownUp) << endl;
		clog << FiDown << "\t" << SplineDown.P[i][0] << "\t" << SplineDown.P[i][1] << endl;
	}
	
	clog << endl;
}
*/
void BEZIER_AIRFOIL::MakeVertexSeq()
{
	SplineBR.VertexSeq();
	SplineBF.VertexSeq();
	SplineTF.VertexSeq();
	SplineTR.VertexSeq();
}

void BEZIER_AIRFOIL::PrintOutVertex(string AirfoilFile, string AirfoilName)
{
	MakeVertexSeq();
	
	ofstream out(AirfoilFile.c_str());

	out << AirfoilName << fixed << setprecision(6) << endl;
	
	for(unsigned int i=0; i<SplineBR.u-1; i++)
        out << SplineBR.V[i][0] << "    " << SplineBR.V[i][1] << endl;
	
	for(unsigned int i=0; i<SplineBF.u-1; i++)
        out << SplineBF.V[i][0] << "    " << SplineBF.V[i][1] << endl;
	
	for(unsigned int i=0; i<SplineTF.u-1; i++)
        out << SplineTF.V[i][0] << "    " << SplineTF.V[i][1] << endl;
	
	for(unsigned int i=0; i<SplineTR.u; i++)
        out << SplineTR.V[i][0] << "    " << SplineTR.V[i][1] << endl;
		
	out.close();
}
