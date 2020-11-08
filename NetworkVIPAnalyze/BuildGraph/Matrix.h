//
// Created by 王尚荣 on 2020/11/7.
//

#ifndef BUILDGRAPH_MATRIX_H
#define BUILDGRAPH_MATRIX_H
#include "List.h"
#include "unordered_map"
using namespace std;
class Matrix {
public:
    Matrix();
    void add(char* src, char* dst);
    void add(int i, int j, double value);

private:
    List<List<int>*> column_idx;
    List<List<int>*> values;
    unordered_map<string, int> url_idx;     // url 映射为 节点索引
    List<char*> idx_url;                    // 节点索引 映射为 url
    int UrlNum;                             // 当前节点数
};


#endif //BUILDGRAPH_MATRIX_H
