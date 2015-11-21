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
	std::string DataFile;
	std::string ConfigFile;
	
	GNUPLOT();
	int Plot2D();
	int Plot3D();
};

#endif