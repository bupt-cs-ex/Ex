//
// Created by 王尚荣 on 2020/9/18.
//

#include "HashTable.h"
void HashTable::put(char* key) {
    unsigned int hash = hashFunction(key);
    unsigned int index = hash & sizemask;
    Node* node = new Node();
    node->pVal = key;
    node->pNext = table[index];
    table[index] = node;
}

bool HashTable::find(char* key) {
    unsigned int hash = hashFunction(key);
    unsigned int index = hash & sizemask;
    if(table[index] == nullptr)
        return false;
    Node* p = table[index];
    while(p != nullptr){
        if(strcmp(p->pVal, key) == 0)
            return true;
        p = p->pNext;
    }
    return false;
}

void HashTable::freeNode(Node *pNode) {
    if(pNode->pNext != nullptr)
        freeNode(pNode->pNext);
    delete pNode;
}