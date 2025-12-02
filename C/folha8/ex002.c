//Faça uma função que receba como parâmetro uma matriz 6 x 12 de inteiros, já preenchida, contendo a quantidade mensal vendida do carro Gol nos anos 2010 a 2015. A função deverá exibir o valor total das vendas em cada mês, ou seja, a soma de cada coluna).

#include <stdio.h>

void exibe(int qtdmensal[6][12]){
    float total = 0;

    for(int k = 0; k < 12; k++){
        int soma = 0;
        for(int i = 0; i < 6; i++){
            soma += qtdmensal[i][k];
        }
        printf("Total do mês %d: %.2f", k + 1, soma);
    }
}