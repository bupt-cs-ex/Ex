//
// Created by 王尚荣 on 2020/11/8.
//

#include "AC_automachine.h"

AC_automachine::AC_automachine():urls(List<char*>(100000)) {
    root = new Node();
}
/**
 * 插入模式串
 * @param pattern 模式串
 */
void AC_automachine::Insert(char *pattern) {
    if(pattern == nullptr)
        return;
    Node* p = root;
    for(int i = 0; i < strlen(pattern); i++) {
        int index = pattern[i] + 128;
        if(p->children[index] == nullptr) {
            p->children[index] = new Node();
        }
        p = p->children[index];
    }
    p->outputList.append(pattern);
    url_idx.insert({pattern, urls.size()});
    urls.append(pattern);
}
/**
 * 构造fail指针域
 */
int AC_automachine::Build() {
    queue q;
    Node* p;
    Node* temp;
    q.push_back(root);          // root节点入队
    while (!q.isEmpty()){
        temp = q.pop_front();   // 取出队列首元素
        for(int i = 0; i < 256; i++){
            if(temp->children[i]){
                if(temp == root){
                    // 根节点的所有子节点fail域为root
                    temp->children[i]->fail = root;
                }else{
                    p = temp->fail;
                    while (p){
                        // 若父节点的fail节点存在child[i] ，
                        // 则子节点的fail域指向父节点fail节点的子节点
                        if(p->children[i]){
                            temp->children[i]->fail = p->children[i];
                            break;
                        }
                        // 否则继续向上跳转
                        p = p->fail;
                    }
                    // 最终根节点的fail为nullptr ，则设置子节点的fail为root
                    if(p == nullptr)
                        temp->children[i]->fail = root;
                }
                // 构造fail结束后将child[i]入队
                q.push_back(temp->children[i]);
            }
        }
    }
    printf("patterns:%d\n", urls.size());
    return urls.size();
}

/**
 * 匹配
 * @param text  长文本串
 * @param base  偏移量
 * @param start 起始状态节点，若为nullptr，从root开始
 * @return      匹配之后的状态
 */
Node* AC_automachine::Match(char *text, Node* start) {
    Node* p = (start == nullptr ? root : start);
    for(int offset = 0; offset < strlen(text); offset++) {
        // 先查找是否存在child[index],不存在则跳转至fail
        int index = text[offset] + 128;
        while (p->children[index] == nullptr && p != root)
            p = p->fail;

        p = p->children[index];
        if(p == nullptr)
            p = root;
        Node* tmp = p;
        while(tmp != root){
            if(!tmp->outputList.isEmpty()){
                for(int i = 0; i < tmp->outputList.size(); i++){
                    int pos = findKey(tmp->outputList[i]);
                    match_result.append(pos);
                }
            }
            tmp = tmp->fail;
        }
    }
    return p;
}
/**
 * 快速查找key在key list中的位置
 * @param key  待查找key
 * @return
 */
int AC_automachine::findKey(char *key) {
    return url_idx[key];
}

AC_automachine::~AC_automachine() {
    for(int i = 0; i < urls.size(); i++)
        delete urls[i];
}
/**
 * 通过文本文件匹配
 * @param filename 文件名，带后缀
 * @param mode     打开模式
 */
List<unsigned int>* AC_automachine::MatchByFile(char *filename, char *mode) {
    FILE *infile = fopen(filename, mode);
    if(infile == nullptr){
        printf("Failed to open %s\n", filename);
        return nullptr;
    }
    clear();
    char buff[2048 + 1];
    Node* start = root;
    int idx = 0;
    while(!feof(infile)) {
        int ch = fgetc(infile);     //读取一个字符
        idx = 0;
        //从文件中读取字符到缓冲区
        while(ch != 0x0A && ch != -1) {
            buff[idx] = ch;
            ++idx;
            if(idx == 2048)
                break;
            ch = fgetc(infile);
        }
        buff[idx] = '\0';           //一次读取完成
        start = Match(buff,start);
    }
    fclose(infile);
    return &match_result;
}

void AC_automachine::clear() {
    match_result.clear();
}
