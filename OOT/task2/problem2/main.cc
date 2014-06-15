#include <iostream>
#include <cstdio>
#include "myType.h"
using namespace std;

int main() {
				MyType<int> s1(10), s2(-5), s3;
				MyType<double> s4(10.3), s5(5.2), s6;
				s3 = s1 + s2;
				s6 = s4 - s5;
				printf(" s1.value = %d s2.value = %d s3.value = %d\n",s1.getValue(),s2.getValue(),s3.getValue());
				printf(" s4.value = %2.1f s5.value = %2.1f s6.value = %2.1f\n",s4.getValue(),s5.getValue(),s6.getValue());
				return 0;
}

