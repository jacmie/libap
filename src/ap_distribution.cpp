#include "ap_distribution.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

namespace ap {

template <class real> 
void sinDistribution(unsigned int n, real factor, std::vector <real> &distrib, int paneling_type, real range)
{
	distrib.resize(0);

    real di = 1.0/(n-1);
    real cosPart, linearPart;
	
    for(unsigned int i=0; i<n; i++) {
		linearPart = di*i;									  	      	//*  *  *  *  *  *
		
		switch (paneling_type) {
			case LEFT:
				cosPart =      1 - cos(           0.5*M_PI*i/(n-1));  	//** *  *   *   * (left)
				break;
			default:
			case CENTER:
				cosPart = 0.5*(1 - cos(               M_PI*i/(n-1))); 	//** *  *  * * ** (center)
				break;
        	case RIGHT:
				cosPart =          cos(0.5*M_PI - 0.5*M_PI*i/(n-1));  	//*   *   *  * ** (right)
				break;
		}
		
		distrib.push_back( range*( factor*cosPart + (1-factor)*linearPart ) );		
    }
}

template <class real> 
bool expDistribution(unsigned int n, real factor, std::vector <real> &distrib, int paneling_type, real range)
{
	distrib.resize(0);

	if(factor <= 0) {
		std::clog << "Factor has to be bigger than 0!!!" << std::endl;
		return 1;
	}

	if(paneling_type != 1) { // One side
    	for(unsigned int i=0; i<n; i++) {
			distrib.push_back( range*pow(i/(n - 1.0), factor) );		
    	}
	}

	else { // Central
		real dL;
		unsigned int r = n%2;
	
		n *= 0.5;
		if(r) n += 1;

		// --- Generate Left part ---

		for(unsigned int i=0; i<n-r; i++) {
			if(r) dL = pow(i/(n - 1.0), factor);
			else dL = pow(i/(n - 0.5), factor);
		
			distrib.push_back(dL - 1.0);		
   	 	}
	
		// --- Copy Left to Right part ---
		 
		for(unsigned int i=0; i<n; i++) {
			distrib.push_back( -distrib[n - i - 1] );		
    	}
	
		// --- Translate & Scale --- 

		for(unsigned int i=0; i<distrib.size(); i++) {
			distrib[i] += 1; 
			distrib[i] *= 0.5*range; 
		}
	}

	return 0;
}

template void sinDistribution <float> (unsigned int n, float factor, std::vector <float> &distrib, int paneling_type, float range);
template void sinDistribution <double> (unsigned int n, double factor, std::vector <double> &distrib, int paneling_type, double range);
template bool expDistribution <float> (unsigned int n, float factor, std::vector <float> &distrib, int paneling_type, float range);
template bool expDistribution <double> (unsigned int n, double factor, std::vector <double> &distrib, int paneling_type, double range);

}
