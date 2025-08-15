#include <stdio.h>
#include <math.h>

int main()
{
	float a, b, c, delta, bhaskara1, bhaskara2, bhaskara3, x, x1, x2;
	printf("Digite o valor de a:\n" );
	scanf("%f", &a);

	printf("\nDigite o valor de b:\n");
	scanf("%f", &b);	

	printf("\nDigite o valor de c:\n");
	scanf("%f", &c);

	delta = b*b-4*a*c;
	printf("\nDelta é: (%.1f)*(%.1f) - 4*(%.1f)*(%.1f)", b, b, a, c);
	printf("\nO valor de delta é: %.1f\n", delta);

	bhaskara1 = (-b+sqrt(delta))/(2*a);
	bhaskara2 = (-b-sqrt(delta))/(2*a);
	bhaskara3 = -b/(2*a);
	printf("\nBhaskara é: (-%.1f ± √%.1f) / (2* %.1f)", b, delta, a);

	if (delta > 0)
	{
		x1 = bhaskara1;
		x2 = bhaskara2;
		printf("\nO valor de Bhaskara é: %.1f e %.1f\n", bhaskara1, bhaskara2);
		printf("\nX1 é: %.1f\n", x1);
		printf("X2 é: %.1f\n", x2);
	}

	else if (delta == 0)
	{
		x = bhaskara3;
		printf("\nO valor de Bhaskara é: %1.f", bhaskara3);
		printf("\nHá somente uma raiz: %.1f\n", x);
	}

	else 
	{
		printf("\nNão há raiz real. O resultado é menor que zero.\n");
	}

	return 0;
}