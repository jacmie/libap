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
//#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>

#include "ap_airfoil.h"

using namespace std;

namespace ap
{
	AIRFOIL::AIRFOIL()
	{
	}

	void AIRFOIL::Clean()
	{
	}

int AIRFOIL::Read( std::string fileName )
{
	Clean();

	int iType = -1;

	if( iReadType == AIRFOIL_BY_CONTENT )   { iType = getiTypeByContent(fileName); }
	if( iReadType == AIRFOIL_BY_EXTENSION ) { iType = getiTypeByExt(fileName); } 

	//std::clog << "iType = " << iType << std::endl;
	switch(iType) { // one of the lines has incorrect format
		case PRF_4: { std::clog << "PRF_4" << std::endl; break; }
		case PRF_3: { std::clog << "PRF_3" << std::endl; break; }
		case PRF_2: { std::clog << "PRF_2" << std::endl; break; }
		case KOO:   { std::clog << "KOO"   << std::endl; break; }
		case XFOIL: { std::clog << "XFOIL" << std::endl; break; }
		case L_DAT: { std::clog << "L_DAT" << std::endl; break; }
	}
	return 1;

	// in case no type was detected finish
	if(iType == -1) 
	{
		std::clog << "Unrecognized airfoil file type!!!" << std::endl;
		return -1;
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
	
	Xf.resize(NacaProfile->N + 1); 
	Zf.resize(NacaProfile->N + 1); 

	for(unsigned int i=0; i<Xf.size(); i++)
		{
		Xf[i] = NacaProfile->X[i];
		Zf[i] = NacaProfile->Z[i];
		}
		
	//DELETE_(NacaProfile);
		
	XFOIL2PRF();
	
	return 0;
}

	/*
    	Gets iType based on file content - private
	*/
	int AIRFOIL::ReadColumns(const int type, std::stringstream &buffer, 
		std::vector <double> &x1, std::vector <double> &y1, std::vector <double> &x2, std::vector <double> &y2, 
		const unsigned int n1, const unsigned int n2)
	{
		std::string rxNum("([-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)");
		std::string col2 = string(".*") + rxNum + string("\\s+") + rxNum + string(".*");
		std::string col3 = col2 + rxNum + string("\\s+") + rxNum + string(".*");
		std::string col4 = col3 + rxNum + string("\\s+") + rxNum + string(".*");
		regex rxcol2(col2);
		regex rxcol3(col3);
		regex rxcol4(col4);

		std::string line;
		int lineNr=0; 
		double x1_, y1_, x2_, y2_;

		// === Check number of columns and count data rows ===
		while( !buffer.eof() ) {
			getline(buffer, line);
			if( 0 == line.length() ) continue;
			
			switch(type) { // one of the lines has incorrect format
				case PRF_4: { if(!regex_match(line, rxcol4)) return 20; break; }
				case PRF_3: { if(!regex_match(line, rxcol3)) return 20; break; }
				case PRF_2: { if(!regex_match(line, rxcol2)) return 20; break; }
				case KOO:   { if(!regex_match(line, rxcol2)) return 20; break; }
				case XFOIL: { if(!regex_match(line, rxcol2)) return 20; break; }
				case L_DAT: { if(!regex_match(line, rxcol2)) return 20; break; }
			}
		
			// --- read row of data ---
			std::stringstream ss;
			ss.str(line);
			switch(type) { 
				case PRF_4: { ss >> x1_ >> y1_ >> x2_ >> y2_; break; }
				case PRF_3: { ss >> x1_ >> y1_ >> x2_; break; }
				default: 	{ ss >> x1_ >> y1_; }
			}

			// --- store the row of data ---
			x1.push_back(x1_);
			y1.push_back(y1_);
			if(type == PRF_4) {
				x2.push_back(x2_);
				y2.push_back(y2_);
			}
			
			lineNr++;
		}
		
		// === Check declared vs counted data rows ===
		switch(type) { // one of the lines has incorrect format
			case PRF_4: { if(x1.size() != n1) return 30; break; }
			case PRF_3: { if(x1.size() != n1) return 30; break; }
			case PRF_2: { if(x1.size() != n1) return 30; break; }
			case KOO:   { if(x1.size() != n1+1) return 30; break; }
			case XFOIL: { break; } // no declared nr of data rows
			case L_DAT: { if(x1.size() != n1+n2) return 30; break; }
		}

		// === Check data end values ===
		switch(type) { // one of the lines has incorrect format
			case PRF_4: { 
					if(x1[0] != 0.0) return 40; 
					if(x1[x1.size()-1] != 100.0) return 40; 
					if(x2[0] != 0.0) return 40; 
					if(x2[x1.size()-1] != 100.0) return 40; 
					break; 
					}
			case PRF_3:  
			case PRF_2: { 
					if(x1[0] != 0.0) { return 40; }
					if(x1[x1.size()-1] != 100.0) { return 40; }
					break; 
					}
			case KOO:   { 
					if(x1[0] != 100.0) { return 40; }
					if(x1[x1.size()-1] != 100.0) { return 40; }
					break; 
					}
			case XFOIL: {
				//	if(x1[0] != 1.0) { return 40; }
				//	if(x1[x1.size()-1] != 1.0) { return 40; }
					break;
					}
			case L_DAT: { 
					if(x1[0] != 0.0 		&& x1[0] != 1.0) { return 40; }
					if(x1[n1-1] != 0.0 		&& x1[n1-1] != 1.0) { return 40; }
					if(x1[n1] != 0.0 		&& x1[n1] != 1.0) { return 40; }
					if(x1[n1+n2-1] != 0.0 	&& x1[n1+n2-1] != 1.0) { return 40; }
					//Devide for two tables!!!!! x2, y2
					break; 
					}
		}

		// === Check data end values ===
		switch(type) { // one of the lines has incorrect format
			case PRF_3:  
			case PRF_2: {
					x2 = x1;
					y2 = y1;
					x1.resize(0.5*n1 + 1);
					y1.resize(0.5*n1 + 1);
					x2.erase(x2.begin(), x2.begin() + 0.5*n1);
					y2.erase(y2.begin(), y2.begin() + 0.5*n1);
					x2[0] = x1[0];
					y2[0] = y1[0];
					break; 
					}
/*			case KOO:   { 
					if(x1[0] != 100.0) { return 40; }
					if(x1[x1.size()-1] != 100.0) { return 40; }
					break; 
					}
			case XFOIL: {
					if(x1[0] != 1.0) { return 40; }
					if(x1[x1.size()-1] != 1.0) { return 40; }
					break;
					}
			case L_DAT: { 
					if(x1[0] != 0.0 		&& x1[0] != 1.0) { return 40; }
					if(x1[n1-1] != 0.0 		&& x1[n1-1] != 1.0) { return 40; }
					if(x1[n1] != 0.0 		&& x1[n1] != 1.0) { return 40; }
					if(x1[n1+n2-1] != 0.0 	&& x1[n1+n2-1] != 1.0) { return 40; }
					//Devide for two tables!!!!! x2, y2
					break; 
					}*/
		}

		return type;
	}

	int AIRFOIL::getiTypeByContent(std::string fileName)
	{
		clog << "getiTypeByContent" << endl;

		ifstream in(fileName);
    	if(!in) return 10; 	//couldn't read file
    	std::stringstream buffer;
	    buffer << in.rdbuf();
   	 	in.close();

		std::string buckup = buffer.str();
		std::string line;

		// set of useful regex expressions
		// \\d - digit
		// \\s - whitespace
		// + - one or more occurences
		// * - zero or more occurences
		// [] - match one from inside
		// (\\+|-)? - possible + or minues - one or zero times
		// . - whatever character
		regex integer("\\s*\\d+\\s*");   						// positive integer
		regex number("\\s*(\\+|-)?[\\d\\.]+\\s*");   			// 1 22 1.2 0.2 .2  2. - any number
		regex prfHeader("\\d+\\s+#\\s+.+");						// number_of_lines # name (e.g. "18	#	NACA 0012	")
		regex kooHeader(".+\\s+,\\s+\\d+");						// name , number_of_lines-1
		regex datNLines("\\s*\\d+\\.\\s*\\d+\\.\\s*");			// 31.  31.
	
		std::vector <double> x1;
		std::vector <double> y1;
		std::vector <double> x2;
		std::vector <double> y2;

		// read first line
		// PRF
		// HEADER - number_of_lines # name
		// [4 cols]
		// * values 0-100
		// if first line matches full HEADER or just number of lines
		getline(buffer, line);
		if( regex_match(line, prfHeader) || regex_match(line, integer) ) {
			buffer.str(buckup); 
			unsigned int n;
			buffer >> n; // get declared number of lines
			getline(buffer, line); //read the header line till the end
			
			unsigned int n_name = line.find_first_of("#");
			name = line.substr(n_name + 1);
			name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
			name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);

			if(PRF_4 == ReadColumns(PRF_4, buffer, x1, y1, x2, y2, n, 0) ) {
				Xg = x1;
				Zg = y1;
				Xd = x2;
				Zd = y2;

				Print4col(clog);
				/*
				double dCa = max( Xd[*std::max_element( Xd.begin(), Xd.end() )], Xg[*std::max_element( Xg.begin(), Xg.end() )] );
				double dX0 = min( Xd[*std::min_element( Xd.begin(), Xd.end() )], Xg[*std::min_element( Xg.begin(), Xg.end() )] );

				dCa -= dX0;
				double dMnoz = 100./dCa;
	
				if( dCa < 80. || dCa > 120. )
				for(unsigned int i=0; i<Xg.size(); i++) {
					Xg[i] *= dMnoz;
					Zg[i] *= dMnoz;
					Xd[i] *= dMnoz;
					Zd[i] *= dMnoz;
				}*/
				
				//TE_correct();		
				PRF2XFOIL();
				Print2col(clog);

				return PRF_4;
			}
		}

		// PRF 2
		// HEADER1 - numer "1" or "2"
		// HEADER2 - number_of_lines
		// [2 cols] or [3 cols]
		// * values 0-100
		buffer.str(buckup); 
		getline(buffer, line); // first line is a number, can be whatever - read second line then
		getline(buffer, line);
		if( regex_match(line, integer) ) { // second line must be single integer - number of lines
			unsigned int n = stoi(line); // convert second line to integer
			
			if(PRF_3 == ReadColumns(PRF_3, buffer, x1, y1, x2, y2, n, 0) ) { 
				Xg = x1;
				Zg = y1;
				Xd = x2;
				Zd = y2;

				Print4col(clog);
				
				PRF2XFOIL();
				Print2col(clog);

				return PRF_3;
			}
		
			buffer.str(buckup); 
			getline(buffer, line); // first line is a number, can be whatever - read second line then
			getline(buffer, line);
			if(PRF_2 == ReadColumns(PRF_2, buffer, x1, y1, x2, y2, n, 0) ) {
				Xg = x1;
				Zg = y1;
				Xd = x2;
				Zd = y2;

				Print4col(clog);
				
				PRF2XFOIL();
				Print2col(clog);

				return PRF_2;
			}
		}

		// KOO
		// HEADER - name , number_of_lines-1
		// [2 cols]
		// * values 0-100
		buffer.str(buckup); 
		getline(buffer, line);
		// check if header matches koo - name , number_of_line
		if(regex_match(line, kooHeader))
		{
			std::size_t coma = line.find_first_of(","); //get number of lines
			int n = stoi( line.substr(coma + 1) );
		
			if(KOO == ReadColumns(KOO, buffer, x1, y1, x2, y2, n, 0) ) return KOO;
		}

		// DAT - lednicer
		// HEADER - name
		// HEADER - number_of_lines. number_of_lines.
		// [empty line]
		// [2 cols]
		// [empty line]
		// [2 cols]
		// * values from 0 to 1
		clog << "LEDD" << endl;
		buffer.str(buckup); 
		getline(buffer, line);
			clog << line << endl;
		getline(buffer, line);
			clog << line << endl;
		if(regex_match(line, datNLines))
		{
			clog << line << endl;
			float n1, n2;
			std::stringstream ss;
			ss.str(line);
			ss >> n1 >> n2;
			clog << n1 << "\t" << n2 << endl;
			
			if(L_DAT == ReadColumns(L_DAT, buffer, x1, y1, x2, y2, n1, n2) ) return L_DAT;
			//int type = ReadColumns(L_DAT, buffer, x1, y1, x2, y2, n1, n2);
			//clog << "type:" << type << endl;
			//if(type) return 20; 
		}
	
		// DAT - selig
		// HEADER - name
		// [2 cols]
		// * values 0.0-1.0
		clog << "XFOIL" << endl;
		buffer.str(buckup); 
		getline(buffer, line);
		
		if(XFOIL == ReadColumns(XFOIL, buffer, x1, y1, x2, y2, 0, 0) ) {
			clog << "XFOIL" << endl;
			Xf = x1;
			Zf = y1;

			/*
    		std::vector<Person> vecOfPersons = { Person("aaa", 7), Person("kkk", 3), Person("aaa", 10), Person("kkk", 2) };
		
			std::sort(vecOfPersons.begin(), vecOfPersons.end(), [](const Person & first, const Person & sec) {
        	if (first.m_name < sec.m_name)
            	return true;
        	else
            	return false;
    		});*/
/*
    		std::vector<Person>::iterator newEnd;
    		newEnd = std::unique(vecOfPersons.begin(), vecOfPersons.end(), [](const Person & first, const Person & sec) {
        	if (first.m_name == sec.m_name)
            	return true;
        	else
            	return false;
    		}); 
  */  
			/*
    		vecOfPersons.erase( newEnd, vecOfPersons.end());
    		std::cout << "After removing duplicate Persons List based on Name\n";
    		std::for_each(vecOfPersons.begin(), vecOfPersons.end(), [](Person & obj) {
        	std::cout<<obj.m_id<< " :: "<<obj.m_name<<std::endl;
   		 	});*/

    		//std::vector<Person>::iterator newEnd;
    		/*std::unique(Xf.begin(), Xf.end(), [](double &first, double &sec) {
        	if (first == sec) {
    			//vecOfPersons.erase( newEnd, vecOfPersons.end());
				Xf.erase( unique( first, sec );
				//Zf.erase( unique( Xf.begin(), Xf.end() ), Xf.end() );

            	return true;
			}*/
        	//else
            //	return false;
    		//}); 
			//sort( vec.begin(), vec.end() );
			//Xf.erase( unique( Xf.begin(), Xf.end() ), Xf.end() );
		

			for(unsigned int i=0; i<Xf.size()-1; i++) {
				if(Xf[i] == Xf[i+1]) { 
					Xf.erase( Xf.begin()+i, Xf.begin()+i+1 ); 
					Zf.erase( Zf.begin()+i, Zf.begin()+i+1 ); 
				}
			}

			Print2col(clog);
			
			unsigned int n05 = std::distance( Xf.begin(), std::min_element(Xf.begin(), Xf.end()) );

			if(Xf.size() == 2*n05+1) {
				clog << "no interpol " << endl;
					Xd = Xg = Xf;
					Zd = Zg = Zf;
					clog << "Xg.size = " << Xg.size() << endl;

					Xg.resize(n05 + 1);
					Zg.resize(n05 + 1);
					std::reverse(Xg.begin(), Xg.end());
					std::reverse(Zg.begin(), Zg.end());
					for(unsigned int i=0; i<Xg.size(); i++) {
						Xg[i] *= 100.0;
						Zg[i] *= 100.0;
					}

					Xd.erase(Xd.begin(), Xd.begin() + n05);
					Zd.erase(Zd.begin(), Zd.begin() + n05);
					for(unsigned int i=0; i<Xd.size(); i++) {
						Xd[i] *= 100.0;
						Zd[i] *= 100.0;
					}
			}
			else { 
				clog << "interpol " << endl;
				PRF2XFOIL(); 
			}

			Print4col(clog);

			return XFOIL;
		}

		clog << "END getiTypeByContent" << endl;

		return -1; // file type not found
	}

/*
        Gets iType based on file extension
*/
int AIRFOIL::getiTypeByExt(std::string fileName)
{
	int iType;

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

	return iType;
}

