#include <stdio.h>
#define MAX 1000

struct produtos{
    int codigo, qtd;
    float preco;
};
typedef struct produtos produtos;

void leitura(produtos produto[]){
    for(int i = 0; i < MAX; i++){
        printf("Digite o código, o preço e a quantidade do produto: ");
        scanf("%d%f%d", &produto[i].codigo, &produto[i].preco, &produto[i].qtd);
    }
}

int busca(produtos produto[], int procura){
    for(int i = 0; i < MAX; i++){
        if(produto[i].codigo == procura)
            return i;
    }
    return -1;
}

int main(){
    produtos produto[MAX];
    int procura, resultado;

    leitura();

    printf("Informe o código do produto a ser pesquisado (0 para encerrar): ");
    scanf("%d", &procura);

    while(procura != 0){
        resultado = busca(produto, procura);
        if(resultado == procura)
            printf("Preço do produto: %f\tQuantidade em estoque: %d", produto[resultado].preco, produto[resultado].qtd);
        else
            printf("Produto não encontrado");

        printf("Informe o código do produto a ser pesquisado (0 para encerrar): ");
        scanf("%d", &procura);
    }

    return 0;
}