#include <stdio.h>

int main(int argc, char** argv){
    FILE *entrada;
    int c;
    int contador[256] = {0};

    if(argc != 2){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");

    if(!entrada){
        fprintf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    c = fgetc(entrada);

    while(c != EOF){
        contador[c]++;
        c = fgetc(entrada);
    }

    for(int i = 0; i < 256; i++){
        if(contador[i] > 0){
            printf("%c: %d\n", i, contador[i]);
        }
    }

    fclose(entrada);

    return 0;
}