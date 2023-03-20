// Part of All Purpose - ap library

#include "ap_naca.h"

#include <cmath>
#include <iostream>
#include <string.h>

namespace ap
{
	// Check to see if this is a valid name for an NACA section
	std::string NACA_AIRFOIL::CheckName(std::string &name)
	{
   		// Trim off possible leading "naca" 
	   	std::size_t pos = name.find("naca");
  		if (pos != std::string::npos) name = name.substr(pos+4);
   
		// Trim off possible leading "NACA"
   		pos = name.find("NACA");
	  	if (pos != std::string::npos) name = name.substr(pos+4);
   
	   	// Remove any front/back white spaces
		name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
		name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);
   	
		unsigned int len = name.length();

	   	if(len < 4 || len > 5) return 0;
   
	   	if(len == 4) {
    	  	// Need all to be numeric
      		for(unsigned int i = 0; i<name.size(); i++) {
	 			if(!isdigit(name[i])) return 0;
			}
   		}
	   	else {
    	  	// First digit has to be 2, 3, 4, 6 
      		if(!strchr("2346", name[0])) return 0;

	      	// Second digit has to be 12345, except if the first digit is [346]
    	  	// then the second can only be [234]
      		if(name[1] < '1' || name[1] > '5') return 0;
	      	if(strchr("346", name[0])) { if(!strchr("234", name[1])) return 0; }

    	  	// Third digit has to be 0 or 1
      		if(name[2] < '0' || name[2] > '1') return 0;

	      	// Last two need to be numeric
		    if(!isdigit(name[3]) || !isdigit(name[4])) return 0;
   		}

