#include "ap_bspline.h"

namespace ap {

template <class REAL> 
B_SPLINE<REAL>::B_SPLINE()
{
	min_degree		= 1; // Line
    
	B_SPLINE::eps   = 1e-6;
    B_SPLINE::iter  = 50;
    B_SPLINE::relax = 1;
}

template <class REAL> 
B_SPLINE<REAL>::B_SPLINE(unsigned int poles_nr, unsigned int curve_degree, unsigned int type)
{
	min_degree		= 1; // Line
    
	B_SPLINE::eps   = 1e-6;
    B_SPLINE::iter  = 50;
    B_SPLINE::relax = 1;
	
	Init(poles_nr, curve_degree, type);
}

template <class REAL> 
void B_SPLINE<REAL>::SetMinDegree(unsigned int val)
{
	min_degree = val;
}

template <class REAL> 
bool B_SPLINE<REAL>::CheckMinDegree(unsigned int degree)
{
	if(degree < min_degree)
	{
		std::clog << "Condition: Degree >= " << " " << min_degree << std::endl;
		std::clog << "Minimum Degree reached: " << degree << "!!!" << std::endl;
		return 1;
	}

	return 0;
}

template <class REAL> 
bool B_SPLINE<REAL>::CheckMinPolesNr(unsigned int poles_nr, unsigned int degree)
{
	if(poles_nr < degree + 1)
	{
		std::clog << "Condition: PolesNr >= Degree + 1" << std::endl;
		std::clog << "Minimum PolesNr reached: " << poles_nr << "!!!" << std::endl;
		return 1;
	}

	return 0;
}

template <class REAL> 
bool B_SPLINE<REAL>::KnotsNrWithoutMults(unsigned int degree, unsigned int type, unsigned int poles_nr, unsigned int &k_nr)
{
	// example: knots = poles + degree + 1 = 10 + 3 + 1 = 14

	if( CheckMinDegree(degree) )
	{
		return 1;
	}

	if( CheckMinPolesNr(poles_nr, degree) )
	{
		return 1;
	}
	
	int KnotsNr;

	if(type == UNIFORM) // Closed Uniform 
	{
		KnotsNr = poles_nr + degree + 1;

		k_nr = KnotsNr;
	}

	else if(type == QUASI_UNIFORM) // Open Uniform 
	{
		KnotsNr = (poles_nr + degree + 1) - 2*degree;

		if(KnotsNr < 0)
		{
			using namespace std;
			clog << "Knots number negative!!!" << endl;
			clog << "PolesNr = " << poles_nr << endl;
			clog << "Degree  = " << degree << endl;
			clog << "Knots   = " << KnotsNr << endl;
			return 1;
		}

		k_nr = KnotsNr;
	}
	
	else if(type == PEACEWISE) // Peacewise
	{
		KnotsNr = (poles_nr + degree + 1) - 2*(degree + 1);	// Substruct Start/End knots 
		
		if(0 != KnotsNr % degree)							//Check if it devides without Rest
		{
			std::clog << "Knots does not devide equally for Peacewise Spline!!!" << std::endl; 
			return 1;
		}

		KnotsNr /= degree;									// Devide for Inner knots
		KnotsNr += 2;										// Add Start/End knots
			
		if(KnotsNr < 0)
		{
			using namespace std;
			clog << "Knots number negative!!!" << endl;
			clog << "PolesNr = " << poles_nr << endl;
			clog << "Degree  = " << degree << endl;
			clog << "Knots   = " << KnotsNr << endl;
			return 1;
		}
		
		k_nr = KnotsNr;
	}

	else
	{
		std::clog << "Unrecognized Bspline type!!!" << std::endl;
		return 1;
	}

	return 0;
}

template <class REAL> 
bool B_SPLINE<REAL>::Init(unsigned int poles_nr, unsigned int curve_degree, unsigned int type)
{
	degree = curve_degree;
	unsigned int order = degree + 1;

	B_SPLINE::P.resize(poles_nr);
   
	// --- Knots ---

	unsigned int k = poles_nr + degree + 1;
	unsigned int k_noMults;
	
	if( KnotsNrWithoutMults(degree, type, poles_nr, k_noMults) )
	{
		return 1;
	}

	/*if(type == UNIFORM) // (closed)
	{
		REAL increment = 1.0/(k - 1);
        
        for(unsigned int i=0; i<k; i++)
    		K.push_back(i*increment);
	}*/
    
	if(type == QUASI_UNIFORM) // (opened)
	{
		REAL increment = 1.0/(k - 2*degree - 1);
     
		for(unsigned int i=0; i<order; i++)
			K.push_back(0.0);

		for(unsigned int i=order; i<k-order; i++)
    		K.push_back((i - degree)*increment);

		for(unsigned int i=k-order; i<k; i++)
    		K.push_back(1.0);
	}

    if(type == PEACEWISE) 
    {
    	REAL increment = 1.0/(k_noMults - 1);

		for(unsigned int i=0; i<order; i++)
			K.push_back(0.0);

		unsigned int j=1;

        for(unsigned int i=0; i<k-2*order; j++)
		{
        	for(unsigned int m=0; m<degree; m++, i++)
    			K.push_back(j*increment);
		}
		
		for(unsigned int i=k-order; i<k; i++)
    		K.push_back(1.0);
    }

	return 0;
}


template <class REAL> 
void B_SPLINE<REAL>::deBoorData(unsigned int k, unsigned int xyz, std::vector <REAL> &d)
{
	int jk_d;

	for(unsigned int j=0; j<degree+1; j++)
	{
		jk_d = j + k - degree;
		d.push_back( B_SPLINE::P[jk_d].Get(xyz) );
	}
}

template <class REAL> 
double B_SPLINE<REAL>::deBoor(unsigned int k, double x,  std::vector <REAL> &d)
{
	// https://en.wikipedia.org/wiki/De_Boor%27s_algorithm
	
	double alpha;
	
    for(unsigned int r=1; r<degree+1; r++)
	{
		//clog << "r = " << r << endl;

		for(unsigned int j=degree; j>r-1; j--)
		{
			int jk_d  = j + k - degree; 
			int j1k_r = j + 1 + k - r;

			//clog << "\t\t" << "alpha = (x - K[j + k - degree]) / (K[j + 1 + k - r] - K[j + k - degree])" << endl;
			//clog << "\t\t" << "alpha = (x - K[" << jk_d << "]) / (K[" << j1k_r << "] - K[" << jk_d << "])" << endl;
			//clog << "\t\t" << alpha << " = (" << x << " - " << K[jk_d] << ") / (" << K[j1k_r] << " - " << K[jk_d] << ")" << endl;
        
            alpha = (x - K[jk_d]) / (K[j1k_r] - K[jk_d]);
            
			d[j] = (1.0 - alpha)*d[j-1] + alpha*d[j];

			//clog << "\t\td[j] = " << d[j] << endl << endl;
		}

		//clog << endl;
	}
	
	return d[degree];
}

template <class REAL> 
int B_SPLINE<REAL>::Vertex(REAL t, REAL &X, REAL &Y, REAL &Z)
{
	// === Index of knot interval k that contains position t ===

	/*if(t < 0 || t > 1)
	{
		clog << "Position = " << t << " is not in the interval t<0,1> !!!" << endl;
		return 1;
	}*/
	
	if(t <= 0.0)
	{
		X = B_SPLINE::P[0].x;
		Y = B_SPLINE::P[0].y;
		Z = B_SPLINE::P[0].z;
		return 0;
	}
	
	if(t >= 1.0)
	{
		X = B_SPLINE::P[B_SPLINE::P.size() - 1].x;
		Y = B_SPLINE::P[B_SPLINE::P.size() - 1].y;
		Z = B_SPLINE::P[B_SPLINE::P.size() - 1].z;
		return 0;
	}
	
	unsigned int k;

	for(k=0; k<K.size()-1; k++)
	{
		if( K[k] <= t && t<K[k+1] )
			break;
	}
	
	// === Compute ===

	// --- X ---

	std::vector <REAL> d; 
	deBoorData(k, 0, d);
	X = deBoor(k, t, d);

	// --- Y ---
	
	d.resize(0); 
	deBoorData(k, 1, d);
	Y = deBoor(k, t, d);
	
	// --- Z ---
	
	d.resize(0); 
	deBoorData(k, 2, d);
	Z = deBoor(k, t, d);
	
	return 0;
}

template <class REAL> 
void B_SPLINE<REAL>::VertexesSeq(unsigned int v_nr)
{
	B_SPLINE::V.resize(v_nr);
	for(unsigned int v=0; v<B_SPLINE::V.size(); v++)
		B_SPLINE::V[v].Set(0.0);

	B_SPLINE::tV.assign(v_nr, 0.0);
    
	REAL t  = 0;
    REAL du = 1/REAL(B_SPLINE::V.size()-1);
	
    for(unsigned int x=0; x<B_SPLINE::V.size(); x++)
    {
        Vertex(t, B_SPLINE::V[x].x, B_SPLINE::V[x].y, B_SPLINE::V[x].z);
		B_SPLINE::tV[x] = t;
        t += du;
    }
}

template <class REAL> 
void B_SPLINE<REAL>::BasisFunctions(REAL t) // only for tests
{
	using namespace std;
	
	clog << endl << "=== Basis Functions ===" << endl;
	//clog << setprecision(2);

	N.resize(B_SPLINE::P.size());
	for(unsigned int k=0; k<K.size(); k++)
		N[k].resize(degree + 1);
	
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

template class B_SPLINE<float>;
template class B_SPLINE<double>;

} // namespace ap
