#include "doctest.h"
#include "Matrix.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
using namespace zich;

vector<double> v1 = {1 ,0 ,0 ,1 };
vector<double> v2 = {0 ,1 ,1 ,0 };
vector<double> v3 = {2 ,2 ,2 ,2 ,2 ,2 };
vector<double> v4 = {2 ,2 ,2 ,2 ,2 ,2 };
vector<double> v5 = {1 ,1 ,1 ,1 };
vector<double> v6 = {2 ,1 ,1 ,0 };
vector<double> v7 = {2 ,1 ,1 ,2 };

TEST_CASE("bad input"){
    
    /*
     this sub case check error in case there is mismatch between the fields of current matrix
     - the size (row and column) does not match to numbers of values (in the vector)
     */
    SUBCASE("bad input in the constructor"){
        CHECK_THROWS(Matrix(v1,1,2));
        CHECK_THROWS(Matrix(v1,2,1));
        CHECK_THROWS(Matrix(v1,1,1));
        CHECK_THROWS(Matrix(v1,0,1));
        CHECK_THROWS(Matrix(v1,1,0));
        CHECK_THROWS(Matrix(v1,0,0));
        CHECK_THROWS(Matrix(v3,3,1));
        CHECK_THROWS(Matrix(v4,2,1));
    }

    SUBCASE("negative input"){
        CHECK_THROWS(Matrix(v1 ,-2 ,-2));
        CHECK_THROWS(Matrix(v1 ,-1 ,2));
        CHECK_THROWS(Matrix(v1 ,2 , -1));
    }
    Matrix m1 = {v1, 2, 2}; // 2*2
    Matrix m2 = {v2 ,2 ,2}; // 2*3
    Matrix m3 = {v3 ,3 ,2}; // 3*2
    Matrix m4 = {v4 ,2 ,3}; // 2*3
    SUBCASE("undefined multiplication"){
        CHECK_THROWS(m1*m3);
        CHECK_THROWS(m2*m3);
        CHECK_THROWS(m4*m2);
    }
    SUBCASE("invalid comparison"){
        // the matrix are not the same size
        bool a;
        CHECK_THROWS(a = (m1 > m3));
        CHECK_THROWS(a = (m1 < m4));
        CHECK_THROWS(a = (m4 <= m2));
        CHECK_THROWS(a = (m1 >=m3));
        CHECK_THROWS(a = (m3 == m4));
        CHECK_THROWS(a = (m4 != m2));
    }
    SUBCASE("invalid added"){
        CHECK_THROWS(m1 - m3);  // sub in case row != row but column = column
        CHECK_THROWS(m1 - m4);  // sub in case row = row but column != column
        CHECK_THROWS(m4 - m3);  // sub in case row != row and column != column
        CHECK_THROWS(m4 + m2);  // add in case row = row but column != column
        CHECK_THROWS(m1 + m3);  // add in case row != row but column = column
        CHECK_THROWS(m1 + m3);  // add in case row != row and column != column
    }
}
TEST_CASE("good input"){
    Matrix m1 = {v1, 2, 2}; // 2*2
    Matrix m2 = {v2 ,2 ,2}; // 2*3
    Matrix m3 = {v3 ,3 ,2}; // 3*2
    Matrix m4 = {v4 ,2 ,3}; // 2*3
    Matrix m5 = {v5 ,2 ,2}; // 2*3
    Matrix m6 = {v6 ,2 , 2}; // 2*3
    Matrix m7 = {v7 ,2 ,2}; // 2*3
    vector<double> minus_v1 = {-1,0,0,-1};
    vector<double> minus_v2 = {0,-1,-1,0};
    vector<double> minus_v3 = {-2,-2,-2,-2,-2,-2};
    vector<double> minus_v4 = {-2,-2,-2,-2,-2,-2};
    vector<double> minus_v5 = {-1,-1,-1,-1};
    Matrix minus_m1 = {minus_v1,2,2};
    Matrix minus_m2 = {minus_v2,2,2};
    Matrix minus_m3 = {minus_v3,3,2};
    Matrix minus_m4 = {minus_v4,2,3};
    Matrix minus_m5 = {minus_v5,2,2};
    SUBCASE("comprasion"){
        bool a1 ,a2 ,a3 ,a4 ,a5 ,a6 , a7;
        a1 = (m1 == m1);
        a2 = (m5 != m1);
        a3 = (m5 < m7);
        a4 = (m7 > m1);
        a5 = (m6 >= m2);
        a6 = (m2 <= m6);
        a7 = a1 && a2 && a3 && a4 && a5 && a6;
        CHECK(a7 == true);
    }
    SUBCASE("prefix & postfix - increament & encreament"){
        Matrix m = {v1 ,2 ,2 };
        m++; // postfix
        bool a = (m == m7);
        CHECK(a == true);
        m--; // postfix
        a = (m == m1);
        CHECK(a == true);
        a = (++m == m7); // prefix
        CHECK(a == true);
        a = (--m == m1); // prefix
        CHECK(a == true);
    }
    SUBCASE("unary operator's"){
        // + unary
        Matrix m = +m1;
        CHECK_EQ(true,m == m1);
        m = +m2;
        CHECK_EQ(true,m == m2);
        m = +m3;
        CHECK_EQ(true,m == m3);
        m = +m4;
        CHECK_EQ(true,m == m4);
        m = +m5;
        CHECK_EQ(true,m == m5);

        // -unary
        m = -m1; 
        CHECK_EQ(true,m == minus_m1);
        m = -m2;
        CHECK_EQ(true,m == minus_m2);
        m = -m3;
        CHECK_EQ(true,m == minus_m3);
        m = -m4;
        CHECK_EQ(true,m == minus_m4);
        m = -m5;
        CHECK_EQ(true,m == minus_m5);
    }
    SUBCASE("add & sub"){
        // add
        Matrix m = m1 + m2;
        CHECK_EQ(true , m5 == m);
        m = m1 + m5;
        CHECK_EQ(true, m7 == m);
        // sub
        m = m7 - m1;
        CHECK_EQ(true, m5 == m);
        m = m5 - m1;
        CHECK_EQ(true, m2 == m);
        m = m5 - m2;
        CHECK_EQ(true ,m1 == m);
    }
    SUBCASE("multiplie"){
        Matrix m = m1 * m7;
        CHECK_EQ(true, m == m7);
        m = m1 * m2;
        CHECK_EQ(true , m == m2);
        m2 *= m1;
        CHECK_EQ(true , m == m2);
        vector<double> zero = {0,0,0,0};
        Matrix z_m = Matrix(zero,2,2);
        bool z1 = (z_m ==(z_m *= m1));
        bool z2 = (z_m == (m2 * z_m));
        bool z3 = (z_m == (z_m * m6));
        bool z = z1 && z2 && z3;
        CHECK_EQ(true, z);
        vector<double> eight = {8,8,8,8,8,8,8,8,8};
        Matrix eight_m = {eight, 3,3};
        m = m3 * m4;
        CHECK_EQ(true , m == eight_m); 
        m *= m*m ; /// m^3
        vector<double> pow = {4608,4608,4608,4608,4608,4608,4608,4608,4608};
        Matrix pow_m = {pow, 3,3};
        CHECK_EQ(true , m == pow_m);
        vector<double> one = {1,1,1,1,1,1,1,1,1};
        vector<double> four = {4,4,4,4,4,4,4,4,4};
        Matrix one_m = {one, 3, 3};
        Matrix four_m = {four, 3, 3};
        double scalar = 0.5;
        four_m = scalar * four_m * scalar;
        CHECK_EQ(true, four_m == one_m);
        four_m *= 4608 ;
        CHECK_EQ(true, four_m == pow_m);
    }
    SUBCASE("input operator"){
        vector<double> identity_1 = {1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1};
        vector<double> identity_2 = {1 ,0 ,0 ,1};
        Matrix m_1 = {identity_1, 3, 3};
        Matrix m_2 = {identity_2, 2, 2};
        istringstream i_1{"[1 0 0], [0 1 0], [0 0 1]\n"};
        CHECK_NOTHROW(i_1 >> m_2);
        CHECK_EQ(true, m_1 == m_2);
        istringstream i_2{"[1 0 ]0], [0 1 0], [0 0 1]\n"};
        CHECK_THROWS(i_2 >> m_2);
        istringstream i_3{"[1 0 0], [0 1], [0 0 1]\n"}; 
        CHECK_THROWS(i_3 >> m_2);
        istringstream i_4{"[1 0 0], [0 1 0], [0 0, 1]\n"};
        CHECK_THROWS(i_4 >> m_2);
    }
    SUBCASE("output operator"){
        
    }
}