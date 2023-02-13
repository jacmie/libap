#ifndef GNUPLOT_PIPE_H
#define GNUPLOT_PIPE_H

#include <string>

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

#endif //GNUPLOT_PIPE_H
