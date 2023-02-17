#include <gtest/gtest.h>

#include "ap_discretization.h"

#include <iostream>
#include <fstream>

using namespace std;
/*
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}*/

TEST(ap_discretizationTest, BasicAssertions) {
	// Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);

	clog << endl << "*** JMdiscretization ***" << endl << endl;

	ofstream out("ap_discretization.xls");

	vector <double> Distro;
	Discretization <double> (40, 2.0, Distro, 1, 7);
	
	for(unsigned int i=0; i<Distro.size(); i++)
	{
		clog << i << "\t" << fixed << setprecision(4) << Distro[i] << endl;
		out << fixed << setprecision(4) << Distro[i] << "\t" << 1 << endl;
	}
	
	out.close();
}
