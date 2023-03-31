#ifndef AP_DISTRIBUTIOIN_H
#define AP_DISTRIBUTIOIN_H

#include <vector>

namespace ap {

enum paneling {LEFT=0, CENTER, RIGHT};

//! Generates distribution 
/*!
 * Based on sin() function projection. 
 * \param n - number of distribution points 
 * \param factor - coefficient of distribution density in range <0, 1>
 * - 0 - linear distribution
 * - 1 - fully non linear distribution
 * \param distrib - returned vector of distribution 
 * \param paneling_type - different paneling types:
 * - 0 - Left side: ** *  *   *   *
 * - 1 - Center: ** *  *  * * **
 * - 2 - Right side: *   *   *  * **
 * \param range - specifies range of the distribution, form 0 to the value 
 */
template <class real> 
void sinDistribution(unsigned int n, real factor, std::vector <real> &distrib, int paneling_type=1, real range=1);

//! Generates distribution 
/*!
 * Based on exp() function projection. 
 * \param n - number of distribution points 
 * \param factor - coefficient of distribution density in range (0, infinity)
 * - (0, 1) - distribution denser to the center (paneling_type==CENTER), or denser to right (paneling_type!=CENTER)
 * -  1 - linear distribution
 * - (1, oo) - distribution denser to the ends (paneling_type==CENTER), or denser to left (paneling_type!=CENTER) 
 * \param distrib - returned vector of distribution 
 * \param paneling_type - different paneling types:
 * - if(1) - Center: ** *  *  * * **
 * - else - Side: ** *  *   *   *
 * \param range - specifies range of the distribution, form 0 to the value
 * \return 0 on success, fails when the factor is negative, or equal to 0.
 */
template <class real> 
bool expDistribution(unsigned int n, real factor, std::vector <real> &distrib, int paneling_type=1, real range=1);

} // namespace ap

#endif
