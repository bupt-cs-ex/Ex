#include <iostream>
#include "Matrix.h"

vector<string> LoadData(Matrix*& mat, const string& mat_txt, const string& url_txt) {
    if(mat == nullptr){
        mat = load_matrix(mat_txt);
    }
    return load_urls(url_txt);
}

int main() {
//    Matrix* matrix = nullptr;
//    string graph_file = "../graph.txt";
//    string urls_file = "../urls.txt";
//    vector<string> urls = LoadData(matrix, graph_file, urls_file);
//    cout << "url nums = " << matrix->UrlNum << endl;

    Matrix* matrix = nullptr;
    string graph_file = "../graph.txt";
    string url_file = "../urls.txt";
    matrix = load_matrix(graph_file);
    vector<string> urls = load_urls(url_file);
    cout << "url nums = " << matrix->UrlNum << endl;
//    matrix->floyd();
    matrix->betweeness_centrality();

    vector<pair<double, int>> betweens_id;
    for(int i = 0; i < matrix->UrlNum; ++i) {
        betweens_id.emplace_back(matrix->betweeness[i], i);
    }
    sort(betweens_id.begin(), betweens_id.end(), [](pair<double, int>& o1, pair<double, int>& o2){return o1.first > o2.first;});
    for(int i = 0; i < 20; ++i) {
        cout << i << ": " << urls[betweens_id[i].second] << " betweeness centrality: " << betweens_id[i].first << endl;
    }



//    //输出所有顶点之间的最短路径
//    for(int i = 0; i < matrix->UrlNum; ++i) {
//        for(int j = 0; j < matrix->UrlNum; ++j) {
//            int ij_col = matrix->_find(i, j);
//            if(ij_col != -1) {
//                cout << i << " to " << j <<" paths: " << j;
//                int preNode = matrix->paths[i][ij_col];
//                while(preNode != i) {
//                    cout << " <- " << preNode;
//                    preNode = matrix->paths[i][matrix->_find(i, preNode)];
//                }
//                cout << " <- " << preNode << endl;
//            }
//        }
//    }


    return 0;
}
