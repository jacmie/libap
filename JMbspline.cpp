#include "JMbspline.h"

using namespace std;

template <class REAL> 
B_SPLINE<REAL>::B_SPLINE()
{
}

template <class REAL> 
B_SPLINE<REAL>::B_SPLINE(unsigned int nmax, unsigned int umax)
{
	Init(nmax, umax);
}

template <class REAL> 
void B_SPLINE<REAL>::Init(unsigned int nmax, unsigned int umax)
{
	npt  = nmax;
    n    = nmax - 1;
    u    = umax;
    eps  = 1e-6;
    iter = 50;
    relax = 1;

	degree = 2;
	order  = degree + 1;

    unsigned int k = npt + degree + 1; // ok ????
	k = 5;
   	clog << "k = " << k << endl;

	K.resize(k);

    //if(UNIFORM)
	{
        REAL increment = 1.0/(k - 1);

		K[0] = 0;

        for(unsigned int d=1; d<K.size(); d++)
    		K[d] += K[d-1] + increment;

	}

    //if(QUASI_UNIFORM)
    {
/*        REAL increment = 1.0;

        for(unsigned int d=0; d<degree; d++)
    		K[d] = 0.0;
        
        for(unsigned int d=degree; d<k-degree; d++)
    		K[d] += K[d-1] + increment;

	    for(unsigned int d=k-degree; d<k; d++)
    		K[d] = K[k-degree-1] + increment;*/
    }
	
	for(unsigned int p=0; p<K.size(); p++)
		clog << p << "\t" << K[p] << endl;
	clog << endl;

	double dd = 1.0/4;

	ofstream out("BasisFun.xls");

	for(unsigned int i=0; i<5; i++)
	{
		clog << "t = " << i*dd;
		out << i*dd << endl;
		BasisFunctions(i*dd);
		clog << endl;
	}

	out.close();

	/*
	P.resize(npt);
	for(unsigned int p=0; p<P.size(); p++)
		P[p].Set(0.0);
	
	V.resize(u);
	for(unsigned int v=0; v<V.size(); v++)
		V[v].Set(0.0);

	tV.assign(u, 0.0);
	*/

	clog << "END" << endl;
}

template <class REAL> 
void B_SPLINE<REAL>::BasisFunctions(REAL t)
{
	clog << endl << "=== Basis Functions ===" << endl;
	clog << setprecision(2);

	N.resize(npt);
	for(unsigned int k=0; k<K.size(); k++)
		N[k].resize(order);
	
	// p==1
	
	clog << endl << "--- p = 0 ---" << endl;

	for(unsigned int i=0; i<K.size()-1; i++)
	{
		clog << K[i] << "\t" << t << "\t" << K[i+1] << "\t";

    	if(K[i] <= t && t < K[i+1])
		{
        	N[i][0] = 1;
		}
    	else
		{
        	N[i][0] = 0;
		}

		clog << i << "\tN" << i << "0 = " << N[i][0] << endl;
	}

/*
	clog << K[p] << "\t" << t << "\t" << K[p+1] << "\t";
    
	if(t == K[K.size()-1])
        N[p][0] = 1;
    else
        N[p][0] = 0;
	
	clog << p << "\t" << N[p][0] << endl;
*/
	// p>1
   
	double u = t;
	double u_i;
	double u_ip;
	double u_ip1;
	double u_i1;

	unsigned int kk = K.size() - 1;
	
	for(unsigned int p=1; p<=degree; p++)
	{
		clog << endl << "--- p = " << p << " ---" << endl;
		clog << "i\t" << "i+1\t" << "i+p\t" << "i+p+1\t" << "p-1\t";
		clog << "u\t" << "u_i\t" << "u_i+1\t" << "u_i+p\t" << "u_i+p+1\t" << "\t";
		clog << "N[i][p-1]\t" << "N[i+1][p-1]" << endl;

		kk--;
		
		for(unsigned int i=0; i<kk; i++)
    	{
			u_i   = K[i];
			u_ip  = K[i+p];
			u_ip1 = K[i+p+1];
			u_i1  = K[i+1];
			
			clog << i << "\t" << i+1 << "\t" << i+p << "\t" << i+p+1 << "\t" << p-1 << "\t";
			clog << t << "\t" << K[i] << "\t" << K[i+1] << "\t" << K[i+p] << "\t" << K[i+p+1] << "\t";
			clog << "\t" << N[i][p-1] << "\t\t" << N[i+1][p-1] << "\t";

			//N[i][p] = N[i][degree-1]*(t - K[i])/(K[i+degree-1] - K[i]) + N[i+1][degree-1]*(K[i+degree] - t)/(K[i+degree] - K[i+1]);
			//N[i][p] = N[i][p-1]*(t - K[i])/(K[i+p-1] - K[i]) + N[i+1][p-1]*(K[i+p] - t)/(K[i+p] - K[i+1]);
			N[i][p] = N[i][p-1]*(u - u_i)/(u_ip - u_i) + N[i+1][p-1]*(u_ip1 - u)/(u_ip1 - u_i1);

			clog << "\t" << N[i][p] << endl;
			
			clog << "N" << i << p << " = N" << i << p-1 << "*(u - u" << i << ")/(u" << i+p << " - u" << i << ") + " 
				 << "N" << i+1 << p-1 << "*(u" << i+p+1 << " - u" << ")/(u" << i+p+1 << " - u" << i+1 << ")" << endl;
			
			clog << "N[i][p] = N[i][p-1]*(" << u << " - " << u_i << ")/(" << u_ip << " - " << u_i << ") + " 
				 << "N[i+1][p-1]*(" << u_ip1 << " - " << u << ")/(" << u_ip1 << " - " << u_i1 << ")" << endl;
			
			clog << "N[i][p] = " << N[i][p-1] << "*(" << u << " - " << u_i << ")/(" << u_ip << " - " << u_i << ") + " 
				 << N[i+1][p-1] << "*(" << u_ip1 << " - " << u << ")/(" << u_ip1 << " - " << u_i1 << ")" << endl;
			/*
			clog << N[i+1][p-1] << "*(" << u_ip1 << " - " << u << ")/(" << u_ip1 << " - " << u_i1 << ")" << endl;
			clog << N[i+1][p-1] << "*(" << u_ip1 << " - u)/(" << u_ip1 << " - " << u_i1 << ")" << endl;
			clog << N[i+1][p-1] << "*(" << u_ip1 << " - u)/(" << u_ip1 - u_i1 << ")" << endl;
			clog << N[i+1][p-1]/(u_ip1 - u_i1) << "*(" << u_ip1 << " - u)" << endl;
			clog << N[i+1][p-1]*u_ip1/(u_ip1 - u_i1) << " - " << N[i+1][p-1]/(u_ip1 - u_i1) << "*u" << endl;
			*/	
			clog << "N" << i << p << " = " << N[i][p-1]/(u_ip - u_i) << "*u" << - N[i][p-1]*u_i/(u_ip - u_i) << " + " 
				 << N[i+1][p-1]*u_ip1/(u_ip1 - u_i1) << " - " << N[i+1][p-1]/(u_ip1 - u_i1) << "*u = " << N[i][p] << endl << endl;
   	 	}
	}
}

