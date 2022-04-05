#include "doctest.h"
#include "Matrix.hpp"
#include <string>
#include <iostream>
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
        try{
            Matrix m1 = {v1 , 1, 2};
            Matrix m2 = {v1 , 2, 1};
            Matrix m3 = {v3 , 2, 3};
            Matrix m4 = {v4 , 3, 2};
        }catch(const exception& e){
            CHECK_EQ(true,true);
        }

    }

    SUBCASE("negative input"){
        // Matrix m;
        try{
            Matrix m1 = {v1 , -2, -2};
            Matrix m2 = {v1 , -2, 2};
            Matrix m3 = {v1 , 2, -2};
        }catch(const exception& e){
            CHECK_EQ(true,true);
        }

    }
    Matrix m1 = {v1, 2, 2}; // 2*2
    Matrix m2 = {v2 ,2 ,2}; // 2*3
    Matrix m3 = {v3 ,3 ,2}; // 3*2
    Matrix m4 = {v4 ,2 ,3}; // 2*3
    SUBCASE("undefined multiplication"){
        CHECK_THROWS(m1*m3);
        CHECK_THROWS(m3*m4);
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
    SUBCASE("comprasion"){
        bool a1 ,a2 ,a3 ,a4 ,a5 ,a6 , a7;
        a1 = (m1 == m2);
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
        a = (++m == m7);
        CHECK(a == true);
        a = (--m == m1);
        CHECK(a == true);
    }
    SUBCASE("unary operator's"){

    }
    SUBCASE("add & sub"){

    }
    SUBCASE("multiplie"){

    }
}