	   	return name;
	}
	
	#define dig(c) ((c)-'0')

	bool NACA_AIRFOIL::GetParams(const std::string &name)
	{
	   	A_[0] = 0.2969;
	   	A_[1] = -0.126;
	   	A_[2] = -0.3516;
	   	A_[3] = 0.2843;
   
	   	if( data_.iTE0 == 0 ) 	A_[4] = -0.1015;
   		else					A_[4] = -0.1036;
   
	   	data_.name = name;
   		if(name.length() == 4) {
      		data_.serie = FOUR_DIGIT;
	      	data_.maxor = dig(name[0])/100.0;
	      	data_.posmax = dig(name[1])/10.0;
      		data_.thmax = 0.01*stoi(name.substr(2)); 
	    }
   		else {
      		int d1, d2, d3;

	      	data_.serie = FIVE_DIGIT;
    	  	data_.thmax = 0.01*stoi(name.substr(3));
      		d1 = dig(name[0]); 
	      	d2 = dig(name[1]);
    	  	d3 = dig(name[2]);
      		data_.posmax = d2/20.0;
	      	data_.ireflex = d3;
	
    	  	if( d3 == 0 || d3 == 1 ) {
        		int code = d1*100 + d2*10 + d3;
        		switch (code) {
	        		case 210: data_.maxor=0.0580; data_.k1=361.4; break;
		        	case 220: data_.maxor=0.1260; data_.k1=51.64; break;
    		    	case 230: data_.maxor=0.2025; data_.k1=15.957;break;
        			case 240: data_.maxor=0.2900; data_.k1=6.643; break;
        			case 250: data_.maxor=0.3910; data_.k1=3.23;  break;
        	
		        	case 211: data_.maxor=0.0621; data_.k1=28.51; break; // approximated data from www.pdas.com
    		    	case 221: data_.maxor=0.1300; data_.k1=51.99; break;
        			case 231: data_.maxor=0.2170; data_.k1=15.793;break;
	        		case 241: data_.maxor=0.3180; data_.k1=6.52;  break;
	    	    	case 251: data_.maxor=0.4410; data_.k1=3.191; break;
        	
    	    		default: break;
        		}
      		}
      		else {
				std::clog << "Wrong number of ireflex = " << d3 << std::endl;
				return 1;
        	}
    	}

		return 0;
	}   

	double NACA_AIRFOIL::ytFunc(const double &x, const double &thmax)
	{
   		if (x == 1.0) return 0.0;

	   	double y = A_[4];
	   	for( int i=1; i<4; i++ ) {
			y = y*x + A_[4-i];
	   	}
	   	y = y*x + A_[0] * sqrt(x);
   
	   	return 5. * thmax * y;
	}

	void NACA_AIRFOIL::CamberFour(double *yc, double *slope,
    	  const double &x, const double &maxor, const double &posmax)
	{
   		if (x < posmax) {
      		*yc = maxor/sqr(posmax) * (2.0*posmax*x - sqr(x));
      		*slope = 2*(maxor/posmax) * (1.0-(x/posmax));
   		}
   		else {
      		*yc = maxor/sqr(1.0-posmax) * ( 1 - 2*posmax + 2*posmax*x - sqr(x));
      		*slope = 2*(maxor/sqr(1-posmax))*(posmax-x);
   		}
	}

	void NACA_AIRFOIL::CamberFive(double *yc, double *slope,
	    const double &x, const double &maxor, const double &posmax, const double &k1, const int &iReflex )
	{
    	double d16 = 1.0/6.0;
    
    	if( iReflex ) {
        	double k21 = (3.*sqr(maxor-posmax)-cube(maxor))/(1-maxor);
        	if (x < maxor) {
	        	*yc = d16*k1*(cube(x-maxor) - k21*sqr(1-maxor)*x - cube(maxor)*(x-1) );
    	    	*slope = d16*k1*(3*sqr(x-maxor) - k21*sqr(1-maxor) - cube(maxor) );
        	}
        	else {
        		*yc = d16*k1*(k21*cube(x-maxor) - k21*sqr(1-maxor)*x - cube(maxor)*(x-1));
        		*slope = d16*k1*(3*k21*sqr(x-maxor) - k21*sqr(1-maxor) - cube(maxor) );
        	}
        }
    	else {
	        if (x < maxor) {
    	    	*yc = d16*k1*(cube(x) - 3.0*maxor*sqr(x) + sqr(maxor)*(3.0-maxor)*x);
        		*slope = d16*k1*( 3.0*sqr(x) - 6.0*maxor*x + sqr(maxor)*(3.0-maxor) );
        	}
        	else {
        		*yc = d16*k1*cube(maxor)*(1.0-x);
        		*slope = d16*k1*cube(maxor);
        	}
        }
	}

	void NACA_AIRFOIL::OutPoint(double x, double yc, double yt, double slope, int is_upper)
	{
   		double xloc, yloc, h;
 
	   	h = sqrt(1+sqr(slope));
   		if (is_upper) {
      		xloc = x  - yt*slope/h;
	      	yloc = yc + yt/h;
   		}
   		else {
      		xloc = x  + yt*slope/h;
      		yloc = yc - yt/h;
   		}
   		
   		x_.push_back(xloc);
		z_.push_back(yloc);
	}

	void NACA_AIRFOIL::DrawSurface(int ndiv)
	{
		x_.resize(0);
		z_.resize(0);

	   	double ainc = M_PI / (ndiv-1);
	   	int i=0, inc=1;
	   	double x, yt, yc, slope;
 
	   	while (i >= 0) {
			x  = 0.5 + cos(i*ainc)/2.0;
      		yt = ytFunc(x, data_.thmax);

	      	if(data_.serie == FOUR_DIGIT) {
				CamberFour(&yc, &slope, x, data_.maxor, data_.posmax);
		  	}
    	  	else {
			 	CamberFive(&yc, &slope, x, data_.maxor, data_.posmax, data_.k1, data_.ireflex); 
		  	}

    	  	OutPoint(x, yc, yt, slope, inc==1);
      
	  		if (i >= ndiv-1 && inc == 1) {
				i--; // to avoid doubled LE points 
			 	inc = -1;
			}
    	  	else i += inc;
   		}
	}

	int NACA_AIRFOIL::GenerateNaca(std::string sNACA, unsigned int set_n)
	{
		std::string name = CheckName(sNACA);

		if(0 == name.length()) {
			std::clog << sNACA << " is not a valid NACA section name!!!" << std::endl;
			return 1;
		}

	   	if( GetParams(name) ) return 1;
   		DrawSurface(set_n);
   
	   	return 0;
	}
}
