#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARTES 8

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
    return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}

void intercala(char *arqA, char *arqB, char *arqSaida){
    FILE *a, *b, *saida;
    Endereco ea, eb;

    a = fopen(arqA, "rb");
    b = fopen(arqB, "rb");
    saida = fopen(arqSaida, "wb");

    if(!a || !b || !saida){
        fprintf(stderr, "Arquivo nao pode ser aberto.\n");
        return;
    }

    fread(&ea, sizeof(Endereco), 1, a);
    fread(&eb, sizeof(Endereco), 1, b);

    while(!feof(a) && !feof(b)){
        if(compara(&ea, &eb)<0){
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, a);
        }else{
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, b);
        }
    }

    while(!feof(a)){
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread(&ea, sizeof(Endereco), 1, a);
    }

    while(!feof(b)){
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread(&eb, sizeof(Endereco), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}

int main(int argc, char **argv){
    FILE *cep;
    Endereco *e;
    char nome[20];

    cep = fopen("cep.dat", "rb");
    fseek(cep, 0, SEEK_END);
    long tamanho = ftell(cep);
    long quantidade =  tamanho / sizeof(Endereco);     

    long divisao = quantidade / PARTES;
    long resto = quantidade % PARTES;

    rewind(cep);

    e = (Endereco*) malloc((divisao + 1)*sizeof(Endereco));

    for(int i = 0; i < PARTES; i++){
        long quantidadeParte = divisao;;

        if(i < resto){
            quantidadeParte++;
        }

        fread(e, sizeof(Endereco), quantidadeParte, cep);
        qsort(e, quantidadeParte, sizeof(Endereco), compara);
        sprintf(nome, "cep_%d.dat", i);

        FILE *parte = fopen(nome, "wb");
        fwrite(e, sizeof(Endereco), quantidadeParte, parte);

        fclose(parte);
    }

    int arquivoNome = PARTES;

    for(int i = 0; i < (PARTES-1)*2; i+=2){
        char nome1[20];
        char nome2[20];
        char nome3[20];

        sprintf(nome1, "cep_%d.dat", i);
        sprintf(nome2, "cep_%d.dat", i+1);
        sprintf(nome3, "cep_%d.dat", arquivoNome);

        intercala(nome1, nome2, nome3);
        arquivoNome++;
    }

    free(e);
}
