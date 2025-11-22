/*Faça um programa, utilizando as funções abaixo, que inicialmente leia a quantidade de funcionários de uma
empresa. Para cada funcionário, o programa deverá ler a matrícula, o código do departamento no qual ele
trabalha (número inteiro de 10 a 20) e a idade. O programa deverá exibir a idade média dos funcionários de
cada departamento. Faça as seguintes funções:
a) inicializa: recebe como parâmetro um vetor de struct e inicializa-o apropriadamente.
b) exibe: recebe como parâmetro um vetor de struct já preenchido e exiba para cada departamento o seu
código e a idade média dos funcionários.*/

#include <stdio.h>

#define MAX 11

struct departamento{
    int soma;
    int qtd;
};
typedef struct departamento departamento;

void inicializa(departamento departamentos[]){
    for(int i = 0; i < MAX; i++){
        departamentos[i].soma = 0;
        departamentos[i].qtd = 0;
    }
}

void exibe(departamento departamentos[]){
    float media;
    int codigo;

    for(int i = 0; i < MAX; i++){
        codigo = i + 10; 

        if(departamentos[i].qtd != 0)
            media = (float)departamentos[i].soma / departamentos[i].qtd;
        else
            media = 0;
        printf("Departamento: %d\tIdade média dos funcionários: %.2f", codigo, media);
    }
}

int main(){
    departamento departamentos[MAX];
    int qtd, matricula, idade, codigo;

    inicializa(departamentos);

    printf("Digite a quantidade de funcionários da empresa: \n");
    scanf("%d", &qtd);

    for(int i = 0; i < qtd; i++){
        printf("\nFuncionário: %d - digite a matrícula, o departamento e a idade: \n", i+1);
        scanf("%d%d%d", &matricula, %codigo, &idade);

        int indice = codigo - 10;

        departamentos[indice].soma += idade;
        departamentos[indice].qtd++;
    }

    exibe(departamentos);

    return 0;
}