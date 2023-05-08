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

TEST(ap_airfoilTest, NACA_from_int) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;

	airfoil.GenerateNaca(23012);
	airfoil.WriteDat("./airfoil_out/out_naca_i_23012.dat");
	EXPECT_EQ(0, Files2str("naca_i_23012.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_naca_i_23012.prf");
	EXPECT_EQ(0, Files2str("naca_i_23012.prf", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_airfoilTest, NACA_from_str) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;

	airfoil.GenerateNaca("NACA 0012");
	airfoil.WriteDat("./airfoil_out/out_naca_s_0012.dat", 3);
	EXPECT_EQ(0, Files2str("naca_s_0012.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_naca_s_0012.prf", 3);
	EXPECT_EQ(0, Files2str("naca_s_0012.prf", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_airfoilTest, AIRFOIL_PRF4) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;
	airfoil.RestrictiveCheck(true);

	EXPECT_EQ(0, airfoil.Read("./airfoil_data/NN_1817.prf"));
	airfoil.WriteDat("./airfoil_out/out_NN_1817.dat");
	EXPECT_EQ(0, Files2str("NN_1817.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_NN_1817.prf");
	EXPECT_EQ(0, Files2str("NN_1817.prf", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_airfoilTest, AIRFOIL_PRF2) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;
	airfoil.RestrictiveCheck(true);

	EXPECT_EQ(2, airfoil.Read("./airfoil_data/CLARK-Y.PRF"));
	airfoil.WriteDat("./airfoil_out/out_CLARK-Y.dat"); 
	EXPECT_EQ(0, Files2str("CLARK-Y.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_CLARK-Y.prf");
	EXPECT_EQ(0, Files2str("CLARK-Y.prf", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_airfoilTest, AIRFOIL_KOO) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;
	airfoil.RestrictiveCheck(true);

	EXPECT_EQ(3, airfoil.Read("./airfoil_data/cb3013.KOO"));
	airfoil.WriteDat("./airfoil_out/out_cb3013.dat");
	EXPECT_EQ(0, Files2str("cb3013.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_cb3013.prf");
	EXPECT_EQ(0, Files2str("cb3013.prf", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_airfoilTest, AIRFOIL_XFOIL) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;
	airfoil.RestrictiveCheck(true);

	EXPECT_EQ(4, airfoil.Read("./airfoil_data/fx66h80.dat"));
	airfoil.WriteDat("./airfoil_out/out_fx66h80.dat");
	EXPECT_EQ(0, Files2str("fx66h80.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_fx66h80.prf");
	EXPECT_EQ(0, Files2str("fx66h80.prf", str1, str2));
	EXPECT_EQ(str1, str2);
	
	EXPECT_EQ(4, airfoil.Read("./airfoil_data/fx66h80_d0_f.dat"));
	airfoil.WriteDat("./airfoil_out/out_fx66h80_d0_f.dat"); // heal !!!!!
	EXPECT_EQ(0, Files2str("fx66h80_d0_f.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_fx66h80_d0_f.prf");
	EXPECT_EQ(0, Files2str("fx66h80_d0_f.prf", str1, str2));
	EXPECT_EQ(str1, str2);
	
	airfoil.Prf2Xfoil(); // heal by interpolation
	airfoil.WriteDat("./airfoil_out/out_fx66h80_d0_f_heal.dat");
	EXPECT_EQ(0, Files2str("fx66h80_d0_f_heal.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	
	EXPECT_EQ(4, airfoil.Read("./airfoil_data/fx66h80_d0_r.dat"));
	airfoil.WriteDat("./airfoil_out/out_fx66h80_d0_r.dat");
	EXPECT_EQ(0, Files2str("fx66h80_d0_r.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_fx66h80_d0_r.prf");
	EXPECT_EQ(0, Files2str("fx66h80_d0_r.prf", str1, str2));
	EXPECT_EQ(str1, str2);
	
	EXPECT_EQ(4, airfoil.Read("./airfoil_data/fx66h80_d0_r_ne.dat"));
	airfoil.WriteDat("./airfoil_out/out_fx66h80_d0_r_ne.dat");
	EXPECT_EQ(0, Files2str("fx66h80_d0_r_ne.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_fx66h80_d0_r_ne.prf");
	EXPECT_EQ(0, Files2str("fx66h80_d0_r_ne.prf", str1, str2));
	EXPECT_EQ(str1, str2);
	
	airfoil.Prf2Xfoil(); // heal by interpolation
	airfoil.WriteDat("./airfoil_out/out_fx66h80_d0_r_ne_heal.dat");
	EXPECT_EQ(0, Files2str("fx66h80_d0_r_ne_heal.dat", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_airfoilTest, AIRFOIL_L_DAT) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;
	airfoil.RestrictiveCheck(true);

	EXPECT_EQ(5, airfoil.Read("./airfoil_data/rae104.dat"));
	airfoil.WriteDat("./airfoil_out/out_rae104.dat");
	EXPECT_EQ(0, Files2str("rae104.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_rae104.prf");
	EXPECT_EQ(0, Files2str("rae104.prf", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_airfoilTest, AIRFOIL_TEclose) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;
	airfoil.RestrictiveCheck(true);

	EXPECT_EQ(0, airfoil.Read("./airfoil_data/NN_1817.prf"));
	airfoil.TEclose();
	
	airfoil.WriteDat("./airfoil_out/out_NN_1817_TE0.dat");
	EXPECT_EQ(0, Files2str("NN_1817_TE0.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_NN_1817_TE0.prf");
	EXPECT_EQ(0, Files2str("NN_1817_TE0.prf", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_airfoilTest, AIRFOIL_Normalize) {
	std::string str1, str2;

	ap::AIRFOIL airfoil;
	airfoil.GenerateNaca("naca 24012");
	airfoil.Normalize();

	airfoil.WriteDat("./airfoil_out/out_naca_s_24012.dat");
	EXPECT_EQ(0, Files2str("naca_s_24012.dat", str1, str2));
	EXPECT_EQ(str1, str2);
	airfoil.WritePrf("./airfoil_out/out_naca_s_24012.prf");
	EXPECT_EQ(0, Files2str("naca_s_24012.prf", str1, str2));
	EXPECT_EQ(str1, str2);
}
