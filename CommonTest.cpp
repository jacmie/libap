#include <cstdlib>
#include <iostream>

#include "JMconsole.h"
#include "JMxfoil.h"
#include "JMairfoilTransform.h"
#include "JMbezier.h"
#include "JMbezierAirfoil.h"
#include "JMdiscretization.h"
#include "JMGnuPlotPipe.h"
#include "JMexternalExe.h"
#include "JMsubstitute.h"
#include "JMfilter.h"

using namespace std;

#ifdef WIN32
CONSOLE con;
#endif

int main(int argc, char *argv[])
{
	//+++ CONVETIONS +++
	/*
	
	Errors:
	0 - OK
	1 - Error of type
	2 - Error of type...
	
	*/
	
	//+++ BASIC FUNCTIONS +++
	
	// *** Console ***
	//OK
	
	// *** JMmath ***
	//OK
	
	// *** JMconvert ***
	//OK
	
	//*** JMdiscretization ***
	
	clog << endl << "*** JMdiscretization ***" << endl << endl;
	
	double *Yy = new double [10];
	
	Discretization(10, 2, 1, 1, Yy);
	
	for(int i=0; i<10; i++)
		clog << i << "\t" << fixed << setprecision(4) << Yy[i] << endl;
	
	delete [] Yy;
	
	//+++ ADVANCED FUNCTIONS +++
	
	// *** JMxfoil ***
	
	clog << endl << "*** JMxfoil ***" << endl << endl;

	XFOIL CreateFoil;
	CreateFoil.global_pipe_command = "./TestDir/JMxfoil/Xfoil > ./TestDir/JMxfoil/Xfoil.log";
	
	clog << "- Make Airfoil" << endl;
	CreateFoil.MakeAirfoil("NACA 23012", "TestDir/JMxfoil/NACA23012.dat");
	CreateFoil.MakeAirfoil("NACA 2412", "TestDir/JMxfoil/NACA2412.dat");
	
	clog << "- Mix Airfoils" << endl;
	CreateFoil.Mixing("TestDir/JMxfoil/NACA23012.dat", "TestDir/JMxfoil/NACA2412.dat", "TestDir/JMxfoil/AirfoilMix.dat");
	
	clog << "- Modify Airfoil" << endl;
	CreateFoil.T   = 0.1;
	CreateFoil.T_x = 0.3;
	CreateFoil.F   = 0.0;
	CreateFoil.F_x = 0.4;
	CreateFoil.ModifyAirfoil("LOAD TestDir/JMxfoil/AirfoilMix.dat", "TestDir/JMxfoil/AirfoilMixMod.dat");
	
	clog << "- Analyz Airfoil" << endl;
	DelFile("TestDir/JMxfoil/XfoilData.dat");
	CreateFoil.Analyz(1, 3, "LOAD TestDir/JMxfoil/NACA2412.dat", "TestDir/JMxfoil/XfoilData.dat", "./TestDir/JMxfoil/Xfoil > ./TestDir/JMxfoil/XfoilAnalyze.log");
	
	//CreateFoil.Re = 300000;																			//For Error
	//CreateFoil.Analyz(1, 16, "LOAD TestDir/JMxfoil/NACA0012coarse.dat", "TestDir/JMxfoil/XfoilData.dat");	//For Error
	
	clog << "- Analyz Convergence" << endl;
	int err_nr;
	string errors = "0";
	CreateFoil.Convergence("TestDir/JMxfoil/XfoilAnalyze.log", err_nr, errors);
	clog << "err_nr = " << err_nr << endl;

	if(err_nr == 0)
	{
		if(0 == CreateFoil.GetData((char *) "TestDir/JMxfoil/XfoilData.dat"))
		{
			clog << "Alfa\t";
			clog << "CL\t";
			clog << "CD\t";
			clog << "CDp\t";
			clog << "CM\t";
			clog << "Top_Xtr\t";
			clog << "Bot_Xtr" << endl;
			
			clog << CreateFoil.Alfa << "\t";
			clog << CreateFoil.CL << "\t";
			clog << CreateFoil.CD << "\t";
			clog << CreateFoil.CDp << "\t";
			clog << CreateFoil.CM << "\t";
			clog << CreateFoil.Top_Xtr << "\t";
			clog << CreateFoil.Bot_Xtr << endl;
		}
		
		else
			clog << "Xfoil data reading error!!!" << endl;
	}
	
	else
		clog << errors << endl;
	
	// *** JMairfoilTransform ***
	
	clog << endl << "*** JMairfoilTransform ***" << endl << endl;

	AIRFOIL_TRANSFORM TestFoil;
	
	TestFoil.ReadAirfoil((char *)"TestDir/JMxfoil/AirfoilMix.dat");
	TestFoil.Transformations();
	TestFoil.WriteAirfoil((char *)"TestDir/JMairfoilTransform/AirfoilMix3D.dat");
	
	// *** JMbezier ***
	
	clog << endl << "*** JMbezier ***" << endl << endl;
	
    int n = 4;  //points -> degrees of freedom n-1 
    int u = 30; //vertex on spline
    
    BEZIER Bez(n, u);
    
    Bez.P[0][0] = 0.0;
	Bez.P[0][1] = 1.0;
    Bez.P[0][2] = 0.0;
  
    Bez.P[1][0] = 2;
    Bez.P[1][1] = 1;
    Bez.P[1][2] = 0.5;
    
    Bez.P[2][0] = 0;
    Bez.P[2][1] = 0.0;
    Bez.P[2][2] = 1;
    
    Bez.P[3][0] = 2;
    Bez.P[3][1] = 0;
    Bez.P[3][2] = 0.5;

	clog << "P:" << endl;
    Bez.PrintPoints(clog);
    clog << endl;
    
	// --- Bezier vertexes ---
    
	clog << "V:" << endl;
    Bez.VertexSeq();
	Bez.PrintVertex(clog);	
    clog << endl;
    
    // --- Write results ---
    
    ofstream out("TestDir/JMbezier/Bezier.xls");
    out << fixed << setprecision(6);
	Bez.PrintPoints(out);
    Bez.PrintVertex(out);
    
	// --- Curve Length ---
	clog << "L = " << Bez.Length() << endl << endl;

	// --- Point t & point from X ---
	
    double X, Y, Z;
    
    clog << "t(X=1.4) = " << Bez.tVertex(0, 1.4) << "% coef." << endl; //X
    Bez.Vertex(Bez.tVertex(0, 1.4), X, Y, Z);
    clog << "X\t" << "Y\t" << "Z" << endl;
    clog << X << "\t" << Y << "\t" << Z << endl;
    //out << endl << X << "\t" << Y << "\t" << Z << endl;
    
    out.close();
	
	// *** BezierAirfoil ***
	
	clog << endl << "*** BezierAirfoil ***" << endl << endl;
	
	BEZIERAIRFOIL Airfoil;
	
	Airfoil.Init(40, 60);
	Airfoil.Spline0.Init(4, 60);
	Airfoil.Spline1.Init(3, 40);
	Airfoil.Spline2.Init(3, 40);
	Airfoil.Spline3.Init(4, 60);
	
	Airfoil.FixPoints();
	Airfoil.MaxTh(0.3, 0.05);
	Airfoil.MinTh(0.3, -0.05);
	Airfoil.RearUpConvexityPoint(0.8, 0.01, 0.6, 0.05);
	Airfoil.RearDownConvexityPoint(0.6, -0.05, 0.8, -0.01);
	Airfoil.ComputeFrontUpConvexityPoint();
	Airfoil.ComputeFrontDownConvexityPoint();
	
	Airfoil.PrintOutVertex("TestDir/JMbezierAirfoil/BezierAiroil.xls", "Bla");
	
	// *** JMGnuPlotPipe ***

	clog << endl << "*** JMGnuPlotPipe ***" << endl << endl;
	
	GNUPLOT GnuPlot;
	GnuPlot.NrOfDataCloumns = 2;
//	GnuPlot.Plot2D("TestDir/JMbezier/Bezier.xls");
	GnuPlot.NrOfDataCloumns = 1;
	GnuPlot.Plot2D("TestDir/JMbezierAirfoil/BezierAiroil.xls");
/*	
	GnuPlot.Plot3D("TestDir/JMgnuplot/GnuValey.dat");
	
	GnuPlot.GnuPlotDir = "cd ./TestDir/JMgnuplot && gnuplot -persist";
	GnuPlot.PlotFromPlt("NORD_Short_Period.plt");
	GnuPlot.PlotFromPlt("GnuValey.plt");
*/	
	// *** JMparallel ***
	
	#ifdef WIN32
	clog << endl << "*** JMparallel ***" << endl << endl;
	
	Call((char *)"Notepad");
	Pipe((char *)"Xfoil.exe", (char *)"", (char *)"TestDir\\Xfoil.log", (char *)"NACA0012", (char *)"w"); //NOT GOOD
	CreateProcess(1, (char *)"TestDir\\Xfoil.exe", (char *)"");
	CreateProcess(1, (char *)"GnuPlot\\pgnuplot.exe", (char *)"");
	#endif
	
	// *** JMsubstite ***

	clog << endl << "*** JMsubstitute ***" << endl << endl;

	//SUBSTITUTE Sub("TestDir/JMsubstitute/Sub.txt", "TestDir/JMsubstitute/SubOut.txt", '%');
	SUBSTITUTE Sub("TestDir/JMsubstitute/Sub2.txt", "TestDir/JMsubstitute/SubOut.txt", '@', '&');
	
	Sub.AddVariable("0", 111);
	Sub.AddVariable("1", 222);
	Sub.AddVariable("uno", 333);
	Sub.AddVariable("due", "444");
	Sub.AddVariable("tre", "555");
    
    Sub.Insert();
	
	// *** Filters ***
	
	clog << endl << "*** JMfilter ***" << endl << endl;
	
	double P[10];
    
    P[0] = -0.00693;
    P[1] = 0.00248;	
    P[2] = 0.00436;	
    P[3] = 0.00401;
    P[4] = 0.00644;	
    P[5] = 0.00793;
    P[6] = 0.00315;	
    P[7] = 0.00753;
    P[8] = 0.00729;	
    P[9] = 0.01088;
	
	//for(int i=0; i<10; i++) //Constant value
	//	P[i] = 1;
	 
	FILTER Filt(10, 7, 1);
	//Filt.Filter(P, 0);
	Filt.FilterRange(0, P, 0);
		
	ofstream fout("TestDir/JMfilter/FilterOut.xls");
	
	for(int i=0; i<10; i++)
	{
		clog << i << "\t" << P[i] << "\t" << Filt.Xfiltered[i] << endl;
		fout << i << "\t" << P[i] << "\t" << Filt.Xfiltered[i] << endl;
	}
	
	clog << endl;
	fout.close();
	
	GnuPlot.NrOfDataCloumns = 2;
	//GnuPlot.Plot2D("TestDir/JMfilter/FilterOut.xls");
   
	// ************
	
	clog << endl << "THE END" << endl << endl;
	
	return EXIT_SUCCESS;
}
