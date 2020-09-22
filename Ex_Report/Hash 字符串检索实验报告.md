# Hash 字符串检索实验报告

## 1、实验内容

在给定的127万字符串中（dict.txt）查找待匹配的1.7万个字符串（string.txt），将查找到的字符串分行保存到 result.txt。



## 2、主要数据结构和流程

### 2.1 流程

- 依次读取 dict.txt 中的 127 万个 keywords，并插入到哈希表中
- 依次读取 string.txt 中的 1.7 万个 keywords，从哈希表中查询，若查找到，则将该 keywords 输出到 result.txt。

![流程图](Hash 字符串检索实验报告/流程图.png)

### 2.2 主要数据结构

#### 哈希表



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





## 4、遇到的问题

1、文件读取失败

解决：因为 clion 会把编译相关的文件放在 cmake-build-debug 文件夹，所以在设置文件的相对路径时应设置为上级目录，即 `../` ，否则文件读取失败。

2、string.txt 文件中读到的所有 keyword 都被输出

解决：



## 5、结果指标





## 6、结论和总结

