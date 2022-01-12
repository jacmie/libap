#include <cstdlib>
#include <iostream>

#include "JMconsole.h"
#include "JMxfoil.h"
#include "JMairfoilTransform.h"
#include "JMbezier.h"
#include "JMbspline.h"
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
	//+++ CONVENTIONS +++
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
	
	clog << endl << "*** JMmath ***" << endl << endl;

    ofstream mout("TestDir/JMmath/Circle.xls");

    unsigned int ndiv = 36;
    double dFi = 360/(ndiv-1);
    double Fi  = 0;
    double x, y;

    clog << "Id\t" << "Fi\t" << "x\t" << "y" << endl; 

    for(unsigned int i=0; i<=ndiv; i++)
    {    	
        x = 1.0;
        y = 0.0;

		RotatePointRefDeg(Fi, 1.0, 1.0, x, y);
            
        clog << i << "\t" << fixed << setprecision(1) << Fi << setprecision(3) << "\t" << x << "\t" << y << endl; 	
        mout << fixed << setprecision(6) << x << "\t" << y << endl;

        Fi += dFi;    
	}

    mout.close();

	double A, B, R;
	Circle(2.0, 1.0, 0.0, 5.0, -1.0, 2.0, A, B, R);
	clog << endl << "A\t" << "B\t" << "R" << endl;
	clog << A << "\t" << B << "\t" << R*R << endl;
	
	// *** JMconvert ***
	//OK
	
	//*** JMdiscretization ***
	
	clog << endl << "*** JMdiscretization ***" << endl << endl;

	ofstream discret_out("TestDir/Discretization/Discretization.xls");

	vector <double> Distro;
	Discretization <double> (40, 2.0, Distro, 1, 7);
	
	for(unsigned int i=0; i<Distro.size(); i++)
	{
		clog << i << "\t" << fixed << setprecision(4) << Distro[i] << endl;
		discret_out << fixed << setprecision(4) << Distro[i] << "\t" << 1 << endl;
	}
	
	discret_out.close();
	
	GNUPLOT GnuPlotDiscret;
	GnuPlotDiscret.NrOfDataCloumns = 1;
	//GnuPlotDiscret.Plot2D("TestDir/Discretization/Discretization.xls");

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
    
    BEZIER <double> Bez(n);
    
    Bez.P[0].x = 0.0;
	Bez.P[0].y = 1.0;
    Bez.P[0].z = 0.0;
  
    Bez.P[1].x = 2;
    Bez.P[1].y = 1;
    Bez.P[1].z = 0.5;
    
    Bez.P[2].x = 0;
    Bez.P[2].y = 0.0;
    Bez.P[2].z = 1;
    
    Bez.P[3].x = 2;
    Bez.P[3].y = 0;
    Bez.P[3].z = 0.5;

	clog << "P:" << endl;
    Bez.PrintPoints(clog);
    clog << endl;
    
	// --- Bezier vertexes ---
    
	clog << "V:" << endl;
    Bez.VertexesSeq(u);
	Bez.PrintVertexes(clog);	
    clog << endl;
    
    // --- Write results ---
    
    ofstream out("TestDir/JMbezier/Bezier.xls");
    out << fixed << setprecision(6);
	Bez.PrintPoints(out);
    Bez.PrintVertexes(out);
    out.close();
    
	// --- Curve Length ---
	
	clog << "L = " << Bez.Length() << endl << endl;
	
	// --- P coordinate Min, Max ---
	
	double Min, Max;
	Bez.PMinMax(0, Min, Max);
	clog << "Min/Max (X):\t" << Min << "\t" << Max << endl << endl;

	// --- Point t & point from X ---
	
    double X, Y, Z;
    
    clog << "t(X=1.4) = " << Bez.tVertex(0, 1.4) << "% coef." << endl; //X
    Bez.Vertex(Bez.tVertex(0, 1.4), X, Y, Z);
   
	clog << endl << "X\t" << "Y\t" << "Z" << endl;
    clog << X << "\t" << Y << "\t" << Z << endl;
    
	// *** JMbspline ***
	
	clog << endl << "*** JMbspline ***" << endl << endl;
	
    unsigned int poles  = 9;
    unsigned int degree = 2;
    unsigned int type   = PEACEWISE; //QUASI_UNIFORM;
    unsigned int vertex = 222;
    
    clog << "poles  = " << poles  << endl;
    clog << "degree = " << degree << endl;
    clog << "vertex = " << vertex << endl;
    clog << "type   = " << type   << endl << endl;
    
	B_SPLINE <double> Bs(poles, degree, type);

    Bs.P[0].x = 1.0;
	Bs.P[0].y = 2.0;
    Bs.P[0].z = 1.0;
  
    Bs.P[1].x = 0.0;
    Bs.P[1].y = 2.0;
    Bs.P[1].z = 1.0;
    
    Bs.P[2].x = 0.0;
    Bs.P[2].y = 1.0;
    Bs.P[2].z = 0.5;
    
    Bs.P[3].x = 0.0;
    Bs.P[3].y = 0.0;
    Bs.P[3].z = 0.0;
     
	Bs.P[4].x = 1.0;
	Bs.P[4].y = 0.0;
    Bs.P[4].z = 0.0;
 	
    Bs.P[5].x = 2.0;
    Bs.P[5].y = 0.0;
    Bs.P[5].z = 0.0;
    
    Bs.P[6].x = 2.0;
    Bs.P[6].y = 1.0;
    Bs.P[6].z = 0.5;
    
    Bs.P[7].x = 2.0;
    Bs.P[7].y = 2.0;
    Bs.P[7].z = 1.0;
	
    Bs.P[8].x = 1.0;
    Bs.P[8].y = 2.0;
    Bs.P[8].z = 1.0;
	
	clog << "P:" << endl;
    Bs.PrintPoints(clog);
    clog << endl;

	// --- Bezier vertexes ---
    
	clog << "V:" << endl;
    Bs.VertexesSeq(vertex);
	Bs.PrintVertexes(clog);	
    clog << endl;

    // --- Write results ---
    
	ofstream bsout("TestDir/JMbspline/Bspline.xls");
    bsout << fixed << setprecision(6);
	//Bs.PrintPoints(bsout);
    Bs.PrintVertexes(bsout);
    bsout.close();
	
	// --- Curve Length ---
	
	clog << "L = " << Bs.Length() << endl << endl;
	
	// --- P coordinate Min, Max ---
	
	Bs.PMinMax(0, Min, Max);
	clog << "Min/Max (X):\t" << Min << "\t" << Max << endl << endl;
	
	// --- Point t & point from X ---
	/*	
    double X, Y, Z;
    
    clog << "t(X=1.4) = " << Bez.tVertex(0, 1.4) << "% coef." << endl; //X
    Bez.Vertex(Bez.tVertex(0, 1.4), X, Y, Z);
    clog << "X\t" << "Y\t" << "Z" << endl;
    clog << X << "\t" << Y << "\t" << Z << endl;
    //out << endl << X << "\t" << Y << "\t" << Z << endl;
    */
	
	GNUPLOT GnuPlott;
	GnuPlott.NrOfDataCloumns = 2;
	//GnuPlott.Plot2D("TestDir/JMbspline/Bspline.xls");

	// *** BezierAirfoil ***
	
	clog << endl << "*** BezierAirfoil ***" << endl << endl;
	
	BEZIER_AIRFOIL Airfoil2b;
    Airfoil2b.Init2b(6, 60);
    Airfoil2b.Init2b(6, 60, 7, 50);

	BEZIER_AIRFOIL Airfoil4b;
    Airfoil4b.Init4b(4, 60, 5, 40);
	//Airfoil4b.Init4b(4, 60, 3, 30, 3, 40, 4, 50);

	clog << "- Set LEcircle" << endl;
    Airfoil2b.SetLEcircle(0.01, -0.02, 0.0, 0.0, 0.01, 0.02);
    //Airfoil2b.SetLEcircle(0.01, -0.02, 0.0, 0.0, 0.01, 0.02, 11);
    clog << "LEcircX: " << Airfoil2b.LEcircX << "\tLEcircY: " << Airfoil2b.LEcircY << "\tLEcircR: " << Airfoil2b.LEcircR << endl;
    Airfoil4b.SetLEcircle(0.01, -0.02, 0.0, 0.0, 0.01, 0.02, 11);
    clog << "LEcircX: " << Airfoil4b.LEcircX << "\tLEcircY: " << Airfoil4b.LEcircY << "\tLEcircR: " << Airfoil4b.LEcircR << endl;
   /* 
	Airfoil4b.SplineBR.PrintPoints(clog);
    Airfoil4b.SplineBF.PrintPoints(clog);
    Airfoil4b.SplineTF.PrintPoints(clog);
    Airfoil4b.SplineTR.PrintPoints(clog);
*/
    clog << "- Set TE" << endl;
	//Airfoil2b.SetTEpoint(1.0, 0.0);
    Airfoil2b.SetTEpointB(1.0, -0.001,  0.02);
    Airfoil2b.SetTEpointT(1.0,  0.001, -0.02);
    Airfoil4b.SetTEpointB(1.0, -0.001,  0.02);
    Airfoil4b.SetTEpointT(1.0,  0.001, -0.02);
  /*  
	Airfoil4b.SplineBR.PrintPoints(clog);
    Airfoil4b.SplineBF.PrintPoints(clog);
    Airfoil4b.SplineTF.PrintPoints(clog);
    Airfoil4b.SplineTR.PrintPoints(clog);
*/	
    clog << "- Set Min/Max Th" << endl;
	Airfoil2b.SetMaxTh(0.3, 0.05);
	Airfoil2b.SetMinTh(0.3, -0.05);
    Airfoil4b.SetMaxTh(0.3, 0.05);
	Airfoil4b.SetMinTh(0.3, -0.05);
