#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bitmap.h"
#include "DCT.h"

int main(int argc, char *argv[]){
	// Alocando memoria pra arquivo
	FILE *f = fopen(argv[1], "rb");
	
	// Leitura e Exibição do File Header
	BMPFILEHEADER fileHeader;
	leituraFileHeader(f, &fileHeader);
	dumpFileHeader(&fileHeader);

	// Leitura e Exibição do infoHeader
	BMPINFOHEADER infoHeader;
	leituraInfoHeader(f, &infoHeader);
	dumpInfoHeader(&infoHeader);

	// Leitura dos componentes B,G,R da imagem
	unsigned char **B = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	unsigned char **G = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	unsigned char **R = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
	readBMPImage(f, &B, &G, &R,infoHeader.biHeight, infoHeader.biWidth);

	double **DCTB = segmentAndDCTImage(B, infoHeader.biWidth, infoHeader.biHeight);
	double **DCTG = segmentAndDCTImage(G, infoHeader.biWidth, infoHeader.biHeight);
	double **DCTR = segmentAndDCTImage(R, infoHeader.biWidth, infoHeader.biHeight);
	
	writeBMPFile(DCTB, DCTG, DCTR, &fileHeader, &infoHeader);
	


	// Liberacao de Memoria
	liberaMatrizUnChar(R,infoHeader.biHeight);
	liberaMatrizUnChar(G,infoHeader.biHeight);
	liberaMatrizUnChar(B,infoHeader.biHeight);
	fclose(f);
	
	return 0;
}