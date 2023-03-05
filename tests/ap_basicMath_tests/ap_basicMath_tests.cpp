#include <gtest/gtest.h>

#include "ap_vector.h"
#include "ap_matrix.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace ap;

TEST(ap_basicMath_tests, VECTOR_3_assign_operator) {
	VECTOR_3 <double> v;
	v.Set(2.3, 5.6, 5.4);

	VECTOR_3 <double> w = v;

	EXPECT_EQ(v, w);
}

TEST(ap_basicMath_tests, VECTOR_3_assign_operator_with_normalization) {
	VECTOR_3 <double> u;
	u.Set(2.3, 5.6, 5.4);

	VECTOR_3 <double> v = u;
	v.Norm();

	VECTOR_3 <double> w;
	w ^= u;

	EXPECT_EQ(v, w);
}

TEST(ap_basicMath_tests, VECTOR_3_set_value) {
	VECTOR_3 <double> v;
    v.Set(3.3); 
	
	EXPECT_DOUBLE_EQ(v.x, 3.3);
	EXPECT_DOUBLE_EQ(v.y, 3.3);
	EXPECT_DOUBLE_EQ(v.z, 3.3);
}

TEST(ap_basicMath_tests, VECTOR_3_set_from_3_values) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.3;

	VECTOR_3 <double> v;
	v.Set(x, y, z);

	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);
}                                                     

TEST(ap_basicMath_tests, VECTOR_3_set_from_VECTOR_3) {
	VECTOR_3 <double> w;
    w.Set(3.3); 

	VECTOR_3 <double> v;
	v.Set(w);

	EXPECT_EQ(v, w);
}                                                     

TEST(ap_basicMath_tests, VECTOR_3_set_from_std_vector) {
	vector <double> w;
	w.assign(3, 3.3);

	VECTOR_3 <double> v;
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

TEST(ap_basicMath_tests, VECTOR_3_set_from_array) {
	double u[] = {1.1};
	double v[] = {1.1, 2.2, 3.3};
	double w[] = {1.1, 2.2, 3.3, 4.4, 5.5};

	VECTOR_3 <double> t;
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

TEST(ap_basicMath_tests, VECTOR_3_get_to_3_values) {
	double x;
	double y;
	double z;

	VECTOR_3 <double> v;
	v.Set(1.1, 1.2, 2.3);
	v.Get(x, y, z);

	EXPECT_DOUBLE_EQ(v.x, x);
	EXPECT_DOUBLE_EQ(v.y, y);
	EXPECT_DOUBLE_EQ(v.z, z);
}                                                     

TEST(ap_basicMath_tests, VECTOR_3_get_to_VECTOR_3) {
	VECTOR_3 <double> w;
    w.Set(3.3); 

	VECTOR_3 <double> v;
	w.Get(v);

	EXPECT_EQ(v, w);
}                                                     

TEST(ap_basicMath_tests, VECTOR_3_get_to_std_vector) {
	VECTOR_3 <double> w;
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

TEST(ap_basicMath_tests, VECTOR_3_get_to_array) {
	double u[1];
	double v[3];
	double w[5];

	VECTOR_3 <double> t;
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

TEST(ap_basicMath_tests, VECTOR_3_length) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR_3 <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.Len(), sqrt(x*x + y*y + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_3_lengthXY) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR_3 <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenXY(), sqrt(x*x + y*y) );
}

TEST(ap_basicMath_tests, VECTOR_3_lengthXZ) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR_3 <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenXZ(), sqrt(x*x + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_3_lengthYZ) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR_3 <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.LenYZ(), sqrt(y*y + z*z) );
}

TEST(ap_basicMath_tests, VECTOR_3_square) {
	double x = 1.1;
	double y = 2.2;
	double z = 2.2;

	VECTOR_3 <double> v;
	v.Set(x, y, z);
	EXPECT_DOUBLE_EQ( v.Sq(), x*x + y*y + z*z );
}
		
