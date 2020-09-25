#include <cstdio>
#include <math.h>
#include "HashTable.h"
#include "BloomFilter.h"
#include <time.h>
using namespace std;

unsigned int SDBMHash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

int hash_table_search_main();
int bloom_filter_main();

int main() {
    int exit_code = bloom_filter_main();
    return exit_code;
}

int hash_table_search_main(){
    clock_t start_time = clock();
    int n = pow(2, 17);
    unsigned int count = 0;
    HashTable tb = HashTable(n, SDBMHash);

    //��ȡ dict.txt �� keywords�����뵽��ϣ��
    FILE *infile = fopen("../dict.txt", "rb");
    if(infile == NULL) {
        printf("Failed to open dict.txt\n");
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
    printf("Finished reading dict.txt\n");

    //��ȡ string.txt �� keywords�����ҹ�ϣ�������ҵ��� keywords ����� result.txt
    infile = fopen("../string.txt", "rb");
    FILE *outfile = fopen("../result.txt", "wb");
    if(infile == nullptr) {
        printf("Failed to open string.txt\n");
        return -1;
    }
    if(outfile == nullptr) {
        printf("Failed to open result.txt\n");
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
    printf("Finished reading string.txt\n");
    fclose(outfile);
    fclose(infile);

    printf("Find %d keys, use %lu ms\n", count, (end_time - start_time) * 1000/CLOCKS_PER_SEC);
    return 0;
}
int bloom_filter_main(){
    srand(time(0));
    clock_t start_time = clock();
    unsigned int count = 0;
    BloomFilter bf(1270000, 0.0001);


    //��ȡ dict.txt �� keywords�����뵽��ϣ��
    FILE *infile = fopen("../dict.txt", "rb");
    if(infile == NULL) {
        printf("Failed to open dict.txt\n");
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
        bf.put(buff);               //�����ϣ��
    }
    fclose(infile);
    printf("Finished reading dict.txt\n");

    //��ȡ string.txt �� keywords�����ҹ�ϣ�������ҵ��� keywords ����� result.txt
    infile = fopen("../string.txt", "rb");
    FILE *outfile = fopen("../result.txt", "wb");
    if(infile == nullptr) {
        printf("Failed to open string.txt\n");
        return -1;
    }
    if(outfile == nullptr) {
        printf("Failed to open result.txt\n");
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
        if(bf.find(buff)) {         //��ϣ���в���keyword
            fputs(buff, outfile);
            fputs("\n", outfile);
            count ++;
        }
    }
    clock_t end_time = clock();
    printf("Finished reading string.txt\n");
    fclose(outfile);
    fclose(infile);

    printf("Find %d keys,use %lu ms\n", count, (end_time - start_time) * 1000/CLOCKS_PER_SEC);
    return 0;
}