//
// Created by 王尚荣 on 2020/11/7.
//

#ifndef BUILDGRAPH_AUTO_MACHINE
#define BUILDGRAPH_AUTO_MACHINE
#include "List.h"
#include <string>
#include <vector>
using namespace std;

/**
 * 自动机
 * 用于匹配html网页中所有的 http://new.souhu.com/*.shtml 链接
 */
class AutoMachine{
    static string URL;
    static string path;
public:
    AutoMachine(string path){
        AutoMachine::path = path;
        init();
    }
    ~AutoMachine(){
//        for(int i = 0; i < result.size(); i++)
//            result[i] = nullptr;
    }
    void init();
    void match(char* text);
    void print();
public:
//    List<char*> result;     // 当前匹配到的有效url
    vector<char*> result;
private:
    char buff[256];         // 当前缓冲区
    int idx;                // 当前缓冲区位置
    int match_idx;          // 匹配到的位置
    bool isStart;           // 是否进行匹配

private:
    void _next(char c);

};


#endif //BUILDGRAPH_AUTO_MACHINE