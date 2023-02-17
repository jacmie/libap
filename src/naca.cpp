/*********************************************************************/
/*                                                                   */
/*                Panukl package - (C) TGG 2002                      */
/*             Config files library - (C) TGG 2015                   */
/*                                                                   */
/*********************************************************************/
/*                          Warszawa, 2020                           */
/*********************************************************************/
/*                                                                   */
/* File: naca.cpp                                                    */
/*                                                                   */
/* Author: T.Grabowski                                               */
/*                                                                   */
/* Contents - NACA_PROFILE class - definition                        */
/*                                                                   */
/* Last update: 21.11.2020                                           */
/*                                                                   */
/*********************************************************************/
/*                                                                   */

/*
 * naca.cpp 
 *
 * Created by Alexandre Naaman (hoser@step.polymtl.ca)  30-08-1995
 * Code clean-up, modifications to include more 5-digit sections: 
 * Shamim Mohamed (shamim@synopsys.com) Sept. 8 95
 * corrected & modified to encapsulate into C++ class 
 * by Tomasz Grabowski (tgrab@meil.pw.edu.pl) Jan. 2012
 * included to PanuklConfigLib 20.11.2020
 */

#include "naca.h"

double NACA_PROFILE::xcoord(double angle)
{
   return 0.5 + cos(angle)/2.0;
}

double NACA_PROFILE::ytfunc(double x, double thmax)
{
   if (x == 1.0) return 0.0;

   double y = A[4];
   for( int i=1; i<4; i++ )
	y = y*x + A[4-i];
   y = y*x + A[0] * sqrt(x);
   
   return 5. * thmax * y;

//   return thmax * (1.4845*sqrt(x) - 0.63*x - 1.758*sqr(x)+
//		       1.4215*cube(x) - 0.5075*sqr(sqr(x)));
}

void NACA_PROFILE::camber_four(double *yc, double *slope,
      double x, double maxor, double posmax)
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

void NACA_PROFILE::camber_five(double *yc, double *slope,
	    double x, double maxor, double posmax, double k1, int iReflex )
{
    double d16 = 1.0/6.0;
    
    if( iReflex )
        {
        double k21 = (3.*sqr(maxor-posmax)-cube(maxor))/(1-maxor);
        if (x < maxor) 
        	{
        	*yc = d16*k1*(cube(x-maxor) - k21*sqr(1-maxor)*x - cube(maxor)*(x-1) );
        	*slope = d16*k1*(3*sqr(x-maxor) - k21*sqr(1-maxor) - cube(maxor) );
        	}
        else 
        	{
        	*yc = d16*k1*(k21*cube(x-maxor) - k21*sqr(1-maxor)*x - cube(maxor)*(x-1));
        	*slope = d16*k1*(3*k21*sqr(x-maxor) - k21*sqr(1-maxor) - cube(maxor) );
        	}
        }
    else
        {
        if (x < maxor) 
        	{
        	*yc = d16*k1*(cube(x) - 3.0*maxor*sqr(x) + sqr(maxor)*(3.0-maxor)*x);
        	*slope = d16*k1*( 3.0*sqr(x) - 6.0*maxor*x + sqr(maxor)*(3.0-maxor) );
        	}
        else 
        	{
        	*yc = d16*k1*cube(maxor)*(1.0-x);
        	*slope = d16*k1*cube(maxor);
        	}
        }
}

void NACA_PROFILE::out_point(double x, double yc, double yt, double slope, int is_upper, FILE *fp)
{
   double xloc, yloc, h;
 
#ifdef Debug
   fprintf(stderr, " >>> x: %.4g\tcamber: %.3g\tthickness: %.3g\n", x, yc, yt);
#endif

   h = sqrt(1+sqr(slope));
   if (is_upper) {
      xloc = x - yt*slope/h;
      yloc = yc + yt/h;
   }
   else {
      xloc = x + yt*slope/h;
      yloc = yc - yt/h;
   }
   /* Save results into file */
   if( iWrite )
   	fprintf(fp,"%5.5f %5.5f\n", xloc, yloc);
   else
   	{
   	if( iLicz < N )
   		{
   		X[iLicz] = xloc;
   		Z[iLicz] = yloc;
   		}
   	else
   		fprintf(stderr, "%5.5f %5.5f %d\n", xloc, yloc, iLicz);
   	iLicz++;
   	}
}

#define dig(c) ((c)-'0')

