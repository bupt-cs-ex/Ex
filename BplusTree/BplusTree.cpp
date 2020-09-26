//
// Created by 王尚荣 on 2020/9/26.
//

#include "BplusTree.h"

TreeNode::TreeNode(int m) {
    M = m;
    keyNums = 0;
    Keys = new int[M + 1];
    child = new TreeNode*[M + 1];
    for(int i = 0; i <= M; i++) {
        child[i] = nullptr;
        Keys[i] = INT32_MAX;
    }
    next = nullptr;

}

BplusTree::BplusTree(int m) {
    if(m < 3)
        throw "m must be large than 3!";
    M = m;
    root = new TreeNode(M);
}

void BplusTree::Insert(int key) {
    Recursive_Insert(root, key, 0, nullptr);
}
/**
 * 递归插入key
 * @param T 插入的节点
 * @param key 插入的值
 * @param i 当前节点是其父节点的第i叉
 * @param parent 节点T的父节点
 */
TreeNode* BplusTree::Recursive_Insert(TreeNode* T, int key, int i, TreeNode* parent) {
    int j = 0;
    while(j < T->keyNums && key >= T->Keys[j]){
        if(key == T->Keys[j])
            return T;         //有重复的值，则无需插入
        j++;
    }
    if( j != 0 && T->child[0] != nullptr)
        j--;
    if(T->child[0] == nullptr){
        // T 是叶子节点
        T = InsertElement(true, parent, T, key, i, j);
    }else{
        // T 是索引节点
        Recursive_Insert(T->child[j], key, j, T);
    }
    //调整节点
    int Limit = M;
    TreeNode* Sibling = nullptr;
    if(T->keyNums > Limit){
        if(parent == nullptr){
            // T 为根节点的情况
            T = SplitNode(parent, T, i);
        }else{
            Sibling = FindSibling(parent, i);
            if(Sibling){
                // 存在有多余key空间的兄弟节点,将多出的一个元素移动过去
                MoveElement(T, Sibling, parent, i, 1);
            }else{
                // 兄弟节点没有空余key空间,分裂节点
                T = SplitNode(parent, T, i);
            }
        }

    }
    // 当有父节点时，更新父节点i处key的值
    if(parent){
        parent->Keys[i] = T->Keys[0];
    }
    return T;
}
/**
 * 对节点插入一个元素：对父节点插入T节点或者对T节点插入key值
 * @param isKey     插入的是值还是节点
 * @param parent    T节点的父节点
 * @param T         插入的节点
 * @param key       插入的值
 * @param i         对T节点插入值key时，i为T在parentd的位置,j为key要插入的位置
 * @param j         对parent节点插入T节点时，i为待插入的位置。j、key无用
 * @return
 */
TreeNode *BplusTree::InsertElement(bool isKey, TreeNode* parent, TreeNode* T, int key, int i, int j) {
    return nullptr;
}
/**
 * 分裂节点
 * @param parent    T节点的父节点
 * @param T         待分裂的节点
 * @param i         该节点在父节点的位置
 * @return          返回插入后的节点（若创建新根则返回新的根节点）
 */
TreeNode *BplusTree::SplitNode(TreeNode* parent, TreeNode* T, int i) {
    int j,k,Limit;
    TreeNode* newNode = new TreeNode(M);
    k = 0;
    j = T->keyNums / 2;
    Limit = T->keyNums;
    //将有半部分复制到新节点中
    while (j < Limit){
        if(T->child[0] != nullptr){
            //针对索引节点，复制其子节点指针
            newNode->child[k] = T->child[j];
            T->child[j] = nullptr;
        }
        newNode->Keys[k] = T->Keys[j];
        T->Keys[j] = INT32_MIN;
        newNode->keyNums++ ;
        T->keyNums--;
        k++;
        j++;
    }
    if(parent != nullptr){
        //将新节点插入到父节点中，位置是i+1 (当前节点的位置为i)
        InsertElement(false, parent, newNode, 0, i+1, 0);
    }else{
        //当前节点T为根节点，分裂之后则需要创建新的根节点
        parent = new TreeNode(M);
        //将两节点插入到根节点中的0，1位置上去
        InsertElement(false, parent, T, 0, 0, 0);
        InsertElement(false, parent, newNode, 0, 1, 0);
        return parent;
    }
    return T;
}
/**
 * 查找兄弟节点，其存储的key未满，否则返回nullptr
 * @param parent 父节点
 * @param i      当前节点在父节点的位置
 * @return       有多余key空间的兄弟节点或nullptr
 */
TreeNode *BplusTree::FindSibling(TreeNode *parent, int i) {
    TreeNode* Sibling = nullptr;
    int Limit = M;
    if(i == 0){
        if(parent->child[1]->keyNums < Limit)
            Sibling = parent->child[1];
    } else if(parent->child[i - 1]->keyNums < Limit)
        Sibling = parent->child[i - 1];
    else if(i+1 < parent->keyNums && parent->child[i + 1]->keyNums < Limit)
        Sibling = parent->child[i + 1];
    return Sibling;
}
/**
 * 移动元素， Src和Dst为相邻节点
 * @param Src       源节点
 * @param Dst       目的节点
 * @param parent    父节点
 * @param i         Src在父节点中的位置
 * @param n         移动元素的个数
 * @return          父节点
 */
TreeNode *BplusTree::MoveElement(TreeNode *Src, TreeNode *Dst, TreeNode *parent, int i, int n) {
    return nullptr;
}
