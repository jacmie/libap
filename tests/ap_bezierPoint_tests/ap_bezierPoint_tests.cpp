#include <gtest/gtest.h>

#include "ap_bezierPoint.h"

using namespace ap;

TEST(ap_bezierPoint_tests, set_single_value) {
    BEZIER_POINT <double> bezP;
    bezP.Set(9.9);
	
	EXPECT_EQ(9.9, bezP.x);
	EXPECT_EQ(9.9, bezP.y);
	EXPECT_EQ(9.9, bezP.z);
}

TEST(ap_bezierPoint_tests, set_values) {
    BEZIER_POINT <double> bezP;
    bezP.Set(1.1, 2.2, 3.3);
	
	EXPECT_EQ(1.1, bezP.x);
	EXPECT_EQ(2.2, bezP.y);
	EXPECT_EQ(3.3, bezP.z);
}

TEST(ap_bezierPoint_tests, set_array) {
    BEZIER_POINT <double> bezP;
    double vec[] = {1.1, 2.2, 3.3};
    bezP.Set(vec);
	
	EXPECT_EQ(1.1, bezP.x);
	EXPECT_EQ(2.2, bezP.y);
	EXPECT_EQ(3.3, bezP.z);
}

TEST(ap_bezierPoint_tests, set_vector) {
    BEZIER_POINT <double> bezP;
	std::vector <double> vec;
	vec.push_back(1.1);
	vec.push_back(2.2);
	vec.push_back(3.3);
    bezP.Set(vec);
	
	EXPECT_EQ(1.1, bezP.x);
	EXPECT_EQ(2.2, bezP.y);
	EXPECT_EQ(3.3, bezP.z);
}

TEST(ap_bezierPoint_tests, get_values) {
    BEZIER_POINT <double> bezP;
    bezP.Set(1.1, 2.2, 3.3);
    
	double x, y, z;
	bezP.Get(x, y, z);
	
	EXPECT_EQ(1.1, x);
	EXPECT_EQ(2.2, y);
	EXPECT_EQ(3.3, z);
}

TEST(ap_bezierPoint_tests, get_array) {
    BEZIER_POINT <double> bezP;
    bezP.Set(1.1, 2.2, 3.3);
    
	double vec[3];
	bezP.Get(vec);
	
	EXPECT_EQ(1.1, vec[0]);
	EXPECT_EQ(2.2, vec[1]);
	EXPECT_EQ(3.3, vec[2]);
}

TEST(ap_bezierPoint_tests, get_vector) {
    BEZIER_POINT <double> bezP;
    bezP.Set(1.1, 2.2, 3.3);
    
	std::vector <double> vec;
	vec.resize(3);
	bezP.Get(vec);
	
	EXPECT_EQ(1.1, vec[0]);
	EXPECT_EQ(2.2, vec[1]);
	EXPECT_EQ(3.3, vec[2]);
}

TEST(ap_bezierPoint_tests, get_sigle_value) {
    BEZIER_POINT <double> bezP;
    bezP.Set(1.1, 2.2, 3.3);
    
	EXPECT_EQ(2.2, bezP.Get(1));
}
