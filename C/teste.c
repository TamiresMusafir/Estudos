#include <stdio.h>
#include <string.h>

int lerVetor(char v[][40], int max){
    int i = 0;

    while(i < max){
        printf("Digite uma string: ");
        scanf(" %[^\n]", v[i]);  

        if(strcmp(v[i], "FIM") == 0)  // para se digitar FIM
            break;

        i++;
    }

    return i;
}

void ordenar(char v[][40], int n){
    int k, min;
    char aux[40];

    for(k = 0; k < n-1; k++){
        min = k;
        for(int i = k+1; i < n; i++){
            if(strcmp(v[i], v[min]) < 0)
                min = i;
        }
        if(min != k){
            strcpy(aux, v[min]);
            strcpy(v[min], v[k]);
            strcpy(v[k], aux);
        }
    }
}

int contarDistintos(char v[][40], int n){
    
    if(n == 0){
        return 0;
    }

    ordenar(v, n);

    int distintos = 1;
    for(int i = 1; i < n; i++){
        if(strcmp(v[i], v[i-1]) != 0){
            distintos++;
        }
    }

    return distintos;
}

int main() {
    char vetor[40][100];
    int quantidade;
    int resultado;
    int max = 100;

    quantidade = lerVetor(vetor, max);

    resultado = contarDistintos(vetor, quantidade);

    printf("\nQuantidade de elementos distintos: %d\n", resultado);

    return 0;
}