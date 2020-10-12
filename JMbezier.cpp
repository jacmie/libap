#include "JMbezier.h"
#include "JMconsole.h"

using namespace std;
//extern CONSOLE con;

BEZIER::BEZIER()
{
}

BEZIER::BEZIER(int nmax, int umax)
{
	Init(nmax, umax);
}

void BEZIER::Init(int nmax, int umax)
{
	npt  = nmax;
    n    = nmax - 1;
    u    = umax;
    eps  = 1e-6;
    iter = 50;
    relax = 1;
	
    C.InitArray(npt);
	C.FillArray(0.0);
	
    P.InitArray2d(npt, 3);
	P.FillArray2d(0.0);
	
	V.InitArray2d(u, 3);
	V.FillArray2d(0.0);

    L.InitArray(u);
	L.FillArray(0.0);

	Vt.InitArray(u);
	Vt.FillArray(0.0);

    BinomialCoef();
}

BEZIER::~BEZIER()
{
	P.DelArray2d();
	V.DelArray2d();
	C.DelArray();
	L.DelArray();
	Vt.DelArray();
}

void BEZIER::Vertex(double t, double &X, double &Y, double &Z)
{
    X = Y = Z = 0;
        
    for(int k=0; k<npt; k++)
    {
        X += C.Array[k]*pow(t, k)*pow(1 - t, n - k)*P.Array2d[k][0];
        Y += C.Array[k]*pow(t, k)*pow(1 - t, n - k)*P.Array2d[k][1];
        Z += C.Array[k]*pow(t, k)*pow(1 - t, n - k)*P.Array2d[k][2];
    }
}

void BEZIER::VertexSeq()
{
    double t = 0;
    double du = 1/double(u-1);
    
    for(int x=0; x<u; x++)
    {
        Vertex(t, V.Array2d[x][0], V.Array2d[x][1], V.Array2d[x][2]);
		Vt.Array[x] = t;
        t += du;
    }
}

double BEZIER::tVertex(int XYZ, double Value)
{
    double min, max;
    PMinMax(XYZ, min, max);
    
    if(Value<min || Value>max)
    {
        cout << "!!!\tmin < X < max\t\t";
        cout << min << " < " << Value << " < " << max << endl;
        return 999;
    }
    
    else
    {
		double f, fprim;
        double t = (Value - min)/(max - min);
        
		if(t == 0 || t == 1)
			return t;
    
        for(int i=0; i<iter; i++) //Newton-Rapson search
        {    
            f = fprim = 0;
        
            //*** f ***
    
            for(int k=0; k<npt; k++)
                f += C.Array[k]*pow(t, k)*pow(1 - t, n - k)*P.Array2d[k][XYZ];
        
            f -= Value;
        
            //*** fprim ***
    
            for(int k=0; k<npt; k++)
			{
				fprim += C.Array[k]*P.Array2d[k][XYZ]*( k*pow(t, k-1)*pow(1 - t, n - k) + 
														  pow(t, k)*(n - k)*pow(1 - t, n - k - 1) );
			}
			
			if(fprim == 0)
			{
				cout << "Can't devide by fprim = 0!" << endl;
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
	double dx=0, dy=0, dz=0;

    for(int i=1; i<u; i++)
	{
		dx = V.Array2d[i][0] - V.Array2d[i-1][0];
        dy = V.Array2d[i][1] - V.Array2d[i-1][1];
		dz = V.Array2d[i][2] - V.Array2d[i-1][2];

		L.Array[i] = L.Array[i-1] + sqrt(dx*dx + dy*dy + dz*dz);
	}

	return L.Array[u-1];
}

double BEZIER::LengthXY()
{
	double dx=0, dy=0;

    for(int i=1; i<u; i++)
	{
		dx = V.Array2d[i][0] - V.Array2d[i-1][0];
        dy = V.Array2d[i][1] - V.Array2d[i-1][1];
		
		L.Array[i] = L.Array[i-1] + sqrt(dx*dx + dy*dy);
	}

	return L.Array[u-1];
}

double BEZIER::LengthYZ()
{
	double dy=0, dz=0;

    for(int i=1; i<u; i++)
	{
        dy = V.Array2d[i][1] - V.Array2d[i-1][1];
		dz = V.Array2d[i][2] - V.Array2d[i-1][2];

		L.Array[i] = L.Array[i-1] + sqrt(dy*dy + dz*dz);
	}

	return L.Array[u-1];
}

double BEZIER::LengthXZ()
{
	double dx=0, dz=0;

    for(int i=1; i<u; i++)
	{
        dx = V.Array2d[i][0] - V.Array2d[i-1][0];
		dz = V.Array2d[i][2] - V.Array2d[i-1][2];

		L.Array[i] = L.Array[i-1] + sqrt(dx*dx + dz*dz);
	}

	return L.Array[u-1];
}

void BEZIER::BinomialCoef()
{
    C.Array[0] = C.Array[n] = 1;
    
    double Cc;
     
    for(int k=1; k<n; k++)
    {
        Cc = 1;
        
        for(int i=1; i<=k; i++)
            Cc *=  double((n - (k - i)))/i;
           
        C.Array[k] = int(Cc);
    }
}

void BEZIER::PMinMax(int XYZ, double &min, double &max)
{
    min = max = P.Array2d[0][XYZ];
    
    for(int k=0; k<npt; k++)
    {
        if(P.Array2d[k][XYZ] < min)
            min = P.Array2d[k][XYZ];
            
        if(P.Array2d[k][XYZ] > max)
            max = P.Array2d[k][XYZ];    
    }
}

void BEZIER::PrintPoints(ostream &out)
{
    for(int i=0; i<npt; i++)
        out << P.Array2d[i][0] << "\t" << P.Array2d[i][1] << "\t" << P.Array2d[i][2] << endl;
}

void BEZIER::PrintVertex(ostream &out)
{
    for(int i=0; i<u; i++)
        out << V.Array2d[i][0] << "\t" << V.Array2d[i][1] << "\t" << V.Array2d[i][2] << endl;
}

