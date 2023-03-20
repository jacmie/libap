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

namespace ap
{
	int AIRFOIL::ReadColumns(const int type, std::stringstream &buffer, 
		std::vector <double> &x1, std::vector <double> &z1, std::vector <double> &x2, std::vector <double> &z2, 
		const unsigned int n1, const unsigned int n2)
	{
		x1.resize(0);
		z1.resize(0);
		x2.resize(0);
		z2.resize(0);

		std::string rxNum("([-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)");
		std::string col2 = std::string(".*") + rxNum + std::string("\\s+") + rxNum + std::string(".*");
		std::string col3 = col2 + rxNum + std::string("\\s+") + rxNum + std::string(".*");
		std::string col4 = col3 + rxNum + std::string("\\s+") + rxNum + std::string(".*");
		std::regex rxcol2(col2);
		std::regex rxcol3(col3);
		std::regex rxcol4(col4);

		std::string line;
		double x1_, y1_, x2_, y2_;

		// === Check number of columns, format and count data rows ===
		while( !buffer.eof() ) {
			getline(buffer, line);
			if( 0 == line.length() ) continue;
			
			switch(type) { // one of the lines has incorrect format
				case PRF_4: { if(!regex_match(line, rxcol4)) return 20; break; }
				case PRF_3: { if(!regex_match(line, rxcol3)) return 21; break; }
				case PRF_2: { if(!regex_match(line, rxcol2)) return 22; break; }
				case KOO:   { if(!regex_match(line, rxcol2)) return 23; break; }
				case XFOIL: { if(!regex_match(line, rxcol2)) return 24; break; }
				case L_DAT: { if(!regex_match(line, rxcol2)) return 25; break; }
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
			z1.push_back(y1_);
			if(type == PRF_4) {
				x2.push_back(x2_);
				z2.push_back(y2_);
			}
		}
		
		// === Check declared vs counted data rows ===
		switch(type) { 
			case PRF_4: { if(x1.size() != n1) return 30; break; }
			case PRF_3: { if(x1.size() != n1) return 31; break; }
			case PRF_2: { if(x1.size() != n1) return 32; break; }
			case KOO:   { if(x1.size() != n1+1) return 33; break; }
			case XFOIL: { break; } // no declared nr of data rows
			case L_DAT: { if(x1.size() != n1+n2) return 35; break; }
		}

		// === Check data end values ===
		if(restrictiveCheck) {
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
					if(x1[0] != 0.0) { return 42; }
					if(x1[x1.size()-1] != 100.0) { return 42; }
					break; 
					}
				case KOO:   { 
					if(x1[0] != 100.0) { return 43; }
					if(x1[x1.size()-1] != 100.0) { return 43; }
					break; 
					}
				case XFOIL: {
					if(x1[0] != 1.0) { return 44; }
					if(x1[x1.size()-1] != 1.0) { return 44; }
					break;
					}
				case L_DAT: { 
					if(x1[0] != 0.0 		&& x1[0] != 1.0) { return 45; }
					if(x1[n1-1] != 0.0 		&& x1[n1-1] != 1.0) { return 45; }
					if(x1[n1] != 0.0 		&& x1[n1] != 1.0) { return 45; }
					if(x1[n1+n2-1] != 0.0 	&& x1[n1+n2-1] != 1.0) { return 45; }
					break; 
					}
			}
		}

