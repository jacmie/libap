#ifndef GNUPLOT_PIPE_H
#define GNUPLOT_PIPE_H

#include <string>

namespace ap {

//! Class to create pipe to the Gnuplot from the code level
class GNUPLOT_PIPE
{
	public:
	
	bool MatrixFlag;
	int FromCloumn;
	int NrOfDataCloumns;
	
	std::string GnuPlotDir;
	
	GNUPLOT_PIPE();
	int Plot2D(std::string DataFile);
	int Plot3D(std::string DataFile);
	void PlotFromPlt(std::string PltFile);
};

} // namespace ap

#endif //GNUPLOT_PIPE_H
