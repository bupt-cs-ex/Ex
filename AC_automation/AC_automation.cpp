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
    Node* parent;
    Node* temp;
    q.push_back(root);
    while (!q.isEmpty()){
        temp = q.pop_front();
        for(int i = 0;i < 26; i++){
            if(temp->child[i]){
                if(temp == root){
                    temp->child[i]->fail = root;
                }else{
                    parent = temp->fail;
                    while (parent){
                        if(parent->child[i]){
                            temp->child[i]->fail = parent->child[i];
                            break;
                        }
                        parent = parent->fail;
                    }
                    if(parent == nullptr)
                        temp->child[i]->fail = root;
                }
                q.push_back(temp->child[i]);
            }
        }
    }
}
