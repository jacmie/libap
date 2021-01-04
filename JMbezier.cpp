#include "JMbezier.h"
#include "JMconsole.h"

using namespace std;

BEZIER::BEZIER()
{
}

BEZIER::BEZIER(unsigned int nmax, unsigned int umax)
{
	Init(nmax, umax);
}

void BEZIER::Init(unsigned int nmax, unsigned int umax)
{
	npt  = nmax;
    n    = nmax - 1;
    u    = umax;
    eps  = 1e-6;
    iter = 50;
    relax = 1;
	
	C.assign(npt, 0.0);

	P.resize(npt);
	for(unsigned int p=0; p<P.size(); p++)
		P[p].assign(3, 0.0);
	
	V.resize(u);
	for(unsigned int v=0; v<V.size(); v++)
		V[v].assign(3, 0.0);

	tV.assign(u, 0.0);

    BinomialCoef();
}

BEZIER::~BEZIER()
{
}

void BEZIER::Vertex(double t, double &X, double &Y, double &Z)
{
    X = Y = Z = 0;
        
    for(unsigned int k=0; k<npt; k++)
    {
        X += C[k]*pow(t, k)*pow(1 - t, n - k)*P[k][0];
        Y += C[k]*pow(t, k)*pow(1 - t, n - k)*P[k][1];
        Z += C[k]*pow(t, k)*pow(1 - t, n - k)*P[k][2];
    }
}

void BEZIER::VertexSeq()
{
    double t = 0;
    double du = 1/double(u-1);
    
    for(unsigned int x=0; x<u; x++)
    {
        Vertex(t, V[x][0], V[x][1], V[x][2]);
		tV[x] = t;
        t += du;
    }
}

double BEZIER::tVertex(unsigned int XYZ, double Value)
{
    double min, max;
    PMinMax(XYZ, min, max);
    
    if(Value<min || Value>max)
    {
        clog << "!!!\tmin < X < max\t\t";
        clog << min << " < " << Value << " < " << max << endl;
        return 999;
    }
    
    else
    {
		double f, fprim;
        double t = (Value - min)/(max - min);
        
		if(t == 0 || t == 1)
			return t;
    
        for(unsigned int i=0; i<iter; i++) //Newton-Rapson search
        {    
            f = fprim = 0;
        
            //*** f ***
    
            for(unsigned int k=0; k<npt; k++)
                f += C[k]*pow(t, k)*pow(1 - t, n - k)*P[k][XYZ];
        
            f -= Value;
        
            //*** fprim ***
    
            for(unsigned int k=0; k<npt; k++)
				fprim += C[k]*P[k][XYZ]*( k*pow(t, k-1)*pow(1 - t, n - k) + pow(t, k)*(n - k)*pow(1 - t, n - k - 1) );
			
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

double BEZIER::Length()
{
	return Length(1, 1, 1);
}

double BEZIER::LengthX()
{
	return Length(1, 0, 0);
}

double BEZIER::LengthY()
{
	return Length(0, 1, 0);
}

double BEZIER::LengthZ()
{
	return Length(0, 0, 1);
}

double BEZIER::LengthXY()
{
	return Length(1, 1, 0);
}

double BEZIER::LengthYZ()
{
	return Length(0, 1, 1);
}

double BEZIER::LengthXZ()
{
	return Length(1, 0, 1);
}

void BEZIER::PMinMax(unsigned int XYZ, double &min, double &max)
{
    min = max = P[0][XYZ];
    
    for(unsigned int k=0; k<npt; k++)
    {
        if(P[k][XYZ] < min)
            min = P[k][XYZ];
            
        if(P[k][XYZ] > max)
            max = P[k][XYZ];    
    }
}

void BEZIER::PrintPoints(ostream &out)
{
    for(unsigned int i=0; i<npt; i++)
        out << P[i][0] << "\t" << P[i][1] << "\t" << P[i][2] << endl;
}

void BEZIER::PrintVertex(ostream &out)
{
    for(unsigned int i=0; i<u; i++)
        out << V[i][0] << "\t" << V[i][1] << "\t" << V[i][2] << endl;
}

double BEZIER::Length(bool xflag, bool yflag, bool zflag)
{
	double L=0, dx=0, dy=0, dz=0;

    for(unsigned int i=1; i<u; i++)
	{
		if(xflag)
			dx = V[i][0] - V[i-1][0];
		else
			dx = 0;

		if(yflag)
	        dy = V[i][1] - V[i-1][1];
		else
			dy = 0;

		if(zflag)
			dz = V[i][2] - V[i-1][2];
		else
			dz = 0;
		
		L += sqrt(dx*dx + dy*dy + dz*dz);
	}

	return L;
}

void BEZIER::BinomialCoef()
{
    C[0] = C[n] = 1;
    
    double Cc;
     
    for(unsigned int k=1; k<n; k++)
    {
        Cc = 1;
        
        for(unsigned int i=1; i<=k; i++)
            Cc *=  double((n - (k - i)))/i;
           
        C[k] = int(Cc);
    }
}


