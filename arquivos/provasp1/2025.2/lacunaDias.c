#include <stdio.h>

struct COVID{
    int dia;
    int novos_casos;
    int obitos;
};

typedef struct COVID COVID;

int main(){
    int count = 0;

    FILE *f = fopen("casos.dat", "rb");

    if(!f){
        fprintf(stderr, "Não foi possível abrir o arquivo %s.\n", "covid.dat");
        return 1;
    }

    COVID c;

    while(fread(&c, sizeof(COVID), 1, f) == 1){
        if(c.dia == count)
            count++;
        else{
            printf("Lacuna encontrada no dia %d", count);
            count++;
        }
    }
}