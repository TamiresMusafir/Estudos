#include <stdio.h>
#define MAX 10573

struct cliente{
    int conta;
    float saldo;
};
typedef struct cliente Tcliente;

int leitura(Tcliente clientes[], float *media){
    int conta;
    float soma = 0;
    int i = 0;

    printf("Digite o número da conta (digite 0 para terminar): \n");
    scanf("%d", &conta); // varável normal para não guardar o 0;

    while(conta != 0 && i < MAX){
 
        clientes[i].conta = conta;
        printf("\nDigite o saldo: ");
        scanf("%f", &clientes[i].saldo);

        soma += clientes[i].saldo;
        i++;

        printf("Digite o número da conta (digite 0 para terminar): \n");
        scanf("%d", &conta);
    }

    *media = soma / i;

    return i;
}

int main(){
    Tcliente clientes[MAX];
    int qtd;
    float media;

    qtd = leitura(clientes, &media);

    printf("Média do saldo: %.2f\n", media);

    for(int i = 0; i < qtd; i++){
        printf("Cliente %d\n", i + 1);
        printf("Número da conta: %d\n", clientes[i].conta);
        printf("Saldo: %.2f\n", clientes[i].saldo);

        if(clientes[i].saldo > media)
            printf("O saldo está acima da média\n");
        else if(clientes[i].saldo == media)
            printf("O saldo está na média\n");
        else
            printf("O saldo está abaixo da média\n");
    }

    return 0;
}