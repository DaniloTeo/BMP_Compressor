#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bitmap.h"
#include "DCT.h"
#include "quantization.h"

int main(int argc, char *argv[]){
	// Alocando memoria pra arquivo
	printf("Opening %s file..\n", argv[1]);
	FILE *f = fopen(argv[1], "rb");
	printf("File opened!\n");

	// Leitura e Exibição do File Header
	printf("Reading File Header...\n");
	BMPFILEHEADER fileHeader;
	leituraFileHeader(f, &fileHeader);
	dumpFileHeader(&fileHeader);

	// Leitura e Exibição do infoHeader
	printf("Reading Image Header...\n");
	BMPINFOHEADER infoHeader;
	leituraInfoHeader(f, &infoHeader);
	dumpInfoHeader(&infoHeader);

	// Leitura dos componentes B,G,R da imagem
	printf("Loading BGR Image components...\n");
	unsigned char **B = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	unsigned char **G = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	unsigned char **R = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	readBMPImage(f, &B, &G, &R,infoHeader.biHeight, infoHeader.biWidth);
	printf("Image loaded!\n");


	//Aplicação da DCT
	printf("Applying DCT to BGR Components...\n");
	double **BAfterDCT = DCTImage(B, infoHeader.biWidth, infoHeader.biHeight);
	double **GAfterDCT = DCTImage(G, infoHeader.biWidth, infoHeader.biHeight);
	double **RAfterDCT = DCTImage(R, infoHeader.biWidth, infoHeader.biHeight);

	printf("Applying Quantization...\n");
	double **BQuantized = quantizeImage(BAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	double **GQuantized = quantizeImage(GAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	double **RQuantized = quantizeImage(RAfterDCT, infoHeader.biWidth, infoHeader.biHeight);

	//Aplicacao da DCT inversa (Essa parte fica no descompressor)
	printf("Applying IDCT to BGR Components...\n");
	B = IDCTImage(BAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	G = IDCTImage(GAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	R = IDCTImage(RAfterDCT, infoHeader.biWidth, infoHeader.biHeight);


	// Escreve output
	printf("Writing output file to disk...\n");
	writeBMPFile(B, G, R, &fileHeader, &infoHeader);
	


	// Liberacao de Memoria

	freeDoubleMatrix(BQuantized, infoHeader.biHeight);
	freeDoubleMatrix(GQuantized, infoHeader.biHeight);
	freeDoubleMatrix(RQuantized, infoHeader.biHeight);
	freeDoubleMatrix(RAfterDCT, infoHeader.biHeight);
	freeDoubleMatrix(GAfterDCT, infoHeader.biHeight);
	freeDoubleMatrix(BAfterDCT, infoHeader.biHeight);
	liberaMatrizUnChar(R,infoHeader.biHeight);
	liberaMatrizUnChar(G,infoHeader.biHeight);
	liberaMatrizUnChar(B,infoHeader.biHeight);
	fclose(f);
	
	return 0;
}