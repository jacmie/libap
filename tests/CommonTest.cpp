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
		
	return EXIT_SUCCESS;
}
