#ifndef QUANTIZE_H_INCLUDED
#define QUANTIZE_H_INCLUDED

void quantize(double **input, double **output, int startWidth, int startHeight );

double **quantizeImage(double **image, int width, int height);

void dequantize(double **input, double **output, int startWidth, int startHeight );

double **dequantizeImage(double **quantImg, int width, int height);

#endif