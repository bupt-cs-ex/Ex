//
// Created by 王尚荣 on 2020/9/18.
//

#ifndef EX_HASHTABLE_HASHTABLE_H
#define EX_HASHTABLE_HASHTABLE_H
#include <string.h>
/**
 * 节点结构
 */
class Node {
public:
    Node() {
        pVal = nullptr;
        len = 0;
        pNext = nullptr;
    }
    char* pVal;        //记录存储的字符串地址
    int len;           //字符串长度
    Node* pNext;       //记录下一节点地址
};
/**
 * 哈希表结构
 */
class HashTable {
public:
    /**
     * 构造函数
     * @param n : 哈希表表长（桶数）
     * @param hash_func : 采用的hash函数
     */
    HashTable(unsigned int n, unsigned int(*hash_func)(char* key)) {
        size = n;
        sizemask = n - 1;
        table = new Node*[n];
        memset(table, 0, size);
        hashFunction = hash_func;
    }
    void put(char* key);
    bool find(char* key);
    ~HashTable() {
        for(unsigned i = 0; i < size; i++) {
            if(table[i] != nullptr) {
                freeNode(table[i]);
                table[i] = nullptr;
            }
        }
        delete []table;
    }
private:
    unsigned int size;                          //哈希表大小
    unsigned int sizemask;                      //哈希表大小掩码，用于计算索引值 size - 1
    Node** table;                               //哈希表头指针
    unsigned int (*hashFunction)(char* key);    //哈希函数
    void freeNode(Node* pNode);                 //释放节点空间
};


#endif //EX_HASHTABLE_HASHTABLE_H
