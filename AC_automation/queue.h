//
// Created by 王尚荣 on 2020/10/15.
//

#ifndef AC_AUTOMATION_QUEUE_H
#define AC_AUTOMATION_QUEUE_H
#include <stdio.h>
#include <string.h>

class Node{
public:
Node(){
    memset(child, NULL, sizeof(Node*) * 26);
    fail = nullptr;
    sum = 0;
}
Node* child[26];
Node* fail;
int sum;
};

class queue {
public:
    queue(int n=16);
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
