//Crie o programa ordena que lê o arquivo inteiro com malloc e fread, ordena pelo CEP com qsort e grava o resultado em outro arquivo. Lembre: o compara faz cast para Endereco*, e o sizeof do qsort é o do Endereco.

#include <stdio.h>

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

int compara(const void *e1, const void *e2){
    return strncmp(
        ((Endereco*)e1)->cep,
        ((Endereco*)e2)->cep,
        8
    );
}