#include <gtest/gtest.h>
#include "../compare_files.h"

#include <string>

#include "ap_bezier.h"

using namespace std;
using namespace ap;

void BezierInit(BEZIER <double> &bez) {
    bez.P[0].x = 0.0;
	bez.P[0].y = 1.0;
    bez.P[0].z = 0.0;
  
    bez.P[1].x = 2;
    bez.P[1].y = 1;
    bez.P[1].z = 0.5;
    
    bez.P[2].x = 0;
    bez.P[2].y = 0.0;
    bez.P[2].z = 1;
    
    bez.P[3].x = 2;
    bez.P[3].y = 0;
    bez.P[3].z = 0.5;
    
	int u = 30; // number of vertex on spline
    bez.VertexesSeq(u);
}

TEST(ap_bezier_tests, bezier_vertexes) {
    BEZIER <double> bez(4); // points -> degrees of freedom n-1
	BezierInit(bez); 		// vertexes generated in init function
	
    ofstream out("./out/out_bezier_vertexes.xls");
    out << fixed << setprecision(6);
	bez.PrintPoles(out);
    bez.PrintVertexes(out);
    out.close();
    
	std::string str1, str2;
	EXPECT_EQ(0, Files2str("bezier_vertexes.xls", str1, str2));
	EXPECT_EQ(str1, str2);
}

TEST(ap_bezier_tests, bezier_length) {
    BEZIER <double> bez(4); // points -> degrees of freedom n-1
	BezierInit(bez); 		// vertexes generated in init function
	
	EXPECT_EQ(2.7610495626308023, bez.Length());
}

TEST(ap_bezier_tests, bezier_min_max) {
    BEZIER <double> bez(4); // points -> degrees of freedom n-1
	BezierInit(bez); 		// vertexes generated in init function
	
	double min, max;
	bez.PMinMax(0, min, max);
	
	EXPECT_EQ(0, min);
	EXPECT_EQ(2, max);
}

TEST(ap_bezier_tests, bezier_point_from_coordinate) {
    BEZIER <double> bez(4); // points -> degrees of freedom n-1
	BezierInit(bez); 		// vertexes generated in init function
	
    double x, y, z;
    
    clog << "t(X=1.4) = " << bez.tVertex(0, 1.4) << "% coef." << endl; //X
    bez.Vertex(bez.tVertex(0, 1.4), x, y, z);
	
	EXPECT_EQ(1.3999997455992781, x);
	EXPECT_EQ(0.047395328756320493, y);
	EXPECT_EQ(0.64772110069595612, z);
}
