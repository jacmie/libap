#include <iostream>
#include <fstream>
#include <cmath>

#include "ap_bezier.h"

namespace ap {

template <class REAL> 
void BEZIER<REAL>::Init(unsigned int nmax) {
	C.assign(nmax, 0.0);

	P.resize(nmax);
	for(unsigned int p=0; p<P.size(); p++) P[p].Set(0.0);
	
    BinomialCoef();
}

template <class REAL> 
int BEZIER<REAL>::Vertex(REAL t, REAL &x, REAL &y, REAL &z)
{
	if(t < 0 || t > 1) {
		std::clog << "Position = " << t << " is not in the interval t<0,1> !!!" << std::endl;
		return 1;
	}
    
	x = y = z = 0;
        
    for(unsigned int k=0; k<P.size(); k++) {
        x += C[k]*pow(t, k)*pow(1 - t, P.size() - 1 - k)*P[k].x;
        y += C[k]*pow(t, k)*pow(1 - t, P.size() - 1 - k)*P[k].y;
        z += C[k]*pow(t, k)*pow(1 - t, P.size() - 1 - k)*P[k].z;
    }

	return 0;
}

template <class REAL> 
void BEZIER<REAL>::VertexesSeq(unsigned int v_nr) {
	V.resize(v_nr);
	for(unsigned int v=0; v<V.size(); v++) V[v].Set(0.0);

	tV.assign(v_nr, 0.0);

    REAL t = 0;
    REAL du = 1/REAL(V.size()-1);
    
    for(unsigned int x=0; x<V.size(); x++) {
        Vertex(t, V[x].x, V[x].y, V[x].z);
		tV[x] = t;
        t += du;
    }
}

template <class REAL> 
REAL BEZIER<REAL>::tVertex(unsigned int xyz, REAL value) {
    REAL min, max;
    PMinMax(xyz, min, max);
    
    if(value<min || value>max) {
        std::clog << "!!!\tmin < X < max\t\t";
        std::clog << min << " < " << value << " < " << max << std::endl;
        return 999;
    }
    
    else {
		REAL f, fprim;
        REAL t = (value - min)/(max - min);
        
		if(t == 0 || t == 1)
			return t;
    
        for(unsigned int i=0; i<iter; i++) { //Newton-Rapson search    
            f = fprim = 0;
        
            //*** f ***
    
            for(unsigned int k=0; k<P.size(); k++)
                f += C[k]*pow(t, k)*pow(1 - t, P.size() - 1 - k)*P[k].Get(xyz);
        
            f -= value;
        
            //*** fprim ***
    
            for(unsigned int k=0; k<P.size(); k++) {
				fprim += C[k]*P[k].Get(xyz)*( k*pow(t, k-1)*pow(1 - t, P.size() - 1 - k) + pow(t, k)*(P.size() - 1 - k)*pow(1 - t, P.size() - 1 - k - 1) );
			}

			if(fprim == 0) {
				std::clog << "Can't devide by fprim = 0!" << std::endl;
				return 999;
			}
			
            t -= relax*f/fprim; 
        
            if(fabs(f)<=eps) break;
        }
		
        return t;
    }
}

template <class REAL> 
REAL BEZIER<REAL>::Length() { return Length(1, 1, 1); }

template <class REAL> 
REAL BEZIER<REAL>::LengthX() { return Length(1, 0, 0); }

template <class REAL> 
REAL BEZIER<REAL>::LengthY() { return Length(0, 1, 0); }

template <class REAL> 
REAL BEZIER<REAL>::LengthZ() { return Length(0, 0, 1); }

template <class REAL> 
REAL BEZIER<REAL>::LengthXY() {	return Length(1, 1, 0); }

template <class REAL> 
REAL BEZIER<REAL>::LengthYZ() { return Length(0, 1, 1); }

template <class REAL> 
REAL BEZIER<REAL>::LengthXZ() { return Length(1, 0, 1); }

template <class REAL> 
void BEZIER<REAL>::PMinMax(unsigned int XYZ, REAL &min, REAL &max) {
    min = max = P[0].Get(XYZ);
    
    for(unsigned int k=0; k<P.size(); k++) {
        if(P[k].Get(XYZ) < min)
            min = P[k].Get(XYZ);
            
        if(P[k].Get(XYZ) > max)
            max = P[k].Get(XYZ);    
    }
}

template <class REAL>
void BEZIER<REAL>::PrintPolesFormat(bool brackets, bool comas, unsigned int separator, unsigned int no_print_xyz) {
    for(unsigned int i=0; i<P.size(); i++) {
        P[i].brackets = brackets;
		P[i].comas = comas;
		P[i].separator = separator;
		P[i].no_print_xyz = no_print_xyz;
	}
}

template <class REAL>
void BEZIER<REAL>::PrintVertexesFormat(bool brackets, bool comas, unsigned int separator, unsigned int no_print_xyz) {
    for(unsigned int i=0; i<V.size(); i++) {
        V[i].brackets = brackets;
		V[i].comas = comas;
		V[i].separator = separator;
		V[i].no_print_xyz = no_print_xyz;
	}
}

template <class REAL> 
void BEZIER<REAL>::PrintPoles(std::ostream &out) {
    for(unsigned int i=0; i<P.size(); i++) {
        out << P[i] << std::endl;
	}
}

template <class REAL> 
void BEZIER<REAL>::PrintVertexes(std::ostream &out) {
    for(unsigned int i=0; i<V.size(); i++) out << V[i] << std::endl;
}

template <class REAL> 
REAL BEZIER<REAL>::Length(bool xflag, bool yflag, bool zflag) {
	REAL L=0, dx=0, dy=0, dz=0;

    for(unsigned int i=1; i<V.size(); i++) {
		if(xflag)	dx = V[i].x - V[i-1].x;
		else		dx = 0;

		if(yflag)	dy = V[i].y - V[i-1].y;
		else		dy = 0;

		if(zflag)	dz = V[i].z - V[i-1].z;
		else		dz = 0;
		
		L += sqrt(dx*dx + dy*dy + dz*dz);
	}

	return L;
}

template <class REAL> 
void BEZIER<REAL>::BinomialCoef() {
    C[0] = C[P.size() - 1] = 1;
    
    REAL Cc;
     
    for(unsigned int k=1; k<P.size() - 1; k++) {
        Cc = 1;
        
        for(unsigned int i=1; i<=k; i++) {
            Cc *=  REAL((P.size() - 1 - (k - i)))/i;
		}

        C[k] = int(Cc);
    }
}

template class BEZIER_POINT<float>;
template class BEZIER_POINT<double>;
template class BEZIER<float>;
template class BEZIER<double>;

} // namespace ap
