#include <stdlib.h>
#include <stdio.h>


void down_and_left(int * count, int * i, int * j, double *vet, double img[][8], int limit){
	while(*j-1 >= 0 && *i+1 < limit){
		*j = *j - 1;
		*i = *i + 1;
		vet[*count] = img[*i][*j];
		*count = *count + 1;
	}
}

void up_and_right(int * count, int * i, int * j, double *vet, double img[][8], int limit){
	while(*j+1 < limit && *i-1 >= 0){
		*j = *j + 1;
		*i = *i - 1;
		vet[*count] = img[*i][*j];
		*count = *count + 1;
	}
}


double * zigzagwalk(double img[][8], int maxDimension){
	double *vet = (double *) malloc(sizeof(double) * (maxDimension * maxDimension));

	if(vet != NULL){
		int i = 0, j = 0, count = 0;
		vet[count] = img[i][j];
		count++;

		while(count < (maxDimension * maxDimension)){
			//agora verificamos o limite das COLUNAS 
			if(j+1 < maxDimension) j++;
			
			// se estivermos no limite das COLUNAS progredimos nas LINHAS
			else{
				if(i+1 < maxDimension) {i++;}
			}
			vet[count] = img[i][j];
			count++;

			//feita essa etapa, podemos fazer o down_and_left
			down_and_left(&count, &i, &j,vet, img, maxDimension);

			// agora progredimos no outro sentido
			//agora verificamos o limite das COLUNAS 
			if(i+1 < maxDimension) i++;
			
			// se estivermos no limite das COLUNAS progredimos nas LINHAS
			else{
				if(j+1 < maxDimension) j++;
			}
			vet[count] = img[i][j];
			count++;
			
			up_and_right(&count, &i, &j, vet, img, maxDimension);


		}

	}

	return vet;

}

/*int main(int argc, char const *argv[]){

	double img[][8] = {	{-415, -33, -58, 35, 58, -51, -15, -12},
						{5, -34, 49, 18, 27, 1, -5, 3},
						{-46, 14, 80, -35, -50, 19, 7, -18},
						{-53, 21, 34, -20, 2, 34, 36, 12},
						{9, -2, 9, -5, -32, -15, 45, 37},
						{-8, 15, -16, 7, -8, 11, 4, 7},
						{19, -28, -2, -26, -2, 7, -44, -21},
						{18, 25, -12, -44, 35, 48, -37, -3}
						};


	double *vet = zigzagwalk(img, 8);

	
	int i;
	for(i = 0; i < 8*8; i++) printf("%lf, ", vet[i]);
	free(vet);

	return 0;
}*/