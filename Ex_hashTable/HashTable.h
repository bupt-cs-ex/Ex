//
// Created by 王尚荣 on 2020/9/18.
//

#ifndef EX_HASHTABLE_HASHTABLE_H
#define EX_HASHTABLE_HASHTABLE_H

class Node{
public:
    char* pVal;
    int len;
    Node* pNext;
};
class HashTable {
public:
    HashTable(int n){
        table_size = n;
    }
private:
    int table_size;
    Node* table;
};


#endif //EX_HASHTABLE_HASHTABLE_H
