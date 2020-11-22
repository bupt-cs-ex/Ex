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
    void print();
    //void save(const string& file_name);
    void set(int i, int j/*, double value, int preNode*/);
    //void floyd();
    void betweeness_centrality();
public:
    vector<vector<int>> column_idx;
    //vector<vector<double>> values;
    //vector<vector<int>> paths;
    vector<double> betweeness;     //记录各顶点的介数
    int UrlNum;                    // 当前节点数
    
//private:
    int _find(int row, int col)const;
};

Matrix* load_matrix(const string& file_name);
vector<string> load_urls(const string& file_name);

#endif //VIPBETWEEN_MATRIX_H
