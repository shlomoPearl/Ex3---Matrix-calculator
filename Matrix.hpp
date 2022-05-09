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
        Matrix(const vector<double>& v,int row,int column);
        Matrix(const Matrix& other); // copy constructor
        // : v(v),row(row),column(column){}
        // ~Matrix();
    
    friend void checkDefine(const Matrix& a ,const Matrix& b , bool flag);
    friend int matrixSum(const Matrix&);

    //math operators
    Matrix operator+()const; //unary
    Matrix operator-()const; // unary
    Matrix operator+(const Matrix& ); 
    Matrix& operator+=(const Matrix &); 
    Matrix operator-(const Matrix&);
    Matrix& operator-=(const Matrix&); 

    //comprasion operator
    bool operator<(const Matrix& )const;
    bool operator<=(const Matrix& )const;
    bool operator>(const Matrix& )const;
    bool operator>=(const Matrix& )const;
    bool operator==(const Matrix& )const;
    bool operator!=(const Matrix& )const;

    //added operator
    Matrix& operator++(); //prefix
    Matrix& operator--(); //prefix
    Matrix operator++(int dummy); //postfix
    Matrix operator--(int dummy); //postfix

    //multiplye operator
    friend Matrix operator*(double scalar ,const Matrix&); // left mult
    friend Matrix operator*(const Matrix& , double scalar); // right mult
    Matrix& operator*=(double scalar);    
    Matrix& operator*=(const Matrix& other);
    Matrix operator*(const Matrix& other)const;  

    //input and output operator
    friend ostream& operator<< (std::ostream& output, const Matrix&); // output
    friend std::istream& operator>> (std::istream& input , Matrix& ); // input
    };
}