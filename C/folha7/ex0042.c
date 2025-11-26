#include <stdio.h>
#include <string.h>
#define TOT 3 
#define MAXC 31

struct produto{
    int qtd;
    float preco;
    char nome[MAXC];
}; 
typedef struct produto Tpro;

void leitura(Tpro v[]){
    for(int i = 0; i < TOT; i++){
        printf("Digite nome, preço e quantidade: ");
        scanf(" %[^\n]%f%d", v[i].nome, &v[i].preco, &v[i].qtd);
    }
}

int busca(Tpro v[], char elemproc[]) 
{
    for(int i = 0; i < TOT; i++){
        if(strcmp(v[i].nome, elemproc) == 0)
            return i;
    }
    return -1;
}

int main(){
    Tpro v[TOT];
    int pos;
    char nomepesq[MAXC];

    leitura(v);

    printf("Digite o nome ou fim: ");
    scanf(" %[^\n]", nomepesq); //folha de cola as 4 linhas

    while(strcmp(nomepesq, "Fim") != 0){
        pos = busca(v, nomepesq);
        if(pos == -1)
            printf("\nProduto não encontrado");
        else{
            printf("\nPreco: %.2f", v[pos].preco);
            printf("\nPreco: %d", v[pos].qtd);
        }
        printf("Digite o nome ou Fim: ");
        scanf(" %[^\n]", nomepesq);
    }

    return 0;
}