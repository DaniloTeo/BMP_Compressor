#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bitmap.h"
#include "DCT.h"
#include "zigzag.h"
#include "rle.h"
#include "quant.h"

int main(int argc, char *argv[]){
  int i,j;
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


	double **Y = alocaMatrizDouble(infoHeader.biHeight, infoHeader.biWidth);
	double **Cb = alocaMatrizDouble(infoHeader.biHeight, infoHeader.biWidth);
	double **Cr = alocaMatrizDouble(infoHeader.biHeight, infoHeader.biWidth);
  

	printf("Applying RGB --> YCbCr Conversion\n");
	RGB2YCbCr(R, G, B, infoHeader.biHeight, infoHeader.biWidth, Y, Cb, Cr);

	printf("Applying DCT to YCbCr Components...\n");
	double **YAfterDCT = DCTImage(Y, infoHeader.biWidth, infoHeader.biHeight);
	double **CbAfterDCT = DCTImage(Cb, infoHeader.biWidth, infoHeader.biHeight);
	double **CrAfterDCT = DCTImage(Cr, infoHeader.biWidth, infoHeader.biHeight);
	


	printf("Applying ZigZagWalk...\n");
	int Yzz_len = 0, Cbzz_len = 0, Crzz_len = 0;
	double **Yzz = zigzagImage(YAfterDCT, infoHeader.biWidth, infoHeader.biHeight, &Yzz_len);
	double **Cbzz = zigzagImage(CbAfterDCT, infoHeader.biWidth, infoHeader.biHeight, &Cbzz_len);
	double **Crzz = zigzagImage(CrAfterDCT, infoHeader.biWidth, infoHeader.biHeight, &Crzz_len);
	
	printf("Appyling RLE Encoding....\n");
	ENCODED_IMAGE ** Y_rle = encodeImage(Yzz, Yzz_len);
	ENCODED_IMAGE ** Cb_rle = encodeImage(Cbzz, Cbzz_len);
	ENCODED_IMAGE ** Cr_rle = encodeImage(Crzz, Crzz_len);

  
  	printf("Writing binary file....\n");
  	writeENCODEDFile(&fileHeader, Y_rle, Cb_rle, Cr_rle, &infoHeader);

	// Liberacao de memoria do descompressor
	// Liberacao dos componentes YCbCr
	freeDoubleMatrix(Y, infoHeader.biHeight);
	freeDoubleMatrix(Cb, infoHeader.biHeight);
	freeDoubleMatrix(Cr, infoHeader.biHeight);

	//Liberacao dos componentes RGB
	liberaMatrizUnChar(R,infoHeader.biHeight);
	liberaMatrizUnChar(G,infoHeader.biHeight);
	liberaMatrizUnChar(B,infoHeader.biHeight);


	// Liberacao dos vetores pos-DCT
	freeDoubleMatrix(YAfterDCT, infoHeader.biHeight);
	freeDoubleMatrix(CbAfterDCT, infoHeader.biHeight);
	freeDoubleMatrix(CrAfterDCT, infoHeader.biHeight);

	freeDoubleMatrix(Yzz, Yzz_len);
	freeDoubleMatrix(Cbzz, Cbzz_len);
	freeDoubleMatrix(Crzz, Crzz_len);

	freeVetorEncoded(Y_rle, Yzz_len);
	freeVetorEncoded(Cb_rle, Cbzz_len);
	freeVetorEncoded(Cr_rle, Crzz_len);

	fclose(f);

	//Essa parte fica no descompressor --------------------------------------------------------
	// setup para leitura do arquivo:
	f = NULL;
	ENCODED_IMAGE **Y_in = NULL, **Cb_in = NULL, **Cr_in = NULL;

	readENCODEDFile(f, &fileHeader, &infoHeader, &Y_in, &Cb_in, &Cr_in);

	// decode
	int zigzag_len = ((infoHeader.biWidth * infoHeader.biHeight)/(8*8));



	printf("Decoding matrixes into ZigZag Array...\n");
	double **Yzz_in = decodeImage(Y_in, zigzag_len);
	double **Cbzz_in = decodeImage(Cb_in, zigzag_len);
	double **Crzz_in = decodeImage(Cr_in, zigzag_len);




	printf("Applying deZigZag...\n");
	double **YAfterdeZZ_in = deZigZagImage(Yzz_in, zigzag_len, infoHeader.biWidth, infoHeader.biHeight);
	double **CbAfterdeZZ_in = deZigZagImage(Cbzz_in, zigzag_len, infoHeader.biWidth, infoHeader.biHeight);
	double **CrAfterdeZZ_in = deZigZagImage(Crzz_in, zigzag_len, infoHeader.biWidth, infoHeader.biHeight);


	printf("Applying IDCT to YCbCr Components...\n");
	double **YAfterIDCT = IDCTImage(YAfterdeZZ_in, infoHeader.biWidth, infoHeader.biHeight);
	double **CbAfterIDCT = IDCTImage(CbAfterdeZZ_in, infoHeader.biWidth, infoHeader.biHeight);
	double **CrAfterIDCT = IDCTImage(CrAfterdeZZ_in, infoHeader.biWidth, infoHeader.biHeight);

	printf("Applying YCbCr --> RGB Conversion\n");
	unsigned char **B_in = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	unsigned char **G_in = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	unsigned char **R_in = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	
	
	YCbCr2RGB(YAfterIDCT, CbAfterIDCT, CrAfterIDCT,  infoHeader.biHeight, infoHeader.biWidth, R_in, G_in, B_in);

	printf("Writing output file to disk...\n");
	writeBMPFile(B_in, G_in, R_in, &fileHeader, &infoHeader);
	


	// Liberacao de Memoria

	

	freeVetorEncoded(Y_in, zigzag_len);
	freeVetorEncoded(Cb_in, zigzag_len);
	freeVetorEncoded(Cr_in, zigzag_len);



	freeDoubleMatrix(Yzz_in, zigzag_len);
	freeDoubleMatrix(Cbzz_in, zigzag_len);
	freeDoubleMatrix(Crzz_in, zigzag_len);

	freeDoubleMatrix(YAfterdeZZ_in, infoHeader.biHeight);
	freeDoubleMatrix(CbAfterdeZZ_in, infoHeader.biHeight);
	freeDoubleMatrix(CrAfterdeZZ_in, infoHeader.biHeight);

	freeDoubleMatrix(YAfterIDCT, infoHeader.biHeight);
	freeDoubleMatrix(CbAfterIDCT, infoHeader.biHeight);
	freeDoubleMatrix(CrAfterIDCT, infoHeader.biHeight);

	liberaMatrizUnChar(R_in,infoHeader.biHeight);
	liberaMatrizUnChar(G_in,infoHeader.biHeight);
	liberaMatrizUnChar(B_in,infoHeader.biHeight);

	// fclose(f);
	
	return 0;
}