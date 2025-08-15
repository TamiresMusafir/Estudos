#include <stdio.h>

int main (){
	float A, B, soma, subtr, mult, divis;

	printf("Digite o primeiro valor:\n");
	scanf("%f", &A);
	printf("Digite o segundo valor:\n");
	scanf("%f", &B);

	soma = A + B;
	subtr = A - B;
	mult = A * B;
	divis = A / B;

	printf("Resultados:\n");
	printf("Valor da Soma: %.1f.\n", soma);
	printf("Valor da Subtração: %.1f.\n", subtr);
	printf("Valor da Multiplicação: %.1f.\n", mult);
	printf("Valor da Divisão:%.1f.\n", divis);
}