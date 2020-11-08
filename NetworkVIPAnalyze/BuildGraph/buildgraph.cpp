#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Matrix.h"
#include "AC_automachine.h"
#define MODE_INSERT 1
#define MODE_MATCH  2
Matrix* matrix;
AC_automachine ac;
/**
 * 匹配文件中的url
 * @param file_name 文件名
 * @param path      模式串
 */
int match_url(char* file_name, char* pattern){
    List<unsigned int>* result = ac.MatchByFile(file_name, "rb");
    unsigned int src = ac.findKey(pattern);
    for(int i = 0 ;i < (*result).size(); i++){
        matrix->add(src, (*result)[i], 1.0);
    }
}
/**
 * 递归读取目录,获得所有模式串
 * @param dirname 目录名
 * @param path    当前路径
 */
void read_dir(const char* dirname, string path, int mode){
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
            char* file_name = new char[strlen(entry->d_name) + path.size()];
            strcpy(file_name, path.c_str());
            strcat(file_name, entry->d_name);
            if(mode == MODE_INSERT){
                ac.Insert(file_name);
                file_name = nullptr;
            }
            else{
                match_url(entry->d_name, file_name);
                delete[] file_name;
            }

        }
    }
    closedir(dir);
    chdir("..");
}

void testMatrix(){

}
void test_hash_map(){
    unordered_map<char* , int, hash_func, cmp> map;
    char* p = "hello";
    char q[] ="hello";
    map.insert({p, 1});
    map.insert({"he", 12});
    if(map.find("he") == map.end())
        printf("no find");
    else
        printf("find");
}
int main() {
    printf("pid:%d\n", getpid());
    read_dir("../webdir", "http://news.sohu.com/", MODE_INSERT);
    int N = ac.Build();
    matrix = new Matrix(N);
    chdir("webdir");
    read_dir("../webdir", "http://news.sohu.com/", MODE_MATCH);
    matrix->print();
    return 0;

}
