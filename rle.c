#include <stdlib.h>
#include <stdio.h>

#include "bitmap.h"
#include "zigzag.h"
#include "rle.h"




ENCODED_IMAGE *initializeEncoded(int tam_vet){
	ENCODED_IMAGE *img = (ENCODED_IMAGE *) malloc(sizeof(ENCODED_IMAGE) * tam_vet);
	img->info = NULL;
	img->qtds = NULL;
	img->len = 0;

	return img;
}



void freeEncoded(ENCODED_IMAGE * img){
	free(img->info);
	free(img->qtds);
	free(img);
}



void freeVetorEncoded(ENCODED_IMAGE **img, int len){
	int i;
	for(i = 0; i < len; i++){
		freeEncoded(img[i]);
	}
	free(img);
}

void printVetorInt(int *vet, int n){
	int i = 0;
	printf("TAMANHO DO VETOR INTEIRO: %d\n", n);
	printf("VETOR:\n");
	for(i = 0; i < n; i++){
		printf("%d ", vet[i]);
	}
	printf("\n");
}

void printVetorDouble(double *vet, int n){
	int i = 0;
	printf("TAMANHO DO VETOR: %d\n", n);
	printf("VETOR:\n");
	for(i = 0; i < n; i++){
		printf("%.2lf ", vet[i]);
	}
	printf("\n");
}


ENCODED_IMAGE * encodeRLE(double *vet, int n){
	int i, count;
	
	ENCODED_IMAGE * out = initializeEncoded(n);

	// printf("Alocando novo vetor com o tamanho original...\n");
	out->info = (double *)malloc(sizeof(double) * n);
	out->qtds = (int *) calloc(n, sizeof(int));
	
	for(i = 0; i < n; i++){
		count = 1;

		while(i < n - 1 && vet[i] == vet[i+1]){
			count++;
			i++;

		}

		// printf("Inserindo valor no contador...\n");
		out->qtds[out->len] = count;
		out->info[out->len] = vet[i];
		(out->len)+=1;
	}

	// printf("Fim do algoritmo principal...\n");
	// printf("\n\n");

	out->info = (double *) realloc(out->info, sizeof(double) * (out->len));
	
	out->qtds = (int *) realloc(out->qtds, sizeof(double) * (out->len));

	return out;
}


void decodeRLE(ENCODED_IMAGE *input, double * output, int len){
	int i,j = 0;

	//descobir o tamanho do vetor original
	// for(i = 0; i < input->len; i++){
	// 	(*decomp_len) += input->qtds[i];
	// }

	output = (double *) malloc(sizeof(double) * len);

	for(i = 0; i < input->len; i++){
		while(input->qtds[i] > 0){
			output[j] = input->info[i];
			input->qtds[i] = input->qtds[i]-1;
			j++;
		}
	}


}

/*ENCODED_IMAGE **encodeImage(double **img, int length){
	int i;

	ENCODED_IMAGE **output = (ENCODED_IMAGE **) malloc(sizeof(ENCODED_IMAGE *) * length);

	for(i = 0; i < length; i++){
		output[i] = initializeEncoded();
		encodeRLE(img[i], (8*8), output[i]);
	}

	return output;
}*/

// double **decodeImage(ENCODED_IMAGE **encoded, int length){
// 	int i, decomp_len;
// 	double **out = (double **) malloc(sizeof(double *) * length);
	
// 	for(i = 0; i < length; i++){
// 		decomp_len = 0;
// 		// printVetorInt(encoded[i]->qtds, encoded[i]->len);
// 		out[i] = decodeRLE(encoded[i], &decomp_len);
// 	}

// 	return out;
// }



// int main(int argc, char *argv[]){
// 	// char string[] = "wwwwaaadexxxxxxywww";
// 	int i, j;
	

// 	/*****************************/
// 	printf("Opening %s file..\n", argv[1]);
// 	FILE *f = fopen(argv[1], "rb");
// 	printf("File opened!\n");

// 	// Leitura e Exibição do File Header
// 	printf("Reading File Header...\n");
// 	BMPFILEHEADER fileHeader;
// 	leituraFileHeader(f, &fileHeader);
// 	dumpFileHeader(&fileHeader);

// 	// Leitura e Exibição do infoHeader
// 	printf("Reading Image Header...\n");
// 	BMPINFOHEADER infoHeader;
// 	leituraInfoHeader(f, &infoHeader);
// 	dumpInfoHeader(&infoHeader);

// 	// Leitura dos componentes B,G,R da imagem
// 	printf("Loading BGR Image components...\n");
// 	unsigned char **B = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
// 	unsigned char **G = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
// 	unsigned char **R = alocaMatrizUnChar(infoHeader.biHeight, infoHeader.biWidth);
// 	readBMPImage(f, &B, &G, &R,infoHeader.biHeight, infoHeader.biWidth);
// 	printf("Image loaded!\n");


// 	/***************************/
// 	int width = infoHeader.biWidth;
// 	int height = infoHeader.biHeight;

// 	// printf("154\n");

// 	// printf("156\n");
// 	double **jorge = (double **) malloc(sizeof(double*) * (height ));
// 	for(i = 0; i < height; i++){
// 		jorge[i] = (double *) malloc(sizeof(double) * width);
// 		for(j = 0; j < width; j++){
// 			jorge[i][j] = (double) B[i][j];
// 		}
// 	}

// 	double *test = NULL;
// 	test = zigzagwalk(jorge, width, height);



// 	ENCODED_IMAGE *out = encodeRLE(test, (width * height));
// 	// printf("158\n");
	
// 	// printf("160\n");
// 	// printf("%d\n", out->len);
// 	double *aux = (double *) malloc(sizeof(double) * (height * width));
// 	j = 0;
// 	for(i = 0; i < out->len; i++){
// 		while(out->qtds[i] > 0){
// 			aux[j] = out->info[i];
// 			out->qtds[i] = out->qtds[i]-1;
// 			j++;
// 		}
// 	}

// 	for(i = 0; i < height * width; i++){
// 		if(test[i] != aux[i]){
// 			printf("ERRO!!!! AAAAAHHH\n");
// 			printf("test[%d]: %.2lf\n", i,test[i]);
// 			printf("aux[%d]: %.2lf\n", i, aux[i]);
// 			break;
// 		}
// 		else printf("TUDO CERTO\n");
// 	}

// 	// double ** decoded = decodeImage(out, (height));
// 	// for(i = 0; i < height; i++){
// 	// 	printf("ITERAÇÃO: %d\n", i);
// 	// 	printVetorDouble(decoded[i], width);
// 	// 	printf("\n\n");
		
// 	// }

// 	// free(decoded);
	
// 	free(aux);
// 	free(out);
// 	free(test);
	
// 	return 0;

// }
