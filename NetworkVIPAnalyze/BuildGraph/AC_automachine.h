//
// Created by 王尚荣 on 2020/11/8.
//

#ifndef BUILDGRAPH_AC_AUTOMACHINE_H
#define BUILDGRAPH_AC_AUTOMACHINE_H

#include <string.h>
#include "queue.h"
#include <unordered_map>
#include "hash.h"
using namespace std;

/**
 * AC 自动机
 */
class AC_automachine {
public:
    AC_automachine();
    ~AC_automachine();
    void Insert(char* pattern);
    int Build();
    Node* Match(char* text, Node* start=nullptr);
    List<unsigned int>* MatchByFile(char* filename, char* mode="rb");
//    void OutputToFile(char* filename);
    int findKey(char* key);
    void clear();
private:
    Node* root;                         // 根节点
    unordered_map<char*, unsigned, hash_func, cmp> url_idx;     // map 快速查找url在urls中的位置
    List<char*> urls;
    List<unsigned int> match_result;            // 一个html中的匹配结果
};

#endif //BUILDGRAPH_AC_AUTOMACHINE_H
