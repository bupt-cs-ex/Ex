//
// Created by 王尚荣 on 2020/10/14.
//

#include "AC_automation.h"

AC_automation::AC_automation() {
    root = new Node();
}
/**
 * 插入模式串
 * @param s 模式串
 */
void AC_automation::Insert(char *s) {
    if(s == nullptr)
        return;
    Node* p = root;
    for(int i = 0; i < strlen(s); i++){
        int index = s[i] - 'a';
        if(p->child[index] == nullptr){
            p->child[index] = new Node();
        }
        p = p->child[index];
    }
    p->sum++;
}
/**
 * 构造fail指针域
 */
void AC_automation::build() {
    queue q;
    Node* p;
    Node* temp;
    q.push_back(root);
    while (!q.isEmpty()){
        temp = q.pop_front();
        for(int i = 0;i < 26; i++){
            if(temp->child[i]){
                if(temp == root){
                    temp->child[i]->fail = root;
                }else{
                    p = temp->fail;
                    while (p){
                        if(p->child[i]){
                            temp->child[i]->fail = p->child[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if(p == nullptr)
                        temp->child[i]->fail = root;
                }
                q.push_back(temp->child[i]);
            }
        }
    }
}

int AC_automation::match(char *key) {
    int count = 0;
    Node* p = root;
    for(int i = 0; i < strlen(key); i++){
        int index = key[i] - 'a';
        while (p->child[index] == nullptr && p != root)
            p = p->fail;
        p = p->child[index];
        if(p == nullptr)
            p = root;
        Node* temp = p;
        while (temp != root){
            // 当前节点未被访问
            if(temp->sum >= 0){
                count += temp->sum;
                temp->sum = -1;
            }else
                break;
            temp = temp->fail;
        }
    }
    return count;
}
