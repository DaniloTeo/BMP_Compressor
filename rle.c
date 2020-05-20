#include <stdlib.h>
#include <stdio.h>
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
		printf("%lf ", vet[i]);
	}
	printf("\n");
}

void encodeRLE(double *vet, int n, ENCODED_IMAGE *out){
	int i, count;
	
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
	printf("\n\n");

	out->info = (double *) realloc(out->info, sizeof(double) * (out->len));
	
	out->qtds = (int *) realloc(out->qtds, sizeof(double) * (out->len));
}


double *decodeRLE(ENCODED_IMAGE *input, int *decomp_len){
	int i,j = 0;

	//descobir o tamanho do vetor original
	for(i = 0; i < input->len; i++){
		(*decomp_len) += input->qtds[i];
	}

	double *output = (double *) malloc(sizeof(double) * (*decomp_len));

	for(i = 0; i < input->len; i++){
		while(input->qtds[i] > 0){
			output[j] = input->info[i];
			input->qtds[i] = input->qtds[i]-1;
			j++;
		}
	}

	return output;


}

ENCODED_IMAGE **encodeImage(double **img, int length){
	int i;

	ENCODED_IMAGE **output = (ENCODED_IMAGE **) malloc(sizeof(ENCODED_IMAGE *) * length);

	for(i = 0; i < length; i++){
		output[i] = initializeEncoded();
		encodeRLE(img[i], (8*8), output[i]);
	}

	return output;
}

double **decodeImage(ENCODED_IMAGE **encoded, int length){
	int i, decomp_len;
	double **out = (double **) malloc(sizeof(double *) * length);
	
	for(i = 0; i < length; i++){
		decomp_len = 0;
		// printVetorInt(encoded[i]->qtds, encoded[i]->len);
		out[i] = decodeRLE(encoded[i], &decomp_len);
	}

	return out;
}



/*
int main(void){
	// char string[] = "wwwwaaadexxxxxxywww";
	int i, j;
	int width = 64, height = 8;
	srand(time(NULL));



	double **test = (double **) malloc(sizeof(double *) * height);

	for(i = 0; i < height; i++){
		test[i] = (double *) malloc(sizeof(double) * width);
		for(j = 0; j < width; j++){
			test[i][j] = (double) (rand() % 3);
		}
	}

	ENCODED_IMAGE **out = encodeImage(test, height);
	
	
	for(i = 0; i < height; i++){
		printf("ITERAÇÃO: %d\n", i);
		printVetorDouble(out[i]->info, out[i]->len);
		printf("\n\n");
		printVetorInt(out[i]->qtds, out[i]->len);
		printf("\n\n");
		
	}

	double ** decoded = decodeImage(out, height);
	for(i = 0; i < height; i++){
		printf("ITERAÇÃO: %d\n", i);
		printVetorDouble(decoded[i], width);
		printf("\n\n");
		
	}


	for(i = 0; i < height; i++){
		free(decoded[i]);
		freeEncoded(out[i]);
		free(test[i]);
	}

	free(decoded);
	free(out);
	free(test);
	
	return 0;

}
*/