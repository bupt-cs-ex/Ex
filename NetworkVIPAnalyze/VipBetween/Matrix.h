//
// Created by edwin on 2020/11/18 0018.
//

#ifndef VIPBETWEEN_MATRIX_H
#define VIPBETWEEN_MATRIX_H

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
using namespace std;

class Matrix {
public:
    Matrix(int N);
    void betweeness_centrality();
public:
    vector<vector<int>> column_idx;
    vector<double> betweeness;     //记录各顶点的介数
    int UrlNum;                    // 当前节点数
};

Matrix* load_matrix(const string& file_name);
vector<string> load_urls(const string& file_name);

#endif //VIPBETWEEN_MATRIX_H
