#ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_

#include <cstddef>

template <class ARRAY_TYPE>
class DYNAMIC_ARRAY
{
    public:
    
    int xn;
    
	ARRAY_TYPE   *Array;
    
    DYNAMIC_ARRAY()
	{
	}
    
	DYNAMIC_ARRAY(int xmax)
	{
		InitArray(xmax);
	}
	
    int InitArray(int xmax)
	{
		xn = xmax;
		
		Array = new ARRAY_TYPE [xn];
        
		if(Array == NULL)
			return 0;
    
		return 1;
	}
	
	void FillArray(ARRAY_TYPE Value)
	{
		for(int i=0; i<xn; i++)
			Array[i] = Value;
	}

    int DelArray()
	{     
		if(Array == NULL)
			return 0;
         
		delete [] Array;
    	
		return 1;
	}
};

template <class ARRAY_TYPE>
class DYNAMIC_ARRAY_2D
{
    public:
    
    int xn, yn;
   
    ARRAY_TYPE  **Array2d;
    
    DYNAMIC_ARRAY_2D()
	{
	}
    
    DYNAMIC_ARRAY_2D(int xmax, int ymax)
	{
		InitArray2d(xmax, ymax);
	}
	
    int InitArray2d(int xmax, int ymax)
	{
		xn = xmax;
		yn = ymax;
    
		Array2d = new ARRAY_TYPE *[xn];
    
		for( int x=0; x<xn; x++)
			Array2d[x] = new ARRAY_TYPE [yn];
        
		if(Array2d == NULL)
			return 0;
    
		return 1;
	}
	
	void FillArray2d(ARRAY_TYPE Value)
	{
		for(int i=0; i<xn; i++)
		{
			for(int j=0; j<yn; j++)
				Array2d[i][j] = Value;
		}
	}

    int DelArray2d()
	{     
		if(Array2d == NULL)
			return 0;
        
		else 
		{
			for( int x=0; x<xn; x++)
				delete [] Array2d[x];
        
			delete [] Array2d;
		}
	
		return 1;
	}
};

template <class ARRAY_TYPE>
class DYNAMIC_ARRAY_3D
{
    public:
    
    int xn, yn, zn;
    
    ARRAY_TYPE ***Array3d;
    
    DYNAMIC_ARRAY_3D()
	{
	}
    
    DYNAMIC_ARRAY_3D(int xmax, int ymax, int zmax)
	{
		InitArray3d(xmax, ymax, zmax);
	}

    int InitArray3d(int xmax, int ymax, int zmax)
	{
		xn = xmax;
		yn = ymax;
		zn = zmax;
    
		Array3d = new ARRAY_TYPE **[xn];
     
		for( int x=0; x<xn; x++)
		{   
			Array3d[x] = new ARRAY_TYPE *[yn];
        
			for( int y=0; y<yn; y++)
				Array3d[x][y] = new ARRAY_TYPE [zn];
		}
    
		if(Array3d == NULL)
			return 0;
     
		return 1;
	}

	void FillArray3d(ARRAY_TYPE Value)
	{
		for(int i=0; i<xn; i++)
		{
			for(int j=0; j<yn; j++)
			{
				for(int k=0; k<zn; k++)
					Array3d[i][j][k] = Value;
			}
		}
	}

    int DelArray3d()
	{     
		if(Array3d == NULL)
			return 0;
        
		else 
		{
			for( int x=0; x<xn; x++)
			{
				for( int y=0; y<yn; y++)
					delete [] Array3d[x][y];
			}   
    
			for( int x=0; x<xn; x++)
				delete [] Array3d[x];
        
			delete [] Array3d;
		}
	
		return 1;
	}
};

#endif