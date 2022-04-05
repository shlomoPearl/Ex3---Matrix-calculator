#pragma once

#include <vector>
#include <string>
using namespace std;
namespace zich{
    class Matrix{

    private:
        int row;
        int column;
        vector<double> v;
    public:
        Matrix(vector<double> v,int row,int column);
        // : v(v),row(row),column(column){}
        // ~Matrix();
    
    //math operators
    Matrix operator+()const; //unary
    Matrix operator-()const; // unary
    Matrix& operator+(const Matrix& ); 
    Matrix& operator+=(double);
    Matrix& operator-(const Matrix&);
    Matrix& operator-=(double);

    //comprasion operator
    bool operator<(const Matrix& );
    bool operator<=(const Matrix& );
    bool operator>(const Matrix& );
    bool operator>=(const Matrix& );
    bool operator==(const Matrix& );
    bool operator!=(const Matrix& );

    //added operator
    Matrix& operator++(); //prefix
    Matrix& operator--(); //prefix
    Matrix operator++(int dummy); //postfix
    Matrix operator--(int dummy); //postfix

    //multiplye operator
    friend Matrix& operator*(double scalar , Matrix&);
    Matrix& operator*=(double scalar);    
    Matrix operator*(const Matrix& other);
    // Matrix& operator*=( Matrix& , Matrix&);

    //input and output operator
    friend ostream& operator<< (std::ostream& output, const Matrix&); // output
    friend std::istream& operator>> (std::istream& input , Matrix& ); // input
    };

   
    
    
}