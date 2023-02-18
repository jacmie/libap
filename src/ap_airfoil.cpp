/*********************************************************************/
/*                                                                   */
/*                Panukl package - (C) TGG 2002                      */
/*             Config files library - (C) TGG 2015                   */
/*                                                                   */
/*********************************************************************/
/*                          Warszawa, 2020                           */
/*********************************************************************/
/*                                                                   */
/* File: airfoil.cpp                                                 */
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

#include <regex>
#include <algorithm>
#include <iostream>

#include "ap_airfoil.h"

using namespace std;

AIRFOIL::AIRFOIL( void )
{
	Xd = 0;
	Xg = 0;
	Zd = 0;
	Zg = 0;
	Xf = 0;
	Zf = 0;
	Xrob = 0;
	Zrob = 0;
	N = 0;
	Nf = 0;
	Nrob = 0;

	/* Types:
	    0 - PRF - PANUKL (prf1) - native PANUKL (4 columns) format \n
	    1 - PRF - prf2 - by L.Wiechers- NAME in header, N below header \n 
	    2 - KOO - koordinate by L.Wiechers \n
	    3 - DAT - SELIG - (Xfoil) \n
	    4 - DAT - LEDNICER
	*/

	iType = 0;
	iReadType = 0;
}

void AIRFOIL::Clean( void )
{
	/*DELETE_TAB( Xd );
	DELETE_TAB( Xg );
	DELETE_TAB( Zd );
	DELETE_TAB( Zg );
	DELETE_TAB( Xf );
	DELETE_TAB( Zf );
	DELETE_TAB( Xrob );
	DELETE_TAB( Zrob );*/
	N = 0;
	Nf = 0;
	Nrob = 0;
	iType = 0;
}

int AIRFOIL::Read( std::string fileName )
{
	Clean();

	fprintf(stderr,"iReadType %d\n",iReadType);
	if( iReadType )
		getiTypeByContent(fileName);   // gets file type by content
	if( iReadType == 0 || iType == -1 )
		getiTypeByExt(fileName);       // gets file type by extension

	// in case no type was detected finish
	if(iType==-1) 
	{
		std::clog << "No correct file was provided!" << std::endl;
		return -1;
	}
	
	switch( iType )
	{
		default:
		case 0:
			if( Read_PRF_0( fileName ) )return -1;
			break;
		case 1:
			if( Read_PRF_1( fileName ) )return -1;
			break;
		case 2:
			if( Read_KOO( fileName ) )return -1;
			break;
		case 3:
			if( Read_DAT( fileName ) )return -1;
			break;
		case 4:
			if( Read_DAT_LEDNICER( fileName ) )return -1;
			break;
	}
			
	return 0;
}

int AIRFOIL::Write( std::string fileName, int iTyp )
{
	switch( iTyp )
		{
		default:
		case 0:
			if( Write_PRF( fileName ) )return -1;
			break;
/*		case 1:
			if( Write_PRF_1( cFile ) )return -1;
			break;
		case 2:
			if( Write_KOO( cFile ) )return -1;
			break;
*/		case 3:
			if( Write_DAT( fileName ) )return -1;
			break;
		}
			
	return 0;
}

int AIRFOIL::ReadNaca( long int iNACA, int NN )
{
	char cNACA[10];
	sprintf(cNACA, "%04ld", iNACA );
	return ReadNaca( cNACA );
}

int AIRFOIL::ReadNaca( std::string NACA, int NN )
{
	//Name = "NACA " + NACA;

	NACA_PROFILE *NacaProfile = new NACA_PROFILE();
	NacaProfile->setTE0( 1 );
	NacaProfile->generate_naca( NACA, NN );
	
	Nf = NacaProfile->N;
	Xf = new double[Nf+1]; 
	Zf = new double[Nf+1]; 

	for( int i=0; i<Nf; i++ )
		{
		Xf[i] = NacaProfile->X[i];
		Zf[i] = NacaProfile->Z[i];
		}
		
	//DELETE_(NacaProfile);
		
	XFOIL2PRF();
	
	return 0;
}