	// Reads particular formats - private

	void AIRFOIL::PRF2XFOIL() {
		for(unsigned int i=0; i<Xd.size(); i++) {           
			Xf.push_back( Xd[Xd.size()-1-i]/100. );
			Zf.push_back( Zd[Xd.size()-1-i]/100. );
		}
	
		for(unsigned int i=Xg.size(); i>1; i--) {
			Xf.push_back( Xg[Xg.size()-i+1]/100. );
			Zf.push_back( Zg[Xg.size()-i+1]/100. );
		}
	}

int AIRFOIL::Write_PRF( std::string fileName )
{
	FILE  *ff;
	ff = fopen( fileName.c_str(), "w" );
	//fprintf(ff,"%d\t#\t%s\n", N, cName );
	for(unsigned int i=0; i<Xg.size(); i++)
		fprintf( ff, "%f %f %f %f\n", Xg[i], Zg[i], Xd[i], Zd[i] );
	fclose(ff);

	return 0;
}

int AIRFOIL::Read_KOO( std::string fileName )
{
	return Read_DAT( fileName );
}

	void AIRFOIL::Print2col(std::ostream &out) {
		out << name << std::endl;
		out << Xf.size() << std::endl;
		for(unsigned int i=0; i<Xf.size(); i++) {
			out << setw(12) << Xf[i] << setw(12) << Zf[i] << std::endl;
		}
	}

