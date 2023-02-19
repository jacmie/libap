#include <gtest/gtest.h>

#include "ap_vector.h"
//#include "ap_matrix.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ap;
/*
TEST(ap_basicMath_tests, VECTOR_set_size_constructor) {
	VECTOR <double> v(20);
	EXPECT_EQ(v.Size(), 20);
	EXPECT_DOUBLE_EQ(v[0], 0.0);
	EXPECT_DOUBLE_EQ(v[19], 0.0);
}

TEST(ap_basicMath_tests, VECTOR_fill_constructor) {
    VECTOR <double> v(20, 9.9);
	EXPECT_EQ(v.Size(), 20);
	EXPECT_DOUBLE_EQ(v[0], 9.9);
	EXPECT_DOUBLE_EQ(v[19], 9.9);
}

TEST(ap_basicMath_tests, VECTOR_copy_constructor) {
    VECTOR <double> w(20, 9.9);
    VECTOR <double> v(w); 
	EXPECT_EQ(v.Size(), 20);
	EXPECT_DOUBLE_EQ(v[0], 9.9);
	EXPECT_DOUBLE_EQ(v[19], 9.9);
}    	
	
//VECTOR( real xp, real yp, real zp ) 	{ x = xp;   y = yp;   z = zp;  };
    	
TEST(ap_basicMath_tests, VECTOR_copy_stdvector_constructor) {
	vector <double> w;
	w.assign(20, 9.9);
	//VECTOR <double> v(w);
}*/

TEST(ap_basicMath_tests, VECTOR_set_value) {
	VECTOR <double> v;
	v.Resize(20);
    v.Set(3.3); 
	EXPECT_EQ(v.Size(), 20);
	EXPECT_DOUBLE_EQ(v[0], 3.3);
	EXPECT_DOUBLE_EQ(v[19], 3.3);
	EXPECT_DOUBLE_EQ(v.x, 3.3);
	EXPECT_DOUBLE_EQ(v.y, 3.3);
	EXPECT_DOUBLE_EQ(v.z, 3.3);
}

TEST(ap_basicMath_tests, VECTOR_set_n_value) {

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set(5, 5.5)); //resize allowed
	EXPECT_DOUBLE_EQ(v[0], 5.5);
	EXPECT_DOUBLE_EQ(v[4], 5.5);
	EXPECT_DOUBLE_EQ(v.x, 5.5);
	EXPECT_DOUBLE_EQ(v.y, 5.5);
	EXPECT_DOUBLE_EQ(v.z, 5.5);
	
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set(3, 7.5, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set(3, 7.5, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set(3, 7.5, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set(3, 7.5, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(v[0], 7.5);
	EXPECT_DOUBLE_EQ(v[2], 7.5);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_VECTOR) {
	VECTOR <double> w;
	w.Resize(20);
    w.Set(3.3); 
	//clog << std::fixed << std::setprecision(3) << "w = " << w << endl;

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set(w)); //resize allowed
	EXPECT_EQ(v, w);
	EXPECT_DOUBLE_EQ(v.x, w.x);
	EXPECT_DOUBLE_EQ(v.y, w.y);
	EXPECT_DOUBLE_EQ(v.z, w.z);
	
	w.Assign(12, 6.6);
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set(w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set(w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set(w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set(w, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_EQ(v, w);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_std_vector) {
	vector <double> w;
	w.assign(20, 3.3);

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set(w)); //resize allowed
	EXPECT_EQ(v.data, w);
	EXPECT_DOUBLE_EQ(v.x, w[0]);
	EXPECT_DOUBLE_EQ(v.y, w[1]);
	EXPECT_DOUBLE_EQ(v.z, w[2]);
	
	w.assign(12, 6.6);
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set(w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set(w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set(w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set(w, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_EQ(v.data, w);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_array) {
	unsigned int size = 5;
	double w[] = {1.1, 2.2, 3.3, 4.4, 5.5};

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set(size, w)); //resize allowed
	EXPECT_EQ(v[0], w[0]);
	EXPECT_EQ(v[4], w[4]);
	EXPECT_DOUBLE_EQ(v.x, w[0]);
	EXPECT_DOUBLE_EQ(v.y, w[1]);
	EXPECT_DOUBLE_EQ(v.z, w[2]);
	
	double w2[] = {1.2, 2.3, 3.4};
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set(3, w2, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set(3, w2, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set(3, w2, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set(3, w2, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(v[0], w2[0]);
	EXPECT_DOUBLE_EQ(v[2], w2[2]);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_2D_values) {
	double x = 1.1;
	double y = 2.2;

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set2D(x, y)); //resize allowed
	EXPECT_DOUBLE_EQ(v[0], x);
	EXPECT_DOUBLE_EQ(v[1], y);
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);

	v.Resize(1);
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set2D(x, y, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set2D(x, y, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set2D(x, y, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set2D(x, y, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_3D_values) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set3D(x, y, z)); //resize allowed
	EXPECT_DOUBLE_EQ(v[0], x);
	EXPECT_DOUBLE_EQ(v[1], y);
	EXPECT_DOUBLE_EQ(v[2], y);
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);

	v.Resize(1);
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set3D(x, y, z, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set3D(x, y, z, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set3D(x, y, z, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set3D(x, y, z, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_4D_values) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;
	double w = 1.0;

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set4D(x, y, z, w)); //resize allowed
	EXPECT_DOUBLE_EQ(v[0], x);
	EXPECT_DOUBLE_EQ(v[1], y);
	EXPECT_DOUBLE_EQ(v[2], y);
	EXPECT_DOUBLE_EQ(v[3], w);
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);
	EXPECT_DOUBLE_EQ(v.w, w);

	v.Resize(1);
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set4D(x, y, z, w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set4D(x, y, z, w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set4D(x, y, z, w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set4D(x, y, z, w, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);
	EXPECT_DOUBLE_EQ(v.w, w);
}                                                     
    	
TEST(ap_basicMath_tests, VECTOR_length) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set3D(x, y, z);
	EXPECT_DOUBLE_EQ( v.Len(), sqrt(x*x + y*y + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_lengthXY) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set3D(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenXY(), sqrt(x*x + y*y) );
}

TEST(ap_basicMath_tests, VECTOR_lengthXZ) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set3D(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenXZ(), sqrt(x*x + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_lengthYZ) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set3D(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenYZ(), sqrt(y*y + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_square) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set3D(x, y, z);
	EXPECT_DOUBLE_EQ( v.Sq(), x*x + y*y + z*z );
}
