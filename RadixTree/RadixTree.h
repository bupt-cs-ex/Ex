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
    unsigned char *value;       //指向节点代表的比特串
    int valBitLen;              //节点代表的比特串的bits长度
    bool isWord;                //是否代表一个词（叶节点）
    RadixNode *children[2];     //指向两个子节点的指针

    RadixNode();
    ~RadixNode();
};


class RadixTree
{
public:
    RadixNode *root;            //指向根节点的指针

    RadixTree();
    ~RadixTree();
    void Insert(char *key);     //将单词 key 插入Radix Tree
    bool Find(char *key);       //从 Radix Tree 种查找单词 key 是否存在
    void copyBits(unsigned char *&destVal, unsigned char *oriVal, int oriBitsStart, int oriBitsEnd);    //将 orival 指向数组的指定比特位拷贝赋值给 destval 指向的数组
    int getFirstBit(unsigned char *key, int curBitIdx);     //获取单词 key 的第 curBitIdx 个比特位
};

#endif //RADIXTREE_RADIXTREE_H
