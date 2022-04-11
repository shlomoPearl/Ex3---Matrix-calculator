#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Matrix.hpp"
#include <stdexcept>
using namespace std;
namespace zich{
    Matrix::Matrix(vector<double> vec , int row, int column){
        if(row < 0 || column < 0 || row * column != vec.size()){
            throw("there is mismatch between the size and the number of element");
        }
        this->v = vec;
        this->row = row;
        this->column = column;
    }
    // copy constructor
    Matrix::Matrix(const Matrix& other){
        this->v = other.v;
        this->row = other.row;
        this->column = other.column;
    }
    /*
    this func get two marix and check if mult is defined on them
    */
    void checkDefine(const Matrix& a ,const Matrix& b , bool flag){
        if(flag){
            if (a.column != b.row){ 
                throw("mult is undefined");
            }
        }else{
            if(a.column != b.column || a.row != b.row){
                throw("add or sub is undefined");
            }
        }
    }
    int matrixSum(const Matrix& mat){
        int sum = 0;
        for (uint i = 0; i < mat.v.size(); i++){
            sum += mat.v.at(i);
        }
        return sum;
    }

    // #### math operators ####
    // unary
    Matrix Matrix::operator+()const{
        return Matrix(*this);
    }
    // unary
    Matrix Matrix::operator-()const{
        Matrix copy = Matrix(*this);
        // change all values to minus
        for (uint i = 0; i < copy.v.size(); i++){
            if (copy.v.at(i) == 0){
                copy.v.at(i) = 0;
            } else {
            copy.v.at(i) *= -1;
            }
        }
        return copy;
    } 

    Matrix Matrix::operator+(const Matrix& other){
        checkDefine(*this , other, false);
        Matrix copy = Matrix(*this);
        for (uint i = 0; i < copy.v.size(); i++){
            copy.v.at(i) += other.v.at(i);
        }
        return copy;
        
    }
    Matrix& Matrix::operator+=(const Matrix& other){
        checkDefine(*this, other, false); //in case its on matrix
        // for (uint i = 0; i < this->v.size(); i++){
        //     // this->v.at(i) += scalar;
        // }
        *this = *this + other;
        return *this;
        
    }
    Matrix Matrix::operator-(const Matrix& other){
        checkDefine(*this, other, false);
        Matrix copy = Matrix(*this);
        for (uint i = 0; i < copy.v.size(); i++){
            copy.v.at(i) -= other.v.at(i);
        }
        return copy;
    }
    //need to check if it on matrix or scalar
    Matrix& Matrix::operator-=(const Matrix& other){
        checkDefine(*this, other, false); //in case its on matrix
        // for (uint i = 0; i < this->v.size(); i++){
        //     this->v.at(i) -= scalar;
        // }
        *this = *this - other;
        return *this;
    }

    //comprasion operator
    bool Matrix::operator<(const Matrix& other)const{
        checkDefine(*this , other, false);
        return (matrixSum(*this) < matrixSum(other)) ? true : false;
    }

    bool Matrix::operator>(const Matrix& other)const{
        checkDefine(*this , other , false);
        return (matrixSum(*this) > matrixSum(other)) ? true : false;
    }
    bool Matrix::operator<=(const Matrix& other)const{
        checkDefine(*this , other, false);
        return (matrixSum(*this) <= matrixSum(other)) ? true : false;
    }
    bool Matrix::operator>=(const Matrix& other)const{
        checkDefine(*this , other , false);
        return (matrixSum(*this) >= matrixSum(other)) ? true : false;
    }
    bool Matrix::operator==(const Matrix& other)const{
        checkDefine(*this , other, false);
        bool eq = true;
        for (uint i = 0; i < this->v.size(); i++){
            if (this->v.at(i) != other.v.at(i)){
                eq = false;
            }
        }
        return eq;
    }
    bool Matrix::operator!=(const Matrix& other)const{
        checkDefine(*this , other, false);
        return !(*this == other);
    }

    //added operator
    // prefix
    Matrix& Matrix::operator++(){
        for (uint i = 0; i < this->v.size() ; i++){
            this->v.at(i)++;
        }
        return *this;
    } 
    // prefix  
    Matrix& Matrix::operator--(){
        for (uint i = 0; i < this->v.size() ; i++){
            this->v.at(i)--;
        }
        return *this;
    }   
    // postfix
    Matrix Matrix::operator++(int dummy){ 
        Matrix copy = *this;
        for (uint i = 0; i < copy.v.size(); i++){
            this->v.at(i) ++;
        }
        return copy;       
    }   
    // postfix
    Matrix Matrix::operator--(int dummy){
        Matrix copy = *this;
        for (uint i = 0; i < copy.v.size(); i++){
            this->v.at(i) --;
        }
        return copy;
    }   

    // #### multiplye operator ####
    // left mult
    Matrix operator*(double scalar,const Matrix& mat){
        vector<double> copy (mat.v.size());
        for (uint i = 0; i < mat.v.size(); i++){
            copy.at(i) = mat.v.at(i) * scalar;
        }
        return Matrix(copy, mat.row, mat.column);
    }
    Matrix operator*(const Matrix& mat, double scalar){
        return scalar*mat;
    }
    Matrix& Matrix::operator*=(double scalar){
        for (uint i = 0; i < this->v.size(); i++){
            this->v.at(i) *= scalar;
        }
        return *this;
    }
    Matrix Matrix::operator*(const Matrix& other)const{
        checkDefine(*this , other, true);
        Matrix copy = Matrix(vector<double>(uint(this->row * other.column), 0),this->row,other.column);
        uint p = 0;
        uint row = 0;
        uint joint = (uint)other.row; // length of column and row
        while (p < copy.v.size()) {
            uint column = 0;
            while (column < other.column) {// column of other{
                uint row_index = 0;
                uint column_index = 0;
                while (row_index < joint) {
                    copy.v.at(p) += this->v.at(row_index + row) * other.v.at(column_index + column);
                    row_index++;
                    column_index += (uint)other.column; // column of other
                }
                column++;
                p++;
            }
            row += joint;
        }

        return copy;
    }
    Matrix& Matrix::operator*=(const Matrix& other){
        checkDefine(*this , other, true);
        *this = *this * other;
        return *this;
    }
    //input and output operator
    ostream& operator<< (ostream& output, const Matrix& c){
        string out = "";
        uint i = 1;
        if (c.row == 1){
            out += '[';
            ostringstream s;
            for (uint i = 0; i < c.column - 1; i++){
                s << c.v.at(i);
                out += s.str();
                out += ' ';
                
            }
            s << c.v.at((uint)c.column -1);
            out += s.str();
            out += ']';
            return output << out;
        }
        if (c.column ==1){
            for(uint i = 0; i < c.row - 1; i++){
                out += '[';
                ostringstream s;
                s << c.v.at(i);
                out += s.str();
                out += ']';
                out += '\n';
            }
            out += '[';
            ostringstream s;
            s << c.v.at(i);
            out += s.str();
            out += ']';
            return output << out;
        }
        
        while (i <= c.v.size()){
            if (i % (uint)c.column != 0){
                if( i % (uint)c.column == 1){
                    out += '[';
                }
                ostringstream s;
                s << c.v.at(i -1);
                out += s.str();
                out += ' ';
            }else{
                ostringstream s;
                s << c.v.at(i -1);
                out += s.str();
                if(i != c.v.size()){
                    out +=  "]\n";
                }else{
                    out += "]";
                }
            }
            i++;
        }
        
        return (output << out);
    }

    istream& operator>> (istream& input, Matrix& c) {
        return input;
    }

}

    
