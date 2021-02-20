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

	SplineBR.Init(nBR, vBR0);
	SplineBF.Init(nBF, vBF0);
	SplineTF.Init(nTF, vTF0);
	SplineTR.Init(nTR, vTR0);

    // All points z coordinates 0
    for(unsigned int p=0; p<SplineBR.P.size(); p++) SplineBR.P[p].z = 0.0;
	for(unsigned int p=0; p<SplineBF.P.size(); p++) SplineBF.P[p].z = 0.0;
	for(unsigned int p=0; p<SplineTF.P.size(); p++) SplineTF.P[p].z = 0.0;
	for(unsigned int p=0; p<SplineTR.P.size(); p++) SplineTR.P[p].z = 0.0;

    if(vBR0 == 0) nBR = 0; 
    if(vTR0 == 0) nTR = 0;
}

void BEZIER_AIRFOIL::SetLEcircle(double x1, double y1, double x2, double y2, double x3, double y3, unsigned int nCircle)
{
	double A, B;
 
    nCirc = nCircle;
    Circle(x1, y1, x2, y2, x3, y3, LEcircX, LEcircY, LEcircR);

    if(nCirc == 0)
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

void BEZIER_AIRFOIL::FrontUpConvexityPoint(double x, double y)
{	
	SplineTF.P[1].x = 0.0;
	SplineTF.P[1].y = y;
}

void BEZIER_AIRFOIL::FrontDownConvexityPoint(double x, double y)
{	
	SplineBF.P[1].x = x;
	SplineBF.P[1].y = y;
}

void BEZIER_AIRFOIL::RearUpConvexityPoint(double x1, double y1, double x2, double y2)
{	
	SplineBR.P[1].x = x1;
	SplineBR.P[1].y = y1;
	
    SplineBR.P[2].x = x2;
	SplineBR.P[2].y = y2;
}

void BEZIER_AIRFOIL::RearDownConvexityPoint(double x1, double y1, double x2, double y2)
{	
	SplineTR.P[1].x = x1;
	SplineTR.P[1].y = y1;
	
    SplineTR.P[2].x = x2;
    SplineTR.P[2].y = y2;
	
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
    double A, B, TE_Fi, LE_Fi, dFi, Fi, x, y;

    if(nCirc != 0)
    {
        
    }

    if(nBR == 0 || nTR == 0) //Single spline on Top/Bottom
    {
		// === Bottom surface ===
		//clog << " === Bottom surface === " << endl;
		 
        LinearFunction(SplineBF.P[0].x, SplineBF.P[0].y, MinThX, 0.0, A, B);
        TE_Fi = atan(A);
		//clog << "TE_Fi: " << TE_Fi*180/M_PI << endl;

        LinearFunction(SplineBF.P[nBF-1].x, SplineBF.P[nBF-1].y, MinThX, 0.0, A, B);
        LE_Fi = atan(A);
		//clog << "LE_Fi: " << LE_Fi*180/M_PI << endl;

	    dFi = (M_PI + TE_Fi - LE_Fi)/(nBF-1);
    	Fi  = TE_Fi;
    
        for(unsigned int i=1; i<nBF; i++)
    	{    	
            Fi -= dFi;
	
            x = SplineBF.P[0].x;
            y = SplineBF.P[0].y;

		    RotatePointRefRad(x, y, Fi, SplineBF.P[nBF-1].x + 0.5*SplineBF.P[0].x, 0);
            
    		SplineBF.P[i].x = x;
    		SplineBF.P[i].y = y*(-MinThY)/(SplineBF.P[nBF-1].x + 0.5*SplineBF.P[0].x);
	    }
        
		// --- LE/TE points correction from Slopes ---

        if(sBF == 0)
            SplineBF.P[nBF-2].x = SplineBF.P[nBF-1].x; //x
        else
        {
            B = SplineBF.P[nBF-1].y - sBF*SplineBF.P[nBF-1].x;
            SplineBF.P[nBF-2].y = sBF*SplineBF.P[nBF-2].x + B; //y
        }

        if(sBR != 0)
        {
            B = SplineBF.P[0].y - sBR*SplineBF.P[0].x;
            SplineBF.P[1].y = sBR*SplineBF.P[1].x + B; //y
        }

		// === Top surface ===
		//clog << " === Top surface === " << endl;

        LinearFunction(SplineTF.P[0].x, SplineTF.P[0].y, MaxThX, 0.0, A, B);
        LE_Fi = atan(A);

        LinearFunction(SplineTF.P[nTF-1].x, SplineTF.P[nTF-1].y, MaxThX, 0.0, A, B);
        TE_Fi = atan(A);

	    dFi = (M_PI + LE_Fi - TE_Fi)/(nTF-1);
    	Fi  = M_PI + LE_Fi;
    
        for(unsigned int i=1; i<nTF; i++)
    	{    	
            Fi -= dFi;
	
            x = SplineTF.P[0].x;
            y = SplineTF.P[0].y;

		    RotatePointRefRad(x, y, Fi, SplineTF.P[0].x + 0.5*SplineTF.P[nTF-1].x, 0);
            
    		SplineTF.P[i].x = x;
    		SplineTF.P[i].y = y*MaxThY/(SplineTF.P[0].x + 0.5*SplineTF.P[nTF-1].x);
	    }
        
		// --- LE/TE points correction from Slopes ---

        if(sTF == 0)
            SplineTF.P[1].x = SplineTF.P[0].x; //x
        else
        {
            B = SplineTF.P[0].y - sTF*SplineTF.P[0].x;
            SplineTF.P[1].y = sTF*SplineTF.P[1].x + B; //y
        }

        if(sTR != 0)
        {
            B = SplineTF.P[nTF-1].y - sTR*SplineTF.P[nTF-1].x;
            SplineTF.P[nTF-2].y = sTR*SplineTF.P[nTF-2].x + B; //y
        }
	}

    else
    {
		clog << setprecision(2);

		// === Bottom Rear surface ===
		clog << " === Bottom Rear surface === " << endl;
		 
        LinearFunction(SplineBR.P[0].x, SplineBR.P[0].y, MinThX, 0.0, A, B);
        TE_Fi = atan(A);
		clog << "TE_Fi: " << TE_Fi*180/M_PI << endl;

        //LinearFunction(SplineBF.P[nBF-1].x, SplineBF.P[nBF-1].y, MinThX, 0.0, A, B);
        //LE_Fi = atan(A);

	    dFi = (0.5*M_PI + TE_Fi)/(nBR-1);
    	Fi  = 0;//TE_Fi;

		clog << "TE_Fi: " << TE_Fi*180/M_PI << "\t\tFii: " << (0.5*M_PI + TE_Fi)*180/M_PI << "\tdFi: " << dFi*180/M_PI << "\tFi0: " << Fi*180/M_PI << endl;
		
		clog << 0 << "\t" << Fi*180/M_PI << "\t" << SplineBR.P[0].x << "\t" << SplineBR.P[0].y << endl << endl;
    
        for(unsigned int i=1; i<nBR; i++)
    	{    	
            Fi -= dFi;
	
            x = SplineBR.P[0].x;
            y = SplineBR.P[0].y;

		    RotatePointRefRad(x, y, Fi, MinThX, 0);
            
    		SplineBR.P[i].x = x;///*(SplineBR.P[0].x - MinThX)*//(-MinThY);
    		//SplineBR.P[i].y = y*(-MinThY)/(SplineBR.P[0].x - MinThX); // with scaling to MinTh
    		SplineBR.P[i].y = MinThY; // with scaling to MinTh

			clog << i << "\t" << (Fi + TE_Fi)*180/M_PI << "\t" << SplineBR.P[i].x << "\t" << SplineBR.P[i].y << endl;
	    }
		
		clog << endl;
		
		// === Bottom Front surface ===
		clog << " === Bottom Front surface === " << endl;
		 
        //LinearFunction(SplineBF.P[0].x, SplineBF.P[0].y, MinThX, 0.0, A, B);
        //TE_Fi = atan(A);

        LinearFunction(SplineBF.P[nBF-1].x, SplineBF.P[nBF-1].y, MinThX, 0.0, A, B);
        LE_Fi = atan(A);
		clog << "LE_Fi: " << LE_Fi*180/M_PI << endl;

	    dFi = (0.5*M_PI - LE_Fi)/(nBF-1);
    	Fi  = -M_PI/2;
		
		clog << "LE_Fi: " << LE_Fi*180/M_PI << "\tFii: " << (0.5*M_PI - LE_Fi)*180/M_PI << "\tdFi: " << dFi*180/M_PI << "\tFi0: " << Fi*180/M_PI << endl;
		
		clog << 0 << "\t" << Fi*180/M_PI << "\t" << SplineBF.P[0].x << "\t" << SplineBF.P[0].y << endl;
		clog << 0 << "\t" << Fi*180/M_PI << "\t" << SplineBF.P[nBF-1].x << "\t" << SplineBF.P[nBF-1].y << endl << endl;
    
        for(unsigned int i=1; i<nBF-i; i++)
    	{    	
            Fi += dFi;
	
            //x = MinThX;
            //y = -sqrt(SplineBF.P[nBF-1].x*SplineBF.P[nBF-1].x + SplineBF.P[nBF-1].y*SplineBF.P[nBF-1].y);
            
			x = SplineBF.P[nBF-1].x;
            y = SplineBF.P[nBF-1].y;

		    clog << i << "\t" << Fi*180/M_PI << "\t" << x << "\t" << y << "\t" << MinThX << "\t" << 0 << "\t" << MinThX - SplineBF.P[nBF-1].x << endl;
		    RotatePointRefRad(x, y, Fi, MinThX, 0);
			
			/*x = LeastSquares(x, y, 0, MinThX, 0, 0);
		    y = 0;
			RotatePointRefRad(x, y, Fi, MinThX, 0);*/
            
    		SplineBF.P[i].x = x;
    		SplineBF.P[i].y = MinThY;//y*(MinThY)/(+MinThX - SplineBF.P[nBF-1].x);
			
			clog << i << "\t" << Fi*180/M_PI << "\t" << SplineBF.P[i].x << "\t" << SplineBF.P[i].y << endl;
			clog << endl;
	    }
		
		clog << endl;
		
		// === Top Front surface ===
		clog << " === Top Front surface === " << endl;
		 
        //LinearFunction(SplineTF.P[0].x, SplineTF.P[0].y, MinThX, 0.0, A, B);
        //TE_Fi = atan(A);

        LinearFunction(SplineTF.P[0].x, SplineTF.P[0].y, MaxThX, 0.0, A, B);
        LE_Fi = atan(A);

	    dFi = (0.5*M_PI + LE_Fi)/(nTF-1);
    	Fi  = 0;//M_PI - LE_Fi;
		
		clog << "LE_Fi: " << LE_Fi*180/M_PI << "\tFii: " << (0.5*M_PI + LE_Fi)*180/M_PI << "\tdFi: " << dFi*180/M_PI << "\tFi0:" << Fi*180/M_PI << endl;
		
		clog << 0 << "\t" << Fi*180/M_PI << "\t" << SplineTF.P[0].x << "\t" << SplineTF.P[0].y << endl << endl;
    
        for(unsigned int i=1; i<nTF; i++)
    	{    	
            Fi -= dFi;
	
            x = SplineTF.P[0].x;
            y = SplineTF.P[0].y;

		    //clog << x << "\t" << y << "\t" << Fi << "\t" << MaxThX << "\t" << 0 << endl;
		    RotatePointRefRad(x, y, Fi, MaxThX, 0);
            
    		SplineTF.P[i].x = x;
    		SplineTF.P[i].y = MaxThY;//y*MaxThY/(MaxThX - SplineTF.P[0].x);
			
			clog << i << "\t" << (Fi + LE_Fi)*180/M_PI << "\t" << SplineTF.P[i].x << "\t" << SplineTF.P[i].y << endl;
	    }

		clog << endl;
		
		// === Top Rear surface ===
		clog << " === Top Rear surface === " << endl;
		 
        LinearFunction(SplineTR.P[nTR-1].x, SplineTR.P[nTR-1].y, MaxThX, 0.0, A, B);
        TE_Fi = atan(A);

	    dFi = (0.5*M_PI - TE_Fi)/(nTR-1);
    	Fi  = 0.5*M_PI;

		clog << "LE_Fi: " << TE_Fi*180/M_PI << "\t\tFii: " << (0.5*M_PI + TE_Fi)*180/M_PI << "\tdFi: " << dFi*180/M_PI << "\tFi0: " << Fi*180/M_PI << endl;
		
		clog << 0 << "\t" << Fi*180/M_PI << "\t" << SplineTR.P[0].x << "\t" << SplineTR.P[0].y << endl << endl;
        
		for(unsigned int i=1; i<nTR-1; i++)
    	{    	
            Fi -= dFi;
	
            x = SplineTR.P[nTR-1].x;
            y = SplineTR.P[nTR-1].y;

		    //clog << x << "\t" << y << "\t" << Fi*180/M_PI << "\t" << MaxThX << "\t" << 0 << endl;
		    RotatePointRefRad(x, y, Fi, MaxThX, 0);
            
    		SplineTR.P[i].x = x;
    		SplineTR.P[i].y = MaxThY;//y*MaxThY/(SplineTR.P[nTR-1].x - MaxThX);
			
			clog << i << "\t" << Fi*180/M_PI << "\t" << SplineTR.P[i].x << "\t" << SplineTR.P[i].y << endl;
	    }

		clog << endl;
    }
}

void BEZIER_AIRFOIL::MakeVertexesSeq()
{
	SplineBR.VertexesSeq();
	SplineBF.VertexesSeq();
	SplineTF.VertexesSeq();
	SplineTR.VertexesSeq();
}

void BEZIER_AIRFOIL::PrintOutPoints(string AirfoilFile)
{
	ofstream out(AirfoilFile.c_str());

	out << fixed << setprecision(6);
	
    if(nBR)
    {
    	SplineBR.PrintPointsFormat(0, 0, 12, 2);
    	SplineBR.PrintPoints(out);
        out << endl;
	}

    SplineBF.PrintPointsFormat(0, 0, 12, 2);
    SplineBF.PrintPoints(out);
    out << endl;
    
	SplineTF.PrintPointsFormat(0, 0, 12, 2);
    SplineTF.PrintPoints(out);
	out << endl;

    if(nTR)
    {
		SplineTR.PrintPointsFormat(0, 0, 12, 2);
    	SplineTR.PrintPoints(out);
	    //for(unsigned int i=0; i<SplineTR.P.size(); i++)
         //   out << SplineTR.P[i].x << "    " << SplineTR.P[i].y << endl;
	}

	out.close();
}

void BEZIER_AIRFOIL::PrintOutVertex(string AirfoilFile, string AirfoilName)
{
	MakeVertexesSeq();
	
	ofstream out(AirfoilFile.c_str());

	out << AirfoilName << fixed << setprecision(6) << endl;
	
    if(nBR)
    {
    	SplineBR.PrintVertexesFormat(0, 0, 12, 2);
    	SplineBR.PrintVertexes(out);
	}

	SplineBF.PrintVertexesFormat(0, 0, 12, 2);
    SplineBF.PrintVertexes(out);
	
	SplineTF.PrintVertexesFormat(0, 0, 12, 2);
    SplineTF.PrintVertexes(out);

    if(nTR)
    {
		SplineTR.PrintVertexesFormat(0, 0, 12, 2);
    	SplineTR.PrintVertexes(out);
    }
	
	out.close();
}
