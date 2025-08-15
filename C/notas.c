#include <stdio.h>

int main()
{
	float p1, p2, media;

	printf("Digite sua nota da P1:\n ");
	scanf("%f", &p1);

	printf("Digite sua nota da P2:\n ");
	scanf("%f", &p2);

	printf("\nSua nota na P1 é %.1f\n", p1);
	printf("Sua nota na P2 é %.1f\n", p2);

	media = (p1+p2)/2;

	printf("\nSua média foi: %.1f\n", media);

	if (media >=7)
	{
		printf("\nEstá Aprovado\n");
	}

	else if (media >=3)
	{
		printf("\nIrá para a Prova Final\n");
	}
	else {
		printf("\nEstá Reprovado\n");
	}

	return 0;
}