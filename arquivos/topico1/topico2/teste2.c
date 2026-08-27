/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int soma(int a, int b){
    return a+b;
}

int multiplica(int a, int b){
    return a*b;
}


void imprimeResultado(int (*f)(int, int), int a, int b){
    printf("%d\n", f(a,b));
}


int main(){
    imprimeResultado(soma,3,4);
    imprimeResultado(multiplica,3,4);
    
    return 0;
}
