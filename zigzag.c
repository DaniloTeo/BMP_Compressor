#include <stdlib.h>
#include <stdio.h>






void down_and_left(int * count, int * i, int * j, double *vet, double **img, int limit, int minWidth,int flag){
	while(*j-1 >= minWidth && *i+1 < limit){
		*j = *j - 1;
		*i = *i + 1;
		if(flag == 1){
			vet[*count] = img[*i][*j];
		}
		else img[*i][*j] = vet[*count];
		
		*count = *count + 1;
	}
}

void up_and_right(int * count, int * i, int * j, double *vet, double **img, int limit, int minHeight,int flag){
	while(*j+1 < limit && *i-1 >= minHeight){
		*j = *j + 1;
		*i = *i - 1;
		if(flag == 1){
			vet[*count] = img[*i][*j];
		}
		else img[*i][*j] = vet[*count];

		*count = *count + 1;
	}
}


double * zigzagwalk(double **img, int maxDimension, int startHeight, int startWidth){
	double *vet = (double *) malloc(sizeof(double) * (maxDimension * maxDimension));
	// printf("linha 34\nstarHeight: %d; startWidth: %d\n", startHeight, startWidth);
	if(vet != NULL){
		int i = startHeight, j = startWidth, count = 0;
		// printf("linha 37\nimg[%d][%d]: %lf; vet[%d]: %lf\n", i, j, img[i][j], count, vet[count]);
		vet[count] = img[i][j];
		count++;

		while(count < (maxDimension * maxDimension)){
			//agora verificamos o limite das COLUNAS 
			if(j+1 < (startWidth + maxDimension)) j++;
			
			// se estivermos no limite das COLUNAS progredimos nas LINHAS
			else{
				if(i+1 < (startHeight + maxDimension)) {i++;}
			}
			// printf("linha 49\nimg[%d][%d]: %lf; vet[%d]: %lf\n", i, j, img[i][j], count, vet[count]);
			vet[count] = img[i][j];
			count++;

			//feita essa etapa, podemos fazer o down_and_left
			down_and_left(&count, &i, &j,vet, img, (startHeight + maxDimension), startWidth, 1);

			// agora progredimos no outro sentido
			//agora verificamos o limite das COLUNAS 
			if(i+1 < (startHeight + maxDimension)) i++;
			
			// se estivermos no limite das COLUNAS progredimos nas LINHAS
			else{
				if(j+1 < (startWidth + maxDimension)) j++;
			}
			// printf("linha 64\nimg[%d][%d]: %lf; vet[%d]: %lf\n", i, j, img[i][j], count, vet[count]);
			vet[count] = img[i][j];
			count++;
			
			up_and_right(&count, &i, &j, vet, img, (startWidth + maxDimension), startHeight, 1);


		}

	}

	return vet;

}

double ** zigzagImage(double **img, int width, int height, int *n_vet){
	int i, j, k = 0;
	int maxDimension = 4;
	double **imageVector = (double **)malloc(sizeof(double *) * (width * height)/(maxDimension*maxDimension));

	// printf("width: %d; height: %d\n\n", width, height);
	for(i = 0; i < height; i+= maxDimension){
		for(j = 0; j < width; j+= maxDimension){
			// printf("linha 84\nk+1: %d\n", (k+1));
			imageVector[k] = zigzagwalk(img, maxDimension, i, j);
			// printf("linha 86\n");
			k++;
		}	
	}



	*n_vet = k;
	return imageVector;

}


void deZigZag(double **img, double *vet, int maxDimension, int startHeight, int startWidth){
	int i = startHeight, j = startWidth, count = 0;

	img[i][j] = vet[count];
	count++;

	while(count < (maxDimension * maxDimension)){
		//agora verificamos o limite das COLUNAS 
		if(j+1 < (startWidth + maxDimension)) j++;
		
		// se estivermos no limite das COLUNAS progredimos nas LINHAS
		else{
			if(i+1 < (startHeight + maxDimension)) {i++;}
		}

		img[i][j] = vet[count];
		count++;

		//feita essa etapa, podemos fazer o down_and_left
		down_and_left(&count, &i, &j,vet, img, (startHeight + maxDimension), startWidth,0);

		// agora progredimos no outro sentido
		//agora verificamos o limite das COLUNAS 
		if(i+1 < (startHeight + maxDimension)) i++;
		
		// se estivermos no limite das COLUNAS progredimos nas LINHAS
		else{
			if(j+1 < (startWidth + maxDimension)) j++;
		}
		// vet[count] = img[i][j];
		img[i][j] = vet[count];
		count++;
		
		up_and_right(&count, &i, &j, vet, img, (startWidth + maxDimension), startHeight,0);


	}



}

double **deZigZagImage(double **imageVector, int n_vet, int width, int height){
	int i, j;
	int k = n_vet;
	int maxDimension = 4;
	double **newImg = (double **) malloc(sizeof(double*) * (height));
	for(i = 0; i < height; i++){
		newImg[i] = (double *) malloc(sizeof(double) * (width));
	}


	for (i = 0; i < height; i+=maxDimension){
		for(j = 0; j < width; j+=maxDimension){
			deZigZag(newImg, imageVector[n_vet-k], maxDimension, i, j);
			k--;
		}
	}

	return newImg;
}




// int main(int argc, char const *argv[]){
// 	int i,j;
// 	int l = 2, c = 3;
// 	int w = 4 * l , h = 4 * c;
// 	double ** img = (double **) malloc(sizeof(double*) * h);
// 	printf("IMAGEM ORIGINAL:\n");
// 	for(i = 0; i < h; i++){
// 			img[i] = (double*)malloc(sizeof(double) * w);
// 		for(j = 0; j < w; j++){
// 			img[i][j] = (i * h) + j;
// 			printf("%.2lf ", img[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	// printf("\n\n");
// 	int n_vet = 0;
// 	double **vet = zigzagImage(img, w, h, &n_vet);
// 	printf("VETORIZADO:\n");
// 	for(i = 0; i < n_vet; i++){
// 		for(j = 0; j < 4*4; j++){
// 			printf("%.2lf ", vet[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n\n");
	
	
// 	double ** newImg = deZigZagImage(vet, n_vet, w, h);
// 	// printf("NOVA IMAGEM:\n");
// 	for(i = 0; i < h; i++){
// 		for(j = 0; j < w; j++){
// 			// printf("%.2lf ", newImg[i][j]);
// 			if(newImg[i][j] != img[i][j]){
// 				printf("ALERTA DE ERRO");
// 				break;
// 			}
// 			else printf("all good ");
// 		}
// 		printf("\n");
// 	}
// 	printf("\n\n");
	


// 	for(i = 0; i < h; i++) {
// 		free(newImg[i]);
// 		free(img[i]);
// 	}
// 	for(i = 0; i < n_vet; i++){
// 		free(vet[i]);
// 	}
// 	free(newImg);
// 	free(img);	
// 	free(vet);
// 	return 0;
// }