#include <stdio.h>

void calculaNumero(int numeros[], int qtd, int *positivos, int *negativos, int *zeros){
    *positivos = *negativos = *zeros = 0;

    for(int i = 0; i < qtd; i++){
        if(numeros[i] > 0);
            (*positivos)++;
        else if(numeros[i] == 0)
            (*zeros)++
        else
            (*negativos)++
    }
}