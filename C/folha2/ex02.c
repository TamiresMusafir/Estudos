#include <stdio.h>
#include <math.h>

float hipotensua (float a, float b)
{
    return sqrt(a*a + b*b);
}

int main()
{
    float cateto1, cateto2, resultado;

    printf("Digite os dois catetos:\n"); 
    scanf("%f %f", &cateto1, &cateto2);
    
    resultado = hipotensua(cateto1, cateto2);

    printf("A hipotenusa é: %f\n", resultado);
    return 0;    
}