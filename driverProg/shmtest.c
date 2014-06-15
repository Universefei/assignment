#include <stdlib.h>
#include <stdio.h>


int
main(int argc, char **argv) {

	int fd, i, nloop, zero = 0;
	int *ptr;
	sem_t *mutex;

	if(argc != 3) {
		err_quit("usage: incr2 <pathname> <#loops>");
	}

	/* argv are all strings (psz: pointer to string,terminated by zero) */
	nloop = atoi ( argv[2] );

	/* open external-stored file and write int */
	fd = open ( argv[1], O_RDDWR | O_CREAT, FILE_MODE );
	write(fd, &zero, sizeof(int));

	/* memory map */
	ptr = mmap ( NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
	close(fd);

	/* Create mutex semaphore */
	mutex = sem_open ( px_ipc_name(SEM_NAME), O_CREAT | O_EXCL, FILE_MODE, 1 );
	sem_unlink ( px_ipc_name ( SEM_NAME ) );

	setbuf( stdout, NULL );

	/* child process */
	if ( fork() == 0 ) {
		for (i=0; i<nloop; ++i) {
			sem_wait( mutex );
			printf ( "child: %d\n", (*ptr)++ );
			sem_post( mutex );
		}
		exit(0);
	}

	/* parent process */
	for (i=0; i<nloop; ++i) {
		sem_wait(mutex);
		printf("parent: %d\n",(*ptr)++);
		sem_post(mutex);
	}

	exit(0);
}


