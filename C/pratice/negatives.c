#include <stdio.h>
#define MAX 30

int produtoNegativo (int valor[], int qtd){
    int produto = 1;

    for(int i = 0; i < qtd; i++){
        if(valor[i] < 0)
            produto *= valor[i];
    }

    return produto;
}

int main (){
    int valor[MAX], qtd, i, produto;

    printf("Digite a quantidade de elementos (max %d): ", MAX);
    scanf("%d", &qtd);

    while(qtd <= 0 || qtd > MAX){
        printf("Quantidade inválida. Digite novamente: ");
        scanf("%d", &qtd);
    }

    for(i = 0; i < qtd; i++){
        printf("Digite o %dº: ", i + 1);
        scanf("%d", &valor[i]);
    }

    produto = produtoNegativo(valor, qtd);

    printf("O produto dos números negativo é: %d\n", produto);

    return 0;
}