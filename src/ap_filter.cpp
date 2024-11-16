#define _USE_MATH_DEFINES

#include <fstream>
#include <cmath>

#include "ap_filter.h"

namespace ap {

FILTER::FILTER(int array_n, int filter_n, double amplitude) {
	//*** Init parameters ***
	
	n  = array_n;
	fn = filter_n;
	
	filter.resize(fn);
	xFiltered.assign(n, 0.0);
	
	//*** Make filter ***
	
    fn += 2;
    
    double del = 2*M_PI/(fn-1);
    
    double sum = 0;
    
    for(int i=1; i<fn-1; i++) {
        filter[i-1] = amplitude*0.5*(1-cos(i*del));
        sum += filter[i-1];
    }
   
    for(int i=1; i<fn-1; i++) {
        filter[i-1] /= sum;
	}

	fn -= 2;
}

int FILTER::Filter(std::vector <double> &xInput, bool overwrite) {
	if(fn > n) return 1;
	
    int findicator;
	
	bool   filt_edge;
    double filt_sum;
	
    for(int i=0; i<n; i++)
    {
		filt_edge = 0;
		filt_sum  = 0;
        xFiltered[i] = 0;
        
        for(int f=0; f<fn; f++) {
            findicator = i - int(0.5*fn) + f;
            
            if(0 <= findicator && findicator < n) {
                xFiltered[i] += filter[f]*xInput[findicator];
            }
			
			else {
				filt_edge = 1;
				filt_sum += filter[f];
			}
        }
       
		if(filt_edge)
			xFiltered[i] /= (1-filt_sum);
    }
	
	if(overwrite) {
		for(int x=0; x<n; x++) xInput[x] = xFiltered[x]; 
	}

	return 0;
}

int FILTER::FilterRange(int shift, double *xInput, bool overwrite) {
	if(fn > n) return 0;
	
	std::vector <double> xIn;
	
	for(int x=0; x<n; x++) { //"n" limits range
		xIn.push_back(xInput[shift + x]); 
	}
	
    Filter(xIn, overwrite);
    
	if(overwrite) {
		for(int x=0; x<n; x++) xInput[x + shift] = xIn[x];
	}

	return 1;
}

void FILTER::Print(std::ofstream &out) {
	for(int x=0; x<n; x++)
        out << x << "\t" << xFiltered[x] << std::endl;
}

} // namespace ap
