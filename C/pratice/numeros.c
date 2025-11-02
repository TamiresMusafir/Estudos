#include <stdio.h>
#define MAX 30

void contaParImpar(int numeros[], int qtd, int *pares, int *impares){
    *pares = 0;
    *impares = 0;

    for(int i = 0; i < qtd; i++){
        if(numeros[i] % 2 == 0){
            (*pares)++;
        }else{
            (*impares)++;
        }
    }
}

int main(){
    int numeros[MAX], qtd, pares, impares, i;

    printf("Digite a quantidade de números (máx 30): ");
    scanf("%d", &qtd);

    while(qtd <= 0 || qtd > MAX){
        printf("Quantidade inválida. Digite novamente: ");
        scanf("%d", &qtd);
    }

    for(i = 0; i < qtd; i++){
        printf("Digite o %dº: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    contaParImpar(numeros, qtd, &pares, &impares);

    printf("Total de Pares: %d\n", pares);
    printf("Total de Ímpares: %d\n", impares);

    return 0;
}