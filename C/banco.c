#include <stdio.h>

int main ()
{
	float saldo = 0;
	float valor, novo_saldo;
	char nome[10] = "";
	char opcao;

	printf("Digite seu nome:\n");
	scanf("%s", nome);

	printf("Olá %s, bem vindo!", nome);
	printf("\nSeu saldo atual na conta é de: R$%.2f", saldo);

 	getchar();

	printf("\nPressione ""d"" para depósito, e ""s"" para saque:");
	scanf("%c", &opcao);

	if (opcao == 'd' || opcao == 'D')
	{
		printf("\nVocê escolheu fazer depósito.");
		printf("\nDigite o valor do depósito:");
		scanf("%f", &valor);

		novo_saldo = saldo + valor;

		printf("\nDepósito realizado! Novo saldo: R$%.2f", novo_saldo);

	}
	else if (opcao == 's' || opcao =='S')
	{
		printf("\nVocê escolheu fazer saque.");
		printf("\nDigite o valor do saque:");
		scanf("%f", &valor);

		novo_saldo = saldo - valor;

		printf("\nDepósito realizado! Novo saldo: R$%f", novo_saldo);
	}
	else
	{
		printf("Opção inválida.");
	}
	while (opcao != 'd' && opcao != 'D' && opcao != 's' && opcao != 'S');

	return 0;
}
