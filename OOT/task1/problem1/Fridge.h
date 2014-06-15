#include <iostream>
#include <cstdio>
using namespace std;

#define MAXTEMPLVL 3

class Fridge {
				private:
								bool compStat;//压缩机状态
								float temp;//冰箱实时温度
								int tempLevel;//冰箱档位
								bool lightStat;//冰箱灯的状态
				public:
								Fridge();
								~Fridge();
								void open();//打开冰箱
								void close();//关闭冰箱
								float getTemp();//获取冰箱实时温度
								void setTemp(float);//传感器实时设置冰箱温度
								void setTempLevel(int);//调节档位
								bool getCompStat();//获得当前压缩机状态，是否在工作
};

								
