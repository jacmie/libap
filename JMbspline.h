#ifndef _B_SPLINE_H_
#define _B_SPLINE_H_

#include "JMbezier.h"

enum bspline_type {UNIFORM, QUASI_UNIFORM, PEACEWISE};

template <class REAL> class B_SPLINE : public BEZIER <REAL>
{
    public:

    unsigned int n, npt, u, order, degree;
    unsigned int iter;
    REAL eps, relax;

	std::vector < BEZIER_POINT <REAL> > P;  // poles
	std::vector < BEZIER_POINT <REAL> > V;  // vertexes
	std::vector <REAL> tV; 				    // t of the vertexes
    
    std::vector < REAL > K;                 // knots (0,2,3,6)
    std::vector < unsigned int > M;         // multiplicities

	B_SPLINE();
    B_SPLINE(unsigned int poles_nr, unsigned int curve_degree, unsigned int vertexes_nr, unsigned int type=QUASI_UNIFORM);
	void Init(unsigned int poles_nr, unsigned int curve_degree, unsigned int vertexes_nr, unsigned int type=QUASI_UNIFORM);
    /*void Vertex(REAL t, REAL &X, REAL &Y, REAL &Z);
    void VertexesSeq();
    REAL tVertex(unsigned int XYZ, REAL Value);
	REAL Length();
	REAL LengthX();
	REAL LengthY();
	REAL LengthZ();
	REAL LengthXY();
	REAL LengthYZ();
	REAL LengthXZ();
	void PMinMax(unsigned int XYZ, REAL &min, REAL &max);
    
    void PrintPointsFormat(bool brackets, bool comas, unsigned int separator, unsigned int no_print_xyz);
    void PrintVertexesFormat(bool brackets, bool comas, unsigned int separator, unsigned int no_print_xyz);
    void PrintPoints(std::ostream &out);
	void PrintVertexes(std::ostream &out);
    */
    //private:
    
	std::vector < std::vector <REAL> > N;

	double deBoor(int k, double x);
    void BasisFunctions(REAL t);
    void GetVertex(REAL t);
    /*
	REAL Length(bool xflag, bool yflag, bool zflag);

    void BernsteinPolynomials();
	void BinomialCoef();*/
};

#endif
