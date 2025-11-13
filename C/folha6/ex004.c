#include <stdio.h>

struct depto{
    int qtd;
    float soma;
};
typedef struct depto Tdepto

void calculaSalario(Tdepto departamentos[]){
    float media;

    printf("Departamento\tSalario Médio");
    for(int i = 0; i < 30; i++){
        if(departamentos[] != 0){
            media = departamentos[i].soma / departamentos[i].qtd;
        }else{
            media = 0;
        }
        printf("Departamento %d: média: %.2f\n", i + 1, media);
    }
}
