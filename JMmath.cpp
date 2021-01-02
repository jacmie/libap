#include <math.h>
#include <iostream>

using namespace std;

void RotatePointRad(double &x, double &y, double AngRad)
{
	double r = sqrt( x*x + y*y );
	
	x += r * cos(AngRad);
    y += r * sin(AngRad);
}

void RotatePointDeg(double &x, double &y, double AngDeg)
{
	RotatePointRad(x, y, AngDeg*M_PI/180);
}

void RotatePointRefRad(double &x, double &y, double AngRad, double Ref)
{
	x -= Ref;
	
	double xx = y*sin(AngRad) + x*cos(AngRad);
	double yy = y*cos(AngRad) - x*sin(AngRad);
	
	x = xx;
	y = yy;
	
	x += Ref;
}

void RotatePointRefDeg(double &x, double &y, double AngDeg, double Ref)
{
	RotatePointRefRad(x, y, AngDeg*M_PI/180, Ref);
}

void LinearFunction(double x1, double y1, double x2, double y2, double &A, double &B)
{
	A = (y2 - y1)/(x2 - x1);
	B = y1 - A*x1;
}

void LinearFunction(double &A, double &B, double x1, double y1, double fiDeg)
{
    A = tan(fiDeg*M_PI/180);
    B = y1 - A*x1;
}

void Parabola(double &A, double &B, double &C, 
              double x1, double y1,
              double x2, double y2,
              double x3, double yprim)
{
    A = (y2 - y1 + x1*yprim - x2*yprim) / (x2*x2 - x1*x1 + 2*x1*x3 - 2*x2*x3);
    B = yprim - 2*A*x3;
    C = y1 - x1*yprim + 2*A*x1*x3 - A*x1*x1;
}

void Circle(double x1, double y1, double x2, double y2, double x3, double y3, double &A, double &B, double &R)
{
	double dX2 = x2 - x1;
	double dX3 = x3 - x1;
	double dY2 = y2 - y1;
	double dY3 = y3 - y1;
	double C2 = x2*x2 + y2*y2 - x1*x1 - y1*y1;
	double C3 = x3*x3 + y3*y3 - x1*x1 - y1*y1;

	A = 0.5*(C3 - C2*dY3/dY2) / (dX3 - dX2*dY3/dY2);
	B = 0.5*(C2 - 2*A*dX2) / dY2;
	R = sqrt((A - x1)*(A - x1) + (B - y1)*(B - y1));
}

double LeastSquares(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2) );
}

int A_x(int n, double *C, double **dH, double *Xo)
{    
    for(int x=0; x<n; x++)
    {
        double s=0;    
            
        for(int y=0; y<n; y++)
        {
            s = s + dH[x][y]*Xo[y];
            C[x] = s;
        }
    }

	return 1;
}

double detA(int n, double **A)
{
    int k=0, g=0;
    double plus=0, minus=0, m1=1, m2=1;
    
    for(int j=0; j<n; j++)
    {
        k=j;
        m1 = 1;
        
        for(int i=0; i<n; i++)
        {
            m1 = m1 * A[i][k];
           
            if(k == n-1)
                k=0;
                
            else
                k++;
        }
        
        plus = plus + m1;
        
        g=j;
        m2 = 1;
        
        for(int i=0; i<n; i++)
        {
            m2 = m2 * A[i][g];
            
            if(g == 0)
                g = n-1;  
            
            else if(g <= n)
                g--;
        }
        
        minus = minus + m2;
    }
    
    //cout << endl << "det[A] = " << plus - minus << endl << endl;    
    
    return plus - minus;
}

int Gauss(int n, double **A, double *X, double *D)
{
    int nmax;
    double amax, b, c, lambda;
    
    for(int k=0; k<n; k++) 
    {
        //selection of pivoting element in thirs column  

        amax = fabs(A[k][k]);
        nmax = k;
        
        for(int i=k+1; i<n; i++)
        {           
            if(fabs(A[i][k]) > amax) 
            {
                amax = fabs(A[i][k]);   //modulus of the pivoting element
                nmax = i;
            }  
        }
        
        //transposition of the rows, row with pivoting element on top        
                 
        if(amax >= 1.0e-21) //numerical zero
        {  
            for(int i=k; i<n; i++)
            {     
                b=A[k][i];
                A[k][i]=A[nmax][i];
                A[nmax][i]=b;
            }
   
            b=D[k];
            D[k]=D[nmax];
            D[nmax]=b;
        }
         
        else
        {
            cout << "ERROR GAUSS: modulus of pivoting element < 0 -> singular matrix" << endl;
            cout << "pivoting element = " << amax << endl;
            break;
        }
        
        //Gauss elimination
   
        // I Step
        
        //devide by pivoting element
           
        c=1.0/A[k][k];
      
        for(int i=k; i<n; i++)
            A[k][i] = A[k][i]*c;
   
        D[k]=D[k]*c;
        
        
        for(int i=0; i<n; i++)    //if i,k=n
        {        
            lambda = -A[i][k]/A[k][k];          
       
            if(i>k)
                D[i] = D[i]+ D[k]*lambda;   
       
            for(int j=k; j<n; j++)
            {      
                if(i>k)
                    A[i][j] = A[i][j] + A[k][j]*lambda;  
                
                else
                    break;
            }     
        }     
    }   
        
    // II Step
    
    for(int i=n-1; i>=0; i--)
    {
        double t=0;

        for(int j=i; j<n; j++)
            t = t + A[i][j]*X[j];

        X[i] = (D[i]-t)/A[i][i];
    }  
	
	return 1;
}

