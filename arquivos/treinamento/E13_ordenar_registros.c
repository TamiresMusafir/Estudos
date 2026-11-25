// Crie o programa ordena que lê o arquivo inteiro com malloc e fread, ordena pelo CEP com qsort e grava o resultado em outro arquivo. Lembre: o compara faz cast para Endereco*, e o sizeof do qsort é o do Endereco.

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

int compara(const void *e1, const void *e2){
    return strncmp(
        ((Endereco*)e1)->cep,
        ((Endereco*)e2)->cep,
        8
    );
}

int main(int argc, char** argv){
    FILE *entrada, *saida;
    Endereco *e;
    
    if(argc != 3){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM] [ARQUIVO SAIDA].\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");

    if(!entrada){
        fprintf(stderr, "Não foi possível abrir o arquivo");
        return 1;
    }

    saida = fopen(argv[2], "wb");

    if(!saida){
        fprintf(stderr, "Não foi possível abrir o arquivo");
        fclose(entrada);
        return 1;
    }

    fseek(entrada, 0, SEEK_END);

    long qtd = ftell(entrada);
    long registros = qtd / sizeof(Endereco);

    rewind(entrada);

    e = malloc(registros * sizeof(Endereco));

    if(e == NULL && registros > 0){
        fprintf(stderr, "Erro ao alocar memória");
        fclose(entrada);
        fclose(saida);
        return 1;
    }

    if(registros > 0){
        printf("Memória alocada com sucesso!\n");

        fread(e, sizeof(Endereco), registros, entrada);
        qsort(e, registros, sizeof(Endereco), compara);
        fwrite(e, sizeof(Endereco), registros, saida);

        fclose(entrada);
        fclose(saida);
        free(e);

        return 0;
    }
    
}
