#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "rle.h"
#include "encoder.h"

BINARY_ENCODING *coeficientCodification (int *arr, int len) {
  int i;
  char cat;
  printf("encoder:11\n");
  BINARY_ENCODING *encoded = (BINARY_ENCODING *) malloc(sizeof(BINARY_ENCODING) * len);
  printf("encoder:13\n");
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
    // printf("encoded:97\n");
    getDCPrefix(&(encoded[i]), cat);
    // printf("encoded:99\n");
    valueEncoding(&(encoded[i]));
    // printf("encoded:101\n");
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
  printf("encoded:194\n");
  int messageLen = 0;
  for(i = 0; i < size; i++){
    messageLen += encoded[i].len;
  }
  printf("encoded:198\n");

  char *message = (char *) malloc(sizeof(char) * messageLen);
  printf("encoded:201\n");
  for(i = 0; i < size; i++){
    strcat(message, encoded[i].code);
  }
  printf("encoded:205\n");
  return message;

}

unsigned char *message2Buffer(char *message, int *bufferLen){
  int i, j;
  unsigned char *buffer = NULL;
  int messageLen = strlen(message);
  int count = 0;
  int charTam = 8;
  printf("encoded:216\n");
  for(i = 0; i < messageLen; i += charTam){
    
    buffer = (unsigned char *) realloc (buffer, (sizeof(unsigned char) * (count + 1)));
    
    
    // printf("message ---- \n");
    for(j = i; j < (charTam + i); j++){      
      // conversao do byte atual para um unico bit no buffer
      buffer[count] = ((buffer[count] << 1) | (message[j] == '1'));
      // printf("%c ", message[j]);
    }
    // printf("buffer[%d] = %d\n", count, buffer[count]);
    count++;
  }
  printf("encoded:231\n");

  *bufferLen = count;
  return buffer;

}

void char2String(unsigned char c, char *decoded){
  char *str = (char *) malloc(sizeof(char ) * 8);
  unsigned char aux = 0;
  int i;

  for(i = 7; i >= 0; i--){
    // printf("231: i = %d, c =  %d\n",i, c);
    aux = c >> i;
    // printf("233: i = %d, aux =  %d\n",i, aux);
    str[7-i] = '0' + aux;
    // printf("235: str[%d] = %d\n", (7-i), str[7-i]);

    aux = aux << i;
    // printf("238: i = %d, aux =  %d\n",i, aux);
    c -= aux;
  // printf("240: i = %d, c =  %d\n",i, c);

  }

  strcat(decoded, str);
  // printf("decoded: %s\n", decoded);
  free(str);
  // printf("241\n");
}

char * file2Message(FILE *f, int fileLen, int bufferLen){
  int i = 0;
  unsigned char aux;
  char *decoded = (char *) malloc((fileLen * 8) + 1);
  printf("fileLen: %d\n", fileLen);

  do{
    fread(&aux, sizeof(unsigned char), 1, f);
    i++;
    // printf("-----------------------------------\n");
    // printf("257: aux: %d, ftell(f): %d\n", (int)aux, (int)ftell(f));
    char2String(aux, decoded);
    // printf("-----------------------------------\n");
    // printf("aux = %d, decoded = %s\n", aux, decoded);
    
  }while(i < bufferLen && (!feof(f)));

  return decoded;
}

int isPrefix(char * accumulator) {
  if (strcmp(accumulator, "010") == 0) {
    return 0;
  } else if (strcmp(accumulator, "011") == 0) {
    return 1;
  } else if (strcmp(accumulator, "100") == 0) {
    return 2;
  } else if (strcmp(accumulator, "00") == 0) {
    return 3;
  } else if (strcmp(accumulator, "101") == 0) {
    return 4;
  } else if (strcmp(accumulator, "110") == 0) {
    return 5;
  } else if (strcmp(accumulator, "1110") == 0) {
    return 6;
  } else if (strcmp(accumulator, "11110") == 0) {
    return 7;
  } else if (strcmp(accumulator, "111110") == 0) {
    return 8;
  } else if (strcmp(accumulator, "1111110") == 0) {
    return 9;
  } else if (strcmp(accumulator, "11111110") == 0) {
    return 10;
  } else return -1;  
}

