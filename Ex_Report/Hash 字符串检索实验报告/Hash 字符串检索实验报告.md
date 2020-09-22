# Hash 字符串检索实验报告

## 1、实验内容

在给定的127万字符串中（dict.txt）查找待匹配的1.7万个字符串（string.txt），将查找到的字符串分行保存到 result.txt。



## 2、主要数据结构和流程

### 2.1 流程

- 依次读取 dict.txt 中的 127 万个 keywords，并插入到哈希表中
- 依次读取 string.txt 中的 1.7 万个 keywords，从哈希表中查询，若查找到，则将该 keywords 输出到 result.txt。

![流程图](流程图.png)

### 2.2 主要数据结构

#### 哈希表

- 数据结构

```c++
/**
 * 节点结构
 */
class Node{
public:
    Node(){
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
    HashTable(unsigned int n, unsigned int(*hash_func)(char* key)){
        size = n;
        sizemask = n - 1;
        table = new Node*[n];
        memset(table, 0, size);
        hashFunction = hash_func;
    }
    void put(char* key);
    bool find(char* key);
    ~HashTable(){
        for(unsigned i = 0; i < size; i++){
            if(table[i] != nullptr){
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

#### 文件读写

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



## 3、实验过程

1. 设置哈希表长度和hash函数

   本实验中采用**`SDBMhash`**函数对字符串取哈希值。

   考虑到字典中包含约**127万**字符和哈希表长度的选取原则（最好是以**2**的次幂作为表长取模会得到较好的散列效果），取表长`n =  2^17` 约等于13万作为此次实验哈希表的表长，平均每个桶中有10个字符串，以达到冲突和查找速度的折中。

2. 创建`HasbTable`对象

3. 读取`dict.txt`并将每个单词插入到`HashTable`对象中

4. 读取`string.txt`中的单词并在`HashTable`中查找，将查找到的单词写入`result.txt`中



## 4、遇到的问题

1、文件读取失败

解决：因为 clion 会把编译相关的文件放在 cmake-build-debug 文件夹，所以在设置文件的相对路径时应设置为上级目录，即 `../` ，否则文件读取失败。





## 5、结果指标





## 6、结论和总结

