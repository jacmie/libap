#include <cstdlib>
#include <iostream>

#include "JMconsole.h"
#include "JMxfoil.h"
#include "JMairfoil.h"
#include "JMbezier.h"
#include "JMbezierAirfoil.h"
#include "JMdiscretization.h"
#include "JMGnuPlotPipe.h"
#include "JMexternalExe.h"
#include "JMsubstitute.h"
#include "JMfilter.h"

using namespace std;
CONSOLE con;

int main(int argc, char *argv[])
{
	//+++ CONVETIONS +++
	/*
	
	Errors:
	0 - Error
	1 - OK
	2 - Error of type
	3 - Error of type...
	
	*/
	
	//+++ BASIC FUNCTIONS +++
	
	//*** Console ***
	//OK
	
	//*** JMmath ***
	//OK
	
	//*** JMconvert ***
	//OK
	
	//*** JMdiscretization ***
	/*
	double *Yy = new double [10];
	
	Discretization(10, 2, 1, 1, Yy);
	
	for(int i=0; i<10; i++)
		cout << i << "\t" << Yy[i] << endl;
	
	delete [] Yy;
	
	//system("pause");
	
	//+++ ADVANCED FUNCTIONS +++
	
	//*** JMxfoil ***
	
	XFOIL CreateFoil;
	
	CreateFoil.MakeAirfoil("NACA 23012", "TestDir/NACA23012.dat");
	CreateFoil.MakeAirfoil("NACA 2412", "TestDir/NACA2412.dat");
	
	CreateFoil.Mixing("TestDir/NACA23012.dat", "TestDir/NACA2412.dat", "TestDir/AirfoilMix.dat");
	
	CreateFoil.T   = 0.1;
	CreateFoil.T_x = 0.3;
	CreateFoil.F   = 0.0;
	CreateFoil.F_x = 0.4;
	CreateFoil.ModifyAirfoil("LOAD TestDir/AirfoilMix.dat", "TestDir/AirfoilMixMod.dat");
	
	DelFile("TestDir\\XfoilData.dat");
	CreateFoil.Analyz(1, 3, "LOAD TestDir/NACA2412.dat", "TestDir/XfoilData.dat");
	
	//CreateFoil.Re = 300000;																					//For Error
	//CreateFoil.Analyz(1, 16, "LOAD TestDir/NACA0012coarse.dat", "TestDir/XfoilData.dat");	//For Error
	
	int err_nr;
	string errors = "0";
	CreateFoil.Convergence("XfoilLog.txt", err_nr, errors);
	
	if(err_nr == 0)
	{
		if(CreateFoil.GetData((char *) "TestDir/XfoilData.dat"))
		{
			con << CreateFoil.Alfa << "\t";
			con << CreateFoil.CL << "\t";
			con << CreateFoil.CD << "\t";
			con << CreateFoil.CDp << "\t";
			con << CreateFoil.CM << "\t";
			con << CreateFoil.Top_Xtr << "\t";
			con << CreateFoil.Bot_Xtr << endl;
		}
		
		else
			con << "Xfoil data reading error!!!" << endl;
	}
	
	
	else
		con << errors << endl;
	
	//*** JMairfoil ***
	
	AIRFOIL TestFoil;
	
	TestFoil.ReadAirfoil((char *)"TestDir/AirfoilMix.dat");
	TestFoil.Transformations();
	TestFoil.WriteAirfoil((char *)"TestDir/AirfoilMix3D.dat");
	
	//*** JMbezier ***
	
    int n = 4;  //points -> degrees of freedom n-1 
    int u = 30; //vertex on spline
    
    BEZIER Bez(n, u);
    
    Bez.P.Array2d[0][0] = 0.0;
	Bez.P.Array2d[0][1] = 1.0;
    Bez.P.Array2d[0][2] = 0.0;
  
    Bez.P.Array2d[1][0] = 2;
    Bez.P.Array2d[1][1] = 1;
    Bez.P.Array2d[1][2] = 0.5;
    
    Bez.P.Array2d[2][0] = 0;
    Bez.P.Array2d[2][1] = 0.0;
    Bez.P.Array2d[2][2] = 1;
    
    Bez.P.Array2d[3][0] = 2;
    Bez.P.Array2d[3][1] = 0;
    Bez.P.Array2d[3][2] = 0.5;
    Bez.PrintPoints(con);
    
	//Bezier curve
    
    Bez.VertexSeq();
    
    //Write results
    
    ofstream out("TestDir/Bezier.xls");
    out << fixed << setprecision(6);
    cout << fixed << setprecision(6);
	Bez.PrintPoints(out);
	Bez.PrintPoints(con);
    cout << endl;
    Bez.PrintVertex(out);
	Bez.PrintVertex(con);	
    cout << endl;
    
	//Point t & point from X
	
    double X, Y, Z;
    
    con << Bez.tVertex(0, 1.4) << endl; //X
    Bez.Vertex(Bez.tVertex(0, 1.4), X, Y, Z);
    con << X << "\t" << Y << "\t" << Z << endl;
    out << endl << X << "\t" << Y << "\t" << Z << endl;
    
    out.close();
	
	//*** BezierAirfoil ***
	
	con << "*** BezierAirfoil ***" << endl;
	
	BEZIERAIRFOIL Airfoil;
	
	Airfoil.Init(40, 60);
	/*Airfoil.Spline0.Init(4, 60);
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
	
	Airfoil.PrintOutVertex("TestDir/BezierAiroil.xls", "Bla");
	
	//*** JMGnuPlotPipe ***

	GNUPLOT GnuPlot;
	
	//GnuPlot.DataFile = "TestDir/Bezier.xls";
	GnuPlot.DataFile = "TestDir/BezierAiroil.xls";
	GnuPlot.ConfigFile = "\"TestDir/config1.gnu\"\n";
	GnuPlot.NrOfDataCloumns = 2;
	GnuPlot.Plot2D();
	
	GnuPlot.DataFile = "TestDir/GnuValey.dat";
	GnuPlot.ConfigFile = "\"TestDir/config3.gnu\"\n";
	GnuPlot.Plot3D();
	
	//*** JMparallel ***
	//Call((char *)"Notepad");
	//Pipe((char *)"Xfoil.exe", (char *)"", (char *)"TestDir\\Xfoil.log", (char *)"NACA0012", (char *)"w"); //NOT GOOD
	//CreateProcess(1, (char *)"TestDir\\Xfoil.exe", (char *)"");
	//CreateProcess(1, (char *)"GnuPlot\\pgnuplot.exe", (char *)"");
	*/
	//*** JMsubstite ***
	
	int n = 5;
    Variables *Var = new Variables [5];
   
    Var[0].Name  = "0";
    Var[0].Value = "111";
    
    Var[1].Name  = "1";
    Var[1].Value = "222";
    
    Var[2].Name  = "uno";
    Var[2].Value = "333";
    
    Var[3].Name  = "due";
    Var[3].Value = "444";
    
    Var[4].Name  = "tre";
    Var[4].Value = "555";
    
	Substitute Sub((char *)"TestDir/Sub.txt", (char *)"TestDir/SubOut.txt", '%');
	//Substitute Sub((char *)"TestDir/Sub2.txt", (char *)"TestDir/SubOut.txt", '@', '&');
    
    Sub.Insert(n, Var);
    
    //system("TestDir\\SubOut.txt");
	
	delete [] Var;
	
	
	//*** JM3dx ***
	
	//*** Filters ***
	/*
	double X[10];
    
    X[0] = -0.00693;
    X[1] = 0.00248;	
    X[2] = 0.00436;	
    X[3] = 0.00401;
    X[4] = 0.00644;	
    X[5] = 0.00793;
    X[6] = 0.00315;	
    X[7] = 0.00753;
    X[8] = 0.00729;	
    X[9] = 0.01088;
	
	//for(int i=0; i<10; i++) //Constant value
	//	X[i] = 1;
	
	for(int i=0; i<10; i++)
		con << i << "\t" << X[i] << endl;
	con << endl;
	 
	FILTER Filt(10, 7, 1);
	//Filt.Filter(X, 0);
	Filt.FilterRange(0, X, 0);
		
	ofstream fout("TestDir/FilterOut.xls");
	
	for(int i=0; i<10; i++)
	{
		con << i << "\t" << Filt.Xfiltered.Array[i] << endl;
		fout << i << "\t" << X[i] << "\t" << Filt.Xfiltered.Array[i] << endl;
	}
	
	con << endl;
	fout.close();
	*/
    system("PAUSE");
    return EXIT_SUCCESS;
}