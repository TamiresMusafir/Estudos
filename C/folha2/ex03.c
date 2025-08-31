#include <stdio.h>

float calculaValorGarcom (float valor)
{
    gorjeta = valor * 0.10;
    return gorjeta;
}

float calculaValorTotal (float valor, float gorjeta)
{
    float total;
    total = valor + garçom;
    return total;
}

int main ()
{
    float valor, gorjeta, total;

    printf("Digite o valor gasto pelo cliente:");
    scanf("%f", &valor);

    gorjeta = calculaValorGarcom(valor);
    total = calculaValorTotal(valor, gorjeta);

    printf("O valor a ser pago para o garçom é:RS %.2f\n", gorjeta);
    printf("O valor total é:RS %.2f\n", total);

    return 0;
}