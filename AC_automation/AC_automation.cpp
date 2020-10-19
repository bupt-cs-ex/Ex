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
 * @param start 起始状态节点，若为nullptr，从root开始
 * @return      匹配之后的状态
 */
Node* AC_automation::Match(char *text, int base, Node* start) {
    Node* p = (start == nullptr ? root:start);
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
                stats[pos]->offsetList.append(base + offset - strlen(p->outList[i]) + 1);
            }
        }
    }
    return p;
}
/**
 * 格式化打印key word 统计信息
 */
void AC_automation::OutputResult() {
    for(int i = 0; i < stats.size(); i++){
        printf("%s\t%-4d, offset: ", stats[i]->key, stats[i]->count);
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
/**
 * 通过文本文件匹配
 * @param filename 文件名，带后缀
 * @param mode     打开模式
 */
void AC_automation::MatchByFile(char *filename, char *mode) {
    FILE *infile = fopen(filename, mode);
    if(infile == nullptr){
        printf("Failed to open %s\n", filename);
        return;
    }
    int base = 0;
    char buff[2048 + 1];
    Node* start = root;
    while(!feof(infile)) {
        int ch = fgetc(infile);     //读取一个字符
        int idx = 0;
        //从文件中读取字符到缓冲区
        while(ch != -1 && idx < 2048) {
            buff[idx] = ch;
            ++idx;
            ch = fgetc(infile);
        }
        buff[idx] = '\0';           //一个keyword读取结束
        start = Match(buff, base, start);
        base += 2048;
    }
    fclose(infile);
}
/**
 * 输出结果到文件
 * @param filename 文件名，带后缀
 */
void AC_automation::OutputToFile(char *filename) {
    FILE *outfile = fopen(filename, "wb");
    if(outfile == nullptr) {
        printf("Failed to open %s\n", filename);
        return;
    }
    // 写入文件
    for(int i = 0; i < stats.size(); i++){
        fputs(stats[i]->key, outfile);
        fputs(" ", outfile);
        fputc(stats[i]->count, outfile);
        fputs("offset: ", outfile);
        // 逆序输出
        for(int j = stats[i]->offsetList.size() - 1; j >= 0; j--)
            fputc(stats[i]->offsetList[j], outfile);
        fputs("\n", outfile);
    }
    printf("finished\n");
    fclose(outfile);
}
