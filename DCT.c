#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double ** allocateDoubleMatrix(int width, int height) {
	double **mat = (double **) malloc(sizeof(double *) * height);
	int i, j;
	for (i = 0; i < height; i++) {
		mat[i] = (double *) malloc(sizeof(double) * width);
	}
	return mat;
}

unsigned char ** allocateCharMatrix(int width, int height) {
	unsigned char **mat = (unsigned char **) malloc(sizeof(unsigned char *) * height);
	int i, j;
	for (i = 0; i < height; i++) {
		mat[i] = (unsigned char *) malloc(sizeof(unsigned char) * width);
	}
	return mat;
}

void freeDoubleMatrix(double **mat, int height) {
	int i;
	for (i = 0; i < height; i++) {
		free(mat[i]);
	}
	free(mat);
}

void freeCharMatrix(unsigned char **mat, int height) {
	int i;
	for (i = 0; i < height; i++) {
		free(mat[i]);
	}
	free(mat);
}
void dct(unsigned char **input, double **output, int startWidth, int startHeight ) {
	int i, j, k, l;
	double ci, cj, dct1, sum, cos1, cos2;
	for (i = startHeight; i < startHeight + 8; i++) {
		for (j = startWidth; j < startWidth + 8; j++) {
			if (i - startHeight == 0) {
				ci = 1 / sqrt(8);
			} else {
				ci = M_SQRT2 / sqrt(8);
			}
			if (j - startWidth == 0) {
				cj = 1 / sqrt(8);
			} else {
				cj = M_SQRT2 / sqrt(8);
			}
			sum = 0;
			for (k = startHeight; k < startHeight + 8; k++) {
				for (l = startWidth; l < startWidth + 8; l++) {
					cos1 = cos((2 * (k - startHeight) + 1) * (i - startHeight) * M_PI / (2 * 8));
					cos2 = cos((2 * (l - startWidth) + 1) * (j - startWidth) * M_PI / (2 * 8));
					dct1 = input[k][l] * cos1 * cos2; 
					sum = sum + dct1;
				}
			}
			output[i][j] = ci * cj * sum;
		}
	}
}
void idct(double **input, double **output, int startWidth, int startHeight ) {
	int i, j, k, l;
	double ci, cj, dct1, sum, cos1, cos2;
	for (i = startHeight; i < startHeight + 8; i++) {
		for (j = startWidth; j < startWidth + 8; j++) {
			sum = 0;
			for (k = startHeight; k < startHeight + 8; k++) {
				for (l = startWidth; l < startWidth + 8; l++) {
					if (k - startHeight == 0) {
						ci = 1 / sqrt(8);
					} else {
						ci = M_SQRT2 / sqrt(8);
					}
					if (l - startWidth == 0) {
						cj = 1 / sqrt(8);
					} else {
						cj = M_SQRT2 / sqrt(8);
					}
					cos1 = cos((2 * (i - startHeight) + 1) * (k - startHeight) * M_PI / (2 * 8));
					cos2 = cos((2 * (j - startWidth) + 1) * (l - startWidth) * M_PI / (2 * 8));
					dct1 =  ci * cj * input[k][l] * cos1 * cos2; 
					sum = sum + dct1;
				}
			}
			output[i][j] = sum;
		}
	}
}

unsigned char **convertDoubleMatrixToChar(double **image, int width, int height) {
	int i, j;
	unsigned char **new = allocateCharMatrix(width, height);
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			new[i][j] = (unsigned char) image[i][j];
		}
	}
	return new;
}

unsigned char **IDCTImage(double **image, int width, int height) {
	int w, h, i, j;
	double **IDCTImage = allocateDoubleMatrix(width, height);
	for (h = 0; h < height; h+=8) {
		for (w = 0; w < width; w+=8) {
			idct(image, IDCTImage, w, h);
		}
	}
	unsigned char **final = convertDoubleMatrixToChar(IDCTImage, width, height);
	return final;
}

double **DCTImage(unsigned char **image, int width, int height) {
	int w, h, i, j;
	double **DCTImage = allocateDoubleMatrix(width, height);
	for (h = 0; h < height; h+=8) {
		for (w = 0; w < width; w+=8) {
			dct(image, DCTImage, w, h);
		}
	}
	return DCTImage;
}
