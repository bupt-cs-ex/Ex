//
// Created by ������ on 2020/9/25.
//

#include "BloomFilter.h"
/**
 * ���캯��
 * @param n �������ַ�������
 * @param e �������������
 */
BloomFilter::BloomFilter(unsigned int n, double e) {
    unsigned m = -1.44 * n * (log(e) / log(2));  // ������ʵ�bit size
    bit_size = m - (m % 8);                             // ��֤mΪ8��������
    hash_num = int(0.7 * m / n);                        // ��Ҫ�Ĺ�ϣ��������
    bit_array = new unsigned char[bit_size/8];          // sizeof(char) = 8 bit
    pos_list = new int[hash_num];                       // bitλ����
    seeds = new int[hash_num];                          // �������飬��������hash����
    for(int i = 0; i < hash_num; i++){
        seeds[i] = rand();
    }
    std::cout<< "m:" << bit_size << " k:" << hash_num << std::endl;
    memset(bit_array, 0b00000000, bit_size/8);      //  init 0
}
/**
 *
 * @param key : ������/�����ַ���
 * @return bit��������,����Ϊhash_nums
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
        bit_array[pos] = bit_array[pos] | val;     // 1000 0000 ���� bit_pos λȡ��
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
