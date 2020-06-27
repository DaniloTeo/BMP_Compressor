#ifndef ZIGZAG_H_INCLUDED
#define ZIGZAG_H_INCLUDED


/*
void down_and_left/up_and_right: funcao que caminha na diagonal para baixo e para esquerda/para cima e para
direita em uma matriz de limitXlimit e insere os elementos em um vetor (encoding) OU executa a operação reversa (decoding) retirando os 
elementos do vetor e inserindo-os em uma matriz limitXlimit
PARAMETROS:
	int * count: ponteiro para o contador de elementos no vetor de saida;
	int * i, j: ponteiro para os indices atuais na matriz;
	double * vet: vetor de saída do encoding;
	double **img: sub-matriz da imagem original (tamanho limitXlimit);
	int limit: limite máximo que os indices podem atingir;
	int minWidth/minHeight: ponto com o minimo valor da sub-matriz sendo varrida;
	int flag: indicador da operação a ser realizada (encoding/decoding);
RETORNO: 
	[retorno por derreferência]
*/
void down_and_left(int * count, int * i, int * j, double *vet, double **img, int limit, int minWidth,int flag);
void up_and_right(int * count, int * i, int * j, double *vet, double **img, int limit, int minHeight,int flag);

/*
double * zigzagwalk: função que caminha em zigzag em uma matriz de tamanho maxDimension X maxDimension
cuidando dos side-steps necessários quando se atinge a borda da matriz e insere os elementos em um vetor
linear.
PARAMETROS:
	double **img: matriz de doubles a ser escaneada em zigzag;
	int maxDimension: dimensoes da matriz;
	int startHeight, startWidth: indices de inicio para o scan;
RETORNO:
	double * vet: vetor linear com os elementos inseridos na ordem em que foram escaneados
*/
double * zigzagwalk(double **img, int maxDimension, int startHeight, int startWidth);

double ** zigzagImage(double **img, int width, int height, int *n_vet);

/*
void deZigZag: função inversa da função zigzagwalk fazendo o decoding do vetor para matriz
*/
void deZigZag(double **img, double *vet, int maxDimension, int startHeight, int startWidth);

double **deZigZagImage(double **imageVector, int n_vet, int width, int height);

#endif
