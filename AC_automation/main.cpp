#include <iostream>
#include "AC_automation.h"
int main() {
    char* text = "helloworldcomeform";
    char* p[3] = {"llo", "rld", "orl"};
    AC_automation ac;
    for(int i = 0; i < 3; i++)
        ac.Insert(p[i]);
    ac.build();
    printf("match %d patterns\n", ac.match(text));
    return 0;
}
