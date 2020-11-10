//
// Created by 王尚荣 on 2020/11/7.
//

#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int N): column_idx(vector<vector<int>>(N)), values(vector<vector<double>>(N)){
    UrlNum = N;
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

double Matrix::get(int i, int j)const {
    if(i < 0 || j < 0 || i >= UrlNum || j >= UrlNum)
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
/**
 * 矩阵保存在.txt文件中
 * 保存格式(三元组格式保存)：
 * LineNum
 * UrlNum
 * i    j     value
 * @param file_name
 */
void Matrix::save(const string &file_name) {
    ofstream out = ofstream(file_name, ofstream::out);
    out<<UrlNum<<endl;
    for(int i = 0; i < UrlNum; i++){
        for(int j = 0; j < column_idx[i].size(); j++){
            out << i << "\t" << column_idx[i][j] << "\t" <<  values[i][j] << endl;
        }
    }
    cout << "save matrix in " << file_name << " success" << endl;
    out.close();
}

void Matrix::set(int i, int j, double value) {
    if(value != 0.0){
        add(i, j, value);
    }
}

double Matrix::det() const {
    return 0;
}


Matrix operator*(const Matrix &A, const Matrix &B) {
    assert(A.UrlNum == B.UrlNum);
    int N = A.UrlNum;
    Matrix M(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            double val = 0.0;
            for(int k = 0; k < N; k++){
                val += A.get(i, k) * B.get(k, j);
            }
            M.set(i, j, val);
        }
    }
    return M;
}
/**
 * 从格式化txt中加载矩阵
 * @param file_name
 * @return
 */
Matrix* load_matrix(const string &file_name) {
    ifstream in = ifstream(file_name, ifstream::in);
    int N;
    in >> N;
    auto* M = new Matrix(N);
    int i, j;
    double value;
    string Line;
    while(in >> i >> j >> value){
        M->add(i, j, value);
    }
    in.close();
    cout << "load matrix from " << file_name << " success" << endl;
    return M;
}

Matrix operator+(const Matrix &A, const Matrix &B) {
    int N = A.UrlNum;
    Matrix M(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            M.set(i, j, A.get(i, j) + B.get(i, j));
        }
    }
    return M;
}

Matrix operator-(const Matrix &A, const Matrix &B) {
    int N = A.UrlNum;
    Matrix M(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            M.set(i, j, A.get(i, j) - B.get(i, j));
        }
    }
    return M;
}
/**
 * 保存urls信息
 * 格式：
 * UrlNum
 * @param file_name
 */
void save_urls(const string &file_name, const vector<string>& urls) {
    ofstream out = ofstream(file_name, ofstream::out);
    out << urls.size() << endl;
    for(int i = 0; i < urls.size(); i++)
        out << urls[i] << endl;
    out.close();
    cout << "save urls in " << file_name << " success" << endl;
}

vector<string> load_urls(const string &file_name) {
    ifstream in = ifstream(file_name, ifstream::in);
    int N;
    in >> N;
    vector<string> urls(N);
    string Line;
    int i = 0;
    while(in >> Line){
        urls[i++] = Line;
    }
    cout << "load urls from " << file_name << " success" << endl;
    in.close();
    return urls;
}
