#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED
// Start of Bitmap Data Structures *******************************************************
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
// End of Bitmap Data Structures ******************************************************

void leituraFileHeader(FILE *F, BMPFILEHEADER *H);

void writeBMPFileHeader(FILE *F, BMPFILEHEADER *H);

void dumpFileHeader(BMPFILEHEADER *h);

void leituraInfoHeader(FILE *f, BMPINFOHEADER *h);

void writeBMPInfoHeader(FILE *f, BMPINFOHEADER *h);

void dumpInfoHeader(BMPINFOHEADER *h);

// End of Bitmap Aux functions ******************************************************

void readBMPImage(FILE *f, unsigned char ***B, unsigned char ***G, unsigned char ***R, int lin, int col);

void writeBMPFile(unsigned char **B, unsigned char **G, unsigned char **R, BMPFILEHEADER *fileHeader, BMPINFOHEADER *infoHeader);	

unsigned char **alocaMatrizUnChar(int lin, int col);

void liberaMatrizUnChar(unsigned char** matriz, int lin);

double **alocaMatrizDouble(int lin, int col);

void liberaMatrizDouble(double** matriz, int lin);

void printUnCharMatriz(unsigned char **m, int lin, int col);

#endif