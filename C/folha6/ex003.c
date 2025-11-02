#include <stdio.h>

int maiorNumeros(float numeros[ ], int qtd, float media){
    int maior = 0;

    for(int i = 0; i < qtd; i++){
        if(numeros[i] > media)
            maior++;
    }

    return maior;
}