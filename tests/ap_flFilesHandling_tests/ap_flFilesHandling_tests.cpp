#include <gtest/gtest.h>

#include "ap_flFilesHandling.h"

#include <iostream>

using namespace std;
using namespace ap;

TEST(ap_flFilesHandling_tests, file_permissions) {
#ifndef _WIN32
    std::vector <bool> permResults;
    permResults.resize(3);
    
    EXPECT_EQ(0, CheckPermissions("../ap_substitute_tests/data/insert_1.txt", permResults) );

	EXPECT_EQ(1, permResults[0]);
	EXPECT_EQ(1, permResults[1]);
	EXPECT_EQ(1, permResults[2]);
#endif
}
    
//std::string FilePath = Browse("All files \t*.{dat,txt}\nData files \t*.dat\nText files \t*.txt", 0);
