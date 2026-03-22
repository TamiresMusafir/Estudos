#include <iostream>
#include <cstdlib> // rand() e srand()
#include <ctime>   // time() para inicializar a semente de rand()

#define T 10

using namespace std;

void bubblesort(int numeros[], int n) {
    int i, j, aux; 

    // O laço 'i' é o contador de rodadas. 
    // Se temos N números, após N-1 rodadas, o último que sobrar estará no lugar certo.
    for(i = 0; i < n - 1; i++) { 
        
        /* POR QUE "n - 1 - i"?
           1. O "- 1": Como comparamos j com j + 1, o j não pode ir até o último índice, 
              senão o j + 1 tentaria acessar um espaço fora da memória do vetor (erro).
           2. O "- i": A cada rodada do i, o maior número daquela vez "flutua" até o fim. 
              O "- i" avisa ao j que ele pode parar antes, pois o final já está ordenado.
              Isso economiza tempo de processamento!
        */
        for(j = 0; j < n - 1 - i; j++) {
            
            // Compara vizinhos (o atual com o da direita)
            if(numeros[j] > numeros[j + 1]) {
                // Se o da esquerda for maior, eles trocam de lugar
                aux = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = aux;
            }
        }   
    }
}

int main() {
    int i, numeros[T];

    srand(time(NULL)); // inicializa a semente para números aleatórios

    for(i = 0; i < T; i++){
        numeros[i] = rand() % 100;
    }

    cout << "Vetor antes: ";
    for(i = 0; i < T; i++){
        cout << numeros[i] << " ";
    }

    bubblesort(numeros, T);

    cout << "\nVetor ordenado: ";
    for(i = 0; i < T; i++){
        cout << numeros[i] << " ";
    }

    return 0;
}