#include <stdio.h>
#define MAX 30;

struct depto{
    int qtd;
    float soma;
};
typedef struct depto Tdepto

void calculaSalario(Tdepto departamentos[], Tdepto qtd){
    float media;

    for(int i = 0; i < qtd; i++){
        media = departamentos[i].soma / departamentos[i].qtd;

        printf("Departamento %d: média: %.2f\n", i + 1, media);
    }
}