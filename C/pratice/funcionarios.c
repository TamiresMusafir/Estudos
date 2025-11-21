/* Faça um programa, utilizando as funções abaixo, para processar os 500 funcionários de uma empresa. Para
cada funcionário, o programa deverá ler o código do departamento no qual ele trabalha (número inteiro de
1 a 10). O programa deverá exibir a quantidade de funcionários de cada departamento. Faça as seguintes
funções:
a) inicializa: recebe como parâmetro um vetor de números inteiros e inicializa-o apropriadamente.
b) exibe: recebe como parâmetro um vetor de números inteiros já preenchido e exibe a quantidade de
funcionários de cada departamento. */

#include <stdio.h>
#define MAX_FUNC 500
#define MAX_DEP 10

void inicializa(int funcionarios[]){
    for(int i = 0; i < MAX_DEP; i++)
        funcionarios[i] = 0;
}

void exibe(int funcionarios[]){
    for(int i = 0; i < MAX_DEP; i++){
        printf("Quantidade de funcionários em cada departamento:");
        printf("\nDepartamento %d: %d\n", i + i, funcionarios[i]);
    }
}

int main(){
    int departamento;
    int funcionarios[MAX_DEP];
    
    inicializa(funcionarios);

    for(int i = 0; i < MAX_FUNC; i++){
        printf("Digite o departamento do funcionário %d: \n", i+1);
        scanf("%d", &departamento);

        funcionarios[departamento - 1]++;
    }

    exibe(funcionarios);

    return 0;
}
