#include "JMfilter.h"

using namespace std;

FILTER::FILTER(int array_n, int filter_n, double amplitude)
{
	//*** Init parameters ***
	
	n  = array_n;
	fn = filter_n;
	
	filter.InitArray(fn);
	Xfiltered.InitArray(n);
	Xfiltered.FillArray(0.0);
	
	//*** Make filter ***
	
    fn += 2;
    
    double del = 2*M_PI/(fn-1);
    
    double sum = 0;
    
    for(int i=1; i<fn-1; i++)
    {
        filter.Array[i-1] = amplitude*0.5*(1-cos(i*del));
        sum += filter.Array[i-1];
    }
   
    for(int i=1; i<fn-1; i++)
        filter.Array[i-1] /= sum;
        
	fn -= 2;
}

FILTER::~FILTER()
{
	filter.DelArray();
	Xfiltered.DelArray(); 
}

int FILTER::Filter(double *Xinput, bool overwrite)
{
	if(fn > n)
		return 0;
	
    int fcount, findicator;
	
	bool   filt_edge;
    double filt_sum;
	
    for(int i=0; i<n; i++)
    {
        fcount = 0;
		filt_edge = 0;
		filt_sum  = 0;
        Xfiltered.Array[i] = 0;
        
        for(int f=0; f<fn; f++)
        {
            findicator = i - int(0.5*fn) + f;
            
            if(0 <= findicator && findicator < n)
            {
                ++fcount;
                Xfiltered.Array[i] += filter.Array[f]*Xinput[findicator];
            }
			
			else
			{
				filt_edge = 1;
				filt_sum += filter.Array[f];
			}
        }
       
		if(filt_edge)
			Xfiltered.Array[i] /= (1-filt_sum);
    }
	
	if(overwrite)
		for(int x=0; x<n; x++)
			Xinput[x] = Xfiltered.Array[x]; 
		
	return 1;
}

int FILTER::FilterRange(int shift, double *Xinput, bool overwrite)
{
	if(fn > n)
		return 0;
	
	DYNAMIC_ARRAY <double> Xin(n);
	
	for(int x=0; x<n; x++) //"n" limits range
		Xin.Array[x] = Xinput[shift + x]; 
	
    Filter(Xin.Array, overwrite);
    
	if(overwrite)
		for(int x=0; x<n; x++)
			Xinput[x + shift] = Xin.Array[x];
		
	Xin.DelArray();
	
	return 1;
}

void FILTER::Print(std::ofstream &out)
{
	for(int x=0; x<n; x++)
        out << x << "\t" << Xfiltered.Array[x] << endl;
}