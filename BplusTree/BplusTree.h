//
// Created by 王尚荣 on 2020/9/26.
//

#ifndef BPLUSTREE_BPLUSTREE_H
#define BPLUSTREE_BPLUSTREE_H
#include <cstdlib>
#include <cstdio>

class TreeNode{
public:
    TreeNode(int m);
    int keyNums;
    int *Keys;
    TreeNode **child;
    TreeNode *next;
private:
    int M;
};

class BplusTree {
public:
    BplusTree(int m);
    void Insert(int key);
    bool Find(int key);
    void TraveData();
    void FormatPrint();

private:
    TreeNode* Recursive_Insert(TreeNode* T, int key, int i, TreeNode* parent);
    TreeNode* InsertElement(bool isKey, TreeNode* parent, TreeNode* T, int key, int i, int j);
    TreeNode* SplitNode(TreeNode* parent, TreeNode* T, int i);
    TreeNode* FindSibling(TreeNode* parent, int i);
    TreeNode* MoveElement(TreeNode* Src, TreeNode* Dst, TreeNode* parent, int i, int n);
    TreeNode* RemoveElement(bool isKey, TreeNode* parent, TreeNode* T, int i, int j);
    TreeNode* FindMostRight(TreeNode* T);
    TreeNode* FindMostLeft(TreeNode* T);
    bool FindByNode(TreeNode* node, int key);
    TreeNode* root;
    int M;
};


#endif //BPLUSTREE_BPLUSTREE_H
