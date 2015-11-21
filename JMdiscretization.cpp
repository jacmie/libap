#include <math.h>

#include <iostream>
using namespace std;

void Discretization(int n, int paneling_type, double factor, double maxVal, double *Val)
{
    double di = 1.0/(n-1);
    double CosPart, LinearPart;
	
	cout << di << endl << endl;
	
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