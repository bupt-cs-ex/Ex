//
// Created by 王尚荣 on 2020/10/14.
//

#include "AC_automachine.h"

AC_automachine::AC_automachine(int m) {
    this->m = m;
    root = new Node(m);
}
/**
 * 插入模式串
 * @param pattern 模式串
 */
void AC_automachine::Insert(char *pattern) {
    if(pattern == nullptr)
        return;
    Node* p = root;
    int patternBitLen = strlen(pattern) * 8;
    int nodeBitLen = getNodeBitSize();
    for(int bitPos = 0; bitPos < patternBitLen; bitPos += nodeBitLen) {
        int nodeIdx = getNodeIdx(pattern, bitPos, nodeBitLen);
        if(p->children[nodeIdx] == nullptr) {
            p->children[nodeIdx] = new Node(m);
        }
        p = p->children[nodeIdx];
    }

    p->outList.append(pattern);
    stats.append(new Stat(pattern));
    key2index.insert({pattern, stats.size() - 1 });
}
/**
 * 构造fail指针域
 */
void AC_automachine::Build() {
    queue q;
    Node* p;
    Node* temp;
    q.push_back(root);          // root节点入队
    while (!q.isEmpty()){
        temp = q.pop_front();   // 取出队列首元素
        for(int i = 0; i < m; i++){
            if(temp->children[i]){
                if(temp == root){
                    // 根节点的所有子节点fail域为root
                    temp->children[i]->fail = root;
                }else{
                    p = temp->fail;
                    while (p){
                        // 若父节点的fail节点存在child[i] ，
                        // 则子节点的fail域指向父节点fail节点下子节点的fail域
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
}

/**
 * 匹配
 * @param text  长文本串
 * @param start 起始状态节点，若为nullptr，从root开始
 * @return      匹配之后的状态
 */
Node* AC_automachine::Match(char *text, unsigned int base, Node* start) {
    Node* p = (start == nullptr ? root : start);
    int textBitLen = strlen(text) * 8;
    int nodeBitLen = getNodeBitSize();
    for(int bitPos = 0; bitPos < textBitLen; bitPos += nodeBitLen) {
        int nodeIdx = getNodeIdx(text, bitPos, nodeBitLen);
        // 先查找是否存在child[index],不存在则跳转至fail
        while (p->children[nodeIdx] == nullptr && p != root)
            p = p->fail;
        p = p->children[nodeIdx];
        if(p == nullptr)
            p = root;
        // 当前节点存在output list
        if(p != root && !p->outList.isEmpty()){
            // 查看output列表 ，添加到统计信息中
            for(int i = 0; i < p->outList.size(); i++){
                int pos = findKey(p->outList[i]);
                stats[pos]->count++;
                stats[pos]->offsetList.append((base + bitPos) / 8 - strlen(p->outList[i]) + 1);
            }
        }
    }
    return p;
}
/**
 * 格式化打印key word 统计信息
 */
void AC_automachine::OutputResult() {
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
int AC_automachine::findKey(char *key) {
    return key2index[key];
}

AC_automachine::~AC_automachine() {
    for(int i = 0; i < stats.size(); i++)
        delete stats[i];
}
/**
 * 通过文本文件匹配
 * @param filename 文件名，带后缀
 * @param mode     打开模式
 */
void AC_automachine::MatchByFile(char *filename, char *mode) {
    FILE *infile = fopen(filename, mode);
    if(infile == nullptr){
        printf("Failed to open %s\n", filename);
        return;
    }
    unsigned int base = 0;
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
        base += 2048 * 8;
    }
    fclose(infile);
}
/**
 * 输出结果到文件
 * @param filename 文件名，带后缀
 */
void AC_automachine::OutputToFile(char *filename) {
    int unique = 0;
    FILE *outfile = fopen(filename, "wb");
    if(outfile == nullptr) {
        printf("Failed to open %s\n", filename);
        return;
    }
    // 写入文件
    for(int i = 0; i < stats.size(); i++){
        if(stats[i]->count == 0)
            continue;
        unique++;
        fprintf(outfile, "%s\t%d\toffset: ",stats[i]->key, stats[i]->count);
//        for(int j = stats[i]->offsetList.size() - 1; j >= 0; j--)
//            fputc(stats[i]->offsetList[j], outfile);
        for(int j = 0; j < 3 && j < stats[i]->offsetList.size(); j++)
            fprintf(outfile, "%ud\t", stats[i]->offsetList[j]);
        fprintf(outfile, "\n");
    }
    printf("finished\n");
    printf("unique:%d\n", unique);
    fclose(outfile);
}
/**
 * 计算一个节点代表的比特数
 */
int AC_automachine::getNodeBitSize() {
    return int(log(m) / log(2));
}
/**
 * //获取关键词 key 在 curKeyBitPos 开始的 n(nodeBitSize) 位，对应的节点序号(即n bits二进制对应的数值)
 * @param key: 关键词
 * @param curKeyBitPos: 起始比特位
 * @param nodeBitSize: 比特长度
 */
int AC_automachine::getNodeIdx(char *key, int curKeyBitPos, int nodeBitSize) {
    int keyByteSize = strlen(key);
    int startKeyByte = curKeyBitPos / 8;
    int startBitPos = curKeyBitPos % 8;

    int endKeyByte = (curKeyBitPos + nodeBitSize - 1) / 8;
    int endBitPos = (curKeyBitPos + nodeBitSize - 1) % 8;
    endBitPos = endKeyByte >= keyByteSize ? 7 : endBitPos;
    endKeyByte = endKeyByte >= keyByteSize ? keyByteSize - 1 : endKeyByte;

    int nodeIdx = 0;
    for(int i = startKeyByte; i <= endKeyByte; ++i) {
        int start = i == startKeyByte ? startBitPos : 0;
        int end = i == endKeyByte ? endBitPos : 7;
        for(int j = start; j <= end; ++j) {
            int bitNum = (key[i] >> (8 - j - 1)) & 1;
            nodeIdx = nodeIdx * 2 + bitNum;
        }
    }
    return nodeIdx;
}