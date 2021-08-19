#include <math.h>
#include <iostream>

using namespace std;

void SetRotatePointRad(double AngRad, double &x, double &y);
void SetRotatePointDeg(double AngDeg, double &x, double &y);
void RotatePointRefRad(double AngRad, double xRef, double yRef, double &x, double &y);
void RotatePointRefDeg(double AngDeg, double xRef, double yRef, double &x, double &y);

bool LinearFunction(double x1, double y1, double x2, double y2, double &A, double &B);
bool LinearFunction(double x1, double y1, double fiDeg, double &A, double &B);
bool LinesCrossing(double A1, double B1, double A2, double B2, double &x, double &y);
void Parabola(double x1, double y1, double x2, double y2, double x3, double yprim, double &A, double &B, double &C);

void Circle(double x1, double y1, double x2, double y2, double x3, double y3, double &A, double &B, double &R);
void Arc2Bezeir(double x1, double y1, double &x2, double &y2, double &x3, double &y3, double x4, double y4, double xCirc, double yCirc);

double LeastSquares(double x1, double y1, double z1, double x2, double y2, double z2);

int    A_x(int n, double *C, double **dH, double *Xo);
double detA(int n, double **A);
int    Scale_A(int n, double *X, double *dF, double **H);
int    x_yT(int n, double *x, double *y, double **A);
double xT_A_y(int n, double *x, double **A, double *y, double **C);
double xT_y(int n, double *x, double *y);

int Gauss(int n, double **A, double *X, double *D);
int Gauss_Jordan(int n, double **A, double *D);
