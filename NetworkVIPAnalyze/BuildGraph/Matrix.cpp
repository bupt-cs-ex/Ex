//
// Created by 王尚荣 on 2020/11/7.
//

#include "Matrix.h"

Matrix::Matrix(int N): column_idx(vector<vector<int>>(N)), values(vector<vector<double>>(N)){
    UrlNum = N;
    printf("%lu\n", column_idx.size());
}


/**
 * 向矩阵Matrix[i][j] 中添加元素
 * @param i
 * @param j
 * @param value
 */
void Matrix::add(int i, int j, double value) {
    if(i < 0 || j < 0 || i >= UrlNum || j >= UrlNum){
        printf("i, j > UrlNum\n");
        return;
    }
    auto idx = find(column_idx[i].begin(), column_idx[i].end(), j);
    // 若 i,j 已存在值 则直接相加 否则创建新值
    if(idx == column_idx[i].end()){
        column_idx[i].push_back(j);
        values[i].push_back(value);
    }else
        values[i][idx - column_idx[i].begin()] += value;
}

double Matrix::get(int i, int j) {
    if(i >= UrlNum || j >= UrlNum)
        return 0.0;
    auto idx = find(column_idx[i].begin(), column_idx[i].end(), j);
    // 查不到，为0
    if(idx == column_idx[i].end())
        return 0.0;
    else
        return values[i][idx - column_idx[i].begin()];
}

void Matrix::print() {
    printf("UrlNum:%d\n", UrlNum);
    printf("columns idx:\n");
    for(int i = 0; i < UrlNum; i++){
        for(int j = 0; j < column_idx[i].size(); j++){
            printf("%d ", column_idx[i][j]);
        }
        printf("\n");
    }
    printf("*****************************\n\nvalues idx:\n");
    for(int i = 0; i < UrlNum; i++){
        for(int j = 0; j < column_idx[i].size(); j++){
            printf("%lf ", values[i][j]);
        }
        printf("\n");
    }

}
