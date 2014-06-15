#include <stdlib.h>
#include <stdio.h>

typedef void (*MsgHandler) (void);

struct MessageMapEntry {
		char          ch;
		MsgHandler    handler;
};

/*---------------------------------------------------------------------------*/
/*                             Mapping handlers                              */
/*---------------------------------------------------------------------------*/

void fA() {
				printf("Press a\n");
}

void fB() {
				printf("Press b\n");
}

void fC() {
				printf("Press c\n");
}

/*----------------------------------------------------------------------------*/

MessageMapEntry MessageMap[100] = {
				{ 'a', fA},
				{ 'b', fB},
				{ 'c', fC},
				{ 0, NULL}
};


