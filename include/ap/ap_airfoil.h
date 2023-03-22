// Part of All Purpose - ap library

#ifndef AP_AIRFOIL_H
#define AP_AIRFOIL_H

#include <vector>

namespace ap
{
    //! Airfoils class
	/*! 
	 * ap::AIRFOIL class can read geometry data from file (5 commonly used fromats),
     * or generate 4-digit and 5-digit NACA airfoils.\n
	 * ap::AIRFOIL originates from part of the Config Lib for Panukl software: 
	 * https://itlims-zsis.meil.pw.edu.pl/software/PANUKL/2020/Config_API/index.html
	 * created by T.Grabowski.\n
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

		//! Sets flag for restrictive check of data when read
		/*!
		 * Additionaly data end values are checked. Values different then 0 and 1 for Xfoil format and 0, 100 for Prf format trigger failure while read.
		 * \param setFlag - flag for restrictive data checking, default false 
		 */
		void RestrictiveCheck(bool setFlag=0) { restrictiveCheck = setFlag; }

		//! Reads airfoil file
		/*!
		 * \param fileName - path to the airfoil data file
		 * \return 0 on success
		 */
		int Read(std::string fileName);

		//! Transformation from Prf format to Xfoil format
		void Prf2Xfoil();
		
		//! Transformation from Xfoil format to Prf format
		void Xfoil2Prf();

 		//! Generates NACA airfoil
		/*!
		 * \param iNACA - NACA airfoil number 
		 * \param set_n - number of points generated along airfoil chord, separately for upper and lower surfaces  
		 * \return 0 on success 
		 */
		int GenerateNaca(unsigned int iNACA, int set_n=100);

		//! Generates NACA airfoil
		/*!
		 * \param sNACA - NACA airfoil number alone, or with prefix NACA eg.: "2412", "naca 0012", or "NACA 23012"  
		 * \param set_n - number of points generated along airfoil chord, separately for upper and lower surfaces  
		 * \return 0 on success 
		 */
		int GenerateNaca(std::string sNACA, int set_n=100);

		//! Set airfoil data - two columns, Xfoil format
		/*!
		 * \param set_name - name of the airfoil, used when writing to file  
		 * \param set_xf - input data vector x in Xfoil format    
		 * \param set_zf - input data vector z in Xfoil format    
		 */
		void Set(const std::string set_name, const std::vector <double> &set_xf, const std::vector <double> &set_zf);
		
		//! Set airfoil data - four columns, prf format
		/*!
		 * \param set_name - name of the airfoil, used when writing to file  
		 * \param set_xg - input data vector xg for upper surface in Prf four column format    
		 * \param set_zg - input data vector zg for upper surface in Prf four column format
		 * \param set_xd - input data vector xd for lower surface in Prf four column format    
		 * \param set_zd - input data vector zd for lower surface in Prf four column format    
		 */
		void Set(const std::string set_name, const std::vector <double> &set_xg, const std::vector <double> &set_zg, const std::vector <double> &set_xd, const std::vector <double> &set_zd);
		
		//! Get airfoil data - two columns, Xfoil format
		/*!
		 * \param get_name - name of the airfoil  
		 * \param get_xf - output data vector x in Xfoil format    
		 * \param get_zf - output data vector z in Xfoil format    
		 */
		void Get(std::string &get_name, std::vector <double> &get_xf, std::vector <double> &get_zf);
		
		//! Get airfoil data - four columns, Prf format
		/*!
		 * \param get_name - name of the airfoil, used when writing to file  
		 * \param get_xg - output data vector xg for upper surface in Prf four column format    
		 * \param get_zg - output data vector zg for upper surface in Prf four column format
		 * \param get_xd - output data vector xd for lower surface in Prf four column format    
		 * \param get_zd - output data vector zd for lower surface in Prf four column format    
		 */
		void Get(std::string &get_name, std::vector <double> &get_xg, std::vector <double> &get_zg, std::vector <double> &get_xd, std::vector <double> &get_zd);

		//! Prints 2 column data
		/*!
		 * Data in Xfoil two column format is passed to the standard output stream.\n
		 * \param out - standard output stream  
		 * \note The output stream can be formated, for example numbers precision and directed on screen, or to file.
		 */
		void Print2col(std::ostream &out);

		//! Prints 4 column data
		/*!
		 * Data in Prf four column format is passed to the standard output stream.\n
		 * \param out - standard output stream  
		 * \note The output stream can be formated, for example numbers precision and directed on screen, or to file.
		 */
		void Print4col(std::ostream &out);
		
		//! Write airfoil to file in Xfoil two column format
		/*!
		 * \param fileName - path to the output airfoil file
		 * \param precision - airfoil coordinates precision, default 6 digits
		 */
		int WriteDat(std::string fileName, unsigned int precision=6);

		//! Write airfoil to file in Prf four column format
		/*!
		 * \param fileName - path to the output airfoil file
		 * \param precision - airfoil coordinates precision, default 6 digits
		 */
		int WritePrf(std::string fileName, unsigned int precision=6);
		
		//! Close TE gap
		/*!
		 * Sets TE thickness to 0.
		 * \param blend - blending distance coefficient between 0 and 1, defines how many points on the airfoil will be modified, default 0.8
		 */
		void TEclose(double blend=0.8);
	
		//! Normalize airfoil
		/*!
		 * - Translate airfoil that LE coordinates are (0,0)
		 * - Derotate airfoil that TE z coordinate is 0
		 * - Scale airfoil that TE x coordinate is 0
		 */
		void Normalize();
	};
}

#endif // AP_AIRFOIL_H


