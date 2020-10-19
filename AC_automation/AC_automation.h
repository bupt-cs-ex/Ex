//
// Created by 王尚荣 on 2020/10/14.
//

#ifndef AC_AUTOMATION_AC_AUTOMATION_H
#define AC_AUTOMATION_AC_AUTOMATION_H
#include <string.h>
#include <stdio.h>
#include "queue.h"
#include <map>
using namespace std;
class Stat{
public:
    Stat(char* k = nullptr){
        key = k;
        count = 0;
    }
    char* key;
    unsigned count;
    List<unsigned> offsetList;
};

class AC_automation {
public:
    AC_automation();
    ~AC_automation();
    void Insert(char* pattern);
    void Build();
    void Match(char* text);
    void OutputResult();
private:
    Node* root;
    List<Stat*> stats;       //统计信息
    map<char*, unsigned> key2index;
    int findKey(char* key);
};


#endif //AC_AUTOMATION_AC_AUTOMATION_H
