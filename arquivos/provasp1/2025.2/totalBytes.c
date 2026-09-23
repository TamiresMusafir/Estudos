#include <stdio.h>

struct COVID{
    int dia;
    int novos_casos;
    int obitos;
};

typedef struct COVID COVID;

main(){
    FILE *f = fopen("covid.dat", "rb");

    if(!f){
        fprintf(stderr, "Não foi possível abrir o arquivo %s.\n", "covid.dat");
        return 1;
    }
    
    fseek(f, 0, SEEK_END);
    long tamanhoBytes = ftell(f);
    long totalRegistros = tamanhoBytes / sizeof(COVID);

    printf("Tamanho total de bytes: %ld", tamanhoBytes);
    printf("Total de registros: %ld", totalRegistros);

    fclose(f);

    return 0;
}