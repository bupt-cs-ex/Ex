# 计算机应用实验二：RawTrie

2020110636 王尚荣	2020110630 王宝江

## 1、实验内容

- 实现RawTrie树结构
- 将给定的127万个字符串（dict.txt）利用Trie树存储
- 给定的待匹配字符串（string.txt），将查找到的单词写入result.txt

## 2、主要数据结构和流程

### 2.1 TrieNode

- 数据结构

  ```c++
  /**
   * Trie树节点结构
   */
  class TrieNode{
  public:
      TrieNode(char v, bool isWord= false){
          memset(child, NULL, sizeof(child)/sizeof(TrieNode*));
          this->isWord = isWord;
          val = v;
      }
      ~TrieNode(){
          for(int i = 0; i < sizeof(child)/sizeof(TrieNode*); i++)
              delete child[i];
      }
      TrieNode* child[256];
      bool isWord;        // 是否为根节点
      char val;           // 记录当前节点表示的值
  };
  ```

### 2.2 Trie

数据结构

```C++
/**
 * Trie树结构
 */
class Trie {
public:
    Trie() {
        root = new TrieNode('\0', false);
    }
    void Insert(char* key);
    bool Find(char* key);
    void FormatPrint();
    ~Trie(){
        delete root;
    }
private:
    TrieNode* root;
private:
    bool Search(TrieNode* node, char* key, int pos);
};
```

插入key

```c++
/**
 * 插入key
 * @param key 待插入的字符串
 */
void Trie::Insert(char *key) {
    if(key == nullptr || strlen(key) == 0)
        return;
    TrieNode* cur = root;
    int len = strlen(key);
    // 迭代将每个字符插入到child域中
    for(int i = 0; i < len; i++){
        int index = key[i] + 128;
        if(!cur->child[index])
            cur->child[index] = new TrieNode(key[i]);
        cur = cur->child[index];
    }
    cur->isWord = true;
}
```

查找key

```c++
bool Trie::Find(char *key) {
    return Search(root, key, 0);
}
/**
 * 在节点中查找从key[index:]是否存在
 * @param node      开始节点
 * @param key       查找的字符串
 * @param pos       从key[pos]开始查找
 * @return          是否存在;
 */
bool Trie::Search(TrieNode *node, char *key, int pos) {
    if(strlen(key) == 0)
        return false;
    int index = key[pos] + 128;
    TrieNode* cur = node->child[index];
    if(!cur)
        return false;
    if(pos == strlen(key) - 1)
        return cur->isWord;
    return Search(cur, key, pos + 1);
}
```

- 文件读写
  - 读文件：使用 `int fgetc(FILE *stream)` 逐个读取字符并保存到字符数组（字符数组存储一个 keyword），如果 `fgetc()` 返回 `0x0A`（换行） 或 `-1`（文件尾），该 keyword 读取结束。
  - 写文件：使用 `int fputs(const char *str, FILE *stream)` 将一个字符数组（keyword）输出到文件

```c++
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
    //在trie树中查找keyword
    if(trie.Find(buff)){		
        fputs(buff, outfile);	//将查找到的keyword输出到文件
        fputs("\n", outfile);
    }
}

fclose(outfile);
fclose(infile);
```



## 3、实验过程

1. 创建Trie树对象
2. 读取dict.txt，将单词插入到Trie中
3. 读取string.txt，在Trie中查找，若查到则将其写入result.txt

## 4、遇到的问题

无

## 5、结果指标

准确率：100% 查找到6306个单词

时间：5502ms

内存峰值：8052MB

## 6、结论和总结

Trie树的高度取决于字典中最长的单词长度，因此查找速度相对于二叉树会快很多，它是通过空间换时间的方式利用字符串的公共前缀来降低查询的时间开销。

Trie树占用内存空间大

