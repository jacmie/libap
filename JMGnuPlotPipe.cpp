#include "JMGnuPlotPipe.h"

using namespace std;

GNUPLOT::GNUPLOT()
{
	MatrixFlag = 0;
	FromCloumn = 1;
	NrOfDataCloumns = 1;
	
#ifdef WIN32
	GnuPlotDir = "pgnuplot";
#else
	GnuPlotDir = "gnuplot -persist";
#endif
}

int GNUPLOT::Plot2D(std::string DataFile)
{
    char Num[16], Line[256];
    
#ifdef WIN32
    FILE *gnucmd = _popen(GnuPlotDir.c_str(), "w");
#else    
    FILE *gnucmd = popen(GnuPlotDir.c_str(), "w");
#endif

    if(!gnucmd)
	{
		//fl_alert("GnuPlot pipe error!");
		clog << "GnuPlot pipe error!" << endl;
        return 1;
	}
    
    //plot 'PlotFile.dat' using 1:3, '' using 1:2 
	strcpy(Line, "plot");
    
    for(int i=FromCloumn; i<=NrOfDataCloumns; i++)
    {   
        strcat(Line, " '");
        strcat(Line, DataFile.c_str());
        strcat(Line, "'");
        strcat(Line, " using ");
        sprintf(Num, "%i", FromCloumn);
        strcat(Line, Num);
        strcat(Line, ":");
        sprintf(Num, "%i", i+1);
        strcat(Line, Num);
            
        if(i != NrOfDataCloumns)
            strcat(Line, ", \\");
        
        strcat(Line, "\n");
    }
           
    strcat(Line, "\n");
   
	//strcat(Line, "pause -1\n");
   
    clog << "Command: " << Line << endl;
    fputs(Line, gnucmd);
    
	fflush(gnucmd);
	
	return 0;
}

int GNUPLOT::Plot3D(std::string DataFile)
{
	char Line[20056];
    
#ifdef WIN32
    FILE *gnucmd = _popen(GnuPlotDir.c_str(), "w");
#else    
    FILE *gnucmd = popen(GnuPlotDir.c_str(), "w");
#endif
   
	if(!gnucmd)
	{
		//fl_alert("GnuPlot pipe error!");
		clog << "GnuPlot pipe error!" << endl;
        return 1;
	}
            
    strcpy(Line, "splot");
            
        strcat(Line, " '");
        strcat(Line, DataFile.c_str());
        strcat(Line, "'");
		
		if(MatrixFlag)
			strcat(Line, " matrix");
           
    strcat(Line, "\n");
   
    clog << "Command: " << Line << endl;
    fputs(Line, gnucmd);
    
    fflush(gnucmd);
	
	return 0;
}

void GNUPLOT::PlotFromPlt(std::string PltFile)
{
	string Command = GnuPlotDir + " " + PltFile; 
	clog << system(Command.c_str()) << endl;
}
