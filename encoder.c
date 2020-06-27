#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "encoder.h"

BINARY_ENCODING *coeficientCodification (int *arr, int len) {
  int i;
  char cat;
  BINARY_ENCODING *encoded = (BINARY_ENCODING *) malloc(sizeof(BINARY_ENCODING) * len);
  for (i = 0; i < len; i++) {
    encoded[i].val = arr[i];
    if (arr[i] == 0) {
      cat = '0';
    } else if (arr[i] == 1 || arr[i] == -1) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -1;
      } else {
        encoded[i].catBaseVal = 1;
      }
      cat = '1';
    } else if ((arr[i] >= 2 && arr[i] <= 3) || (arr[i] <= -2 && arr[i] >= -3)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -3;
      } else {
        encoded[i].catBaseVal = 2;
      }
      cat = '2';
    } else if ((arr[i] >= 4 && arr[i] <= 7) || (arr[i] <= -4 && arr[i] >= -7)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -7;
      } else {
        encoded[i].catBaseVal = 4;
      }
      cat = '3';
    } else if ((arr[i] >= 8 && arr[i] <= 15) || (arr[i] <= -8 && arr[i] >= -15)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -15;
      } else {
        encoded[i].catBaseVal = 8;
      }
      cat = '4';
    } else if ((arr[i] >= 16 && arr[i] <= 31) || (arr[i] <= -16 && arr[i] >= -31)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -31;
      } else {
        encoded[i].catBaseVal = 16;
      }
      cat = '5';
    } else if ((arr[i] >= 32 && arr[i] <= 63) || (arr[i] <= -32 && arr[i] >= -63)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -63;
      } else {
        encoded[i].catBaseVal = 32;
      }
      cat = '6';
    } else if ((arr[i] >= 64 && arr[i] <= 127) || (arr[i] <= -64 && arr[i] >= -127)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -127;
      } else {
        encoded[i].catBaseVal = 64;
      }
      cat = '7';
    } else if ((arr[i] >= 128 && arr[i] <= 255) || (arr[i] <= -128 && arr[i] >= -255)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -255;
      } else {
        encoded[i].catBaseVal = 128;
      }
      cat = '8';
    } else if ((arr[i] >= 256 && arr[i] <= 511) || (arr[i] <= -256 && arr[i] >= -511)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -511;
      } else {
        encoded[i].catBaseVal = 256;
      }
      cat = '9';
    } else if ((arr[i] >= 512 && arr[i] <= 1023) || (arr[i] <= -512 && arr[i] >= -1023)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -1023;
      } else {
        encoded[i].catBaseVal = 512;
      }
      cat = 'A';
    } else if ((arr[i] >= 1024 && arr[i] <= 2047) || (arr[i] <= -1024 && arr[i] >= -2047)) {
      if (arr[i] < 0) {
        encoded[i].catBaseVal = -2047;
      } else {
        encoded[i].catBaseVal = 1024;
      }
      cat = 'B';
    }
    encoded[i].cat = cat;
    getDCPrefix(&(encoded[i]), cat);
    valueEncoding(&(encoded[i]));
  }
  return encoded;
}

void getDCPrefix (BINARY_ENCODING *obj, char category) {
  if (category == '0') {
    obj->len = 3;
    obj->mantissa = 0;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "010");
  } else if (category == '1') {
    obj->len = 4;
    obj->mantissa = 1;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "011");
  } else if (category == '2') {
    obj->len = 5;
    obj->mantissa = 2;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "100");
  } else if (category == '3') {
    obj->len = 5;
    obj->mantissa = 3;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "00");
  } else if (category == '4') {
    obj->len = 7;
    obj->mantissa = 4;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "101");
  } else if (category == '5') {
    obj->len = 8;
    obj->mantissa = 5;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "110");
  } else if (category == '6') {
    obj->len = 10;
    obj->mantissa = 6;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "1110");
  } else if (category == '7') {
    obj->len = 12;
    obj->mantissa = 7;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "11110");
  } else if (category == '8') {
    obj->len = 14;
    obj->mantissa = 8;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "111110");
  } else if (category == '9') {
    obj->len = 16;
    obj->mantissa = 9;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "1111110");
  } else if (category == 'A') {
    obj->len = 18;
    obj->mantissa = 10;
    obj->code = (char *) malloc(sizeof(char) * (obj->len + 1));
    strcpy(obj->code, "11111110");
  }
}

