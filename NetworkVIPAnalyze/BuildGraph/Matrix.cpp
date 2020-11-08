//
// Created by 王尚荣 on 2020/11/7.
//

#include "Matrix.h"

Matrix::Matrix(int N){
    UrlNum = N;
    column_idx = new List<int>[N];
    values = new List<double>[N];
}


/**
 * 向矩阵Matrix[i][j] 中添加元素
 * @param i
 * @param j
 * @param value
 */
void Matrix::add(int i, int j, double value) {
    int idx = column_idx[i].find(j);
    // 若 i,j 已存在值 则直接相加 否则创建新值
    if(idx == -1){
        column_idx[i].append(j);
        values[i].append(value);
    }else
        values[i][idx] += value;
}

double Matrix::get(int i, int j) {
    int idx = column_idx[i].find(j);
    // 查不到，为0
    if(idx == -1)
        return 0.0;
    else
        return values[i][idx];
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
