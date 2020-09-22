#include <cstdio>
#include <math.h>
#include "HashTable.h"
#include <time.h>
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
    clock_t start_time = clock();
    int n = pow(2, 17);
    unsigned int count = 0;
    HashTable tb = HashTable(n, SDBMHash);
    FILE *infile = fopen("../dict.txt", "rb");
    if(infile == NULL)
    {
        printf("Failed open dict.txt\n");
        return -1;
    }

    while(!feof(infile))
    {
        char buff[128];
        int ch = fgetc(infile);
        int idx = 0;
        while(ch != 0x0A && ch != -1)
        {
            buff[idx] = ch;
            ++idx;
            ch = fgetc(infile);
        }
        buff[idx] = '\0';
        tb.put(buff);
    }
    fclose(infile);
    printf("Finished read dict.txt\n");

    infile = fopen("../string.txt", "rb");
    FILE *outfile = fopen("../result.txt", "wb");
    if(infile == nullptr){
        printf("Failed open string.txt\n");
        return -1;
    }
    if(outfile == nullptr){
        printf("Failed open result.txt\n");
        return -1;
    }
    while(!feof(infile)){
        char buff[128];
        int ch = fgetc(infile);
        int idx = 0;
        while(ch != 0x0A && ch != -1){
            buff[idx] = ch;
            ++idx;
            ch = fgetc(infile);
        }
        buff[idx] = '\0';
        if(tb.find(buff)){
            fputs(buff, outfile);
            fputs("\n", outfile);
            count ++;
        }
    }
    clock_t end_time = clock();
    printf("Finished read string.txt\n");
    fclose(outfile);
    fclose(infile);
    printf("find %d keys, use %lu ms\n", count, (end_time - start_time) * 1000/CLOCKS_PER_SEC);
    return 0;
}
