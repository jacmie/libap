#ifndef _BEZIER_POINT_H_
#define _BEZIER_POINT_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

template <class REAL> class BEZIER_POINT
{
    public:
        
    REAL x;
    REAL y;
    REAL z;

    BEZIER_POINT();

    void Set(REAL val);
    void Set(REAL x0, REAL y0, REAL z0);
    void Set(REAL *vec);
    void Set(std::vector <REAL> &vec);

    void Get(REAL &x0, REAL &y0, REAL &z0);
    void Get(REAL *vec);
    void Get(std::vector <REAL> &vec);

    REAL Get(unsigned int XYZ);

    //Print format atributes
    bool brackets;
    bool comas;
    unsigned int separator;
    unsigned int no_print_xyz;
};

template <class REAL>
std::ostream& operator << (std::ostream &out, const BEZIER_POINT <REAL> &BP)
{
    if(BP.brackets)
        out << "{";  
    
    if(BP.separator)
    {
        if(BP.no_print_xyz != 0)
        {
            out << std::setw(BP.separator) << BP.x;
            if(BP.comas)
                out << ",";
        }
        
        if(BP.no_print_xyz != 1)
        {
            out << std::setw(BP.separator) << BP.y;
            if(BP.comas && BP.no_print_xyz != 2)
                out << ",";
        }

        if(BP.no_print_xyz != 2)
            out << std::setw(BP.separator) << BP.z;
    }

    else
    {    
        if(BP.no_print_xyz != 0)
        {
            out << BP.x;
            if(BP.comas)
                out << ",";
            out << "\t";
        }
        
        if(BP.no_print_xyz != 1)
        {
            out << BP.y;
            if(BP.comas && BP.no_print_xyz != 2)
                out << ",";
            if(BP.no_print_xyz != 2)
                out << "\t";
        }

        if(BP.no_print_xyz != 2)
            out << BP.z; 
    }

    if(BP.brackets)
        out << "}";

    return out;
}

#endif
