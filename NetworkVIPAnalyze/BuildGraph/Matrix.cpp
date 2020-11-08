//
// Created by 王尚荣 on 2020/11/7.
//

#include "Matrix.h"

Matrix::Matrix() {
    UrlNum = 0;
}

/**
 * 将源节点指向目的节点的边加入到图中
 * @param src 源节点
 * @param dst 目的节点
 */
void Matrix::add(char *src, char *dst) {
    string str_src(src);
    string str_dst(dst);
    if(url_idx.find(str_src) == url_idx.end()){
        url_idx.insert({str_src, UrlNum++});
        idx_url.append(src);
    }
    if(url_idx.find(str_dst) == url_idx.end()){
        url_idx.insert({str_dst, UrlNum++});
        idx_url.append(dst);
    }
    add(url_idx[str_dst], url_idx[str_src], 1.0);
}

void Matrix::add(int i, int j, double value) {

}
