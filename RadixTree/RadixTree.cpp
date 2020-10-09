//
// Created by edwin on 2020/10/5 0005.
//
#include "RadixTree.h"

RadixNode::RadixNode()
{
    value = nullptr;
    valBitLen = 0;
    isWord = false;
    children[0] = nullptr;
    children[1] = nullptr;
}

RadixNode::~RadixNode()
{
    if(value != nullptr)
    {
        delete []value;
        value = nullptr;
    }

    delete children[0];
    children[0] = nullptr;

    delete children[1];
    children[1] = nullptr;
}


RadixTree::RadixTree()
{
    root = new RadixNode();
}

RadixTree::~RadixTree()
{
    delete root;
}

void RadixTree::Insert(char *key)
{
    if(key == nullptr || strlen(key) == 0)
        return;

    int keyBitsLen = strlen(key) * 8;   //key 的 bits 长度

    RadixNode *preNode = root;
    RadixNode *curNode;
    int keyBitIdx = 0;
    //获取关键词 key 当前遍历到的 bit 位，决定与 0 子树还是 1 子树比较
    int firstKeyBit = getFirstBit(reinterpret_cast<unsigned char*> (key), keyBitIdx);
    curNode = preNode->children[firstKeyBit];
    while(keyBitIdx < keyBitsLen)
    {
        firstKeyBit = getFirstBit(reinterpret_cast<unsigned char*> (key), keyBitIdx);

        if(curNode == nullptr)          //比较的节点为空，则新建节点，拷贝 key 剩余部分，遍历结束
        {
            curNode = new RadixNode();
            curNode->valBitLen = keyBitsLen - keyBitIdx;
            copyBits(curNode->value, reinterpret_cast<unsigned char*> (key), keyBitIdx, keyBitsLen);

            //插入完成，结束遍历
            //firstKeyBit = getFirstBit(reinterpret_cast<unsigned char*> (key), keyBitIdx);
            preNode->children[firstKeyBit] = curNode;
            keyBitIdx = keyBitsLen;
            curNode->isWord = true;
        }
        else                            //逐比特比较节点的值和key的值
        {
            int nodeBitIdx = 0;
            int curKeyBit = getFirstBit(reinterpret_cast<unsigned char*> (key), keyBitIdx);
            int curNodeBit = getFirstBit(curNode->value, nodeBitIdx);
            //逐比特比较节点的值和key的值
            while((nodeBitIdx < curNode->valBitLen) && (keyBitIdx < keyBitsLen) && (curKeyBit == curNodeBit))
            {
                ++keyBitIdx;
                ++nodeBitIdx;
                if(keyBitIdx < keyBitsLen)
                    curKeyBit = getFirstBit(reinterpret_cast<unsigned char*> (key), keyBitIdx);
                if(nodeBitIdx < curNode->valBitLen)
                    curNodeBit = getFirstBit(curNode->value, nodeBitIdx);
            }

            //因出现比较的bit值不同而退出循环的情况
            if(keyBitIdx < keyBitsLen && nodeBitIdx < curNode->valBitLen && curKeyBit != curNodeBit)
            {
                //生成一个前缀节点以存储公共前缀
                RadixNode *prefixNode = new RadixNode();
                prefixNode->valBitLen = nodeBitIdx;
                copyBits(prefixNode->value, curNode->value, 0, nodeBitIdx);

                //将 curNode 的value值去掉公共前缀
                unsigned char *remainVal = nullptr;
                copyBits(remainVal, curNode->value, nodeBitIdx, curNode->valBitLen);
                delete [](curNode->value);
                curNode->value = remainVal;
                curNode->valBitLen = curNode->valBitLen - nodeBitIdx;

                //生成新的子节点存储 keyword 的剩余(后缀)部分
                RadixNode *suffixNode = new RadixNode();
                suffixNode->valBitLen = keyBitsLen - keyBitIdx;
                copyBits(suffixNode->value, reinterpret_cast<unsigned char*> (key), keyBitIdx, keyBitsLen);
                suffixNode->isWord = true;      //该后缀节点代表 keyword 这个词

                //插入前缀节点
                preNode->children[firstKeyBit] = prefixNode;
                //preNode = prefixNode;
                prefixNode->children[curNodeBit] = curNode;

                //插入新生成的 keyword 后缀子节点
                prefixNode->children[curKeyBit] = suffixNode;

                //插入完成，结束遍历字符串的bits
                keyBitIdx = keyBitsLen;
            }

            //因 keyword 先遍历结束，但 curNode->value 未遍历完，而退出循环的情况
            else if(keyBitIdx >= keyBitsLen && nodeBitIdx < curNode->valBitLen)
            {
                //生成 curNode->value 的后缀的节点（去掉公共前缀，即去掉整个 keyword 的值），代表原本的 curNode 表示的的词
                RadixNode *suffixNode = new RadixNode();
                suffixNode->valBitLen = curNode->valBitLen - nodeBitIdx;
                copyBits(suffixNode->value, curNode->value, nodeBitIdx, curNode->valBitLen);
                suffixNode->isWord = true;

                //修改 curNode->value 值为公共前缀，即keyword，代表keyword这个词
                unsigned char *prefixVal = nullptr;
                copyBits(prefixVal, curNode->value, 0, nodeBitIdx);
                delete [](curNode->value);
                curNode->value = prefixVal;
                curNode->valBitLen = nodeBitIdx;

                //插入后缀节点
                //preNode = curNode;
                curNode->children[curNodeBit] = suffixNode;
                //curNode = curNode->children[curNodeBit];

                //插入完成，结束遍历字符串的bits
                //keyBitIdx = keyBitsLen;     //本身已成立，可不加
            }

            //keyword 和 curNode->value 的 bit 位同时遍历完 而退出循环的情况
            else if(keyBitIdx >= keyBitsLen && nodeBitIdx >= curNode->valBitLen)
            {
                curNode->isWord = true;
                //插入完成，结束遍历
                keyBitIdx = keyBitsLen;     //本身已成立，可不加
            }

            //因 curNode->value 的bits先遍历结束，但 keyword 未遍历完，而退出循环的情况
            else if(keyBitIdx < keyBitsLen && nodeBitIdx >= curNode->valBitLen)
            {
                preNode = curNode;
                curNode = curNode->children[curKeyBit];
                //keyBitIdx不变，定位到当前遍历到的位置
                //继续循环遍历，kyeword剩余部分与下一层节点进行比较
            }
        }
    }
}

