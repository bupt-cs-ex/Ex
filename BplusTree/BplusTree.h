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

private:
    TreeNode* Recursive_Insert(TreeNode* T, int key, int i, TreeNode* parent);
    TreeNode* InsertElement(bool isKey, TreeNode* parent, TreeNode* T, int key, int i, int j);
    TreeNode* SplitNode(TreeNode* parent, TreeNode* T, int i);
    TreeNode* FindSibling(TreeNode* parent, int i);
    TreeNode* MoveElement(TreeNode* Src, TreeNode* Dst, TreeNode* parent, int i, int n);
    TreeNode* root;
    int M;
};


#endif //BPLUSTREE_BPLUSTREE_H
