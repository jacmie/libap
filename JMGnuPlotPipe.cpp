#include "JMGnuPlotPipe.h"

using namespace std;

GNUPLOT::GNUPLOT()
{
	MatrixFlag = 0;
	FromCloumn = 1;
	NrOfDataCloumns = 1;
	
	//DataFile;
	ConfigFile = "";

#ifdef WIN32
	GnuPlotDir = "pgnuplot";
#else
	GnuPlotDir = "gnuplot -persist";
#endif
}

int GNUPLOT::Plot2D()
{
    char Num[16], Line[256];
    
#ifdef WIN32
    FILE *gnucmd = _popen(GnuPlotDir.c_str(), "w");
#else    
    FILE *gnucmd = popen(GnuPlotDir.c_str(), "w");
#endif

    if(!gnucmd)
	{
		fl_alert("GnuPlot pipe error!");
        return 0;
	}
	
    strcpy(Line, "load ");
    strcat(Line, ConfigFile.c_str());
	strcat(Line, "\n");
	
    strcat(Line, "plot");
            
    //plot 'PlotFile.dat' using 1:3, '' using 1:2 
    
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
   
    fputs(Line, gnucmd);
    cout << Line << endl;
    fflush(gnucmd);
	
	return 1;
}

int GNUPLOT::Plot3D()
{
	char Line[20056];
    
#ifdef WIN32
    FILE *gnucmd = _popen(GnuPlotDir.c_str(), "w");
#else    
    FILE *gnucmd = popen(GnuPlotDir.c_str(), "w");
#endif
   
	if(!gnucmd)
	{
		fl_alert("GnuPlot pipe error!");
        return 0;
	}
            
    strcpy(Line, "load ");
    strcat(Line, ConfigFile.c_str());
    strcat(Line, "\n");
   
    strcat(Line, "splot");
            
        strcat(Line, " '");
        strcat(Line, DataFile.c_str());
        strcat(Line, "'");
		
		if(MatrixFlag)
			strcat(Line, " matrix");
           
    strcat(Line, "\n");
   
    fputs(Line, gnucmd);
    
    fflush(gnucmd);
	
	return 1;
}