bool RadixTree::Find(char *key)
{
    if(key == nullptr || strlen(key) == 0)
        return false;

    int keyBitsLen = strlen(key) * 8;
    RadixNode * curNode;
    int keyBitIdx = 0;
    int firstKeyBit = getFirstBit(reinterpret_cast<unsigned char*>(key), keyBitIdx);
    curNode = root->children[firstKeyBit];
    while(keyBitIdx < keyBitsLen)
    {
        if(curNode == nullptr)
            return false;

        int nodeBitIdx = 0;
        int curKeyBit = getFirstBit(reinterpret_cast<unsigned char*> (key), keyBitIdx);
        int curNodeBit = getFirstBit(curNode->value, nodeBitIdx);
        //逐比特比较节点的值和key的值
        while((nodeBitIdx < curNode->valBitLen) && (keyBitIdx < keyBitsLen) && (curKeyBit == curNodeBit))
        {
            ++keyBitIdx;
            ++nodeBitIdx;
            if(keyBitIdx < keyBitsLen)
                curKeyBit = getFirstBit(reinterpret_cast<unsigned char*> (key), keyBitIdx);
            if(nodeBitIdx < curNode->valBitLen)
                curNodeBit = getFirstBit(curNode->value, nodeBitIdx);
        }

        //因出现比较的bit值不同而退出循环的情况
        if(keyBitIdx < keyBitsLen && nodeBitIdx < curNode->valBitLen && curKeyBit != curNodeBit)
            return false;

        //因 keyword 先遍历结束，但 curNode->value 未遍历完，而退出循环的情况
        else if(keyBitIdx >= keyBitsLen && nodeBitIdx < curNode->valBitLen)

            return false;

        //keyword 和 curNode->value 的 bit 位同时遍历完 而退出循环的情况
        else if(keyBitIdx >= keyBitsLen && nodeBitIdx >= curNode->valBitLen)
            return curNode->isWord;

        //因 curNode->value 的bits先遍历结束，但 keyword 未遍历完，而退出循环的情况
        else if(keyBitIdx < keyBitsLen && nodeBitIdx >= curNode->valBitLen)
            curNode = curNode->children[curKeyBit];
    }
}

void RadixTree::copyBits(unsigned char *&destVal, unsigned char *oriVal, int oriBitsStart, int oriBitsEnd)
{
    if(destVal != nullptr && destVal != oriVal) //非空且不是自拷贝
    {
        delete []destVal;
    }
    int bitsLen = oriBitsEnd - oriBitsStart;
    int bytesLen = bitsLen / 8 + 1;
    destVal = new unsigned char[bytesLen];
    memset(destVal, 0, bytesLen);

    for(int i = 0; i < bitsLen; ++i)
    {
        //取 oriVal 的 1bit
        int oriBitNum = getFirstBit(oriVal, oriBitsStart + i);

        int destByteIdx = i / 8;
        int destByteBitIdx = i % 8;

        //将取出的 1bit 拷贝给 destVal
        if(oriBitNum == 0)
        {
            unsigned char maskBits = ~(1 << (8 - destByteBitIdx - 1));
            destVal[destByteIdx] = destVal[destByteIdx] & maskBits;
        }
        else if(oriBitNum == 1)
        {
            unsigned char maskBits = 1 << (8 - destByteBitIdx - 1);
            destVal[destByteIdx] = destVal[destByteIdx] | maskBits;
        }
    }
}

int RadixTree::getFirstBit(unsigned char *key, int curBitIdx)    //得到key字符串curBitIdx比特位的值
{
    int ByteIdx = curBitIdx / 8;
    int ByteBitIdx = curBitIdx % 8;
    int bitNum = (key[ByteIdx] >> (8 - ByteBitIdx - 1)) & 1;

    return bitNum;
}