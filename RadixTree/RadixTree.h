//
// Created by wbj on 2020/10/5 0005.
//

#ifndef RADIXTREE_RADIXTREE_H
#define RADIXTREE_RADIXTREE_H
#include <string.h>
#include <stdio.h>

class RadixNode
{
public:
    unsigned char *value;
    int valBitLen;
    bool isWord;
    RadixNode *children[2];

    RadixNode();
    ~RadixNode();
};


class RadixTree
{
public:
    RadixNode *root;

    RadixTree();
    ~RadixTree();
    void Insert(char *key);
    bool Find(char *key);
    void copyBits(unsigned char *&destVal, unsigned char *oriVal, int oriBitsStart, int oriBitsEnd);
    int getFirstBit(unsigned char *key, int curBitIdx);
};

#endif //RADIXTREE_RADIXTREE_H