int Gauss_Jordan(int n, double **A, double *D)
{
    int nmax, flag=1;
    double amax, b, c, lambda;
    
    for(int k=0; k<n; k++) 
    {      
        //selection of pivoting element in thirs column  

        amax = fabs(A[k][k]);
        nmax = k;
        
        for(int i=k+1; i<n; i++)
        {           
            if(fabs(A[i][k]) > amax) 
            {
                amax = fabs(A[i][k]);   //modulus of the pivoting element
                nmax = i;
            }  
        }
        
        //transposition of the rows, row with pivoting element on top        
                 
        if(amax >= 10e-16) //numerical zero
        {  
            for(int i=k; i<n; i++)
            {     
                b=A[k][i];
                A[k][i]=A[nmax][i];
                A[nmax][i]=b;
            }
   
            b=D[k];
            D[k]=D[nmax];
            D[nmax]=b;
        }
         
        else
        {
            cout << "ERROR GAUSS: modulus of pivoting element < 0 -> singular matrix" << endl;
            cout << "pivoting element = " << amax << endl;
            flag = 0;
            break;
        }

        //Gauss-Jordan elimination
      
        //devide by pivoting element
           
        c=1.0/A[k][k];
      
        for(int i=k; i<n; i++)
            A[k][i] = A[k][i]*c;
   
        D[k]=D[k]*c;
        
        //elimination
        
        for(int i=0; i<n; i++)    //if i,k=n
        {        
            lambda = -A[i][k]/A[k][k];          
       
            if(i!=k)
                D[i] = D[i]+ D[k]*lambda;   
       
            for(int j=k; j<n; j++)
            {      
                if(i!=k)
                    A[i][j] = A[i][j] + A[k][j]*lambda;  
            }     
        }     
    }
    
    return flag;
}

int Scale_A(int n, double *X, double *dF, double **H)
{
    double sum, Hbis[3][3];
   
    double **D1;  
    D1    = new double *[n];
    D1[0] = new double  [n*n];
    
    for(int i=1; i<n; i++)      
        D1[i] = D1[i-1] + n;
        
    //*** D1 init ***
   
    for(int j=0; j<n; j++)
    {   
        for(int i=0; i<n; i++)
        {
            if(j==i)
                D1[j][i] = fabs( X[j] );
            
            else
                D1[j][i] = 0;
        }
    } 
    
    //*** scale H ***
    
    for(int j=0; j<n; j++)
    {   
        for(int i=0; i<n; i++)
        {  
            sum = 0;
            
            for(int s=0; s<n; s++)
            {
                sum = sum + D1[j][s]* H[i][s] ; 
               
                Hbis[j][i] = sum;
            }
        }
    }
    
    for(int j=0; j<n; j++)
    {
        for(int i=0; i<n; i++)
        {  
            sum = 0;
            
            for(int s=0; s<n; s++)
            {
                sum = sum + Hbis[j][s]* D1[i][s] ; 
               
                H[j][i] = sum;
            }
        }
    }
       
    delete [] D1[0];
    delete [] D1;

	return 1;
}

int x_yT(int n, double *x, double *y, double **A)
{    
    for(int i=0; i<n; i++)  
    {
        for(int j=0; j<n; j++)
            A[i][j] = x[j]*y[i];    
    }

	return 1;
}

double xT_A_y(int n, double *x, double **A, double *y, double **C) 
{
    for(int i=0; i<n; i++) 
    {
        for(int z=0; z<n; z++)
            C[i][z] = x[i]*A[i][z];
    }
    
    double H = 0;
   
    for(int i=0; i<n; i++) 
    {
        for(int z=0; z<n; z++)
            H = H + C[i][z]*y[z];
    }
    
    return H;
}

double xT_y(int n, double *x, double *y)
{
    double r = 0;
    
    for(int i=0; i<n; i++)  
        r += x[i]*y[i]; 
        
    return r;
}
