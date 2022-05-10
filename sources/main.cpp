// #include "Matrix.cpp"
// #include <string>
// #include <iostream>
// #include <vector>
// int main(){
//     using namespace std;
//     using namespace zich;
//     vector<double> identity_1 = {1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1};
//     vector<double> identity_2 = {1 ,0 ,0 ,1};
//     Matrix m_1 = {identity_1, 3, 3};
//     Matrix m_2 = {identity_2, 2, 2};
//     m_1 *= m_1;
//     m_2 *= m_2;
//     cout << m_1 << endl << endl;
//     cout << m_2 << endl << endl;
//     m_1 *= 9;
//     m_2 *= 9;
//     cout << m_1 << endl << endl;
//     cout << m_2 << endl;
//     bool a = m_1 == m_1;
//     cout << a << endl;
//     Matrix m_3 = {identity_1, 3, 3};
//     a = m_1 == m_3;
//     cout << a << endl;
//     m_1 += m_3;
//     cout << m_1 << endl << endl;
//     m_1 -= m_3;
//     cout << m_1 << endl << endl;
//     istringstream i{"[1 0 0], [0 1 0], [0 0 1]\n"};
//     i >> m_1;
//     cout << m_1 << endl << endl;
//     return 0;
// }