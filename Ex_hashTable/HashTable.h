//
// Created by 王尚荣 on 2020/9/18.
//

#ifndef EX_HASHTABLE_HASHTABLE_H
#define EX_HASHTABLE_HASHTABLE_H
#include <string.h>
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
    HashTable(unsigned int n, unsigned int(*hash_func)(char* key)){
        size = n;
        sizemask = n - 1;
        table = new Node*[n];
        hashFunction = hash_func;
    }
    void put(char* key);
    bool find(char* key);
    ~HashTable(){
        for(unsigned i = 0; i < size; i++){
            if(table[i] != nullptr){
                freeNode(table[i]);
                table[i] = nullptr;
            }
        }
        delete []table;
    }
private:
    unsigned int size;                          //哈希表大小
    unsigned int sizemask;                      //哈希表大小掩码，用于计算索引值 size - 1
    Node** table;
    unsigned int (*hashFunction)(char* key);    //哈希函数
    void freeNode(Node* pNode);                 //释放节点空间
};


#endif //EX_HASHTABLE_HASHTABLE_H
