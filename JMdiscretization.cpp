#include "JMdiscretization.h"

using namespace std;

void Discretization(int n, int paneling_type, double factor, double maxVal, double *Val)
{
    double di = 1.0/(n-1);
    double CosPart, LinearPart;
	
    for(int i=0; i<n; i++)
    {															//Wing Span Paneling
		LinearPart = di*i;							  	      	//*  *  *  *  *  *
		
		switch (paneling_type)
		{
			case 0:
				CosPart =      1 - cos(           0.5*M_PI*i/(n-1));  	//** *  *   *   * (left)
				break;
			default:
			case 1:
				CosPart = 0.5*(1 - cos(               M_PI*i/(n-1))); 	//** *  *  * * ** (center)
				break;
        	case 2:
				CosPart =          cos(0.5*M_PI - 0.5*M_PI*i/(n-1));  	//*   *   *  * ** (right)
				break;
		}
		
		Val[i] = maxVal*( factor*CosPart + (1-factor)*LinearPart );		
    }
}

template <class REAL> 
bool Discretization(unsigned int n, REAL factor, std::vector <REAL> &Val, bool paneling_type, REAL maxVal)
{
	if(factor <= 0)
	{
		clog << "Factor has to be bigger than 0!!!" << endl;
		return 1;
	}

	if(paneling_type == 0) // One side
	{
    	for(unsigned int i=0; i<n; i++)
		{
			Val.push_back( maxVal*pow(i/(n - 1.0), factor) );		
    	}
	}

	else // Central
	{
		REAL dL;
		unsigned int r = n%2;
	
		n *= 0.5;
		if(r)
			n += 1;

		// --- Generate Left part ---

		for(unsigned int i=0; i<n-r; i++)
	    {
			if(r)
			{
				dL = pow(i/(n - 1.0), factor);
			}
		
			else
			{
				dL = pow(i/(n - 0.5), factor);
			}
		
			Val.push_back(dL - 1.0);		
   	 	}
	
		// --- Copy Left to Right part ---
		 
		for(unsigned int i=0; i<n; i++)
    	{
			Val.push_back( -Val[n - i - 1] );		
    	}
	
		// --- Translate & Scale --- 

		for(unsigned int i=0; i<Val.size(); i++)
		{
			Val[i] += 1; 
			Val[i] *= 0.5*maxVal; 
		}
	}

	return 0;
}

template bool Discretization <float> (unsigned int n, float factor, std::vector <float> &Val, bool paneling_type, float maxVal);
template bool Discretization <double> (unsigned int n, double factor, std::vector <double> &Val, bool paneling_type, double maxVal);
