#include <stdio.h>
#define MAX 3

struct produto{
    int codigo, qtd;
    float preco;
};
typedef struct produto produto;

void leitura(produto produto[]){
    for(int i = 0; i < MAX; i++){
        printf("Digite o código, o preço e a quantidade do produto: ");
        scanf("%d%f%d", &produto[i].codigo, &produto[i].preco, &produto[i].qtd);
    }
}

int busca(produto produto[], int procura){
    for(int i = 0; i < MAX; i++){
        if(produto[i].codigo == procura)
            return i;
    }
    return -1;
}

int main(){
    produto produtos[MAX];
    int procura, resultado;

    leitura(produtos);

    printf("Informe o código do produto a ser pesquisado (0 para encerrar): ");
    scanf("%d", &procura);

    while(procura != 0){
        resultado = busca(produtos, procura);
        if(resultado == -1) //melhor começar por -1
            printf("Produto não encontrado\n");
        else
            printf("Preço do produto: %.2f\t Quantidade em estoque: %d\n", produtos[resultado].preco, produtos[resultado].qtd);

        printf("Informe o código do produto a ser pesquisado (0 para encerrar): ");
        scanf("%d", &procura);
    }

    return 0;
}