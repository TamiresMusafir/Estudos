#include

int retornaPares(int numeros[], int qtd){
    int produto = 1;

    for(int i = 0; i < qtd; i++){
        if(numeros[i] % 2 == 0)
            produto *= numeros[i];
    } 
    if(produto == 1)
        produto = 0;

    return produto;
}