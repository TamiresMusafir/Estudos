#include <stdio.h>
#define MAX 50

void inicializa(int registro[], int qtd){
    for(int i = 0; i < qtd; i++)
        registro[i] = 0;
}

void exibe(int registro[], int qtd){
    for(int i = 0; i < qtd; i++)
        printf("Quarto %d foi ocupado %d vezes\n", i + 1, registro[i]);
}

int main(){
    int quarto;
    int registro[MAX];

    inicializa(registro, MAX);

    printf("Digite um quarto (0 para encerrar): \n");
    scanf("%d", &quarto);

    while(quarto != 0){
        registro[quarto - 1]++;

        printf("Digite um quarto (0 para encerrar): \n");
        scanf("%d", &quarto);
    }

    exibe(registro, MAX);

    return 0;
}