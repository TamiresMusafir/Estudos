#include <stdio.h>

void exibe(int qtdVendida[4][31], float precos[4][31]){
    float total;

    for(int i = 0; i < 4; i++){
        total = 0; //inicializar sempre
        for(int k = 0; k < 31; k++){
            total += qtdVendida[i][k] * precos[i][k];
        }
        printf("Combustível %d: %.2f vendas no mês.", i + 1, total);
    }

    for(int k = 0; k < 31; k++){
        total = 0;
        for(int i = 0; i < 31; i++){
            total += qtdVendida[i][k] * precos[i][k]
        }
        printf("Valor das vendas do dia %d: %.2f", k + 1, total);
    }
}