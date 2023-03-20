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
		std::string name;

		std::vector <double> xf;  ///< x coordinates (Xfoil format)
		std::vector <double> zf;  ///< z coordinates (Xfoil format)
	
		std::vector <double> xg;  ///< x coordinates of upper contour (prf points)
		std::vector <double> xd;  ///< x coordinates of lower contour (prf points)
		std::vector <double> zg;  ///< z coordinates of upper contour (prf points)
		std::vector <double> zd;  ///< z coordinates of lower contour (prf points)

		enum airfoilFileType {PRF_4=0, PRF_3, PRF_2, KOO, XFOIL, L_DAT};

		bool restrictiveCheck = 0;

		int ReadColumns(const int type, std::stringstream &buffer, 
			std::vector <double> &x1, std::vector <double> &z1, std::vector <double> &x2, std::vector <double> &z2, 
			const unsigned int n1, const unsigned int n2);

		// Maths
		void SetInterpolationData(std::vector <double> &xin, std::vector <double> &yin, std::vector <double> &xdata, std::vector <double> &zdata, double &xinterp);
		double L_interp(const std::vector <double> &x, const std::vector <double> &y, const double &xi); 
		
		// Utils
		void RemoveDoubleDataRows(std::vector <double> &x, std::vector <double> &z);
		void ReversTabs(std::vector <double> &x, std::vector <double> &z);
		void ResizeTabs(std::vector <double> &x, std::vector <double> &z, const unsigned int &setSize); 
		void ScaleTabs(std::vector <double> &x, std::vector <double> &z, const double &scale);
		void EraseTabsElements(std::vector <double> &x, std::vector <double> &z, const unsigned int &toElem);

	public:
	
		AIRFOIL() = default;

		//! Sets flag for restrictive check of data that is read.
		//! Deffault false, allows end values different then 0 and 1 for Xfoil and 0 100 for Prf.
		void RestrictiveCheck(bool setFlag=0) { restrictiveCheck = setFlag; }

		//! Reads airfoil file
		int Read(std::string fileName);

		//! Transformation from Prf format to Xfoil format
		void Prf2Xfoil();
		
		//! Transformation from Xfoil format to Prf format
		void Xfoil2Prf();

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

		//! Prints 2 column data
		void Print2col(std::ostream &out);

		//! Prints 4 column data
		void Print4col(std::ostream &out);
		
		//! Write airfoil in Xfoil format
		int WriteDat(std::string fileName, unsigned int precision=6);

		//! Write airfoil in Prf format
		int WritePrf(std::string fileName, unsigned int precision=6);
		
		//! Close TE gap
		int TE_close(double blend);
	
		//! Normalize airfoil
		void Normalize();
	};
}

#endif // AP_AIRFOIL_H


