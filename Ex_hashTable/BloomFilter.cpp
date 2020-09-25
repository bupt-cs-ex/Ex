//
// Created by 王尚荣 on 2020/9/25.
//

#include "BloomFilter.h"
BloomFilter::BloomFilter(unsigned int m, double e, int k) {
    bit_size = m - (m % 8);                         //保证m为8的整数倍
    error_rate = e;
    hash_num = k;                                   // 需要的哈希函数数量
    bit_array = new unsigned char[bit_size/8];      // sizeof(char) = 8 bit
    memset(bit_array, 0b00000000, bit_size/8);       //  init 0
}
/**
 *
 * @param key : 待插入/查找字符串
 * @return bit索引数组,长度为hash_nums
 */
int *BloomFilter::get_bit_posList(char *key) {
    int* ret = new int[hash_num];
    unsigned int seed;
    for(int i = 0; i < hash_num; i++){
        unsigned int hashcode = 0;
        seed = rand();
        MurmurHash3_x86_32(key, strlen(key), seed, &hashcode);
        ret[i] = hashcode % bit_size;
    }
    return ret;
}

void BloomFilter::put(char *key) {
    int* pos_list = get_bit_posList(key);
    for(int i = 0; i < hash_num; i++){
        int pos = pos_list[i] / 8;
        int bit_pos = pos_list[i] % 8;
        unsigned char val = 0b10000000;
        val = val >> bit_pos;
        bit_array[pos] = bit_array[pos] | val;     // 1000 0000 右移 bit_pos 位取或
    }
    delete pos_list;
}

bool BloomFilter::find(char *key) {
    int* pos_list = get_bit_posList(key);
    for(int i = 0; i < hash_num; i++){
        int pos = pos_list[i] / 8;
        int bit_pos = pos_list[i] % 8;
        unsigned char val = 0b10000000;
        val = val >> bit_pos;
        if((bit_array[pos] & val) == 0b00000000)
            return false;
    }
    return true;
}
