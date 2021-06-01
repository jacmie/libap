#ifndef _DISCR_H_
#define _DISCR_H_

#include <math.h>
#include <vector>

#include <iostream>

enum discretization_type {LEFT, CENTER, RIGHT, LINEAR};

void Discretization(int n, int paneling_type, double factor, double maxVal, double *Val);

template <class REAL> 
void Discretization(int n, int paneling_type, REAL factor, REAL maxVal, std::vector <REAL> &Val);

#endif
