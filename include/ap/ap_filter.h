#ifndef AP_FILTER_H
#define AP_FILTER_H

#define _USE_MATH_DEFINES

#include <fstream>
#include <vector>

struct FILTER
{
	int n, fn;
	std::vector <double> filter;
	std::vector <double> Xfiltered;
	
	FILTER(int array_n, int filter_n, double amplitude);
	~FILTER();
	int Filter(std::vector <double> &Xinput, bool overwrite);
	int FilterRange(int shift, double *Xinput, bool overwrite);
	void Print(std::ofstream &out);
};

#endif