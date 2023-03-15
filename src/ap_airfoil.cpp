// Part of All Purpose - ap library

#include <regex>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>

#include "ap_airfoil.h"
#include "ap_naca.h"

using namespace std;

namespace ap
{
	int AIRFOIL::Set(const std::string set_name, const std::vector <double> &set_xg, const std::vector <double> &set_zg, const std::vector <double> &set_xd, const std::vector <double> &set_zd)
	{
		name = set_name;
		xg = set_xg;
		zg = set_zg;
		xd = set_xd;
		zd = set_zd;

		return 0;
	}

	int AIRFOIL::Read( std::string fileName )
	{
		int iType = ReadContent(fileName); 

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

	int AIRFOIL::GenerateNaca(unsigned int iNACA, int n)
	{
		char cNACA[10];
		//sprintf(cNACA, "%04ld", iNACA );
		return GenerateNaca(cNACA, n);
	}

	int AIRFOIL::GenerateNaca(std::string NACA, int n)
	{
		//Name = "NACA " + NACA;

		NACA_PROFILE *NacaProfile = new NACA_PROFILE();
		NacaProfile->setTE0( 1 );
		NacaProfile->generate_naca(NACA, n);
	
		xf.resize(NacaProfile->N + 1); 
		zf.resize(NacaProfile->N + 1); 

		for(unsigned int i=0; i<xf.size(); i++)
		{
			xf[i] = NacaProfile->X[i];
			zf[i] = NacaProfile->Z[i];
		}
		
		//DELETE_(NacaProfile);
		
		XFOIL2PRF();
	
		return 0;
	}

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

		// === Check number of columns, format and count data rows ===
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
		switch(type) { 
			case PRF_4: { if(x1.size() != n1) return 30; break; }
			case PRF_3: { if(x1.size() != n1) return 30; break; }
			case PRF_2: { if(x1.size() != n1) return 30; break; }
			case KOO:   { if(x1.size() != n1+1) return 30; break; }
			case XFOIL: { break; } // no declared nr of data rows
			case L_DAT: { if(x1.size() != n1+n2) return 30; break; }
		}

		// === Check data end values ===
		switch(type) { 
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

		// === Arrange data tables ===
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
					}*/
			case L_DAT: { 
					x2 = x1;
					y2 = y1;
					x1.resize(n1);
					y1.resize(n1);
					x2[0] = x1[0];
					y2[0] = y1[0];
					x2.erase(x2.begin(), x2.begin() + n1+1);
					y2.erase(y2.begin(), y2.begin() + n1+1);
					std::reverse(x1.begin(), x1.end());
					std::reverse(y1.begin(), y1.end());
					x1.insert(x1.end(), x2.begin(), x2.end());
					y1.insert(y1.end(), y2.begin(), y2.end());
					break; 
					}
		}

