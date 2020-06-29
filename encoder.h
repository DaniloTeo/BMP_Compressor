#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED

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

#endif