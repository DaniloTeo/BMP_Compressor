#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
	// printf("40\n");

	novo->freq = freq;
	novo->val = val;
	novo->left = NULL;
	novo->right = NULL;
	novo->code = (char *) malloc(sizeof(char) * maxLen + 1);
	// printf("47\n");
	// printf("maxLen: %d\n", maxLen);
	novo->code[0] = '\0';
	// printf("49\n");
	return novo;
}

void freePxlHistogram(pxlHistogram *p){
	free(p->code);
	free(p);
}

Huff *createHuff(double val, double freq, int pos){
	Huff *novo = (Huff *) malloc(sizeof(Huff));
	// printf("60\n");
	novo->freq = freq;
	novo->val = val;
	novo->pos = pos;

	return novo;
}

int fibonacci(int n){ 
    if (n <= 1) 
        return 1; 
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
	double aux = 1/p;
		// printf("1/p: %.2lf\n", (1/p));
		// printf("aux: %.2lf\n", aux);
		// printf("fib(%d): %d\n", i, fibonacci(i));
	while ((int)aux > fibonacci(i)){
		
		i++;
	} 
	// printf("acabo\n");
	return i - 3;
}

void initializeListAndTree(pxlHistogram **pxlHistList, Huff **huffTree, int totElements, int *hist, int big, int codeLen) {
	int i, j;
	double prob;
	j = 0;
	for (i = 0; i < big + 1; i++) {
		if (hist[i] != 0) {
			prob = (double) hist[i] / (double) totElements;
			// printf("135\n");
			pxlHistList[j] = createPxlHistogram(prob, i, codeLen);
			// printf("137\n");
			huffTree[j] = createHuff(hist[i], prob, j);
			// printf("139\n");
			j++;
		}
	}
}
// Building Huffman Tree

void sortHistogram(Huff **huffTree, int nonZero) {
	int i, j;
	Huff *temp = NULL;
	printf("152\n");
	for (i = 0; i < nonZero; i++) {
		for (j = i + 1; j < nonZero; j++) {
			if (huffTree[i]->freq < huffTree[j]->freq) {
				// printf("156\n");
				temp = huffTree[i];
				// printf("158\n");
				huffTree[i] = huffTree[j];
				// printf("160\n");
				huffTree[j] = temp;
			}
		}
	}
}

void buildHuffmanTree(pxlHistogram **pxlHistList, Huff **huffTree, int nonZero, int codeLen){
	double sumfreq;
	int sumval, n = 0, k = 0, i = 0;
	int nextNode = nonZero;

	// printf("172\n");
	while(n < nonZero - 1){
		sumfreq = huffTree[nonZero - n - 1]->freq + huffTree[nonZero - n - 2]->freq;
		sumval = huffTree[nonZero - n - 1]->val + huffTree[nonZero - n - 2]->val;

		pxlHistogram *aux = createPxlHistogram(sumfreq, sumval, codeLen);
		aux->left = pxlHistList[huffTree[nonZero - n - 2]->pos];
		aux->right = pxlHistList[huffTree[nonZero - n - 1]->pos];

		pxlHistList[nextNode] = aux;

		i = 0; 
		while(sumfreq <= huffTree[i]->freq) i++;

		for (k = nonZero; k >= 0; k--){
			if(k == i){
				huffTree[k]->freq = sumfreq;
				huffTree[k]->val = sumval;
				huffTree[k]->pos = nextNode;

			}

			else if (k > i){
				huffTree[k] = huffTree[k - 1];
			}
		}
		n++;
		nextNode++;

	}
}

void assignCode(pxlHistogram **pxlHistList, int nonZero, int nNodes){
	char left = '0', right = '1';
	int i;

	for (i = nNodes - 1; i >= nonZero; i--){
		if(pxlHistList[i]->left != NULL){
			strcat(pxlHistList[i]->left->code, pxlHistList[i]->code);
			strcat(pxlHistList[i]->left->code, &left);
		}

		if(pxlHistList[i]->right != NULL){
			strcat(pxlHistList[i]->right->code, pxlHistList[i]->code);
			strcat(pxlHistList[i]->right->code, &right);
		}
	}
}


void printHuffman(pxlHistogram ** pxlHistList, int nonZeros){
	int i;

	for (i = 0; i < nonZeros; i++) { 
        printf("    %.2lf      -> %s\n", pxlHistList[i]->val,pxlHistList[i]->code); 
    } 
}

int main(void){
	int i, j;
	int height = 8, width = 8;
	double **test = (double **) malloc(sizeof(double *) * height);

	for(i = 0; i < height; i++){
		test[i] = (double *) malloc(sizeof(double) * width);
		for(j = 0; j < width; j++){
			test[i][j] = (double) (rand() % 3);
			printf("%.lf ", test[i][j]);
		}
	}
	printf("\n");

	ENCODED_IMAGE **out = encodeImage(test, height);

	ENCODED_IMAGE *img = out[0]; //IMAGEM DA BRABA
	
	printVetorDouble(img->info, img->len);
	printVetorInt(img->qtds, img->len);


	double *huffmanArray =  prepareHuffman(img);
	int totElements = (2 * img->len);
	
	int big = findBiggest(huffmanArray, totElements);
	int *histo = histogram(huffmanArray, totElements, big);
	// printf("242\n");
	int nonZero = findNonZero(histo, big);
	double p = findingP(histo, big);
	int codeLen = maxLength(p);
	// printf("246\n");
	
	pxlHistogram **pxlHistList = NULL;
	Huff **huffTree = NULL;
	int nNodes = 2 * nonZero - 1;
	// printf("251\n");
	pxlHistList = (pxlHistogram **) malloc(sizeof(pxlHistogram *) * nNodes);
	huffTree = (Huff **) malloc(sizeof(Huff *) * nonZero);
	// printf("254\n");
	initializeListAndTree(pxlHistList, huffTree, totElements, histo, big, codeLen);
	printf("histogram:\n");
	printPxlHistogram (pxlHistList, nonZero);
	printf("end of histrogram\n");
	printf("huff:\n");
	printHuff (huffTree, nonZero);
	printf("end of huff\n");
	// printf("256\n");
	sortHistogram(huffTree, nonZero);
	// printf("258\n");
	buildHuffmanTree(pxlHistList, huffTree, nonZero, codeLen);
	// printf("260\n");

	assignCode(pxlHistList,nonZero,nNodes);
	// printf("263\n");
	printHuffman(pxlHistList, nonZero);
	
	free(huffTree);
	free(huffmanArray);
	free(test);
	return 0;
}