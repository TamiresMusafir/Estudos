#include <stdio.h>

// Função que calcula o salário
float calculaSalario(float valorHora, int horasTrabalhadas) {
    float salario;
    if (horasTrabalhadas <= 40) {
        salario = valorHora * horasTrabalhadas;
    } else {
        // Calcula as horas extras com 50% a mais
        int horasExtras = horasTrabalhadas - 40;
        salario = (valorHora * 40) + (horasExtras * valorHora * 1.5);
    }
    return salario;
}

int main() {
    float valorHora;
    int horasTrabalhadas;
    float salario;

    // Solicita os valores para o usuário
    printf("Digite o valor da hora de trabalho: ");
    scanf("%f", &valorHora);

    printf("Digite a quantidade de horas trabalhadas: ");
    scanf("%d", &horasTrabalhadas);

    // Chama a função e armazena o resultado em salario
    salario = calculaSalario(valorHora, horasTrabalhadas);

    // Exibe o resultado
    printf("O salario calculado e: %.2f\n", salario);

    return 0;
}
