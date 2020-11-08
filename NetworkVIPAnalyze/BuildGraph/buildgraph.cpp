#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "AutoMachine.h"
#include "Matrix.h"

Matrix matrix;

/**
 * 匹配文件中的url http://news.sohu.com/*.shtml
 * @param file_name 文件名
 * @param path      当前路径
 */
int match_url(char* file_name, string path){
    FILE *infile = fopen(file_name, "rb");
    if(infile == NULL) {
        printf("Failed to open test.shtml\n");
        return -1;
    }
    AutoMachine am(path);
    int idx = 0;
    char buff[2048 + 1];
    while(!feof(infile)) {
        int ch = fgetc(infile);     //读取一个字符
        idx = 0;
        //从文件中读取字符到缓冲区
        while(ch != 0x0A && ch != -1) {
            buff[idx] = ch;
            ++idx;
            if(idx == 2048)
                break;
            ch = fgetc(infile);
        }
        buff[idx] = '\0';
        am.match(buff);
    }
    fclose(infile);
//    am.print();
    string s = path + string(file_name);
    char* src = new char[s.size()];
    strcpy(src, s.c_str());
    for(int i = 0; i < am.result.size(); i++)
        matrix.add(src, am.result[i]);
}
/**
 * 递归读取目录
 * @param dirname 目录名
 * @param path    当前路径
 */
void read_dir(const char* dirname, string path){
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    if((dir = opendir(dirname)) == NULL){
        printf("Can't open dir:%s\n", dirname);
        return;
    }
    chdir(dirname);
    while((entry = readdir(dir)) != NULL){
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)){
            if((strcmp(entry->d_name, ".") == 0 ) || (strcmp(entry->d_name, "..") == 0))
                continue;
            printf("dir  name:%s%s\n",path.c_str(), entry->d_name);
            read_dir(entry->d_name, path + string(entry->d_name) + "/");
        }else{
            printf("file name:%s%s\n",path.c_str(), entry->d_name);
            match_url(entry->d_name, path);
        }
    }
    chdir("..");
    closedir(dir);
}


int main() {
    read_dir("../01", "http://news.sohu.com/");
    return 0;
}
