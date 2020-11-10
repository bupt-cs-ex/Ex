//
// Created by 王尚荣 on 2020/11/7.
//

#ifndef BUILDGRAPH_MATRIX_H
#define BUILDGRAPH_MATRIX_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Matrix {
public:
    Matrix(int N);
    void add(int i, int j, double value);
    void set(int i, int j, double value);
    double get(int i, int j)const;
    void print();
    void save(const string& file_name);
    double det()const;
public:
    vector<vector<int>> column_idx;
    vector<vector<double>> values;
    int UrlNum;                             // 当前节点数
};

Matrix operator*(const Matrix& A, const Matrix& B);
Matrix operator+(const Matrix& A, const Matrix& B);
Matrix operator-(const Matrix& A, const Matrix& B);

Matrix* load_matrix(const string& file_name);
void save_urls(const string& file_name, const vector<string>& urls);
vector<string> load_urls(const string& file_name);
#endif //BUILDGRAPH_MATRIX_H
