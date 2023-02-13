#ifndef _GNUPLOT_H_
#define _GNUPLOT_H_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <FL/fl_ask.H>

class GNUPLOT
{
	public:
	
	bool MatrixFlag;
	int FromCloumn;
	int NrOfDataCloumns;
	
	std::string GnuPlotDir;
	
	GNUPLOT();
	int Plot2D(std::string DataFile);
	int Plot3D(std::string DataFile);
	void PlotFromPlt(std::string PltFile);
};

#endif