		return type;
	}

	int AIRFOIL::ReadContent(std::string fileName)
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
				xg = x1;
				zg = y1;
				xd = x2;
				zd = y2;

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
				xg = x1;
				zg = y1;
				xd = x2;
				zd = y2;

				Print4col(clog);
				
				PRF2XFOIL();
				Print2col(clog);

				return PRF_3;
			}
		
			buffer.str(buckup); 
			getline(buffer, line); // first line is a number, can be whatever - read second line then
			getline(buffer, line);
			if(PRF_2 == ReadColumns(PRF_2, buffer, x1, y1, x2, y2, n, 0) ) {
				xg = x1;
				zg = y1;
				xd = x2;
				zd = y2;

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
		
			if(KOO == ReadColumns(KOO, buffer, x1, y1, x2, y2, n, 0) ) {
				xf = x1;
				zf = y1;
				for(unsigned int i=0; i<xf.size(); i++) {
					xf[i] *= 0.01;
					zf[i] *= 0.01;
				}

				Print2col(clog);
				XFOIL2PRF();
				Print4col(clog);
			
				return KOO;
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
			
			if(L_DAT == ReadColumns(L_DAT, buffer, x1, y1, x2, y2, n1, n2) ) {
				xf = x1;
				zf = y1;

				Print2col(clog);
				XFOIL2PRF();
				Print4col(clog);

				return L_DAT;
			}
		}
	
		// DAT - xfoil
		// HEADER - name
		// [2 cols]
		// * values 0.0-1.0
		clog << "XFOIL" << endl;
		buffer.str(buckup); 
		getline(buffer, line);
		
		if(XFOIL == ReadColumns(XFOIL, buffer, x1, y1, x2, y2, 0, 0) ) {
			clog << "XFOIL" << endl;
			xf = x1;
			zf = y1;
		
			// === remove subsequent doubled rows ===
			for(unsigned int i=0; i<xf.size()-1; i++) {
				if(xf[i] == xf[i+1]) { 
					xf.erase( xf.begin()+i, xf.begin()+i+1 ); 
					zf.erase( zf.begin()+i, zf.begin()+i+1 ); 
				}
			}

			Print2col(clog);
			
			// === find minimum element ===
			unsigned int nMin = std::distance( xf.begin(), std::min_element(xf.begin(), xf.end()) );

			for(unsigned int i=0; i<=nMin; i++) clog << i << "\t" << zf[i] << endl;
			clog << nMin << endl;
			for(unsigned int i=nMin; i<=zf.size()-1; i++) clog << i << "\t" << zf[i] << endl;
			clog << zf.size()-nMin << endl;


			// === sort according to Xfoil convention ===
			double front = std::accumulate(&zf[0], &zf[0]+nMin, 0.0);
			double rear  = std::accumulate(&zf[0]+nMin, &zf[0]+zf.size()-1, 0.0);
			unsigned int nFront = nMin;
			unsigned int nRear  = zf.size() - nMin;
			clog << front/nMin << "\t" << rear/(zf.size()-nMin) << endl;
			
			if( front/nFront < rear/nRear ) {
				std::reverse(xf.begin(), xf.end());
				std::reverse(zf.begin(), zf.end());
			}

			Print2col(clog);
			XFOIL2PRF();
			Print4col(clog);

			return XFOIL;
		}

		clog << "END getiTypeByContent" << endl;

		return -1; // file type not found
	}

	double AIRFOIL::L_interp(const std::vector <double> &x, const std::vector <double> &y, const double &xi) {
		double l, L = 0;

		for(unsigned int i=0; i<x.size(); i++) {
			l = 1;

			for(unsigned int j=0; j<x.size(); j++) {
				if(i == j) continue;
				l *= ((xi - x[j])/(x[i] - x[j]));
			}

			L += l*y[i];
		}

		return L;
	}

	void AIRFOIL::XFOIL2PRF()
	{
			unsigned int nMin = std::distance( xf.begin(), std::min_element(xf.begin(), xf.end()) );

			if(xf.size() == 2*nMin+1) { // equal data division
				clog << "no interpol " << endl;
					xd = xg = xf;
					zd = zg = zf;
					clog << "Xg.size = " << xg.size() << endl;

					xg.resize(nMin + 1);
					zg.resize(nMin + 1);
					std::reverse(xg.begin(), xg.end());
					std::reverse(zg.begin(), zg.end());
					for(unsigned int i=0; i<xg.size(); i++) {
						xg[i] *= 100.0;
						zg[i] *= 100.0;
					}

					xd.erase(xd.begin(), xd.begin() + nMin);
					zd.erase(zd.begin(), zd.begin() + nMin);
					for(unsigned int i=0; i<xd.size(); i++) {
						xd[i] *= 100.0;
						zd[i] *= 100.0;
					}
			}
			else { // interpolation needed
				clog << "interpol " << endl;
	
				vector <double> xin;
				vector <double> yin;
				xin.resize(3);
				yin.resize(3);
				
				xin[0] = 0;
				xin[1] = 2;
				xin[2] = 4;
				yin[0] = 0;
				yin[1] = 4;
				yin[2] = 16;

				clog << L_interp(xin, yin, 3) << endl;

				clog << nMin << "\t" << 0.5*xf.size() - 1 << endl;
				
				if( nMin > 0.5*xf.size() - 1 ) {
					xg = xf;
					zg = zf;

					xg.resize(nMin + 1);
					zg.resize(nMin + 1);
					std::reverse(xg.begin(), xg.end());
					std::reverse(zg.begin(), zg.end());
					for(unsigned int i=0; i<xg.size(); i++) {
						xg[i] *= 100.0;
						zg[i] *= 100.0;
					}

					xd = xg;
					zd.assign(xd.size(), 0.0);
					zd[0] = zg[0];
					zd[zg.size()-1] = zg[zg.size()-1];

					std::vector <double> xdata;
					std::vector <double> zdata;
					xdata = xf;
					zdata = zf;

					xdata.erase(xdata.begin(), xdata.begin() + nMin);
					zdata.erase(zdata.begin(), zdata.begin() + nMin);
					for(unsigned int i=0; i<xdata.size(); i++) {
						xdata[i] *= 100.0;
						zdata[i] *= 100.0;
					}

					for(unsigned int i=1; i<xg.size()-1; i++)
					{
						//clog << xdata[i] << "\t" << zdata[i] << endl;

						std::vector <double>::iterator low, up;
  						low = std::lower_bound(xdata.begin(), xdata.end(), xg[i]);

						unsigned int d = std::distance(xdata.begin(), low);
						clog << d << "\t" << xdata[std::distance(xdata.begin(), low)] << "\t" << xg[i] << "\t";
		
						unsigned int shift = 0;

						if(d==0) shift = -1;
						if(d>0 && d<xdata.size()-1)
						if(d==xdata.size()-1) shift = 1;
						
						xin[0] = xdata[d-1+shift];
						xin[1] = xdata[d+shift];
						xin[2] = xdata[d+1+shift];
						yin[0] = zdata[d-1+shift];
						yin[1] = zdata[d+shift];
						yin[2] = zdata[d+1+shift];

						zd[i] = L_interp(xin, yin, xg[i]);
						
						clog << zd[i] << endl;
					}
					
				}
				else {
					clog << "IN" << endl;
					
					xd = xf;
					zd = zf;

					xd.erase(xd.begin(), xd.begin() + nMin);
					zd.erase(zd.begin(), zd.begin() + nMin);
					for(unsigned int i=0; i<xd.size(); i++) {
						xd[i] *= 100.0;
						zd[i] *= 100.0;
					}

					xg = xd;
					zg.assign(xd.size(), 0.0);
					zg[0] = zd[0];
					zg[zd.size()-1] = zd[zd.size()-1];

					std::vector <double> xdata;
					std::vector <double> zdata;
					xdata = xf;
					zdata = zf;

					xdata.resize(nMin+1);
					zdata.resize(nMin+1);
					for(unsigned int i=0; i<xdata.size(); i++) {
						xdata[i] *= 100.0;
						zdata[i] *= 100.0;
					}
					std::reverse(xdata.begin(), xdata.end());
					std::reverse(zdata.begin(), zdata.end());

					clog << endl;
					for(unsigned int i=0; i<xdata.size(); i++)
					{
						clog << xdata[i] << "\t" << zdata[i] << endl;
					}
					clog << endl;

					for(unsigned int i=1; i<xd.size()-1; i++)
					{
						std::vector <double>::iterator low, up;
  						low = std::upper_bound(xdata.begin(), xdata.end(), xd[i]);

						unsigned int d = std::distance(xdata.begin(), low);
						clog << i << "\t" << d << "\t" << xdata[std::distance(xdata.begin(), low)] << "\t" << xd[i] << "\t";
		
						unsigned int shift = 0;

						if(d==0) shift = -1;
						if(d>0 && d<xdata.size()-1)
						if(d==xdata.size()-1) shift = 1;
						
						xin[0] = xdata[d-1+shift];
						xin[1] = xdata[d+shift];
						xin[2] = xdata[d+1+shift];
						yin[0] = zdata[d-1+shift];
						yin[1] = zdata[d+shift];
						yin[2] = zdata[d+1+shift];

						zg[i] = L_interp(xin, yin, xg[i]);
						
						clog << zg[i] << endl;
					}
				}
			}
	}

	// Reads particular formats - private

	void AIRFOIL::PRF2XFOIL() {
		for(unsigned int i=0; i<xd.size(); i++) {           
			xf.push_back( xd[xd.size()-1-i]/100. );
			zf.push_back( zd[xd.size()-1-i]/100. );
		}
	
		for(unsigned int i=xg.size(); i>1; i--) {
			xf.push_back( xg[xg.size()-i+1]/100. );
			zf.push_back( zg[xg.size()-i+1]/100. );
		}
	}

	void AIRFOIL::Print2col(std::ostream &out) {
		out << name << std::endl;
		for(unsigned int i=0; i<xf.size(); i++) {
			out << setw(12) << xf[i] << setw(12) << zf[i] << std::endl;
		}
	}

	void AIRFOIL::Print4col(std::ostream &out) {
		out << name << std::endl;
		for(unsigned int i=0; i<xg.size(); i++) {
			out << setw(12) << xg[i] << setw(12) << zg[i] << setw(12) << xd[i] << setw(12) << zd[i] << std::endl;
		}
	}

int AIRFOIL::Write_PRF( std::string fileName )
{
/*	FILE  *ff;
	ff = fopen( fileName.c_str(), "w" );
	//fprintf(ff,"%d\t#\t%s\n", N, cName );
	for(unsigned int i=0; i<Xg.size(); i++)
		fprintf( ff, "%f %f %f %f\n", Xg[i], Zg[i], Xd[i], Zd[i] );
	fclose(ff);*/

	return 0;
}

int AIRFOIL::Write_DAT( std::string fileName )
{
/*	FILE  *ff;
	ff = fopen( fileName.c_str(), "w" );
	fprintf(ff,"%s\n", fileName.c_str() );
	for(unsigned int i=0; i<Xf.size(); i++)
		fprintf( ff, " %f %f \n", Xf[i], Zf[i] );
	fclose(ff);*/
	
	return 0;
}

void AIRFOIL::TE_correct( void )
{
     //  double zz = 0.5*(Zd[N-1]+Zg[N-1]);
       // Zd[N-1] = Zg[N-1] = zz;
}
}