	void AIRFOIL::Print4col(std::ostream &out) {
		out << name << std::endl;
		out << Xg.size() << std::endl;
		for(unsigned int i=0; i<Xg.size(); i++) {
			out << setw(12) << Xg[i] << setw(12) << Zg[i] << setw(12) << Xd[i] << setw(12) << Zd[i] << std::endl;
		}
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
	Xf.resize(rowsPos+rowsNeg);
	Zf.resize(rowsPos+rowsNeg);

	//Nf = rowsPos+rowsNeg-1; //total number of points(rows) that will be in the end

	for( int i=rowsPos-1; i>=0; i-- ) {
	    ReadPar(ff, "%lf %lf",&Xf[i],&Zf[i]); //read all upper
	}

	for( int i=0; i<rowsNeg; i++ ) {
	    ReadPar(ff, "%lf %lf",&Xf[rowsPos-1 + i],&Zf[rowsPos-1 + i]); //read all lower
	}

	fclose( ff );
	
	//Check( &Nf, &Xf[0], &Zf[0] );

	XFOIL2PRF();

	return 0;
}

int AIRFOIL::Read_DAT( std::string fileName )
{
	/*FILE  *ff;
	ff = fopen( fileName.c_str(), "r" );
	if( ff == NULL )
		{
		//sprintf( comment.c_str(), "File: %s not found!\n", fileName.c_str() );
		fprintf( stderr, "File: %s not found!\n", fileName.c_str() );
		return -1;
		}

	//Nf = nLines( ff ) - 1;
	fclose( ff );
	if( Xf.size() < 6 )
		{
		//sprintf( comment.c_str(), "File: %s - the number of rows is too small!\n", fileName.c_str() ); //!!!!!!!!!!!!!!!!!!!!!!!!
		fprintf( stderr, "File: %s - the number of rows is too small!\n", fileName.c_str() );
		return -1;
		}
		
	Xf.resize(Nf+1);
	Zf.resize(Nf+1);
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
	
	Check( &Nf, &Xf[0], &Zf[0] );
	
	XFOIL2PRF();
*/
	return 0;
}

void AIRFOIL::XFOIL2PRF( void )
{
	int nmax = Xf.size();
	int nmin = Xf.size();
	double dCa = dMaxT( &Xf[0], &nmax );
	double dX0 = dMinT( &Xf[0], &nmin );
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
	    for(int i=Xf.size(); i>nmin; i--)
	        {
	        Xf[i] = Xf[i-1];
	        Zf[i] = Zf[i-1];
	        }
	    Xf[nmin] = X0;
	    Zf[nmin] = Y0;
	    //Nf++;
	    nmax++;
	    nmin++;
	    //nmax = Nf;
	    //nmin = Nf;
	    dCa = dMaxT( &Xf[0], &nmax );
	    dX0 = dMinT( &Xf[0], &nmin );
	    }
	dCa -= dX0;
	double dMnoz = 100./dCa;
	
