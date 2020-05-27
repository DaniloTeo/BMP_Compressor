#ifndef QUANTIZE_H_INCLUDED
#define QUANTIZE_H_INCLUDED

// double ** allocateDoubleMatrix(int width, int height);

void quantizeLuma(double **input, double **output, int startWidth, int startHeight );

double **quantizeImageLuma(double **image, int width, int height);

void quantizeCroma(double **input, double **output, int startWidth, int startHeight );

double **quantizeImageCroma(double **image, int width, int height);

#endif