		// === Arrange data tables ===
		switch(type) {
			case PRF_4: { break; }  
			case PRF_3:  
			case PRF_2: {
					x2 = x1;
					z2 = z1;
					x1.resize(0.5*n1 + 1);
					z1.resize(0.5*n1 + 1);
					x2.erase(x2.begin(), x2.begin() + 0.5*n1);
					z2.erase(z2.begin(), z2.begin() + 0.5*n1);
					x2[0] = x1[0];
					z2[0] = z1[0];
					break; 
					}
			case KOO: { 
					for(unsigned int i=0; i<x1.size(); i++) {
						x1[i] *= 0.01;
						z1[i] *= 0.01;
					}
					break; 
					}
			case XFOIL: {
					// find minimum element
					unsigned int nMin = std::distance( x1.begin(), std::min_element(x1.begin(), x1.end()) );
					// sort according to Xfoil convention
					double front = std::accumulate(&z1[0], &z1[0]+nMin, 0.0);
					double rear  = std::accumulate(&z1[0]+nMin, &z1[0]+z1.size()-1, 0.0);
					unsigned int nFront = nMin;
					unsigned int nRear  = z1.size() - nMin;
					if( front/nFront < rear/nRear ) {
						std::reverse(x1.begin(), x1.end());
						std::reverse(z1.begin(), z1.end());
					} 
					break; 
					}
			case L_DAT: { 
					x2 = x1;
					z2 = z1;
					x1.resize(n1);
					z1.resize(n1);
					x2[0] = x1[0];
					z2[0] = z1[0];
					x2.erase(x2.begin(), x2.begin() + n1+1);
					z2.erase(z2.begin(), z2.begin() + n1+1);
					std::reverse(x1.begin(), x1.end());
					std::reverse(z1.begin(), z1.end());
					x1.insert(x1.end(), x2.begin(), x2.end());
					z1.insert(z1.end(), z2.begin(), z2.end());
					break; 
					}
		}

