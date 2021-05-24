#ifndef _B_SPLINE_H_
#define _B_SPLINE_H_

#include "JMbezier.h"

enum bspline_type {UNIFORM, QUASI_UNIFORM, PEACEWISE};

template <class REAL> class B_SPLINE : public BEZIER <REAL>
{
    public:

    unsigned int degree;
    std::vector < REAL > K;

	B_SPLINE();
    B_SPLINE(unsigned int poles_nr, unsigned int curve_degree, unsigned int type=QUASI_UNIFORM);
	void Init(unsigned int poles_nr, unsigned int curve_degree, unsigned int type=QUASI_UNIFORM);
    int  Vertex(REAL t, REAL &X, REAL &Y, REAL &Z);
	void VertexesSeq(unsigned int v_nr);
    
	//REAL tVertex(unsigned int XYZ, REAL Value);
    
	private:
    
	double deBoor(unsigned int k, double x, std::vector <REAL> d);

	public:

	std::vector < std::vector <REAL> > N;
	void BasisFunctions(REAL t); // only for tests
};

#endif
