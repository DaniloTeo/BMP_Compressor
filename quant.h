#ifndef QUANT_H_INCLUDED
#define QUANT_H_INCLUDED

void quantizeLuma(double **input, double **output, int startWidth, int startHeight);

double **quantizeImageLuma(double **image, int width, int height);

void quantizeCroma(double **input, double **output, int startWidth, int startHeight);

double **quantizeImageCroma(double **image, int width, int height);

#endif

