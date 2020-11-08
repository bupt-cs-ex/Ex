//
// Created by 王尚荣 on 2020/11/8.
//

#ifndef BUILDGRAPH_HASH_H
#define BUILDGRAPH_HASH_H

// hash_map key的比较函数
struct cmp{
    bool operator()(const char* s1, const char* s2)const{
        if(s1 && s2)
            return strcmp(s1, s2) == 0;
        else
            return false;
    }
};
struct hash_func{
    unsigned int operator()(const char* str)const{
        unsigned int hash = 0;

        while (*str) {
            // equivalent to: hash = 65599*hash + (*str++);
            hash = (*str++) + (hash << 6) + (hash << 16) - hash;
        }
        return (hash & 0x7FFFFFFF);
    }

};
#endif //BUILDGRAPH_HASH_H
