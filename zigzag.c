#include <stdlib.h>
#include <stdio.h>


void down_and_left(int * count, int * i, int * j, double *vet, double **img, int limit){
	while(*j-1 >= 0 && *i+1 < limit){
		*j = *j - 1;
		*i = *i + 1;
		vet[*count] = img[*i][*j];
		*count = *count + 1;
	}
}

void up_and_right(int * count, int * i, int * j, double *vet, double **img, int limit){
	while(*j+1 < limit && *i-1 >= 0){
		*j = *j + 1;
		*i = *i - 1;
		vet[*count] = img[*i][*j];
		*count = *count + 1;
	}
}


double * zigzagwalk(double **img, int maxDimension, int startHeight, int startWidth){
	double *vet = (double *) malloc(sizeof(double) * (maxDimension * maxDimension));

	if(vet != NULL){
		int i = startHeight, j = startWidth, count = 0;
		vet[count] = img[i][j];
		count++;

		while(count < (maxDimension * maxDimension)){
			//agora verificamos o limite das COLUNAS 
			if(j+1 < (startWidth + maxDimension)) j++;
			
			// se estivermos no limite das COLUNAS progredimos nas LINHAS
			else{
				if(i+1 < (startHeight + maxDimension)) {i++;}
			}
			vet[count] = img[i][j];
			count++;

			//feita essa etapa, podemos fazer o down_and_left
			down_and_left(&count, &i, &j,vet, img, (startHeight + maxDimension));

			// agora progredimos no outro sentido
			//agora verificamos o limite das COLUNAS 
			if(i+1 < (startHeight + maxDimension)) i++;
			
			// se estivermos no limite das COLUNAS progredimos nas LINHAS
			else{
				if(j+1 < (startWidth + maxDimension)) j++;
			}
			vet[count] = img[i][j];
			count++;
			
			up_and_right(&count, &i, &j, vet, img, (startWidth + maxDimension));


		}

	}

	return vet;

}

double ** zigzagImage(double **img, int width, int height, int *n_vet){
	int i, j, k = 0;

	double **imageVector = (double **)malloc(sizeof(double *) * (width/8) * (height/8));


	for(i = 0; i < height; i+=8){
		for(j = 0; j < width; j+=8){
			imageVector[k] = zigzagwalk(img, 8, i, j);
			k++;
		}	
	}



	*n_vet = k;
	return imageVector;

}



/*int main(int argc, char const *argv[]){
	int i,j;
	double ** img = (double **) malloc(sizeof(double*) * 8);

	for(i = 0; i < 8; i++){
			img[i] = (double*)malloc(sizeof(double) * 8);
		for(j = 0; j < 8; j++){
			img[i][j] = (i * 8) + j;
			printf("%.2lf ", img[i][j]);
		}
		printf("\n");
	}


	int n_vet = 0;

	double **vet = zigzagImage(img, 8, 8, &n_vet);

	
	


	for(i = 0; i < n_vet; i++){
		for(j = 0; j < 8*8; j++){
			printf("%.2lf ", vet[i][j]);
		}
		printf("\n");
	}

	
	for(i = 0; i < 8; i++) {
		free(img[i]);
	}

	for(i = 0; i < n_vet; i++){
		free(vet[i]);
	}


	free(img);
	free(vet);

	return 0;
}*/