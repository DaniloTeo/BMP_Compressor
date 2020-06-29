#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"
#include "rle.h"
#include "encoder.h"

/*Start of Bitmap Aux functions *******************************************************/
void leituraFileHeader(FILE *F, BMPFILEHEADER *H){
	/* F é o arquivo Bitmap que deve ter sido “lido” do disco */
	fread(&H->bfType,sizeof (unsigned short int),1,F);
	fread(&H->bfSize,sizeof (unsigned int),1,F);
	fread(&H->bfReserved1,sizeof (unsigned short int),1,F);
	fread(&H->bfReserved2,sizeof (unsigned short int),1,F); 
	fread(&H->bfOffBits,sizeof (unsigned int),1,F);
}

void writeBMPFileHeader(FILE *F, BMPFILEHEADER *H){
	fwrite(&H->bfType,sizeof (unsigned short int),1,F);
	fwrite(&H->bfSize,sizeof (unsigned int),1,F);
	fwrite(&H->bfReserved1,sizeof (unsigned short int),1,F);
	fwrite(&H->bfReserved2,sizeof (unsigned short int),1,F); 
	fwrite(&H->bfOffBits,sizeof (unsigned int),1,F);
}

void dumpFileHeader(BMPFILEHEADER *h){
	printf("Magic Number of File: %hu\n", h->bfType);
	printf("Size of File: %hu\n", h->bfSize);
	printf("Reserved Var 1: %hu\n", h->bfReserved1);
	printf("Reserved Var 2: %hu\n", h->bfReserved2);
	printf("Offset to Bitmap Data: %hu\n", h->bfOffBits);
	printf("-----+-----+-----+-----+-----+-----+\n");
}

void leituraInfoHeader(FILE *f, BMPINFOHEADER *h){
	fread(&h->biSize, sizeof(unsigned int), 1, f);
	fread(&h->biWidth, sizeof(int), 1, f);
	fread(&h->biHeight, sizeof(int), 1, f);
	fread(&h->biPlanes, sizeof(unsigned short), 1, f);
	fread(&h->biBitCount, sizeof(unsigned short), 1, f);
	fread(&h->biCompression, sizeof(unsigned int), 1, f);
	fread(&h->biSizeImage, sizeof(unsigned int), 1, f);
	fread(&h->biXPelsPerMeter, sizeof(int), 1, f);
	fread(&h->biYPelsPerMeter, sizeof(int), 1, f);
	fread(&h->biClrUsed, sizeof(unsigned int), 1, f);
	fread(&h->biClrImportant, sizeof(unsigned int), 1, f);
}

void writeBMPInfoHeader(FILE *f, BMPINFOHEADER *h){
	fwrite(&h->biSize, sizeof(unsigned int), 1, f);
	fwrite(&h->biWidth, sizeof(int), 1, f);
	fwrite(&h->biHeight, sizeof(int), 1, f);
	fwrite(&h->biPlanes, sizeof(unsigned short), 1, f);
	fwrite(&h->biBitCount, sizeof(unsigned short), 1, f);
	fwrite(&h->biCompression, sizeof(unsigned int), 1, f);
	fwrite(&h->biSizeImage, sizeof(unsigned int), 1, f);
	fwrite(&h->biXPelsPerMeter, sizeof(int), 1, f);
	fwrite(&h->biYPelsPerMeter, sizeof(int), 1, f);
	fwrite(&h->biClrUsed, sizeof(unsigned int), 1, f);
	fwrite(&h->biClrImportant, sizeof(unsigned int), 1, f);
}

