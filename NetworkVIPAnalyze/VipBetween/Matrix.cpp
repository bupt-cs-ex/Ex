//
// Created by edwin on 2020/11/18 0018.
//

#include <iostream>
#include "Matrix.h"
#include <numeric>

Matrix::Matrix(int N):column_idx(vector<vector<int>>(N)),
//values(vector<vector<double>>(N)),
//paths(vector<vector<int>>(N)), betweeness(vector<double>(N, 0.0)){
betweeness(vector<double>(N, 0.0)){
    UrlNum = N;
//    for(int i = 0; i < UrlNum; ++i) {
//        betweeness[i] = 0.0;
//    }
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
//    printf("*****************************\n\nvalues idx:\n");
//    for(int i = 0; i < UrlNum; i++){
//        for(int j = 0; j < column_idx[i].size(); j++){
//            printf("%lf ", values[i][j]);
//        }
//        printf("\n");
//    }
//    printf("*****************************\n\npath idx:\n");
//    for(int i = 0; i < UrlNum; i++){
//        for(int j = 0; j < column_idx[i].size(); j++){
//            printf("%d ", paths[i][j]);
//        }
//        printf("\n");
//    }
//    printf("----------------------------------\n\n");

}
/**
 * 矩阵保存在.txt文件中
 * 保存格式(三元组格式保存)：
 * LineNum
 * UrlNum
 * i    j     value
 * @param file_name
 */
//void Matrix::save(const string &file_name) {
//    ofstream out = ofstream(file_name, ofstream::out);
//    out<<UrlNum<<endl;
//    for(int i = 0; i < UrlNum; i++){
//        for(int j = 0; j < column_idx[i].size(); j++){
//            out << i << "\t" << column_idx[i][j] << "\t" <<  values[i][j] << endl;
//        }
//    }
//    cout << "save matrix in " << file_name << " success" << endl;
//    out.close();
//}
/**
 * 用于直接设置值
 * @param i
 * @param j
 * @param value
 */
void Matrix::set(int i, int j/*, double value, int preNode*/) {
//    if(value != 0.0){
//        column_idx[i].push_back(j);
//        //values[i].push_back(value);
//        //paths[i].push_back(preNode);
//    }
    column_idx[i].push_back(j);
}
/**
 * 使用floyd算法求所有顶点对最短路径
 */
//void Matrix::floyd() {
//    //print();
//    cout << "floyd..." << endl;
//    for(int k = 0; k < UrlNum; k++) {
//        cout << " k = " << k << endl;
//        for(int i = 0; i < UrlNum; i++) {
//            for(int j = 0; j < UrlNum; j++) {
//                //查找各个值实际在values中存储的列号
//                int ik_col = _find(i, k);
//                int kj_col = _find(k, j);
//                int ij_col = _find(i, j);
//
//                //j != i: 对角线元素不更新
//                if(j != i && ik_col != -1 && kj_col != -1) {
//                    if(ij_col == -1) {
//                        int newValue = values[i][ik_col] + values[k][kj_col];
//                        int preNode = paths[k][kj_col];
//                        set(i, j, newValue, preNode);
//                    }
//                    else if(values[i][ik_col] + values[k][kj_col] < values[i][ij_col]) {
//                        values[i][ij_col] = values[i][ik_col] + values[k][kj_col];
//                        paths[i][ij_col] = paths[k][kj_col];
//                    }
//                }
//            }
//        }
//        //print();
//    }
//    cout << "floyd finished." << endl;
//}
/**
 * 计算各点的最短路径条数
 */
void Matrix::betweeness_centrality()
{
    cout << "count betweeness centrality..." << endl;

    for(int i = 0; i < UrlNum; i++) {           //遍历每个节点
        if(i % 100 == 0)
            cout << "currnet node: " << i << endl;

        stack<int> S;
        vector<vector<int>> pred(UrlNum);       //从第i个节点到其它各节点的前驱节点集合
        vector<int> sigma(UrlNum, 0);       //从第i个节点到其他节点的最短路径数
        sigma[i] = 1;
        vector<int> dist(UrlNum, -1);       //从第i个节点到其它节点的最短距离
        dist[i] = 0;
        queue<int> Q;
        Q.push(i);

        while(!Q.empty()) {
            int v = Q.front();                  //从队列首部取出一个节点
            Q.pop();
            S.push(v);
            for(int j = 0; j < column_idx[v].size(); j++) {
                int w = column_idx[v][j];       //w为v的邻接节点

                //如果点w是第一次被找到
                if(dist[w] < 0) {
                    Q.push(w);
                    dist[w] = dist[v] + 1;
                }

                //如果是经过点v到w的最短路
                if(dist[w] == dist[v] + 1) {
                    sigma[w] += sigma[v];
                    pred[w].push_back(v);
                }
            }
        }

        vector<double> delta(UrlNum, 0);
        while(!S.empty()) {
            int w = S.top();
            S.pop();
            for(int j = 0; j < pred[w].size(); j++){
                int v = pred[w][j];
                delta[v] += double(sigma[v]) / double(sigma[w]) * (1.0 + delta[w]);   //记得将sigma转化为double，否则计算结果会变成int
            }
            if(w != i) {
                betweeness[w] += delta[w];
            }
        }
    }

    cout << "finished count betweens centrality." << endl;
}

/**
 * 查看一下第row行有没有列号为col
 * @param row
 * @param col
 * @return idx or -1
 */
int Matrix::_find(int row, int col)const {
    for(int i = 0 ; i < column_idx[row].size(); i++)
        if(column_idx[row][i] == col)
            return i;
    return -1;
}

/**
 * 从格式化txt中加载矩阵
 * @param file_name
 * @return
 */
Matrix* load_matrix(const string &file_name) {
    ifstream in = ifstream(file_name, ifstream::in);
    int N;
    cout << "start read " << file_name << endl;
    in >> N;
    auto* M = new Matrix(N);
    int row, col;
    double value;
    string Line;
    while(in >> col >> row >> value) {  //由于路径指向相反，所以反着读行列值
        //M->set(row, col, value, row);
        //M->set(row, col, 1, row);        //无权图，有边的权值都设为1, 前驱节点初始化为起点
        //M->set(row, col, 1);
        M->column_idx[row].push_back(col);
    }
    in.close();
    cout << "load matrix from " << file_name << " success" << endl;
    return M;
}

vector<string> load_urls(const string &file_name) {
    ifstream in = ifstream(file_name, ifstream::in);
    int N = 0;
    cout << "start read file" << file_name << endl;
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
