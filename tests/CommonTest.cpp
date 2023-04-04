#include "JMGnuPlotPipe.h"
#include "JMexternalExe.h"

#ifdef _WIN32
	//#include "JMconsole.h"
	//CONSOLE con;
#endif

int main(int argc, char *argv[])
{
	using namespace std;
	
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
