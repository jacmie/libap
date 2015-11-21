#ifndef _AIRFOIL_H_
#define _AIRFOIL_H_

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <FL/fl_ask.H>

#include "JMmath.h"

class AIRFOIL_TRANSFORM
{
	public:
	
	int NrOfRows;
	int NrOfCord;
	
	double rotation, ref;
	double scale;
	double strch;
	double trans_x;
	double dy, dz; //for X axis rotation
	double trans_y;
	double trans_z;
	
	double *x;
	double *y;
    double *z;
	
	AIRFOIL_TRANSFORM();
	~AIRFOIL_TRANSFORM();
	
	int  ReadAirfoil(char *AirfoilFile);
	void Transformations();
	int  WriteAirfoil(char *AirfoilFile);
	//void Z_correction(int nprof, double Xr, double Yr, double Zr, double Xt, double Yt, double Zt, AIRFOIL *prof);
	
	private:
	
	void CheckFileFormat(std::ifstream &in);
	void CountRows(std::ifstream &in);
};

#endif