template <class REAL> 
BEZIER_POINT <REAL> B_SPLINE<REAL>::GetVertex(REAL t)
{
	BEZIER_POINT <REAL> v;
	
	unsigned int k;

	for(k=0; k<K.size()-1; k++)
	{
		if( K[k] <= t && t<K[k+1] )
			break;
	}
		

	for(unsigned int p=0; p<P.size(); p++)
	{
		for(unsigned int d=0; d<=degree; d++)
		{
			clog << d << "\t" << k << "\t" << N[d][k]*P[p].x << endl;
		}
	}	

	return v;
}

/*
template <class REAL> 
void BEZIER<REAL>::Vertex(REAL t, REAL &X, REAL &Y, REAL &Z)
{
    X = Y = Z = 0;
        
    for(unsigned int k=0; k<npt; k++)
    {
        X += C[k]*pow(t, k)*pow(1 - t, n - k)*P[k].x;
        Y += C[k]*pow(t, k)*pow(1 - t, n - k)*P[k].y;
        Z += C[k]*pow(t, k)*pow(1 - t, n - k)*P[k].z;
    }
}

template <class REAL> 
void BEZIER<REAL>::VertexesSeq()
{
    REAL t = 0;
    REAL du = 1/REAL(u-1);
    
    for(unsigned int x=0; x<u; x++)
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
        
            // *** f ***
    
            for(unsigned int k=0; k<npt; k++)
                f += C[k]*pow(t, k)*pow(1 - t, n - k)*P[k].Get(XYZ);
        
            f -= Value;
        
            // *** fprim ***
    
            for(unsigned int k=0; k<npt; k++)
				fprim += C[k]*P[k].Get(XYZ)*( k*pow(t, k-1)*pow(1 - t, n - k) + pow(t, k)*(n - k)*pow(1 - t, n - k - 1) );
			
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
    
    for(unsigned int k=0; k<npt; k++)
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
    for(unsigned int i=0; i<npt; i++)
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
    for(unsigned int i=0; i<u; i++)
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
    for(unsigned int i=0; i<npt; i++)
        out << P[i] << endl;
}

template <class REAL> 
void BEZIER<REAL>::PrintVertexes(ostream &out)
{
    for(unsigned int i=0; i<u; i++)
        out << V[i] << endl;
}

template <class REAL> 
REAL BEZIER<REAL>::Length(bool xflag, bool yflag, bool zflag)
{
	REAL L=0, dx=0, dy=0, dz=0;

    for(unsigned int i=1; i<u; i++)
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
}*/

template class B_SPLINE<float>;
template class B_SPLINE<double>;

