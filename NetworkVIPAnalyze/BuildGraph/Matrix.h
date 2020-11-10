//
// Created by 王尚荣 on 2020/11/7.
//

#ifndef BUILDGRAPH_MATRIX_H
#define BUILDGRAPH_MATRIX_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

class Matrix {
public:
    Matrix(int N);
    void add(int i, int j, double value);
    void set(int i, int j, double value);
    double get(int i, int j)const;
    void print();
    void save(const string& file_name);
    Matrix& operator*(double alpha);
    void set_base(double b);

public:
    vector<vector<int>> column_idx;
    vector<vector<double>> values;
    int UrlNum;                             // 当前节点数
    double base;
};

Matrix operator*(const Matrix& A, const Matrix& B);
vector<double> operator*(const Matrix& A, const vector<double>& vec);
double get_mod(const vector<double>& v1, const vector<double>& v2);
Matrix* load_matrix(const string& file_name);
void save_urls(const string& file_name, const vector<string>& urls);
vector<string> load_urls(const string& file_name);
#endif //BUILDGRAPH_MATRIX_H
