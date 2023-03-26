// Part of All Purpose - ap library

#ifndef AP_BASIC_MATH_H
#define AP_BASIC_MATH_H

namespace ap 
{

//! Set 2D point by rotation 
/*!
 * \param angRad - angle of rotation in radians
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 * \note Initially reference point of rotation liyes on the x axis. It is advised to set the initial value of x=r (radius of rotation) and y=0. 
 */
void SetRotatePointRad(double angRad, double &x, double &y);

//! Set 2D point by rotation 
/*!
 * \param angDeg - angle of rotation in degrees
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 * \note Initially reference point of rotation liyes on the x axis. It is advised to set the initial value of x=r (radius of rotation) and y=0. 
 */
void SetRotatePointDeg(double angDeg, double &x, double &y);

//! Set 2D point by rotation about reference point 
/*!
 * \param angRad - angle of rotation in radians
 * \param xRef - reference point x coordinate about which rotation is done
 * \param yRef - reference point x coordinate about which rotation is done
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 * \note Initially reference point of rotation liyes on the x axis. It is advised to set the initial value of x=r (radius of rotation) and y=0. 
 */
void SetRotatePointRefRad(double angRad, double xRef, double yRef, double &x, double &y);

//! Set 2D point by rotation about reference point 
/*!
 * \param angDeg - angle of rotation in degrees
 * \param xRef - reference point x coordinate about which rotation is done
 * \param yRef - reference point x coordinate about which rotation is done
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 * \note Initially reference point of rotation liyes on the x axis. It is advised to set the initial value of x=r (radius of rotation) and y=0. 
 */
void SetRotatePointRefDeg(double angDeg, double xRef, double yRef, double &x, double &y);


//! Set 2D point by rotation about reference point 
/*!
 * \param angDeg - angle of rotation in degrees
 * \param xRef - reference point x coordinate about which rotation is done
 * \param yRef - reference point x coordinate about which rotation is done
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 * \note Initially reference point of rotation liyes on the x axis. It is advised to set the initial value of x=r (radius of rotation) and y=0. 
 */
void RotatePointRad(double angRad, double &x, double &y);
void RotatePointDeg(double angDeg, double &x, double &y);
void RotatePointRefRad(double angRad, double xRef, double yRef, double &x, double &y);
void RotatePointRefDeg(double angDeg, double xRef, double yRef, double &x, double &y);

bool LinearFunction(double x1, double y1, double x2, double y2, double &A, double &B);
bool LinearFunction(double x1, double y1, double fiDeg, double &A, double &B);
bool LinesIntersection(double A1, double B1, double A2, double B2, double &x, double &y);
void Parabola(double x1, double y1, double x2, double y2, double x3, double yprim, double &A, double &B, double &C);

void Circle(double x1, double y1, double x2, double y2, double x3, double y3, double &A, double &B, double &R);
bool Arc2Bezier(double x1, double y1, double &x2, double &y2, double &x3, double &y3, double x4, double y4, double xCirc, double yCirc);

double Distance(double x1, double y1, double z1, double x2, double y2, double z2);

int    A_x(int n, double *C, double **dH, double *Xo);
double detA(int n, double **A);
int    Scale_A(int n, double *X, double **H);
int    x_yT(int n, double *x, double *y, double **A);
double xT_A_y(int n, double *x, double **A, double *y, double **C);
double xT_y(int n, double *x, double *y);

int Gauss(int n, double **A, double *X, double *D);
int Gauss_Jordan(int n, double **A, double *D);

}

#endif // AP_BASIC_MATH_H
