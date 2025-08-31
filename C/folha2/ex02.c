#include <stdio.h>
#include <math.h>

float hipotenusa (float a, float b)
{
    return sqrt(a*a + b*b);
}

int main()
{
    float cateto1, cateto2, resultado;

    printf("Digite os dois catetos:\n"); 
    scanf("%f %f", &cateto1, &cateto2);
    
    resultado = hipotenusa(cateto1, cateto2);

    printf("A hipotenusa é: %f\n", resultado);
    return 0;    
}