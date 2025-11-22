/*Faça um programa, utilizando as funções abaixo, que inicialmente leia a quantidade de funcionários de uma
empresa. Para cada funcionário, o programa deverá ler a matrícula, o código do departamento no qual ele
trabalha (número inteiro de 10 a 20) e a idade. O programa deverá exibir a idade média dos funcionários de
cada departamento. Faça as seguintes funções:
a) inicializa: recebe como parâmetro um vetor de struct e inicializa-o apropriadamente.
b) exibe: recebe como parâmetro um vetor de struct já preenchido e exiba para cada departamento o seu
código e a idade média dos funcionários.*/

#include <stdio.h>

#define MAX 11

struct funcionarios{
    int soma;
    int qtd;
}

void inicializa()