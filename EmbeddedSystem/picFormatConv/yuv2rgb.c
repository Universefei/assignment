#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 50
/*---------------------------------------------------------------------------*/
/*                          definition & declaration                         */
/*---------------------------------------------------------------------------*/
unsigned char *bmpBuf;
unsigned char *pBmpBuf;
unsigned char *header;

int bmpWidth;
int bmpHeight;
int bibitCount;

unsigned char *YBuffer;
unsigned char *UBuffer;
unsigned char *VBuffer;

/*---------------------------------------------------------------------------*/
/*                                 readyuv()                                 */
/*---------------------------------------------------------------------------*/

int 
readyuv(char * bmpName)
{
	FILE *fp = fopen(bmpName,"rb");

	if(NULL == fp ) {
		printf("open %s failed! \n",bmpName);
		return 0;
	}

	/* NB: Do not fread before malloc real space in mem!!! */
	header = (unsigned char *) malloc (54);
	fread(header,1,54,fp);    

	pBmpBuf= (unsigned char *) malloc(1024*768*2);   
	fread(pBmpBuf,1,2*1024*768,fp);
    
	fclose(fp);

	return 1;
}

/*---------------------------------------------------------------------------*/
/*                                  writergb()                               */
/*---------------------------------------------------------------------------*/

int 
writergb(char *pathname,unsigned char *bmpBuf)
{
	FILE *fp = fopen(pathname,"wb");

	if(NULL == fp) {
		return 0;
	}

	/* write bmp header */
	fwrite(header,sizeof(char),54,fp);
	
	/* write bmp data */
    fwrite(bmpBuf, sizeof(char),3*768*1024, fp);

	fclose(fp);
	
	return 1;
}

/*---------------------------------------------------------------------------*/
/*                                 yuv2rgb()                                 */
/*---------------------------------------------------------------------------*/

int 
yuv2rgb(unsigned char *pBmpBuf)
{
    int i,j;
    int R, G, B;
    int Y, U, V;
    //Allocate memory for input and output buffers.
    bmpBuf = (unsigned char *) malloc (768*1024*3);

    for (i=0; i<1024*768; ++i) 
	{
		//printf("processing number %d pixel!\n",i);
		/* ? if i is an even number? */
        int YIndex = i;
        int VIndex = 1024*768+i/2;
        int UIndex = 1024*768+1024*768/2+i/2;

        Y = pBmpBuf[YIndex];
        U = pBmpBuf[UIndex];
        V = pBmpBuf[VIndex];

        R =(unsigned char)( Y + (1.4075 * (V-128)));
        G =(unsigned char) (Y - (0.7169 * (V-128)) - (0.3455 * (U-128)));
        B =(unsigned char) (Y + (1.7790 * (U-128)));

        if(R > 255) R =(unsigned char) 255;
        if(G > 255) G = (unsigned char)255;
        if(B > 255) B =(unsigned char) 255;
        if(R < 0) R =(unsigned char) 0;
        if(G < 0) G =(unsigned char) 0;
        if(B < 0) B =(unsigned char) 0;

        bmpBuf[3*i]=R;
        bmpBuf[3*i+1]=G;
        bmpBuf[3*i+2]=B;
    }
    //Write frames of Y then U then V components
	return 3;
}


/*---------------------------------------------------------------------------*/
/*                                 main()                                    */
/*---------------------------------------------------------------------------*/

int 
main(int argc, char * argv[])
{

	char readpath[BUFSZ];
	char writepath[BUFSZ];

	strcpy(readpath, argv[1]);
	strcpy(writepath, argv[2]);

	/* read YUV pixel pic to mem */
	readyuv(readpath);

	/* convert YUV to RGB */
	printf("converting %s to %s \n",readpath,writepath);
    yuv2rgb(pBmpBuf);
	printf("DONE\n");

	/* data persistence */
    writergb(writepath,bmpBuf);

	return 0;
}