	double dW1, dW2;
	int iSter = 0;		// 1 - lower surface first, 0 - upper surface first
	int NN = min( nmin, nmax );
	if( nmax > nmin || nmax == 0 )
		{
		dW1 = dAverage( &Zf[0], nmin );
		dW2 = dAverage( &Zf[nmin], Xf.size() - nmin );
		if( dW2 > dW1 )iSter = 1;
		NN = nmin;
		}
	else
		{
		dW1 = dAverage( &Zf[0], nmax );
		dW2 = dAverage( &Zf[nmax], nmin - nmax );
		if( dW2 > dW1 )iSter = 1;
		NN = nmax;
		}
		
	fprintf( stderr, "ReadDAT - Xfoil2Prf:\n" );
	//fprintf( stderr, "Nf = %d NN = %d iSter = %d\n", Nf, NN, iSter );
	fprintf( stderr, "max %d min %d\n", nmax, nmin );
	fprintf( stderr, "X0  %f Ca  %f\n", dX0, dCa );
	fflush( stderr );
	
	std::vector <double> Xfrob;
	Xfrob.resize( Xf.size() );
	for(unsigned int i=0; i<Xf.size(); i++ )Xfrob[i] = Xf[i];
	unsigned int N = Xf.size();
	//SortClean( &N, &Xfrob[0] );
	
