#include <stdio.h>

int soma(int a, int b){
    return a+b;
}

int multiplica(int a, int b){
    return a*b;
}


int main(){
    int (*f)(int, int); // ponteiro para uma função
    
    f = soma; // variavel f aponta pro codigo da função soma
    int x = f(3,4); 
    printf("%d\n", x);
    
    f = multiplica;
    x = f(3,4);
    printf("%d\n", x);
    
    return 0;
}
