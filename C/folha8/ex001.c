//Faça uma função que receba como parâmetro uma matriz 6 x 12 de inteiros, já preenchida, contendo a quantidade mensal vendida do carro Gol nos anos 2010 a 2015 e um vetor contendo o preço do carro nos anos de 2010 a 2015. A função deverá exibir o valor total das vendas do Gol em cada ano (2010 a 2015).

#include <stdio.h>

void exibe(int qtdmensal[6][12], int preco[6]){
	float total = 0;
	int ano = 2010;

	for(int i = 0; i < 6; i++){
		int soma = 0;
		for(int k = 0; k < 12; k++){
			soma += qtdmensal[i][k];
		}
		total = soma * preco[i];
		printf("Total no ano %d : R$%.2f\n", ano, total); //folha: sempre colocar \n
		ano++;
	}
}