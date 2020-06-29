#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED
#include "rle.h"

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

/*
void leituraFileHeader: realiza a leitura do cabeçalho da imagem.
PARAMETROS:
	FILE *F: arquivo a ser lido;
	BMPFILEHEADER *H: ponteiro para a struct que contem as informações do cabeçalho
RETORNO:
	[retorno por derreferência]
*/
void leituraFileHeader(FILE *F, BMPFILEHEADER *H);

/*
void writeBMPFileHeader: escreve as informações do cabeçalho em um arquivo binario.
PARAMETROS:
	FILE *F: arquivo no qual o header será escrito;
	BMPFILEHEADER *H: cabeçalho a ser escrito no arquivo.
RETORNO:
	---

*/
void writeBMPFileHeader(FILE *F, BMPFILEHEADER *H);

/*
void dumpFileHeader: imprime as informações do BMPFILEHEADER *h na stdout
*/
void dumpFileHeader(BMPFILEHEADER *h);

/*
void leituraInfoHeader: realiza a leitura do cabeçalho da imagem.
PARAMETROS:
	FILE *F: arquivo a ser lido;
	BMPINFOHEADER *H: ponteiro para a struct que contem as informações do cabeçalho
RETORNO:
	[retorno por derreferência]
*/
void leituraInfoHeader(FILE *f, BMPINFOHEADER *h);

/*
void writeBMPInfoHeader: escreve as informações do cabeçalho em um arquivo binario.
PARAMETROS:
	FILE *F: arquivo no qual o header será escrito;
	BMPINFOHEADER *H: cabeçalho a ser escrito no arquivo.
RETORNO:
	---

*/
void writeBMPInfoHeader(FILE *f, BMPINFOHEADER *h);

/*
void dumpInfoHeader: imprime as informações do BMPINFOHEADER *h na stdout
*/
void dumpInfoHeader(BMPINFOHEADER *h);

// End of Bitmap Aux functions ******************************************************

/*
void readBMPImage: função que le do disco um arquivo .bmp para processamento.
PARARAMETROS:
	FILE *f: arquivo da imagem original
	unsigned char ***B, ***G, ***R: ponteiros para matrizes de unsigned char de cada componente da imagem
	int lin, col: dimensões da imagem, obtidas da leitura do cabeçalho
RETORNO:
	[retorno por derreferência]
*/
void readBMPImage(FILE *f, unsigned char ***B, unsigned char ***G, unsigned char ***R, int lin, int col);

/*
void writeBMPFile: função que escreve no disco o arquivo da imagem após o processamento.
PARAMETROS:
	unsigned char **B, **G, **R: matrizes contendo as componentes RGB da imagem
	BMPFILEHEADER *fileHeader, BMPINFOHEADER *infoHeader: cabeçalhos do arquivo original
RETORNO:
	---
*/
void writeBMPFile(unsigned char **B, unsigned char **G, unsigned char **R, BMPFILEHEADER *fileHeader, BMPINFOHEADER *infoHeader);	

/*
void RGB2YCbCr: função que cuida da conversão RGB para YCbCr trocando o tipo das componentes de
				unsigned char para double
*/
void RGB2YCbCr(unsigned char **R, unsigned char **G, unsigned char **B, int height, int width, double **Y, double **Cb, double **Cr);


/*
void YCbCr2RGB: função inversa da RGB2YCbCr
*/
void YCbCr2RGB(double **Y, double **Cb, double **Cr,  int height, int width, unsigned char **R, unsigned char **G, unsigned char **B);

//******* Funções auxiliares de manipulação de matrizes ****************************************
unsigned char **alocaMatrizUnChar(int lin, int col);

void liberaMatrizUnChar(unsigned char** matriz, int lin);

double **alocaMatrizDouble(int lin, int col);

void liberaMatrizDouble(double** matriz, int lin);

void printUnCharMatriz(unsigned char **m, int lin, int col);

void writeENCODEDFile(BMPFILEHEADER *fileHeader, ENCODED_IMAGE *Y, ENCODED_IMAGE *Cb, ENCODED_IMAGE *Cr, BMPINFOHEADER *infoHeader);


#endif