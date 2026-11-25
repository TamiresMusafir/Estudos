// Crie o programa binaria que recebe o arquivo ordenado (o ord.dat do E13) e um CEP, e faz a busca binária com fseek + fread a cada tentativa. Imprima achou no indice I, leituras L ou nao achou, leituras L.

#include <stdio.h>
#include <string.h>

struct _Endereco{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; 
};

typedef struct _Endereco Endereco;

int main(int argc, char **argv){
    FILE *arquivo;
    Endereco e;
    
    if(argc != 3){
		fprintf(stderr, "USO: %s [ARQUIVO] [CEP]", argv[0]);
		return 1;
	}

    arquivo = fopen(argv[1], "rb");

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    long registros = tamanho / sizeof(Endereco);
    long inicio = 0;
    long fim = registros - 1;

    rewind(arquivo);

    int leituras = 0;
    int achou = 0;

    while(inicio <= fim){
        long meio = (inicio+fim) / 2;
        leituras++;
        fseek(arquivo, meio * sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, arquivo);

        if(strncmp(argv[2],e.cep,8)==0){
            printf("Achou no índice %ld - leituras: %d", meio, leituras);
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            achou = 1;
			break;
		} else if(strncmp(argv[2],e.cep,8) > 0) {
            inicio = meio + 1;
        }else{
            fim = meio -1;
        }	
    }

    if(achou == 0)
        printf("Não achou. Leituras realizadas: %d", leituras);

    fclose(arquivo);
    return 0;

}
