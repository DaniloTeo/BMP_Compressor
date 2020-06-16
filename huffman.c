#include <stdlib.h>
#include <stdio.h>
#include "rle.h"

struct pxlHistogram{
	double val, freq;
	struct pxlHistogram *ant, *prox;
	char *code;
};

typedef struct pxlHistogram pxlHistogram;

struct Huff{
	double freq, val;
	int pos;
}

typedef struct Huff Huff;


pxlHistogram *createPxlHistogram(double freq, double val, int maxLen){
	pxlHistogram *novo = (pxlHistogram *) malloc(sizeof(pxlHistogram));

	novo->freq = freq;
	novo->val = val;
	novo->ant = NULL;
	novo->prox = NULL;
	novo->code = (char *) malloc(sizeof(char) * maxLen);

	return novo;
}

void freePxlHistogram(pxlHistogram *p){
	free(p->code);
	free(p);
}

Huff *createHuff(double val, double freq, int pos){
	Huff *novo = (Huff *) malloc(sizeof(Huff));
	novo->freq = freq;
	novo->val = val;
	novo->pos = pos;

	return novo;
}

int fibonacci(int n){ 
    if (n <= 1) 
        return n; 
    return fibonacci(n - 1) + fibonacci(n - 2); 
} 




double * prepareHuffman(ENCODED_IMAGE *img){
	double * arr = (double *) malloc(sizeof(double) * (2 * img->len));
	int i;

	for(i = 0; i < img->len; i++){
		arr[i*2] = img->qtds[i];
		arr[i*2 + 1] = img->info[i];
	}

	return arr;
}

int findBiggest(double * arr, int len){
	int i;
	int maior = 0;
	for(i = 0; i < len; i++){
		if(arr[i] > maior) maior = arr[i];
	}

	return maior;
}

freqTable * histogramFromArray(double *arr, int len){
	int maior = findBiggest(arr, len);
	double * temp = (double *) calloc((maior + 1 ), sizeof(double));
	int i, j;
	for(i = 0; i < len; i++){
		temp[arr[i]]++;
	}


	int nofOcurrences = 0;
	int nofNodes = 0;
	int menor = 1e6;
	for(i = 0; i < (maior + 1); i++){
		if(temp[i] != 0){
			nofOcurrences += temp[i];
			nofNodes++;			
			if(temp[i] < menor) menor = temp[i];
		}
	}

	double p = menor/nofOcurrences;

	int auxLen = 0;
	while((1/p) < fibonacci(auxLen)) auxLen++;

	int maxCodeLen = auxLen - 3;
	int totalofNodes = (2 * nofNodes) -1;

	pxlHistogram **listPxlHistogram = (pxlHistogram **) malloc(sizeof(pxlHistogram *) * totalofNodes);
	Huff **listHuff = (Huff **) malloc(sizeof(Huff *) * nofNodes);

	double prob;
	for(i = 0; i < (maior + 1); i++){
		if(temp[i] != 0){
			prob = temp[i]/nofOcurrences;
			
			listHuff[j] = createHuff(i, prob, j);
			listPxlHistogram = createPxlHistogram(prob, i, maxCodeLen);
			j++;
		}
	}
	// step 5 -- https://www.geeksforgeeks.org/image-compression-using-huffman-coding/




	free(temp);
}

int main(void){
	
	

	double *huffmanArray =  prepareHuffman();

	histogramFromArray(huffmanArray, (2 * img->len));

	

	free(huffmanArray);
	return 0;
}