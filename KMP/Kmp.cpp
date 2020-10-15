//
// Created by 王尚荣 on 2020/10/9.
//
#include "Kmp.h"

int* GetNext(char* p){
    int pLen = strlen(p);
    int* next = new int[pLen];
    next[0] = -1;
    int k = -1;
    int j = 0;
    while(j < pLen - 1){
        if(k == -1 || p[k] == p[j]){
            k++;
            j++;
            // 优化next数组
            if(p[j] != p[k])
                next[j] = k;
            else
                next[j] = next[k];
        }else
            k = next[k];
    }
    return next;
}

int KmpSearch(char *s, char *p) {
    int* next = GetNext(p);
    int sLen = strlen(s);
    int pLen = strlen(p);
    int i = 0, j = 0;
    while(i < sLen && j < pLen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    delete[] next;
    if(j == pLen)
        return i - j;
    else
        return -1;
}

