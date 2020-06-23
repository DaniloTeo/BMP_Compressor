#include <stdlib.h>
#include <stdio.h>




void down_and_left(int * count, int * i, int * j, double *vet, double **img, int limit ,int flag){
	while(*j-1 >= 0 && *i+1 < limit){
		*j = *j - 1;
		*i = *i + 1;
		if(flag == 1){
			// printf("linha 12\nimg[%d][%d]: %lf; vet[%d]: %lf\n", *i, *j, img[*i][*j], *count, vet[*count]);
			vet[*count] = img[*i][*j];
		}
		else
			img[*i][*j] = vet[*count];
		*count = *count + 1;
	}
}

void up_and_right(int * count, int * i, int * j, double *vet, double **img, int limit,int flag){
	while(*j+1 < limit && *i-1 >= 0){
		*j = *j + 1;
		*i = *i - 1;
		if(flag == 1){
			// printf("linha 25\nimg[%d][%d]: %lf; vet[%d]: %lf\n", *i, *j, img[*i][*j], *count, vet[*count]);
			vet[*count] = img[*i][*j];
		}
		else
			img[*i][*j] = vet[*count];
		*count = *count + 1;
	}
}


double * zigzagwalk(double **img, int width, int height){
	double *vet = (double *) malloc(sizeof(double) * (width * height));
	// printf("linha 34\nstarHeight: %d; startWidth: %d\n", startHeight, startWidth);
	if(vet != NULL){
		int i = 0, j = 0, count = 0;
		// printf("linha 37\nimg[%d][%d]: %lf; vet[%d]: %lf\n", i, j, img[i][j], count, vet[count]);
		vet[count] = img[i][j];
		count++;

		while(count < (width * height)){
			//agora verificamos o limite das COLUNAS 
			if(j+1 < (width)) j++;
			
			// se estivermos no limite das COLUNAS progredimos nas LINHAS
			else{
				if(i+1 < (height)) i++;
			}
			// printf("linha 49\nimg[%d][%d]: %lf; vet[%d]: %lf\n", i, j, img[i][j], count, vet[count]);
			vet[count] = img[i][j];
			count++;

			//feita essa etapa, podemos fazer o down_and_left
			down_and_left(&count, &i, &j,vet, img, height, 1);

			// agora progredimos no outro sentido
			//agora verificamos o limite das COLUNAS 
			if(i+1 < (height)) i++;
			
			// se estivermos no limite das COLUNAS progredimos nas LINHAS
			else{
				if(j+1 < (width)) j++;
			}
			// printf("linha 64\nimg[%d][%d]: %lf; vet[%d]: %lf\n", i, j, img[i][j], count, vet[count]);
			vet[count] = img[i][j];
			count++;
			
			up_and_right(&count, &i, &j, vet, img, width, 1);


		}

	}

	return vet;

}

// double * zigzagImage(double **img, int width, int height, int *n_vet){
// 	int i, j, k = 0;

// 	double *imageVector = (double **)malloc(sizeof(double *) * (width * height));

// 	// printf("width: %d; height: %d\n\n", width, height);
// 	for(i = 0; i < height; i+=8){
// 		for(j = 0; j < width; j+=8){
// 			// printf("linha 84\nk+1: %d\n", (k+1));
// 			zigzagwalk(img, 8, i, j);
// 			// printf("linha 86\n");
// 			k++;
// 		}	
// 	}



// 	// *n_vet = k;
// 	return imageVector;

// }


void deZigZag(double **img, double *vet, int width, int height){
	int i = 0, j = 0, count = 0;

	img[i][j] = vet[count];
	count++;

	while(count < (width * height)){
		//agora verificamos o limite das COLUNAS 
		if(j+1 < (width)) j++;
		
		// se estivermos no limite das COLUNAS progredimos nas LINHAS
		else{
			if(i+1 < (height)) {i++;}
		}

		img[i][j] = vet[count];
		count++;

		//feita essa etapa, podemos fazer o down_and_left
		down_and_left(&count, &i, &j,vet, img, (height),0);

		// agora progredimos no outro sentido
		//agora verificamos o limite das COLUNAS 
		if(i+1 < (height)) i++;
		
		// se estivermos no limite das COLUNAS progredimos nas LINHAS
		else{
			if(j+1 < (width)) j++;
		}
		// vet[count] = img[i][j];
		img[i][j] = vet[count];
		count++;
		
		up_and_right(&count, &i, &j, vet, img, (width),0);


	}



}

// double **deZigZagImage(double **imageVector, int n_vet, int width, int height){
// 	int i, j;
// 	int k = n_vet;
// 	double **newImg = (double **) malloc(sizeof(double*) * (height));
// 	for(i = 0; i < height; i++){
// 		newImg[i] = (double *) malloc(sizeof(double) * (width));
// 	}


// 	for (i = 0; i < height; i+=8){
// 		for(j = 0; j < width; j+=8){
// 			deZigZag(newImg, imageVector[n_vet-k], 8, i, j);
// 			k--;
// 		}
// 	}

// 	return newImg;
// }

/*
int main(int argc, char const *argv[]){
	int i,j;
	int h = 9 , w = 9;
	double ** img = (double **) malloc(sizeof(double*) * h);

	// printf("IMAGEM ORIGINAL:\n");
	for(i = 0; i < h; i++){
			img[i] = (double*)malloc(sizeof(double) * w);
		for(j = 0; j < w; j++){
			img[i][j] = (i * h) + j;
			printf("%.2lf ", img[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

	int n_vet = 0;

	double *vet = zigzagwalk(img, w, h);


	printf("VETORIZADO:\n");
	for(i = 0; i < (w * h); i++){
		printf("%.2lf ", vet[i]);
	}
	printf("\n\n");
	
	


	deZigZag(img, vet, w, h);
	printf("NOVA IMAGEM:\n");
	for(i = 0; i < h; i++){
		for(j = 0; j < w; j++){
			printf("%.2lf ", img[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");






	for(i = 0; i < 8; i++) {
		// free(newImg[i]);
		free(img[i]);
	}

	
	// free(newImg);
	free(img);	
	free(vet);

	return 0;
}*/