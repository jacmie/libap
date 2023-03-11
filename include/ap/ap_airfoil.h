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

#ifndef AP_AIRFOIL_H
#define AP_AIRFOIL_H

#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ap_naca.h"

/** AIRFOIL class to manipulate the airfoil geometry or \n
    it can read geometry data from file (5 commonly used fromats)
    or generate 4-digit and 5-digit naca airfoils \n
    Geometry data (coordinates) is stored in the arrays.\n
    included to PanuklConfigLib 20.11.2020
*/

namespace ap
{
	enum recognizeAirfoilBy {AIRFOIL_BY_CONTENT=0, AIRFOIL_BY_EXTENSION};

class AIRFOIL
{
	enum airfoilFileType {PRF_4=0, PRF_3, PRF_2, KOO, XFOIL, L_DAT};

	// 0 - recognition by content, 1 - recognition by filename extention
	int iReadType;	
	
	// local variables (arrays)
	int Nrob;
	double *Xrob, *Zrob;
	
	// read by format
	int Read_PRF_0( std::string fileName );
	int Read_PRF_1( std::string fileName );
	int Read_KOO( std::string fileName );
	int Read_DAT( std::string fileName );
	int Read_DAT_LEDNICER( std::string fileName );	// by Anna Sima

	void ReadRow(int type, std::string &line, double &x1, double &y1, double &x2, double &y2);
	int ReadColumns(const int type, std::stringstream &buffer, 
		std::vector <double> &x1, std::vector <double> &y1, std::vector <double> &x2, std::vector <double> &y2, 
		const unsigned int n1, const unsigned int n2);
	// methods to get file type by a file content or its extension (by Anna Sima)
	int getiTypeByContent( std::string fileName );
	int getiTypeByExt( std::string fileName );

	// methods to provide a valid PRF format
	int Write_PRF( std::string fileName );
	int Write_DAT( std::string fileName );

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

	int ReadStr( FILE * stream, char *Par );
	void ReadStrL( FILE * stream, char *Par , int *len);
	int ReadPar( FILE *stream, const char *Format, void *Par );
	int ReadPar( FILE *stream, const char *Format, void *Par1, void *Par2 );
	int ReadPar( FILE *stream, const char *Format, void *Par1, void *Par2, void *Par3 );
	int ReadPar( FILE * stream, const char * Format, void *Par1, void *Par2, void *Par3, void *Par4 );
	int ReadComm( FILE *stream );
	void ReadDummy( FILE *stream );
	int isstrblank( char *cc, int iLen );
	int nLines( FILE * stream );
	
	std::string cc;
	std::string comment;

protected:
	
	int iRead;   ///< 0 - no data, 1 - data read succesfuly

public:
	
	int Nf;      ///< size of the vectors with geometry data - compatible with Xfoil
	double *Xf;  ///< X coordinates (Nf points)
	double *Zf;  ///< Z coordinates (Nf points)
	
	int N;       ///< size of the vectors with geometry data - 4 column native PANUKL format
	std::vector <double> Xd;  ///< X coordinates of lower contour (N points)
	std::vector <double> Xg;  ///< X coordinates of upper contour (N points)
	std::vector <double> Zd;  ///< Z coordinates of lower contour (N points)
	std::vector <double> Zg;  ///< Z coordinates of upper contour (N points)

	/** File type: \n
	    0 - PRF - PANUKL (prf1) - native PANUKL (4 columns) format \n
	    1 - PRF - prf2 - by L.Wiechers- NAME in header, N below header \n 
	    2 - KOO - koordinate by L.Wiechers \n
	    3 - DAT - SELIG - (Xfoil) \n
	    4 - DAT - LEDNICER
	*/
	int iType;
	
	std::string fileName; ///< filename (without path)
	
	//! prints PRF file (default on stdout)
	void Print( FILE* f=stdout );

	//! reads profile file
	int Read( std::string fileName );

	//! saves profile file - two types are available: \n 0 - native PANUKL (4 columns) \n 3 - SELIG (Xfoil compatible) \n other - no action
	int Write( std::string fileName, int iTyp=0 );
	
	//! returns read status: 0 - no data, 1 - data read succesfuly
	int ReadStatus() { return iRead; }

	//! returns the type of format recognition: \n 0 - recognition by content (default), \n 1 - recognition by filename extention
	int GetReadType() { return iReadType; }

	//! sets the type of format recognition
	void SetReadType( int iRT ) { iReadType = iRT; }
	
	//! generates NACA airfoil given by long int value (e.g. iNACA = 23012), \n NN - the number of points that define the airfoil geometry
	int ReadNaca( long int iNACA, int NN=100 );

	//! generates NACA airfoil given by string (e.g. cNACA = "23012"), \n NN - the number of points that define the airfoil geometry
	int ReadNaca( std::string NACA, int NN=100 );

	//! cleans local variables
	void Clean( void );

	AIRFOIL( void );
	~AIRFOIL( void ){ Clean(); };
};
}

#endif /*AP_AIRFOIL_H*/


