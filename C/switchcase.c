#include <stdio.h>

const char* explicação = "Digite um texto de 1 a 7 para obter um dia da semana, de acordo com o calendário.\n";

int main()
{
	int d;

	printf("%s\n", explicação);

	printf("Digite um número de 1 a 7:\n");
	scanf("%d", &d);

	switch(d){
		case 1:
			printf("Domingo.\n");
			break;

		case 2:
			printf("Segunda-feira.\n");
			break;

		case 3:
			printf("Terça-feira.\n");
			break;

		case 4:
			printf("Quarta-feira.\n");
			break;

		case 5:
			printf("Quinta-feira.\n");
			break;

		case 6:
			printf("Sexta-feira.\n");
			break;

		case 7:
			printf("Sábado.\n");
			break;

		default:
			printf("Valor inválido. Digita certo, animal.\n");
			break;
	}
	return 0;
}