int decodeNumber(char *suffix, int suffixSize) {
  char signal = suffix[0];
  int i;
  int baseCatVal;
  if (signal == '0') {
    baseCatVal = (pow(2, suffixSize) - 1) * (-1);
  } else {
    baseCatVal = (pow(2, suffixSize - 1));
  }
  for (i = suffixSize - 1; i > 0; i--) {
    baseCatVal += pow(2, suffixSize - i - 1) * (suffix[i] - '0');
  }
  return baseCatVal;
}

int *decodeBinaryString(char *bin, int fileLen) {
  int len = fileLen;//strlen(bin);
  int i, suffixSize, j, val, prefixIndex;
  int *decodedValues = (int *) malloc(sizeof(int));
  char *prefix = (char *) malloc(sizeof(char) * 9);
  char *suffix = (char *) malloc(sizeof(char) * 11);
  val = 0;
  prefixIndex = 0;
  for (i = 0; i < len; i++) {
    prefix[prefixIndex] = bin[i];
    prefixIndex++;
    // printf("prefixo = %s\n", prefix);
    suffixSize = isPrefix(prefix);
    if (suffixSize == 0) {
      decodedValues[val] = 0;
      val++;
      decodedValues = (int *) realloc(decodedValues, sizeof(int) * (val + 1));
      prefixIndex = 0;
      for (j = 0; j < 9; j++) {
        prefix[j] = '\0';
      }
    } else if (suffixSize > 0) {
      for (j = i + 1; j < i + suffixSize + 1; j++) {
        suffix[j - i - 1] = bin[j];
      }
      suffix[suffixSize] = '\0';
      // printf("sufixo = %s\n",suffix);
      decodedValues[val] = decodeNumber(suffix, suffixSize);
      // printf("VALOR DECODIFICADO = %d\n", decodedValues[val]);
      // printf("VALOR ESPERADO     = %d\n", val);
      val++;
      // i = i + j - 1; // --> passo perde um monte de valores
      i = i + suffixSize;
      decodedValues = (int *) realloc(decodedValues, sizeof(int) * (val + 1));
      // printf("I = %d, J = %d, PREFIXINDEX = %d\n", i, j, prefixIndex);
      prefixIndex = 0;
      for (j = 0; j < 9; j++) {
        prefix[j] = '\0';
      }
    }
  }
  free(prefix);
  free(suffix);
  return decodedValues;
}

void EI2File(ENCODED_IMAGE **img, FILE *f, int len) {
  int i;
  unsigned char *buffer = NULL;
  int bufferLen = 0;
  BINARY_ENCODING *encodedQts = NULL;
  BINARY_ENCODING *encodedVals = NULL;
  char *auxMessage = NULL;
  int messageLen = 0;
  printf("len: %d\n", len);
  
  for (i = 0; i < len; i++) {
    printf("i = %d\n", i);
    if (i >= len) {
      printf("ERA PRA TER PARADO PORRA\n");
    }
    // printf("encoder:373\n");
    encodedQts = coeficientCodification(img[i]->qtds, img[i]->len);
    // printf("encoder:375\n");
    encodedVals = coeficientCodification(img[i]->info, img[i]->len);
  
   
    //write qtds
    // printf("encoder:380\n");
    auxMessage = encoded2FullMessage(encodedQts, img[i]->len);
    // printf("encoder:382\n");
    messageLen = (int)strlen(auxMessage);
    // printf("QTDS - %d: messageLen = %d\n", i, messageLen);
    fwrite(&messageLen, sizeof(int), 1, f);
    // printf("encoder:385\n");
    bufferLen = 0;
    buffer = message2Buffer(auxMessage, &bufferLen);
    // printf("QTDS - %d: bufferLen = %d\n", i, bufferLen);
    // printf("encoder:388\n");
    fwrite(&bufferLen, sizeof(int), 1, f);
    // printf("encoder:390\n");
    fwrite(&buffer, sizeof(unsigned char), bufferLen, f);
    // printf("encoder:392\n");

    //clear memory for writing info array
    free(buffer); buffer = NULL;
    free(auxMessage); auxMessage = NULL;
    printf("QTDS - ftell(f): %d\n",(int)ftell(f));
    //write info
    // printf("encoded:399\n");
    auxMessage = encoded2FullMessage(encodedVals, img[i]->len);
    // printf("encoded:401\n");
    messageLen = (int)strlen(auxMessage);
    // printf("INFO - %d: messageLen = %d\n", i, messageLen);
    fwrite(&messageLen, sizeof(int), 1, f);
    // printf("encoded:404\n");
    bufferLen = 0;
    buffer = message2Buffer(auxMessage, &bufferLen);
    // printf("INFO - %d: bufferLen = %d\n", i, bufferLen);
    // printf("encoded:407\n");
    fwrite(&bufferLen, sizeof(int), 1, f);
    // printf("encoded:409\n");
    fwrite(&buffer, sizeof(unsigned char), bufferLen, f);
    // printf("encoded:411\n");
    printf("INFO - ftell(f): %d\n",(int)ftell(f));
    
    // reset memory for next iteration
    free(buffer);
    free(auxMessage);

    free(encodedQts->code);
    free(encodedQts);
    free(encodedVals->code);
    free(encodedVals);


  }
}


