# Projeto: Compressão de Imagens

## **TO DO**:
 - Implementar Quantização/Desquantização;
 - Implementar vetorização e enconding/decoding(Run-Length ou Diferencial);
 - Implementar Alg. Compressão/Descompressão(Huffman?);

## **DONE**:
 - Implementar separação em 8x8;
 - Implementar DCT / IDCT;
 - Encapsular melhor cada grupo de funções;

## Como Rodar
	make
	./BMP_compressor ./PATH TO THE IMAGE

## Objetivos

O objetivo principal do projeto é colocar em prática conceitos teóricos abordados em sala de aula relacionados   a   técnicas   de   codificação   de   mídias.   Para   isso,   os   grupos   deverão   implementar   algumastécnicas de compressão e descompressão – a saber.
Cada grupo deverá desenvolver um compressor para imagens e seu respectivo descompressor. Ocompressor deve aceitar como entrada uma imagem (segundo modelo abaixo). Como saída o compressor deve gerar um arquivo binário que represente a imagem de modo comprimido e a taxa de compressão atingida.
O descompressor deve receber como entrada  um arquivo binário  armazenado  em disco, o qual deve   ter   sido   produzido   pelo   correspondente   compressor.   Como   saída,   o   descompressor   produz   uma imagem com qualidade similar à imagem original.
As técnicas de compressão a serem desenvolvidas são, no mínimo: compressão com perdas com autilização de transformada DCT e compressão sem perdas utilizando codificação diferencial.	


## Importante

1. Somente os bits que representam cada código gerado devem ser gravados no arquivo binário desaída;
2. O projeto deve apresentar implementações funcionais para Compressor e Descompressor;
3. O compressor e o descompressor devem se encontram em módulos diferentes e devidamente implementado como programas;
4. A   implementação   das   técnicas   deverá   primar   pela   busca   da   maior   taxa   de   compressão   commelhor qualidade possível;


## Modelo da Imagem
- Arquivos BMP, sem compressão;
- 24 bits para cor
- Altura e largura sempre múltiplos de 8
- Dimensões **mínimas**: 8 x 8 pixels
- Dimensões **máximas**: 1280 x 800 pixels
- Se a imagem utilizada como entrada para o compressor não atender os critérios acima, a compressão não deve ser feita, exibindo ao usuário o motivo.

### Estruturas para Bitmap


	typedef struct 						/**** BMP file header structure ****/    
	{
		unsigned short bfType;			/* Magic number for file */ 
		unsigned int   bfSize;			/* Size of file */ 
		unsigned short bfReserved1;		/* Reserved */
		unsigned short bfReserved2;		/* ... */
		unsigned int   bfOffBits;		/* Offset to bitmap data */
		} BMPFILEHEADER;
										/* bfType deve ser = "MB" */



	typedef struct  /**** BMP file info structure ****/
	{
		unsigned int   biSize;			/* Size of info header */
		int 	 	   biWidth;    		/* Width of image */
		int   		   biHeight;   		/* Height of image */
		unsigned short biPlanes;		/* Number of color planes */
		unsigned short biBitCount;		/* Number of bits per pixel */
		unsigned int   biCompression;	/* Type of compression to use */
		unsigned int   biSizeImage;		/* Size of image data */
		int            biXPelsPerMeter;	/* X pixels per meter */ 
		int            biYPelsPerMeter;	/* Y pixels per meter */
		unsigned int   biClrUsed;		/* Number of colors used */
		unsigned int   biClrImportant;	/* Number of important colors */
	} BMPINFOHEADER;


### Leitura de Bitmap

	void leituraHeader(FILE *F, BITMAPFILEHEADER *H){
		/* F é o arquivo Bitmap que deve ter sido “lido” do disco */
		fread(&H->Type,sizeof (unsigned short int),1,F);
		fread(&H->Size,sizeof (unsigned int),1,F);
		fread(&H->Reserved1,sizeof (unsigned short int),1,F);
		fread(&H->Reserved2,sizeof (unsigned short int),1,F); 
		fread(&H->OffBits,sizeof (unsigned int),1,F);
	}


### Links Úteis:
 - [Compressão de BMP utilizando Huffman](https://www.geeksforgeeks.org/image-compression-using-huffman-coding/)
 - [Descrição de arquivos BMP](http://paulbourke.net/dataformats/bmp/)
 - [Aula com Informações sobre o processo JPEG](https://ae4.tidia-ae.usp.br/access/content/group/d06ef1d7-9569-4321-91f3-7e9a644c6e50/Slides%20das%20Aulas/aula_jpeg.pdf)
 - [Artigo da Wikipedia sobre JPEG](https://en.wikipedia.org/wiki/JPEG)
