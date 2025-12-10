#include <stdio.h>
#define MAX 10000

struct livro{
    int codigo, qtdexist, qtdemp;
};
typedef struct livro livro;

void ordena(livro livros[], int qtd){
    int k, i, min; //colocar toda a função na folha
    livro aux; // colocar na folha, precisa ser struct o aux

    for(k = 0; k < qtd - 1; k++){
        min = k;
        for(i = k+1; i < qtd; i++){
            if(livros[i].codigo < livros[min].codigo)
                min = i;
        }
        if(min != k){
            aux = livros[min];
            livros[min] = livros[k];
            livros[k] = aux;
        }
    }
}

int busca(livro livros[], int codigo, int qtd){
    int ini = 0;
    int pos = -1;
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

    return pos; // não achou
}

int leitura(livro livros[]){
    int codigo;
    int i = 0; //não esquecer, declarar no while fora.

    printf("Digite o código ou 0: ");
    scanf("%d", &codigo);

    while(codigo != 0 && codigo < MAX){
        livros[i].codigo = codigo;

        printf("Digite a quantidade existente e emprestada: ");
        scanf("%d%d", &livros[i].qtdexist, &livros[i].qtdemp);

        i++; //NÃO ESQUECER NO WHILE E NEM OS ;!

        printf("Digite o código ou 0: ");
        scanf("%d", &codigo);
    }

    return i;
}

int main(){
    int qtd, pesquisa, resultado;
    livro livros[MAX];

    qtd = leitura(livros);
    ordena(livros, qtd);

    printf("Digite o código a ser pesquisado: ");
    scanf("%d", &pesquisa);

    while(pesquisa != 0){
        resultado = busca(livros, pesquisa, qtd);
        if(resultado == -1)
            printf("Livro inexistente.\n");
        else if(livros[resultado].qtdexist == livros[resultado].qtdemp)
            printf("Livro não disponível para empréstimo\n");
        else    
            printf("Livro disponível para empréstimo.\n");

        printf("Digite o código a ser pesquisado: ");
        scanf("%d", &pesquisa);
    }

    return 0; //não esquecer!
}



