#include <gtest/gtest.h>
#include "../compare_files.h"

#include "ap_bspline.h"

using namespace std;
using namespace ap;

void BsplineInit(B_SPLINE <double> &bs) {
    bs.P[0].x = 1.0;
	bs.P[0].y = 2.0;
    bs.P[0].z = 1.0;
  
    bs.P[1].x = 0.0;
    bs.P[1].y = 2.0;
    bs.P[1].z = 1.0;
    
    bs.P[2].x = 0.0;
    bs.P[2].y = 1.0;
    bs.P[2].z = 0.5;
    
    bs.P[3].x = 0.0;
    bs.P[3].y = 0.0;
    bs.P[3].z = 0.0;
    
	bs.P[4].x = 1.0;
	bs.P[4].y = 0.0;
    bs.P[4].z = 0.0;
 	
    bs.P[5].x = 2.0;
    bs.P[5].y = 0.0;
    bs.P[5].z = 0.0;
    
    bs.P[6].x = 2.0;
    bs.P[6].y = 1.0;
    bs.P[6].z = 0.5;
    
    bs.P[7].x = 2.0;
    bs.P[7].y = 2.0;
    bs.P[7].z = 1.0;
	
    bs.P[8].x = 1.0;
    bs.P[8].y = 2.0;
    bs.P[8].z = 1.0;

    bs.VertexesSeq(200);
}

TEST(ap_bspline_tests, bspline_vertexes) {
	B_SPLINE <double> bs(9, 2, PEACEWISE);
	BsplineInit(bs); // vertexes generated in init function
	
    ofstream out("./out/out_bspline_vertexes.xls");
    out << fixed << setprecision(6);
    bs.PrintVertexes(out);
    out.close();
    
	std::string str1, str2;
	EXPECT_EQ(0, Files2str("bspline_vertexes.xls", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_bspline_tests, bspline_length) {
	B_SPLINE <double> bs(9, 2, PEACEWISE);
	BsplineInit(bs); // vertexes generated in init function
	
	EXPECT_EQ(6.8800015506146686, bs.Length());
}

TEST(ap_bspline_tests, bspline_min_max) {
	B_SPLINE <double> bs(9, 2, PEACEWISE);
	BsplineInit(bs); // vertexes generated in init function
	
	double min, max;
	bs.PMinMax(0, min, max);
	
	EXPECT_EQ(0, min);
	EXPECT_EQ(2, max);
}

/*TEST(ap_bezier_tests, bezier_point_from_coordinate) {
    BEZIER <double> bez(4); // points -> degrees of freedom n-1
	BezierInit(bez); 		// vertexes generated in init function
	
    double x, y, z;
    
    clog << "t(X=1.4) = " << Bez.tVertex(0, 1.4) << "% coef." << endl; //X
    Bez.Vertex(Bez.tVertex(0, 1.4), X, Y, Z);
    clog << "X\t" << "Y\t" << "Z" << endl;
    clog << X << "\t" << Y << "\t" << Z << endl;
    //out << endl << X << "\t" << Y << "\t" << Z << endl;
	
	EXPECT_EQ(1.3999997455992781, x);
	EXPECT_EQ(0.047395328756320493, y);
	EXPECT_EQ(0.64772110069595612, z);
}*/
	
