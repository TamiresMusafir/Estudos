#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

#define T 8

void intercala(int numeros[], int inicio, int fim, int meio) {
    // aux é o nosso "rascunho" para organizar os números antes de devolver pro original.
    int i, aux[T], posLivre = inicio, inicioA1 = inicio, inicioA2 = meio + 1;

    // Enquanto houver números nas DUAS metades (Esquerda e Direita)
    while(inicioA1 <= meio && inicioA2 <= fim) {
        
        // O "Segurança": Compara quem é o menor.
        // Se o da esquerda for MAIOR, significa que o da direita é o MENOR.
        if(numeros[inicioA1] > numeros[inicioA2]) {
            aux[posLivre] = numeros[inicioA2]; // O menor (A2) entra no rascunho
            inicioA2++; // O "dedo" da direita desce para o próximo número
        } else {
            // Caso contrário, o da esquerda era o menor ou igual
            aux[posLivre] = numeros[inicioA1]; 
            inicioA1++; // O "dedo" da esquerda desce para o próximo número
        }
        posLivre++; // Pulamos para a próxima vaga livre no nosso rascunho
    }

    // Se o While acabou, uma das metades ficou vazia. 
    // Estes loops abaixo garantem que ninguém seja esquecido (as "Sobras").

    // Se sobrou alguém na 1ª metade (Esquerda)
    for(i = inicioA1; i <= meio; i++) {
        aux[posLivre] = numeros[i];
        posLivre++;
    }

    // Se sobrou alguém na 2ª metade (Direita)
    for(i = inicioA2; i <= fim; i++) {
        aux[posLivre] = numeros[i];
        posLivre++;
    }

    // O "Passar a Limpo": Copia tudo o que organizamos no rascunho (aux)
    // de volta para o vetor original (numeros)
    for(i = inicio; i <= fim; i++) {
        numeros[i] = aux[i];
    }
}

void mergesort(int numeros[], int inicio, int fim) {
    int meio;

    // Condição de Parada: Só divide se o pedaço tiver mais de 1 elemento (inicio < fim)
    if(inicio < fim) {
        // Acha o ponto de corte
        meio = (inicio + fim) / 2;

        // 1. Esmaga a esquerda (Recursão: chama a si mesmo até sobrar um número só)
        mergesort(numeros, inicio, meio);

        // 2. Esmaga a direita (Mesma coisa, mas para o outro lado)
        mergesort(numeros, meio + 1, fim);

        // 3. O Prêmio: Com as duas metades prontas e organizadas, ele intercala (junta)
        intercala(numeros, inicio, fim, meio);
    }
}

int main(){
    int i, numeros[T];

    for(i = 0; i < T; i++){
        cout << "Entre com o " << i + 1 << " número: ";
        cin >> numeros[i]; 
    }

    mergesort(numeros, 0, T-1);

    cout << "Números ordenados: ";
    for(i = 0; i < T; i++)
        cout << numeros[i] << "\t";

    return 0;
}