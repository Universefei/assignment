PNPmsgMap
=========

### Problem

![task](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/task.png)

### Src hierarchy

```
./PNPMsgMap
├── lib              (动态库内函数代码)
│   ├── fA.c
│   ├── fB.c
│   ├── fC.c
│   └── fD.c
├── main.c           (主函数)
├── MsgMap.conf      (配置文件)
├── README.md        (markdown文档)
└── tool.sh          (一些编译等的小工具)
```

### tool.sh introduction

![tool.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/tool.png)
- `./tool.sh --doc`  : 说明文档
- `./tool.sh --lib`  : 编译目录`./lib`下的所有.c文件到动态库`./lib/libfei.so`中
- `./tool.sh --main` : 编译主函数，生成可执行文件./appMain
- `./tool.sh --clean`: 删除生成的二进制文件

![tool-lib.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/tool-lib.png)

![tool-main.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/tool-main.png)

## Demo

### 1.run ./appMain

![runfirst.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/run%20first.png)

**NOTE:**

- fE在配置文件中为信号e的处理函数，但是在动态库中没有实现
- fF在配置文件和动态库中都不存在

### 2. add fE

![addfe.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/add%20fe.png)

- 在`./lib`中实现fE
- 用`./tool.sh --lib`重新编译动态库，生成新的`./lib/libfei.so`
- 使用`touch MsgMap.conf`更新配置文件时间戳

### 3. run fE after adding fE

![runafteraddingfe.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/run%20after%20adding%20fe.png)

- 再次发送消息e,可以执行新加入的fE函数了！

### 4. add fF

![addff.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/add%20fF.png)

- 在`./lib`文件夹下实现fF
- 用`./tool.sh --lib`重新生成新的`./lib/libfei.so`
- 在配置文件中增加信号f条目

### 5 run fF after adding it

![runff.png](https://raw.github.com/Universefei/feinote/master/curriculum/driverProg/PNPmsgMap/misc/run%20demo%20snapshot%20after%20adding%20fF.png)

- 发送消息f,可以执行新加入的处理函数fF了

### NOTE：
以上过程中，`appMain`主程序始终没有终止