/*	
	Airfoil4b.SplineBR.PrintPoints(clog);
    Airfoil4b.SplineBF.PrintPoints(clog);
    Airfoil4b.SplineTF.PrintPoints(clog);
    Airfoil4b.SplineTR.PrintPoints(clog);
*/
    Airfoil2b.PrintOutPoints("TestDir/JMbezierAirfoil/BezierAiroilPoints.xls");
	
	clog << "- Init Splines" << endl << endl;

    Airfoil2b.InitAirfoilSplinePoints();
    Airfoil4b.InitAirfoilSplinePoints();

    Airfoil2b.PrintOutPoints("TestDir/JMbezierAirfoil/BezierAiroil2bPoints.xls");
    Airfoil4b.PrintOutPoints("TestDir/JMbezierAirfoil/BezierAiroil4bPoints.xls");

	Airfoil2b.PrintOutVertex("TestDir/JMbezierAirfoil/BezierAiroil2bVertex.xls", "Airfoil2b");
	Airfoil4b.PrintOutVertex("TestDir/JMbezierAirfoil/BezierAiroil4bVertex.xls", "Airfoil4b");
	
	// *** JMGnuPlotPipe ***

	clog << endl << "*** JMGnuPlotPipe ***" << endl << endl;
	
	GNUPLOT GnuPlot;
	GnuPlot.NrOfDataCloumns = 2;
	//GnuPlot.Plot2D("TestDir/JMmath/Circle.xls");
	//GnuPlot.Plot2D("TestDir/JMbezier/Bezier.xls");
	//GnuPlot.NrOfDataCloumns = 1;
    //GnuPlot.Plot2D("TestDir/JMbezierAirfoil/BezierAiroil2bPoints.xls");
	//GnuPlot.Plot2D("TestDir/JMbezierAirfoil/BezierAiroil2bVertex.xls");
    //GnuPlot.Plot2D("TestDir/JMbezierAirfoil/BezierAiroil4bPoints.xls");
	//GnuPlot.Plot2D("TestDir/JMbezierAirfoil/BezierAiroil4bVertex.xls");
