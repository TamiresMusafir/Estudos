#include <stdio.h>

int numeros(int qtdNum)
{
    int num, maior;

    for(int i = 1; i <= qtdNum; i++)
    {
        printf("Digite o número:");
        scanf("%d", &num);

        if(i == 1 || num > maior)
        {
            maior = num;
        }
    }

    return maior;
}

int main()
{
    int qtdNum, maior;

    printf("Digite a quantidade de números:");
    scanf("%d", &qtdNum);

    maior = numeros(qtdNum);

    printf("O maior número é: %d", maior);

    return 0;
}