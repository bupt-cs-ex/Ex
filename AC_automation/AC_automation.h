//
// Created by 王尚荣 on 2020/10/14.
//

#ifndef AC_AUTOMATION_AC_AUTOMATION_H
#define AC_AUTOMATION_AC_AUTOMATION_H
#include <string.h>
#include <stdio.h>
#include "queue.h"
#include <unordered_map>
using namespace std;
/**
 *  统计信息
 *  存储 key count offset1, offset2 ...
 *  存储key的源
 */
class Stat{
public:
    Stat(char* k = nullptr) {
        key = k;
        count = 0;
    }
    char* key;
    unsigned count;
    List<unsigned> offsetList;
};

/**
 * AC 自动机
 */
class AC_automation {
public:
    AC_automation();
    ~AC_automation();
    void Insert(char* pattern);
    void Build();
    Node* Match(char* text, int base=0, Node* start=nullptr);
    void MatchByFile(char* filename, char* mode="rb");
    void OutputResult();
    void OutputToFile(char* filename);
private:
    Node* root;                         // 根节点
    List<Stat*> stats;                  // 记录每个key的统计信息
    unordered_map<char*, unsigned> key2index;     // map 快速查找key在stats中的位置
    int findKey(char* key);
};


#endif //AC_AUTOMATION_AC_AUTOMATION_H
