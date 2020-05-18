#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "quantization.h"
#include "bitmap.h"

void quantize(double **input, double **output, int startWidth, int startHeight ) {
	int i, j;
	double aux;
	double table[][8] = 	{{16, 11, 10, 16, 24, 40, 51, 61},
								{12, 12, 14, 19, 26, 58, 60, 55},
								{14, 13, 16, 24, 40, 57, 69, 56},
								{14, 17, 22, 29, 51, 87, 80, 62},
								{18, 22, 37, 56, 68, 109, 103, 77},
								{24, 35, 55, 64, 81, 104, 113, 92},
								{49, 64, 78, 87, 103, 121, 120, 101},
								{72, 92, 95, 98, 112, 100, 103, 99}
							};
	
	for (i = startHeight; i < startHeight + 8; i++) {
		for (j = startWidth; j < startWidth + 8; j++) {
			output[i][j] = (double) round(input[i][j] / table[i - startHeight][j - startWidth]);
		}
	}
}

void dequantize(double **input, double **output, int startWidth, int startHeight ) {
	int i, j;
	double aux;
	double table[][8] = 	{{16, 11, 10, 16, 24, 40, 51, 61},
								{12, 12, 14, 19, 26, 58, 60, 55},
								{14, 13, 16, 24, 40, 57, 69, 56},
								{14, 17, 22, 29, 51, 87, 80, 62},
								{18, 22, 37, 56, 68, 109, 103, 77},
								{24, 35, 55, 64, 81, 104, 113, 92},
								{49, 64, 78, 87, 103, 121, 120, 101},
								{72, 92, 95, 98, 112, 100, 103, 99}
							};
	
	for (i = startHeight; i < startHeight + 8; i++) {
		for (j = startWidth; j < startWidth + 8; j++) {
			if (input[i][j] == 0.0) {
				output[i][j] = table[i - startHeight][j - startWidth];
			} else if (input[i][j] == -0.0) {
				output[i][j] = - table[i - startHeight][j - startWidth];
			} else {
				output[i][j] = (double) input[i][j] * table[i - startHeight][j - startWidth];
			}
		}
	}
}

double **quantizeImage(double **image, int width, int height) {
	int w, h;
	double **quantImage = alocaMatrizDouble(height, width);
	for (h = 0; h < height; h+=8) {
		for (w = 0; w < width; w+=8) {
			quantize(image, quantImage, w, h);
		}
	}
	return quantImage;
}

double **dequantizeImage(double **quantImg, int width, int height) {
	int w, h;
	double **dequantImage = alocaMatrizDouble(height, width);
	for (h = 0; h < height; h+=8) {
		for (w = 0; w < width; w+=8) {
			dequantize(quantImg, dequantImage, w, h);
		}
	}
	return dequantImage;	
}