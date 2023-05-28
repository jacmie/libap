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

//! Rotate 2D point 
/*!
 * \param angRad - angle of rotation in radians
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 */
void RotatePointRad(double angRad, double &x, double &y);

//! Rotate 2D point 
/*!
 * \param angDeg - angle of rotation in degrees
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 */
void RotatePointDeg(double angDeg, double &x, double &y);

//! Rotate 2D point 
/*!
 * \param angRad - angle of rotation in radians
 * \param xRef - reference point x coordinate about which rotation is done
 * \param yRef - reference point x coordinate about which rotation is done
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 */
void RotatePointRefRad(double angRad, double xRef, double yRef, double &x, double &y);

//! Rotate 2D point 
/*!
 * \param angDeg - angle of rotation in degrees
 * \param xRef - reference point x coordinate about which rotation is done
 * \param yRef - reference point x coordinate about which rotation is done
 * \param x - returned x coordinate (initial value also used to determin the radius of rotation)
 * \param y - returned y coordinate (initial value also used to determin the radius of rotation)
 */
void RotatePointRefDeg(double angDeg, double xRef, double yRef, double &x, double &y);

//! Get linear function coefficients based on two points
/*!
 * \param x1 - first point x coordinate 
 * \param y1 - first point y coordinate 
 * \param x2 - second point x coordinate 
 * \param y2 - second point y coordinate 
 * \param A - returned A coefficiet of the function
 * \param B - returned B coefficiet of the function
 * \return 0 on success, fails when x1==x2 (vertical line, or point)
 */
bool LinearFunction(double x1, double y1, double x2, double y2, double &A, double &B);

//! Get linear function coefficients based on point and slope angle
/*!
 * \param x1 - reference point x coordinate 
 * \param y1 - reference point y coordinate 
 * \param fiDeg - slope angle in degrees 
 * \param A - returned A coefficiet of the function
 * \param B - returned B coefficiet of the function
 * \return 0 on success, fails when fiDeg==90 || fiDeg==180 (vertical line) 
 */
bool LinearFunction(double x1, double y1, double fiDeg, double &A, double &B);

//! Linear functions intersection
/*!
 * \param A1 - first linear function A coefficient 
 * \param B1 - first linear function B coefficient 
 * \param A2 - second linear function A coefficient 
 * \param B2 - second linear function B coefficient 
 * \param x - returned x coordinate of the intersection
 * \param y - returned y coefficiet of the intersection
 * \return 0 on success, fails when A1==A2 (parallel lines)
 */
bool LinesIntersection(double A1, double B1, double A2, double B2, double &x, double &y);

//! Get parabola coefficients based on two points and slope in point
/*!
 * \param x1 - first point x coordinate 
 * \param y1 - first point y coordinate 
 * \param x2 - second point x coordinate 
 * \param y2 - second point y coordinate 
 * \param x3 - slope x coordinate (can be the same as x1, or x2)
 * \param yPrim - slope at the x3 
 * \param A - returned A coefficiet of the function
 * \param B - returned B coefficiet of the function
 * \param C - returned C coefficiet of the function
 */
void Parabola(double x1, double y1, double x2, double y2, double x3, double yPrim, double &A, double &B, double &C);

//! Get circle coefficients and radius based on three points
/*!
 * \param x1 - first point x coordinate 
 * \param y1 - first point y coordinate 
 * \param x2 - second point x coordinate 
 * \param y2 - second point y coordinate 
 * \param x3 - third point x coordinate 
 * \param y3 - third point y coordinate 
 * \param A - returned A coefficiet of the circle
 * \param B - returned B coefficiet of the circle
 * \param R - returned radius of the circle
 */
void Circle(double x1, double y1, double x2, double y2, double x3, double y3, double &A, double &B, double &R);

//! Arc aproximation with bezier curve 
/*!
 * Third order (4 points) bezier curve aproximates arc. The arc has to have less than 90deg. 
 * \param x1 - first point x coordinate, beggining of the arc and the bezier curve
 * \param y1 - first point y coordinate, beggining of the arc and the bezier curve 
 * \param x2 - returned second point x coordinate 
 * \param y2 - returned second point y coordinate 
 * \param x3 - returned third point x coordinate 
 * \param y3 - returned third point y coordinate 
 * \param x4 - returned fourth point x coordinate, end of the arc and the bezier curve 
 * \param y4 - returned fourth point y coordinate, end of the arc and the bezier curve 
 * \param xCirc - circle center x coordinate 
 * \param yCirc - circle center y coordinate 
 * \return 0 on success
 */
bool Arc2Bezier(double x1, double y1, double &x2, double &y2, double &x3, double &y3, double x4, double y4, double xCirc, double yCirc);

//! Distance between two points 
/*!
 * \param x1 - first point x coordinate
 * \param y1 - first point y coordinate 
 * \param z1 - first point z coordinate 
 * \param x2 - second point x coordinate 
 * \param y2 - second point y coordinate 
 * \param z2 - second point z coordinate 
 * \note Use z=0 to compute distance in 2D space  
 * \return Distance value between two points.
 */
double Distance(double x1, double y1, double z1, double x2, double y2, double z2);

//! Multiply matrix by vector 
int    A_x(int n, double *C, double **dH, double *Xo);

//! Compute matrix determinant 
double detA(int n, double **A);

//! Scale matrix
int    Scale_A(int n, double *X, double **H);

//! Multiply vector by vector 
int    x_yT(int n, double *x, double *y, double **A);

//! Multiply vector-matrix-vector 
double xT_A_y(int n, double *x, double **A, double *y, double **C);

//! Multiply vector by vector 
double xT_y(int n, double *x, double *y);

//! Solve linear system of equations with the Gauss method
int Gauss(int n, double **A, double *X, double *D);

//! Solve linear system of equations with the Gauss-Jordan method
int Gauss_Jordan(int n, double **A, double *D);

}

#endif // AP_BASIC_MATH_H
