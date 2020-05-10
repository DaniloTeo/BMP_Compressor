#include <stdlib.h>
#include <stdio.h>

double * encodeRLE(double *vet, int n, int *conts, int *conts_len, int *tam){
	int i;
	
	//tamanho do vetor output
	printf("Alocando novo vetor com o tamanho original...\n");
	double * output = (double *)malloc(sizeof(double) * n);
	
	for(i = 0; i < n; i++){
		int count = 1;

		while(i < n - 1 && vet[i] == vet[i+1]){
			count++;
			i++;

		}

		printf("Inserindo valor no contador...\n");
		conts[*conts_len] = count;
		(*conts_len)+=1;
		output[*tam] = vet[i];
		(*tam)+=1;
	}

	printf("Fim do algoritmo principal...\n");
	printf("\n\n");

	output = (double *) realloc(output, sizeof(double) * (*tam));


	return output;
}


double *decodeRLE(int *conts, int len, double *comp, int *decomp_len){
	int i,j = 0;

	//descobir o tamanho do vetor original
	for(i = 0; i < len; i++){
		(*decomp_len) += conts[i];
	}

	double *output = (double *) malloc(sizeof(double) * (*decomp_len));

	for(i = 0; i < len; i++){
		while(conts[i] > 0){
			output[j] = comp[i];
			conts[i] = conts[i]-1;
			j++;
		}
	}

	return output;


}


void printVetorInt(int *vet, int n){
	int i = 0;
	printf("TAMANHO DO VETOR: %d\n", n);
	printf("VETOR:\n");
	for(i = 0; i < n; i++){
		printf("%d ", vet[i]);
	}
	printf("\n");
}
void printVetorDouble(double *vet, int n){
	int i = 0;
	printf("TAMANHO DO VETOR: %d\n", n);
	printf("VETOR:\n");
	for(i = 0; i < n; i++){
		printf("%lf ", vet[i]);
	}
	printf("\n");
}

/*
int main(void){
	// char string[] = "wwwwaaadexxxxxxywww";
	double vet[13] = {32.0, 32.0, 12.2, 12.2, 12.2, 30.6, 42.42, 5.0,5.0,5.0, 41.2, 41.2, 41.2};
	int *conts = (int *) calloc(13, sizeof(int));
	int conts_len = 0, comp_len = 0;

	printf("VETOR ORIGINAL:\n");
	printVetorDouble(vet, 13);

	printf("Comprimindo\n\n");
	double * comp = encodeRLE(vet, 13, conts, &conts_len, &comp_len);


	conts = (int *)realloc(conts, sizeof(int) * conts_len);

	printVetorDouble(comp, comp_len);
	printVetorInt(conts, conts_len);


	printf("Extraindo...\n");
	int decomp_len = 0;
	double *output = decodeRLE(conts, conts_len, comp, &decomp_len);
	printVetorDouble(output, decomp_len);


	free(output);
	free(comp);
	free(conts);
	return 0;
}*/
