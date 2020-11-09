#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Matrix.h"
#include "AC_automachine.h"
#define MODE_INSERT 1
#define MODE_MATCH  2
Matrix* matrix = nullptr;
AC_automachine* ac = nullptr;
/**
 * 匹配文件中的url
 * @param file_name 文件名
 * @param path      模式串
 */
void match_url(char* file_name, const string& pattern){
    vector<int>* result = ac->MatchByFile(string(file_name), "rb");
    if(result){
        int src = ac->findKey(pattern);
        int length = (*result).size();
        for(int i = 0 ;i < length; i++){
            matrix->add(src, (*result)[i], 1.0 / length);
        }
    }
}
/**
 * 递归读取目录,获得所有模式串
 * @param dirname 目录名
 * @param path    当前路径
 */
void read_dir(const char* dirname, const string& path, int mode){
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
//            printf("dir  name:%s%s\n",path.c_str(), entry->d_name);
            read_dir(entry->d_name, path + string(entry->d_name) + "/", mode);
        }else{
//            printf("file name:%s%s\n",path.c_str(), entry->d_name);
            string file_name = path + string(entry->d_name);
            if(mode == MODE_INSERT){
                ac->Insert(file_name);
            }
            else{
                match_url(entry->d_name, file_name);
            }

        }
    }
    closedir(dir);
    chdir("..");
}

int main() {
    printf("pid:%d\n", getpid());
    ac = new AC_automachine();
    read_dir("../webdir", "http://news.sohu.com/", MODE_INSERT);
    int N = ac->Build();
    matrix = new Matrix(N);
    chdir("webdir");
    read_dir("../webdir", "http://news.sohu.com/", MODE_MATCH);
    matrix->print();
    return 0;

}
