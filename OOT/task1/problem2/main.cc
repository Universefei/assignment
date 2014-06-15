#include <iostream>
#include "Wine.h"
using namespace std;

int main() {
				pkg shop1;
				seprate shop2;

				float tarmnt;
				float tarprice;

				shop1.setMnt(3);
				shop1.setPrice(13.0);
				shop2.setMnt(9.13);
				shop2.setPrice(11.1);

/*****************************************************************************
 * 下面这一句会用到 包含多态/重载多态/强制多态
 * 包含多态：pkg是seprate的子类型
 * 重载多态：重载了+操作符
 * 强制多态：在调用+计算平均单价的时候，double与int类型相加会有强制类型转换
 ****************************************************************************/
				seprate targ=shop2+shop1;

/*****************************************************************************
 * 下面语句用到参数多态
 * cout<< 可以接受不同类型的值答应到标准输出
 ****************************************************************************/
				tarmnt=targ.getMnt();
				tarprice=targ.getPrice();
				cout<<"Total weight:   "<<tarmnt<<endl;
				cout<<"avarege price:  "<<tarprice<<endl;

				return 0;
}

