#ifndef DCT_H_INCLUDED
#define DCT_H_INCLUDED

void printCharMatrix(unsigned char **matrix, int width, int height);

void printDoubleMatrix(double **matrix, int width, int height);

double ** allocateDoubleMatrix(int width, int height);

unsigned char ** allocateCharMatrix(int width, int height);

void freeDoubleMatrix(double **mat, int height);

void freeCharMatrix(unsigned char **mat, int height);

void dct(unsigned char **input, double **output, int startWidth, int startHeight );

void idct(double **input, unsigned char **output, int startWidth, int startHeight );

double ** createDCTImage(int width, int height);

double ** segmentAndDCTImage(unsigned char **image, int width, int height);

#endif