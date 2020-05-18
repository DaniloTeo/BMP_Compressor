#ifndef RLE_H_INCLUDED
#define RLE_H_INCLUDED


typedef struct{
	double *info;
	int *qtds;
	int len;

} ENCODED_IMAGE;


ENCODED_IMAGE *initializeEncoded(void);

void freeEncoded(ENCODED_IMAGE * img);

void printVetorInt(int *vet, int n);

void printVetorDouble(double *vet, int n);

void encodeRLE(double *vet, int n, ENCODED_IMAGE *out);

double *decodeRLE(ENCODED_IMAGE *input, int *decomp_len);

ENCODED_IMAGE **encodeImage(double **img, int length);

double **decodeImage(ENCODED_IMAGE **encoded, int length);



#endif