#include <stdio.h>

void umPosto(int qtdVendas, float *maiorAlcool, float *maiorGasolina, float *maiorDiesel){
    char tipo;
    float valor;

    for(int cont = 0; cont < qtdVendas; cont++){
        printf("Combustíveis: A - Álcool, G - Gasolina, D - Diesel\n");
        printf("Digite o tipo de combustível: ");
        scanf(" %c", &tipo);

        printf("Digite o valor da venda: ");
        scanf("%f", &valor);

        if (tipo == 'A'){
            if(valor > *maiorAlcool){
                *maiorAlcool = valor;
            }
        }else if (tipo == 'G'){
            if (valor > *maiorGasolina){
                *maiorGasolina = valor;
            }
        }
        else if (tipo == 'D'){
            if (valor > *maiorDiesel){
                *maiorDiesel = valor;
            }
        }else{
            printf("Tipo inválido");
        }
    }    
}

int main(){
    int qtdVendas, codigo;
    float maiorAlcool = 0;
    float maiorGasolina = 0;
    float maiorDiesel = 0;

    printf("Digite o código do posto (digite 0 para encerrar):");
    scanf("%d", &codigo);

    while(codigo != 0){
        printf("Digite a quantidade de vendas do posto: ");
        scanf("%d", &qtdVendas);

        umPosto(qtdVendas, &maiorAlcool, &maiorGasolina, &maiorDiesel);

        printf("Maior valor de venda de Álcool, Gasolina e Diesel: %.2f, %.2f, %.2f\n", maiorAlcool, maiorGasolina, maiorDiesel);

        printf("Digite o código do próximo posto (digite 0 para encerrar):");
        scanf("%d", &codigo);
    }

    return 0;
}