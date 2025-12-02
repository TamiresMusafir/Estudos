#include <stdio.h>
#define MAX 50

void inicializa(int registro[]){
    for(int i = 0; i < MAX; i++)
        registro[i] = 0;
}

void exibe(int registro[]){
    for(int i = 0; i < MAX; i++)
        printf("Quarto %d foi ocupado %d vezes\n", i + 1, registro[i]);
}

int main(){
    int quarto;
    int registro[MAX];

    inicializa(registro);

    printf("Digite um quarto (0 para encerrar): \n");
    scanf("%d", &quarto);

    while(quarto != 0){
        registro[quarto - 1]++; // folha

        printf("Digite um quarto (0 para encerrar): \n");
        scanf("%d", &quarto);
    }

    exibe(registro);

    return 0;
}
