#include <stdio.h>
#define TOT 11

struct depto{
    int soma, qtd
};
typedef struct depto Tdepto;

void inicializa(Tdepto v[]){
    for(int i = 0; i < TOT; i++){
        v[i].soma = 0;
        v[i].qtd = 0;
    }
}

void exibe(Tfunc v[]){
    float media;

    for(int i = 0; i < TOT; i++){
        if(v[i].qtd != 0)
            media = (float)v[i].soma / v[i].qtd;
        else
            media = 0;
        printf("\nDepartamento %d: %.2f", i+10, media);
    }
}

int main(){
    Tdepto v[TOT];
    int cont, matr, dep, idade, qtd;
    char sexo;

    inicializa(v);

    printf("Digite quantidade funcionarios: ");
    scanf("%d", &qtd);

    for(cont = 0; cont < qtd; cont++){
        printf("Digite matrícula, departamento, idade e sexo: ");
        scanf("%d%d%d %c", &matr, &dep, &idade, &sexo);

        if(sexo == 'F'){
            v[dep - 10].soma += idade;
            v[dep - 10].qtd++;
        }
    }

    exibe(v);

    return 0;
}