#ifndef _FILTER_H_
#define _FILTER_H_

#include <math.h>
#include <iostream>
#include <fstream>

#include "JMdynArray.h"

struct FILTER
{
	int n, fn;
	DYNAMIC_ARRAY <double> filter;
	DYNAMIC_ARRAY <double> Xfiltered;
	
	FILTER(int array_n, int filter_n, double amplitude);
	~FILTER();
	int Filter(double *Xinput, bool overwrite);
	int FilterRange(int shift, double *Xinput, bool overwrite);
	void Print(std::ofstream &out);
};

#endif