#include "JMbspline.h"

using namespace std;

template <class REAL> 
B_SPLINE<REAL>::B_SPLINE()
{
}

template <class REAL> 
B_SPLINE<REAL>::B_SPLINE(unsigned int poles_nr, unsigned int curve_degree, unsigned int vertexes_nr, unsigned int type)
{
	Init(poles_nr, curve_degree, vertexes_nr, type);
}

template <class REAL> 
void B_SPLINE<REAL>::Init(unsigned int poles_nr, unsigned int curve_degree, unsigned int vertexes_nr, unsigned int type)
{
	npt  = poles_nr;
    n    = poles_nr - 1;
    u    = vertexes_nr;
    B_SPLINE::eps  = 1e-6;
    B_SPLINE::iter = 50;
    B_SPLINE::relax = 1;

	degree = curve_degree;
	order  = degree + 1;

	B_SPLINE::P.resize(npt);
   
	// --- Knots ---
	
	unsigned int k = npt + degree + 1;

	if(type == UNIFORM) // (closed)
	{
		REAL increment = 1.0/(k - 1);
        
        for(unsigned int i=0; i<k; i++)
    		K.push_back(i*increment);
	}
    
	if(type == QUASI_UNIFORM) // (opened)
	{
		REAL increment = 1.0/(k -2*degree);
        
		for(unsigned int i=0; i<order; i++)
			K.push_back(0.0);

        for(unsigned int i=order; i<k-order; i++)
		{
    		K.push_back((i - degree)*increment);
		}

		for(unsigned int i=k-order; i<k; i++)
    		K.push_back(1.0);
	}

    if(type == PEACEWISE) 
    {
    	REAL increment = 1.0/(k - 2*degree)*degree;
        
		for(unsigned int i=0; i<order; i++)
			K.push_back(0.0);
        
        for(unsigned int i=order; i<k-degree; i+=degree)
		{
			unsigned int j=i; 
				
        	for(unsigned int m=0; m<degree; m++, i++)
    			K.push_back((j - degree)*increment);
		}
		
	    for(unsigned int i=k-order; i<k; i++)
    		K.push_back(1.0);
    }
	
	for(unsigned int p=0; p<K.size(); p++)
		clog << p << "\t" << K[p] << endl;
	clog << endl;
}

template <class REAL> 
void B_SPLINE<REAL>::BasisFunctions(REAL t) // only for tests
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
			
			clog << "N" << i << p << " = " << N[i][p-1]/(u_ip - u_i) << "*u" << - N[i][p-1]*u_i/(u_ip - u_i) << " + " 
				 << N[i+1][p-1]*u_ip1/(u_ip1 - u_i1) << " - " << N[i+1][p-1]/(u_ip1 - u_i1) << "*u = " << N[i][p] << endl << endl;
   	 	}
	}
}

template <class REAL> 
double B_SPLINE<REAL>::deBoor(std::ofstream &out, double x)
{
    /*Evaluates S(x).

    Arguments
    ---------
    k: Index of knot interval that contains x.
    x: Position.
    t: Array of knot positions, needs to be padded as described above.
    c: Array of control points.
    p: Degree of B-spline.
    
	*/

	/*
    d = [c[j + k - p] for j in range(0, p + 1)]

    for r in range(1, p + 1):
	{
		for j in range(p, r - 1, -1):
		{
            alpha = (x - t[j + k - p]) / (t[j + 1 + k - r] - t[j + k - p])
            d[j] = (1.0 - alpha) * d[j - 1] + alpha * d[j]
		}
	}
	*/
    
    /*Evaluates S(x).

    Arguments
    ---------
    k: Index of knot interval that contains x.
    x: Position.
    
	*/
	
	clog << endl;
	
	for(unsigned int p=0; p<B_SPLINE::P.size(); p++)
	{
		clog << "P" << p << " = " << B_SPLINE::P[p].y << endl;  
	}

	// --- Set range ---
	
	unsigned int k;

	for(k=0; k<K.size()-1; k++)
	{
		if( K[k] <= x && x<K[k+1] )
			break;
	}
	
	clog << endl << "t = " << x << " -> k = " << k << endl; 
	clog << endl;
	
	// --- Compute ---

	clog << "r = " << 0 << endl << endl;

	vector <REAL> d; 
	
	out << x << "\t";

	// x
	
	for(unsigned int j=0; j<degree+1; j++) 
	{
		d.push_back( B_SPLINE::P[j + k - degree].x );
		clog << j << "\t" << j + k - degree << "\t" << d[j] << endl;
	}

	clog << endl;

	out << deBoor2(k, x, d) << "\t";

	// y
	
	d.resize(0); 
	
	for(unsigned int j=0; j<degree+1; j++) 
	{
		d.push_back( B_SPLINE::P[j + k - degree].y );
		clog << j << "\t" << j + k - degree << "\t" << d[j] << endl;
	}

	clog << endl;

	out << deBoor2(k, x, d) << "\t";
	
	// z
	
	d.resize(0); 
	
	for(unsigned int j=0; j<degree+1; j++) 
	{
		d.push_back( B_SPLINE::P[j + k - degree].z );
		clog << j << "\t" << j + k - degree << "\t" << d[j] << endl;
	}

	clog << endl;

	out << deBoor2(k, x, d) << endl;
	
	/*
	double alpha;
	
    for(unsigned int r=1; r<degree+1; r++)
	{
		clog << "r = " << r << endl;

		for(unsigned int j=degree; j>r-1; j--)
		{
			clog << "\t" << j << "\t";

			//int jk_d = j + k - degree;

			clog << K[j + k - degree] << "\t" << K[j + 1 + k - r] << endl;

            alpha = (x - K[j + k - degree]) / (K[j + 1 + k - r] - K[j + k - degree]);
            
			clog << "\t\t" << "alpha = (x - K[j + k - degree]) / (K[j + 1 + k - r] - K[j + k - degree])" << endl;
			clog << "\t\t" << alpha << " = (" << x << " - " << K[j + k - degree] << ") / (" << K[j + 1 + k - r] << " - " << K[j + k - degree] << ")" << endl;
        
			d[j] = (1.0 - alpha)*d[j-1] + alpha*d[j];

			clog << "\t\t" << d[j] << endl << endl;
		}
		clog << endl;
	}
	
	clog << d[degree] << endl;
    
	return d[degree];*/
	return 1;
}

