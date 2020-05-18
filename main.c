#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bitmap.h"
#include "DCT.h"
#include "quantization.h"
#include "zigzag.h"

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


	double **Y = alocaMatrizDouble(infoHeader.biHeight, infoHeader.biWidth);
	double **Cb = alocaMatrizDouble(infoHeader.biHeight, infoHeader.biWidth);
	double **Cr = alocaMatrizDouble(infoHeader.biHeight, infoHeader.biWidth);


	printf("Applying RGB --> YCbCr Conversion\n");
	RGB2YCbCr(R, G, B, infoHeader.biHeight, infoHeader.biWidth, Y, Cb, Cr);

	//Aplicação da DCT
	printf("Applying DCT to YCbCr Components...\n");
	double **YAfterDCT = DCTImage(Y, infoHeader.biWidth, infoHeader.biHeight);
	double **CbAfterDCT = DCTImage(Cb, infoHeader.biWidth, infoHeader.biHeight);
	double **CrAfterDCT = DCTImage(Cr, infoHeader.biWidth, infoHeader.biHeight);

	printf("Applying Quantization...\n");
	double **YQuantized = quantizeImage(YAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	double **CbQuantized = quantizeImage(CbAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	double **CrQuantized = quantizeImage(CrAfterDCT, infoHeader.biWidth, infoHeader.biHeight);

	//zigzag
	int cont_y = 0, cont_cb = 0, cont_cr = 0;

	printf("Applying ZigZagWalk...\n");
	double **Yzz = zigzagImage(YAfterDCT, infoHeader.biWidth, infoHeader.biHeight, &cont_y);
	double **Cbzz = zigzagImage(CbAfterDCT, infoHeader.biWidth, infoHeader.biHeight, &cont_cb);
	double **Crzz = zigzagImage(CrAfterDCT, infoHeader.biWidth, infoHeader.biHeight, &cont_cr);
	
	




	//Essa parte fica no descompressor --------------------------------------------------------


	//dezigzag
	printf("Applying deZigZag...\n");
	YAfterDCT = deZigZagImage(Yzz, cont_y, infoHeader.biWidth, infoHeader.biHeight);
	CbAfterDCT = deZigZagImage(Cbzz, cont_cb, infoHeader.biWidth, infoHeader.biHeight);
	CrAfterDCT = deZigZagImage(Crzz, cont_cr, infoHeader.biWidth, infoHeader.biHeight);


	// Implementar (Des)Quantização
	printf("Applying Dequantization...\n");
	double **YDequantized = quantizeImage(YQuantized, infoHeader.biWidth, infoHeader.biHeight);
	double **CbDequantized = quantizeImage(CbQuantized, infoHeader.biWidth, infoHeader.biHeight);
	double **CrDequantized = quantizeImage(CrQuantized, infoHeader.biWidth, infoHeader.biHeight);
	


	printf("Applying IDCT to BGR Components...\n");
	Y = IDCTImage(YDequantized, infoHeader.biWidth, infoHeader.biHeight);
	Cb = IDCTImage(CbDequantized, infoHeader.biWidth, infoHeader.biHeight);
	Cr = IDCTImage(CrDequantized, infoHeader.biWidth, infoHeader.biHeight);

	printf("Applying YCbCr --> RGB Conversion\n");
	YCbCr2RGB(Y, Cb, Cr,  infoHeader.biHeight, infoHeader.biWidth, R, G, B);


	// Escreve output
	printf("Writing output file to disk...\n");
	writeBMPFile(B, G, R, &fileHeader, &infoHeader);
	


	// Liberacao de Memoria

	// Liberacao dos vetores do zizag
	freeDoubleMatrix(Yzz, cont_y);
	freeDoubleMatrix(Cbzz, cont_cb);
	freeDoubleMatrix(Crzz, cont_cr);

	//Liberacao dos vetores quantizados
	freeDoubleMatrix(YQuantized, infoHeader.biHeight);
	freeDoubleMatrix(CbQuantized, infoHeader.biHeight);
	freeDoubleMatrix(CrQuantized, infoHeader.biHeight);

	// Liberacao dos vetores pos-DCT
	freeDoubleMatrix(YAfterDCT, infoHeader.biHeight);
	freeDoubleMatrix(CbAfterDCT, infoHeader.biHeight);
	freeDoubleMatrix(CrAfterDCT, infoHeader.biHeight);

	// Liberacao dos componentes YCbCr
	freeDoubleMatrix(Y, infoHeader.biHeight);
	freeDoubleMatrix(Cb, infoHeader.biHeight);
	freeDoubleMatrix(Cr, infoHeader.biHeight);

	//Liberacao dos componentes RGB
	liberaMatrizUnChar(R,infoHeader.biHeight);
	liberaMatrizUnChar(G,infoHeader.biHeight);
	liberaMatrizUnChar(B,infoHeader.biHeight);

	fclose(f);
	
	return 0;
}