#ifndef DCT_H_INCLUDED
#define DCT_H_INCLUDED

double ** allocateDoubleMatrix(int width, int height);

unsigned char ** allocateCharMatrix(int width, int height);

void freeDoubleMatrix(double **mat, int height);

void freeCharMatrix(unsigned char **mat, int height);

void dct(/*unsigned char*/double **input, double **output, int startWidth, int startHeight );

void idct(double **input, double **output, int startWidth, int startHeight );

unsigned char **convertDoubleMatrixToChar(double **image, int width, int height);

double **IDCTImage(double **image, int width, int height);

double **DCTImage(/*unsigned char*/double **image, int width, int height);

#endif