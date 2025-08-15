#include <stdio.h>

int main()
{
	float sb, sl, imposto, dedução, desconto, impostoporcentual, semdesconto, salarioimposto;

	printf("Informe seu salário bruto:\n");
	scanf("%f", &sb);

	if (sb <= 2259.20)
	{
		imposto = 0;
		printf("\nisento\n");
	}

	else if (sb <= 2259.21)
	{
		imposto = 7.5/100;
		dedução = 169.44;
	}

	else if (sb <= 3751.05)
	{
		imposto = 15.0/100;
		dedução = 381.44;
	}

	else if (sb <= 4664.68)
	{
		imposto = 22.5/100;
		dedução = 662.77;
	}

	else {
		imposto = 27.5/100;
		dedução = 662.77;
	}

	if (imposto == 0)
	{	
		sl = sb;
	}

	else {
		desconto = (sb*imposto) - dedução;
		sl = sb - desconto;
		semdesconto = sb*imposto;
	}

	impostoporcentual = imposto * 100;
	salarioimposto = sb - semdesconto; 


	printf("\nSeu Salário Bruto é: %.2f\n", sb);
	printf("Seu Salário Líquido é: %.2f\n", sl);
	printf("O Imposto foi de: %.0f%%\n", impostoporcentual);
	printf("O Desconto no Salário foi de: %.2f\n", desconto);
	printf("A Dedução no Imposto foi de: %.2f\n", dedução);
	printf("Sem a Dedução, o Imposto seria de: %.2f\n", semdesconto);
	printf("Sem a Dedução, o Salário seria: %.2f\n", salarioimposto);

	return 0;
}