#ifndef BEZIER_POINT_H
#define BEZIER_POINT_H

#include <iomanip>
#include <iostream>
#include <vector>

namespace ap {

//! Template class for points used in bezier and bspline curves
/*!
 * This class is based on header file only. There is no source file that has to be compiled and object file linked.
 * Simple include the header in the developed code.
 */
template <class REAL> 
class BEZIER_POINT {
    public:
        
	//! Point x coordinate
    REAL x = 0;
	//! Point y coordinate
    REAL y = 0;
	//! Point z coordinate
    REAL z = 0;

	//! Default constuctor
    BEZIER_POINT() = default;

	//! Sets value for all coordinates of the point
	/*!
 	 * \param val - value assigned to all coordinates of the point
 	 */
    void Set(REAL val) { x = y = z = val; }
	
	//! Sets values to the point coordinates
	/*!
 	 * \param x0 - value set for the x coordinate of the point
 	 * \param y0 - value set for the y coordinate of the point
 	 * \param z0 - value set for the z coordinate of the point
 	 */
    void Set(REAL x0, REAL y0, REAL z0) { x = x0; y = y0; z = z0; }
    
	//! Sets array to the point coordinates
	/*!
 	 * \param vec - array assigned to the coordinates of the point
 	 */
	void Set(REAL *vec) { x = vec[0]; y = vec[1]; z = vec[2]; }
    
	//! Sets vector to the point coordinates
	/*!
 	 * \param vec - vector assigned to the coordinates of the point
 	 */
    void Set(std::vector <REAL> &vec) { x = vec[0]; y = vec[1]; z = vec[2]; }

	
	//! Gets values of the point coordinates
	/*!
 	 * \param x0 - gets value of the x coordinate
 	 * \param y0 - gets value of the y coordinate
 	 * \param z0 - gets value of the z coordinate
 	 */
    void Get(REAL &x0, REAL &y0, REAL &z0) { x0 = x; y0 = y; z0 = z; }
    
	//! Gets array of the point coordinates
	/*!
 	 * \param vec - extracted array of the coordinates of the point
 	 */
    void Get(REAL *vec) { vec[0] = x; vec[1] = y; vec[2] = z; }
    
	//! Gets vector of the point coordinates
	/*!
 	 * \param vec - extracted vector of the coordinates of the point
 	 */
    void Get(std::vector <REAL> &vec) { vec[0] = x; vec[1] = y; vec[2] = z; }

	//! Gets coordinate of the point
	/*!
 	 * \param xyz - index of the coordinate:
	 * - 0 - x
	 * - 1 - y
	 * - 2 - z
 	 */
    REAL Get(unsigned int xyz) {
    	if(xyz == 0) return x;
    	if(xyz == 1) return y;
    	if(xyz == 2) return z;
    	return xyz;
	}

    // Print format atributes
    bool brackets = 0;	//!< Flag to use brackets when the point is printed in the output stream, default - false 
    bool comas = 0;		//!< Flag to use comas when the point is printed in the output stream, default - false
    unsigned int separator = 12;	//!< Space reserved to print point coordinate when the point is printed in the output stream
    unsigned int no_print_xyz = 4;	//!< Index of the point coordinate to ommit when the point is printed in the output stream, egz.: 2 - z coordinate not printed
};

template <class REAL>
std::ostream& operator << (std::ostream &out, const BEZIER_POINT <REAL> &BP) {
    if(BP.brackets)
        out << "{";  
    
    if(BP.separator)
    {
        if(BP.no_print_xyz != 0) {
            out << std::setw(BP.separator) << BP.x;
            if(BP.comas) out << ",";
        }
        
        if(BP.no_print_xyz != 1) {
            out << std::setw(BP.separator) << BP.y;
            if(BP.comas && BP.no_print_xyz != 2) out << ",";
        }

        if(BP.no_print_xyz != 2) out << std::setw(BP.separator) << BP.z;
    }

    else {    
        if(BP.no_print_xyz != 0) {
            out << BP.x;
            if(BP.comas) out << ",";
            out << "\t";
        }
        
        if(BP.no_print_xyz != 1) {
            out << BP.y;
            if(BP.comas && BP.no_print_xyz != 2) out << ",";
            if(BP.no_print_xyz != 2) out << "\t";
        }

        if(BP.no_print_xyz != 2) out << BP.z; 
    }

    if(BP.brackets) out << "}";

    return out;
}

} // namespace ap

#endif