/*	
	GnuPlot.Plot3D("TestDir/JMgnuplot/GnuValey.dat");
	
	GnuPlot.GnuPlotDir = "cd ./TestDir/JMgnuplot && gnuplot -persist";
	GnuPlot.PlotFromPlt("NORD_Short_Period.plt");
	GnuPlot.PlotFromPlt("GnuValey.plt");
*/	
	// *** JMparallel ***
	
	clog << endl << "*** JMparallel ***" << endl << endl;

#ifdef WIN32

	Call((char *)"Notepad");
	Pipe((char *)"Xfoil.exe", (char *)"", (char *)"TestDir\\Xfoil.log", (char *)"NACA0012", (char *)"w"); //NOT GOOD

//	CreateProcess(1, (char *)"TestDir\\Xfoil.exe", (char *)"");
//	CreateProcess(1, (char *)"GnuPlot\\pgnuplot.exe", (char *)"");

#else

	//Pipe((char*)"./TestDir/JMxfoil/Xfoil", (char *)"./TestDir/JMexternalExe/XfoilCommands.txt", (char *)"./TestDir/JMexternalExe/Xfoil.log", (char *)"NACA0012", (char *)"w");
	Pipe((char*)"./TestDir/JMxfoil/Xfoil", (char *)"", (char *)"./TestDir/JMexternalExe/Xfoil.log", (char *)"NACA0012\nquit\n", (char *)"w");

	std::vector <std::string> Arg;
    Arg.push_back("Sq");                                // Global directory
	Arg.push_back("2.3");
	Arg.push_back("4.1");
	CreateProcess(Arg);
	
    Arg.resize(0);
	Arg.push_back("sh");    							// Global direcotry
	Arg.push_back("./TestDir/JMexternalExe/Sq.sh");	    // Local directory, doesn't support home dir: '~' !!!
	Arg.push_back("2.3");
	Arg.push_back("4.1");
	CreateProcess(Arg);

