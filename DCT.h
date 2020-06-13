#ifndef DCT_H_INCLUDED
#define DCT_H_INCLUDED
//****** Funções auxiliares para manipulação de matrizes ***********************
double ** allocateDoubleMatrix(int width, int height);

unsigned char ** allocateCharMatrix(int width, int height);

void freeDoubleMatrix(double **mat, int height);

void freeCharMatrix(unsigned char **mat, int height);
//****** FIM das funções auxiliares para manipulação de matrizes ***********************

/*
void dct: executa a Transformada Discreta dos Cossenos sobre sub-matrizes da imagem.
PARAMETROS:
	double **input: sub-matriz de entrada para a DCT
	double **output: sub-matriz de saída para a DCT
	int startWidth, startHeight: indíces de início na sub-matriz relativos à imagem toda
RETORNO:
	[retorno por derreferência]
*/
void dct(double **input, double **output, int startWidth, int startHeight );

/*
void idct: função inversa da função dct
*/
void idct(double **input, double **output, int startWidth, int startHeight );

/*
unsigned char **convertDoubleMatrixToChar: função que converte uma matriz de double e converte para
	uma matriz de unsigned char
PARAMETROS:
	double ** image: matriz de entrada:
	int width, height: dimensões da matriz
RETORNO:
	unsigned char ** new: matriz de saída após a conversão
*/
unsigned char **convertDoubleMatrixToChar(double **image, int width, int height);


/*
double ** DCTImage: função que cuida da iteração sobre sub-matrizes 8x8 sobre a imagem original para
	a aplicação da DCT em cada uma
PARAMETROS:
	double **image: imagem original convertida para double **
	int width, height: dimensoes da matriz original
RETORNO:
	double **DCTImage: matriz de saída da DCT geral
*/
double **DCTImage(double **image, int width, int height);

/*
unsigned char **IDCTImage: função inversa da função DCTImage
*/
double **IDCTImage(double **image, int width, int height);
#endif