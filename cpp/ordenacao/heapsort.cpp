#include <iostream>
using namespace std;

#define T 10

void heap(int A[], int t){
    for (int i = (t / 2); i >= 0; i--) 
        descer(A, i, t - 1);
}


void heapsort(int A[], int n) {
    int i;
    //função que transforma o array num heap
    // heap(A, T);
    // ordenação
    for (i = n - 1; i >= 1; i--) {
        troca(&A[0], &A[i]);
        descer(A, 0, i-1);
    }
}

void descer(int A[], int i, int q){
    int d = 2 * i + 2
    int e = 2 * i + 1
    int maior = i; 
    // verificar se tem filhos e comparar com d(direita) e (esquerda).
    if (d <= q && A[d] > A[i]) 
        maior = d;
    if (e <= q && A[e] > A[maior]) 
        maior = e;
    if (maior != i){ 
    //trocar com o maior dos filhos e chamar função novamente
        troca(&A[i], &A[maior]);
        descer(A, maior, q);
    }
}

void troca(int *a, int * b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int main(){
    int A[T] = {50,2,75,8,10,6,15,4,9,3};
    int i;
    heapsort (A,T);
    
    for (i = 0; i < T; i++) {
        cout << A[i];
    }
}