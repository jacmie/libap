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
	
	REAL dL, Scale = 1.5;
	REAL dL1, dL2;

    for(int i=0; i<n; i++)
    {															//Wing Span Paneling
		LinearPart = di*i;							  	      	//*  *  *  *  *  *
	
		//dL = i/(n - 1.0);
		
		dL = pow(i/(n - 1.0), Scale) / pow((n - 1.0)/(n - 1.0), Scale);
/*
		switch (paneling_type)
		{
			case 0:
				CosPart =      1 - cos(           0.5*M_PI*dL);  	//** *  *   *   * (left)
				break;
			default:
			case 1:
				CosPart = 0.5*(1 - cos(               M_PI*dL)); 	//** *  *  * * ** (center)
				break;
        	case 2:
				CosPart =          cos(0.5*M_PI - 0.5*M_PI*dL);  	//*   *   *  * ** (right)
				break;
		}
*/		
		//Val.push_back( maxVal*( factor*CosPart + (1-factor)*LinearPart ) );		
		//Val.push_back( maxVal*CosPart );		
		Val.push_back( maxVal*dL );		

		clog << endl;
    }
   /* 
	for(int i=0; i<n; i++)
    {
		dL1 = pow(i/(n - 1.0), Scale) / pow((n - 1.0)/(n - 1.0), Scale);
		
		Val.push_back( maxVal*dL );		

		clog << endl;
		
		dL2 = pow(i/(n - 1.0), 1/Scale) / pow((n - 1.0)/(n - 1.0), 1/Scale);
		
		Val.push_back( maxVal*(dL1 + dL2)*0.5 );		

		clog << endl;
    }*/
}

template void Discretization <float> (int n, int paneling_type, float factor, float maxVal, std::vector <float> &Val);
template void Discretization <double> (int n, int paneling_type, double factor, double maxVal, std::vector <double> &Val);
