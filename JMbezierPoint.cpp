#include "JMbezierPoint.h"

using namespace std;

template <class REAL> 
BEZIER_POINT<REAL>::BEZIER_POINT()
{
    Set(0.0);

    brackets  = 0;
    comas     = 0;
    separator = 12;
    no_print_xyz = 4;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Set(REAL val)
{
    x = y = z = val;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Set(REAL x0, REAL y0, REAL z0)
{
    x = x0; y = y0; z = z0;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Set(REAL *vec)
{
    x = vec[0]; y = vec[1]; z = vec[2];
}

template <class REAL> 
void BEZIER_POINT<REAL>::Set(std::vector <REAL> &vec)
{
    x = vec[0]; y = vec[1]; z = vec[2];
}

template <class REAL> 
void BEZIER_POINT<REAL>::Get(REAL &x0, REAL &y0, REAL &z0)
{
    x0 = x; y0 = y; z0 = z;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Get(REAL *vec)
{
    vec[0] = x; vec[1] = y; vec[2] = z;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Get(std::vector <REAL> &vec)
{
    vec[0] = x; vec[1] = y; vec[2] = z;
}

template <class REAL> 
REAL BEZIER_POINT<REAL>::Get(unsigned int XYZ)
{
    if(XYZ == 0) return x;
    if(XYZ == 1) return y;
    if(XYZ == 2) return z;
    return XYZ;
}

template class BEZIER_POINT<float>;
template class BEZIER_POINT<double>;

