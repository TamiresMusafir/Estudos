#include <stdio.h>

void tabuada (int numero){
    int multp;

    for(int i = 1; i <= 10; i++ ){
        multp = numero * i;
        printf("%d x %d = %d\n", numero, i, multp);
    }
}

int main(){
    int numero;

    printf("Digite um numero: ");
    scanf("%d", &numero);

    tabuada(numero);

    return 0;
}