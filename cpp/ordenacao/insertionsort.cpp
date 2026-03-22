#include <iostream>
#include <ctime>
#include <cstdlib>
 
#define T 10

using namespace std;

void insertionsort(int numeros[], int n){

    int i, j, aux;
    // i → controla as rodadas (qual elemento estamos inserindo)
    // j → percorre pra trás (comparando com os anteriores)
    // aux → guarda o valor atual que queremos posicionar corretamente

    for(i = 1; i < n; i++){
        // começa do índice 1 porque o primeiro elemento (índice 0)
        // já é considerado "ordenado"

        aux = numeros[i];
        // guarda o valor atual (o que queremos inserir no lugar certo)

        j = i - 1;
        // começa olhando o elemento imediatamente anterior

        while(j >= 0 && numeros[j] > aux){
            // enquanto:
            // 1. ainda não saiu do vetor (j >= 0)
            // 2. o valor anterior é maior que o atual (aux)

            numeros[j + 1] = numeros[j];
            // empurra o número maior uma posição pra direita

            j--;
            // anda uma posição pra esquerda (vai "voltando")
        }

        numeros[j + 1] = aux;
        // coloca o valor guardado (aux) no lugar correto
        // (j+1 porque o j já andou uma casa a mais no while)
    }
}

int main(){
    int i, numeros[T];
    
    srand(time(NULL));

    for(i = 0; i < T; i++){
        numeros[i] = rand() % 100;
    }

    cout << "Números antes: ";

    for(i = 0; i < T; i++)
        cout << numeros[i] << " ";

    insertionsort(numeros, T);

    cout << "\nNumeros depois: ";

    for(i = 0; i < T; i++)
        cout << numeros[i] << " ";

    return 0;
}