#ifndef _BEZIER_H_
#define _BEZIER_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

#include "JMdynArray.h"

class BEZIER
{
    public:
    
    int n, npt, u;
    int iter;
    double eps, relax;
    
	DYNAMIC_ARRAY <double> C;
	DYNAMIC_ARRAY_2D <double> P;
	DYNAMIC_ARRAY_2D <double> V;
	
    //int     *C;
    //double **P; //def points
    //double **V; //vertex
       
	BEZIER();
    BEZIER(int n, int umax);
    ~BEZIER();
	void Init(int nmax, int umax);
    void Vertex(double t, double &X, double &Y, double &Z);
    void VertexSeq();
    double tVertex(int XYZ, double Value);
    void PrintPoints(std::ostream &out);
	void PrintVertex(std::ostream &out);
	void PMinMax(int XYZ, double &min, double &max);

    private:
    
    void BinomialCoef();
};

#endif
