#include <stdio.h>
#include <string.h>
#define TOT 3
#define MAX 31

struct produto{
    int qtd;
    float preco;
    char nome[MAX];
};
typedef struct produto produto;

void leitura(produto produtos[]){
    for(int i = 0; i < TOT; i++){
        printf("Digite o nome, a quantidade e o preço: ");
        scanf(" %[^\n]%d%f", produtos[i].nome, &produtos[i].qtd, &produtos[i].preco);
    }
}

int busca(produto produtos[], char procura[]){
    for(int i = 0; i < TOT; i++){
        if(strcmp(procura, produtos[i].nome) == 0) //folha
            return i;
    }
    return -1;
}

int main(){
    char procura[MAX];
    produto produtos[TOT];
    int resultado;

    leitura(produtos);

    printf("Digite o nome do produto a ser procurado (Fim para encerrar): ");
    scanf(" %[^\n]", procura);

    while(strcmp(procura, "Fim") != 0){ //folha
        resultado = busca(produtos, procura);

        if(resultado == -1)
            printf("Produto não encontrado\n");
        else{
            printf("Preço: %.2f\t Quantidade: %d", produtos[resultado].preco, produtos[resultado].qtd);
        }
        
        printf("\nDigite o nome do produto a ser procurado (Fim para encerrar): \n");
        scanf(" %[^\n]", procura); // folha. Não usa &
    }

    return 0;
}

/*erros para folha de cola:

1 - Se é um vetor de char, não colocar & no scanf, pois um vetor já um ponteiro;
2 - "Fim" ao invés de 'Fim', pois 'Fim' é um caracter único*/