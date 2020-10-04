#include <cstdio>
#include <math.h>
#include "BloomFilter.h"
#include <time.h>
#include <unistd.h>
using namespace std;

int main() {
    srand(time(0));
    clock_t start_time = clock();
    unsigned int count = 0;
    double errors[3] = {0.0001, 0.00001, 0.000001};     //������

    int i = 0;
    for(i = 0; i < 3; ++i)
    {
        BloomFilter bf(1270000, errors[i]);
        count = 0;

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
            bf.put(buff);               //�����ϣ��
        }
        fclose(infile);
        //printf("Finished reading dict.txt\n");

        //��ȡ string.txt �� keywords�����ҹ�ϣ�������ҵ��� keywords ����� result.txt
        infile = fopen("../string.txt", "rb");
        char outfile_name[100];
        sprintf(outfile_name, "../bupt_03_%d.txt", i);
        FILE *outfile = fopen(outfile_name, "wb");
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
            if(bf.find(buff)) {         //��ϣ���в���keyword
                fputs(buff, outfile);
                fputs("\n", outfile);
                count ++;
            }
        }
        //printf("Finished reading string.txt\n");
        fclose(outfile);
        fclose(infile);

        printf("Error rate: %f, string_match: %d\n\n", errors[i], count);
    }

    clock_t end_time = clock();
    printf("runtime: %lu ms\n", (end_time - start_time) * 1000/CLOCKS_PER_SEC);

<<<<<<< Updated upstream
    printf("Find %d keys,fp:%lf, use %lu ms\n", count, double(count - 6306) / 1270000, (end_time - start_time) * 1000/CLOCKS_PER_SEC);
=======
    sleep(3);
>>>>>>> Stashed changes
    return 0;
}