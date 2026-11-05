#include <stdio.h>

#define MAX 256

int main(int argc, char** argv){
    FILE *entrada;
    int c;
    int total = 0;
    int count[MAX] = {0};

    if(argc != 2){
        fprintf(stderr,"Erro na chamada do comando.\n");
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1],"rb");

    if(!entrada){
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    c = fgetc(entrada);

    while(c != EOF){
        count[c]++;
        total++;
        c = fgetc(entrada);
    }

    for(int i = 0; i < MAX; i++){
        printf("%d: %d\n", i, count[i]);
    }

    printf("Total de impressões: %d\n", total);

    fclose(entrada);
    return 0;
}