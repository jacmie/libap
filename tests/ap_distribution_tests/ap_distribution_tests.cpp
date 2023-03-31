#include <gtest/gtest.h>
#include "../compare_files.h"

#include "ap_distribution.h"

using namespace std;
using namespace ap;

TEST(ap_distribution_tests, sin_function_distribution) {
	vector <double> distro;
	distro.resize(20);

	sinDistribution <double> (distro.size(), 0.8, distro, RIGHT, 3.0);
	
	ofstream out("./out/out_distribution_sin.xls");
	for(unsigned int i=0; i<distro.size(); i++) {
		out << fixed << setprecision(4) << distro[i] << "\t" << 1 << endl;
	}
	
	out.close();
	
	std::string str1, str2;
	EXPECT_EQ(0, Files2str("distribution_sin.xls", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_distribution_tests, exp_function_distribution) {
	vector <double> distro;
	distro.resize(40);

	EXPECT_EQ(0, expDistribution <double> (distro.size(), 2.0, distro, CENTER, 7.0));
	
	ofstream out("./out/out_distribution_exp.xls");
	for(unsigned int i=0; i<distro.size(); i++) {
		out << fixed << setprecision(4) << distro[i] << "\t" << 1 << endl;
	}
	
	out.close();
	
	std::string str1, str2;
	EXPECT_EQ(0, Files2str("distribution_exp.xls", str1, str2));
	EXPECT_EQ(str1, str2);
}
