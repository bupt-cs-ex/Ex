//
// Created by 王尚荣 on 2020/9/28.
//

#include "Trie.h"
#include <queue>
using namespace std;
/**
 * 插入key
 * @param key 待插入的字符串
 */
void Trie::Insert(char *key) {
    if(key == nullptr || strlen(key) == 0)
        return;
    TrieNode* cur = root;
    int len = strlen(key);
    for(int i = 0; i < len; i++){
        int index = key[i] + 128;
        if(!cur->child[index])
            cur->child[index] = new TrieNode(key[i]);
        cur = cur->child[index];
    }
    cur->isWord = true;
}

bool Trie::Find(char *key) {
    return Search(root, key, 0);
}
/**
 * 在节点中查找从key[index:]是否存在
 * @param node      开始节点
 * @param key       查找的字符串
 * @param pos       从key[pos]开始查找
 * @return          是否存在;
 */
bool Trie::Search(TrieNode *node, char *key, int pos) {
    if(strlen(key) == 0)
        return false;
    int index = key[pos] + 128;
    TrieNode* cur = node->child[index];
    if(!cur)
        return false;
    if(pos == strlen(key) - 1)
        return cur->isWord;
    return Search(cur, key, pos + 1);
}
/**
 * 格式化打印树形结构
 */
void Trie::FormatPrint() {
    queue<pair<TrieNode*, int>> q;
    int level = 0;
    q.push({root, level});
    while(!q.empty()){
        auto m = q.front();
        q.pop();
        if(!m.first)
            continue;
        TrieNode* p = m.first;
        int cur_level = m.second;
        if(cur_level > level){
            printf("\n");
            level = cur_level;
        }
        printf("[");
        for(int i = 0; i < sizeof(p->child)/sizeof(TrieNode*); i++){
            if(p->child[i]){
                printf("%c,", i - 128);
                q.push({p->child[i], level + 1});
            }
        }
        printf("] ");
    }
}

