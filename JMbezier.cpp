#include "JMbezier.h"
#include "JMconsole.h"

using namespace std;

template <class REAL> 
BEZIER_POINT<REAL>::BEZIER_POINT()
{
    Set(0.0);

    brackets  = 0;
    comas     = 0;
    separator = 12;
    no_print_xyz = 4;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Set(REAL val)
{
    x = y = z = val;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Set(REAL x0, REAL y0, REAL z0)
{
    x = x0; y = y0; z = z0;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Set(REAL *vec)
{
    x = vec[0]; y = vec[1]; z = vec[2];
}

template <class REAL> 
void BEZIER_POINT<REAL>::Set(std::vector <REAL> &vec)
{
    x = vec[0]; y = vec[1]; z = vec[2];
}

template <class REAL> 
void BEZIER_POINT<REAL>::Get(REAL &x0, REAL &y0, REAL &z0)
{
    x0 = x; y0 = y; z0 = z;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Get(REAL *vec)
{
    vec[0] = x; vec[1] = y; vec[2] = z;
}

template <class REAL> 
void BEZIER_POINT<REAL>::Get(std::vector <REAL> &vec)
{
    vec[0] = x; vec[1] = y; vec[2] = z;
}

template <class REAL> 
REAL BEZIER_POINT<REAL>::Get(unsigned int XYZ)
{
    if(XYZ == 0) return x;
    if(XYZ == 1) return y;
    if(XYZ == 2) return z;
    return XYZ;
}

template <class REAL>
ostream& operator << (std::ostream &out, const BEZIER_POINT <REAL> &BP)
{
    if(BP.brackets)
        out << "{";  
    
    if(BP.separator)
    {
        if(BP.no_print_xyz != 0)
        {
            out << setw(BP.separator) << BP.x;
            if(BP.comas)
                out << ",";
        }
        
        if(BP.no_print_xyz != 1)
        {
            out << setw(BP.separator) << BP.y;
            if(BP.comas && BP.no_print_xyz != 2)
                out << ",";
        }

        if(BP.no_print_xyz != 2)
            out << setw(BP.separator) << BP.z;
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

template <class REAL> 
BEZIER<REAL>::BEZIER()
{
}

template <class REAL> 
BEZIER<REAL>::BEZIER(unsigned int nmax, unsigned int umax)
{
	Init(nmax, umax);
}

template <class REAL> 
void BEZIER<REAL>::Init(unsigned int nmax, unsigned int umax)
{
    eps   = 1e-6;
    iter  = 50;
    relax = 1;
	
	C.assign(nmax, 0.0);

	P.resize(nmax);
	for(unsigned int p=0; p<P.size(); p++)
		P[p].Set(0.0);
	
	V.resize(umax);
	for(unsigned int v=0; v<V.size(); v++)
		V[v].Set(0.0);

	tV.assign(umax, 0.0);

    BinomialCoef();
}

template <class REAL> 
void BEZIER<REAL>::Vertex(REAL t, REAL &X, REAL &Y, REAL &Z)
{
    X = Y = Z = 0;
        
    for(unsigned int k=0; k<P.size(); k++)
    {
        X += C[k]*pow(t, k)*pow(1 - t, P.size() - 1 - k)*P[k].x;
        Y += C[k]*pow(t, k)*pow(1 - t, P.size() - 1 - k)*P[k].y;
        Z += C[k]*pow(t, k)*pow(1 - t, P.size() - 1 - k)*P[k].z;
    }
}

template <class REAL> 
void BEZIER<REAL>::VertexesSeq()
{
    REAL t = 0;
    REAL du = 1/REAL(V.size()-1);
    
    for(unsigned int x=0; x<V.size(); x++)
    {
        Vertex(t, V[x].x, V[x].y, V[x].z);
		tV[x] = t;
        t += du;
    }
}

template <class REAL> 
REAL BEZIER<REAL>::tVertex(unsigned int XYZ, REAL Value)
{
    REAL min, max;
    PMinMax(XYZ, min, max);
    
    if(Value<min || Value>max)
    {
        clog << "!!!\tmin < X < max\t\t";
        clog << min << " < " << Value << " < " << max << endl;
        return 999;
    }
    
    else
    {
		REAL f, fprim;
        REAL t = (Value - min)/(max - min);
        
		if(t == 0 || t == 1)
			return t;
    
        for(unsigned int i=0; i<iter; i++) //Newton-Rapson search
        {    
            f = fprim = 0;
        
            //*** f ***
    
            for(unsigned int k=0; k<P.size(); k++)
                f += C[k]*pow(t, k)*pow(1 - t, P.size() - 1 - k)*P[k].Get(XYZ);
        
            f -= Value;
        
            //*** fprim ***
    
            for(unsigned int k=0; k<P.size(); k++)
				fprim += C[k]*P[k].Get(XYZ)*( k*pow(t, k-1)*pow(1 - t, P.size() - 1 - k) + pow(t, k)*(P.size() - 1 - k)*pow(1 - t, P.size() - 1 - k - 1) );
			
			if(fprim == 0)
			{
				clog << "Can't devide by fprim = 0!" << endl;
				return 999;
			}
			
            t -= relax*f/fprim; 
        
            if(fabs(f)<=eps)
                break;
        }
		
        return t;
    }
}

template <class REAL> 
REAL BEZIER<REAL>::Length()
{
	return Length(1, 1, 1);
}

template <class REAL> 
REAL BEZIER<REAL>::LengthX()
{
	return Length(1, 0, 0);
}

template <class REAL> 
REAL BEZIER<REAL>::LengthY()
{
	return Length(0, 1, 0);
}

template <class REAL> 
REAL BEZIER<REAL>::LengthZ()
{
	return Length(0, 0, 1);
}

template <class REAL> 
REAL BEZIER<REAL>::LengthXY()
{
	return Length(1, 1, 0);
}

template <class REAL> 
REAL BEZIER<REAL>::LengthYZ()
{
	return Length(0, 1, 1);
}

template <class REAL> 
REAL BEZIER<REAL>::LengthXZ()
{
	return Length(1, 0, 1);
}

template <class REAL> 
void BEZIER<REAL>::PMinMax(unsigned int XYZ, REAL &min, REAL &max)
{
    min = max = P[0].Get(XYZ);
    
    for(unsigned int k=0; k<P.size(); k++)
    {
        if(P[k].Get(XYZ) < min)
            min = P[k].Get(XYZ);
            
        if(P[k].Get(XYZ) > max)
            max = P[k].Get(XYZ);    
    }
}

template <class REAL>
void BEZIER<REAL>::PrintPointsFormat(bool brackets, bool comas, unsigned int separator, unsigned int no_print_xyz)
{
    for(unsigned int i=0; i<P.size(); i++)
	{
        P[i].brackets = brackets;
		P[i].comas = comas;
		P[i].separator = separator;
		P[i].no_print_xyz = no_print_xyz;
	}
}

template <class REAL>
void BEZIER<REAL>::PrintVertexesFormat(bool brackets, bool comas, unsigned int separator, unsigned int no_print_xyz)
{
    for(unsigned int i=0; i<V.size(); i++)
	{
        V[i].brackets = brackets;
		V[i].comas = comas;
		V[i].separator = separator;
		V[i].no_print_xyz = no_print_xyz;
	}
}

template <class REAL> 
void BEZIER<REAL>::PrintPoints(ostream &out)
{
    for(unsigned int i=0; i<P.size(); i++)
        out << P[i] << endl;
}

template <class REAL> 
void BEZIER<REAL>::PrintVertexes(ostream &out)
{
    for(unsigned int i=0; i<V.size(); i++)
        out << V[i] << endl;
}

template <class REAL> 
REAL BEZIER<REAL>::Length(bool xflag, bool yflag, bool zflag)
{
	REAL L=0, dx=0, dy=0, dz=0;

    for(unsigned int i=1; i<V.size(); i++)
	{
		if(xflag)
			dx = V[i].x - V[i-1].x;
		else
			dx = 0;

		if(yflag)
	        dy = V[i].y - V[i-1].y;
		else
			dy = 0;

		if(zflag)
			dz = V[i].z - V[i-1].z;
		else
			dz = 0;
		
		L += sqrt(dx*dx + dy*dy + dz*dz);
	}

	return L;
}

template <class REAL> 
void BEZIER<REAL>::BinomialCoef()
{
    C[0] = C[P.size() - 1] = 1;
    
    REAL Cc;
     
    for(unsigned int k=1; k<P.size() - 1; k++)
    {
        Cc = 1;
        
        for(unsigned int i=1; i<=k; i++)
            Cc *=  REAL((P.size() - 1 - (k - i)))/i;
           
        C[k] = int(Cc);
    }
}

template class BEZIER_POINT<float>;
template class BEZIER_POINT<double>;
template class BEZIER<float>;
template class BEZIER<double>;