	Xg.resize(N); 
	Xd.resize(N); 
	Zg.resize(N); 
	Zd.resize(N);

	if(iSter == 1)
	{
		for(unsigned int i=0; i<N; i++)
		{
			Xd[i] = Xfrob[i];
			Zd[i] = inter1( &Xf[0], &Zf[0], NN+1, Xd[i] );
			Xg[i] = Xd[i];
			Zg[i] = inter1( &Xf[NN], &Zf[NN], Xf.size()-NN, Xg[i] );
		}
	}
	else
	{
		for(unsigned int i=0; i<N; i++)
		{
			Xd[i] = Xfrob[i];
			Zd[i] = inter1( &Xf[NN], &Zf[NN], Xf.size()-NN, Xd[i] );
			Xg[i] = Xd[i];
			Zg[i] = inter1( &Xf[0], &Zf[0], NN+1, Xg[i] );
		}
	}
}

int AIRFOIL::Write_DAT( std::string fileName )
{
	FILE  *ff;
	ff = fopen( fileName.c_str(), "w" );
	fprintf(ff,"%s\n", fileName.c_str() );
	for(unsigned int i=0; i<Xf.size(); i++)
		fprintf( ff, " %f %f \n", Xf[i], Zf[i] );
	fclose(ff);
	
	return 0;
}

void AIRFOIL::TE_correct( void )
{
     //  double zz = 0.5*(Zd[N-1]+Zg[N-1]);
       // Zd[N-1] = Zg[N-1] = zz;
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
	int N = *nn;
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

	clog << "Par: " << Par << endl;

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
}
