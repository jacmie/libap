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
void Discretization(int n, int paneling_type, REAL factor, REAL maxVal, std::vector <REAL> &Val)
{
    REAL di = 1.0/(n-1);
    REAL CosPart, LinearPart;
	
	REAL dL, Scale = 1;
	REAL dL1, dL2;

    for(int i=0; i<n; i++)
    {															//Wing Span Paneling
		LinearPart = di*i;							  	      	//*  *  *  *  *  *
	
		//dL = i/(n - 1.0);
		
		dL = pow(i/(n - 1.0), Scale) / pow((n - 1.0)/(n - 1.0), Scale);
		//Val.push_back(dL);		
    }
   
	clog << "n = " << n << endl;
	clog << "r = " << n%2 << endl;

	unsigned int r = n%2;
	
	n *= 0.5;
//	n += r;
	
	if(r)
		n += 1;
	
	clog << "n = " << n << endl;

	for(int i=0; i<n-r; i++)
    {
		if(r)
			dL = pow(i/(n - 1.0), Scale) / pow((n - 1.0)/(n - 1.0), Scale);
		else
			dL = pow(i/(n - 0.5), Scale) / pow((n - 0.5)/(n - 0.5), Scale);
		
		Val.push_back(dL - 1.0);		
    }
	
	for(int i=0; i<n; i++)
    {
		clog << n - i - 1 << endl;
		Val.push_back( - Val[n - i - 1] );		

		clog << endl;
    }
	
	for(unsigned int i=0; i<Val.size(); i++)
	{
		Val[i] += 1; 
		Val[i] *= 0.5*maxVal; 
	}
}

template void Discretization <float> (int n, int paneling_type, float factor, float maxVal, std::vector <float> &Val);
template void Discretization <double> (int n, int paneling_type, double factor, double maxVal, std::vector <double> &Val);
