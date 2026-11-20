#include <stdio.h>      // FILE, fopen, fread, fwrite, fseek, ftell, fclose...
#include <stdlib.h>     // malloc, free, qsort
#include <string.h>     // strncmp

typedef struct _Endereco Endereco;

struct _Endereco{
    char logradouro[72];   // Nome do logradouro
    char bairro[72];       // Bairro
    char cidade[72];       // Cidade
    char uf[72];           // UF
    char sigla[2];         // Sigla
    char cep[8];           // CEP
    char lixo[2];          // Espaço + quebra de linha
};

// Função usada pelo qsort para comparar DOIS Enderecos.
//
// O qsort não sabe que estamos trabalhando com Endereco.
// Por isso ele passa os dois elementos como void*, ou seja, ponteiros genéricos.
//
// e1 = endereço do primeiro Endereco
// e2 = endereço do segundo Endereco
int compara(const void *e1, const void *e2){
    // (Endereco*) faz um CASTING: "trate e1 como sendo um ponteiro para Endereco".
    // Depois, ->cep acessa o campo cep desse Endereco.
    // Fazemos a mesma coisa com e2.
    // strncmp compara os dois CEPs.
    // Retorna:
    // < 0 → e1 vem antes de e2
    // = 0 → são iguais
    // > 0 → e1 vem depois de e2
    //
    // O qsort usa esse resultado para saber como deve ordenar os registros.
    return strncmp(
        ((Endereco*)e1)->cep,
        ((Endereco*)e2)->cep,
        8
    );
}


int main(int argc, char**argv){
    // f     → arquivo original (cep.dat)
    // saida → arquivo que será criado (cep-ordenado.dat)
    FILE *f, *saida;

    // e é um PONTEIRO para Endereco. Guarda o endereço de uma área da memória onde ficarão vários Enderecos.
    Endereco *e;

    // posicao → vai guardar o tamanho do arquivo em bytes
    // qtd     → quantidade de registros Endereco no arquivo
    long posicao, qtd, metade;

	// Abre o arquivo cep.dat para leitura binária.
    f = fopen("cep.dat", "rb");  

    // Vai para o FINAL do arquivo.
    //
    // Precisamos ir para o final para descobrir o tamanho total do arquivo.
    fseek(f, 0, SEEK_END);

    // ftell() informa a posição atual no arquivo.
    //
    // Como estamos no final, essa posição representa quantos BYTES o arquivo possui.
    posicao = ftell(f);

    // Descobrimos quantos registros existem.
    // Exemplo:
    // arquivo = 300000 bytes
    // sizeof(Endereco) = 300 bytes
    // 300000 / 300 = 1000 registros
    qtd = posicao / sizeof(Endereco);

    // Reserva na memória RAM espaço suficiente para armazenar TODOS os registros.
    //
    // qtd * sizeof(Endereco) significa:
    // quantidade de registros × tamanho de cada registro
    //
    // malloc() retorna um endereço de memória.
    //
    // (Endereco*) é um CASTING:
    // estamos dizendo para tratar o endereço retornado pelo malloc como um ponteiro para Endereco.
    e = (Endereco*) malloc(qtd * sizeof(Endereco));

    // IMPORTANTE:
    // Antes fizemos: fseek(f, 0, SEEK_END);
    // Então a posição do arquivo está no FINAL.
    // Mas agora queremos ler os registros desde o começo.
    // rewind(f) volta a posição do arquivo para o início.
    rewind(f);
	
    // Lê os registros do arquivo e coloca na memória.
    // e → endereço de onde os dados serão armazenados
    // sizeof(Endereco) → tamanho de CADA registro
    // qtd → quantidade de registros que queremos ler
    // f → arquivo de onde vamos ler
    //
    // fread retorna quantos elementos conseguiu ler.
    //
    // Então: fread(...) == qtd
    // significa: "consegui ler exatamente a quantidade que esperava?"
    if(fread(e, sizeof(Endereco), qtd, f) == qtd){
        printf("Lido = OK\n");
    }

    // Ordena os registros que estão na memória.
    // e → endereço do primeiro elemento da área de memória
    // qtd → quantidade de elementos
    // sizeof(Endereco) → tamanho de cada elemento
    // compara → função que o qsort deve usar para comparar dois elementos.
    // O qsort é quem decide QUAIS dois elementos comparar e quando.
    // Ele chama a função compara automaticamente.
    qsort(e, qtd, sizeof(Endereco), compara);

    printf("Ordenado = OK\n");

    // Cria o arquivo onde será guardada a versão ordenada.
    // "wb" = write binary - escrever arquivo binário
    saida = fopen("cep-ordenado.dat", "wb");

    // Escreve no novo arquivo os registros que estão agora ordenados na memória.
    // e → de onde pegar os dados
    // sizeof(Endereco) → tamanho de cada registro
	// qtd → quantidade de registros
    // saida → arquivo onde escrever
    fwrite(e, sizeof(Endereco), qtd, saida);

    fclose(saida); // Fecha o arquivo de saída.

    // Libera a memória que foi reservada pelo malloc().
    // Não precisamos mais dos registros na RAM, então devolvemos esse espaço ao sistema.
    free(e);

    return 0;
}
