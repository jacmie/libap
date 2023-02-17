/*********************************************************************/
/*                                                                   */
/*                Panukl package - (C) TGG 2002                      */
/*             Config files library - (C) TGG 2015                   */
/*                                                                   */
/*********************************************************************/
/*                          Warszawa, 2020                           */
/*********************************************************************/
/*                                                                   */
/* File: airfoil.h                                                   */
/*                                                                   */
/* Author: T.Grabowski                                               */
/*                                                                   */
/* Contents - airfoil class                                          */
/*                                                                   */ 
/* Last update: 24.11.2020                                           */
/*                                                                   */
/*********************************************************************/
/*                                                                   */
/*                                                                   */

#ifndef _AIRFOIL_H_
#define _AIRFOIL_H_

#include <cstdio>
#include <cstdlib>
#include <vector>

#include "iofun.h"
#include "memfun.h"
#include "naca.h"

/** AIRFOIL class to manipulate the airfoil geometry or \n
    it can read geometry data from file (5 commonly used fromats)
    or generate 4-digit and 5-digit naca airfoils \n
    Geometry data (coordinates) is stored in the arrays.\n
    included to PanuklConfigLib 20.11.2020
*/

class AIRFOIL : public IOFUN, public MEMFUN 
{
	// 0 - recognition by content, 1 - recognition by filename extention
	int iReadType;	
	
	// local variables (arrays)
	int Nrob;
	double *Xrob, *Zrob;
	
	// read by format
	int Read_PRF_0( char *cFile );
	int Read_PRF_1( char *cFile );
	int Read_KOO( char *cFile );
	int Read_DAT( char *cFile );
	int Read_DAT_LEDNICER( char *cFile );	// by Anna Sima

	// methods to get file type by a file content or its extension (by Anna Sima)
	void getiTypeByContent( char *cFile );
	void getiTypeByExt( char *cFile );

	// methods to provide a valid PRF format
	int Write_PRF( char *cFile );
	int Write_DAT( char *cFile );

	// Transformations
	void PRF2XFOIL( void );
	void XFOIL2PRF( void );
	void TE_correct( void );
	void Check( int *nn, double *X, double *Z );

	// Maths
	double dAverage( double*, int );
	double dmin( double d1, double d2){ return( d2 < d1 ? d2 : d1 ); };
	double dmax( double d1, double d2){ return( d2 > d1 ? d2 : d1 ); };
	double tabmax( double*, int );
	double tabmin( double*, int );
	double dMaxT( double*, int* );
	double dMinT( double*, int* );
	double inter1(double *xx, double *yy, unsigned long n, double x );
	unsigned long locate(double xx[], unsigned long n, double x );
	double apr3( double dX, double *dXX, double *dYY );
	void SortClean( int *N, double *X );
	void Sort1( int N, double dRA[] );
	void Sort2( int iN, double dRA[], double dKOL[], int iOrder );
	bool check_order( double d1, double d2, int iFlag = 0 );
	
	char cc[200];
	char comment[512];

        protected:
	
	int iRead;   ///< 0 - no data, 1 - data read succesfuly

	int iGUI;    ///< GUI flag - messages displayed using wrapping function "alert"
	void (*alert)( char *c ) = NULL;  ///< virtual fuction to display the message (if iGUI > 0)

        public:
	
	int Nf;      ///< size of the vectors with geometry data - compatible with Xfoil
	double *Xf;  ///< X coordinates (Nf points)
	double *Zf;  ///< Z coordinates (Nf points)
	
	int N;       ///< size of the vectors with geometry data - 4 column native PANUKL format
	double *Xd;  ///< X coordinates of lower contour (N points)
	double *Xg;  ///< X coordinates of upper contour (N points)
	double *Zd;  ///< Z coordinates of lower contour (N points)
	double *Zg;  ///< Z coordinates of upper contour (N points)

	/** File type: \n
	    0 - PRF - PANUKL (prf1) - native PANUKL (4 columns) format \n
	    1 - PRF - prf2 - by L.Wiechers- NAME in header, N below header \n 
	    2 - KOO - koordinate by L.Wiechers \n
	    3 - DAT - SELIG - (Xfoil) \n
	    4 - DAT - LEDNICER
	*/
	int iType;
	
	char cName[100];                                   ///< filename (without path)
	
	/// prints PRF file (default on stdout)
	void Print( FILE* f=stdout );
	/// reads profile file
	int Read( char *cFile );
	/// saves profile file - two types are available: \n 0 - native PANUKL (4 columns) \n 3 - SELIG (Xfoil compatible) \n other - no action
	int Write( char *cFile, int iTyp=0 );
	
	/// returns read status: 0 - no data, 1 - data read succesfuly
	int ReadStatus( void ){ return iRead; };           
	/// returns the type of format recognition: \n 0 - recognition by content (default), \n 1 - recognition by filename extention
	int GetReadType( void ) { return iReadType; };
	/// sets the type of format recognition
	void SetReadType( int iRT ) { iReadType = iRT; };  
	
	/// generates NACA airfoil given by long int value (e.g. iNACA = 23012), \n NN - the number of points that define the airfoil geometry
	int ReadNaca( long int iNACA, int NN=100 );
	/// generates NACA airfoil given by string (e.g. cNACA = "23012"), \n NN - the number of points that define the airfoil geometry
	int ReadNaca( char* cNACA, int NN=100 );
	/// cleans local variables
	void Clean( void );

	AIRFOIL( void );
	~AIRFOIL( void ){ Clean(); };
};

#endif /*_AIRFOIL_H_*/


