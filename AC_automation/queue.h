//
// Created by 王尚荣 on 2020/10/15.
//

#ifndef AC_AUTOMATION_QUEUE_H
#define AC_AUTOMATION_QUEUE_H
#include <stdio.h>
#include <string.h>
#include "List.h"
/**
 * AC自动机的节点结构
 */
class Node{
public:
    Node(int m = 4){
        this->m = m;
        children = new Node* [m];
        for(int i = 0; i < m; ++i) {
            children[i] = nullptr;
        }
        fail = nullptr;
    }
    ~Node(){
        for(int i = 0; i < m; ++i)
            delete children[i];
        delete [] children;
    }
    int m;                  // 分叉数
    Node** children;
    Node* fail;
    List<char*> outList;    // 当前节点的输出列表
};

/**
 * 循环队列，用于dfs构建AC自动机的fail域
 */
class queue {
public:
    queue(int n=2048);
    ~queue();
    void push_back(Node* p);
    Node* front();
    Node* back();
    Node* pop_front();
    bool isEmpty();
private:
    int capacity;       // 容量
    int length;         // 当前数组长度
    int head;           // 队列首
    int tail;           // 队列尾
    Node** array;

    void reSize();      // 队列加倍
};


#endif //AC_AUTOMATION_QUEUE_H