TEST(ap_basicMath_tests, VECTOR_3_normalize) {
	double x = 1.1;
	double y = 2.2;
	double z = 3.3;

	VECTOR_3 <double> v;
	v.Set(x, y, z);

	EXPECT_DOUBLE_EQ( v.Norm(), sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.x, x/sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.y, y/sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( v.z, z/sqrt(x*x + y*y + z*z) );
	EXPECT_DOUBLE_EQ( 1.0, v.Len() );
}

TEST(ap_basicMath_tests, VECTOR_3_IsNan) {
	VECTOR_3 <double> v;
	
	EXPECT_EQ(0, v.IsNan()) << v << std::endl;
}
		
TEST(ap_basicMath_tests, VECTOR_3_coordinates_products) {
	VECTOR_3 <double> a;
	VECTOR_3 <double> b;
	a.Set(4.0, 4.0, 4.0);
	b.Set(1.0, 2.0, 3.0);

	VECTOR_3 <double> c = a&b;
	VECTOR_3 <double> d;
	d.Set(4.0, 8.0, 12.0);
	EXPECT_EQ(c, d);
	
	a&=b;
	EXPECT_EQ(a, d);
}

TEST(ap_basicMath_tests, VECTOR_3_dot_product) {
	VECTOR_3 <double> a;
	VECTOR_3 <double> b;
	a.Set(1.0, 2.0, 3.0);
	b.Set(1.0, 2.0, 3.0);
	
	EXPECT_DOUBLE_EQ(14, a*b);
}

TEST(ap_basicMath_tests, VECTOR_3_cross_product) {
	VECTOR_3 <double> a;
	VECTOR_3 <double> b;
	a.Set(4.0, 4.0, 4.0);
	b.Set(1.0, 2.0, 3.0);

	VECTOR_3 <double> c = a%b;
	VECTOR_3 <double> d;
	d.Set(4.0, -8.0, 4.0);
	EXPECT_EQ(c, d);
	
	a%=b;
	EXPECT_EQ(a, d);
}

TEST(ap_basicMath_tests, VECTOR_3_mult_VECTOR_3_scalar) {
 	VECTOR_3 <double> v;
	v.Set(1.1, 2.2, 4.4);
 
	VECTOR_3 <double> w = v*2.0;
	EXPECT_DOUBLE_EQ(2.2, w.x);
	EXPECT_DOUBLE_EQ(4.4, w.y);
	EXPECT_DOUBLE_EQ(8.8, w.z);

	v *= 2.0;
	EXPECT_DOUBLE_EQ(2.2, v.x);
	EXPECT_DOUBLE_EQ(4.4, v.y);
	EXPECT_DOUBLE_EQ(8.8, v.z);
}

TEST(ap_basicMath_tests, VECTOR_3_mult_scalar_VECTOR_3) {
 	VECTOR_3 <double> v;
	v.Set(1.1, 2.2, 4.4);
 
	VECTOR_3 <double> w = 2.0*v;
	EXPECT_DOUBLE_EQ(2.2, w.x);
	EXPECT_DOUBLE_EQ(4.4, w.y);
	EXPECT_DOUBLE_EQ(8.8, w.z);
}

TEST(ap_basicMath_tests, VECTOR_3_divide_VECTOR_3_with_scalar) {
 	VECTOR_3 <double> v;
	v.Set(2.2, 4.4, 8.8);
 
	VECTOR_3 <double> w = v/2.0;
	EXPECT_DOUBLE_EQ(1.1, w.x);
	EXPECT_DOUBLE_EQ(2.2, w.y);
	EXPECT_DOUBLE_EQ(4.4, w.z);

	v /= 2.0;
	EXPECT_DOUBLE_EQ(1.1, v.x);
	EXPECT_DOUBLE_EQ(2.2, v.y);
	EXPECT_DOUBLE_EQ(4.4, v.z);
}

TEST(ap_basicMath_tests, VECTOR_3_add_VECTOR_3S) {
	VECTOR_3 <double> a;
	VECTOR_3 <double> b;
	a.Set(4.0, 4.0, 4.0);
	b.Set(1.0, 2.0, 3.0);

	VECTOR_3 <double> c = a+b;
	VECTOR_3 <double> d;
	d.Set(5.0, 6.0, 7.0);
	EXPECT_EQ(c, d);

	a += b;
	EXPECT_EQ(a, d);
}

TEST(ap_basicMath_tests, VECTOR_3_substract_VECTOR_3S) {
	VECTOR_3 <double> a;
	VECTOR_3 <double> b;
	a.Set(4.0, 4.0, 4.0);
	b.Set(1.0, 2.0, 3.0);
	
	VECTOR_3 <double> c = a-b;
	VECTOR_3 <double> d;
	d.Set(3.0, 2.0, 1.0);
	EXPECT_EQ(c, d);

	a -= b;
	EXPECT_EQ(a, d);
}

TEST(ap_basicMath_tests, VECTOR_3_revers) {
	VECTOR_3 <double> a;
	VECTOR_3 <double> b;
	a.Set(1.0, 2.0, 3.0);
	b.Set(-1.0, -2.0, -3.0);

	EXPECT_EQ(-a, b);
}

TEST(ap_basicMath_tests, MATRIX_3x3_set_from_std_vector) {
	vector <double> w;
	w.assign(9, 3.3);

	MATRIX_3x3 <double> A;
	EXPECT_EQ(0, A.Set(w));
	EXPECT_DOUBLE_EQ(A.xx, w[0]);
	EXPECT_DOUBLE_EQ(A.xy, w[1]);
	EXPECT_DOUBLE_EQ(A.xz, w[2]);
	EXPECT_DOUBLE_EQ(A.yx, w[3]);
	EXPECT_DOUBLE_EQ(A.yy, w[4]);
	EXPECT_DOUBLE_EQ(A.yz, w[5]);
	EXPECT_DOUBLE_EQ(A.zx, w[6]);
	EXPECT_DOUBLE_EQ(A.zy, w[7]);
	EXPECT_DOUBLE_EQ(A.zz, w[8]);
	
	w.assign(4, 6.6);
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Set(w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Set(w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Set(w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Set(w, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, w[0]);
	EXPECT_DOUBLE_EQ(A.xy, w[1]);
	EXPECT_DOUBLE_EQ(A.yx, w[2]);
	EXPECT_DOUBLE_EQ(A.yy, w[3]);
	
	w.assign(15, 9.9);
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Set(w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Set(w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Set(w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Set(w, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, w[0]);
	EXPECT_DOUBLE_EQ(A.xy, w[1]);
	EXPECT_DOUBLE_EQ(A.xz, w[2]);
	EXPECT_DOUBLE_EQ(A.yx, w[3]);
	EXPECT_DOUBLE_EQ(A.yy, w[4]);
	EXPECT_DOUBLE_EQ(A.yz, w[5]);
	EXPECT_DOUBLE_EQ(A.zx, w[6]);
	EXPECT_DOUBLE_EQ(A.zy, w[7]);
	EXPECT_DOUBLE_EQ(A.zz, w[8]);
	
	vector <vector <double> > v;
	v.resize(3);
	for(unsigned int i=0; i<3; i++) { v[i].assign(3, i*1.1); }

	EXPECT_EQ(0, A.Set(v));
	EXPECT_DOUBLE_EQ(A.xx, v[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, v[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, v[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, v[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, v[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, v[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, v[2][2]);
	
	vector <vector <double> > v2;
	v2.resize(2);
	for(unsigned int i=0; i<2; i++)
		v2[i].assign(2, 3.3);
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Set(v2, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Set(v2, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Set(v2, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Set(v2, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, v2[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v2[0][1]);
	EXPECT_DOUBLE_EQ(A.yx, v2[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v2[1][1]);
	
	vector <vector <double> > v3;
	v3.resize(4);
	for(unsigned int i=0; i<4; i++)
		v3[i].assign(4, 4.4);
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Set(v3, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Set(v3, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Set(v3, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Set(v3, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, v3[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v3[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, v3[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, v3[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v3[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, v3[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, v3[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, v3[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, v3[2][2]);
}

TEST(ap_basicMath_tests, MATRIX_3x3_set_from_array) {
	double w[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

	MATRIX_3x3 <double> A;
	EXPECT_EQ(0, A.Set(9, w));
	EXPECT_DOUBLE_EQ(A.xx, w[0]);
	EXPECT_DOUBLE_EQ(A.xy, w[1]);
	EXPECT_DOUBLE_EQ(A.xz, w[2]);
	EXPECT_DOUBLE_EQ(A.yx, w[3]);
	EXPECT_DOUBLE_EQ(A.yy, w[4]);
	EXPECT_DOUBLE_EQ(A.yz, w[5]);
	EXPECT_DOUBLE_EQ(A.zx, w[6]);
	EXPECT_DOUBLE_EQ(A.zy, w[7]);
	EXPECT_DOUBLE_EQ(A.zz, w[8]);
	
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Set(4, w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Set(4, w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Set(4, w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Set(4, w, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, w[0]);
	EXPECT_DOUBLE_EQ(A.xy, w[1]);
	EXPECT_DOUBLE_EQ(A.yx, w[2]);
	EXPECT_DOUBLE_EQ(A.yy, w[3]);
	
	double w2[] = {1.1, 1.2, 1.3, 1.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3};
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Set(16, w2, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Set(16, w2, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Set(16, w2, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Set(16, w2, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, w2[0]);
	EXPECT_DOUBLE_EQ(A.xy, w2[1]);
	EXPECT_DOUBLE_EQ(A.xz, w2[2]);
	EXPECT_DOUBLE_EQ(A.yx, w2[3]);
	EXPECT_DOUBLE_EQ(A.yy, w2[4]);
	EXPECT_DOUBLE_EQ(A.yz, w2[5]);
	EXPECT_DOUBLE_EQ(A.zx, w2[6]);
	EXPECT_DOUBLE_EQ(A.zy, w2[7]);
	EXPECT_DOUBLE_EQ(A.zz, w2[8]);
	
	double v[3][3];
	for(unsigned int i=0; i<3; i++) {
		for(unsigned int j; j<3; j++) { v[i][j] = 1.0 + i*0.1*j; }
	}
		
	A.Set(v);
	EXPECT_DOUBLE_EQ(A.xx, v[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, v[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, v[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, v[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, v[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, v[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, v[2][2]);
}

TEST(ap_basicMath_tests, MATRIX_3x3_set_from_array_of_pointers) {
	double **v = new double* [3];
	for(unsigned int i=0; i<3; i++) {
  		v[i] = new double [3];
		for(unsigned int j; j<3; j++) { v[i][j] = 1.0 + i*0.1*j; }
	}
	
	MATRIX_3x3 <double> A;
	EXPECT_EQ(0, A.Set(3, v));
	EXPECT_DOUBLE_EQ(A.xx, v[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, v[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, v[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, v[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, v[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, v[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, v[2][2]);
	
	double **v2 = new double* [2];
	for(unsigned int i=0; i<2; i++) {
  		v2[i] = new double [2];
		for(unsigned int j; j<2; j++) { v2[i][j] = 1.0 + i*0.2*j; }
	}
	
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Set(2, v2, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Set(2, v2, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Set(2, v2, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Set(2, v2, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, v2[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v2[0][1]);
	EXPECT_DOUBLE_EQ(A.yx, v2[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v2[1][1]);
	
	double **v3 = new double* [4];
	for(unsigned int i=0; i<4; i++) {
  		v3[i] = new double [4];
		for(unsigned int j; j<4; j++) { v3[i][j] = 1.0 + i*0.3*j; }
	}
	
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Set(4, v3, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Set(4, v3, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Set(4, v3, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Set(4, v3, 1)) << "grFlag=1, rFlag=1 - size unmatched allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, v3[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v3[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, v3[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, v3[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v3[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, v3[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, v3[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, v3[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, v3[2][2]);
}

TEST(ap_basicMath_tests, MATRIX_3x3_get_to_std_vector_one_dim) {
	MATRIX_3x3 <double> A;
    A.Set(3.3); 

	std::vector <double> v;
	EXPECT_EQ(0, A.Get(v));
	EXPECT_EQ(A.xx, v[0]);
	EXPECT_EQ(A.xy, v[1]);
	EXPECT_EQ(A.xz, v[2]);
	EXPECT_EQ(A.yx, v[3]);
	EXPECT_EQ(A.yy, v[4]);
	EXPECT_EQ(A.yz, v[5]);
	EXPECT_EQ(A.zx, v[6]);
	EXPECT_EQ(A.zy, v[7]);
	EXPECT_EQ(A.zz, v[8]);
	
	v.assign(4, 6.6);
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Get(v, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Get(v, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Get(v, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Get(v, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, v[0]);
	EXPECT_DOUBLE_EQ(A.xy, v[1]);
	EXPECT_DOUBLE_EQ(A.yx, v[2]);
	EXPECT_DOUBLE_EQ(A.yy, v[3]);
	
	v.assign(16, 9.9);
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Get(v, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Get(v, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Get(v, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Get(v, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, v[0]);
	EXPECT_DOUBLE_EQ(A.xy, v[1]);
	EXPECT_DOUBLE_EQ(A.xz, v[2]);
	EXPECT_DOUBLE_EQ(A.yx, v[3]);
	EXPECT_DOUBLE_EQ(A.yy, v[4]);
	EXPECT_DOUBLE_EQ(A.yz, v[5]);
	EXPECT_DOUBLE_EQ(A.zx, v[6]);
	EXPECT_DOUBLE_EQ(A.zy, v[7]);
	EXPECT_DOUBLE_EQ(A.zz, v[8]);
}                                                     

TEST(ap_basicMath_tests, MATRIX_3x3_set_rotation_matrix) {
	MATRIX_3x3 <double> M;
	double dAng = 30;
	double rAng = dAng*M_PI/180;

	M.RotMatX(rAng);
	EXPECT_EQ(M.xx, 1);
	EXPECT_EQ(M.xy, 0);
	EXPECT_EQ(M.xz, 0);
	EXPECT_EQ(M.yx, 0);
	EXPECT_EQ(M.yy, cos(rAng));
	EXPECT_EQ(M.yz, -sin(rAng));
	EXPECT_EQ(M.zx, 0);
	EXPECT_EQ(M.zy, sin(rAng));
	EXPECT_EQ(M.zz, cos(rAng));

	M.RotMatY(rAng);
	EXPECT_EQ(M.xx, cos(rAng));
	EXPECT_EQ(M.xy, 0);
	EXPECT_EQ(M.xz, sin(rAng));
	EXPECT_EQ(M.yx, 0);
	EXPECT_EQ(M.yy, 1);
	EXPECT_EQ(M.yz, 0);
	EXPECT_EQ(M.zx, -sin(rAng));
	EXPECT_EQ(M.zy, 0);
	EXPECT_EQ(M.zz, cos(rAng));

	M.RotMatZ(rAng);
	EXPECT_EQ(M.xx, cos(rAng));
	EXPECT_EQ(M.xy, -sin(rAng));
	EXPECT_EQ(M.xz, 0);
	EXPECT_EQ(M.yx, sin(rAng));
	EXPECT_EQ(M.yy, cos(rAng));
	EXPECT_EQ(M.yz, 0);
	EXPECT_EQ(M.zx, 0);
	EXPECT_EQ(M.zy, 0);
	EXPECT_EQ(M.zz, 1);

	M.RotMatXdeg(dAng);
	EXPECT_EQ(M.xx, 1);
	EXPECT_EQ(M.xy, 0);
	EXPECT_EQ(M.xz, 0);
	EXPECT_EQ(M.yx, 0);
	EXPECT_EQ(M.yy, cos(rAng));
	EXPECT_EQ(M.yz, -sin(rAng));
	EXPECT_EQ(M.zx, 0);
	EXPECT_EQ(M.zy, sin(rAng));
	EXPECT_EQ(M.zz, cos(rAng));

	M.RotMatYdeg(dAng);
	EXPECT_EQ(M.xx, cos(rAng));
	EXPECT_EQ(M.xy, 0);
	EXPECT_EQ(M.xz, sin(rAng));
	EXPECT_EQ(M.yx, 0);
	EXPECT_EQ(M.yy, 1);
	EXPECT_EQ(M.yz, 0);
	EXPECT_EQ(M.zx, -sin(rAng));
	EXPECT_EQ(M.zy, 0);
	EXPECT_EQ(M.zz, cos(rAng));

	M.RotMatZdeg(dAng);
	EXPECT_EQ(M.xx, cos(rAng));
	EXPECT_EQ(M.xy, -sin(rAng));
	EXPECT_EQ(M.xz, 0);
	EXPECT_EQ(M.yx, sin(rAng));
	EXPECT_EQ(M.yy, cos(rAng));
	EXPECT_EQ(M.yz, 0);
	EXPECT_EQ(M.zx, 0);
	EXPECT_EQ(M.zy, 0);
	EXPECT_EQ(M.zz, 1);
}

TEST(ap_basicMath_tests, MATRIX_3x3_get_to_std_vector_two_dim) {
	MATRIX_3x3 <double> A;
    A.Set(3.3); 

	std::vector < std::vector <double> > v;
	v.resize(3);
	for(unsigned int i=0; i<v.size(); i++) { v[i].resize(3); }

	EXPECT_EQ(0, A.Get(v));
	EXPECT_EQ(A.xx, v[0][0]);
	EXPECT_EQ(A.xy, v[0][1]);
	EXPECT_EQ(A.xz, v[0][2]);
	EXPECT_EQ(A.yx, v[1][0]);
	EXPECT_EQ(A.yy, v[1][1]);
	EXPECT_EQ(A.yz, v[1][2]);
	EXPECT_EQ(A.zx, v[2][0]);
	EXPECT_EQ(A.zy, v[2][1]);
	EXPECT_EQ(A.zz, v[2][2]);
	
	std::vector < std::vector <double> > v2;
	v2.resize(2);
	for(unsigned int i=0; i<v2.size(); i++) { v2[i].resize(2); }
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Get(v2, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Get(v2, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Get(v2, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Get(v2, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, v[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v[0][1]);
	EXPECT_DOUBLE_EQ(A.yx, v[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v[1][1]);
	
	std::vector < std::vector <double> > v3;
	v3.resize(4);
	for(unsigned int i=0; i<v3.size(); i++) { v3[i].resize(4); }
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Get(v3, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Get(v3, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Get(v3, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Get(v3, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, v3[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v3[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, v3[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, v3[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v3[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, v3[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, v3[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, v3[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, v3[2][2]);
}                                                     

TEST(ap_basicMath_tests, MATRIX_3x3_get_to_array_one_dim) {
	double u[4];
	double v[9];
	double w[16];

	MATRIX_3x3 <double> A;
	A.Set(5.4);
	EXPECT_EQ(0, A.Get(9, v));
	EXPECT_DOUBLE_EQ(A.xx, v[0]);
	EXPECT_DOUBLE_EQ(A.xy, v[1]);
	EXPECT_DOUBLE_EQ(A.xz, v[2]);
	EXPECT_DOUBLE_EQ(A.yx, v[3]);
	EXPECT_DOUBLE_EQ(A.yy, v[4]);
	EXPECT_DOUBLE_EQ(A.yz, v[5]);
	EXPECT_DOUBLE_EQ(A.zx, v[6]);
	EXPECT_DOUBLE_EQ(A.zy, v[7]);
	EXPECT_DOUBLE_EQ(A.zz, v[8]);
	
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Get(4, u, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Get(4, u, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Get(4, u, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Get(4, u, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, u[0]);
	EXPECT_DOUBLE_EQ(A.xy, u[1]);
	EXPECT_DOUBLE_EQ(A.yx, u[2]);
	EXPECT_DOUBLE_EQ(A.yy, u[3]);
	
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Get(16, w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Get(16, w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Get(16, w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Get(16, w, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, w[0]);
	EXPECT_DOUBLE_EQ(A.xy, w[1]);
	EXPECT_DOUBLE_EQ(A.xz, w[2]);
	EXPECT_DOUBLE_EQ(A.yx, w[3]);
	EXPECT_DOUBLE_EQ(A.yy, w[4]);
	EXPECT_DOUBLE_EQ(A.yz, w[5]);
	EXPECT_DOUBLE_EQ(A.zx, w[6]);
	EXPECT_DOUBLE_EQ(A.zy, w[7]);
	EXPECT_DOUBLE_EQ(A.zz, w[8]);
}                                                     

TEST(ap_basicMath_tests, MATRIX_3x3_get_to_array_fixed_two_dim) {
	double v[3][3];

	MATRIX_3x3 <double> A(5.4);
	A.Get(v);
	EXPECT_DOUBLE_EQ(A.xx, v[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, v[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, v[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, v[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, v[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, v[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, v[2][2]);
}                                                     

TEST(ap_basicMath_tests, MATRIX_3x3_get_to_array_two_dim) {
	double **u = new double* [2];
	for(unsigned int i=0; i<2; i++) {
  		u[i] = new double [2];
	}
	
	double **v = new double* [3];
	for(unsigned int i=0; i<3; i++) {
  		v[i] = new double [3];
	}
	
	double **w = new double* [3];
	for(unsigned int i=0; i<3; i++) {
  		w[i] = new double [3];
	}

	MATRIX_3x3 <double> A;
	A.Set(5.4);
	EXPECT_EQ(0, A.Get(3, v));
	EXPECT_DOUBLE_EQ(A.xx, v[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, v[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, v[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, v[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, v[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, v[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, v[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, v[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, v[2][2]);
	
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Get(2, u, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Get(2, u, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Get(2, u, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Get(2, u, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, u[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, u[0][1]);
	EXPECT_DOUBLE_EQ(A.yx, u[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, u[1][1]);
	
	A.SetGolobalResizeFlag(0);                
	EXPECT_EQ(1, A.Get(4, w, 0)) << "grFlag=0, rFlag=0" << std::endl; 
	EXPECT_EQ(1, A.Get(4, w, 1)) << "grFlag=0, rFlag=1" << std::endl;
	A.SetGolobalResizeFlag(1);                
	EXPECT_EQ(1, A.Get(4, w, 0)) << "grFlag=1, rFlag=0" << std::endl;
	EXPECT_EQ(0, A.Get(4, w, 1)) << "grFlag=1, rFlag=1 - resize allowed" << std::endl;
	EXPECT_DOUBLE_EQ(A.xx, w[0][0]);
	EXPECT_DOUBLE_EQ(A.xy, w[0][1]);
	EXPECT_DOUBLE_EQ(A.xz, w[0][2]);
	EXPECT_DOUBLE_EQ(A.yx, w[1][0]);
	EXPECT_DOUBLE_EQ(A.yy, w[1][1]);
	EXPECT_DOUBLE_EQ(A.yz, w[1][2]);
	EXPECT_DOUBLE_EQ(A.zx, w[2][0]);
	EXPECT_DOUBLE_EQ(A.zy, w[2][1]);
	EXPECT_DOUBLE_EQ(A.zz, w[2][2]);
}                                                     

TEST(ap_basicMath_tests, MATRIX_3x3_determinant) {
	MATRIX_3x3 <double> A(4.6);
	double val = 4.6*4.6*4.6 * 3;

	EXPECT_DOUBLE_EQ(A.Det(), val);
}
