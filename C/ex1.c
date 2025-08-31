#include <stdio.h>

int criaNumero() {
    int x, y;

    printf("Digite o primeiro número de 2 algarismos:\n");
    scanf("%d", &x);

    printf("Digite o segundo número de 2 algarismos:\n");
    scanf("%d", &y);

    return x * 100 + y;
}

int main() {
    int resultado;

    resultado = criaNumero();  // chama a função que já faz tudo
    printf("O número criado é: %d\n", resultado);

    return 0;
}