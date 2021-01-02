#include <math.h>
#include <iostream>

using namespace std;

void RotatePointRad(double &x, double &y, double AngRad);
void RotatePointDeg(double &x, double &y, double AngDeg);
void RotatePointRefRad(double &x, double &y, double AngRad, double Ref);
void RotatePointRefDeg(double &x, double &y, double AngDeg, double Ref);

void LinearFunction(double x1, double y1, double x2, double y2, double &A, double &B);
void LinearFunction(double &A, double &B, double x1, double y1, double fiDeg);
void Parabola(double &A, double &B, double &C, 
              double x1, double y1,
              double x2, double y2,
              double x3, double yprim);

void Circle(double x1, double y1, double x2, double y2, double x3, double y3, double &A, double &B, double &R);

double LeastSquares(double x1, double y1, double z1, double x2, double y2, double z2);

int    A_x(int n, double *C, double **dH, double *Xo);
double detA(int n, double **A);
int    Scale_A(int n, double *X, double *dF, double **H);
int    x_yT(int n, double *x, double *y, double **A);
double xT_A_y(int n, double *x, double **A, double *y, double **C);
double xT_y(int n, double *x, double *y);

int Gauss(int n, double **A, double *X, double *D);
int Gauss_Jordan(int n, double **A, double *D);
