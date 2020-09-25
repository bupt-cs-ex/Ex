//
// Created by ÍõÉÐÈÙ on 2020/9/25.
//

#ifndef EX_HASHTABLE_BLOOMFILTER_H
#define EX_HASHTABLE_BLOOMFILTER_H
#include <string.h>
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "MurmurHash3.h"
/**
 * ²¼Â¡¹ýÂË
 */
class BloomFilter {
public:
    BloomFilter(unsigned n, double e);
    void put(char* key);
    bool find(char* key);
    ~BloomFilter(){
        delete[] bit_array;
    }
private:
    int* get_bit_posList(char* key);
    unsigned int bit_size;
    int hash_num;
    unsigned char *bit_array;
};


#endif //EX_HASHTABLE_BLOOMFILTER_H
