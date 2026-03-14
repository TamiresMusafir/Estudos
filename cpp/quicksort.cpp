#include <iostream>

using namespace std;

void troca (int *x, int *y){
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

void quickSort(int valores[], int inicio, int fim){
    int i, j, chave;

    if(fim - inicio < 2){
        if((fim - inicio) == 1){
            if(valores[inicio] > valores[fim])
                troca (&valores[inicio], &valores[fim]);
        }
    } else {
        i = inicio;
        j = fim;
        chave = valores[inicio];

        while(j > i){
            i++;
            while(valores[j] < chave){
                i++;
            }
            while(valores[j] > chave){
                j--;
            }
            if (j < i)
                troca (&valores[i], &valores[j]);
        }
    troca (&valores[inicio], &valores[j]);
    quickSort(valores, inicio, j-1);
    quickSort(valores, j+1, fim);
    }
}

int main(){
    int qtd;
    int inicio = 0;

    cout << "Digite a quantidade de números: ";
    cin >> qtd;

    int valores[qtd];

    for(int i = 0; i < qtd; i++){
        cout << "Entre com o " << i+1 << "número: ";
        cin >> valores[i];
    }

    quickSort(valores, inicio, qtd);

    for(int i = 0; i < qtd; i++){
        cout << valores[i] << "\t";
    }

    //usar rand e srand para gerar números aleatórios.
}