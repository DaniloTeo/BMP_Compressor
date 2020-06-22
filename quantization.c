#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bitmap.h"

// double ** allocateDoubleMatrix(int width, int height) {
//  double **mat = (double **) malloc(sizeof(double *) * height);
//  int i, j;
//  for (i = 0; i < height; i++) {
//      mat[i] = (double *) malloc(sizeof(double) * width);
//  }
//  return mat;
// }

void quantizeLuma(double **input, double **output, int startWidth, int startHeight ) {
	double quantTable[][8] = {  {	16,	11,	10, 16, 24, 40, 51, 61		},
								{	12,	12,	14, 19, 26, 58, 60, 55		},
								{	14,	13,	16, 24, 40, 57, 69, 56		},
								{	14,	17,	22, 29, 51, 87, 80, 62		},
								{	18,	22,	37, 56, 68, 109, 103, 77	},
								{	24,	35,	55, 64, 81, 104, 113, 92	},
								{	49,	64,	78, 87, 103, 121, 120, 101	},
								{	72,	92,	95, 98, 112, 100, 103, 99	}};
	int i, j;
	double aux;
	for (i = startHeight; i < startHeight + 8; i++) {
		for (j = startWidth; j < startWidth + 8; j++) {
			output[i][j] = round(input[i][j] / quantTable[i - startHeight][j - startWidth]);
		}
	}
}

double **quantizeImageLuma(double **image, int width, int height) {
	int w, h;
	double **quantImage = alocaMatrizDouble(height, width);
	for (h = 0; h < height; h+=8) {
		for (w = 0; w < width; w+=8) {
			quantizeLuma(image, quantImage, w, h);
		}
	}
	return quantImage;
}

void quantizeCroma(double **input, double **output, int startWidth, int startHeight ) {
	double quantTable[][8] = {	{	17,	18,	24,	47,	99,	99,	99,	99	},
								{	18,	21,	26,	66,	99,	99,	99,	99	},
								{	24,	26,	56,	99,	99,	99,	99,	99	},
								{	47,	66,	99,	99,	99,	99,	99,	99	},
								{	99,	99,	99,	99,	99,	99,	99,	99	},
								{	99,	99,	99,	99,	99,	99,	99,	99	},
								{	99,	99,	99,	99,	99,	99,	99,	99	},
								{	99,	99,	99,	99,	99,	99,	99,	99	}};
	int i, j;
	double aux;
	for (i = startHeight; i < startHeight + 8; i++) {
		for (j = startWidth; j < startWidth + 8; j++) {
			output[i][j] = round(input[i][j] / quantTable[i - startHeight][j - startWidth]);
		}
	}
}

double **quantizeImageCroma(double **image, int width, int height) {
	int w, h;
	double **quantImage = alocaMatrizDouble(height, width);
	for (h = 0; h < height; h+=8) {
		for (w = 0; w < width; w+=8) {
			quantizeCroma(image, quantImage, w, h);
		}
	}
	return quantImage;
}

/*
int main(void) {
	double img[][8] = { {-415, -33, -58, 35, 58, -51, -15, -12},
								{5, -34, 49, 18, 27, 1, -5, 3},
								{-46, 14, 80, -35, -50, 19, 7, -18},
								{-53, 21, 34, -20, 2, 34, 36, 12},
								{9, -2, 9, -5, -32, -15, 45, 37},
								{-8, 15, -16, 7, -8, 11, 4, 7},
								{19, -28, -2, -26, -2, 7, -44, -21},
								{18, 25, -12, -44, 35, 48, -37, -3}
							};
	print(quantizeImage(img, 8, 8));

	
	return 0;
}

*/
