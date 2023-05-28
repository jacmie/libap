#include <gtest/gtest.h>

#include "ap_convert.h"

using namespace std;
using namespace ap;

TEST(ap_convert_tests, Cstr2f) {
    char chRealShort[] = {"0.125"};
	float realShort = 0.125;
	EXPECT_EQ(realShort, Cstr2f(chRealShort));
    
	char chRealLong[] = {"0.123456789123456789123456789"}; 
	float realLong = 0.123456789123456789123456789;
	EXPECT_EQ(realLong, Cstr2f(chRealLong));
}

TEST(ap_convert_tests, Cstr2d) {
    char chRealShort[] = {"0.125"};
	double realShort = 0.125;
	EXPECT_EQ(realShort, Cstr2d(chRealShort));
    
	char chRealLong[] = {"0.123456789123456789123456789"}; 
	double realLong = 0.123456789123456789123456789;
	EXPECT_EQ(realLong, Cstr2d(chRealLong));
}

/*TEST(ap_convert_tests, f2Cstr) {
    char chRealShort[] = {"0.125"};
	float realShort = 0.125;
	EXPECT_EQ(*chRealShort, *f2Cstr("%.4f", realShort));
	EXPECT_EQ(*chRealShort, *f2Cstr(realShort));
    
	char chRealLong[] = {"0.123456789123456789123456789"}; 
	float realLong = 0.123456789123456789123456789;
	EXPECT_EQ(*chRealLong, *f2Cstr("%.4f", realLong));
	EXPECT_EQ(*chRealLong, *f2Cstr(realLong));
}

TEST(ap_convert_tests, d2Cstr) {
    char chRealShort[] = {"0.125"};
	double realShort = 0.125;
	EXPECT_EQ(*chRealShort, *d2Cstr("%.4f", realShort));
	EXPECT_EQ(*chRealShort, *d2Cstr(realShort));
    
	char chRealLong[] = {"0.123456789123456789123456789"}; 
	double realLong = 0.123456789123456789123456789;
	EXPECT_EQ(*chRealLong, *d2Cstr("%.4f", realLong));
	EXPECT_EQ(*chRealLong, *d2Cstr(realLong));
}*/

TEST(ap_convert_tests, Str2f) {
    std::string strRealShort = "0.125";
	float realShort = 0.125;
	EXPECT_EQ(realShort, Str2f(strRealShort));
    
    std::string strRealLong = "0.123456789123456789123456789";
	float realLong = 0.123456789123456789123456789;
	EXPECT_EQ(realLong, Str2f(strRealLong));
}

TEST(ap_convert_tests, Str2d) {
    std::string strRealShort = "0.125";
	double realShort = 0.125;
	EXPECT_EQ(realShort, Str2d(strRealShort));
    
    std::string strRealLong = "0.123456789123456789123456789";
	double realLong = 0.123456789123456789123456789;
	EXPECT_EQ(realLong, Str2d(strRealLong));
}

TEST(ap_convert_tests, f2Str) {
    std::string strRealShort = "0.125";
	float realShort = 0.125;
	EXPECT_EQ(strRealShort, f2Str(realShort));
    strRealShort = "0.1250";
	EXPECT_EQ(strRealShort, f2Str("%.4f", realShort));
    
    std::string strRealLong = "0.12345679";
	float realLong = 0.123456789123456789123456789;
	EXPECT_EQ(strRealLong, f2Str(realLong));
    strRealLong = "0.1235";
	EXPECT_EQ(strRealLong, f2Str("%.4f", realLong));
}

TEST(ap_convert_tests, d2Str) {
    std::string strRealShort = "0.125";
	double realShort = 0.125;
	EXPECT_EQ(strRealShort, d2Str(realShort));
    strRealShort = "0.1250";
	EXPECT_EQ(strRealShort, d2Str("%.4f", realShort));
    
    std::string strRealLong = "0.1234567891234568";
	double realLong = 0.123456789123456789123456789;
	EXPECT_EQ(strRealLong, d2Str(realLong));
    strRealLong = "0.1235";
	EXPECT_EQ(strRealLong, d2Str("%.4f", realLong));
}

