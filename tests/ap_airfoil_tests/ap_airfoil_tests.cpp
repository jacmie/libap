#include <gtest/gtest.h>

#include "ap_airfoil.h"

#include <iostream>
#include <fstream>

using namespace std;

int Files2str(const std::string &fileName, std::string &str1, std::string &str2)
{
	ifstream in1("./airfoil_ref/ref_" + fileName);
	if(!in1) return 1;
	std::stringstream buf1;
	buf1 << in1.rdbuf();
	str1 = buf1.str();
	in1.close();

	ifstream in2("./airfoil_out/out_" + fileName);
	if(!in2) return 2;
	std::stringstream buf2;
	buf2 << in2.rdbuf();
	str2 = buf2.str();
	in2.close();

	return 0;
}

TEST(ap_airfoilTest, IO_operations) {

	ap::AIRFOIL airfoil;

	clog << "PRF" << endl;
	airfoil.Read("./airfoil_data/NN_1817.prf");
	airfoil.WriteDat("./airfoil_out/out_NN_1817.dat");
	airfoil.WritePrf("./airfoil_out/out_NN_1817.prf");
    	
	clog << "PRF2" << endl;
	airfoil.Read("./airfoil_data/CLARK-Y.PRF");
	airfoil.WriteDat("./airfoil_out/out_CLARK-Y.dat"); 
	airfoil.WritePrf("./airfoil_out/out_CLARK-Y.prf");

	clog << "KOO" << endl;
	airfoil.Read("./airfoil_data/cb3013.KOO");
	airfoil.WriteDat("./airfoil_out/out_cb3013.dat");
	airfoil.WritePrf("./airfoil_out/out_cb3013.prf");

	clog << "XFOIL" << endl;
	airfoil.Read("./airfoil_data/fx66h80.dat");
	airfoil.WriteDat("./airfoil_out/out_fx66h80.dat");
	airfoil.WritePrf("./airfoil_out/out_fx66h80.prf");
	
	airfoil.Read("./airfoil_data/fx66h80_d0_f.dat");
	airfoil.WriteDat("./airfoil_out/out_fx66h80_d0_f.dat"); // heal !!!!!
	airfoil.WritePrf("./airfoil_out/out_fx66h80_d0_f.prf");
	
	airfoil.Read("./airfoil_data/fx66h80_d0_r.dat");
	airfoil.WriteDat("./airfoil_out/out_fx66h80_d0_r.dat");
	airfoil.WritePrf("./airfoil_out/out_fx66h80_d0_r.prf");
	
	airfoil.Read("./airfoil_data/fx66h80_d0_r_ne.dat");
	airfoil.WriteDat("./airfoil_out/out_fx66h80_d0_r_ne.dat"); // heal !!!!!
	airfoil.WritePrf("./airfoil_out/out_fx66h80_d0_r_ne.prf");
	
	clog << "LED" << endl;
	airfoil.Read("./airfoil_data/rae104.dat");
	airfoil.WriteDat("./airfoil_out/out_rae104.dat");
	airfoil.WritePrf("./airfoil_out/out_rae104.prf");
	
	std::string str1, str2;

	EXPECT_EQ(0, Files2str("NN_1817.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	EXPECT_EQ(1, Files2str("NN_1817.prf", str1, str2));
	EXPECT_EQ(str1, str2);


	//Profil -> ReadNaca( (char*)AirfoilFile.c_str(), Vnr ); // generate NACA
/*
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
	//EXPECT_DOUBLE_EQ(0, 1);
}
