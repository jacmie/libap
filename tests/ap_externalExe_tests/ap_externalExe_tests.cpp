#include <gtest/gtest.h>
#include "../compare_files.h"

#include "ap_externalExe.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ap;

TEST(ap_externalExe_tests, pipe) {
	
#ifdef _WIN32
	Pipe((char *)"TestDir\\JMxfoil\\Xfoil.exe", (char *)"", (char *)"TestDir\\JMexternalExe\\Xfoil.log", (char *)"NACA0012\nquit\n", (char *)"w");
#elif __linux__  // no Xfoil for MacOS, to do
	Pipe((char*)"../ap_xfoil_tests/bin/linux/Xfoil", (char *)"", (char *)"./out/out_xfoil.log", (char *)"NACA0012\nquit\n", (char *)"w");
#endif
	
	std::string str1, str2;
	EXPECT_EQ(0, Files2str("xfoil.log", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_externalExe_tests, execute_binary) {
	std::vector <std::string> arg;
	
#ifdef _WIN32
    arg.push_back("../../build/tests/Release/sq.exe"); 
#else
    arg.push_back("../../build/tests/sq"); 
#endif
	
	arg.push_back("2.3");
	arg.push_back("4.1");
	EXPECT_EQ(0, ExeCreateProcess(arg)) << "Change path if 'build' is not in the CMAKE_CURRENT_SOURCE_DIR";
}

TEST(ap_externalExe_tests, execute_script) {
	std::vector <std::string> arg;
	
#ifdef _WIN32
	arg.push_back("./bin/sq.cmd");	    				// Local directory, doesn't support home dir: '~' !!!
#else
	arg.push_back("sh");    							// Global direcotry
	arg.push_back("./bin/sq.sh");	    				// Local directory, doesn't support home dir: '~' !!!
#endif

	arg.push_back("2.3");
	arg.push_back("4.1");
	EXPECT_EQ(0, ExeCreateProcess(arg)) << "Change path in sript if 'build' is not in the CMAKE_CURRENT_SOURCE_DIR";
}