/*
        Gets iType based on file content (by Anna Sima) - private
*/
void AIRFOIL::getiTypeByContent(std::string fileName)
{
	iType = -1; // type not yet found
	
	FILE *ff = fopen( fileName.c_str(), "r" );
	
	// set of useful regex expressions
	// \\d - digit
	// \\s - whitespace
	// + - one or more occurences
	// * - zero or more occurences
	// [] - match one from inside
	// (\\+|-)? - possible + or minues - one or zero times
	// . - whatever character
	regex integer("\\s*\\d+\\s*");   				// positive integer
	regex number("\\s*(\\+|-)?[\\d\\.]+\\s*");   			// 1 22 1.2 0.2 .2  2. - any number
	regex prfHeader("\\d+\\s+#\\s+.+");				// number_of_lines # name (e.g. "18	#	NACA 0012	")
	regex kooHeader(".+\\s+,\\s+\\d+");				// name , number_of_lines-1
	regex datNLines("\\s*\\d+\\.\\s*\\d+\\.\\s*");			// 31.  31.
	regex twoCols  ("\\s*(\\+|-)?[\\d\\.]+\\s+(\\+|-)?[\\d\\.]+\\s*");  //number whitespaces(\s) number
	regex threeCols("\\s*(\\+|-)?[\\d\\.]+\\s+(\\+|-)?[\\d\\.]+\\s+(\\+|-)?[\\d\\.]+\\s*");
	regex fourCols ("\\s*(\\+|-)?[\\d\\.]+\\s+(\\+|-)?[\\d\\.]+\\s+(\\+|-)?[\\d\\.]+\\s+(\\+|-)?[\\d\\.]+\\s*");
	
	// read first line
	// PRF
	// HEADER - number_of_lines # name
	// [4 cols]
	// * values 0-100
	// if first line matches full HEADER or just number of lines
	//ReadStr( ff, cc.c_str()); !!!!!!!!!!!!!!!!!
	if(regex_match(cc,prfHeader)||regex_match(cc,integer)) 
		{
		int N;
		fseek(ff,0, SEEK_SET); // go to beginning
		ReadPar( ff, "%d", &N );

		// check number of lines
		/*if(nLines( ff )!=N) 
			{
			fprintf(stderr,"Number of lines is incorrect, should be %d\n",N);
			iType=-1;
			}
		else
			{
			iType = 0; // assume it is ok
			// check all further lines
			for(int i=0; i<N; i++) 
				{
				//ReadStr( ff, cc );
				if(!regex_match(cc,fourCols))
					{
					// one of the lines is incorrect
					fprintf(stderr,"%s - line incorrect!\n",cc);
					iType=-1; // set to nok
					break;
					}
				}
			}*/
		}
    
	// PRF 2
	// HEADER1 - numer "1" or "2"
	// HEADER2 - number_of_lines
	// [2 cols] or [3 cols]
	// * values 0-100
	if(iType==-1) // // not yet found?
		{
		fseek(ff,0, SEEK_SET); // go to beginning
		//ReadStr( ff, cc); !!!!!!!!!!!!!!
		// first line is a number, can be whatever - read second line then
		//ReadStr( ff, cc); !!!!!!!!!!!!!!
		// second line must be integer - number of lines
		if(regex_match(cc,integer)) 
			{
			//N = atoi(cc); // convert second line to integer !!!!!!!!!!!!!!!
			/*if(nLines( ff )!=N) !!!!!!!!!!!!!!!!
				{
				fprintf(stderr,"Number of lines is incorrect, should be %d\n",N);
				iType=-1;
				}
			else
				{
				iType = 1; // assume type is PRF 2
				// check all lines match format of two or three columns
				for(int i=0; i<N; i++)
					{
					//ReadStr( ff, cc ); !!!!!!!!!!!!!
					if(!regex_match(cc,twoCols)&&!regex_match(cc,threeCols))
						{
						// one of the lines is incorrect
						fprintf(stderr,"%s - line incorrect!\n",cc);
						iType=-1; // set to nok
						break;
						}
					}
				}*/
			}
		}

	// KOO
	// HEADER - name , number_of_lines-1
	// [2 cols]
	// * values 0-100
	if(iType==-1) // not yet found?
		{
		fseek(ff,0, SEEK_SET); // go to beginning
		//ReadStr( ff, cc ); !!!!!!!!!!!!!!!!!!!
		// check if header matches koo - name , number_of_line
		if(regex_match(cc,kooHeader))
			{
			//get number of lines
			//int iLen = strlen( cc ); !!!!!!!!!!!!!!!!!!!!!!!1
			// replace all characters with whitespace till ,
			/*for( int i=0; i<iLen; i++ ) !!!!!!!!!!!!!!!!!!!!!!!
				{
				if(cc[i]==',' )
					{
					cc[i]=' ';
					break;
					}
				cc[i]=' ';
				}*/
			// convert spaces + number of lines string to number
			//N = atoi(cc); !!!!!!!!!!!!!!!!
			/*if(nLines( ff )!=N+1) !!!!!!!!!!!!!!!!!!!!!!!!
				{
				fprintf(stderr,"Number of lines is incorrect, should be %d\n",N);
				iType=-1;
				}
			else
				{
				iType=2;
				}*/
			}
		}

	// DAT - selig
	// HEADER - name
	// [2 cols]
	// * values 0.0-1.0
	if(iType==-1)     // not yet found?
		{
		fseek(ff,0, SEEK_SET); // go to beginning
		//ReadStr( ff, cc ); !!!!!!!!!!!!!!!
		//N = nLines( ff ); !!!!!!!!!!!!!!!!11
		// valide or further lines
		iType = 3; // assume type is DAT selig
		for(int i=0; i < N/2; i++) 
			{
			//ReadStr( ff, cc ); !!!!!!!!!!!!!!!!!!1
			if(!regex_match(cc,twoCols))
				{
				//fprintf(stderr,"%s - line incorrect(3)!\n",cc); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				iType=-1;
				break;
				}
			}
		}

	// DAT - lednicer
	// HEADER - name
	// HEADER - number_of_lines. number_of_lines.
	// [empty line]
	// [2 cols]
	// [empty line]
	// [2 cols]
	// * values from 0 to 1
	if(iType==-1)	// not yet found?
		{
		fseek(ff,0, SEEK_SET); // go to beginning
		//N = nLines( ff ); // get number of lines !!!!!!!!!!!!!!!!
		//ReadStr( ff, cc ); // name - whatever value, ignore comparison !!!!!!!!!!!!!!!!1
		//ReadStr( ff, cc ); // should be number_of_lines. number_of_lines.!!!!!!!!!!!!!!
		if(regex_match(cc,datNLines))
			{
			fseek(ff,0, SEEK_SET); // go to beginnig
			//ReadStr( ff, cc );     // omit first line !!!!!!!!!!!!!!!!!!!!!11
			float f1,f2;
			int n1,n2;
			ReadPar(ff, "%f %f",&f1,&f2);
			n1 = f1;
			n2 = f2;
			if(N!=n1+n2+2)
				{
				fprintf(stderr,"Number of lines incorrect, should be %d, is %d\n",N,n1+n2);
				iType=-1;
				}
			else
				{
				iType=4; // assume it is lednicer
				for(int i=0; i < N; i++)
					{
					//ReadStr( ff, cc ); !!!!!!!!!!!!!!!!!!!!!!!!!!!
					//string sc=cc;
					//if(!regex_match(cc,twoCols) && !sc.empty() && !IsBlank(sc) )
					if(!regex_match(cc,twoCols) && cc[0]!='\0' )
						{  
						// ommit empty lines - lines == \0
						//fprintf(stderr,"%s - line incorrect!\n",cc); !!!!!!!!!!!!!!!!!!!!!!!!!1
						iType=-1;
						break;
						}
				}
			}
		}
	}
	
	fclose(ff);

}
/*
        Gets iType based on file extension
*/
void AIRFOIL::getiTypeByExt(std::string fileName)
{
	//const char *pext = filename_ext( (const char*)fileName ); //!!!!!!!!!!!
	char ext[4]; 
	//for(int i=0; i<3; i++)ext[i] = toupper( pext[i+1] );// !!!!!!!!!!!!!!!1
	ext[3] = '\0';

	//fprintf(stderr,"cfile %s pext %s\n",cFile,pext);
	fprintf( stderr, "ext %s\n", ext );

	if( strcmp( ext, "PRF" ) == 0 )
		{
		iType = 0;
		FILE *ff = fopen( fileName.c_str(), "r" );
		if( ff )
			{
			int N;
			ReadPar( ff, "%d", &N );
			//int NN = nLines( ff ); !!!!!!!!!!!!!!!!!!!!!!!!!!!
			//if( N != NN )iType = 1; !!!!!!!!!!!!!!!!!!!!!!!!!!!
			//fprintf( stderr, "N %d NN %d typ %d\n", N, NN, iType );
			fclose( ff );
			}
		else
			iType=-1;
		}
	else if( strcmp( ext, "KOO" ) == 0 )
		{
		iType = 2;
		}
	else if( strcmp( ext, "DAT" ) == 0 )
		{
		// If both first numeric values are greater than 1, the file is lednicer format
		iType = 3;
		FILE *ff = fopen( fileName.c_str(), "r" );
		if( ff )
			{
			char cc[512];
			int iLen = 0;
			double topCoords, bottomCoords;
			// header - name
			ReadStrL( ff, cc, &iLen );
			// first line with numbers
			ReadPar( ff, "%lf %lf", &topCoords, &bottomCoords );

			if( topCoords > 1 && bottomCoords > 1 ) iType = 4;
			fclose( ff );
			}
		else
			iType=-1;
		}
	else
		iType=-1;

}

