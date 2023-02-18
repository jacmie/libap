/*********************************************************************/
/*                                                                   */
/*                Panukl package - (C) TGG 2002                      */
/*             Config files library - (C) TGG 2015                   */
/*                                                                   */
/*********************************************************************/
/*                          Warszawa, 2020                           */
/*********************************************************************/
/*                                                                   */
/* File: naca.h                                                      */
/*                                                                   */
/* Author: T.Grabowski                                               */
/*                                                                   */
/* Contents - NACA_PROFILE class - declaration                       */
/*                                                                   */
/* Last update: 21.11.2020                                           */
/*                                                                   */
/*********************************************************************/
/*                                                                   */

/*
 * naca.h 
 *
 * Created by Alexandre Naaman (hoser@step.polymtl.ca)  30-08-1995
 * Code clean-up, modifications to include more 5-digit sections: 
 * Shamim Mohamed (shamim@synopsys.com) Sept. 8 95
 * corrected & modified to encapsulate into C++ class 
 * by Tomasz Grabowski (tgrab@meil.pw.edu.pl) Jan. 2012
 * included to PanuklConfigLib 20.11.2020
 */

#ifndef AP_NACA_H
#define AP_NACA_H

#include <cstdio>
#include <cmath>
#include <cctype>

#include <string>

//#include "memfun.h"

enum series { four_digit, five_digit };

/// A struct containing airfoil data

struct NACA_AIRFOIL_DATA 
{
   const char *name;     ///< 4- or 5-digit airfoil code
   double      maxor;    ///< the maximum camber
   double      posmax;   ///< the location of maximum camber
   double      thmax;    ///< the maximum thickness
   double      k1;       ///< constant to determine the desired lift coefficient (5-digit serie)
   enum series serie;    ///< type of serie - 4- or 5-digit
   int         ireflex;  ///< reflex flag - if ireflex = 1, Cm should be close to 0 (5-digit serie)
   int         iTE0;     ///< trailing edge flag, 1 - TE thickness equal to zero
};

/** NACA_PROFILE class to generate 4-digit and 5-digit naca airfoils \n
    \n
    Created by Alexandre Naaman (hoser@step.polymtl.ca)  30-08-1995 \n
    Code clean-up, modifications to include more 5-digit sections: \n
    Shamim Mohamed (shamim@synopsys.com) 8-09-1995 \n
    corrected & modified to encapsulate into C++ class \n
    by Tomasz Grabowski (tgrab@meil.pw.edu.pl) Jan.2012 \n
    included to PanuklConfigLib 20.11.2020
*/


class NACA_PROFILE
{
private:
	
	double A[5];
	
	NACA_AIRFOIL_DATA data;
	
	int iWrite;
	int iLicz;

	double sqr(double x) { return x*x; };
	double cube(double x) { return x*x*x; };
	
	double xcoord( double angle);
	double ytfunc( double x, double thmax );

	void camber_four(double *yc, double *slope, double x, double maxor, double posmax);
	void camber_five(double *yc, double *slope, double x, double maxor, double posmax, double k1, int iReflex);

	void out_point(double x, double yc, double yt, double slope, int is_upper, FILE *fp);

	void get_params(struct NACA_AIRFOIL_DATA *data, std::string name);

	void draw_surface(int ndiv, const struct NACA_AIRFOIL_DATA *data, FILE *fp);

	std::string check_name(std::string name);
	
	void ClearTabs( void );
	void CreateTabs( int nn );

public:
	
	NACA_PROFILE(void){ X=Z=0; };
	~NACA_PROFILE(void);
  
	int generate_naca(std::string name, int num, FILE *fp);  		///< generates naca airfoil coordinates (NN points) and stores it in file defined by stream "fp"
	int generate_naca(std::string file_name, std::string NACA);   	///< generates naca airfoil coordinates (NN points) and stores it in file "file_name"
	int generate_naca(std::string cNACA, int NN=100);        		///< generates naca airfoil coordinates (NN points) and stores it in vectores X and Z
	
	void setTE0( int TE = 1 )/** TE=1 forces the zero thickness trailing edge*/{ data.iTE0 = TE; };

	double *X;	///< x coordinates vector
	double *Z;	///< z coordinates vecotr
	int N;		///< coordiantes vectors' size
};

#endif /*AP_NACA_H*/
