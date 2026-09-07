#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;
struct _Endereco{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

struct indiceCep{
    char cep[8];
    long posicao;
};

typedef struct indiceCep IndiceCep;

int compara(const void *a, const void *b){
    return strncmp(
        ((IndiceCep*)a)->cep,
        ((IndiceCep*)b)->cep,
        8
    );
}

int main(int argc, char **argv){
    FILE *f;
    Endereco e;
    IndiceCep *indice;

    long tamanhoBytes, qtd, i;

    if(argc != 2){
        fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
        return 1;
    }

    f = fopen("cep.dat", "rb");

    if(f == NULL){
        fprintf(stderr, "Erro ao abrir cep.dat\n");
        return 1;
    }

    fseek(f, 0, SEEK_END);

    tamanhoBytes = ftell(f);

    qtd = tamanhoBytes / sizeof(Endereco);

    indice = malloc(qtd * sizeof(IndiceCep));

    if(indice == NULL){
        fprintf(stderr, "Erro ao alocar memoria\n");
        fclose(f);
        return 1;
    }

    rewind(f);

    for(i = 0; i < qtd; i++){
        fread(&e, sizeof(Endereco), 1, f);
        strncpy(indice[i].cep, e.cep, 8);
        indice[i].posicao = i;
    }

    qsort(indice, qtd, sizeof(IndiceCep), compara);

    long inicio = 0;
    long fim = qtd - 1;

    while(inicio <= fim){
        long meio = (inicio + fim) / 2;
        int resultado = strncmp(argv[1], indice[meio].cep, 8);

        if(resultado == 0){
            long posicao = indice[meio].posicao;

            fseek(f, posicao * sizeof(Endereco), SEEK_SET);
            fread(&e, sizeof(Endereco), 1, f);

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

            break;
        }else if(resultado > 0){
            inicio = meio + 1;
        }else{
            fim = meio - 1;
        }
    }

    free(indice);
    fclose(f);

    return 0;
}