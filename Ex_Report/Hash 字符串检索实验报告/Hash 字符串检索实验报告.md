# 计算机应用实验一：Hash 技术字符串检索

2020110636 王尚荣	2020110630 王宝江

## 1、实验内容

### 1.1 hashtable 字符串检索

- 将给定的127万个字符串（dict.txt），利用哈希表存储在内存。

- 在127万个字符串中查找待匹配的1.7万个字符串（string.txt），将查找到的字符串分行保存到 result.txt。

### 1.2 bloom filter

- 构建 bloom filter ，包含4个参数：

  - f：期望的错误率
  - n：待存储的字符串数量
  - m：需开辟的存储空间位数
  - k：哈希函数的个数

  根据错误率 f 和字符串数量 n，动态计算：

  - 需开辟的存储空间位数 m：
    $$
    m = n × log_2e × log_2(1/f) ≈ n × 1.44 × log_2(1/f)
    $$
    

  - 合适的哈希函数个数 k：

  $$
  k = ln2 × m/n ≈ 0.693 × m/n
  $$

- 在给定的 127 万个字符串中查找待匹配的 1.7 万个字符串。



## 2、主要数据结构和流程

### 2.1 hashtable 字符串检索

#### 2.1.1 流程

- 依次读取 dict.txt 中的 127 万个 keywords，并插入到哈希表中
- 依次读取 string.txt 中的 1.7 万个 keywords，从哈希表中查询，若查找到，则将该 keyword 输出到 result.txt。

![流程图](流程图.png)

#### 2.1.2 主要数据结构

##### 2.1.2.1 哈希表

- 数据结构

  ```c++
  /**
   * 节点结构
   */
  class Node {
  public:
      Node() {
          pVal = nullptr;
          len = 0;
          pNext = nullptr;
      }
      char* pVal;        //记录存储的字符串地址
      int len;           //字符串长度
      Node* pNext;       //记录下一节点地址
  };
  /**
   * 哈希表结构
   */
  class HashTable {
  public:
      /**
       * 构造函数
       * @param n : 哈希表表长（桶数）
       * @param hash_func : 采用的hash函数
       */
      HashTable(unsigned int n, unsigned int(*hash_func)(char* key)) {
          size = n;
          sizemask = n - 1;
          table = new Node*[n];
          memset(table, 0, size);
          hashFunction = hash_func;
      }
      void put(char* key);
      bool find(char* key);
      ~HashTable(){
          for(unsigned i = 0; i < size; i++) {
              if(table[i] != nullptr) {
                  freeNode(table[i]);
                  table[i] = nullptr;
              }
          }
          delete []table;
      }
  private:
      unsigned int size;                          //哈希表大小
      unsigned int sizemask;                      //哈希表大小掩码，用于计算索引值 size - 1
      Node** table;                               //哈希表头指针
      unsigned int (*hashFunction)(char* key);    //哈希函数
      void freeNode(Node* pNode);                 //释放节点空间
  };-
  
  ```

- 插入

  计算待插入字符串的hash值，与掩码按位取或（快速取模）得到索引值，创建节点对象，将其插入到对应索引的头节点处

  ```c++
  void HashTable::put(char* key) {
      unsigned int hash = hashFunction(key);
      unsigned int index = hash & sizemask;
      Node* node = new Node();
      node->len = strlen(key);
      node->pVal = new char[node->len];
      strcpy(node->pVal, key);
      node->pNext = table[index];
      table[index] = node;
  }
  ```

- 查找

  计算待插入字符串的hash值，与掩码按位取或（快速取模）得到索引值，从索引处头节点遍历开始遍历链表，匹配成功时返回`true`，否则返回`false`

  ```c++
  /**
   * @param key : 待查找字符串
   * @return : 查找结果
   */
  bool HashTable::find(char* key) {
      unsigned int hash = hashFunction(key);
      unsigned int index = hash & sizemask;
      if(table[index] == nullptr)
          return false;
      Node* p = table[index];
      while(p != nullptr){
          if(strcmp(p->pVal, key) == 0)
              return true;
          p = p->pNext;
      }
      return false;
  }
  ```

##### 2.1.2.2 文件读写

- 读文件：使用 `int fgetc(FILE *stream)` 逐个读取字符并保存到字符数组（字符数组存储一个 keyword），如果 `fgetc()` 返回 `0x0A`（换行） 或 `-1`（文件尾），该 keyword 读取结束。
- 写文件：使用 `int fputs(const char *str, FILE *stream)` 将一个字符数组（keyword）输出到文件

