#include <stdio.h>
#include <stdbool.h>

typedef struct {
    long chave;
    char dados[1000];
} Registro;

void* openTree(const char* nomeArquivo);
bool findKey(void* tree, long key, long* offset);
void insertKey(void* tree, long key, long offset);
void closeTree(void* tree);

// LETRA A
void indexaArquivo(const char *arquivoDados, const char *arquivoIndice){
    FILE *dados = fopen(arquivoDados, "rb");
    Registro r;
    
    if(!dados){
        fprintf(stderr, "Não foi possível abrir o arquivo de dados");
        return;
    }

    void *tree = openTree(arquivoIndice);

    if(tree == NULL){
        fclose(dados);
        return;
    }

    long offset = ftell(dados);

    while(fread(&r, sizeof(Registro), 1, dados) == 1){        
        insertKey(tree, r.chave, offset);
        offset = ftell(dados);
    }

    closeTree(tree);
    fclose(dados);
}

// LETRA B
void imprimeDados(const char *arquivoDados, const char *arquivoIndice, long chave){
    FILE *dados = fopen(arquivoDados, "rb");
    Registro r;

    if(!dados){
        fprintf(stderr, "Não foi possível abrir o arquivo de dados");
        return;
    }

    void *tree = openTree(arquivoIndice);

    if(tree == NULL){
        fclose(dados);
        return;
    }

    long offset;

    bool achou = findKey(tree, chave, &offset);

    if(!achou){
        printf("Chave não encontrada");
        fclose(dados);
        closeTree(tree);
        return;
    }

    fseek(dados, offset, SEEK_SET);

    fread(&r, sizeof(Registro), 1, dados);

    printf("%s\n", r.dados);

    fclose(dados);
    closeTree(tree);
}

//LETRA C
void diferencaArquivos(const char* arquivo1, const char* arquivo2, const char* indiceArquivo1, const char* arquivoSaida) {
    FILE *dados1 = fopen(arquivo1, "rb");
    Registro r1, r2;

    if(!dados1){
        fprintf(stderr, "Não foi possível abrir o arquivo de dados");
        return;
    }

    FILE *dados2 = fopen(arquivo2, "rb");

    if(!dados2){
        fprintf(stderr, "Não foi possível abrir o arquivo de dados");
        fclose(dados1);
        return;
    }

    void *tree = openTree(indiceArquivo1);

    if(tree == NULL){
        fclose(dados1);
        fclose(dados2);
        return;
    }

    FILE *dadoSaida = fopen(arquivoSaida, "wb");

    if(!dadoSaida){
        fprintf(stderr, "Não foi possível abrir o arquivo de dados");
        fclose(dados1);
        fclose(dados2);
        closeTree(tree);
        return;
    }

    long offset = ftell(dados1);

    while(fread(&r1, sizeof(Registro), 1, dados1) == 1){        
        insertKey(tree, r1.chave, offset);
        offset = ftell(dados1);
    }


    while(fread(&r2, sizeof(Registro), 1, dados2) == 1){
        bool achou = findKey(tree, r2.chave, &offset);

        if(!achou){
            fwrite(&r2, sizeof(Registro), 1, dadoSaida);
        }
    }

    fclose(dados1);
    fclose(dados2);
    fclose(dadoSaida);
    closeTree(tree);
}