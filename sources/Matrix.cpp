#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Matrix.hpp"
#include <stdexcept>
#include <cmath>
const int IS_NUMBER_UP_BORDER = 9;
const int IS_NUMBER_LOW_BORDER = 0;
const int BASE = 10;
using namespace std;
namespace zich{
    Matrix::Matrix(const vector<double>& vec , int row, int column){
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
    bool isNumber(const char c){
        bool ans = c - '0' <= IS_NUMBER_UP_BORDER && c - '0' >= IS_NUMBER_LOW_BORDER;
        return ans;        
    }
    int getFractionPoint(const string& s){
        for (uint i = 0; i < s.size(); i++){
            if (s.at(i) == '.'){
                return (int)i;
            }
        }
        return s.size();
    }

    double stringToNumber(const string& s){
        double  num = 0;
        int point = getFractionPoint(s);  /// 1
        for (uint i = 0; i < point; i++){
            int current = s.at(i) - '0';
            num += (current * pow (BASE, (uint)point -1 - i));
        }
        for (int i = 0; i < (int)s.size() - point - 1; i++){
            int current = s.at((uint)i) - '0';
            num += (current * pow (BASE, -1 - (int)i));
        }
        return num;
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
        bool ans = matrixSum(*this) < matrixSum(other);
        return ans;
    }

    bool Matrix::operator>(const Matrix& other)const{
        checkDefine(*this , other , false);
        bool ans = matrixSum(*this) > matrixSum(other);
        return ans;
    }
    bool Matrix::operator<=(const Matrix& other)const{
        checkDefine(*this , other, false);
        bool ans = matrixSum(*this) <= matrixSum(other);
        return ans;
    }
    bool Matrix::operator>=(const Matrix& other)const{
        checkDefine(*this , other , false);
        bool ans = matrixSum(*this) >= matrixSum(other);
        return ans;
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
    //output operator
    ostream& operator<< (ostream& output, const Matrix& c){
        string out;
        uint i = 1;
        // take care on marix with 1 row 
        if (c.row == 1){
            out += '[';
            // s is needed for the cast from the matrix to string will be in good format
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
        // take care on marix with 1 column
        if (c.column ==1){
            for(uint i = 0; i < c.row - 1; i++){
                out += '[';
                // s is needed for the cast from the matrix to string will be in good format
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
        // the genral case when M is matrix nXk such that n >= 2 ,k >=2
        while (i <= c.v.size()){
            if (i % (uint)c.column != 0){  // Go through the whole line except the last element
                if( i % (uint)c.column == 1){  // start of line
                    out += '[';
                }
                // s is needed for the cast from the matrix to string will be in good format
                ostringstream s;
                s << c.v.at(i -1);
                out += s.str();
                out += ' ';
            }else{
                // s is needed for the cast from the matrix to string will be in good format
                ostringstream s;
                s << c.v.at(i -1); // this is the last element in this line
                out += s.str();
                if(i != c.v.size()){
                    out +=  "]\n";  // end of line
                }else{
                    out += "]";  // end of matrix
                }
            }
            i++;
        }
        return (output << out);
    }
    // input operator
    istream& operator>> (istream& input, Matrix& c) { 
        string st;
        getline(input , st);
        uint i = 0;
        int row = 0;
        int column = 0;
        bool startOfRow = true;
        bool onePoint = true;
        while (i < st.size()) {
            if (st.at(i) == '[') {
                if (!startOfRow) {
                    throw ("invalid input 1");
                }
                row++;
                startOfRow = false;
            }
            if (st.at(i) == ']') {
                if (startOfRow) {
                    throw ("invalid input 2");
                }
                startOfRow = true;
            }
            if (st.at(st.size() - 1 ) != ']') {
                throw ("invalid input 3");
            }
            
            if (st.at(i) == ',') {
                if (st.at(i+1) != ' ') {
                    throw ("invalid input 4");
                }
            }
            if (isNumber(st.at(i))) {
                string numString;
                onePoint = true;
                numString += st.at(i);
                i++;
                while (i < st.size() && (isNumber(st.at(i)) || st.at(i) == '.') ){
                    if (st.at(i) == '.' && (!onePoint || !isNumber(st.at(i+1)))){
                        throw ("invalid input");
                    }
                    if (onePoint && st.at(i) == '.'){
                        onePoint = false;
                    }
                    numString += st.at(i);
                    i++;
                }// while
                double num = stringToNumber(numString);
                c.v.push_back(num);
            }            
            i++;
        }// while
        return input;
    }

}

    
