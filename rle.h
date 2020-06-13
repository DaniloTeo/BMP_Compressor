#ifndef RLE_H_INCLUDED
#define RLE_H_INCLUDED



/*
ENCODE_IMAGE
	struct para armazenar o ouput das funções de RLE
	ATTR:
		double *info: vetor com elementos unicos do vetor original;
		int *qtds: vetor com o numero de repetições de cada um dos elementos do vetor original
		int len: tamanho de ambos os vetores acima
*/
typedef struct{
	double *info;
	int *qtds;
	int len;

} ENCODED_IMAGE;


/*
ENCODED_IMAGE *initializeEncoded: aloca a memoria necessaria e inicializa os atributos de um
elemento do tipo ENCODED_IMAGE.
PARAMETROS:	
	---
RETORNA:
	ENCODED_IMAGE *img: struct devidamente inicializada
*/
ENCODED_IMAGE *initializeEncoded(void);

/*
void freeEncoded: libera a memoria alocada para um elemento ENCODED_IMAGE
PARAMETROS:
	ENCODED_IMAGE * img: elemento a ter a memoria liberada
RETORNA:
	---
*/
void freeEncoded(ENCODED_IMAGE * img);

/*
void freeVetorEncoded: itera sobre um vetor de elementos ENCODED_IMAGE a fim de liberar a memoria.
PARAMETROS:
	ENCODED_IMAGE **img: vetor de ENCODED_IMAGE *;
	int len: tamanho do vetor a ser desalocado
RETORNA:
	---
*/
void freeVetorEncoded(ENCODED_IMAGE **img, int len);

/*
void printVetorInt: função de impressão de inteiros auxiliar
*/
void printVetorInt(int *vet, int n);

/*
void printVetorDouble: função de impressão de double auxiliar
*/
void printVetorDouble(double *vet, int n);

/*
void encodeRLE: executa o RUN LENGHT ENCODING sobre um vetor de double.
PARAMETROS:
	double * vet: vetor de doubles a ser comprimido;
	int n: comprimento do vetor vet;
	ENCODED_IMAGE *out: elemento de output do vetor comprimido
RETORNA:	
	[retorno por derreferência]

*/
void encodeRLE(double *vet, int n, ENCODED_IMAGE *out);

/*
double decodeRLE: função inversa da função encodeRLE
*/
double *decodeRLE(ENCODED_IMAGE *input, int *decomp_len);

/*
ENCODED_IMAGE **encodeImage: função que itera sobre um vetor de double * e executa o RUN-LENGTH
ENCODING para cada sub-vetor
PARAMETROS:
	double **img: vetor de double * a ser comprimido
	int length: comprimento do vetor
RETORNA:
	ENCODED_IMAGE ** output: vetor de ENCODED_IMAGE * 
*/
ENCODED_IMAGE **encodeImage(double **img, int length);

/*
double ** decodeImage: função inversa da função encodeImage
*/
double **decodeImage(ENCODED_IMAGE **encoded, int length);



#endif