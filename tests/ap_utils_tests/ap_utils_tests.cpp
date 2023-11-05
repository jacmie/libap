#include <gtest/gtest.h>

#include "ap_utils.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ap;

TEST(ap_utils_tests, iequals) {
	EXPECT_EQ(true, iequals("Casenonsensitive", "caseNonSensitive") );
	EXPECT_EQ(false, iequals("Casenonsensitive", "caseSensitive") );
}

TEST(ap_utils_tests, split) {
    auto vector = split("The.string.to.split", '.');

	EXPECT_EQ(vector[0], "The");
	EXPECT_EQ(vector[1], "string");
	EXPECT_EQ(vector[2], "to");
	EXPECT_EQ(vector[3], "split");
}

