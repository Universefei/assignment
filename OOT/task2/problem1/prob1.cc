#include <iostream>
#include "fei.h"
#include <cstdio>

using namespace std;
namespace lun 
{
void hello() {
printf("   Hello,world!\n");
}
}

using fei::hello;
int main () {
	hello();
	return 0;
}
	
