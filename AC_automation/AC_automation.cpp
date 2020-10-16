//
// Created by 王尚荣 on 2020/10/14.
//

#include "AC_automation.h"

AC_automation::AC_automation() {
    root = new Node();
}
/**
 * 插入模式串
 * @param pattern 模式串
 */
void AC_automation::Insert(char *pattern) {
    if(pattern == nullptr)
        return;
    Node* p = root;
    for(int i = 0; i < strlen(pattern); i++){
        int index = pattern[i] - 'a';
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
    q.push_back(root);          // root节点入队
    while (!q.isEmpty()){
        temp = q.pop_front();   // 取出队列首元素
        for(int i = 0;i < 26; i++){
            if(temp->child[i]){
                if(temp == root){
                    // 根节点的所有子节点fail域为root
                    temp->child[i]->fail = root;
                }else{
                    p = temp->fail;
                    while (p){
                        // 若父节点的fail节点存在child[i] ，
                        // 则子节点的fail域指向父节点fail节点下子节点的fail域
                        if(p->child[i]){
                            temp->child[i]->fail = p->child[i];
                            break;
                        }
                        // 否则继续向上跳转
                        p = p->fail;
                    }
                    // 最终根节点的fail为nullptr ，则设置子节点的fail为root
                    if(p == nullptr)
                        temp->child[i]->fail = root;
                }
                // 构造fail结束后将child[i]入队
                q.push_back(temp->child[i]);
            }
        }
    }
}

/**
 * 匹配
 * @param text  长文本串
 * @return      匹配成功的模式串个数
 */
int AC_automation::match(char *text) {
    int count = 0;
    Node* p = root;
    for(int i = 0; i < strlen(text); i++){
        int index = text[i] - 'a';
        // 先查找是否存在child[index],不存在则跳转至fail
        while (p->child[index] == nullptr && p != root)
            p = p->fail;
        p = p->child[index];
        if(p == nullptr)
            p = root;           //完全找不到匹配的单词，则跳回根节点，匹配下一个词
        Node* temp = p;
        while (temp != root){
            // 当前节点未被访问过
            if(temp->sum >= 0){
                // 累加当前节点包含的模式串个数，然后将其置为-1，避免重复计算
                count += temp->sum;
                temp->sum = -1;
            }else
                break;  // 当前节点被访问过，跳出
            temp = temp->fail;
        }
    }
    return count;
}
