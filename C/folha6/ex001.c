#include

int retornaPares(int numeros[], int qtd){
    int produto = 1;

    for(int i = 0; i < qtd; i++){
        if(numeros[i] % 2 == 0)
            produto *= numeros[i];
    } 
    return produto;
}