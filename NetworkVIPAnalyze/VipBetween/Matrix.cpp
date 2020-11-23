//
// Created by edwin on 2020/11/18 0018.
//

#include <iostream>
#include "Matrix.h"
#include <numeric>

Matrix::Matrix(int N):column_idx(vector<vector<int>>(N)), betweeness(vector<double>(N, 0.0)){
    UrlNum = N;
}
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
