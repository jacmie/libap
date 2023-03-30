#include <gtest/gtest.h>
#include "../compare_files.h"

#include "ap_discretization.h"

using namespace std;
using namespace ap;

TEST(ap_discretization_tests, sin_function_discretization) {
	vector <double> distro;
	distro.resize(20);

	Discretization(distro.size(), 2, 0.8, 3.0, &distro[0]);
	
	ofstream out("./out/out_discretization_sin.xls");
	for(unsigned int i=0; i<distro.size(); i++) {
		out << fixed << setprecision(4) << distro[i] << "\t" << 1 << endl;
	}
	
	out.close();
	
	std::string str1, str2;
	EXPECT_EQ(0, Files2str("discretization_sin.xls", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_discretization_tests, exp_function_discretization) {
	vector <double> distro;
	EXPECT_EQ(0, Discretization <double> (40, 2.0, distro, 1, 7));
	
	ofstream out("./out/out_discretization_exp.xls");
	for(unsigned int i=0; i<distro.size(); i++) {
		out << fixed << setprecision(4) << distro[i] << "\t" << 1 << endl;
	}
	
	out.close();
	
	std::string str1, str2;
	EXPECT_EQ(0, Files2str("discretization_exp.xls", str1, str2));
	EXPECT_EQ(str1, str2);
}
