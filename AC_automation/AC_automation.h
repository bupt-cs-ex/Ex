//
// Created by 王尚荣 on 2020/10/14.
//

#ifndef AC_AUTOMATION_AC_AUTOMATION_H
#define AC_AUTOMATION_AC_AUTOMATION_H
#include <string.h>
#include <stdio.h>
#include "queue.h"

class AC_automation {
public:
    AC_automation();
    void Insert(char* s);
    void build();
    int match(char* key);
private:
    Node* root;
};


#endif //AC_AUTOMATION_AC_AUTOMATION_H
