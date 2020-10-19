#include <iostream>
#include "AC_automation.h"
int main() {
    char* text = "helloworldcomeformllo";
    char* p[5] = {"llo", "rlds", "orld", "orl", "ll"};
    AC_automation ac;
    for(int i = 0; i < 5; i++)
        ac.Insert(p[i]);
    ac.Build();
    ac.Match(text);
    ac.OutputResult();
    return 0;
}
