#ifndef AP_FILTER_H
#define AP_FILTER_H

#include <vector>

namespace ap {

//! One dimensional filter 
struct FILTER
{
	int n, fn;
	std::vector <double> filter;
	std::vector <double> xFiltered;
	
	//! Filter constructor 
	/*!
 	 * \param array_n - size of array to filter
 	 * \param filter_n - range on which filter blends
 	 * \param amplitude - gain of the filter
 	 */
	FILTER(int array_n, int filter_n, double amplitude);
	
	//! Filter the input 
	/*!
 	 * \param xInput - input vector to filter
 	 * \param overwrite - flag to overwrite input vector with filtered values
 	 * \return 0 on success, fails when filter range is higher then size of the input vector
 	 */
	int Filter(std::vector <double> &xInput, bool overwrite);
	
	//! Filter the input in range 
	/*!
 	 * \param shift - bottom limit, top limit defines array_n set in constructor
 	 * \param xInput - input vector to filter
 	 * \param overwrite - flag to overwrite input vector with filtered values
 	 * \return 0 on success, fails when filter range is higher then size of the input vector
 	 */
	int FilterRange(int shift, double *xInput, bool overwrite);
	
	//! Passes results to the standard output stream 
	void Print(std::ofstream &out);
};

} // namespace ap

#endif
