// Part of All Purpose - ap library

#ifndef AP_AIRFOIL_H
#define AP_AIRFOIL_H

#include <vector>

namespace ap
{
    //! Airfoil class
	/*! 
	 * ap::AIRFOIL originates as part of the Config Lib for Panukl software: 
	 * https://itlims-zsis.meil.pw.edu.pl/software/PANUKL/2020/Config_API/index.html
	 * created by T.Grabowski.\n
	 * ap::AIRFOIL class can read geometry data from file (5 commonly used fromats),
     * or generate 4-digit and 5-digit NACA airfoils.\n
	*/
	class AIRFOIL
	{
		enum airfoilFileType {PRF_4=0, PRF_3, PRF_2, KOO, XFOIL, L_DAT};

		int ReadColumns(const int type, std::stringstream &buffer, 
			std::vector <double> &x1, std::vector <double> &y1, std::vector <double> &x2, std::vector <double> &y2, 
			const unsigned int n1, const unsigned int n2);
		int ReadContent(std::string fileName);

		// Transformations
		void PRF2XFOIL();
		void XFOIL2PRF();

		// Maths
		double L_interp(const std::vector <double> &x, const std::vector <double> &y, const double &xi); 

		std::string name;

		std::vector <double> xf;  ///< x coordinates (Xfoil format)
		std::vector <double> zf;  ///< z coordinates (Xfoil format)
	
		std::vector <double> xg;  ///< x coordinates of upper contour (prf points)
		std::vector <double> xd;  ///< x coordinates of lower contour (prf points)
		std::vector <double> zg;  ///< z coordinates of upper contour (prf points)
		std::vector <double> zd;  ///< z coordinates of lower contour (prf points)

	public:
	
		AIRFOIL() = default;

		//! Reads airfoil file
		int Read(std::string fileName);

		//! Generates NACA airfoil given by long int value (e.g. iNACA = 23012), \n NN - the number of points that define the airfoil geometry
		int GenerateNaca(unsigned int iNACA, int n=100);

		//! Generates NACA airfoil given by string (e.g. cNACA = "23012"), \n NN - the number of points that define the airfoil geometry
		int GenerateNaca(std::string NACA, int n=100);

		//! Set airfoil data - two columns, Xfoil format
		int Set(const std::string set_name, const std::vector <double> &set_xf, const std::vector <double> &set_zf);
		
		//! Set airfoil data - four columns, prf format
		int Set(const std::string set_name, const std::vector <double> &set_xg, const std::vector <double> &set_zg, const std::vector <double> &set_xd, const std::vector <double> &set_zd);
		
		//! Get airfoil data - two columns, Xfoil format
		int Get(std::string get_name, std::vector <double> &get_xf, std::vector <double> &get_zf);
		
		//! Get airfoil data - four columns, prf format
		int Get(std::string get_name, std::vector <double> &get_xg, std::vector <double> &get_zg, std::vector <double> &get_xd, std::vector <double> &get_zd);

		//! prints 2 column data
		void Print2col(std::ostream &out);

		//! prints 4 column data
		void Print4col(std::ostream &out);
		
		int WriteDat(std::string fileName, unsigned int precision=6);

		int WritePrf(std::string fileName, unsigned int precision=6);
		
		void TE_correct();
	};
}

#endif // AP_AIRFOIL_H


