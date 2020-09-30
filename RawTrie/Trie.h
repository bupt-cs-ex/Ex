//
// Created by 王尚荣 on 2020/9/28.
//

#ifndef RAWTRIE_TRIE_H
#define RAWTRIE_TRIE_H
#include <iostream>
/**
 * Trie树节点结构
 */
class TrieNode{
public:
    TrieNode(char v, bool isWord= false){
        memset(child, NULL, sizeof(child)/sizeof(TrieNode*));
        this->isWord = isWord;
        val = v;
    }
    ~TrieNode(){
        for(int i = 0; i < sizeof(child)/sizeof(TrieNode*); i++)
            delete child[i];
    }
    TrieNode* child[256];
    bool isWord;        // 是否为根节点
    char val;           // 记录当前节点表示的值
};
/**
 * Trie树结构
 */
class Trie {
public:
    Trie() {
        root = new TrieNode('\0', false);
    }
    void Insert(char* key);
    bool Find(char* key);
    void FormatPrint();
    ~Trie(){
        delete root;
    }
private:
    TrieNode* root;
private:
    bool Search(TrieNode* node, char* key, int pos);
};


#endif //RAWTRIE_TRIE_H
