#include <stdio.h>

// stdout, stdin, stderr

int main(int argc, char** argv){
	FILE *entrada;
	int c, count;

	if(argc != 2){
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1],"rb");
	
	if(!entrada){
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	c = fgetc(entrada);

	while(c != EOF){
		if (c=='\n')
			count++;
		c = fgetc(entrada);
	}

	printf("quantidade de linhas: %d", count);

	fclose(entrada);
	return 0;
}