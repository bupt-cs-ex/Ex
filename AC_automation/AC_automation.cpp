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
        int index = pattern[i] + 128;
        if(p->child[index] == nullptr){
            p->child[index] = new Node();
        }
        p = p->child[index];
    }
    p->outList.append(pattern);
    stats.append(new Stat(pattern));
    key2index.insert({pattern, stats.size() - 1 });
}
/**
 * 构造fail指针域
 */
void AC_automation::Build() {
    queue q;
    Node* p;
    Node* temp;
    q.push_back(root);          // root节点入队
    while (!q.isEmpty()){
        temp = q.pop_front();   // 取出队列首元素
        for(int i = 0;i < 256; i++){
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
void AC_automation::Match(char *text) {
    Node* p = root;
    for(int offset = 0; offset < strlen(text); offset++){
        int index = text[offset] + 128;
        // 先查找是否存在child[index],不存在则跳转至fail
        while (p->child[index] == nullptr && p != root)
            p = p->fail;
        p = p->child[index];
        if(p == nullptr)
            p = root;
        // 当前节点存在output list
        if(p != root && !p->outList.isEmpty()){
            // 查看output列表 ，添加到统计信息中
            for(int i = 0; i < p->outList.size(); i++){
                int pos = findKey(p->outList[i]);
                stats[pos]->count++;
                stats[pos]->offsetList.append(offset - strlen(p->outList[i]) + 1);
            }
        }

    }
}
/**
 * 格式化打印key word 统计信息
 */
void AC_automation::OutputResult() {
    for(int i = 0; i < stats.size(); i++){
        printf("%-10s %-4d, offset: ", stats[i]->key, stats[i]->count);
        // 逆序输出
        for(int j = stats[i]->offsetList.size() - 1; j >= 0; j--)
            printf("%d ",stats[i]->offsetList[j]);
        printf("\n");
    }
}
/**
 * 快速查找key在key list中的位置
 * @param key  待查找key
 * @return
 */
int AC_automation::findKey(char *key) {
    return key2index[key];
}

AC_automation::~AC_automation() {
    for(int i = 0; i < stats.size(); i++)
        delete stats[i];
}