```C++
FILE *infile = fopen("../string.txt", "rb");	//待读取的文件
FILE *outfile = fopen("../result.txt", "wb");	//待输出的文件

//文件读取失败的情况
if(infile == NULL){
    printf("Failed open string.txt\n");
    return -1;
}
if(outfile == NULL){
    printf("Failed open result.txt\n");
    return -1;
}

//读取文件直到文件尾
while(!feof(infile)){
    char buff[128];				//用于存储一个keyword
    int ch = fgetc(infile);		//读取一个字符
    int idx = 0;
    //逐个读取字符，直到行尾或文件尾
    while(ch != 0x0A && ch != -1){
        buff[idx] = ch;
        ++idx;
        ch = fgetc(infile);
    }
    buff[idx] = '\0';			//一个keyword读取结束
    //在哈希表中查找keyword
    if(tb.find(buff)){		
        fputs(buff, outfile);	//将查找到的keyword输出到文件
        fputs("\n", outfile);
    }
}

fclose(outfile);
fclose(infile);
```

### 2.2 bloom filter

#### 2.2.1 流程

- 构建一个 bloom filter，根据预期的错误率 f 和字典中的字符串数量 n，动态计算：

  - 需开辟的最优存储空间位数 m：
    $$
    m = n × log_2e × log_2(1/f) ≈ n × 1.44 × log_2(1/f)
    $$

  - 合适的哈希函数个数 k：
    $$
    k = ln2 × m/n ≈ 0.693 × m/n
    $$

- 生成一个 m 位的数组
- 使用 murmurhash 生成 k 个相互独立的哈希函数
- 依次读取 dict.txt 中的 127 万个 keywords，每读取一个 keyword，使用 k 个哈希函数将其映射到数组的 k 个位置，将这 k 个位置置为 1
- 依次读取 string.txt 中的 1.7 万个 keywords，每读取一个 keyword，使用同样的 k 个哈希函数将其映射到数组的 k 个位置，如果这 k 个位置都为1，则说明查找成功，将该 keyword 输出到 result.txt。统计查找成功的 keywords 个数。

#### 2.2.2 主要数据结构

##### 2.2.2.1 bloom filter

- 数据结构

  ```C++
  class BloomFilter {
  public:
      BloomFilter(unsigned n, double e);
      void put(char* key);
      bool find(char* key);
      ~BloomFilter(){
          delete[] bit_array;
          delete[] pos_list;
          delete[] seeds;
      }
  private:
      void get_bit_posList(char* key);
      unsigned int bit_size;
      int hash_num;
      unsigned char *bit_array;
      int* pos_list;
      int* seeds;
  };
  ```

- 构造函数

  ```c++
  /**
   * 构造函数
   * @param n 集合中字符串个数
   * @param e 允许的最大错误率
   */
  BloomFilter::BloomFilter(unsigned int n, double e) {
      unsigned m = -1.44 * n * (log(e) / log(2));     // 计算合适的bit size
      bit_size = m - (m % 8);                             // 保证m为8的整数倍
      hash_num = int(0.7 * m / n);                        // 需要的哈希函数数量
      bit_array = new unsigned char[bit_size/8];          // sizeof(char) = 8 bit
      pos_list = new int[hash_num];                       // bit位数组
      seeds = new int[hash_num];                          // 种子数组，用于生成hash函数
      for(int i = 0; i < hash_num; i++) {
          seeds[i] = rand();
      }
      std::cout<< "m:" << bit_size << " k:" << hash_num << std::endl;
      memset(bit_array, 0b00000000, bit_size/8);      //  init 0
  }
  ```

- 使用 k 个哈希函数映射到 k 个位置

  ```C++
  void BloomFilter::get_bit_posList(char *key) {
      for(int i = 0; i < hash_num; i++){
          unsigned int hashcode = 0;
          MurmurHash3_x86_32(key, strlen(key), seeds[i], &hashcode);
          pos_list[i] = hashcode % bit_size;
      }
  }
  ```

- 插入

  ```C++
  void BloomFilter::put(char *key) {
      get_bit_posList(key);
      for(int i = 0; i < hash_num; i++) {
          int pos = pos_list[i] / 8;
          int bit_pos = pos_list[i] % 8;
          unsigned char val = 0b10000000;
          val = val >> bit_pos;
          bit_array[pos] = bit_array[pos] | val;     // 1000 0000 右移 bit_pos 位取或
      }
  }
  ```

- 查找

  ```C++
  bool BloomFilter::find(char *key) {
      get_bit_posList(key);
      for(int i = 0; i < hash_num; i++) {
          int pos = pos_list[i] / 8;
          int bit_pos = pos_list[i] % 8;
          unsigned char val = 0b10000000;
          val = val >> bit_pos;
          if(unsigned(bit_array[pos] & val) == 0)
              return false;
      }
      return true;
  }
  ```

  ##### 2.2.2.2 文件读写

  基本同 2.1.2.2 文件读写。



## 3、实验过程

### 3.1 hashtable 字符串检索

