#include <iostream>
#include "BplusTree.h"

int main() {
    BplusTree tree(3);
    for(int i=1;i<9;i++){
        tree.Insert(i);
    }
    tree.FormatPrint();
    return 0;
}
