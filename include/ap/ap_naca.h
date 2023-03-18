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

#include <vector>
#include <string>

enum series { four_digit, five_digit };

/// A struct containing airfoil data

struct NACA_AIRFOIL_DATA 
{
	std::string name;     ///< 4- or 5-digit airfoil code
   	double      maxor;    ///< the maximum camber
   	double      posmax;   ///< the location of maximum camber
   	double      thmax;    ///< the maximum thickness
   	double      k1;       ///< constant to determine the desired lift coefficient (5-digit serie)
   	enum series serie;    ///< type of serie - 4- or 5-digit
   	int         ireflex;  ///< reflex flag - if ireflex = 1, Cm should be close to 0 (5-digit serie)
   	int         iTE0 = 1; ///< trailing edge flag, 1 - TE thickness equal to zero
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

class NACA_AIRFOIL
{
	double A_[5];
	NACA_AIRFOIL_DATA data_;

	std::vector <double> x_;	///< x coordinates vector
	std::vector <double> z_;	///< z coordinates vecotr

	double sqr(double x) { return x*x; };
	double cube(double x) { return x*x*x; };
	
	double ytfunc( double x, double thmax );

	void camber_four(double *yc, double *slope, double x, double maxor, double posmax);
	void camber_five(double *yc, double *slope, double x, double maxor, double posmax, double k1, int iReflex);

	void OutPoint(double x, double yc, double yt, double slope, int is_upper);

	void GetParams(std::string name);

	void DrawSurface(int ndiv);

	std::string CheckName(std::string name);

public:

	//! Default constructor
	NACA_AIRFOIL() = default;

	//! Forces zero thickness trailing edge
	void SetTE0(bool TE = true) { data_.iTE0 = TE; };

 	//! Generates NACA airfoil coordinates and stores it in vectores x and z
	int GenerateNaca(std::string sNACA, unsigned int set_n=100);

	//! Gets vector of x coordinates
	std::vector <double> GetXvector() { return x_; }
	
	//! Gets vector of z coordinates
	std::vector <double> GetZvector() { return z_; }
	
	//! Gets vectors x and z coordinates
	void GetVectors(std::vector <double> &get_x, std::vector <double> &get_z) { get_x = x_; get_z = z_; }
};

#endif // AP_NACA_H