template <class REAL> 
double B_SPLINE<REAL>::deBoor2(unsigned int k, double x, vector <REAL> d)
{
	clog << "r = " << 0 << endl << endl;
/*
	for(unsigned int j=0; j<degree+1; j++) 
	{
		d.push_back( B_SPLINE::P[j + k - degree].y );
		clog << j << "\t" << j + k - degree << "\t" << d[j] << endl;
	}

	clog << endl;
*/
	double alpha;
	
    for(unsigned int r=1; r<degree+1; r++)
	{
		clog << "r = " << r << endl;

		for(unsigned int j=degree; j>r-1; j--)
		{
			clog << "\t" << j << "\t";

			//int jk_d = j + k - degree;

			clog << K[j + k - degree] << "\t" << K[j + 1 + k - r] << endl;

            alpha = (x - K[j + k - degree]) / (K[j + 1 + k - r] - K[j + k - degree]);
            
			clog << "\t\t" << "alpha = (x - K[j + k - degree]) / (K[j + 1 + k - r] - K[j + k - degree])" << endl;
			clog << "\t\t" << alpha << " = (" << x << " - " << K[j + k - degree] << ") / (" << K[j + 1 + k - r] << " - " << K[j + k - degree] << ")" << endl;
        
			d[j] = (1.0 - alpha)*d[j-1] + alpha*d[j];

			clog << "\t\t" << d[j] << endl << endl;
		}
		clog << endl;
	}
	
	clog << d[degree] << endl;
    
	return d[degree];
}

template <class REAL> 
void B_SPLINE<REAL>::GetVertex(REAL t)
{
	clog << "t = " << t << endl << endl; 
	
	REAL Psum_x=0;
	REAL Psum_y=0;
	REAL Psum_z=0;

	for(unsigned int p=0; p<B_SPLINE::P.size(); p++)
	{
		clog << "P" << p << " = " << B_SPLINE::P[p].y << endl;  

		for(unsigned int i=0; i<N.size(); i++)
		{
			for(unsigned int j=0; j<N[i].size(); j++)
			{
				clog << "N_" << i << j << " = " << N[i][j] << endl;
	
				Psum_x += N[i][j]*B_SPLINE::P[p].x;
				Psum_y += N[i][j]*B_SPLINE::P[p].y;
				Psum_z += N[i][j]*B_SPLINE::P[p].z;

				clog << N[i][j]*B_SPLINE::P[p].x << "\t" << Psum_x << endl;
				clog << N[i][j]*B_SPLINE::P[p].y << "\t" << Psum_y << endl;
				clog << N[i][j]*B_SPLINE::P[p].z << "\t" << Psum_z << endl;
			}

			clog << endl;
		}	
	}	

//	BEZIER_POINT <REAL> v;
/*	
	unsigned int k;

	for(k=0; k<K.size()-1; k++)
	{
		if( K[k] <= t && t<K[k+1] )
			break;
	}
	
	clog << "t = " << t << " -> k = " << k << endl; 

	for(unsigned int p=0; p<B_SPLINE::P.size(); p++)
	{
		clog << P[p].y << endl;
	}	
*/
//	return v;
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

