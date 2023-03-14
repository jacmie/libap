#include <gtest/gtest.h>

#include "ap_airfoil.h"

#include <iostream>
#include <fstream>

using namespace std;

TEST(ap_airfoilTest, airfoil_format_recognition) {
	ap::AIRFOIL airfoil;

	// default
	EXPECT_DOUBLE_EQ(0, airfoil.GetReadType());
	EXPECT_DOUBLE_EQ(ap::AIRFOIL_BY_CONTENT, airfoil.GetReadType());
	
	airfoil.SetReadType(1); // 0 - recognition by content, 1 - recognition by filename extention
	
	EXPECT_DOUBLE_EQ(1, airfoil.GetReadType());
	EXPECT_DOUBLE_EQ(ap::AIRFOIL_BY_EXTENSION, airfoil.GetReadType());
	
	airfoil.SetReadType(ap::AIRFOIL_BY_CONTENT); // 0 - recognition by content, 1 - recognition by filename extention
	
	EXPECT_DOUBLE_EQ(0, airfoil.GetReadType());
	EXPECT_DOUBLE_EQ(ap::AIRFOIL_BY_CONTENT, airfoil.GetReadType());
}

TEST(ap_airfoilTest, IO_operations) {

	ap::AIRFOIL airfoil;

	airfoil.SetReadType(ap::AIRFOIL_BY_CONTENT); // 0 - recognition by content, 1 - recognition by filename extention

//	clog << "PRF" << endl;
//	airfoil.Read("./airfoil_data/NN_1817.prf");
//    airfoil.ReadStatus();	
/*    	
	clog << "PRF2" << endl;
	airfoil.Read("./airfoil_data/CLARK-Y.PRF");
    airfoil.ReadStatus();	

	clog << "KOO" << endl;
	airfoil.Read("./airfoil_data/cb3013.KOO");
    airfoil.ReadStatus();	
i*/
	clog << "XFOIL" << endl;
	//airfoil.Read("./airfoil_data/fx66h80.dat");
	airfoil.Read("./airfoil_data/fx66h80_d0_r_ne.dat");
    airfoil.ReadStatus();	
/*	
	clog << "LED" << endl;
	airfoil.Read("./airfoil_data/rae104.dat");
    airfoil.ReadStatus();	
	//Profil -> ReadNaca( (char*)AirfoilFile.c_str(), Vnr ); // generate NACA

	std::vector <double> Xf;
	std::vector <double> Zf;
    
	for(int i=0; i<airfoil.Nf; i++)
	{
	    Xf.push_back(airfoil.Xf[i]);
	    Zf.push_back(airfoil.Zf[i]);
	}
	
	for(unsigned int i=0; i<Xf.size(); i++)
	    clog << i << "\t" << fixed << setprecision(5) << Xf[i] << "\t" << Zf[i] << endl;
	clog << endl;
*/
	// === Revers if necessary === 
   
	/* 
 	iType:
	    0 - PRF - PANUKL (prf1) - native PANUKL (4 columns) format \n
	    1 - PRF - prf2 - by L.Wiechers- NAME in header, N below header \n 
	    2 - KOO - koordinate by L.Wiechers \n
	    3 - DAT - SELIG - (Xfoil) \n
	    4 - DAT - LEDNICER
	*/

	//if(Profil->iType == 0 || Profil->iType == 1)
	//	ReversDataPointsOrder();

	//DELETE_( Profil );
	
	//for(unsigned int i=0; i<Xf.size(); i++)
	//    cerr << i << "\t" << fixed << setprecision(5) << Xf[i] << "\t" << Zf[i] << endl;
	EXPECT_DOUBLE_EQ(0, 1);
}
