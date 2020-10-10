//
// Created by wbj on 2020/10/4 0004.
//

#include "mtrie_define.h"

MTrieNode::MTrieNode(int m, bool isWord)
{
    this->m = m;
    this->isWord = isWord;

    children = new MTrieNode *[m];
    for(int i = 0; i < m; ++i)
    {
        children[i] = nullptr;
    }
}

MTrieNode::~MTrieNode()
{
    for(int i = 0; i < m; ++i)
    {
        delete children[i];
    }
    delete []children;
}


MTrie::MTrie(int m)
{
    this->m = m;
    root = new MTrieNode(m, false);
}

MTrie::~MTrie()
{
    delete root;
}

//获取每个节点代表的比特位数 n，2^n = m
int MTrie::getBitSize()
{
    return int(log(m) / log(2));
}

//插入一个词
void MTrie::Insert(char *key)
{
    if(key == nullptr || strlen(key) == 0)
        return;

    MTrieNode *cur = root;
    int keyByteSize = strlen(key);
    int nodeBitSize = getBitSize();
    for(int bitPos = 0; bitPos < keyByteSize * 8; bitPos += nodeBitSize)
    {
        int nodeIdx = getNodeIdx(key, bitPos, nodeBitSize);

        if(cur->children[nodeIdx] == nullptr)
        {
            cur->children[nodeIdx] = new MTrieNode(m, false);
        }
        cur = cur->children[nodeIdx];
    }
    cur->isWord = true;
}

//查找一个词
bool MTrie::Find(char *key)
{
    if(key == nullptr || strlen(key) == 0)
        return false;

    MTrieNode *cur = root;
    int keyByteSize = strlen(key);
    int nodeBitSize = getBitSize();
    for(int bitPos = 0; bitPos < keyByteSize * 8; bitPos += nodeBitSize)
    {
        int nodeIdx = getNodeIdx(key, bitPos, nodeBitSize);
        if(cur->children[nodeIdx] == nullptr)
        {
            return false;
        }
        else
        {
            cur = cur->children[nodeIdx];
        }
    }

    return cur->isWord;
}


//根据关键词 key 在 curKeyBitPos 开始的 n(nodeBitSize) 位bit，得到对应的节点序号(即n bits二进制对应的数值)
int MTrie::getNodeIdx(char *key, int curKeyBitPos, int nodeBitSize)
{
    int keyByteSize = strlen(key);
    int startKeyByte = curKeyBitPos / 8;
    int startBitPos = curKeyBitPos % 8;

    int endKeyByte = (curKeyBitPos + nodeBitSize - 1) / 8;
    int endBitPos = (curKeyBitPos + nodeBitSize - 1) % 8;
    endBitPos = endKeyByte >= keyByteSize ? 7 : endBitPos;
    endKeyByte = endKeyByte >= keyByteSize ? keyByteSize - 1 : endKeyByte;

    int nodeIdx = 0;
    for(int i = startKeyByte; i <= endKeyByte; ++i)
    {
        int start = i == startKeyByte ? startBitPos : 0;
        int end = i == endKeyByte ? endBitPos : 7;
        for(int j = start; j <= end; ++j)
        {
            int bitNum = (key[i] >> (8 - j - 1)) & 1;
            nodeIdx = nodeIdx * 2 + bitNum;
        }
    }
    return nodeIdx;
}