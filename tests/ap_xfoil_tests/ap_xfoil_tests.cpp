#include <gtest/gtest.h>

#include "ap_xfoil.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ap;

#ifndef __APPLE__  // no Xfoil for MacOS, to do

TEST(ap_xfoil_tests, make_airfoil) {
	XFOIL createFoil;
#ifdef _WIN32
	createFoil.global_pipe_command = ".\\bin\\windows\\Xfoil.exe > .\\out\\out\\Xfoil.log";
#else
	createFoil.global_pipe_command = "./bin/linux/Xfoil > ./out/Xfoil.log";
#endif
	EXPECT_EQ(0, createFoil.MakeAirfoil("NACA 23012", "./out/NACA23012.dat"));
	EXPECT_EQ(0, createFoil.MakeAirfoil("NACA 2412", "./out/NACA2412.dat"));
}

TEST(ap_xfoil_tests, mix_airfoils) {
	XFOIL createFoil;
#ifdef _WIN32
	createFoil.global_pipe_command = ".\\bin\\windows\\Xfoil.exe > .\\out\\out\\Xfoil.log";
#else
	createFoil.global_pipe_command = "./bin/linux/Xfoil > ./out/Xfoil.log";
#endif	
	EXPECT_EQ(0, createFoil.Mixing("./out/NACA23012.dat", "./out/NACA2412.dat", "./out/AirfoilMix.dat"));
}

TEST(ap_xfoil_tests, modify) {
	XFOIL createFoil;
#ifdef _WIN32
	createFoil.global_pipe_command = ".\\bin\\windows\\Xfoil.exe > .\\out\\out\\Xfoil.log";
#else
	createFoil.global_pipe_command = "./bin/linux/Xfoil > ./out/Xfoil.log";
#endif	
	createFoil.T   = 0.1;
	createFoil.T_x = 0.3;
	createFoil.F   = 0.0;
	createFoil.F_x = 0.4;
	EXPECT_EQ(0, createFoil.ModifyAirfoil("LOAD TestDir/JMxfoil/AirfoilMix.dat", "TestDir/JMxfoil/AirfoilMixMod.dat"));
}

TEST(ap_xfoil_tests, analyz) {
	XFOIL createFoil;
#ifdef _WIN32
	createFoil.global_pipe_command = ".\\bin\\windows\\Xfoil.exe > .\\out\\out\\Xfoil.log";
	DelFile(".\\out\\XfoilData.dat");
	EXPECT_EQ(0, createFoil.Analyz(1, 3, "LOAD ./out/NACA2412.dat", "./out/XfoilData.dat", ".\\bin\\windows\\Xfoil.exe > .\\out\\XfoilAnalyze.log"));
#else
	createFoil.global_pipe_command = "./bin/linux/Xfoil > ./out/Xfoil.log";
	DelFile("./out/XfoilData.dat");
	EXPECT_EQ(0, createFoil.Analyz(1, 3, "LOAD ./out/NACA2412.dat", "./out/XfoilData.dat", "./bin/linux/Xfoil > ./out/XfoilAnalyze.log"));
#endif	

	int err_nr;
	string errors = "0";
	createFoil.Convergence("./out/XfoilAnalyze.log", err_nr, errors);
	EXPECT_EQ(0, err_nr);

	if(err_nr == 0)
	{
		if(0 == createFoil.GetData((char *) "./out/XfoilData.dat"))
		{
			EXPECT_EQ(3, createFoil.Alfa);
			EXPECT_EQ(0.647, createFoil.CL);
			EXPECT_EQ(0.01074, createFoil.CD);
			EXPECT_EQ(0.00234, createFoil.CDp);
			EXPECT_EQ(-0.0659, createFoil.CM);
			EXPECT_EQ(0.6177, createFoil.Top_Xtr);
			EXPECT_EQ(1, createFoil.Bot_Xtr);
		}
		
		else
			clog << "Xfoil data reading error!!!" << endl;
	}
	
	else
		clog << errors << endl;
}

#endif
