#include <stdlib.h>
#include <stdio.h>

typedef struct { 						/**** BMP file header structure ****/    
	unsigned short bfType;			/* Magic number for file */ 
	unsigned int   bfSize;			/* Size of file */ 
	unsigned short bfReserved1;		/* Reserved */
	unsigned short bfReserved2;		/* ... */
	unsigned int   bfOffBits;		/* Offset to bitmap data */
} BMPFILEHEADER;					/* bfType deve ser = "MB" */

typedef struct{  /**** BMP file info structure ****/

	unsigned int   biSize;			/* Size of info header */
	int 	 	   biWidth;    		/* Width of image */
	int   		   biHeight;   		/* Height of image */
	unsigned short biPlanes;		/* Number of color planes */
	unsigned short biBitCount;		/* Number of bits per pixel */
	unsigned int   biCompression;	/* Type of compression to use */
	unsigned int   biSizeImage;		/* Size of image data */
	int            biXPelsPerMeter;	/* X pixels per meter */ 
	int            biYPelsPerMeter;	/* Y pixels per meter */
	unsigned int   biClrUsed;		/* Number of colors used */
	unsigned int   biClrImportant;	/* Number of important colors */
} BMPINFOHEADER;


void leituraHeader(FILE *F, BITMAPFILEHEADER *H){
	/* F é o arquivo Bitmap que deve ter sido “lido” do disco */
	fread(&H->Type,sizeof (unsigned short int),1,F);
	fread(&H->Size,sizeof (unsigned int),1,F);
	fread(&H->Reserved1,sizeof (unsigned short int),1,F);
	fread(&H->Reserved2,sizeof (unsigned short int),1,F); 
	fread(&H->OffBits,sizeof (unsigned int),1,F);
}


unsigned char **alocaMatrizUnChar(int lin, int col){
	int i = 0;
	unsigned char **mat = (unsigned char **) malloc(sizeof(unsigned char *) * lin);

	for(i = 0; i < lin; i++){
		mat[i] = (unsigned char *) malloc(sizeof(unsigned char) * col);
	}

	return mat;
}

void liberaMatrizUnChar(unsigned char** matriz, int lin){
	int i = 0;
	for(i = 0; i < lin; i++){
		free(matriz[i]);
	}

	free(matriz);
}

double **alocaMatrizDouble(int lin, int col){
	int i = 0;
	double **mat = (double **) malloc(sizeof(double *) * lin);

	for(i = 0; i < lin; i++){
		mat[i] = (double *) malloc(sizeof(double) * col);
	}

	return mat;
}

void liberaMatrizDouble(double** matriz, int lin){
	int i = 0;
	for(i = 0; i < lin; i++){
		free(matriz[i]);
	}

	free(matriz);
}	







int main(void){
	
	return 0;
}