void NACA_PROFILE::get_params(struct NACA_AIRFOIL_DATA *data, const char *name)
{
   A[0] = 0.2969;
   A[1] = -0.126;
   A[2] = -0.3516;
   A[3] = 0.2843;
   
   if( data->iTE0 == 0 )
       A[4] = -0.1015;
   else				
       A[4] = -0.1036;
   
   data->name = name;
   if(strlen(name) == 4) 
      {
      data->serie = four_digit;
      data->maxor = dig(name[0])/100.0;
      data->posmax = dig(name[1])/10.0;
      data->thmax = atoi(name+2)/100.0;
      }
   else 
      {
      int d1, d2, d3;

      data->serie = five_digit;
      data->thmax = atoi(name+3)/100.0;
      d1 = dig(name[0]); 
      d2 = dig(name[1]);
      d3 = dig(name[2]);
      data->posmax = d2/20.0;
      data->ireflex = d3;
	
      if( d3 == 0 || d3 == 1 ) 
      	{
        int code = d1*100 + d2*10 + d3;
        switch (code) 
        	{
        	case 210: data->maxor=0.0580; data->k1=361.4; break;
        	case 220: data->maxor=0.1260; data->k1=51.64; break;
        	case 230: data->maxor=0.2025; data->k1=15.957;break;
        	case 240: data->maxor=0.2900; data->k1=6.643; break;
        	case 250: data->maxor=0.3910; data->k1=3.23;  break;
        	
        	case 211: data->maxor=0.0621; data->k1=28.51; break;		// approximated data from www.pdas.com
        	case 221: data->maxor=0.1300; data->k1=51.99; break;
        	case 231: data->maxor=0.2170; data->k1=15.793;break;
        	case 241: data->maxor=0.3180; data->k1=6.52;  break;
        	case 251: data->maxor=0.4410; data->k1=3.191; break;
        	
        	default: break;
        	}
      	}
      else
        {
        fprintf(stderr, "wrong number ireflex = %d\n", d3 );
        }
      }
}      

void NACA_PROFILE::draw_surface(int ndiv, const struct NACA_AIRFOIL_DATA *data, FILE *fp)
{
   double ainc = M_PI / (ndiv-1);
   int i=0, inc=1;
   double x, yt, yc, slope;
 
   while (i >= 0) 
      {
      x = xcoord(i * ainc);
      yt = ytfunc(x, data->thmax);
      if (data->serie == four_digit)
		 camber_four(&yc, &slope, x, data->maxor, data->posmax);
      else
		 camber_five(&yc, &slope, x, data->maxor, data->posmax, data->k1, data->ireflex); 
      out_point(x, yc, yt, slope, inc==1, fp);
      if (i >= ndiv-1 && inc == 1)
	     {
		 i--; 			// to avoid doubled LE points 
		 inc = -1;
		 }
      else
		 i += inc;
      }
}

/*
 * Check to see if this is a valid name for an NACA section
 */
char* NACA_PROFILE::check_name(char *name)
{
   int len;

   /* Trim off a leading NACA or naca */
   if(!strncmp(name, "NACA", 4) || !strncmp(name, "naca", 4))
      name += 4;

   len = strlen(name);

   if(len < 4 || len > 5) {
      return 0;
   }
   
   if(len == 4) {
      /* Need to all be numeric */
      int i;
      for(i = 0; i < 4; i++) 
	 if(!isdigit(name[i]))
	    return 0;
   }
   else {
      /* Ok, first digit has to be 2, 3, 4, 6 */
      if(!strchr("2346", name[0]))
	 return 0;

      /* Second digit has to be 12345, except if the first digit is [346]
      // then the second can only be [234] */
      if(name[1] < '1' || name[1] > '5')
	 return 0;
      if(strchr("346", name[0]))
	 if(!strchr("234", name[1]))
	    return 0;

      /* Third digit has to be 0 or 1 */
      if(name[2] < '0' || name[2] > '1')
	 return 0;

      /* last two need to be numeric */
      if(!isdigit(name[3]) || !isdigit(name[4]))
	 return 0;
   }
   return name;
}

int NACA_PROFILE::generate_naca(char* cNACA, int NN)
{
	N = 2*NN - 1; // must be odd
	CreateTabs( N );

	char *cname;

	if(!(cname = check_name(cNACA))) 
		{
		fprintf(stderr, "%s is not a valid NACA section name.\n", cNACA );
		return -1;
		}
	else
		{
		fprintf( stderr, "NACA %s - cname %s\n", cNACA, cname );
		}

   iWrite = 0;
   iLicz = 0;

   get_params(&data, cname);
   
   draw_surface(NN, &data, stderr);
   
   return 0;
}

int NACA_PROFILE::generate_naca(char *file_name, char* cNACA)
{
	FILE *fp = fopen( file_name, "w" );
	
	char *cname;

	if(!(cname = check_name(cNACA))) 
		{
		fprintf(stderr, "%s is not a valid NACA section name.\n", cNACA );
		return -1;
		}
	else
		{
		fprintf( stderr, "NACA %s - cname %s\n", cNACA, cname );
		}

	return generate_naca(cname, 160, fp);
}

int NACA_PROFILE::generate_naca(char *name, int num, FILE *fp)
{
   iWrite = 1;

   get_params(&data, name);
   
   fprintf(fp, "NACA %s\n", name);

#ifdef Debug
   fprintf(stderr, "%s:\n  camber: %g\n   thickness: %g\n   max_camber_pos: %g\n   series: %s\n",
	   data.name, data.maxor, data.thmax, data.posmax,
	   ((data.serie == four_digit)? "four digit" : "five digit"));
#endif
    
   draw_surface(num, &data, fp);
   
   fclose (fp);
   
   return 0;
}

void NACA_PROFILE::ClearTabs( void )
{
	DELETE_TAB( X );
	DELETE_TAB( Z );
}

void NACA_PROFILE::CreateTabs( int nn )
{
	ClearTabs();
	X = new double[nn];
	Z = new double[nn];
}

NACA_PROFILE::~NACA_PROFILE(void)
{
	ClearTabs();
}