1. 设置哈希表长度和hash函数

   本实验中采用**`SDBMhash`**函数对字符串取哈希值。

   考虑到字典中包含约**127万**字符和哈希表长度的选取原则（最好是以**2**的次幂作为表长取模会得到较好的散列效果），取表长`n =  2^17` 约等于13万作为此次实验哈希表的表长，平均每个桶中有10个字符串，以达到冲突和查找速度的折中。

2. 创建`HasbTable`对象

3. 读取`dict.txt`并将每个 keyword 插入到`HashTable`对象中

4. 读取`string.txt`中的 keyword 并在`HashTable`中查找，将查找到的单词写入`result.txt`中

### 3.2 bloom filter

1. 创建 `BloomFilter ` 对象，向构造函数传入参数，例如，字符串数量 n=1270000，预期错误率 e=0.00001。动态计算 m 和 k，生成长度为 m 的位数组，以及 k 个相互独立的哈希函数。
2. 读取`dict.txt`，每读取一个 keyword，使用 k 个哈希函数将其映射到 bloom filter 数组的 k 个位置，将这 k 个位置置为 1
3. 读取`string.txt`，每读取一个 keyword，使用同样的 k 个哈希函数将其映射到数组的 k 个位置，如果这 k 个位置都为1，则说明查找成功，将该 keyword 输出到 `result.txt`。统计查找成功的 keywords 个数。



## 4、遇到的问题

- 问题1：文件读取失败

  解决：因为 clion 会把编译相关的文件放在 cmake-build-debug 文件夹，所以在设置文件的相对路径时应设置为上级目录，即 `../` ，否则文件读取失败。

- 问题2：bloom filter 的 m 和 k 计算正确，但只查找到一个 keyword

  解决：插入和查找使用的应该是同样的 k 个相互独立的哈希函数。



## 5、结果指标

### 5.1 hashtable 字符串检索

#### 5.1.1 结果

查找到 6306 个 keywords，查到的各个 keyword 详见 result.txt 。

#### 5.1.2 运行时间

627 ms

### 5.2 bloom filter

#### 5.2.1 结果对比

字典字符串数量 n 都为 127万，待查找的字符串正确的查找结果为查找到 6306 个

| 预期错误率e | 存储空间位数m | 哈希函数个数k | 查到个数 | 实际错误率 | 运行时间 |
| ----------- | ------------- | ------------- | -------- | ---------- | -------- |
| 0.1         | 6075136       | 3             | 7436     | 0.179194   | 474ms    |
| 0.01        | 12150280      | 6             | 6427     | 0.019188   | 686ms    |
| 0.001       | 18225424      | 10            | 6314     | 0.001269   | 937ms    |
| 0.0001      | 24300568      | 13            | 6307     | 0.000159   | 1165ms   |
| 0.00001     | 30375704      | 16            | 6306     | 0.000000   | 1409ms   |
| 0.000001    | 36450848      | 20            | 6306     | 0.000000   | 1657ms   |
| 0.0000001   | 42525992      | 23            | 6306     | 0.000000   | 1933ms   |



## 6、结论和总结

### 6.1 hashtable 字符串检索

哈希表通过将关键码值映射到表中一个位置来访问记录，以加快查找速度。选择合适的哈希函数和哈希表表长，以寻求冲突和查找速度的平衡。本实验测试了 2\^15，2\^16，2\^17，2\^18，2\^19 等不同表长，发现取表长 2^17 时，查找速度最快。

### 6.2 bloom filter

- bloom filter 使用 k 个相互独立的哈希函数将每一个 keyword 映射到 二进制位数组的 k 位置，并将该 k 个位置置为 1 ，查找时使用相同的 k 个哈希函数将 keyword 映射到 k 个位置，若 k 个位置都为1，则认为查找成功，否咋查找失败。
- 根据 bloom filter 的原理，不会出现漏报（即存在 keyword 但查找失败），但是会出现误报（即不存在 keyword 但是查找成功），因为一个不存在的 keyword 经过 k 个哈希函数映射得到的 k 个位置，可能刚好都已被其他 keywords 映射过。
- 但是 bloom filter 具有很大的空间优势和时间优势。
  - 空间优势：对于 n 个字符串，bloom filter只需要开辟具有  $m = n × log_2e × log_2(1/f) ≈ n × 1.44 × log_2(1/f)$  bit 的数组，一个 bit 存储 0/1 即可，不需要存储 keyword 本身。对于127万个字符串，哪怕预期达到百万分之一的错误率，也只需要 42525992 位的数组，即 5.3M 存储空间。
  - 时间优势，插入和查找的时间复杂度都为 O(1)
- 因此，bloom filter 是采用准确率换时间的思想。根据对应的公式可以计算得到最小需要开辟的存储空间位数，以及所需的哈希表个数。