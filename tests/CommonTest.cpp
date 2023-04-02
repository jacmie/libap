#include "JMxfoil.h"
#include "JMairfoilTransform.h"
#include "JMbezier.h"
#include "JMbspline.h"
#include "JMbezierAirfoil.h"
#include "JMGnuPlotPipe.h"
#include "JMexternalExe.h"

#ifdef _WIN32
	//#include "JMconsole.h"
	//CONSOLE con;
#endif

int main(int argc, char *argv[])
{
	using namespace std;

	//+++ ADVANCED FUNCTIONS +++
	
	// *** JMxfoil ***
	
	clog << endl << "*** JMxfoil ***" << endl << endl;
	
	XFOIL CreateFoil;
	
#ifdef _WIN32
	CreateFoil.global_pipe_command = "TestDir\\JMxfoil\\Xfoil.exe > TestDir\\JMxfoil\\Xfoil.log";
#else
	CreateFoil.global_pipe_command = "./TestDir/JMxfoil/Xfoil.exe > /TestDir/JMxfoil/Xfoil.log";
#endif

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
	
#ifdef _WIN32
	DelFile("TestDir\\JMxfoil\\XfoilData.dat");
	CreateFoil.Analyz(1, 3, "LOAD TestDir/JMxfoil/NACA2412.dat", "TestDir/JMxfoil/XfoilData.dat", "TestDir\\JMxfoil\\Xfoil > TestDir\\JMxfoil\\XfoilAnalyze.log");
#else	
	DelFile("TestDir/JMxfoil/XfoilData.dat");
	CreateFoil.Analyz(1, 3, "LOAD TestDir/JMxfoil/NACA2412.dat", "TestDir/JMxfoil/XfoilData.dat", "./TestDir/JMxfoil/Xfoil > ./TestDir/JMxfoil/XfoilAnalyze.log");
#endif

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
	// *** JMexternalExe ***
	
	clog << endl << "*** JMexternalExe ***" << endl << endl;

#ifdef _WIN32

	clog << "- Call" << endl;
	//Call((char *)"Notepad");
	clog << "- Pipe" << endl;
	Pipe((char *)"TestDir\\JMxfoil\\Xfoil.exe", (char *)"", (char *)"TestDir\\JMexternalExe\\Xfoil.log", (char *)"NACA0012\nquit\n", (char *)"w");
	
	// Put to PATH: "C:/msys64/usr/local/bin/Sq.exe" !!!
	
	clog << "- Process - string" << endl;
	std::vector <std::string> Arg;
    Arg.push_back("C:/msys64/usr/local/bin/Sq.exe");  	// Global directory
	Arg.push_back("2.3");
	Arg.push_back("4.1");
	ExeCreateProcess(Arg);
	
    Arg.resize(0);
	Arg.push_back("TestDir\\JMexternalExe\\Sq.cmd");	// Local directory only in MSYS, doesn't support home dir: '~' !!!
	//Arg.push_back("C:\\msys64\\home\\jmiel\\JMcommon\\TestDir\\JMexternalExe\\Sq.cmd"); // Global direcotry
	Arg.push_back("2.3");
	Arg.push_back("4.1");
	ExeCreateProcess(Arg);

#else

	clog << "- Pipe" << endl;
	//Pipe((char*)"./TestDir/JMxfoil/Xfoil", (char *)"./TestDir/JMexternalExe/XfoilCommands.txt", (char *)"./TestDir/JMexternalExe/Xfoil.log", (char *)"NACA0012", (char *)"w");
	Pipe((char*)"./TestDir/JMxfoil/Xfoil", (char *)"", (char *)"./TestDir/JMexternalExe/Xfoil.log", (char *)"NACA0012\nquit\n", (char *)"w");

	clog << "- Process - string" << endl;
	std::vector <std::string> Arg;
    Arg.push_back("Sq");                                // Global directory
	Arg.push_back("2.3");
	Arg.push_back("4.1");
	ExeCreateProcess(Arg);
	
    Arg.resize(0);
	Arg.push_back("sh");    							// Global direcotry
	Arg.push_back("./TestDir/JMexternalExe/Sq.sh");	    // Local directory, doesn't support home dir: '~' !!!
	Arg.push_back("2.3");
	Arg.push_back("4.1");
	ExeCreateProcess(Arg);

#endif
		
	return EXIT_SUCCESS;
}
