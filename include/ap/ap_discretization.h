#ifndef _DISCR_H_
#define _DISCR_H_

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>

void Discretization(int n, int paneling_type, double factor, double maxVal, double *Val);

template <class REAL> 
bool Discretization(unsigned int n, REAL factor, std::vector <REAL> &Val, bool paneling_type=0, REAL maxVal=1.0);

#endif
