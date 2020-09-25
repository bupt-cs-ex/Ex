//
// Created by ÍõÉÐÈÙ on 2020/9/25.
//

#ifndef EX_HASHTABLE_BLOOMFILTER_H
#define EX_HASHTABLE_BLOOMFILTER_H
#include <string.h>
#include <time.h>
#include <cstdlib>
#include "MurmurHash3.h"
/**
 * ²¼Â¡¹ýÂË
 */
class BloomFilter {
public:
    BloomFilter(unsigned m, double e, int k);
    void put(char* key);
    bool find(char* key);
private:
    int* get_bit_posList(char* key);
    unsigned int bit_size;
    double error_rate;
    int hash_num;
    unsigned char *bit_array;
};


#endif //EX_HASHTABLE_BLOOMFILTER_H
