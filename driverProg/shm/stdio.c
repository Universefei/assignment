#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** argv specification
 *  ==================
 *  argv[1] : bigfile name to be processed
 *  argv[2] : amount of bytes every time to read from stream
 */

int
main(int argc, char **argv) {

	unsigned char buf[100000];
	int i;
	int cntRead = 0;
	long cnt =0;

	FILE *fpopen = fopen(argv[1], "rb+");
	int readLen = atoi(argv[2]);

	while(!feof(fpopen)) {

		cntRead = fread(&buf, 1, readLen, fpopen);

		for (i=0; i<cntRead; ++i) {
			if(buf[i] == 0)
				++cnt;
		}
	}

	fclose(fpopen);
	printf("the number of unsigned char 0 : %ld\n", cnt);

	return 0;
}

