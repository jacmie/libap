#include <gtest/gtest.h>

#include "ap_vector.h"
//#include "ap_matrix.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ap;

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
	double z = 2.3;

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set3D(x, y, z)); //resize allowed
	EXPECT_DOUBLE_EQ(v[0], x);
	EXPECT_DOUBLE_EQ(v[1], y);
	EXPECT_DOUBLE_EQ(v[2], z);
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
	double z = 2.3;
	double w = 1.0;

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set4D(x, y, z, w)); //resize allowed
	EXPECT_DOUBLE_EQ(v[0], x);
	EXPECT_DOUBLE_EQ(v[1], y);
	EXPECT_DOUBLE_EQ(v[2], z);
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
		
TEST(ap_basicMath_tests, VECTOR_normalize) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set3D(x, y, z);

	EXPECT_DOUBLE_EQ( v.Norm(), sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.x, x/sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.y, y/sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.z, z/sqrt(x*x + y*y + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_get_to_VECTOR) {
	VECTOR <double> w;
	w.Resize(20);
    w.Set(3.3); 

	VECTOR <double> v;
	EXPECT_EQ(0, w.Get(v)); //resize allowed
	EXPECT_EQ(v, w);
	EXPECT_DOUBLE_EQ(v.x, w.x);
	EXPECT_DOUBLE_EQ(v.y, w.y);
	EXPECT_DOUBLE_EQ(v.z, w.z);
	
	v.Assign(12, 6.6);
	w.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, w.Get(v, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	v.Assign(12, 6.6);
	EXPECT_EQ(1, w.Get(v, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.Assign(12, 6.6);
	w.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, w.Get(v, 0)) << "grFlag=1, rFlag=0" << std::endl;
	v.Assign(12, 6.6);
	EXPECT_EQ(0, w.Get(v, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_EQ(v, w);
}                                                     

TEST(ap_basicMath_tests, VECTOR_get_to_std_vector) {
	VECTOR <double> w;
	w.Resize(20);
    w.Set(3.3); 
	//vector <double> w;
	//w.assign(20, 3.3);

	std::vector <double> v;
	EXPECT_EQ(0, w.Get(v)); //resize allowed
	EXPECT_EQ(w.data, v);
	EXPECT_DOUBLE_EQ(w.x, v[0]);
	EXPECT_DOUBLE_EQ(w.y, v[1]);
	EXPECT_DOUBLE_EQ(w.z, v[2]);
	
	v.assign(12, 6.6);
	w.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, w.Get(v, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	v.assign(12, 6.6);
	EXPECT_EQ(1, w.Get(v, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.assign(12, 6.6);
	w.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, w.Get(v, 0)) << "grFlag=1, rFlag=0" << std::endl;
	v.assign(12, 6.6);
	EXPECT_EQ(0, w.Get(v, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_EQ(w.data, v);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_to_array) {
	unsigned int size = 5;
	double v[5];

	VECTOR <double> w;
	w.Assign(5, 5.4);
	EXPECT_EQ(0, w.Get(size, v)); //resize allowed
	EXPECT_EQ(v[0], w[0]);
	EXPECT_EQ(v[4], w[4]);
	EXPECT_DOUBLE_EQ(w.x, v[0]);
	EXPECT_DOUBLE_EQ(w.y, v[1]);
	EXPECT_DOUBLE_EQ(w.z, v[2]);
	
	double w2[] = {1.2, 2.3, 3.4};
	EXPECT_EQ(1, w.Get(3, w2)) << "grFlag=0, rFlag=0" << std::endl; 
}                                                     

TEST(ap_basicMath_tests, VECTOR_get_to_2D_values) {
	double x;
	double y;

	VECTOR <double> v;
	v.Set2D(1.1, 1.2);
	
	EXPECT_EQ(0, v.Get2D(x, y));
	EXPECT_DOUBLE_EQ(v[0], x);
	EXPECT_DOUBLE_EQ(v[1], y);
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);

	v.Resize(1);
	EXPECT_EQ(1, v.Get2D(x, y)); 
}                            

TEST(ap_basicMath_tests, VECTOR_get_to_3D_values) {
	double x;
	double y;
	double z;

	VECTOR <double> v;
	v.Set3D(1.1, 1.2, 2.3);
	std::clog << v << std::endl;
	EXPECT_EQ(0, v.Get3D(x, y, z));
	EXPECT_DOUBLE_EQ(v[0], x);
	EXPECT_DOUBLE_EQ(v[1], y);
	EXPECT_DOUBLE_EQ(v[2], z);
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);

	v.Resize(1);
	EXPECT_EQ(1, v.Get3D(x, y, z)); 
}                                                     

TEST(ap_basicMath_tests, VECTOR_get_to_4D_values) {
	double x;
	double y;
	double z;
	double w;

	VECTOR <double> v;
	v.Set4D(1.1, 1.2, 2.3, 3.3);
	std::clog << v << std::endl;
	EXPECT_EQ(0, v.Get4D(x, y, z, w));
	EXPECT_DOUBLE_EQ(v[0], x);
	EXPECT_DOUBLE_EQ(v[1], y);
	EXPECT_DOUBLE_EQ(v[2], z);
	EXPECT_DOUBLE_EQ(v[3], w);
	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);
	EXPECT_DOUBLE_EQ(v.w, w);

	v.Resize(1);
	EXPECT_EQ(1, v.Get4D(x, y, z, w)); 
}                                                     

TEST(ap_basicMath_tests, VECTOR_IsNan) {
	VECTOR <double> v;
	v.Resize(9);
	
	EXPECT_EQ(0, v.IsNan()) << v << std::endl;
}
