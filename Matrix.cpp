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
    this func get two marix and check if mult add and sub is defined on them.
    the bool flag is to divide between the cases of mult and sub or add
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
    // check if this char represent number
    bool isNumber(const char c){
        bool ans = c - '0' <= IS_NUMBER_UP_BORDER && c - '0' >= IS_NUMBER_LOW_BORDER;
        return ans;        
    }
    // check if there is this number that represent by the string is fraction number
    // return point index
    int getFractionPoint(const string& s){
        for (uint i = 0; i < s.size(); i++){
            if (s.at(i) == '.'){
                return (int)i;
            }
        }
        return s.size();
    }
    // cast string  that represent number to real number
    // return the cast number
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
    // unary- return copy of the matrix
    Matrix Matrix::operator+()const{
        return Matrix(*this);
    }
    // unary- return copy of the matrix with minus on all the element 
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
    // binary- return copy matrix represent the '+' between 2 matrix
    Matrix Matrix::operator+(const Matrix& other){
        checkDefine(*this , other, false);
        Matrix copy = Matrix(*this);
        for (uint i = 0; i < copy.v.size(); i++){
            copy.v.at(i) += other.v.at(i);
        }
        return copy;
        
    }
    // return reference to this matrix with add of element in other matrix
    Matrix& Matrix::operator+=(const Matrix& other){
        checkDefine(*this, other, false); 
        *this = *this + other;
        return *this;
    }
    // // binary- return copy matrix represent the '-' between 2 matrix
    Matrix Matrix::operator-(const Matrix& other){
        checkDefine(*this, other, false);
        Matrix copy = Matrix(*this);
        for (uint i = 0; i < copy.v.size(); i++){
            copy.v.at(i) -= other.v.at(i);
        }
        return copy;
    }
    // return reference to this matrix with sub of element in other matrix
    Matrix& Matrix::operator-=(const Matrix& other){
        checkDefine(*this, other, false); 
        *this = *this - other;
        return *this;
    }

    // #### comprasion operator ####
    // all the compration operator are const because they don't change the objects

    // return if sum of this matrix < other matrix
    bool Matrix::operator<(const Matrix& other)const{
        checkDefine(*this , other, false);
        bool ans = matrixSum(*this) < matrixSum(other);
        return ans;
    }
    // return if sum of this matrix > other matrix
    bool Matrix::operator>(const Matrix& other)const{
        checkDefine(*this , other , false);
        bool ans = matrixSum(*this) > matrixSum(other);
        return ans;
    }
    // return if sum of this matrix <= other matrix 
    // implements by '!' on > operator
    bool Matrix::operator<=(const Matrix& other)const{
        checkDefine(*this , other, false);
        bool ans = *this > other;
        return !ans;
    }
    // return if sum of this matrix >= other matrix 
    // implements by '!' on < operator
    bool Matrix::operator>=(const Matrix& other)const{
        checkDefine(*this , other , false);
        bool ans = *this < other;
        return !ans;
    }
    // return if matrix this[i][j] == other[i][j] for all i,j  
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
    // return if matrix this[i][j] == other[i][j] for all i,j
    // implementts by using '!' on == operator
    bool Matrix::operator!=(const Matrix& other)const{
        checkDefine(*this , other, false);
        return !(*this == other);
    }

    // #### added operator ####
    // prefix - increase the elements in 1 and than return refrence to this matrix
    Matrix& Matrix::operator++(){
        for (uint i = 0; i < this->v.size() ; i++){
            this->v.at(i)++;
        }
        return *this;
    } 
    // prefix - decrease the elements in 1 and than return refrence to this matrix  
    Matrix& Matrix::operator--(){
        for (uint i = 0; i < this->v.size() ; i++){
            this->v.at(i)--;
        }
        return *this;
    }   
    // postfix - return copy of this and increase the elements of this in 1
    // the dummy int is for the compiler will seperate between postfix and prefix
    Matrix Matrix::operator++(int dummy){ 
        Matrix copy = *this;
        for (uint i = 0; i < copy.v.size(); i++){
            this->v.at(i) ++;
        }
        return copy;       
    }   
    // postfix - return copy of this and  decrease the elements of this in 1
    // the dummy int is for the compiler will seperate between postfix and prefix
    Matrix Matrix::operator--(int dummy){
        Matrix copy = *this;
        for (uint i = 0; i < copy.v.size(); i++){
            this->v.at(i) --;
        }
        return copy;
    }   

    // #### multiplye operator ####

    // left mult in scalar
    Matrix operator*(double scalar,const Matrix& mat){
        vector<double> copy (mat.v.size());
        for (uint i = 0; i < mat.v.size(); i++){
            copy.at(i) = mat.v.at(i) * scalar;
        }
        return Matrix(copy, mat.row, mat.column);
    }
    // right mult in scalar
    // implement with left mult operator
    Matrix operator*(const Matrix& mat, double scalar){
        return scalar*mat;
    }
    // mult the elements in scalar and return reference
    // implement with right mult operator
    Matrix& Matrix::operator*=(double scalar){
        *this = *this * scalar;
        return *this;
    }
    /*
    @ return - copy matrix represent mult between two matrix
    @ implements by 3 while loop and some variabels-
    first while - all the elements of copy
    second while - current row of this and column of other
    third while - current element
    p -> represent the copy element - make sur we pass all the copy marix values
    row -> represent the row of this- make sure we pass all the row
    joint -> length of column and row are the same
    column -> make sure we pass through this row and othe column elements
    row_index -> offset in current row
    column_index -> offset in current column
    */
    Matrix Matrix::operator*(const Matrix& other)const{
        checkDefine(*this , other, true);
        Matrix copy = Matrix(vector<double>(uint(this->row * other.column), 0),this->row,other.column);
        uint p = 0;
        uint row = 0; 
        uint joint = (uint)other.row; 
        while (p < copy.v.size()) {
            uint column = 0;  
            while (column < other.column) {
                uint row_index = 0; 
                uint column_index = 0; 
                while (row_index < joint) {
                    copy.v.at(p) += this->v.at(row_index + row) * other.v.at(column_index + column);
                    row_index++;
                    column_index += (uint)other.column; 
                } 
                column++;
                p++;
            } 
            row += joint;
        } 
        return copy;
    }
    // mult the elements of this matrix in other matrix
    // return reference
    // implement with '*' operator on matrix
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
        vector<double> _v;
        int row = 0;
        int column = 1;
        bool startOfRow = true;
        bool onePoint = true; // for double number
        int numberOfColumnUpdate = 0;
        bool first = true;
        while (i < st.size()) {
            if (st.at(i) == '[') {
                if (!startOfRow) {  // current line input doesn't finish
                    throw invalid_argument("unexcepted argument1");
                }
                row++;
                startOfRow = false; // not except to '[' until ']'
            }
            
            if (isNumber(st.at(i))) {
                string numString;
                onePoint = true;
                numString += st.at(i);
                i++;
                while (i < st.size() && (isNumber(st.at(i)) || st.at(i) == '.') ){
                    if (st.at(i) == '.' && (!onePoint || !isNumber(st.at(i+1)))){
                        throw invalid_argument("invalid number");
                    }
                    if (onePoint && st.at(i) == '.'){
                        onePoint = false;
                    }
                    numString += st.at(i);
                    i++;
                }// while of number
                double num = stringToNumber(numString);
                _v.push_back(num);  
            }
            // count the element in each line. this is the column number
            if (st.at(i) == ' ' && !startOfRow) {
                column++;
            }
            if (st.at(i) == ']') {
                if (startOfRow) { // current line input already finish
                    throw invalid_argument("unexcepted argument2");
                }
                startOfRow = true;  // except to '['
                if (!first && numberOfColumnUpdate != column ) {
                    throw invalid_argument("diffrence between the column");
                }
                numberOfColumnUpdate = column;
                first = false;
                column = 1;
            }
            if (st.at(i) == ',') {  // The lines are separated with ', ' - comma and space
                i++;
                if (st.at(i) != ' ') {  
                    throw invalid_argument("unexcepted argument4");
                }
            }       
            i++;
        }// while
        // update the size and vector
        c.v = _v;
        c.column = numberOfColumnUpdate;
        c.row = row;
        return input;
    }
}

    
