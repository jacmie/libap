// Part of All Purpose - ap library

#ifndef AP_NACA_H
#define AP_NACA_H

#include <vector>
#include <string>

namespace ap
{
	//! NACA airfoils class
	/*! 
	 * Generates 4-digit and 5-digit naca airfoils. \n 
	 * ap::NACA_AIRFOIL originates from part of the Config Lib for Panukl software: 
	 * https://itlims-zsis.meil.pw.edu.pl/software/PANUKL/2020/Config_API/index.html
	 * created by T.Grabowski.\n\n
	*/
	class NACA_AIRFOIL
	{
		enum series {FOUR_DIGIT, FIVE_DIGIT};
	
		//! A struct containing airfoil data
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

		double A_[5];
		NACA_AIRFOIL_DATA data_;

		std::vector <double> x_;	///< x coordinates vector
		std::vector <double> z_;	///< z coordinates vecotr

		std::string CheckName(std::string &name);
		bool GetParams(const std::string &name);
		double ytFunc(const double &x, const double &thmax );

		double sqr(const double &x) { return x*x; };
		double cube(const double &x) { return x*x*x; };
		void CamberFour(double *yc, double *slope, 
			const double &x, const double &maxor, const double &posmax);
		void CamberFive(double *yc, double *slope, 
			const double &x, const double &maxor, const double &posmax, const double &k1, const int &iReflex);
		
		void OutPoint(double x, double yc, double yt, double slope, int is_upper);
		void DrawSurface(int ndiv);
		void Normalize();

	public:

		//! Default constructor
		NACA_AIRFOIL() = default;

		//! Forces zero thickness trailing edge
		/*!
		 * \param TE - flag for zero TE thickness, default true 
		 */
		void SetTE0(bool TE = true) { data_.iTE0 = TE; };

 		//! Generates NACA airfoil coordinates and stores it in vectores x and z
		/*!
		 * \param iNACA - NACA airfoil number 
		 * \param set_n - number of points generated along airfoil chord, separately for upper and lower surfaces  
		 * \return 0 on success 
		 */
		int GenerateNaca(unsigned int iNACA, unsigned int set_n=100);
 		
		//! Generates NACA airfoil coordinates and stores it in vectores x and z
		/*!
		 * \param sNACA - NACA airfoil number alone, or with prefix NACA eg.: "2412", "naca 0012", or "NACA 23012"  
		 * \param set_n - number of points generated along airfoil chord, separately for upper and lower surfaces  
		 * \return 0 on success 
		 */
		int GenerateNaca(std::string sNACA, unsigned int set_n=100);

		//! Gets data vector of x coordinates
		/*!
		 * \return x vector of data points 
		 */
		std::vector <double> GetXvector() { return x_; }
	
		//! Gets data vector of z coordinates
		/*!
		 * \return z vector of data points 
		 */
		std::vector <double> GetZvector() { return z_; }
	
		//! Gets data vectors x and z of coordinates
		/*!
		 * \param get_x - x vector of data points 
		 * \param get_z - z vector of data points 
		 */
		void GetVectors(std::vector <double> &get_x, std::vector <double> &get_z) { get_x = x_; get_z = z_; }
	};
}

#endif // AP_NACA_H
