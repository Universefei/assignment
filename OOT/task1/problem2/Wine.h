#include <iostream>
using namespace std;

/*****************************************************************************
 * 商店出售酒水，有两种出售方法：
 *
 * 1. 包装好的，每瓶一斤，不能拆瓶，每次只能买整数瓶，对应class pkg
 * 2. 称斤出售，重量随意，对应class seprate
 *
 ****************************************************************************/

class pkg {
				private: 
								int mnt; //瓶数，也就是斤数
								float price; //每瓶单价
				public:
								pkg();
								~pkg();
								void setMnt(int);
								void setPrice(float);
								int getMnt();
								float getPrice();
								float totalCost();//计算总共花费
}

class seprate {
				private: 
								float mnt; //称重出售的重量
								float price;//单价 
				public:
								seprate();
								~seprate();
								friend seprate operator +(const seprate& buy1,const pkg& buy2);
								void setMnt(int);
								void setPrice(float);
								int getMnt();
								float getPrice();
								float totalCost();
}
				
