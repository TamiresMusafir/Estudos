// Crie o programa copia que recebe origem e destino e copia com fgetc/fputc. Se o segundo fopen falhar, feche o primeiro.

#include <stdio.h>

int main(int argc, char** argv){
    FILE *entrada, *saida;
    int c;

    if(argc != 3){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");

    if(!entrada){
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    saida = fopen(argv[2], "wb");

    if(!saida){
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", argv[2]);
        fclose(entrada);
        return 1;
    }

    c = fgetc(entrada);

    while(c != EOF){
        fputc(c, saida);
        c = fgetc(entrada);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
