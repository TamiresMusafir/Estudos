#include <stdio.h>
#include <math.h>

float hipotenusa (float a, float b)
{
    return sqrt(a*a + b*b);
}

int main()
{
    float cateto1, cateto2, resultado;

    printf("Digite o primeiro cateto:\n"); 
    scanf("%f", &cateto1);

    printf("\nDigite o segundo cateto:\n"); 
    scanf("%f", &cateto2);
    
    resultado = hipotenusa(cateto1, cateto2);

    printf("A hipotenusa é: %.1f\n", resultado);
    return 0;    
}
