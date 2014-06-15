#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 60

int
main() {

	char readbuf[BUFSZ];
	FILE* fp = fopen("./MsgMap.conf","r");
	
	char msg[10];
	char handle[BUFSZ-10];

	while (fgets(readbuf,BUFSZ,fp)) {
		sscanf(readbuf,"%s %s",msg,handle);
	/*	
		(char *)msg = gets(readbuf);
		(char *)handle = gets(readbuf);
		*/
		printf("msg: %s  handle: %s\n",msg,handle);
	}
	
	return 0;
}

		

