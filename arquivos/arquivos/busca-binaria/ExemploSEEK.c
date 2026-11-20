/*
 * ATENÇÃO:
 * Este código ainda NÃO é uma busca binária completa.
 * Ele encontra o registro do meio do arquivo e, depois disso,
 * continua lendo os próximos registros de forma sequencial.
 */

#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv){
	FILE *f;
	Endereco e;
	int qt;
	int c;

	if(argc != 2){
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	c = 0;

	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco)); // Mostra o tamanho de uma estrutura Endereco em bytes. Neste caso, sizeof(Endereco) = 300.

	f = fopen("cep.dat","rb"); // Abre o arquivo cep.dat para leitura em modo binário.
	
	fseek(f,0,SEEK_END); // Move a posição atual do arquivo para o final.

	long tamanhoBytes = ftell(f); // Retorna a posição atual do arquivo. Como estamos no final, indica o tamanho total do arquivo em bytes.
	long tamanhoRegistros = tamanhoBytes/sizeof(Endereco); // Divide o tamanho total do arquivo pelo tamanho de um Endereco para descobrir quantos registros existem no arquivo.
	long inicio = 0; // Primeiro registro do arquivo.
	long fim = tamanhoRegistros-1; // Índice do último registro do arquivo.
	long meio = (inicio+fim)/2; // Calcula o índice do registro que está no meio.

	// Move a posição do arquivo para o início do registro do meio.
	// fseek trabalha com bytes, então: meio * sizeof(Endereco) transforma o número do registro em uma posição em bytes.
	fseek(f,meio*sizeof(Endereco),SEEK_SET);

	// Lê 1 Endereco a partir da posição atual do arquivo e coloca os dados dentro da variável e.
	// qt recebe a quantidade de Enderecos que foram lidos. Se conseguiu ler 1 registro, qt = 1.
	qt = fread(&e,sizeof(Endereco),1,f);

	while(qt > 0){
		c++; // Conta quantos registros foram lidos.

		// argv[1] < e.cep  => strcmp(argv[1],e.cep) < 0
		// argv[1] > e.cep  => strcmp(argv[1],e.cep) > 0
		// argv[1] == e.cep => strcmp(argv[1],e.cep) == 0
		// pode usar o strstr

		// Compara o CEP informado com o CEP do registro atual. Compara os primeiros 8 caracteres.
		if(strncmp(argv[1],e.cep,8)==0){
			// Se encontrou o CEP, mostra os dados do endereço.
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);

			break; // Sai do while porque encontrou o CEP.
		}

		// Lê o próximo Endereco do arquivo. O fread começa a ler da posição atual do arquivo.
		// Como o fread anterior já avançou a posição, agora ele lê o próximo registro.
		qt = fread(&e,sizeof(Endereco),1,f);
	}

	printf("Total Lido: %d\n", c); // Mostra quantos registros foram lidos.

	fclose(f); // Fecha o arquivo.

	return 0;
}
