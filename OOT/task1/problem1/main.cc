#include "Fridge.h"

int main() {
				Fridge myfri;
				myfri.open();
				myfri.setTemp(2.1);
				myfri.setTempLevel(2);

				cout<<"compStat:   "<<myfri.getCompStat()<<endl;
				cout<<"currenttemp:"<<myfri.getTemp()<<endl;

				return 0;
}

