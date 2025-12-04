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

int busca(livro livros[], int busca, int qtd){
    int ini = 0;
    pos = -1;
    int fim = qtd - 1;
    int med;

    while(pos == -1 && ini <= fim){
        med = (ini + fim) / 2;

        if(livros[med].codigo == codigo)
            pos = med;        // achou!

        else
            if(livros[med].codigo < codigo)
                ini = med + 1;     // procura na direita
            else
                fim = med - 1;     // procura na esquerda
    }

    return -1; // não achou
}

void leitura(livro livros[]){


}