void valueEncoding (BINARY_ENCODING *obj) {
  if (obj->val == 0) return;
  int c, d, count, n;
  char *p;
  count = 0;
  if (obj->catBaseVal < 0) {
    n = obj->catBaseVal - obj->val;
    obj->code[obj->len - obj->mantissa] = '0';
  } else {
    n = obj->val - obj->catBaseVal;
    obj->code[obj->len - obj->mantissa] = '1';
  }
  p = (char *) malloc(sizeof(char) * (32 + 1));
  for (c = 31; c >= 0; c--) {
    d = n >> c;
    if (d & 1) {
      *(p + count) = '1';
    } else {
      *(p + count) = '0';
    }
    count++;
  }
  *(p + count) = '\0';
  strcpy(&(obj->code[obj->len - obj->mantissa + 1]), &(p[33 - obj->mantissa]));
}

char * encoded2FullMessage(BINARY_ENCODING *encoded, int size){
  int i;
  
  int messageLen = 0;
  for(i = 0; i < size; i++){
    messageLen += encoded[i].len;
  }

  char *message = (char *) malloc(sizeof(char) * messageLen);

  for(i = 0; i < size; i++){
    strcat(message, encoded[i].code);
  }

  return message;

}

unsigned char *message2Buffer(char *message, int *bufferLen){
  int i, j;
  unsigned char *buffer = NULL;
  int messageLen = strlen(message);
  int count = 0;
  int charTam = 8;
  
  for(i = 0; i < messageLen; i += charTam){
    
    buffer = (unsigned char *) realloc (buffer, (sizeof(unsigned char) * (count + 1)));
    count++;
    
    for(j = i; j < charTam; j++){      
      // conversao do byte atual para um unico bit no buffer
      buffer[count] = ((buffer[count] << 1) | (message[j] == '1'));
    }
  }

  *bufferLen = count;
  return buffer;

}

void char2String(unsigned char c, char *decoded, int len){
  char *str = (char *) malloc(sizeof(char ) * 8);
  unsigned char aux;
  int i;

  for(i = 7; i >= 0; i--){
    aux = c >> i;
    str[7-i] = '0' + aux;

    aux = aux << i;
    c -= aux;
  }

  strcat(decoded, str);

  free(str);
}

char * file2Message(FILE *f, int fileLen){
  int i;
  unsigned char aux;
  char *decoded = (char *) malloc((fileLen * 8) + 1);
  i = ftell(f);
  
  while(i < fileLen){

    fread(&aux, sizeof(unsigned char), 1, f);
    char2String(aux, decoded, (fileLen * 8));
    
    i = ftell(f);
  }


  return decoded;

}



int main(int argc, char *argv[]){
  int i;
  int size = 256;
  int *array = (int *) malloc(sizeof(int) * size);
  for (i = 0; i < size; i++) {
    array[i] = i;
  }
  BINARY_ENCODING *encoded = coeficientCodification(array, size);
  char *message = encoded2FullMessage(encoded, size);

  // printf("%s\n", message);
  int bufferLen = 0;
  unsigned char *buffer = message2Buffer(message, &bufferLen);
  // printf("bufferLen: %d\n", bufferLen);

  // for(i = 0; i < bufferLen; i++){
  //   printf("%c ", buffer[i]);
  // }
  // printf("\n");


  FILE *out_bin, *in_bin;
  printf("Turning char to binary...\n");
 
  // Salvando binario do codigo criado
  printf("Writing binary file...\n");
  out_bin = fopen("out_bits.bin", "wb");
  fwrite(buffer, sizeof(unsigned char), bufferLen , out_bin);
  fclose(out_bin);

  
  in_bin  = fopen("out_bits.bin", "rb");
  
  fseek(in_bin, 0L, SEEK_END);
  int fileLen = ftell(in_bin);
  printf("fileLen * 8 = %d, strlen(message) = %d\n", fileLen*8, strlen(message));
  rewind(in_bin);

  char *decoded = file2Message(in_bin, fileLen);


  if(strlen(decoded) == strlen(message)){
    printf("TAMANHOS IGUAIS\n");

    for(i = 0; i < strlen(decoded); i++){
      if(message[i] != decoded[i]){
        printf("ALERTA DE ERRO---------\n");
        break;
      }
    }

    if(i == strlen(decoded)) printf("ALERTA DE TA TUDO BEM\n");

  }
  else printf("TAMANHOS DIFERENTES!\nstrlen(message)= %d | strlen(decoded)= %d\n", strlen(message), strlen(decoded));


  free(decoded);
  free(message);
  free(buffer);
  fclose(in_bin);

  return 0;
}