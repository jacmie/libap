#include <gtest/gtest.h>

#include "ap_filter.h"

using namespace ap;

TEST(ap_filter_tests, filter) {
	double P[10];
    
    P[0] = -0.00693;
    P[1] = 0.00248;	
    P[2] = 0.00436;	
    P[3] = 0.00401;
    P[4] = 0.00644;	
    P[5] = 0.00793;
    P[6] = 0.00315;	
    P[7] = 0.00753;
    P[8] = 0.00729;	
    P[9] = 0.01088;
	
	FILTER Filt(10, 7, 1);
	Filt.FilterRange(0, P, 0);

	EXPECT_EQ(-0.00081837467504308346,	Filt.xFiltered[0]);
	EXPECT_EQ(0.00096449454474985849,	Filt.xFiltered[1]);
	EXPECT_EQ(0.0028067297948817381,	Filt.xFiltered[2]);
	EXPECT_EQ(0.0044699521087124827,	Filt.xFiltered[3]);
	EXPECT_EQ(0.005463089510961255,		Filt.xFiltered[4]);
	EXPECT_EQ(0.0058979200038444639,	Filt.xFiltered[5]);
	EXPECT_EQ(0.0063478813581595416, 	Filt.xFiltered[6]);
	EXPECT_EQ(0.0069518210459382692,	Filt.xFiltered[7]);
	EXPECT_EQ(0.0076755120719470141,	Filt.xFiltered[8]);
	EXPECT_EQ(0.0085314844148224617,	Filt.xFiltered[9]);
}
