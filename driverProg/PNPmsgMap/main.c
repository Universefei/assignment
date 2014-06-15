#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXMSG 100
#define SONAME "./lib/libfei.so"

//#define DEBUG

/******************************************************************************
 *                          definition & declaration                          *
 *****************************************************************************/

typedef void (* MsgHandler) (void);

struct MessageMapEntry {
	char ch;
	MsgHandler handler;
};

struct stat statbuf;
struct stat curstat;

struct MessageMapEntry MessageMap[MAXMSG];

/******************************************************************************
 *                             misc                                           *
 *****************************************************************************/

void
noFunc() {
	printf("Function name can't be found in ./lib/libfei.so!\n");
}

void
MessageMapInit() {
	int i;
	for (i=0;i<MAXMSG;i++) {
		MessageMap[i].ch = 0;
		MessageMap[i].handler = NULL;
	}
}

/******************************************************************************
 *                            conf2MsgMap()                                   *
 *****************************************************************************/

/*----- seekFuncInSo() ------------------------------------------------------*/

/**
 * Find out the Function pointer in ./libfei.so
 *
 * @param *handle       : handle of the dlopen-ed *.so file
 * @param *function     : function name to be searched
 *
 * @return Function Address in handle's dynamic link lib
 */

MsgHandler
seekFuncInSo(void* handle,
							void* funcname
) {
	/* TODO: everytime check handler address will load lib,low efficiency */
	MsgHandler gothandler = (MsgHandler) dlsym(handle, (char*)funcname);
	if (NULL == gothandler) {
		printf("Handler function %s is in file ./MsgMap.conf \n",(char *)funcname);
		printf("But it is not implement in ./lib/libfei.so \n");
		printf("Make sure function implemented and run ./demo.sh --lib before modify ./MsgMap.conf\n");
		return (MsgHandler)noFunc;
	} 
	return gothandler;
				
}

/*----- readTuple() ---------------------------------------------------------*/

/**
 * Read a line (a tuple) in the configure file
 *
 * @param i *file  : the opened configure file
 * @param o *Msg   : message char got
 * @param o *name  : the function name got frome the file line
 *
 * @return  0=end of file; 1=not end of file
 */
int 
readTuple(FILE* file, char* Msg, char* name) { 
	char buf[60];
	if(fgets(buf, 60, file) == NULL) return 0;
	if (sscanf(buf, "%c %s", Msg, name) < 0) {
		printf("read error!\n");
	}
#ifdef DEBUG
	printf("DEBUG: message:%c handlername: %s\n",*Msg, name);
#endif
	return 1;
}

/*----- conf2MsgMap() -------------------------------------------------------*/

/**
 * Open and Read config file, searching correspongding Message handling 
 * function in dynamic lib,and set MessageMap table
 */
void
conf2MsgMap(void* handle) {
	/**
	 * How to set MessageMap values from config file
	 * =============================================
	 * Three steps:
	 * 1] open and read configure file (./MsgMap.conf)
	 * 2] search function in *.so file (,/lib/libfei.so)
	 * 3] set global MessageMap Table
	 */
	char gotMsg;
	char gotName[50];

	/**
 	 * readFlag = 0 : end of file
 	 * readFlag = 1 : not end of file
 	 */
	int readFlag=1;

	/* open configuration file */
	FILE* openedconf = fopen("./MsgMap.conf","r");

	/* read config file and set global MsgMap Table */
	int i = 0;
	while (i<MAXMSG) {
		readFlag = readTuple(openedconf, &gotMsg, gotName);
		if(readFlag !=0) {
#ifdef DEBUG
			printf("DEBUG: read one tuple \n");
#endif
			MessageMap[i].ch = gotMsg;
			MessageMap[i].handler = seekFuncInSo(handle, (void*)gotName);
			i++;
		} else  break;
	};
	if (readFlag) {
		printf("exceed max message limit\n");
	} 

	/* close config file */
	fclose(openedconf);

#ifdef DEBUG
	printf("DEBUG: conf2MsgMap excute! refresh MessageMap \n");
#endif
}

/******************************************************************************
 *                             threadProc()                                  *
 *****************************************************************************/

/**
 * This thread is responsed to monitor config file, and reload dynamic link 
 * lib, set global MessageMap table
 */
void threadProc(void* handle) {
#ifdef DEBUG
	printf("DEBUG: thread starting manage dynamic lib!\n");
#endif
	while(1) {
#ifdef DEBUG
		printf("DEBUG: checking MsgMap.conf stat \n");
#endif
		/* check config file status */
		stat("./MsgMap.conf", &curstat);
		/* compare current stat modified-time stamp to statbuf */
		if (curstat.st_mtime != statbuf.st_mtime) {
			statbuf = curstat;
			/* since *.so have changed kick out it from mem */
			dlclose(handle);
			/* reload *.so */
			handle = dlopen(SONAME, RTLD_NOW);
			/* reset MessageMmap */
			conf2MsgMap(handle);
		}
		/* check every other 5 sec. */
		sleep(5);
	}
}

/******************************************************************************
 *                                  main()                                    *
 *****************************************************************************/

int 
main() {
	pthread_t id;
	char ch;

	MessageMapInit();
	void* handle = dlopen(SONAME, RTLD_NOW);

	conf2MsgMap(handle);
	stat("./MsgMap.conf", &statbuf);

	/* create thread to manage dynamic lib and check conf file update */
	pthread_create(&id, NULL, (void *)threadProc, handle);

	/* main process to handle user request */
	/* wait for source config file complete! */
	printf("Press a Key: \n");

	while(scanf("%c",&ch)&&ch!='x') {
		int i;
		int flag = 0;

		if(ch == '\n') continue;
		for(i=0;(MessageMap[i].ch != 0) && (i < MAXMSG);i++) {
			if (MessageMap[i].ch == ch) {
				MessageMap[i].handler();
				flag =1;
				break;
			}
		}
		if(!flag) {
			printf("no such message in MsgMap.conf\n");
		}
	}

	pthread_join(id, NULL);
	return 0;
}