		return type;
	}

	int AIRFOIL::Read(std::string fileName)
	{
		name = "";
		xf.resize(0);
		zf.resize(0);
		xg.resize(0);
		zg.resize(0);
		xd.resize(0);
		zd.resize(0);
	
		std::vector <double> x1;
		std::vector <double> y1;
		std::vector <double> x2;
		std::vector <double> y2;

		std::ifstream in(fileName);
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
		std::regex integer("\\s*\\d+\\s*");   						// positive integer
		std::regex number("\\s*(\\+|-)?[\\d\\.]+\\s*");   			// 1 22 1.2 0.2 .2  2. - any number
		std::regex prfHeader("\\d+\\s+#\\s+.+");					// number_of_lines # name (e.g. "18	#	NACA 0012	")
		std::regex kooHeader(".+\\s+,\\s+\\d+");					// name , number_of_lines-1
		std::regex datNLines("\\s*\\d+\\.\\s*\\d+\\.\\s*");			// 31.  31.

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
			
			name = line.substr(line.find_first_of("#") + 1);
			name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
			name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);

			if(PRF_4 == ReadColumns(PRF_4, buffer, x1, y1, x2, y2, n, 0) ) {
				xg = x1;
				zg = y1;
				xd = x2;
				zd = y2;

				Prf2Xfoil();
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
			
			name = fileName.substr( fileName.find_last_of("\\/") + 1 );
			name = name.substr( 0, name.find_last_of(".") );

			if(PRF_3 == ReadColumns(PRF_3, buffer, x1, y1, x2, y2, n, 0) ) { 
				xg = x1;
				zg = y1;
				xd = x2;
				zd = y2;

				Prf2Xfoil();
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

				Prf2Xfoil();
				return PRF_2;
			}
		}

		// KOO
		// HEADER - name , number_of_lines-1
		// [2 cols]
		// * values 0-100
		buffer.str(buckup); 
		getline(buffer, line);
		if(regex_match(line, kooHeader))
		{
			std::size_t coma = line.find_first_of(","); //get number of lines
			name = line.substr(0, coma);
			name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
			name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);
			int n = stoi( line.substr(coma + 1) );
		
			if(KOO == ReadColumns(KOO, buffer, x1, y1, x2, y2, n, 0) ) {
				xf = x1;
				zf = y1;
				RemoveDoubleDataRows(xf, zf);

				Xfoil2Prf();
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
		buffer.str(buckup); 
		getline(buffer, line);
		name = line;
		name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
		name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);
		getline(buffer, line);
		if(std::regex_match(line, datNLines))
		{
			float n1, n2;
			std::stringstream ss;
			ss.str(line);
			ss >> n1 >> n2;
			
			if(L_DAT == ReadColumns(L_DAT, buffer, x1, y1, x2, y2, n1, n2) ) {
				xf = x1;
				zf = y1;
				RemoveDoubleDataRows(xf, zf);

				Xfoil2Prf();
				return L_DAT;
			}
		}
	
		// DAT - xfoil
		// HEADER - name
		// [2 cols]
		// * values 0.0-1.0
		buffer.str(buckup); 
		getline(buffer, line);
		name = line;
		name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
		name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);
		if(XFOIL == ReadColumns(XFOIL, buffer, x1, y1, x2, y2, 0, 0) ) {
			xf = x1;
			zf = y1;
			RemoveDoubleDataRows(xf, zf);

			Xfoil2Prf();
			return XFOIL;
		}

		return -1; // file type not found
	}

	void AIRFOIL::SetInterpolationData(std::vector <double> &xin, std::vector <double> &yin, std::vector <double> &xdata, std::vector <double> &zdata, double &xinterp) {
		std::vector <double>::iterator low;
		low = std::lower_bound(xdata.begin(), xdata.end(), xinterp);

		unsigned int d = std::distance(xdata.begin(), low);
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
	}

	// Lagrange interpolation
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

	// Remove subsequent doubled rows
	void AIRFOIL::RemoveDoubleDataRows(std::vector <double> &x, std::vector <double> &z) {
		for(unsigned int i=0; i<x.size()-1; i++) {
			if(x[i] == x[i+1]) { 
				x.erase( x.begin()+i, x.begin()+i+1 ); 
				z.erase( z.begin()+i, z.begin()+i+1 ); 
			}
		}
	}
	
	void AIRFOIL::ReversTabs(std::vector <double> &x, std::vector <double> &z) {
		std::reverse(x.begin(), x.end());
		std::reverse(z.begin(), z.end());
	}
	
	void AIRFOIL::ResizeTabs(std::vector <double> &x, std::vector <double> &z, const unsigned int &setSize) {
		x.resize(setSize);
		z.resize(setSize);
	}

	void AIRFOIL::ScaleTabs(std::vector <double> &x, std::vector <double> &z, const double &scale) {
		for(unsigned int i=0; i<x.size(); i++) {
			x[i] *= scale;
			z[i] *= scale;
		}
	}
	
	void AIRFOIL::EraseTabsElements(std::vector <double> &x, std::vector <double> &z, const unsigned int &toElem) {
		x.erase(x.begin(), x.begin() + toElem);
		z.erase(z.begin(), z.begin() + toElem);
	}

	void AIRFOIL::Prf2Xfoil() {
		for(unsigned int i=0; i<xd.size(); i++) {           
			xf.push_back( xd[xd.size()-1-i]/100. );
			zf.push_back( zd[xd.size()-1-i]/100. );
		}
	
		for(unsigned int i=xg.size(); i>1; i--) {
			xf.push_back( xg[xg.size()-i+1]/100. );
			zf.push_back( zg[xg.size()-i+1]/100. );
		}
	}

	void AIRFOIL::Xfoil2Prf()
	{
			unsigned int nMin = std::distance( xf.begin(), std::min_element(xf.begin(), xf.end()) );

			if(xf.size() == 2*nMin+1) { // equal data division
					xd = xg = xf;
					zd = zg = zf;

					ResizeTabs(xg, zg, nMin+1);
					ReversTabs(xg, zg);
					ScaleTabs(xg, zg, 100);

					EraseTabsElements(xd, zd, nMin);
					ScaleTabs(xd, zd, 100);
			}
			else { // interpolation needed
				std::vector <double> xin;
				std::vector <double> yin;
				xin.resize(3);
				yin.resize(3);
				
				if( nMin > 0.5*xf.size() - 1 ) {
					xg = xf;
					zg = zf;

					ResizeTabs(xg, zg, nMin+1);
					ReversTabs(xg, zg);
					ScaleTabs(xg, zg, 100);

					xd = xg;
					zd.assign(xd.size(), 0.0);
					zd[0] = zg[0];
					zd[zg.size()-1] = zg[zg.size()-1];

					std::vector <double> xdata;
					std::vector <double> zdata;
					xdata = xf;
					zdata = zf;

					EraseTabsElements(xdata, zdata, nMin);
					ScaleTabs(xdata, zdata, 100);

					for(unsigned int i=1; i<xg.size()-1; i++) {
						SetInterpolationData(xin, yin, xdata, zdata, xg[i]);
						zd[i] = L_interp(xin, yin, xg[i]);
					}
					
				}
				else {
					xd = xf;
					zd = zf;

					EraseTabsElements(xd, zd, nMin);
					ScaleTabs(xd, zd, 100);

					xg = xd;
					zg.assign(xd.size(), 0.0);
					zg[0] = zd[0];
					zg[zd.size()-1] = zd[zd.size()-1];

					std::vector <double> xdata;
					std::vector <double> zdata;
					xdata = xf;
					zdata = zf;

					ResizeTabs(xdata, zdata, nMin+1);
					ScaleTabs(xdata, zdata, 100);
					ReversTabs(xdata, zdata);

					for(unsigned int i=1; i<xd.size()-1; i++) {
						SetInterpolationData(xin, yin, xdata, zdata, xd[i]);
						zg[i] = L_interp(xin, yin, xg[i]);
					}
				}
			}
	}
	
	int AIRFOIL::Set(const std::string set_name, const std::vector <double> &set_xg, const std::vector <double> &set_zg, const std::vector <double> &set_xd, const std::vector <double> &set_zd)
	{
		name = set_name;
		xg = set_xg;
		zg = set_zg;
		xd = set_xd;
		zd = set_zd;

		return 0;
	}

	int AIRFOIL::GenerateNaca(unsigned int iNACA, int n) {
		std::string str;
    	std::stringstream ss;
    	ss << iNACA;
    	ss >> str;
		
		return GenerateNaca(str, n);
	}

	int AIRFOIL::GenerateNaca(std::string NACA, int n) {
		if(NACA.size() <= 5) name = "NACA " + NACA;
		else name = NACA;

		NACA_AIRFOIL nacaAirfoil;
		nacaAirfoil.GenerateNaca(NACA, n);
		nacaAirfoil.GetVectors(xf, zf);
		
		Xfoil2Prf();
	
		return 0;
	}


	void AIRFOIL::Print2col(std::ostream &out) {
		for(unsigned int i=0; i<xf.size(); i++) {
			out << std::setw(12) << xf[i] << std::setw(12) << zf[i] << std::endl;
		}
	}

	void AIRFOIL::Print4col(std::ostream &out) {
		for(unsigned int i=0; i<xg.size(); i++) {
			out << std::setw(12) << xg[i] << std::setw(12) << zg[i] << std::setw(12) << xd[i] << std::setw(12) << zd[i] << std::endl;
		}
	}

	int AIRFOIL::WriteDat(std::string fileName, unsigned int precision) {
		std::ofstream out(fileName);
		if(!out) return 1;

		out << name << std::endl;
		out << std::fixed << std::setprecision(precision);
		Print2col(out);
		out.close();
	
		return 0;
	}

	int AIRFOIL::WritePrf(std::string fileName, unsigned int precision) {
		std::ofstream out(fileName);
		if(!out) return 1;

		out << std::setw(4) << xg.size() << "  #  " << name << std::endl;
		out << std::fixed << std::setprecision(precision);
		Print4col(out);
		out.close();

		return 0;
	}

	void AIRFOIL::TE_correct( void )
	{
     //  double zz = 0.5*(Zd[N-1]+Zg[N-1]);
       // Zd[N-1] = Zg[N-1] = zz;
	}

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
}
