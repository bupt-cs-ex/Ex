//
// Created by 王尚荣 on 2020/9/25.
//

#include "BloomFilter.h"
/**
 * 构造函数
 * @param n 集合中字符串个数
 * @param e 允许的最大错误率
 */
BloomFilter::BloomFilter(unsigned int n, double e) {
    unsigned m = -1.44 * n * (log(e) / log(2));  // 计算合适的bit size
    bit_size = m - (m % 8);                             // 保证m为8的整数倍
    hash_num = int(0.7 * m / n);                        // 需要的哈希函数数量
    bit_array = new unsigned char[bit_size/8];          // sizeof(char) = 8 bit
    pos_list = new int[hash_num];                       // bit位数组
    seeds = new int[hash_num];                          // 种子数组，用于生成hash函数
    for(int i = 0; i < hash_num; i++){
        seeds[i] = rand();
    }
    std::cout<< "m:" << bit_size << " k:" << hash_num << std::endl;
    memset(bit_array, 0b00000000, bit_size/8);      //  init 0
}
/**
 *
 * @param key : 待插入/查找字符串
 * @return bit索引数组,长度为hash_nums
 */
void BloomFilter::get_bit_posList(char *key) {
    unsigned int seed;
    for(int i = 0; i < hash_num; i++){
        unsigned int hashcode = 0;
        MurmurHash3_x86_32(key, strlen(key), seeds[i], &hashcode);
        pos_list[i] = hashcode % bit_size;
    }
}

void BloomFilter::put(char *key) {
    get_bit_posList(key);
    for(int i = 0; i < hash_num; i++){
        int pos = pos_list[i] / 8;
        int bit_pos = pos_list[i] % 8;
        unsigned char val = 0b10000000;
        val = val >> bit_pos;
        bit_array[pos] = bit_array[pos] | val;     // 1000 0000 右移 bit_pos 位取或
    }
}

bool BloomFilter::find(char *key) {
    get_bit_posList(key);
    for(int i = 0; i < hash_num; i++){
        int pos = pos_list[i] / 8;
        int bit_pos = pos_list[i] % 8;
        unsigned char val = 0b10000000;
        val = val >> bit_pos;
        if(unsigned(bit_array[pos] & val) == 0)
            return false;
    }
    return true;
}