// Reads particular formats - private

int AIRFOIL::Read_PRF_0( std::string fileName )
{
	FILE  *ff;
	ff = fopen( fileName.c_str(), "r" );
	if( ff == NULL )
		{
		fprintf( stderr, "File: %s not found!\n", fileName.c_str() );
		return -1;
		}
	
	ReadPar( ff, "%d", &N );
	Xg = new double[N]; 
	Xd = new double[N]; 
	Zg = new double[N]; 
	Zd = new double[N]; 
	
	for(int i=0; i<N; i++)
		ReadPar( ff, "%lf %lf %lf %lf", &Xg[i], &Zg[i], &Xd[i], &Zd[i] );
	fclose( ff );

	double dAd = dAverage( Zd, N );
	double dAg = dAverage( Zg, N );
	if( dAg < dAd )
		{
		ff = fopen( fileName.c_str(), "r" );
		ReadPar( ff, "%d", &N );
		
		for(int i=0; i<N; i++)
			ReadPar( ff, "%lf %lf %lf %lf", &Xd[i], &Zd[i], &Xg[i], &Zg[i] );
		fclose( ff );
		}
	
	double dCa = max( tabmax( Xd, N ), tabmax( Xg, N ) );
	double dX0 = min( tabmin( Xd, N ), tabmin( Xg, N ) );

	dCa -= dX0;
	double dMnoz = 100./dCa;
	
	if( dCa < 80. || dCa > 120. )
	for(int i=0; i<N; i++)
		{
		Xg[i] *= dMnoz;
		Zg[i] *= dMnoz;
		Xd[i] *= dMnoz;
		Zd[i] *= dMnoz;
		}
/*
	fprintf(stderr, "\nprofil z pliku: %s\n", cFile );
	for(int i=0; i<N; i++)
		fprintf( stderr, "%lf %lf %lf %lf\n", Xg[i], Zg[i], Xd[i], Zd[i] );
*/
	TE_correct();		
	
	//int iN = strlen( filename_name( cFile ) ) - 4; !!!!!!!!!!!!!!!
	//strncpy( cName, filename_name( cFile ), iN ); !!!!!!!!!!!
	//cName[ iN ] = '\0'; !!!!!!!!!!!!!!

//	fprintf(stderr, "\nnazwa: %s\n", cName );
	
	PRF2XFOIL();
	
	return 0;
}

