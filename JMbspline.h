#ifndef _B_SPLINE_H_
#define _B_SPLINE_H_

#include "JMbezier.h"

//#include 

template <class REAL> class B_SPLINE : public BEZIER <REAL>
{
    public:

    unsigned int n, npt, u, order, degree;
    unsigned int iter;
    REAL eps, relax;

	std::vector < BEZIER_POINT <REAL> > P;  // defining points
	std::vector < BEZIER_POINT <REAL> > V;  // vertexes
	std::vector <REAL> tV; 				    // t of the vertexes
    
    std::vector < REAL > K;                 // knots (0,2,3,6)
    std::vector < unsigned int > M;         // multiplicities

	B_SPLINE();
    B_SPLINE(unsigned int n, unsigned int umax);
	void Init(unsigned int nmax, unsigned int umax);
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
    private:
    
	std::vector < std::vector <REAL> > N;

    void BasisFunctions(std::ofstream &out, REAL t);
    /*
	REAL Length(bool xflag, bool yflag, bool zflag);

    void BernsteinPolynomials();
	void BinomialCoef();*/
};

#endif
