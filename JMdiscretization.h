#ifndef _DISCR_H_
#define _DISCR_H_

#include <math.h>
#include <vector>

#include <iostream>

void Discretization(int n, int paneling_type, double factor, double maxVal, double *Val);

template <class REAL> 
bool Discretization(unsigned int n, REAL factor, std::vector <REAL> &Val, bool paneling_type=0, REAL maxVal=1.0);

#endif
