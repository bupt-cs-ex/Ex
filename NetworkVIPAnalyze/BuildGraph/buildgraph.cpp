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
string graph_file = "graph.txt";
string urls_file = "urls.txt";
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
void test(){
    string Line = "12\t14\t0.056";
    int p1, p2;
    p1 = Line.find_first_of('\t');
    p2 = Line.find_last_of('\t');
    int i = stoi(Line.substr(0, p1));
    int j = stoi(Line.substr(p1 + 1, p2));
    double value = stod(Line.substr(p2));
    cout<<i<<endl;
    cout<<j<<endl;
    cout<<value<<endl;
}
vector<string> LoadData(Matrix*& mat, const string& mat_txt, const string& url_txt){
    chdir("..");
    mat = load_matrix(mat_txt);
    return load_urls(url_txt);
}
int main() {
//    printf("pid:%d\n", getpid());
//    ac = new AC_automachine();
//    read_dir("../01", "http://news.sohu.com/", MODE_INSERT);
//    int N = ac->Build();
//    matrix = new Matrix(N);
//    chdir("01");
//    read_dir("../01", "http://news.sohu.com/", MODE_MATCH);
//    matrix->print();
//    save_urls("urls.txt", ac->urls);
//    matrix->save("graph.txt");
    vector<string> urls = LoadData(matrix, graph_file, urls_file);
    cout << urls.size() << urls[1] << endl;
    matrix->print();
    return 0;

}
