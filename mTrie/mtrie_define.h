//
// Created by wbj on 2020/10/4 0004.
//

#ifndef MTRIE_MTRIE_DEFINE_H
#define MTRIE_MTRIE_DEFINE_H
#include <math.h>
#include <string.h>

class MTrieNode
{
public:
    int m;                  //叉数，节点的分支数、子节点数
    bool isWord;            //是否为叶节点，即组成一个单词
    MTrieNode **children;   //指向子节点的指针

    MTrieNode(int m, bool isWord = false);
    ~MTrieNode();
};

class MTrie
{
public:
    MTrieNode* root;        //根节点
    int m;                  //叉数

    MTrie(int m);
    ~MTrie();
    int getBitSize();       //获取每个节点代表的比特位数 n，2^n = m
    void Insert(char *key); //插入一个词
    bool Find(char *key);   //查找一个词
    int getNodeIdx(char *key, int curKeyBitPos, int nodeBitSize);   //获取关键词 key 在 curKeyBitPos 开始的 n(nodeBitSize) 位，对应的节点序号(即n bits二进制对应的数值)
};

#endif //MTRIE_MTRIE_DEFINE_H
