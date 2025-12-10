#include <stdio.h>

#define CLIENTES 20
#define PRODUTOS 10

int satisfeitos(servicos[][PRODUTOS]){
    int total = 0;

    for(int i = 0; i < CLIENTES; i++){
        int soma = 0;
        for(int k = 0; k < PRODUTOS; k++){
            if(servicos[i][k] == 4 || servicos[i][k] == 5)
                soma++;  
        }
        if(soma > 5)
            total++;
    }

    return total;
}

void imprime(servicos[][PRODUTOS]){
    int maior = -1;

    for(int k = 0; k < PRODUTOS; k++){
        int soma = 0;
        for(int i = 0; i < CLIENTES; i++)[
            if(servicos[i][k] == 1 || servicos[i][k] == 2)
                soma++;  
        ]
        if(soma > maior){
            maior = soma;
        }
    }

    for(int k = 0; k < PRODUTOS; k++){
        int soma = 0;
        for(int i = 0; i < CLIENTES; i++){
            if(servicos[i][k] == 1 || servicos[i][k] == 2)
                soma++; 
        }
        if(soma == maior)
            printf("O produto %d possui muitas avaliações insatisfeitas", k);
    }
}

void media(servicos[][PRODUTOS]){
    float media = 0;

    for(int k = 0; k < PRODUTOS; k++){
        int soma = 0;
        for(int i = 0; i < CLIENTES; i++){
            soma += servicos[i][k];
        }
        media = (float)soma / CLIENTES;
        printf("O produto %d possui média %.2f", k + 1, media);
    }
}

void imprime(servicos[][PRODUTOS], int questao){
    int total =  0;

    for(int i = 0; i < CLIENTES; i++){
        if(servicos[i][questao-1] == 5)
            total++;
    }
    printf("%d clientes atribuíram nota máxima ao produto %d", total, questao);
}

int main(){

    for(int = 0; )

   
}