int AIRFOIL::Read_PRF_1( std::string fileName )
{
	FILE  *ff;
	ff = fopen( fileName.c_str(), "r" );
	if( ff == NULL )
		{
		fprintf( stderr, "File: %s not found!\n", fileName.c_str() );
		return -1;
		}
	
	int iTyp = 2;
	ReadPar( ff, "%d", &iTyp );
	ReadPar( ff, "%d", &Nrob );
	Xrob = new double[2*Nrob]; 
	Zrob = new double[2*Nrob];
	Nf = Nrob;
	if( iTyp == 1 ) Nf = Nf*2 - 1;
	Xf = new double[Nf]; 
	Zf = new double[Nf]; 
	
	if( iTyp == 1 )
		{
		int i =0;
		ReadPar( ff, "%lf %lf %lf", &Xrob[i], &Zrob[i], &Zrob[Nrob] );
		Xf[i] = Xrob[i];
		Zf[i] = Zrob[i];
		for(i=1; i<Nrob; i++)
			{
			ReadPar( ff, "%lf %lf %lf", &Xrob[i], &Zrob[i], &Zrob[i+Nrob-1] );
			Xf[i] = Xrob[i];
			Zf[i] = Zrob[i];
			Xf[i+Nrob-1] = Xrob[i+Nrob-1] = Xrob[i];
			Zf[i+Nrob-1] = Zrob[i+Nrob-1];
			}
		Nrob = Nrob*2 - 1;
		}
	else
		{
		for(int i=0; i<Nrob; i++)
			{
			ReadPar( ff, "%lf %lf", &Xrob[i], &Zrob[i] );
			Xf[i] = Xrob[i];
			Zf[i] = Zrob[i];
			}
		}
/*		
	fprintf(stderr,"Nrob = %d Nf %d\n",Nrob,Nf);
	for(int i=0; i<Nrob; i++ )
		fprintf(stderr,"%lf %lf \n",Xrob[i],Zrob[i]);
*/	
	fclose( ff );
	
	//int iN = strlen( filename_name( cFile ) ) - 4;
	//strncpy( cName, filename_name( cFile ), iN ); !!!!!!!!!!!!!!!
	//cName[ iN ] = '\0'; !!!!!!!!!!!!!!!!!
	
	double *Xfrob = new double[Nrob];
	for( int i=0; i<Nrob; i++ )Xfrob[i] = Xrob[i];
	N = Nrob;
	SortClean( &N, Xfrob );
	
	int nmax = N;
	int nmin = N;
	double dCa = dMaxT( Xrob, &nmax );
	double dX0 = dMinT( Xrob, &nmin );

	dCa -= dX0;
	double dMnoz = 100./dCa;
	
	int NN = nmax;
	
	for( int i=Nrob; i>NN+1; i-- )
		{
		Xrob[i] = Xrob[i-1];
		Zrob[i] = Zrob[i-1];
		}
	Xrob[NN+1] = Xrob[0];
	Zrob[NN+1] = Zrob[0];
	Nrob++;
	
	Xg = new double[N]; 
	Xd = new double[N]; 
	Zg = new double[N]; 
	Zd = new double[N];
	for( int i=0; i<N; i++ )
		{
		Xd[i] = Xfrob[i];
		Zd[i] = inter1( &Xrob[NN+1], &Zrob[NN+1], Nrob-NN-1, Xd[i] );
		Xg[i] = Xd[i];
		Zg[i] = inter1( Xrob, Zrob, NN+1, Xg[i] );
		}
	
	for( int i=0; i<N; i++ )
		{
		Xg[i] -= dX0;
		Xg[i] *= dMnoz;
		Xd[i] -= dX0;
		Xd[i] *= dMnoz;
		Zg[i] *= dMnoz;
		Zd[i] *= dMnoz;
		}

	TE_correct();	

//	Print( stderr );

	//PRF2XFOIL();
	int nf2 = 0;
	while( Xf[nf2] < Xf[nf2+1] && nf2 < Nf )nf2++;
	Sort2( nf2+1, Xf, Zf, -1 );
	for( int i=0; i<Nf; i++ )
		{
		Xf[i] -= dX0;
		Xf[i] *= dMnoz/100.;
		Zf[i] *= dMnoz/100.;
		}
	//DELETE_TAB( Xfrob );
	return 0;
}

