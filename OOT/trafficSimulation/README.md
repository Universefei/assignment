TrafficSimulation
=================

###Problem:

![prob1](https://raw.github.com/Universefei/feinote/master/curriculum/OOT/trafficSimulation/figures/prob1.png)
![prob2](https://raw.github.com/Universefei/feinote/master/curriculum/OOT/trafficSimulation/figures/prob2.png)
![prob3](https://raw.github.com/Universefei/feinote/master/curriculum/OOT/trafficSimulation/figures/prob3.png)


###Environment:
* OS        :Ubuntu 12.04
* Compiler  :G++ (qmake to build)
* Language  :C++

##设计说明书

本程序采用`Qt Graphics View`框架编写，`Qt Graphics View`提供了 `QGraphicsItem`,
`QGraphicsScene`和`QGraphicsView`三个类，其中：

1. `QGraphicsItem`表示界面中的物体，其中的`boundingRect()`,`paint()`为纯虚函数
   用户对于每个它的子类可以在这两个函数中定义物体的边框用于监测是否碰撞，和定义
   他们的形状，`advance`函数定义每一帧中，本物体应该执行的代码。
2. `QGraphicsScene`视图类，它用户规划多个物体Item之间的布局情况。
3. `QGraphicsView`场景类，用于实际的现实。

###设计类图和序列图

**Class Diagram**
![class diagram](https://raw.github.com/Universefei/feinote/master/curriculum/OOT/trafficSimulation/figures/Class%20diagram.png)

**Sequence Diagram**
![sequence diagram](https://raw.github.com/Universefei/feinote/master/curriculum/OOT/trafficSimulation/figures/Sequence%20Diagram.png)


###类说明
注：更具体的类说明可以查看相应类的接口文件(.h), 注释十分详细。

**Class QGraphicsItem**
* boundingRect() :给出大概的物体的矩形边框已用于检测是否碰撞
* paint() :画物体
* shape() :具体的边框，形状
* advance() :定义每一帧中每个物体应该进行的动作，在一下的每个类中都会用到，重要！

**Class TrafficLight**
* ticker :路灯的计时器
* getTrafficStatus() :获取当前路灯某个方向的状态，返回的是路灯的颜色。

**Class Car**
* genPlace :汽车产生的地点。
* dist :汽车的目的地。
* speed :汽车的速度。
* setStartPos() :根据汽车产生的地点，在constructor中调用此函数，将其放入相应位置。
* turnDirection() :从不同的产生地产生的车的拐弯方法不同，此函数是virtual函数，在
                   每个`CarXXX`中应该具体定义他们如何拐弯。
* abletoForward() :判断某路口的某路灯是否可以通行。
* checkLightForward() :根据car位置判断此刻（此帧）是否可以移动。根据前面是否有车和路灯情况。

**Class CarXXX**
* turnDirection() :重新实现的父类中的函数，因为不同地方出发的车转弯方法不同，所以每种都应定义
                   自己的转弯方法。

**Class CarGenerator**
* ticker : 汽车工厂的计时器。
* genPlace : 汽车工厂产生以哪里为产生地点的汽车。
* trafHeavy : 交通拥堵状况, 数值越大，产生车越快。表明交通越拥堵。
* placeSet() : 在constructor中调用，将本工厂放在相应的地方。


###全局和静态命名规则
注：全部声明在`misc.h`中了，其中有注释。

* `pLightAtCr1` `pLightAtCr2` ：在cr1的路灯和在cr2的路灯
* `EPlace` ：枚举类型，表明各个路口`eBSN` `eBSS` `eTBN` `eTBS` `eRHW` `eRHE`
* `pointColor[6]` :表示各个路口车的颜色,例如：`pointColor[eBSN]`表BSN路口出车的颜色
* `startPoint[6]` :表每个路口起点的坐标.
* `endPoint[6]` :表示以某个路口为终点的时候此终点的坐标
* `cr1Center` `cr2Center` :路口中心坐标, 也就是红绿灯中心坐标
* `lightCrXYYY` :在路口X，从YYY来的车辆应该检查红绿灯状态的点坐标
* `BBB2AAA` :从BBB方向到AAA方向的车应该转弯的点


###仿真流程

* linux环境下安装Qt sdk
* 打开terminal, cd到应用程序目录
* `qmake -project`
* `qmake trafficSimulation.pro`为项目生成Makefile文件
* `make`编译
* `./trafficSimulation`命令即可运行

###仿真画面
![snapshot](https://raw.github.com/Universefei/feinote/master/curriculum/OOT/trafficSimulation/figures/snapshoot1.png)

##源程序清单

```
.
├── AUTHORS
├── doc/
│   ├── 13prj.pdf
│   ├── Class Diagram0.asta
│   └── Class Diagram0.asta.bak
├── figures/
├── README.md
├── src/ (源码文件夹)
│   ├── car.cpp
│   ├── carFrom.cpp
│   ├── carFrom.h
│   ├── carGenerator.cpp
│   ├── carGenerator.h
│   ├── car.h
│   ├── main.cpp
│   ├── Makefile
│   ├── misc.h
│   ├── trafficLight.cpp
│   ├── trafficLight.h
│   ├── trafficSimulation
│   └── trafficSimulation.pro
└── TODO
```

##运行情况总结报告

![snapshot](https://raw.github.com/Universefei/feinote/master/curriculum/OOT/trafficSimulation/figures/snapshoot1.png)
![snapshot](https://raw.github.com/Universefei/feinote/master/curriculum/OOT/trafficSimulation/figures/snapshot2.png)

注：车身的颜色代表了车的产生地点，车头的颜色表明了车的目的地。

* 运行结果如上，红绿灯实时改变，当碰到红灯的时候车辆停止。
* 运行程序后可看到看到车辆运行路线符合要求！

##意见和建议

大作太难了，特别是没有做过界面的，刚开始无从下手，花了好长时间才做出来。
希望以后作业可以不要求搞界面的，对于没有UI编程经验的人来说，第一次难度好大。
或者老师可以给一下UI方面编程的具体意见。

