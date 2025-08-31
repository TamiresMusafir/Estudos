#include <stdio.h>

float calculaMedia (float n1, float n2)
{
    float media;
    media = (n1 + n2)/2;
    return media;
}

int main ()
{
    int matricula;
    float nota_p1, nota_p2, nota_t1, nota_t2;
    float mediaProvas, mediaTrabalhos, mediaFinal;

    printf("Digite sua matrícula:");
    scanf("%d", &matricula);

    printf("\nDigite sua nota da p1:");
    scanf("%f", &nota_p1);

    printf("\nDigite sua nota da p2:");
    scanf("%f", &nota_p2);

    printf("\nDigite sua nota do primeiro trabalho:");
    scanf("%f", &nota_t1);

    printf("\nDigite sua nota do segundo trabalho:");
    scanf("%f", &nota_t2);

    mediaProvas = calculaMedia(nota_p1, nota_p2);
    mediaTrabalhos = calculaMedia(nota_t1, nota_t2);
    mediaFinal = calculaMedia(mediaProvas, mediaTrabalhos);

    printf("\nSua matrícula é: %d", matricula);

    printf("\nSua média nas provas foi: %.1f", mediaProvas);

    printf("\nSua média nos trabalhos foi: %.1f", mediaTrabalhos);

    printf("\nSua média nas provas foi: %.1f", mediaProvas);

    printf("\nSua média final foi: %.1f", mediaFinal);

    return 0;
}