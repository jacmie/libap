#include "ap_gnuplotPipe.h"

#include <cstdio>
#include <iostream>

namespace ap {

GNUPLOT_PIPE::GNUPLOT_PIPE()
{
	MatrixFlag = 0;
	FromCloumn = 1;
	NrOfDataCloumns = 1;
	
#ifdef _WIN32
	GnuPlotDir = "pgnuplot";
#else
	GnuPlotDir = "gnuplot -persist";
#endif
}

int GNUPLOT_PIPE::Plot2D(std::string DataFile) {    
#ifdef _WIN32
    FILE *gnucmd = _popen(GnuPlotDir.c_str(), "w");
#else    
    FILE *gnucmd = popen(GnuPlotDir.c_str(), "w");
#endif

    if(!gnucmd) {
		std::clog << "GnuPlot pipe error!" << std::endl;
        return 1;
	}
    
    //plot 'PlotFile.dat' using 1:3, '' using 1:2 
    std::string line = "plot";
	
    for(int i=FromCloumn; i<=NrOfDataCloumns; i++)
    {   
		line += " '" + DataFile + "'" + " using ";
        line += std::to_string(FromCloumn);
        line += ":";
        line += std::to_string(i+1);
            
        if(i != NrOfDataCloumns)
            line += ", \\";
        
        line += "\n";
    }
           
    line += "\n";
   
    std::clog << "Command: " << line << std::endl;
    fputs(line.c_str(), gnucmd);
    
	fflush(gnucmd);
	
	return 0;
}

int GNUPLOT_PIPE::Plot3D(std::string DataFile) {
#ifdef _WIN32
    FILE *gnucmd = _popen(GnuPlotDir.c_str(), "w");
#else    
    FILE *gnucmd = popen(GnuPlotDir.c_str(), "w");
#endif
   
	if(!gnucmd) {
		std::clog << "GnuPlot pipe error!" << std::endl;
        return 1;
	}
    
	std::string line = "splot";
    line += " '" + DataFile + "'";
		
	if(MatrixFlag) {
		line += " matrix";
	}
	
    line += "\n";

    std::clog << "Command: " << line << std::endl;
    fputs(line.c_str(), gnucmd);
    
    fflush(gnucmd);
	
	return 0;
}

void GNUPLOT_PIPE::PlotFromPlt(std::string PltFile) {
	std::string Command = GnuPlotDir + " " + PltFile; 
	std::clog << system(Command.c_str()) << std::endl;
}

} // namespace ap
