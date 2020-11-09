//
// Created by 王尚荣 on 2020/11/7.
//

#ifndef BUILDGRAPH_MATRIX_H
#define BUILDGRAPH_MATRIX_H
#include "List.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "hash.h"
using namespace std;

class Matrix {
public:
    Matrix(int N);
    void add(int i, int j, double value);
    double get(int i, int j);
    void print();

private:
    vector<vector<int>> column_idx;
    vector<vector<double>> values;
    int UrlNum;                             // 当前节点数
};


#endif //BUILDGRAPH_MATRIX_H