void AIRFOIL::PRF2XFOIL( void )
{
	Nf = 2*N - 1;
	Xf = new double[Nf];
	Zf = new double[Nf];
	for(int i=0; i<N; i++)
		{
		Xf[i] = Xd[N-1-i]/100.;
		Zf[i] = Zd[N-1-i]/100.;
		}
	for(int i=N; i<Nf; i++)
		{
		Xf[i] = Xg[i-N+1]/100.;
		Zf[i] = Zg[i-N+1]/100.;
		}
}

int AIRFOIL::Write_PRF( std::string fileName )
{
	FILE  *ff;
	ff = fopen( fileName.c_str(), "w" );
	//fprintf(ff,"%d\t#\t%s\n", N, cName );
	for( int i=0; i<N; i++ )
		fprintf( ff, "%f %f %f %f\n", Xg[i], Zg[i], Xd[i], Zd[i] );
	fclose(ff);

	return 0;
}

int AIRFOIL::Read_KOO( std::string fileName )
{
	return Read_DAT( fileName );
}

void AIRFOIL::Print( FILE* f ) {

    //fprintf(f,"%d\t#\t%s\n", N, cName );
	for( int i=0; i<N; i++ )
		fprintf(f,"%f %f %f %f\n", Xg[i], Zg[i], Xd[i], Zd[i] );

}

int AIRFOIL::Read_DAT_LEDNICER( std::string fileName )	// by Anna Sima
{
	FILE  *ff;
	ff = fopen( fileName.c_str(), "r" );
	if( ff == NULL )
		{
		//sprintf( comment, "File: %s not found!\n", cFile );
		fprintf( stderr, "File: %s not found!\n", fileName.c_str() );
		return -1;
		}
//reads 1st line - profile name
	//ReadStr( ff, cName );

	float f1, f2;
	int rowsPos, rowsNeg;

	ReadPar(ff, "%f %f", &f1, &f2);
	rowsPos = f1;
	rowsNeg = f2;

//makes empty arrays to store values from the file
	Xf = new double[rowsPos+rowsNeg];
	Zf = new double[rowsPos+rowsNeg];

	Nf = rowsPos+rowsNeg-1; //total number of points(rows) that will be in the end

	for( int i=rowsPos-1; i>=0; i-- ) {
	    ReadPar(ff, "%lf %lf",&Xf[i],&Zf[i]); //read all upper
	}

	for( int i=0; i<rowsNeg; i++ ) {
	    ReadPar(ff, "%lf %lf",&Xf[rowsPos-1 + i],&Zf[rowsPos-1 + i]); //read all lower
	}

	fclose( ff );
	
	Check( &Nf, Xf, Zf );

	XFOIL2PRF();

	return 0;
}

