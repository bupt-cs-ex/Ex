#include <cstdio>
#include <math.h>
#include "HashTable.h"
#include <time.h>
#include <unistd.h>
using namespace std;

unsigned int SDBMHash(char *str) {
    unsigned int hash = 0;

    while (*str) {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

int main() {
    int pid = getpid();
    clock_t start_time = clock();
    int n = pow(2, 17);
    unsigned int count = 0;
    HashTable tb = HashTable(n, SDBMHash);

    //��ȡ dict.txt �� keywords�����뵽��ϣ��
    FILE *infile = fopen("../dict.txt", "rb");
    if(infile == NULL) {
        //printf("Failed to open dict.txt\n");
        return -1;
    }
    while(!feof(infile)) {
        char buff[128];             //���ڴ洢һ��keyword
        int ch = fgetc(infile);     //��ȡһ���ַ�
        int idx = 0;
        //�����ȡ�ַ���ֱ����β���ļ�β
        while(ch != 0x0A && ch != -1) {
            buff[idx] = ch;
            ++idx;
            ch = fgetc(infile);
        }
        buff[idx] = '\0';           //һ��keyword��ȡ����
        tb.put(buff);               //�����ϣ��
    }
    fclose(infile);
    //printf("Finished reading dict.txt\n");

    //��ȡ string.txt �� keywords�����ҹ�ϣ�������ҵ��� keywords ����� result.txt
    infile = fopen("../string.txt", "rb");
    FILE *outfile = fopen("../bupt_03.txt", "wb");
    if(infile == nullptr) {
        //printf("Failed to open string.txt\n");
        return -1;
    }
    if(outfile == nullptr) {
        //printf("Failed to open result.txt\n");
        return -1;
    }
    while(!feof(infile)) {
        char buff[128];
        int ch = fgetc(infile);     //���ڴ洢һ��keyword
        int idx = 0;                //��ȡһ���ַ�
        //�����ȡ�ַ���ֱ����β���ļ�β
        while(ch != 0x0A && ch != -1) {
            buff[idx] = ch;
            ++idx;
            ch = fgetc(infile);
        }
        buff[idx] = '\0';           //һ��keyword��ȡ����
        if(tb.find(buff)) {         //��ϣ���в���keyword
            fputs(buff, outfile);
            fputs("\n", outfile);
            count ++;
        }
    }
    clock_t end_time = clock();
    //printf("Finished reading string.txt\n");
    fclose(outfile);
    fclose(infile);

    printf("\nruntime: %lu ms, string_match: %d\n", (end_time - start_time) * 1000/CLOCKS_PER_SEC, count);
    sleep(3);
    return 0;
}
