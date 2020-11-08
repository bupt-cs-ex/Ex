//
// Created by 王尚荣 on 2020/11/7.
//

#ifndef BUILDGRAPH_AUTO_MACHINE
#define BUILDGRAPH_AUTO_MACHINE
#include "List.h"
#include <string>
using namespace std;

/**
 * 自动机
 * 用于匹配html网页中所有的 http://new.souhu.com/*.shtml 链接
 */
class AutoMachine{
    static string URL;
public:
    AutoMachine(string path){
        this->path = path;
        init();
    }
    void init();
    void match(char* text);
    void print();
public:
    List<char*> result;     // 当前匹配到的有效url
private:
    char buff[256];         // 当前缓冲区
    int idx;                // 当前缓冲区位置
    int match_idx;          // 匹配到的位置
    string path;            // 当前html文件的路径
    bool isStart;           // 是否进行匹配

private:
    void _next(char c);

};


#endif //BUILDGRAPH_AUTO_MACHINE