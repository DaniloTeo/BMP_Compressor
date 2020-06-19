#include <stdlib.h>
#include <stdio.h>
#include "rle.h"

struct pxlHistogram {
	double val, freq;
	struct pxlHistogram *left, *right;
	char *code;
};

typedef struct pxlHistogram pxlHistogram;

struct Huff {
	double freq, val;
	int pos;
};

typedef struct Huff Huff;

void printPxlHistogram (pxlHistogram **pxlHst, int sizeofPxlHst) {
	int i = 0;
	for (i = 0; i < sizeofPxlHst; i++) {
		printf("\n");
		printf("\nValor = %lf\nFrequencia = %lf\n", pxlHst[i]->val, pxlHst[i]->freq);
		printf("Codigo = %s\n", pxlHst[i]->code);
	}
}

void printHuff (Huff **huff, int sizeofhuff) {
	int i = 0;
	for (i = 0; i < sizeofhuff; i++) {
		printf("\n");
		printf("\nValor = %lf\nFrequencia = %lf\nPosição = %d\n", huff[i]->val, huff[i]->freq, huff[i]->pos);
	}
}

pxlHistogram *createPxlHistogram(double freq, double val, int maxLen){
	pxlHistogram *novo = (pxlHistogram *) malloc(sizeof(pxlHistogram));

	novo->freq = freq;
	novo->val = val;
	novo->left = NULL;
	novo->right = NULL;
	novo->code = (char *) malloc(sizeof(char) * maxLen + 1);
	novo->code[0] = '\0';

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

int *histogram(double *huffmanArray, int sizeOfArray, int big) {
	int i = 0;
	int *hist = (int *) calloc(big + 1, sizeof(int));
	for (i = 0; i < sizeOfArray; i++) {
		hist[(int) huffmanArray[i]]++;
	}
	return hist;
}

int findNonZero(int *hist, int big) {
	int nonZero = 0;
	int i;
	for (i = 0; i < big + 1; i++) { 
    	if (hist[i] != 0) nonZero++; 
	}
	return nonZero;
}

double findingP(int *hist, int big) {
	int nOcurences = 0;
	int menor = 100000000;
	int i;
	for (i = 0; i < big + 1; i++) { 
    	if (hist[i] != 0) {
			nOcurences += hist[i];
			if (hist[i] < menor) menor = hist[i];
		}
	}
	return (double) menor / (double) nOcurences;
}

int maxLength(double p) {
	int i = 0;
	while ((1 / p) < fibonacci(i)) i++;
	return i - 3;
}

void initializeListAndTree(pxlHistogram **pxlHistList, Huff **huffTree, int totElements, int *hist, int big, int codeLen) {
	int i, j;
	double prob;
	j = 0;
	for (i = 0; i < big + 1; i++) {
		if (hist[i] != 0) {
			prob = (double) hist[i] / (double) totElements;
			pxlHistList[j] = createPxlHistogram(prob, i, codeLen);
			huffTree[j] = createHuff(hist[i], prob, j);
			j++;
		}
	}
}
// Building Huffman Tree

void sortHistogram(Huff **huffTree, int nonZero) {
	int i, j;
	Huff *temp = NULL;
	for (i = 0; i < nonZero; i++) {
		for (j = i + 1; j < nonZero; j++) {
			if (huffTree[i]->freq < huffTree[j]->freq) {
				temp = huffTree[i];
				huffTree[i] = huffTree[j];
				huffTree[j] = temp;
			}
		}
	}
}

int main(void){
	ENCODED_IMAGE *img = NULL; //IMAGEM DA BRABA
	double *huffmanArray =  prepareHuffman(img);
	int totElements = (2 * img->len);
	int big = findBiggest(huffmanArray, totElements);
	int *histo = histogram(huffmanArray, totElements, big);
	int nonZero = findNonZero(histo, big);
	double p = findingP(histo, big);
	int codeLen = maxLength(p);
	pxlHistogram **pxlHistList = NULL;
	Huff **huffTree = NULL;
	int nNodes = 2 * nonZero - 1;
	pxlHistList = (pxlHistogram **) malloc(sizeof(pxlHistogram *) * nNodes);
	huffTree = (Huff **) malloc(sizeof(Huff *) * nonZero);


	free(huffmanArray);
	return 0;
}