int AIRFOIL::Read_DAT( std::string fileName )
{
	FILE  *ff;
	ff = fopen( fileName.c_str(), "r" );
	if( ff == NULL )
		{
		//sprintf( comment.c_str(), "File: %s not found!\n", fileName.c_str() );
		fprintf( stderr, "File: %s not found!\n", fileName.c_str() );
		return -1;
		}

	//Nf = nLines( ff ) - 1;
	fclose( ff );
	if( Nf < 6 )
		{
		//sprintf( comment.c_str(), "File: %s - the number of rows is too small!\n", fileName.c_str() ); //!!!!!!!!!!!!!!!!!!!!!!!!
		fprintf( stderr, "File: %s - the number of rows is too small!\n", fileName.c_str() );
		return -1;
		}
		
	Xf = new double[Nf+1];
	Zf = new double[Nf+1];
	ff = fopen( fileName.c_str(), "r" );
	//ReadStr( ff, cName );
	if( iType == 2 )
		{
		//int iLen = strlen( cName );
		//for( int i=iLen; i>0; i-- )if( cName[i] == ',' )cName[i] = '\0';
		}
	for( int i=0; i<Nf; i++ )
		if( iType == 2 )
			{
			//ReadStr( ff, cc );
			//for( int ii=0; ii < (int)strlen( cc ); ii++)if( cc[ii] == ',' )cc[ii] = ' '; //!!!!!!!!!!!!!!!!!!!!!!
			//sscanf( cc, "%lf %lf", &Xf[i], &Zf[i] ); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
		else
			if( ReadPar( ff, "%lf %lf", &Xf[i], &Zf[i] ) == EOF )
				{
				Nf = i;
				break;
				};
	fclose( ff );
	
	Check( &Nf, Xf, Zf );
	
	XFOIL2PRF();

	return 0;
}

void AIRFOIL::XFOIL2PRF( void )
{
	int nmax = Nf;
	int nmin = Nf;
	double dCa = dMaxT( Xf, &nmax );
	double dX0 = dMinT( Xf, &nmin );
	//fprintf(stderr,"Xf min %f %f %f\n",Xf[nmin-1],Xf[nmin],Xf[nmin+1]);
	
	if( Xf[nmin-1] == Xf[nmin] )		// nose correction
	    {
	    double XX[4], YY[4];
	    for( int i=0; i<4; i++)
	        {
	        XX[i]=Xf[nmin-2+i];
	        YY[i]=Zf[nmin-2+i];
	        }
	    double Y0 = 0.5*(YY[2]+YY[1]);
	    double X0 = apr3( Y0, YY, XX );
	    for( int i=Nf; i>nmin; i-- )
	        {
	        Xf[i] = Xf[i-1];
	        Zf[i] = Zf[i-1];
	        }
	    Xf[nmin] = X0;
	    Zf[nmin] = Y0;
	    Nf++;
	    nmax = Nf;
	    nmin = Nf;
	    dCa = dMaxT( Xf, &nmax );
	    dX0 = dMinT( Xf, &nmin );
	    }
	dCa -= dX0;
	double dMnoz = 100./dCa;
	
	double dW1, dW2;
	int iSter = 0;		// 1 - lower surface first, 0 - upper surface first
	int NN = min( nmin, nmax );
	if( nmax > nmin || nmax == 0 )
		{
		dW1 = dAverage( Zf, nmin );
		dW2 = dAverage( &Zf[nmin], Nf - nmin );
		if( dW2 > dW1 )iSter = 1;
		NN = nmin;
		}
	else
		{
		dW1 = dAverage( Zf, nmax );
		dW2 = dAverage( &Zf[nmax], nmin - nmax );
		if( dW2 > dW1 )iSter = 1;
		NN = nmax;
		}
		
	fprintf( stderr, "ReadDAT - Xfoil2Prf:\n" );
	fprintf( stderr, "Nf = %d NN = %d iSter = %d\n", Nf, NN, iSter );
	fprintf( stderr, "max %d min %d\n", nmax, nmin );
	fprintf( stderr, "X0  %f Ca  %f\n", dX0, dCa );
	fflush( stderr );
	
	double *Xfrob = new double[Nf];
	for( int i=0; i<Nf; i++ )Xfrob[i] = Xf[i];
	N = Nf;
	SortClean( &N, Xfrob );
	
	Xg = new double[N]; 
	Xd = new double[N]; 
	Zg = new double[N]; 
	Zd = new double[N];
	if(iSter == 1)
		{
		for( int i=0; i<N; i++ )
			{
			Xd[i] = Xfrob[i];
			Zd[i] = inter1( Xf, Zf, NN+1, Xd[i] );
			Xg[i] = Xd[i];
			Zg[i] = inter1( &Xf[NN], &Zf[NN], Nf-NN, Xg[i] );
			}
		}
	else
		{
		for( int i=0; i<N; i++ )
			{
			Xd[i] = Xfrob[i];
			Zd[i] = inter1( &Xf[NN], &Zf[NN], Nf-NN, Xd[i] );
			Xg[i] = Xd[i];
			Zg[i] = inter1( Xf, Zf, NN+1, Xg[i] );
			}
		}
	
	for( int i=0; i<N; i++ )
		{
		Xg[i] -= dX0;
		Xg[i] *= dMnoz;
		Xd[i] -= dX0;
		Xd[i] *= dMnoz;
		Zg[i] *= dMnoz;
		Zd[i] *= dMnoz;
		}

	TE_correct();		
	
	for( int i=0; i<Nf; i++ )
		{
		Xf[i] -= dX0;
		Xf[i] *= dMnoz/100.;
		Zf[i] *= dMnoz/100.;
		}

}

int AIRFOIL::Write_DAT( std::string fileName )
{
	FILE  *ff;
	ff = fopen( fileName.c_str(), "w" );
	fprintf(ff,"%s\n", fileName.c_str() );
	for( int i=0; i<Nf; i++ )
		fprintf( ff, " %f %f \n", Xf[i], Zf[i] );
	fclose(ff);
	
	return 0;
}

void AIRFOIL::TE_correct( void )
{
        double zz = 0.5*(Zd[N-1]+Zg[N-1]);
        Zd[N-1] = Zg[N-1] = zz;
}

// math routines

double AIRFOIL::dAverage( double *dTab, int i1 )
{
	double dSum = 0.;
	for( int i=0; i<i1; i++) dSum += dTab[i];
	dSum = dSum / i1;
	
	return (dSum);
}

double AIRFOIL::tabmax( double* dTab, int n )
{
	double dWyn = dTab[0];
	if(n>1)for( int i=1; i<n; i++ )dWyn = max( dWyn, dTab[i] );
	return dWyn;
}

double AIRFOIL::tabmin( double* dTab, int n )
{
	double dWyn = dTab[0];
	if(n>1)for( int i=1; i<n; i++ )dWyn = min( dWyn, dTab[i] );
	return dWyn;
}

double AIRFOIL::dMaxT( double *dTab, int *i1 )
{
	int n = *i1;
	*i1 = 0;
	double dRob = dTab[0];
	for( int i=0; i<n; i++)
		{
		dRob = max( dTab[i], dRob );
		if( dRob == dTab[i] )*i1 = i;
		}
	return (dRob);
}

double AIRFOIL::dMinT( double *dTab, int *i1 )
{
	int n = *i1;
	*i1 = 0;
	double dRob = dTab[0];
	for( int i=0; i<n; i++)
		{
		dRob = min( dTab[i], dRob );
		if( dRob == dTab[i] )*i1 = i;
		}
	return (dRob);
}

void AIRFOIL::Check( int *nn, double *X, double *Z )
{
	N = *nn;
	for(int i=0; i<N-1; i++)
                {
                if( X[i] == X[i+1] && Z[i] == Z[i+1] )
                        {
                        for( int ii=i; ii<N-1; ii++ )
				{
				X[ii]=X[ii+1];
				Z[ii]=Z[ii+1];
				}
                        N--;
                        }
                }
        *nn = N;
}

unsigned long AIRFOIL::locate(double xx[], unsigned long n, double x )
{
	unsigned long j;
	unsigned long ju,jm,jl;

	int ascnd;
	ascnd = ( xx[n-1] >= xx[0] );

	if( ascnd )
		{
		if( x <= xx[0] )
			j = 0;
		else if ( x >= xx[n-1] )
			j = n - 2;
		else
			{
			jl = 0;
			ju = n;
			while ( ju-jl > 1)
				{
				jm = (ju+jl) >> 1;		// midpoint (ju+jl)/2
				if( (x >= xx[jm]) == ascnd)
					jl=jm;
				else
					ju=jm;
				}
			j = jl;
			}
		}
	else
		{
		if( x >= xx[0] )
			j = 0;
		else if ( x <= xx[n-1] )
			j = n - 2;
		else
			{
			jl = 0;
			ju = n;
			while ( ju-jl > 1)
				{
				jm = (ju+jl) >> 1;		// midpoint (ju+jl)/2
				if( (x >= xx[jm]) == ascnd)
					jl=jm;
				else
					ju=jm;
				}
			j = jl;
			}
		}
		
	return j;
		
}

/*
	linear interpolation for one-dimensional array (no extrapolation)
*/

double AIRFOIL::inter1(double *xx, double *yy, unsigned long n, double x )
{
	unsigned long numer;
	double y;
	
	if( (xx[n-1]-xx[0]) < 0. )
    		{
		x = min( x, xx[0] );
		x = max( x, xx[n-1] );
		}
	 else
    		{
		x = max( x, xx[0] );
		x = min( x, xx[n-1] );
    		}
	numer  = locate(xx, n, x );
	//double aa = (yy[numer+1]-yy[numer])/(xx[numer+1]-xx[numer]);
	//double bb = yy[numer] - aa*xx[numer];
	//y = aa*x + bb;

	y = yy[numer+1]*(x-xx[numer]) + yy[numer]*(xx[numer+1]-x);
	y /= xx[numer+1]-xx[numer];

	
	return y;
}

double AIRFOIL::apr3( double dX, double *dXX, double *dYY )
{
	double X1 = dXX[0];
	double X2 = dXX[1];
	double X3 = dXX[2];
	double X4 = dXX[3];
	double F1 = dYY[0];
	double F2 = dYY[1];
	double F3 = dYY[2];
	double F4 = dYY[3];
	
	double X13 = pow( X1, 3.0 );
	double X23 = pow( X2, 3.0 );
	double X33 = pow( X3, 3.0 );
	double X43 = pow( X4, 3.0 );
	
	double Q1 = X33*(X2-X1) - X23*(X3-X1) + X13*(X3-X2);
	double Q2 = X43*(X2-X1) - X23*(X4-X1) + X13*(X4-X2);
	double Q3 = (X3-X2)*(X2-X1)*(X3-X1);
	double Q4 = (X4-X2)*(X2-X1)*(X4-X1);
	double Q5 = F3*(X2-X1) - F2*(X3-X1) + F1*(X3-X2);
	double Q6 = F4*(X2-X1) - F2*(X4-X1) + F1*(X4-X2);
	
	double a3 = (Q3*Q6-Q4*Q5)/(Q2*Q3-Q1*Q4);
	double a2 = (Q5-a3*Q1)/Q3;
	double a1 = (F2-F1)/(X2-X1) - a3*(X23-X13)/(X2-X1) - a2*(X1+X2);
	double a0 = F1 - a1*X1 - a2*X1*X1 - a3*X13;
	
	return( a0 + a1*dX + a2*dX*dX + a3*dX*dX*dX );
}

//
//	Sorting routine with deleting the same values
//

void AIRFOIL::SortClean( int *N, double *X )
{
        int NN = *N;
        Sort1( NN, X );
        for( int i=0; i<NN-1; i++ )
                {
                if( X[i] == X[i+1] )
                        {
                        for( int ii=i; ii<NN-1; ii++ )X[ii]=X[ii+1];
                        NN--;
                        }
                }
        *N = NN;
}

//
//	Simply sorting routine
//

void AIRFOIL::Sort1( int N, double dRA[] )
{
	double T;
	int i,j,k;

	k = N;
	while( k > 1 )
		{
		k = k/2;
		for( j=0; j<(N-k); j++ )
			for( i=j; i>=0; i-=k )
				{
				if( dRA[i] > dRA[i+k] )
					{
					T = dRA[i];
					dRA[i] = dRA[i+k];
					dRA[i+k] = T;
					}
				}
		}
}


bool AIRFOIL::check_order( double d1, double d2, int iFlag )
{
	if( iFlag >= 0 )
		return ( d1 < d2 );
	else
		return ( d1 > d2 );
}

//	read line
int AIRFOIL::ReadStr( FILE * stream, char *Par )
{
	ReadDummy( stream );

	char cc;
	int i;
	
	cc = fgetc( stream );
	i = 0;
	while ( cc != '\n' && cc != EOF && cc != 0xD ) 
		{
		Par[i] = cc;
		cc = fgetc( stream);
		i++;
		}
	if( cc == 0xD )
		{
		cc = fgetc( stream );
		if( cc != 0xA )ungetc( cc, stream );
		}
	
	Par[i]='\0';

	int j;
	for( j=i-1; j>0; j-- )
		{
		if( isblank(Par[j]) )
			Par[j] = '\0';
		else
			break;
		}
		
	char *cRob = new char[j+2];
	std::strcpy( cRob, Par );
	int i0 = 0;
	for( int i=0; i<j+1; i++ )
		{
		if( isblank(cRob[i]) )
			i0 = i+1;
		else
			break;
		}
	strcpy( Par, cRob+i0 );
	delete [] cRob;
	
	if( cc == EOF )return EOF;
	return strlen( Par );	
}

void AIRFOIL::ReadStrL( FILE * stream, char *Par , int *len)
{
	char cc;
	int i;
	
	cc = fgetc( stream );
	i = 0;
	while ( cc != '\n' && cc != EOF && cc != 0xD ) 
		{
		Par[i] = cc;
		cc = fgetc( stream);
		i++;
		}
	if( cc == 0xD )
		{
		cc = fgetc( stream );
		if( cc != 0xA )ungetc(cc,stream);
		}

	Par[i]='\0';
	if( cc == EOF )Par[i+1]=EOF;
	*len = i;
		
}

//	read up to four values from one line with comment
int AIRFOIL::ReadPar( FILE *stream, const char *Format, void *Par )
{
	ReadDummy( stream );
	fscanf( stream, Format, Par );			/* read value    */
	return ReadComm( stream );
}

int AIRFOIL::ReadPar( FILE *stream, const char *Format, void *Par1, void *Par2 )
{
	ReadDummy( stream );
	fscanf( stream, Format, Par1, Par2 );
	return ReadComm( stream );
}

int AIRFOIL::ReadPar( FILE *stream, const char *Format, void *Par1, void *Par2, void *Par3 )
{
	ReadDummy( stream );
	fscanf( stream, Format, Par1, Par2, Par3 );
	return ReadComm( stream );
}

int AIRFOIL::ReadPar( FILE * stream, const char * Format, void *Par1, void *Par2, void *Par3, void *Par4 )
{
	ReadDummy( stream );
	fscanf( stream, Format, Par1, Par2, Par3, Par4 );
	return ReadComm( stream );
}

int AIRFOIL::ReadComm( FILE *stream )
{
	char a;
	while ( a = fgetc( stream ) , ( a != '\n' && a != EOF ) );		/* omit comment */
	if( a == EOF )return EOF;
	return 0;	
}

void AIRFOIL::ReadDummy( FILE *stream )
{
	unsigned char ucRes = 1;
	while ( ucRes )
		{
		char ch = fgetc(stream);
		ucRes = (ch == '#');
		ungetc(ch,stream);
		//fseek( stream, -1, SEEK_CUR );
		if( ucRes )ReadComm( stream );
		}
}

//
//	Sorting routine with ordering 2nd array
//

void AIRFOIL::Sort2( int iN, double dRA[], double dKOL[], int iOrder )
{

	double dRRA, dRA2;
	int i,j,l,iR;

	l = iN/2 + 1;
	iR = iN;

	if( iN <= 1 ) return;

	while( true )
		{
		if( l > 1 )
			{
			l = l - 1;
			dRRA = dRA[l-1];
			dRA2 = dKOL[l-1];
			}
		else
			{
			dRRA = dRA[iR-1];
			dRA2 = dKOL[iR-1];
			dRA[iR-1] = dRA[0];
			dKOL[iR-1] = dKOL[0];
			iR--;
			if( iR == 1 )
				{
				dRA[0] = dRRA;
				dKOL[0] = dRA2;
				return;
				}
			}
			
		i = l;
		j = l + l;
		while( j <= iR )
			{
			if( ( j < iR ) && check_order( dRA[j-1], dRA[j], iOrder ) )j++;
			if( check_order( dRRA, dRA[j-1], iOrder ) )
				{
				dRA[i-1] = dRA[j-1];
				dKOL[i-1] = dKOL[j-1];
				i = j;
				j = j + j;
				}
			else
				{
				j = iR + 1;
				}
			//fprintf(stderr,"j=%d ir %d\n",j,iR);fflush(stderr);
			}
		
		dRA[i-1] = dRRA;
		dKOL[i-1] = dRA2;
		}

}
