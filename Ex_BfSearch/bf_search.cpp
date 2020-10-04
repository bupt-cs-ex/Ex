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
    double errors[3] = {0.0001, 0.00001, 0.000001};     //错误率

    int i = 0;
    for(i = 0; i < 3; ++i)
    {
        BloomFilter bf(1270000, errors[i]);
        count = 0;

        //读取 dict.txt 的 keywords，插入到哈希表
        FILE *infile = fopen("../dict.txt", "rb");
        if(infile == NULL) {
            //printf("Failed to open dict.txt\n");
            return -1;
        }
        while(!feof(infile)) {
            char buff[128];             //用于存储一个keyword
            int ch = fgetc(infile);     //读取一个字符
            int idx = 0;
            //逐个读取字符，直到行尾或文件尾
            while(ch != 0x0A && ch != -1) {
                buff[idx] = ch;
                ++idx;
                ch = fgetc(infile);
            }
            buff[idx] = '\0';           //一个keyword读取结束
            bf.put(buff);               //插入哈希表
        }
        fclose(infile);
        //printf("Finished reading dict.txt\n");

        //读取 string.txt 的 keywords，查找哈希表，将查找到的 keywords 输出到 result.txt
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
            int ch = fgetc(infile);     //用于存储一个keyword
            int idx = 0;                //读取一个字符
            //逐个读取字符，直到行尾或文件尾
            while(ch != 0x0A && ch != -1) {
                buff[idx] = ch;
                ++idx;
                ch = fgetc(infile);
            }
            buff[idx] = '\0';           //一个keyword读取结束
            if(bf.find(buff)) {         //哈希表中查找keyword
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