void dumpInfoHeader(BMPINFOHEADER *h){
	printf("Size of Info Header: %hu\n", h->biSize);
	printf("Width of Image: %d\n", h->biWidth);
	printf("Height of Image: %d\n", h->biHeight);
	printf("No of Color Planes: %hu\n", h->biPlanes);
	printf("No of Bits per Pixel: %hu\n", h->biBitCount);
	printf("Type of Compression to Use: %u\n", h->biCompression);
	printf("Size of Image Data: %u\n", h->biSizeImage);
	printf("X Pixels per Meter: %d\n", h->biXPelsPerMeter);
	printf("Y Pixels per Meter: %d\n", h->biYPelsPerMeter);
	printf("No of Colors Used: %u\n", h->biClrUsed);
	printf("No of Important Colors: %u\n", h->biClrImportant);
	printf("-----+-----+-----+-----+-----+-----+\n");
}
void writeENCODEDFile(BMPFILEHEADER *fileHeader, ENCODED_IMAGE **Y, ENCODED_IMAGE **Cb, ENCODED_IMAGE **Cr, BMPINFOHEADER *infoHeader){
  int i = 0;
  	printf("bitmap:79\n");
	FILE *out = fopen("out.xbl", "wb");
	printf("bitmap:81\n");
	writeBMPFileHeader(out, fileHeader);
	writeBMPInfoHeader(out, infoHeader);
  printf("bitmap:84\n");
  printf("ftell(out): %d\n",(int)ftell(out));
  EI2File(Y, out, (infoHeader->biHeight * infoHeader->biWidth) / (8*8));
  printf("bitmap:86\n");
  EI2File(Cb, out, (infoHeader->biHeight * infoHeader->biWidth) / (8*8));
  printf("bitmap:88\n");
  EI2File(Cr, out, (infoHeader->biHeight * infoHeader->biWidth) / (8*8));
  printf("bitmap:90\n");

  fclose(out);
}

void readENCODEDFile(FILE *F, BMPFILEHEADER *H, BMPINFOHEADER *I , ENCODED_IMAGE **Y, ENCODED_IMAGE **Cb, ENCODED_IMAGE**Cr) {
  F = fopen("out.xbl", "rb");
  leituraFileHeader(F, H);
  leituraInfoHeader(F, I);
  int nOfRLEs = (I->biHeight * I->biWidth) / (8*8);

  File2EI(Y, F, nOfRLEs);
  File2EI(Cb, F, nOfRLEs);
  File2EI(Cr, F, nOfRLEs);


  fclose(F);
}

/*End of Bitmap Aux functions *******************************************************/

void readBMPImage(FILE *f, unsigned char ***B, unsigned char ***G, unsigned char ***R, int lin, int col){
	int i = 0, j = 0;

	for(i = 0; i < lin; i++){
		for(j = 0; j < col; j++){
			(*B)[i][j] = fgetc(f);
			(*G)[i][j] = fgetc(f);
			(*R)[i][j] = fgetc(f);
		}
	}
}

void writeBMPFile(unsigned char **B, unsigned char **G, unsigned char **R, BMPFILEHEADER *fileHeader, BMPINFOHEADER *infoHeader){
	int i = 0, j = 0;
	int lin = infoHeader->biHeight, col = infoHeader->biWidth;
	FILE *out = fopen("out.bmp", "wb");
	
	// Escreve os cabeçalhos
	writeBMPFileHeader(out, fileHeader);
	writeBMPInfoHeader(out, infoHeader);
	
	// Escreve os dados da imagem
	for(i = 0; i < lin; i++){
		for(j = 0; j < col; j++){
			fwrite(&B[i][j], sizeof(unsigned char), 1, out);
			fwrite(&G[i][j], sizeof(unsigned char), 1, out);
			fwrite(&R[i][j], sizeof(unsigned char), 1, out);
		}
	}

	fclose(out);
}	

void RGB2YCbCr(unsigned char **R, unsigned char **G, unsigned char **B, int height, int width, double **Y, double **Cb, double **Cr){
	int i, j;

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			Y[i][j] = (0.299f * (R[i][j]) + 0.587f * (G[i][j]) + 0.114f * (B[i][j]));
			Cb[i][j] = 0.564f * (B[i][j] - Y[i][j]);
			Cr[i][j] = 0.713f * (R[i][j] - Y[i][j]);
		}
	}
}


void YCbCr2RGB(double **Y, double **Cb, double **Cr,  int height, int width, unsigned char **R, unsigned char **G, unsigned char **B){
	int i, j;

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			R[i][j] = Y[i][j] + (1.402f * Cr[i][j]);
			G[i][j] = Y[i][j] - (0.344f * Cb[i][j]) - (0.714f * Cr[i][j]);
			B[i][j] = Y[i][j] + (1.772f * Cb[i][j]);
		}
	}
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

void printUnCharMatriz(unsigned char **m, int lin, int col){
	int i,j;
	for (i = 0; i < lin; i++){
		for(j = 0; j < col; j++){
			printf("%u ", m[i][j]);
		}
		printf("\n");
	}
}


