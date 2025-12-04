#include <stdio.h>
#define MAX 10000

struct livro{
    int codigo, qtdexist, qtdemp;
};
typedef struct livro livro;

void ordena(livro livros[], int qtd){
    int k, i, min, aux; //colocar toda a função na folha

    for(k = 0; k < qtd - 1; k++){
        min = k;
        for(i = k+1; i < qtd; i++){
            if(livros[i].cod < livros[min].cod)
                min = i;
        }
        if(min != k){
            aux = livros[min];
            livros[min] = livros[k];
            livros[k] = aux;
        }
    }
}

int busca(){

}
