#ifndef QUANTIZE_H_INCLUDED
#define QUANTIZE_H_INCLUDED

double ** allocateDoubleMatrix(int width, int height);

void quantize(double **input, double **output, int startWidth, int startHeight );

double **quantizeImage(double **image, int width, int height);

#endif