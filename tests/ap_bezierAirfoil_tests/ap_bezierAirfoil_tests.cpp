#include <gtest/gtest.h>
#include "../compare_files.h"

#include "ap_bezierAirfoil.h"

using namespace ap;

TEST(ap_bezierAirfoil_tests, from_2_bezier_curves) {
	BEZIER_AIRFOIL Airfoil2b;
    Airfoil2b.Init2b(6, 60);

    Airfoil2b.SetLEcircle(0.01, -0.02, 0.0, 0.0, 0.01, 0.02);
    
    Airfoil2b.SetTEpointB(1.0, -0.001,  0.02);
    Airfoil2b.SetTEpointT(1.0,  0.001, -0.02);
    
	Airfoil2b.SetMaxTh(0.3, 0.05);
	Airfoil2b.SetMinTh(0.3, -0.05);
    
    Airfoil2b.InitAirfoilSplinePoints();

	std::string str1, str2;
    Airfoil2b.PrintOutPoles("./out/out_bezierAiroil2bPoles.xls");
	EXPECT_EQ(0, Files2str("bezierAiroil2bPoles.xls", str1, str2));
	EXPECT_EQ(str1, str2);

	Airfoil2b.PrintOutVertex("./out/out_bezierAiroil2bVertex.xls", "Airfoil2b");
	EXPECT_EQ(0, Files2str("bezierAiroil2bVertex.xls", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_bezierAirfoil_tests, from_4_bezier_curves) {
	BEZIER_AIRFOIL Airfoil4b;
    Airfoil4b.Init4b(4, 60, 5, 40);

    Airfoil4b.SetLEcircle(0.01, -0.02, 0.0, 0.0, 0.01, 0.02, 11);
    
    Airfoil4b.SetTEpointB(1.0, -0.001,  0.02);
    Airfoil4b.SetTEpointT(1.0,  0.001, -0.02);
    
    Airfoil4b.SetMaxTh(0.3, 0.05);
	Airfoil4b.SetMinTh(0.3, -0.05);
    
    Airfoil4b.InitAirfoilSplinePoints();

	std::string str1, str2;
    Airfoil4b.PrintOutPoles("./out/out_bezierAiroil4bPoles.xls");
	EXPECT_EQ(0, Files2str("bezierAiroil4bPoles.xls", str1, str2));
	EXPECT_EQ(str1, str2);
	Airfoil4b.PrintOutVertex("./out/out_bezierAiroil4bVertex.xls", "Airfoil4b");
	EXPECT_EQ(0, Files2str("bezierAiroil4bVertex.xls", str1, str2));
	EXPECT_EQ(str1, str2);
}
