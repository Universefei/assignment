#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int 
main(int argc, char **argv) {

	int fdopen, i;
	unsigned char *ptr;
	long cnt = 0;

	/* get file bulk */
	struct stat opfile;
	stat(argv[1], &opfile);

	/* open file */
	fdopen = open(argv[1], O_RDWR);

	/* memory map */
	ptr = (unsigned char *) mmap(0, opfile.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdopen, 0);

	/* read all external storage content */
	for(i = 0; i < opfile.st_size; ++i ) {
		if(ptr[i] == 0)
			++cnt;
	}

	printf("the number of unsigned char 0 : %ld\n", cnt);

	return 0;
}


	
