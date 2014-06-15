StandardIO VS. mmap
====================

姓名: Fei Lunzhou
学号：1303121797

### Problem description
![problem](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/shm/figure/problem.png)

### SRC hierarchy
```
.
├── figure/            (misc)
├── mmap.c             (source file of reading bigfile via mmap)
├── README.md          (documentation)
├── statistic.sh*
├── stdio.c            (source file of readming bigfile via standard io)
├── testReport         (statistic data result of testing)
└── tools.sh*          (tools to compile/ run test etc.)
```

### tools.sh specification
![tools.sh](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/shm/figure/tools.png)

**NOTE:**
* `./tools.sh -d` 查看文档
* `./tools.sh -b` 创建大文件 1M X 1000，名称为bigfile
* `./tools.sh -c` 编译代码
* `./tools.sh -t` 进行测试，测试结果数据保存在生成的testReport文件中了

### Notice board
由于一次结果具有偶然性，每组实验进行三次测试.



## DEMO

### 1. create bigfile
![bigfile](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/shm/figure/bigfile.png)

### 2. compile source code file
![compile](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/shm/figure/compile.png)

### 3. test
![test](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/shm/figure/testResult.png)

* 也可在`testReport`中查看测试结果
* [我的测试结果](https://github.com/Universefei/feinote/blob/master/curriculum/driverProg/shm/testReport)


## Analysis & Conclusion

### 1.标准IO过程
1. 数据从外存到内核缓冲区
2. 数据从内核缓冲区拷贝到用户空间
3. 用户程序在用户空间读写访问数据

### 2.内存映射过程
1. 系统调用为外存映射文件分配页表
2. 用户程序直接操作映射到的用户地址空间数据
3. 当用户访问页表发现未调入内存时，IO从外存调如到内存页

### 比较
* 标准IO比内存映射多一个从内核空间到用户空间的拷贝过程
* 标准IO每次读写都要一次系统调用`read()` `write()`等,需要保存上下文，跳转，
  恢复上下文等过程, 内存映射只需分配好页表后，直接操作 用户空间内存既可.k

### Conclusion
理论上讲，标准IO应该比内存映射慢,主要耗时在系统调用和内存拷贝上的时间浪费，
但实验的数据看到当`fread()`每次读取到128B左右时候与mmap几乎相当，进一步增加
一次`fread()`的字节数,标准IO似乎比mmap更快。原因待进一步分析

可能的原因：
* 编译器优化的问题
* 测试程序的问题


