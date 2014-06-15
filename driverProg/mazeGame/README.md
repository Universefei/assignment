MazeGame algorithm component
============================


### Hierarchy
```
.
├── archive/
│   └── 小作业2.doc
├── exdllSrc/                   (exdll.dll实现源码文件夹)
│   ├── exdll.cpp
│   ├── Maze.h
│   ├── StdAfx.cpp              (vc自动生成)
│   └── StdAfx.h                (vc自动生成)
├── figure/
├── README.md                    (本文档)
└── workshop/                    (运行文件夹)
    ├── 0.map
    ├── 1.map
    ├── 2.map
    ├── 3.map
    ├── 4.map
    ├── 5.map
    ├── 6.map
    ├── 7.map
    ├── 8.map
    ├── config.ini
    ├── exdll.dll                (用exdllSrc编译生成的.dll动态链接库,component)
    ├── ExplorerDll.dll
    └── MazeGame.exe*            (游戏主程序,Container)
```

## 算法主要思想

1. 贪心
2. 深度优先遍历

**贪心的思想**

- 若能在X轴方向上靠近终点，则优先在X上靠近终点。
- 若能在Y轴方向上靠近终点，则在Y轴上移动并靠近终点。
- 若以上都不行，则可还可选择的方向顶多有两个。
  - 若可选的方向还有两个。
    - 若从上一个位置到现在的这个位置的方向在目前的位置可用：尝试这个方向。
	- 若从上一个位置到现在的这个位置的方向在目前位置不可用：在两个中任选一个，但优先左和上。
  - 若可选的方向只有一个；尝试这个方向。
  - 若此前没有可选的方向：返回。

**Notice Board**

具体的实现细节可见代码，有较详细注释.
[click here](https://github.com/Universefei/feinote/blob/master/curriculum/driverProg/mazeGame/exdllSrc/exdll.cpp)


## 运行结果

运行路径和步数可见下图：

![0.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/0.png)

![1.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/1.png)

![2.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/2.png)

![3.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/3.png)

![4.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/4.png)

![5.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/5.png)

![6.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/6.png)

![7.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/7.png)

![8.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/mazeGame/figure/8.png)


