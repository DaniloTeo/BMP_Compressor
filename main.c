#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bitmap.h"
#include "DCT.h"
#include "zigzag.h"
#include "rle.h"

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
	// double **YQuantized = quantizeImageLuma(YAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	// double **CbQuantized = quantizeImageCroma(CbAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	// double **CrQuantized = quantizeImageCroma(CrAfterDCT, infoHeader.biWidth, infoHeader.biHeight);

	printf("Applying ZigZagWalk...\n");
	double *Yzz = zigzagwalk(YAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	double *Cbzz = zigzagwalk(CbAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	double *Crzz = zigzagwalk(CrAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	
	printf("Appyling RLE Encoding....\n");
	ENCODED_IMAGE * Y_rle = encodeRLE(Yzz, (infoHeader.biWidth * infoHeader.biHeight));
	ENCODED_IMAGE * Cb_rle = encodeRLE(Cbzz, (infoHeader.biWidth * infoHeader.biHeight));
	ENCODED_IMAGE * Cr_rle = encodeRLE(Crzz, (infoHeader.biWidth * infoHeader.biHeight));

  writeENCODEDFile(&fileHeader, Y_rle, Cb_rle, Cr_rle, &infoHeader);


	//Essa parte fica no descompressor --------------------------------------------------------

	// decode

	decodeRLE(Y_rle, Yzz, (infoHeader.biWidth * infoHeader.biHeight));
	decodeRLE(Cb_rle, Cbzz, (infoHeader.biWidth * infoHeader.biHeight));
	decodeRLE(Cr_rle, Crzz, (infoHeader.biWidth * infoHeader.biHeight));



	//dezigzag
	printf("Applying deZigZag...\n");
	deZigZag(YAfterDCT, Yzz, infoHeader.biWidth, infoHeader.biHeight);
	deZigZag(CbAfterDCT, Cbzz, infoHeader.biWidth, infoHeader.biHeight);
	deZigZag(CrAfterDCT, Crzz, infoHeader.biWidth, infoHeader.biHeight);


	// Implementar (Des)Quantização


	printf("Applying IDCT to BGR Components...\n");
	Y = IDCTImage(YAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	Cb = IDCTImage(CbAfterDCT, infoHeader.biWidth, infoHeader.biHeight);
	Cr = IDCTImage(CrAfterDCT, infoHeader.biWidth, infoHeader.biHeight);

	printf("Applying YCbCr --> RGB Conversion\n");
	YCbCr2RGB(Y, Cb, Cr,  infoHeader.biHeight, infoHeader.biWidth, R, G, B);


	// Escreve output
	printf("Writing output file to disk...\n");
	writeBMPFile(B, G, R, &fileHeader, &infoHeader);
	


	// Liberacao de Memoria

	freeEncoded(Y_rle);
	freeEncoded(Cb_rle);
	freeEncoded(Cr_rle);



	// Liberacao dos vetores do zizag
	free(Yzz);
	free(Cbzz);
	free(Crzz);

	//Liberacao dos vetores quantizados
	// freeDoubleMatrix(YQuantized, infoHeader.biHeight);
	// freeDoubleMatrix(CbQuantized, infoHeader.biHeight);
	// freeDoubleMatrix(CrQuantized, infoHeader.biHeight);

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