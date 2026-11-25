//Crie a função long buscaSequencial(FILE *f, char *cep, long *lidos), que devolve a posição do registro (começando em 0) ou -1 se não achar, e guarda em *lidos quantos registros foram lidos. Crie o programa sequencial que a usa e imprime achou na posicao P, lidos L ou nao achou, lidos L.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Endereco{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

typedef struct Endereco Endereco;

long buscaSequencial(FILE *f, char *cep, long *lidos){
    Endereco registro;
    long pos = -1;

    while(fread(&registro, sizeof(Endereco), 1, f) == 1){
        (*lidos)++;
        pos++;

        if(strncmp(cep, registro.cep, 8) == 0)
            return pos;
    }

    return -1;
}

int main(int argc, char** argv){
    FILE *arquivo;
    long lidos = 0;

    if(argc != 3){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM] [CEP].\n", argv[0]);
        return 1;
    }

    arquivo = fopen(argv[1], "rb");

    if(!arquivo){
        fprintf(stderr, "Não foi possível abrir o arquivo");
        return 1;
    }

    char *cep = argv[2]; 

    long pos = buscaSequencial(arquivo, cep, &lidos);

    if (pos == -1)
        printf("Não achou - Lidos: %ld.\n", lidos);
    else{
        printf("Achou na posição %ld - Lidos: %ld", pos, lidos);
    }

    fclose(arquivo);
    return 0;
}