void File2EI(ENCODED_IMAGE **img, FILE *f, int len){
  int i;
  int msgLen = 0, bufferLen = 0;
  char *bitsString = NULL;

  for(i = 0; i < len; i++){

    //leitura do vetor de qtds
    fread(&msgLen, sizeof(int), 1, f);
    fread(&bufferLen, sizeof(int),1, f);
    bitsString = file2Message(f, msgLen, bufferLen);
    img[i]->qtds = decodeBinaryString(bitsString, msgLen);

    bufferLen = 0;
    msgLen = 0;
    free(bitsString);bitsString = NULL;

    //leitura do vetor info
    fread(&msgLen, sizeof(int), 1, f);
    fread(&bufferLen, sizeof(int),1, f);
    bitsString = file2Message(f, msgLen, bufferLen);
    img[i]->info = decodeBinaryString(bitsString, msgLen);


    bufferLen = 0;
    msgLen = 0;
    free(bitsString);bitsString = NULL;
  }
}

// int main(int argc, char *argv[]){
//   int i;
//   int size = 10;
//   int *array = (int *) malloc(sizeof(int) * size);
//   for (i = 0; i < size; i++) {
//     array[i] = i;
//   }
//   BINARY_ENCODING *encoded = coeficientCodification(array, size);
//   char *message = encoded2FullMessage(encoded, size);

//   int bufferLen = 0;
//   unsigned char *buffer = message2Buffer(message, &bufferLen);
//   // printf("bufferLen: %d\n", bufferLen);





//   FILE *out_bin, *in_bin;
//   printf("Turning char to binary...\n");
 
//   // Salvando binario do codigo criado
//   printf("Writing binary file...\n");
//   out_bin = fopen("out_bits.bin", "wb");
//   int messageLen = (int) strlen(message);
//   fwrite(&messageLen, sizeof(int), 1 ,out_bin);
//   fwrite(buffer, sizeof(unsigned char), bufferLen , out_bin);
//   fclose(out_bin);

  
//   in_bin  = fopen("out_bits.bin", "rb");
  
//   int fileLen = 0;
 
//   fseek(in_bin, 0, SEEK_END);
//   int tam = ftell(in_bin);
//   rewind(in_bin);
 
//   fread(&fileLen, sizeof(int), 1, in_bin);
//   char *decoded = file2Message(in_bin, fileLen);
  
  

//   int *fullyDecoded4real = decodeBinaryString(decoded, fileLen);
  

//   free(decoded);
//   free(message);
//   free(buffer);
//   free(fullyDecoded4real);
//   fclose(in_bin);

//   return 0;
// }