#include <stdio.h>
#define TOT 1000 

struct produto{
    int cod, qtd;
    float preco;
}; 

typedef struct produto Tpro;

void leitura(Tpro v[]){
    for(int i = 0; i < TOT; i++){
        printf("Digite código, preço e quantidade: ");
        scanf("%d%f%d", &v[i].cod, &v[i].preco, &v[i].qtd);
    }
}

int busca(Tpro v[], int elemproc) //nao recebe qtd como parâmetro pq é exatamente 1000
{
    for(int i = 0; i < TOT; i++){
        if(v[i].cod == elemproc)
            return i;
    }
    return -1;
}

int main(){
    Tpro v[TOT];
    int codpesq, pos;

    leitura(v);

    printf("Digite o código ou 0: ");
    scanf("%d", &codpesq);

    while(codpesq != 0){
        pos = busca(v, codpesq);
        if(pos == -1)
            printf("\nProduto não encontrado");
        else{
            printf("\nPreco: %.2f", v[pos].preco);
            printf("\nQuantidade: %d", v[pos].qtd);
        }
        printf("Digite o código ou 0: ");
        scanf("%d", &codpesq);
    }

    return 0;
}