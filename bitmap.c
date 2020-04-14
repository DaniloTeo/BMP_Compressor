#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"

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
			fwrite(&R[i][j], sizeof(unsigned char), 1, out);
			fwrite(&G[i][j], sizeof(unsigned char), 1, out);
			fwrite(&B[i][j], sizeof(unsigned char), 1, out);
		}
	}

	fclose(out);
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
