#include <iostream>
#include <stdlib.h>
#include "HashTable.h"
using namespace std;
unsigned int SDBMHash(char *str)
{
    unsigned int hash = 0;

    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

int main() {
    int n = 128;
    HashTable hs = HashTable(n, SDBMHash);
    FILE *infile = fopen("dict.txt", "rb");
    int buff_len = 128;
    unsigned char buff[buff_len];
    if(infile == nullptr){
        cout <<"打开dict.txt失败" << endl;
        return -1;
    }
    int rc = 0;
    while((rc = fread(buff, sizeof(unsigned char), 1024, infile)) != 0){
        cout<<buff<<endl;
    }
    fclose(infile);
    return 0;
}
