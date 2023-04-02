#include <gtest/gtest.h>
#include "../compare_files.h"

#include "ap_substitute.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ap;

TEST(ap_substitute_tests, insert_1) {
	SUBSTITUTE sub("./data/insert_1.txt", "./out/out_insert_1.txt", '%');

	EXPECT_EQ(1, sub.AddVariable("", 999) );
	EXPECT_EQ(0, sub.AddVariable("0", 111) );
	EXPECT_EQ(0, sub.AddVariable("1", 222) );
	EXPECT_EQ(0, sub.AddVariable("uno", 333) );
	EXPECT_EQ(0, sub.AddVariable("due", "444") );
	EXPECT_EQ(0, sub.AddVariable("tre", "555") );
    EXPECT_EQ(1, sub.AddVariable("ff", "") );
    EXPECT_EQ(0, sub.AddVariable("mod", "modify") );
	EXPECT_EQ(0, sub.AddVariable("naca", 2412) );

    EXPECT_EQ(0, sub.Insert() );

	std::string str1, str2;
	EXPECT_EQ(0, Files2str("insert_1.txt", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_substitute_tests, insert_2) {
	SUBSTITUTE sub("./data/insert_2.txt", "./out/out_insert_2.txt", '@', '&');

	EXPECT_EQ(1, sub.AddVariable("", 999) );
	EXPECT_EQ(0, sub.AddVariable("0", 111) );
	EXPECT_EQ(0, sub.AddVariable("1", 222) );
	EXPECT_EQ(0, sub.AddVariable("uno", 333) );
	EXPECT_EQ(0, sub.AddVariable("due", "444") );
	EXPECT_EQ(0, sub.AddVariable("tre", "555") );
    EXPECT_EQ(1, sub.AddVariable("ff", "") );
    EXPECT_EQ(0, sub.AddVariable("mod", "modify") );
	EXPECT_EQ(0, sub.AddVariable("naca", 2412) );

    EXPECT_EQ(0, sub.Insert() );

	std::string str1, str2;
	EXPECT_EQ(0, Files2str("insert_2.txt", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_substitute_tests, derive) {
	
	SUBSTITUTE sub("./data/xfoil_data_template.dat", "./data/xfoil_data.dat", '@', '&');
	
	EXPECT_EQ(0, sub.AddVariable("@CL", 0) );
	EXPECT_EQ(0, sub.AddVariable("@AoA&", 0) );
	EXPECT_EQ(0, sub.AddVariable("@CD", 0) );
	EXPECT_EQ(0, sub.AddVariable("CM&", 0) );
    EXPECT_EQ(1, sub.AddVariable("", 0) );

	sub.Extract();

	EXPECT_EQ("0.6470",  sub.var[0].value);
	EXPECT_EQ("3.000",   sub.var[1].value);
	EXPECT_EQ("0.01074", sub.var[2].value);
	EXPECT_EQ("-0.0659", sub.var[3].value);
}
