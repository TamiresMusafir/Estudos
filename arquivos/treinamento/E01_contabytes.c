#include <stdio.h>

// Crie o programa contabytes que recebe um arquivo e imprime quantos bytes e quantas linhas ('\n') ele tem. Leia com fgetc.

#define MAX 256

int main(int argc, char** argv[]){
    FILE *entrada;
    int c;
    int contador[MAX] = {0};
    int totalLinhas = 0;
    int totalbytes = 0;
    
    if(argc != 2){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");

    if(!entrada){
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    c = fgetc(entrada);

    while(c != EOF){
        contador[c]++;
        totalbytes++;
        if(c == '\n')
            totalLinhas++;
        c = fgetc(entrada);
    }

    for(int i = 0; i < MAX; i++){
        if(i != '\n' && contador[i] > 0 )
            printf("%c: %d\n", i, contador[i]);
    }

    printf("Total de quebra de linhas: %d\n", totalLinhas);
    printf("Total de bytes presentes no arquivo: %d\n", totalbytes);

    fclose(entrada);

    return 0;
}
