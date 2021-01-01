#include "JMbezierAirfoil.h"

#ifdef WIN32
#include "JMconsole.h"
extern CONSOLE con;
#endif

using namespace std;

BEZIERAIRFOIL::BEZIERAIRFOIL()
{	
}

void BEZIERAIRFOIL::Init(int vFront, int vRear)
{
	Spline0.Init(4, vRear);
	Spline1.Init(3, vFront);
	Spline2.Init(3, vFront);
	Spline3.Init(4, vRear);
}

void BEZIERAIRFOIL::FixPoints()
{
	//=== X axis ===
	
	Spline0.P[0][0] = 1.0;
	Spline1.P[2][0] = 0.0;
	Spline2.P[0][0] = 0.0;
	Spline3.P[3][0] = 1.0;
	
	//=== Y axis ===
	
	Spline0.P[0][1] = 0.0;
	Spline1.P[2][1] = 0.0;
	Spline2.P[0][1] = 0.0;
	Spline3.P[3][1] = 0.0;
	
	//=== Z axis not used ===
	
	Spline0.P[0][2] = 0.0;
    Spline0.P[1][2] = 0.0;
    Spline0.P[2][2] = 0.0;
    Spline0.P[3][2] = 0.0;
	
	Spline1.P[0][2] = 0.0;
    Spline1.P[1][2] = 0.0;
    Spline1.P[2][2] = 0.0;
    
	Spline2.P[0][2] = 0.0;
    Spline2.P[1][2] = 0.0;
    Spline2.P[2][2] = 0.0;
    
	Spline3.P[0][2] = 0.0;
    Spline3.P[1][2] = 0.0;
    Spline3.P[2][2] = 0.0;
    Spline3.P[3][2] = 0.0;
}

void BEZIERAIRFOIL::MaxTh(double x, double y)
{	
	Spline0.P[3][0] = x;
	Spline1.P[0][0] = x;
	
	Spline0.P[3][1] = y;
	Spline1.P[0][1] = y;
}

void BEZIERAIRFOIL::MinTh(double x, double y)
{	
	Spline2.P[2][0] = x;
	Spline3.P[0][0] = x;
	
	Spline2.P[2][1] = y;
	Spline3.P[0][1] = y;
}

void BEZIERAIRFOIL::FrontUpConvexityPoint(double x, double y)
{	
	Spline1.P[1][0] = 0.0;
	Spline1.P[1][1] = y;
}

void BEZIERAIRFOIL::FrontDownConvexityPoint(double x, double y)
{	
	Spline2.P[1][0] = x;
	Spline2.P[1][1] = y;
}

void BEZIERAIRFOIL::RearUpConvexityPoint(double x1, double y1, double x2, double y2)
{	
	Spline0.P[1][0] = x1;
	Spline0.P[1][1] = y1;
	
    Spline0.P[2][0] = x2;
	Spline0.P[2][1] = y2;
}

void BEZIERAIRFOIL::RearDownConvexityPoint(double x1, double y1, double x2, double y2)
{	
	Spline3.P[1][0] = x1;
	Spline3.P[1][1] = y1;
	
    Spline3.P[2][0] = x2;
    Spline3.P[2][1] = y2;
	
	double A, B;
	LinearFunction(x1, y1, x2, y2, A, B);
	FrontDownConvexityPoint(0.0, B);
}

void BEZIERAIRFOIL::ComputeFrontUpConvexityPoint()
{
	double A, B;
	LinearFunction(Spline0.P[3][0], Spline0.P[3][1], Spline0.P[2][0], Spline0.P[2][1], A, B);
	FrontUpConvexityPoint(0.0, B);
}

void BEZIERAIRFOIL::ComputeFrontDownConvexityPoint()
{
	double A, B;
	LinearFunction(Spline3.P[0][0], Spline3.P[0][1], Spline3.P[1][0], Spline3.P[1][1], A, B);
	FrontDownConvexityPoint(0.0, B);
}

void BEZIERAIRFOIL::MakeVertexSeq()
{
	Spline0.VertexSeq();
	Spline1.VertexSeq();
	Spline2.VertexSeq();
	Spline3.VertexSeq();
}

void BEZIERAIRFOIL::PrintOutVertex(string AirfoilFile, string AirfoilName)
{
	MakeVertexSeq();
	
	ofstream out(AirfoilFile.c_str());

	out << AirfoilName << fixed << setprecision(6) << endl;
	
	for(int i=0; i<Spline0.u-1; i++)
        out << Spline0.V[i][0] << "    " << Spline0.V[i][1] << endl;
	
	for(int i=0; i<Spline1.u-1; i++)
        out << Spline1.V[i][0] << "    " << Spline1.V[i][1] << endl;
	
	for(int i=0; i<Spline2.u-1; i++)
        out << Spline2.V[i][0] << "    " << Spline2.V[i][1] << endl;
	
	for(int i=0; i<Spline3.u; i++)
        out << Spline3.V[i][0] << "    " << Spline3.V[i][1] << endl;
		
	out.close();
}
