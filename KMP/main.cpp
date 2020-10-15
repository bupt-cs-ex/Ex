#include <iostream>
#include "Kmp.h"
int main() {
    char* s = "hellsaheqwohellodsah";
    char* p = "hello";
    std::cout<< KmpSearch(s,p)<<std::endl;
    return 0;
}
