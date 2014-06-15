#include "Fridge.h"

/**
 * 全局二维数组存每个档的最高温度和最低温度
 * tempTbl[k][0] 存k档时候的最低温度
 * tempTbl[k][1] 存k档时候的最高温度
 */
float tempTbl[MAXTEMPLVL][2]={
				-3.9,-2.0,
				-2.0,0.0,
				0,3
};

Fridge::Fridge() {
				compStat=false;
				temp=20;
				tempLevel=0;
				lightStat=false;
}

Fridge::~Fridge() {
}

void Fridge::open() {
				lightStat=true;
}

void Fridge::close() {
				lightStat=false;
}

/**
 * 获得当前冰箱实时温度
 */
float Fridge::getTemp() {
				return temp;
}

/**
 * 传感器会实时设置冰箱的当前温度,并实时检测是否要启动/关闭压缩机
 */
void Fridge::setTemp(float t) {
				temp=t;
				if(temp>tempTbl[tempLevel][1]) {
								compStat=true;
				}
				if(temp<tempTbl[tempLevel][0]) {
								compStat=false;
				}
}

/**
 * 调节档位，并与当前温度比较看是否需要启动压缩机
 */
void Fridge::setTempLevel(int t) {
				if(t<0||t>=MAXTEMPLVL) {
								cout<<"input tempreture incorecttly!"<<endl;
								return;
				}
				else tempLevel=t;
				
				if(temp>tempTbl[t][1]) {
								compStat=true;
				}
				if(temp<tempTbl[t][0]) {
								compStat=false;
				}

}

/**
 * 获得压缩机状态
 */
bool Fridge::getCompStat() {
				return compStat;
}

