
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

struct indiceCep {
    char cep[8];
    long posicao;
};

typedef struct indiceCep IndiceCep;

int compara(const void *a, const void *b) {
    return strncmp(
        ((IndiceCep*)a)->cep,
        ((IndiceCep*)b)->cep,
        8
    );
}

int main(int argc, char **argv) {
    FILE *arquivo;
    Endereco e;
    IndiceCep *indice;

    long tamanho, registros;
    long i;

    if(argc != 3) {
        fprintf(stderr, "USO: %s [ARQUIVO] [CEP]\n", argv[0]);
        return 1;
    }

    arquivo = fopen(argv[1], "rb");

    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    fseek(arquivo, 0, SEEK_END);

    tamanho = ftell(arquivo);
    registros = tamanho / sizeof(Endereco);

    indice = malloc(registros * sizeof(IndiceCep));

    if(indice == NULL && registros > 0) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        fclose(arquivo);
        return 1;
    }

    rewind(arquivo);

    for(i = 0; i < registros; i++) {
        fread(&e, sizeof(Endereco), 1, arquivo);

        strncpy(indice[i].cep, e.cep, 8);
        indice[i].posicao = i;
    }

    qsort(indice, registros, sizeof(IndiceCep), compara);

    long inicio = 0;
    long fim = registros - 1;

    int achou = 0;

    while(inicio <= fim) {
        long meio = (inicio + fim) / 2;

        int resultado = strncmp(argv[2], indice[meio].cep, 8);

        if(resultado == 0) {
            long posicao = indice[meio].posicao;

            fseek(arquivo, posicao * sizeof(Endereco), SEEK_SET);
            fread(&e, sizeof(Endereco), 1, arquivo);

            printf("Achou na posição %ld\n", posicao);

            printf(
                "%.72s\n"
                "%.72s\n"
                "%.72s\n"
                "%.72s\n"
                "%.2s\n"
                "%.8s\n",
                e.logradouro,
                e.bairro,
                e.cidade,
                e.uf,
                e.sigla,
                e.cep
            );

            achou = 1;
            break;

        } else if(resultado > 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if(achou == 0) {
        printf("Não achou.\n");
    }

    free(indice);
    fclose(arquivo);

    return 0;
}
