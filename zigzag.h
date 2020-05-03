#ifndef ZIGZAG_H_INCLUDED
#define ZIGZAG_H_INCLUDED

void down_and_left(int * count, int * i, int * j, double *vet, double **img, int limit);

void up_and_right(int * count, int * i, int * j, double *vet, double **img, int limit);

double * zigzagwalk(double img[][8], int maxDimension);

#endif