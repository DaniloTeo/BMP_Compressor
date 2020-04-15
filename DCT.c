#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void printCharMatrix(unsigned char **matrix, int width, int height) {
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void printDoubleMatrix(double **matrix, int width, int height) {
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}

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
// APARENTEMENTE FUNCIONA
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
// AINDA NAO TÁ CERTA, EU NÃO CONSEGUI ENTENDER A DIFERENÇA ENTRE A NORMAL E A INVERSA
void idct(double **input, unsigned char **output, int startWidth, int startHeight ) {
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

double ** createDCTImage(int width, int height) {
	int h;
	double **aux = (double **) malloc(sizeof(double *) * height);
	for (h = 0; h < height; h++) {
		aux[h] = (double *) malloc(sizeof(double) * width);
	}
	return aux;
}

double ** segmentAndDCTImage(unsigned char **image, int width, int height) {
	int w, h, i, j;
	double **DCTImage = createDCTImage(width, height);
	double **IDCTImage = createDCTImage(width, height);
	double aux;

	for (h = 0; h < height; h+=8) {
		for (w = 0; w < width; w+=8) {
			dct(image, DCTImage, w, h);
			idct(DCTImage, IDCTImage, w, h);
		}
	}
	return IDCTImage;
}
