#ifndef _BEZIER_H_
#define _BEZIER_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>

class BEZIER
{
    public:
    
    int n, npt, u;
    int iter;
    double eps, relax;
    
	std::vector < std::vector <double> > P; // defining points
	std::vector < std::vector <double> > V; // vertexes
	std::vector <double> tV; 				// t of the vertexes

	BEZIER();
    BEZIER(int n, int umax);
    ~BEZIER();
	void Init(int nmax, int umax);
    void Vertex(double t, double &X, double &Y, double &Z);
    void VertexSeq();
    double tVertex(int XYZ, double Value);
	double Length();
	double LengthX();
	double LengthY();
	double LengthZ();
	double LengthXY();
	double LengthYZ();
	double LengthXZ();
	void PMinMax(int XYZ, double &min, double &max);
    void PrintPoints(std::ostream &out);
	void PrintVertex(std::ostream &out);

    private:
    
	std::vector <double> C;
    
	double Length(bool xflag, bool yflag, bool zflag);
	void BinomialCoef();
};

#endif
