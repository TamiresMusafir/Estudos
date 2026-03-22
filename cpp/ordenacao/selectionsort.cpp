#include <iostream>
#include <ctime>
#include <cstdlib>

#define T 10

using namespace std;

void selectionsort(int numeros[], int n){
    int i, j, min, aux;

    for(i = 0; i < n - 1; i++){
        // percorre cada posição do vetor (menos a última)

        min = i;
        // assume que o menor elemento é o da posição atual

        for(j = i + 1; j < n; j++ ){
            // percorre o resto do vetor (depois do i)

            if(numeros[j] < numeros[min])
                min = j;
            // se achar um valor menor, atualiza o índice do menor
        }

        if(min != i){
            // só troca se encontrou um menor diferente

            aux = numeros[min];
            numeros[min] = numeros[i];
            numeros[i] = aux;
            // troca o menor encontrado com a posição atual
        }
    }
}

int main(){
    int i, numeros[T];
    
    srand(time(NULL));

    for(i = 0; i < T; i++){
        numeros[i] = rand() % 100;
    }

    cout << "Vetor antes: ";
    for(i = 0; i < T; i++){
        cout << numeros[i] << " ";
    }

    selectionsort(numeros, T);

    cout << "\nVetor depois: ";
    for(i = 0; i < T; i++){
        cout << numeros[i] << " ";
    }

    return 0;
}