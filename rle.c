#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "bitmap.h"
#include "zigzag.h"
#include "rle.h"




ENCODED_IMAGE *initializeEncoded(void){
	ENCODED_IMAGE *img = (ENCODED_IMAGE *) malloc(sizeof(ENCODED_IMAGE));
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
	// printf("TAMANHO DO VETOR INTEIRO: %d\n", n);
	// printf("VETOR:\n");
	for(i = 0; i < n; i++){
		printf("%d ", vet[i]);
	}
	printf("\n");
}

void printVetorDouble(double *vet, int n){
	int i = 0;
	// printf("TAMANHO DO VETOR: %d\n", n);
	// printf("VETOR:\n");
	for(i = 0; i < n; i++){
		printf("%.2lf ", vet[i]);
	}
	printf("\n");
}


ENCODED_IMAGE * encodeRLE(double *vet, int n){
	int i, count;
	ENCODED_IMAGE *out = initializeEncoded();
	// printf("Alocando novo vetor com o tamanho original...\n");
	out->info = (int *) malloc(sizeof(int) * n);
	out->qtds = (int *) calloc(n, sizeof(int));
	
	for(i = 0; i < n; i++){
		count = 1;

		while(i < n - 1 && vet[i] == vet[i+1]){
			count++;
			i++;

		}

		// printf("Inserindo valor no contador...\n");
		out->qtds[out->len] = count;
		out->info[out->len] = (int)vet[i];
		(out->len)+=1;
	}

	// printf("Fim do algoritmo principal...\n");
	// printf("\n\n");

	out->info = (int *) realloc(out->info, sizeof(int) * (out->len));
	
	out->qtds = (int *) realloc(out->qtds, sizeof(int) * (out->len));

	return out;
}

ENCODED_IMAGE **encodeImage(double **img, int length){
	int i;
	int maxDimension = 4;
	ENCODED_IMAGE **output = (ENCODED_IMAGE **) malloc(sizeof(ENCODED_IMAGE *) * length);

	for(i = 0; i < length; i++){

		output[i] = encodeRLE(img[i], (maxDimension*maxDimension));
	}

	return output;
}

double * decodeRLE(ENCODED_IMAGE *input){
	int i,j = 0;
	int decomp_len = 0;
	//descobir o tamanho do vetor original
	for(i = 0; i < input->len; i++){
		decomp_len += input->qtds[i];
	}

	double *output = (double *) malloc(sizeof(double) * decomp_len);

	for(i = 0; i < input->len; i++){
		while(input->qtds[i] > 0){
			output[j] = (double)input->info[i];
			input->qtds[i] = input->qtds[i]-1;
			j++;
		}
	}

	return output;
}


double **decodeImage(ENCODED_IMAGE **encoded, int length){
	int i;
	double **out = (double **) malloc(sizeof(double *) * length);
	
	for(i = 0; i < length; i++){
		// printVetorInt(encoded[i]->qtds, encoded[i]->len);
		out[i] = decodeRLE(encoded[i]);
	}

	return out;
}



// int main(void){
// 	// char string[] = "wwwwaaadexxxxxxywww";
// 	int i, j;
// 	int width = 8, height = 8;
// 	srand(time(NULL));



// 	double **test = (double **) malloc(sizeof(double *) * height);

// 	for(i = 0; i < height; i++){
// 		test[i] = (double *) malloc(sizeof(double) * width);
// 		for(j = 0; j < width; j++){
// 			test[i][j] = (double) (rand() % 3);
// 			// printf("%.2lf ", test[i][j]);
// 		}
// 		// printf("\n");
// 	}

// 	int n_vet = 0;
// 	printf("ZIGZAGGED IMAGE--------------------\n");
// 	double **jorge = zigzagImage(test, width, height, &n_vet);

// 	for(i = 0; i < n_vet; i++){
// 		for(j = 0; j < (4*4); j++){
// 			printf("%.2lf ", jorge[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n\n");


// 	printf("n_vet: %d\n", n_vet);

// 	ENCODED_IMAGE **out = encodeImage(jorge, n_vet);

// 	printf("ENCODED-----------------------\n");	
// 	for(i = 0; i < n_vet; i++){
// 		printf("ITERAÇÃO: %d\n", i);
// 		printVetorInt(out[i]->info, out[i]->len);
// 		printVetorInt(out[i]->qtds, out[i]->len);
// 		printf("\n");
		
// 	}


// 	printf("DECODED-----------------------\n");
// 	double ** decoded = decodeImage(out, n_vet);
// 	printf("SAIU\n");
// 	for(i = 0; i < n_vet; i++){
// 		for(j = 0; j < (4*4); j++){
// 			if(decoded[i][j] != jorge[i][j]){
// 				printf("ALGO DEU ERRADO!!\n");
// 				break;
// 			}
// 		}
// 	}
// 	if(i == n_vet) printf("TUDO CERTO\n");;


// 	for(i = 0; i < height; i++){
// 		free(test[i]);
// 	}

// 	for(i = 0; i < n_vet; i++){
// 		free(decoded[i]);
// 		freeEncoded(out[i]);
// 	}

// 	free(decoded);
// 	free(out);
// 	free(test);
	
// 	return 0;

// }