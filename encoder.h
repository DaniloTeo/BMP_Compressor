#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED
#include "rle.h"
typedef struct {
	char *code;
	int val;
	int len;
  int mantissa;
  int catBaseVal;
  char cat;
} BINARY_ENCODING;

BINARY_ENCODING *coeficientCodification (int *arr, int len);

void getDCPrefix (BINARY_ENCODING *obj, char category);

void valueEncoding (BINARY_ENCODING *obj);

char * encoded2FullMessage(BINARY_ENCODING *encoded, int size);

unsigned char *message2Buffer(char *message, int *bufferLen);

void char2String(unsigned char c, char *decoded);

char * file2Message(FILE *f, int fileLen, int bufferLen);

int isPrefix(char * accumulator) ;

int decodeNumber(char *suffix, int suffixSize) ;

int *decodeBinaryString(char *bin, int fileLen) ;

void EI2File(ENCODED_IMAGE **img, FILE *f, int len) ;

void File2EI(ENCODED_IMAGE **img, FILE *f, int len);


#endif