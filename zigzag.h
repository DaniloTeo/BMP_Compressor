#ifndef ZIGZAG_H_INCLUDED
#define ZIGZAG_H_INCLUDED

void down_and_left(int * count, int * i, int * j, double *vet, double **img, int limit, int flag);

void up_and_right(int * count, int * i, int * j, double *vet, double **img, int limit, int flag);

double * zigzagwalk(double **img, int maxDimension, int startHeight, int startWidth);

double ** zigzagImage(double **img, int width, int height, int *n_vet);

void deZigZag(double **img, double *vet, int maxDimension,int startWidth, int startHeight);

double **deZigZagImage(double **imageVector, int n_vet, int width, int height);


#endif
