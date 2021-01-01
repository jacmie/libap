#include "JMairfoilTransform.h"

using namespace std;

AIRFOIL_TRANSFORM::AIRFOIL_TRANSFORM()
{
	NrOfRows = 0;
	NrOfCord = 0;
	
	rotation = 0;
	ref		 = 0.25;
	scale	 = 1;
	strch	 = 1;
	dy		 = 0; //for X axis rotation
	dz		 = 0; //for X axis rotation
	trans_x	 = 0;
	trans_y  = 0;
	trans_z  = 0;
}

AIRFOIL_TRANSFORM::~AIRFOIL_TRANSFORM()
{
	delete [] x;
	delete [] y;
	delete [] z;	
}

int AIRFOIL_TRANSFORM::ReadAirfoil(char *AirfoilFile)
{
	//*** Open airoil data file ***
	
	ifstream in(AirfoilFile);

    if(!in)
    {
		//fl_alert("Can't read airfoil:\n%s", AirfoilFile);
		clog << "Can't read airfoil:" << AirfoilFile << endl;
        return 0;
    }

	//*** Count rows and initialize table ***
	
	CountRows(in);
	
	x = new double [NrOfRows];
	y = new double [NrOfRows];
	z = new double [NrOfRows];
   
    //*** Check for airfoil file format ***
    
    CheckFileFormat(in);
       	
    //*** Operations on profile points ***
     
    //while (!in.eof())   
    for(int i=0; i<NrOfCord; i++)
	{     
        in >> x[i] >> z[i]; 
        y[i] = 0;  
	}
	
	in.close();
	
	return 1;
}

void AIRFOIL_TRANSFORM::CountRows(ifstream &in)
{
    char wiersz [255];

    while (!in.eof())
    {
        in.getline(wiersz, sizeof(wiersz));
        NrOfRows++;
		//cout << wiersz << "\t" << NrOfRows << endl;
    }

    NrOfRows--;

	in.clear();
	in.seekg(0, ios::beg);
}

void AIRFOIL_TRANSFORM::CheckFileFormat(ifstream &in)
{
	char line[256];
    stringstream name;
    
    in.getline(line, sizeof(line), '\n');
    
    string str(line);
   
    if (string::npos == str.find_first_not_of("-+e.0123456789 \t"))
    {
        name << str;
		name >> x[0] >> z[0];
		NrOfCord = NrOfRows;
        //i = 1;
    }
    
    else
		NrOfCord = NrOfRows - 1;
        //i = 0;
}

void AIRFOIL_TRANSFORM::Transformations()
{		
	for(int i=0; i<NrOfCord; i++)
	{
		// 1. rotation about Y axis (Alfa)
		RotatePointRefRad(x[i], z[i], rotation*M_PI/180, ref);
		
		// 2. scaling
		x[i] *= scale;
		z[i] *= scale;
           
		// 2.1 streach
		x[i] *= strch;
		  
		// 3. mirror profile
		//prof[i].z = prof[i].z * mirror;        
               
		// 4. rotation about X axis
		
		double katN;
	
		//dy = data[j].y - data[j-1].y;
		//dz = data[j].z - data[j-1].z;
          
		if(dy!=0)                      
			katN = -atan(dz/dy);        
         
		else  //dy=0 
		{
			if(dz == 0)   
				katN = 0;
         
			else
				katN = -M_PI/2;
		}
			
		RotatePointRefRad(y[i], z[i], katN, y[i]);
		
		// 5. X, Y, Z translations  
        x[i] += trans_x; 
		y[i] += trans_y;             
		z[i] += trans_z;
	}
}

int AIRFOIL_TRANSFORM::WriteAirfoil(char *AirfoilFile)
{
	ofstream out(AirfoilFile);

    if(!out)
    {
         cout << "Out data error!!!" << endl << endl;
         return 1;
    }
    
    //int w = --i;
    
    for(int i=0; i<NrOfCord; i++) 
    {
        //cout << fixed << setprecision(4) << x[i] << "\t" << y[i] << "\t" << z[i] << endl;   
        out << fixed << setprecision(4) << x[i] << "\t" << y[i] << "\t" << z[i] << endl;  
    }
       
    out.close();
	
	return 0;
}

/*
void WING_DEF::Z_correction(int nprof, double Xr, double Yr, double Zr, double Xt, double Yt, double Zt, AIRFOIL *prof)
{
	double A, B, C, D, E, F;
	
	LinearFunction(Yr, Xr, Yt, Xt, A, B);	//XY
	LinearFunction(Yr, Zr, Yt, Zt, C, D);	//ZY
	
	int p, n = 20;
	double x, y, z;
	double zprim, dz;
	
	for(int j=0; j<n; j++)	//po Y
	{
		y = j*10;
		
		x = A*y + B;
		z = C*y + D;
		
		//poszukiwanie punktu na profilu
		
		for(p=0; p<nprof; p++)	
		{
			if(prof[p].x > x)
				break;
		}
		
		//funkcja liniowa dla lokalnych pounktów na profilu
		
		LinearFunction(prof[p+1].x, prof[p+1].z, prof[p].x, prof[p].z, E, F);	//ZX
		
		zprim = E*x + F;

		//wykonanie korekty dz
		
		dz = z - zprim;
		
		for(p=0; p<nprof; p++)	
			prof[p].z += dz;
	}
}*/
