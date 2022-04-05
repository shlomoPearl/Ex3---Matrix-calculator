#include <vector>
#include <iostream>
#include "Matrix.hpp"
using namespace std;
namespace zich{
    Matrix::Matrix(vector<double> vec , int row, int column){
        this->v = vec;
        this->row = row;
        this->column = column;
    }
    // #### math operators ####
    // unary
    Matrix Matrix::operator+()const{
        return Matrix(this->v,this->row,this->column);
    }
    // unary
    Matrix Matrix::operator-()const{
        vector<double> copy = this->v;
        // change all values to minus
        for (uint i = 0; i < copy.size(); i++){
            copy.at(i) = - copy.at(i);
        }
        return Matrix(copy,this->row,this->column);
    } 

    Matrix& Matrix::operator+(const Matrix& other){
        for (uint i = 0; i < this->v.size(); i++){
            this->v.at(i) += other.v.at(i);
        }
        return *this;
        
    }
    Matrix& Matrix::operator+=(double scalar){
        for (uint i = 0; i < this->v.size(); i++){
            this->v.at(i) += scalar;
        }
        return *this;
        
    }
    Matrix& Matrix::operator-(const Matrix& other){
        for (uint i = 0; i < this->v.size(); i++){
            this->v.at(i) -= other.v.at(i);
        }
        return *this;
    }
    Matrix& Matrix::operator-=(double scalar){
        for (uint i = 0; i < this->v.size(); i++){
            this->v.at(i) -= scalar;
        }
        return *this;
    }

    //comprasion operator
    bool Matrix::operator<(const Matrix& other){return false;}
    bool Matrix::operator<=(const Matrix& other){return false;}
    bool Matrix::operator>(const Matrix& other){return false;}
    bool Matrix::operator>=(const Matrix& other){return false;}
    bool Matrix::operator==(const Matrix& other){return false;}
    bool Matrix::operator!=(const Matrix& other){return false;}

    //added operator
    Matrix& Matrix::operator++(){return *this;}   // prefix
    Matrix& Matrix::operator--(){return *this;}    // prefix
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

    //multiplye operator
    Matrix& operator*(double scalar, Matrix& mat){
        for (uint i = 0; i < mat.v.size(); i++){
            mat.v.at(i) *= scalar;
        }
        return mat;
    }
    Matrix& Matrix::operator*=(double scalar){
        for (uint i = 0; i < this->v.size(); i++){
            this->v.at(i) *= scalar;
        }
        return *this;
    }
    Matrix Matrix::operator*(const Matrix& other){
        vector<double> copy(uint(this->row) * uint(this->column));
        for (uint i = 0; i < this->row ; i++){
            for (uint k = 0; k < this->column ; k++){
                for (uint j = 0; j < other.row ; j++){
                    copy.at(i+k) = this->v.at(i+k) * other.v.at(k+j);
                }
            }   
        }
        return  Matrix(copy, this->row, other.column);
    }
 
    //input and output operator
    ostream& operator<< (ostream& output, const Matrix& c){
        return (output << "shlomo");
    }
    istream& operator>> (istream& input, Matrix& c) {
        return input;
    }

}

    
