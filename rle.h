#ifndef RLE_H_INCLUDED
#define RLE_H_INCLUDED

double * encodeRLE(double *vet, int n, int *conts, int *conts_len, int *tam);

double * decodeRLE(int *conts, int len, double *comp, int *decomp_len);

void printVetorInt(int *vet, int n);

void printVetorDouble(double *vet, int n);


#endif