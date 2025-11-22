/*Um banco possui as seguintes informações dos seus clientes: número da conta do cliente e saldo do cliente.
Faça um programa, utilizando a função abaixo, que leia os dados dos clientes e exiba para cada cliente o
número da conta, o saldo do cliente e uma mensagem informando se o saldo dele está acima do saldo médio
dos clientes do banco, abaixo do saldo médio dos clientes do banco ou se é igual ao saldo médio dos clientes
do banco. Término da leitura: número da conta do cliente = 0. Considere que o banco possui, no máximo,
10573 clientes. O seu programa deverá utilizar a função abaixo.
a) leitura: recebe como parâmetro um vetor de struct a ser preenchido, lê os dados de cada cliente,
armazenando no vetor. Esta função irá retornar a quantidade de clientes do banco. Irá também calcular
o saldo médio dos clientes do banco armazenando-o na variável cujo endereço é fornecido na chamada
da função.*/

#include <stdio.h>

#define MAX 10573

struct clientes {
    int conta;
    float saldo;
};
typedef struct clientes clientes;

int leitura(clientes clientes[], float *media){
    float saldo = 0;
    int i = 0;
    int conta;

    printf("\nCliente %d\n", i+1);

    printf("Digite o número da conta: \n");
    scanf("%d", &conta);

    while(conta != 0 && i < MAX){
       
        clientes[i].conta = conta; // atribuição correta

        printf("Digite o saldo: \n");
        scanf("%f", &clientes[i].saldo);

        saldo += clientes[i].saldo;
        i++;

        printf("\nCliente %d\n", i+1);

        printf("Digite o número da conta: \n");
        scanf("%d", &conta);
    }

    *media = saldo / i;

    return i;
}

int main(){
    int qtd;
    float media;
    clientes clientes[MAX];

    qtd = leitura(clientes, &media);

    printf("Média: %.2f", media);

    for(int i = 0; i < qtd; i++){
        printf("\nCliente: %d\tConta: %d\tSaldo: %.2f\n", i+1, clientes[i].conta, clientes[i].saldo);

        if(clientes[i].saldo < media)
            printf("\nO saldo está abaixo da média\n");
        else if(clientes[i].saldo == media)
            printf("\nO saldo está na média\n");
        else
            printf("\nO saldo está acima da média\n");
    }

    return 0;
}