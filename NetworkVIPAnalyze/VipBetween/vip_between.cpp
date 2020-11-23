#include <iostream>
#include "Matrix.h"
#include <time.h>

vector<string> LoadData(Matrix*& mat, const string& mat_txt, const string& url_txt) {
    if(mat == nullptr){
        mat = load_matrix(mat_txt);
    }
    return load_urls(url_txt);
}

int main() {
    clock_t start_time = clock();

    Matrix* matrix = nullptr;
    string graph_file = "../graph.txt";
    string url_file = "../urls.txt";
    matrix = load_matrix(graph_file);
    vector<string> urls = load_urls(url_file);
    cout << "url nums = " << matrix->UrlNum << endl;
    matrix->betweeness_centrality();

    vector<pair<double, int>> betweens_id;
    for(int i = 0; i < matrix->UrlNum; ++i) {
        betweens_id.emplace_back(matrix->betweeness[i], i);
    }
    sort(betweens_id.begin(), betweens_id.end(), [](pair<double, int>& o1, pair<double, int>& o2){return o1.first > o2.first;});
    for(int i = 0; i < 20; ++i) {
        cout << i + 1 << ": " << urls[betweens_id[i].second] << " , betweeness centrality: " << betweens_id[i].first << endl;
    }

    clock_t end_time = clock();
    printf("total runtime: %lu ms\n", (end_time - start_time) * 1000/CLOCKS_PER_SEC);

    return 0;
}
