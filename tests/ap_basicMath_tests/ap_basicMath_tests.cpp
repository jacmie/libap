#include <gtest/gtest.h>

#include "ap_vector.h"
//#include "ap_matrix.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ap;

TEST(ap_basicMath_tests, VECTOR_assign_operator) {
	VECTOR <double> v;
	v.Set(2.3, 5.6, 5.4);

	VECTOR <double> w = v;

	EXPECT_EQ(v, w);
}

TEST(ap_basicMath_tests, VECTOR_assign_operator_with_normalization) {
	VECTOR <double> u;
	u.Set(2.3, 5.6, 5.4);

	VECTOR <double> v = u;
	v.Norm();

	VECTOR <double> w;
	w ^= u;

	EXPECT_EQ(v, w);
}

TEST(ap_basicMath_tests, VECTOR_set_value) {
	VECTOR <double> v;
    v.Set(3.3); 
	
	EXPECT_DOUBLE_EQ(v.x, 3.3);
	EXPECT_DOUBLE_EQ(v.y, 3.3);
	EXPECT_DOUBLE_EQ(v.z, 3.3);
}

TEST(ap_basicMath_tests, VECTOR_set_from_3_values) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.3;

	VECTOR <double> v;
	v.Set(x, y, z);

	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_VECTOR) {
	VECTOR <double> w;
    w.Set(3.3); 

	VECTOR <double> v;
	v.Set(w);

	EXPECT_EQ(v, w);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_std_vector) {
	vector <double> w;
	w.assign(3, 3.3);

	VECTOR <double> v;
	EXPECT_EQ(0, v.Set(w));
	EXPECT_DOUBLE_EQ(v.x, w[0]);
	EXPECT_DOUBLE_EQ(v.y, w[1]);
	EXPECT_DOUBLE_EQ(v.z, w[2]);
	
	w.assign(1, 6.6);
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set(w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set(w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set(w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set(w, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(v.x, w[0]);
	
	w.assign(5, 9.9);
	v.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, v.Set(w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, v.Set(w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, v.Set(w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, v.Set(w, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(v.x, w[0]);
	EXPECT_DOUBLE_EQ(v.y, w[1]);
	EXPECT_DOUBLE_EQ(v.z, w[2]);
}                                                     

TEST(ap_basicMath_tests, VECTOR_set_from_array) {
	double u[] = {1.1};
	double v[] = {1.1, 2.2, 3.3};
	double w[] = {1.1, 2.2, 3.3, 4.4, 5.5};

	VECTOR <double> t;
	EXPECT_EQ(0, t.Set(3, v));
	EXPECT_DOUBLE_EQ(t.x, v[0]);
	EXPECT_DOUBLE_EQ(t.y, v[1]);
	EXPECT_DOUBLE_EQ(t.z, v[2]);
	
	t.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, t.Set(2, u, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, t.Set(2, u, 1)) << "grFlag=0, rFlag=1" << std::endl;
	t.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, t.Set(2, u, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, t.Set(2, u, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(t.x, u[0]);
	
	t.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, t.Set(5, w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, t.Set(5, w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	t.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, t.Set(5, w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, t.Set(5, w, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(t.x, w[0]);
	EXPECT_DOUBLE_EQ(t.y, w[1]);
	EXPECT_DOUBLE_EQ(t.z, w[2]);
}                                                     

TEST(ap_basicMath_tests, VECTOR_get_to_3_values) {
	double x;
	double y;
	double z;

	VECTOR <double> v;
	v.Set(1.1, 1.2, 2.3);
	v.Get(x, y, z);

	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);
}                                                     

TEST(ap_basicMath_tests, VECTOR_get_to_VECTOR) {
	VECTOR <double> w;
    w.Set(3.3); 

	VECTOR <double> v;
	w.Get(v);

	EXPECT_EQ(v, w);
}                                                     

TEST(ap_basicMath_tests, VECTOR_get_to_std_vector) {
	VECTOR <double> w;
    w.Set(3.3); 

	std::vector <double> v;
	EXPECT_EQ(0, w.Get(v));
	EXPECT_EQ(w.x, v[0]);
	EXPECT_EQ(w.y, v[1]);
	EXPECT_EQ(w.z, v[2]);
	
	v.assign(1, 6.6);
	w.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, w.Get(v, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	v.assign(1, 6.6);
	EXPECT_EQ(1, w.Get(v, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.assign(1, 6.6);
	w.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, w.Get(v, 0)) << "grFlag=1, rFlag=0" << std::endl;
	v.assign(1, 6.6);
	EXPECT_EQ(0, w.Get(v, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(w.x, v[0]);
	EXPECT_DOUBLE_EQ(w.y, v[1]);
	EXPECT_DOUBLE_EQ(w.z, v[2]);
	
	v.assign(5, 9.9);
	w.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, w.Get(v, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	v.assign(5, 9.9);
	EXPECT_EQ(1, w.Get(v, 1)) << "grFlag=0, rFlag=1" << std::endl;
	v.assign(5, 9.9);
	w.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, w.Get(v, 0)) << "grFlag=1, rFlag=0" << std::endl;
	v.assign(5, 9.9);
	EXPECT_EQ(0, w.Get(v, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(w.x, v[0]);
	EXPECT_DOUBLE_EQ(w.y, v[1]);
	EXPECT_DOUBLE_EQ(w.z, v[2]);
}                                                     

TEST(ap_basicMath_tests, VECTOR_get_to_array) {
	double u[1];
	double v[3];
	double w[5];

	VECTOR <double> t;
	t.Set(5.4);
	EXPECT_EQ(0, t.Get(3, v));
	EXPECT_DOUBLE_EQ(t.x, v[0]);
	EXPECT_DOUBLE_EQ(t.y, v[1]);
	EXPECT_DOUBLE_EQ(t.z, v[2]);
	
	t.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, t.Get(1, u, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, t.Get(1, u, 1)) << "grFlag=0, rFlag=1" << std::endl;
	t.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, t.Get(1, u, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, t.Get(1, u, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(t.x, u[0]);
	
	t.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, t.Get(5, w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, t.Get(5, w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	t.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, t.Get(5, w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, t.Get(5, w, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(t.x, w[0]);
	EXPECT_DOUBLE_EQ(t.y, w[1]);
	EXPECT_DOUBLE_EQ(t.z, w[2]);
}                                                     

TEST(ap_basicMath_tests, VECTOR_length) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.Len(), sqrt(x*x + y*y + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_lengthXY) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenXY(), sqrt(x*x + y*y) );
}

TEST(ap_basicMath_tests, VECTOR_lengthXZ) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenXZ(), sqrt(x*x + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_lengthYZ) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenYZ(), sqrt(y*y + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_square) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.Sq(), x*x + y*y + z*z );
}
		
TEST(ap_basicMath_tests, VECTOR_normalize) {
	double x = 1.1;
	double y = 2.2;
	double z = 3.3;

	VECTOR <double> v;
	v.Set(x, y, z);

	EXPECT_DOUBLE_EQ( v.Norm(), sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.x, x/sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.y, y/sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.z, z/sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( 1.0, v.Len() );
}

TEST(ap_basicMath_tests, VECTOR_IsNan) {
	VECTOR <double> v;
	
	EXPECT_EQ(0, v.IsNan()) << v << std::endl;
}
		
TEST(ap_basicMath_tests, VECTOR_coordinates_products) {
	VECTOR <double> a;
	VECTOR <double> b;
	a.Set(4.0, 4.0, 4.0);
	b.Set(1.0, 2.0, 3.0);

	VECTOR <double> c = a&b;
	VECTOR <double> d;
	d.Set(4.0, 8.0, 12.0);
	EXPECT_EQ(c, d);
	
	a&=b;
	EXPECT_EQ(a, d);
}

TEST(ap_basicMath_tests, VECTOR_dot_product) {
	VECTOR <double> a;
	VECTOR <double> b;
	a.Set(1.0, 2.0, 3.0);
	b.Set(1.0, 2.0, 3.0);
	
	EXPECT_DOUBLE_EQ(14, a*b);
}

TEST(ap_basicMath_tests, VECTOR_cross_product) {
	VECTOR <double> a;
	VECTOR <double> b;
	a.Set(4.0, 4.0, 4.0);
	b.Set(1.0, 2.0, 3.0);

	VECTOR <double> c = a%b;
	VECTOR <double> d;
	d.Set(4.0, -8.0, 4.0);
	EXPECT_EQ(c, d);
	
	a%=b;
	EXPECT_EQ(a, d);
}

TEST(ap_basicMath_tests, VECTOR_mult_VECTOR_scalar) {
 	VECTOR <double> v;
	v.Set(1.1, 2.2, 4.4);
 
	VECTOR <double> w = v*2.0;
	EXPECT_DOUBLE_EQ(2.2, w.x);
	EXPECT_DOUBLE_EQ(4.4, w.y);
	EXPECT_DOUBLE_EQ(8.8, w.z);

	v *= 2.0;
	EXPECT_DOUBLE_EQ(2.2, v.x);
	EXPECT_DOUBLE_EQ(4.4, v.y);
	EXPECT_DOUBLE_EQ(8.8, v.z);
}

TEST(ap_basicMath_tests, VECTOR_mult_scalar_VECTOR) {
 	VECTOR <double> v;
	v.Set(1.1, 2.2, 4.4);
 
	VECTOR <double> w = 2.0*v;
	EXPECT_DOUBLE_EQ(2.2, w.x);
	EXPECT_DOUBLE_EQ(4.4, w.y);
	EXPECT_DOUBLE_EQ(8.8, w.z);
}

TEST(ap_basicMath_tests, VECTOR_divide_VECTOR_with_scalar) {
 	VECTOR <double> v;
	v.Set(2.2, 4.4, 8.8);
 
	VECTOR <double> w = v/2.0;
	EXPECT_DOUBLE_EQ(1.1, w.x);
	EXPECT_DOUBLE_EQ(2.2, w.y);
	EXPECT_DOUBLE_EQ(4.4, w.z);

	v /= 2.0;
	EXPECT_DOUBLE_EQ(1.1, v.x);
	EXPECT_DOUBLE_EQ(2.2, v.y);
	EXPECT_DOUBLE_EQ(4.4, v.z);
}

TEST(ap_basicMath_tests, VECTOR_add_VECTORS) {
	VECTOR <double> a;
	VECTOR <double> b;
	a.Set(4.0, 4.0, 4.0);
	b.Set(1.0, 2.0, 3.0);

	VECTOR <double> c = a+b;
	VECTOR <double> d;
	d.Set(5.0, 6.0, 7.0);
	EXPECT_EQ(c, d);

	a += b;
	EXPECT_EQ(a, d);
}

TEST(ap_basicMath_tests, VECTOR_substract_VECTORS) {
	VECTOR <double> a;
	VECTOR <double> b;
	a.Set(4.0, 4.0, 4.0);
	b.Set(1.0, 2.0, 3.0);
	
	VECTOR <double> c = a-b;
	VECTOR <double> d;
	d.Set(3.0, 2.0, 1.0);
	EXPECT_EQ(c, d);

	a -= b;
	EXPECT_EQ(a, d);
}

TEST(ap_basicMath_tests, VECTOR_revers) {
	VECTOR <double> a;
	VECTOR <double> b;
	a.Set(1.0, 2.0, 3.0);
	b.Set(-1.0, -2.0, -3.0);

	EXPECT_EQ(-a, b);
}

