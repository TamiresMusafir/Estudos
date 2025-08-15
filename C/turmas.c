#include <stdio.h>
#include <stdlib.h>

void inicializa(int departamentos[], float salarios[], int totalFuncionarios) {
	//printf("começando a função inicializa");
	for (int i = 0; i < totalFuncionarios; i++) {
		departamentos[i] = rand() % 10 + 1;
		salarios[i] = rand() % 2000 + 1000;
		printf("populando: %.2f.\n", salarios[i]);
	}

vendas_mensais = [
  [2010, [[1, 3], [2, 5]]],
  [2011, [[1, 4], [2, 7]]]
]

precos = [[2010, 123], [2011, 234]]

vendas_totais[]

	for (x = 0; x < total; x++){
		ano = vendas_mensais[x][0]    // = 2010
		meses = vendas_mensais[x][1]  // = [[1, 3], [2, 5]]	

		for (i = 1; i <= 12, i++) {
			mes = meses[i]              // = [1,3]
		}
	}

}

void exibe(int departamentos[], float salarios[], int totalFuncionarios) {
	//printf("começando a função exibe");
	for (int i = 0; i < totalFuncionarios; i++) {
		printf("Departamento: %d - Salário: R$%.2f\n", departamentos[i], salarios[i]);
	}
}

int main()
{
	//printf("Iniciando o programa.\n");
	int departamentos[] = {1,2,3,4,5,6,7,8,9,10};
	int totalFuncionarios = 500;
	float salarios[totalFuncionarios];

	inicializa(departamentos, salarios, totalFuncionarios);
	exibe(departamentos, salarios, totalFuncionarios);

	return 0;
}

