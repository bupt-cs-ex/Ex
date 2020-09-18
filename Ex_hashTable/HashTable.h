//
// Created by 王尚荣 on 2020/9/18.
//

#ifndef EX_HASHTABLE_HASHTABLE_H
#define EX_HASHTABLE_HASHTABLE_H

class Node{
public:
    Node(){
        pVal = nullptr;
        len = 0;
        pNext = nullptr;
    }
    char* pVal;
    int len;
    Node* pNext;
};
class HashTable {
public:
    HashTable(unsigned long n, unsigned int(*hash_func)(const void* key)){
        size = n;
        sizemask = n - 1;
        table = new Node[n];
        hashFunction = hash_func;
    }
    void put(char* key);
    ~HashTable(){
        delete []table;
    }
private:
    unsigned long size;                                 //哈希表大小
    unsigned long sizemask;                             //哈希表大小掩码，用于计算索引值 size - 1
    Node* table;
    unsigned int (*hashFunction)(const void* key);      //哈希函数
};


#endif //EX_HASHTABLE_HASHTABLE_H
