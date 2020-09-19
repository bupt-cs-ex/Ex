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
    FILE *infile = fopen("../dict.txt", "rb");
    if(infile == NULL)
    {
        printf("Failed open dict.txt\n");
        return -1;
    }

    while(!feof(infile))
    {
        char buff[128];
        char ch = fgetc(infile);
        int idx = 0;
        while(ch != 0x0A)
        {
            buff[idx] = ch;
            ++idx;
            ch = fgetc(infile);
        }
        buff[idx] = '\0';
        printf("%s\n", buff);
    }

    fclose(infile);
    return 0;
}
