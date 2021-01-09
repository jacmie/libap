#ifndef _BEZIER_H_
#define _BEZIER_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>

template <class REAL> class BEZIER_POINT
{
    public:
        
    REAL x;
    REAL y;
    REAL z;

    BEZIER_POINT();

    void Set(REAL val);
    void Set(REAL x0, REAL y0, REAL z0);
    void Set(REAL *vec);
    void Set(std::vector <REAL> &vec);

    void Get(REAL &x0, REAL &y0, REAL &z0);
    void Get(REAL *vec);
    void Get(std::vector <REAL> &vec);

    REAL Get(unsigned int XYZ);

    //Print format atributes
    bool brackets;
    bool comas;
    unsigned int separator;
    unsigned int no_print_xyz;
};

template <class REAL> class BEZIER
{
    public:
    
    unsigned int n, npt, u;
    unsigned int iter;
    REAL eps, relax;

	std::vector < BEZIER_POINT <REAL> > P;  // defining points
	std::vector < BEZIER_POINT <REAL> > V;  // vertexes
	std::vector <REAL> tV; 				    // t of the vertexes

	BEZIER();
    BEZIER(unsigned int n, unsigned int umax);
	void Init(unsigned int nmax, unsigned int umax);
    void Vertex(REAL t, REAL &X, REAL &Y, REAL &Z);
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

    private:
    
	std::vector <REAL> C;
    
	REAL Length(bool xflag, bool yflag, bool zflag);
	void BinomialCoef();
};

#endif
