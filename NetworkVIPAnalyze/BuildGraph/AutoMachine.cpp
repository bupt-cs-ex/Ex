//
// Created by 王尚荣 on 2020/11/7.
//
#include "AutoMachine.h"
#include <string.h>

string AutoMachine::URL = "http://news.sohu.com/*.shtml";// 待匹配的URL 静态成员

void AutoMachine::init() {
    idx = 0;
    match_idx = 0;
}

void AutoMachine::match(char *text) {
    for(int i = 0; i < strlen(text); i++){
        if(text[i] == '<'){
            isStart = true;
            continue;
        }else if(text[i] == '>'){
            isStart = false;
            init();
        }
        if(isStart)
            _next(text[i]);
    }
}

void AutoMachine::_next(char c) {
    if(match_idx == AutoMachine::URL.size()){
        buff[idx++] = '\0';
        char* url = new char[idx];
        strcpy(url, buff);
        result.append(url);     //完成一次匹配，将结果加入到result
        isStart = false;
        init();
    }
    if(AutoMachine::URL[match_idx] == '*'){
        if(c == '.')
            match_idx += 2;     // 这里要跳两步 首先跳过*符号
        buff[idx++] = c;
    } else if(AutoMachine::URL[match_idx] == c){
        match_idx++;
        buff[idx++] = c;
    }else{
        init();
    }
}

void AutoMachine::print() {
    printf("match %d urls\n", result.size());
    for(int i = 0; i < result.size(); i++)
        printf("%d: %s\n",i, result[i]);
}
