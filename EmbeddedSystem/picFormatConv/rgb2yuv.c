#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFSZ 50

/*---------------------------------------------------------------------------*/
/*                           definition & declaration                        */
/*---------------------------------------------------------------------------*/

unsigned char *header;
unsigned char *bmpBuf;
unsigned char *pBmpBuf;

int bmpWidth;
int bmpHeight;
int bibitCount;

unsigned char *YBuffer;
unsigned char *UBuffer;
unsigned char *VBuffer;

/*---------------------------------------------------------------------------*/
/*                               readbmp()                                   */
/*---------------------------------------------------------------------------*/

/* read pic from external storage to internal memory */
int 
readbmp(char *bmpName)
{
	/* read binary and check status */
	FILE *fp = fopen(bmpName,"rb");
	if(fp == 0 )return 0;

	/* read bmp format pic header to pszheader */
    header=(unsigned char *) malloc(54); 
	fread(header,1,54,fp);  

	/* how many bytes need to store one line pixels */
	int lineByte = 24 * 1024 / 8 ;
	
	/* allocate space for entire picture */
	pBmpBuf=(unsigned char *) malloc(lineByte * 768);    
	/* read external storage to allocated internal memory */
	fread(pBmpBuf,1,lineByte * 768,fp);

	/*fclose(fp);*/

	return 1;
}

/*---------------------------------------------------------------------------*/
/*                               writebmp()                                  */
/*---------------------------------------------------------------------------*/

/* write UVB format pixel pic from memory to external storage */
int 
writebmp(char *pathname,unsigned char *YBuffer,
		unsigned char *UBuffer,unsigned char *VBuffer,
		unsigned char *header)
{
	/* write binary */
	FILE *fp = fopen(pathname,"wb");

	if(fp == 0) return 0;

	/* write header */
	fwrite(header,sizeof(char),54,fp);

	/* store YUV infos */
    fwrite(YBuffer, sizeof(char), 768*1024, fp);
	fwrite(VBuffer, sizeof(char), 768*1024/2, fp);
	fwrite(UBuffer, sizeof(char), 768*1024/2, fp);
	fclose(fp);
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*                                  rgb2yuv()                                */
/*---------------------------------------------------------------------------*/

/* convert RGB to YUV */
int 
rgb2yuv(unsigned char *bmpBuf)
{
    int i,j;
    int R, G, B;
    int Y, U, V;
    //Allocate memory for input and output buffers.
   
	/* this syntax? inner the malloc clause */
    YBuffer = (unsigned char * ) malloc(768*1024); 
	
	/* why divid 2? compass? */
    UBuffer = (unsigned char * ) malloc(768*1024/2);
    VBuffer = (unsigned char * ) malloc(768*1024/2);
	if (YBuffer == NULL || UBuffer == NULL || VBuffer == NULL) {
			printf("memory heap allocate failed!\n");
	}

    //Define some working variables and arrays
    //Define buffers for filtering (width+2 to allow filtering edges)
	//one byte for 2 edges left and right respectively
    unsigned char *ULine = ((unsigned char *) malloc(1024+2))+1;
    unsigned char *VLine = ((unsigned char *) malloc(1024+2))+1;

	/* what does -1 means? filtering edges */
    ULine[-1]=ULine[1024]=128;
    VLine[-1]=VLine[1024]=128;
    
    for (i=0; i<768; i++) {

		/* process line by line */
        int RGBIndex = 3*1024*i;
        int YIndex   = 1024*i; /* 1024 byte per line to store Y (8bit) */
        int UVIndex  = 1024*i/2; /* 1024/2 = 512 line to store U or V (4bit) */
        
        for ( j=0; j<1024; j++) {
			R = bmpBuf[RGBIndex++];
			G = bmpBuf[RGBIndex++];
			B = bmpBuf[RGBIndex++];

			//Convert RGB to YUV
			Y = (unsigned char) (0.299*R+0.587*G+0.114*B );
			V = (unsigned char) (0.5*R-0.4187*G-0.0813*B+128); 
			U = (unsigned char) (-0.1687*R-0.3313*G+0.5*B+128);


			/* write YUV to pixel, direct to Output file mirror */
			//Clip Y ready for output & copy UV ready for filtering
			if(Y>255 || Y==255) {
			 YBuffer[YIndex++] = (unsigned char) 255;
			}
			if(Y<0 || Y==0) {
			 YBuffer[YIndex++] = (unsigned char) 0;
			}
			if(0<Y && Y<255) {
			 YBuffer[YIndex++] = (unsigned char) Y;
			}
			/* write U,V to temperory line buff */
			VLine[j] = V;
			ULine[j] = U;
        }

        for ( j=0; j<1024; j+=2) {

			//Filter line & Convert algorithm
			V = ((VLine[j-1]+2*VLine[j]+VLine[j+1]+2)/4);
			U = ((ULine[j-1]+2*ULine[j]+ULine[j+1]+2)/4);

			if(V>255 || V==255) VBuffer[UVIndex] =(unsigned char) 255;
			if(U>255 || U==255) UBuffer[UVIndex++]= (unsigned char) 255;

			if(V<0 || V==0) VBuffer[UVIndex] =(unsigned char) 0;
			if(U<0 || U==0) UBuffer[UVIndex++]=(unsigned char) 0;

			if(0<V && V<255) VBuffer[UVIndex] =(unsigned char) V;
			if(0<U && U<255) UBuffer[UVIndex++]= (unsigned char) U;
			 //Clip and copy UV to output buffer    
        }
     
    }

	return 3;

}


/******************************************************************************
 *                                  main()                                    *
 *****************************************************************************/

int 
main(int argc, char * argv[]) 
{
	char readpath[BUFSZ];
	char writepath[BUFSZ];

	strcpy(readpath, argv[1]);
	strcpy(writepath, argv[2]);

	/* read pic from hardisk to memory */
	readbmp(readpath);
   
	/* convert algorithem */
	printf("Converting %s to %s \n", readpath, writepath);
    rgb2yuv(pBmpBuf);
	printf("DONE\n");

	/* data persistence */
    writebmp(writepath,YBuffer,UBuffer,VBuffer,header);
	
	return 0;
}

