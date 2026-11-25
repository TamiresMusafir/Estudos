#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long chave;
    char dados[1000];
} Registro;

void* openTree(const char* nomeArquivo);
bool findKey(void* tree, long key, long* offset);
void insertKey(void* tree, long key, long offset);
void closeTree(void* tree);

int constroiIndice(char *arquivoDados, char *arquivoIndice){
    FILE *dados = fopen(arquivoDados, "rb");
    Registro r;
    
    if(!dados){
        fprintf(stderr, "Não foi possível abrir o arquivo de dados");
        return 1;
    }

  
}