#endif
	
	// *** JMsubstite ***

	clog << endl << "*** JMsubstitute ***" << endl << endl;

	// === Insert ===
	
	//SUBSTITUTE Sub("TestDir/JMsubstitute/Sub.txt", "TestDir/JMsubstitute/SubOut.txt", '%');
	SUBSTITUTE Sub("TestDir/JMsubstitute/Sub2.txt", "TestDir/JMsubstitute/SubOut.txt", '@', '&');

    clog << endl;

	Sub.AddVariable("0", 111);
	Sub.AddVariable("1", 222);
	Sub.AddVariable("uno", 333);
	Sub.AddVariable("due", "444");
	Sub.AddVariable("tre", "555");
    Sub.AddVariable("ff", "");
    Sub.AddVariable("mod", "modify");
	Sub.AddVariable("naca", 2412);

    for(unsigned int i=0; i<Sub.Var.size(); i++)   
    {
        clog << Sub.Var[i].Name << "\t" << Sub.Var[i].Value << endl;
    }
    clog << endl;

    Sub.Insert();
	
    clog << endl;

	// === Derieve ===
	
	SUBSTITUTE SubD("TestDir/JMsubstitute/XfoilDataTemplate.dat", "TestDir/JMsubstitute/XfoilData.dat", '@', '&');
	
	SubD.AddVariable("@CL", 0);
	SubD.AddVariable("@AoA&", 0);
	SubD.AddVariable("@CD", 0);
	SubD.AddVariable("CM&", 0);
    SubD.AddVariable("", 0);

    //SUBSTITUTE SubD("/home/JM/C++/Core/FlowTree/FT_Projects/SqTemplate.dat", "/home/JM/C++/Core/FlowTree/FT_Projects/SqOut.dat", '@', '&');
	//SubD.AddVariable("SqRes", 0);

    clog << endl;

	SubD.Extract();

	for(unsigned int i=0; i<SubD.Var.size(); i++)
	{
		clog << SubD.Var[i].Name << "\t" << SubD.Var[i].Value << endl;
	}

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
