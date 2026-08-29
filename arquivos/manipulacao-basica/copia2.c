```c
#include <stdio.h>          // Biblioteca que contém as funções de manipulação de arquivos

#define TAMANHO 8192        // Define o tamanho do buffer: 8192 bytes

int main(int argc, char** argv)
{
    FILE *entrada, *saida;  // Ponteiros para os arquivos de entrada e saída

    char buffer[TAMANHO];   // Área da memória que armazena temporariamente os dados que serão lidos
                            // Aqui o buffer consegue guardar até 8192 bytes

    int qtd;                // Vai guardar QUANTOS elementos o fread conseguiu ler

    // Esperamos 3 argumentos:
    // argv[0] = nome do programa
    // argv[1] = arquivo de origem
    // argv[2] = arquivo de destino
    if(argc != 3){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);

        return 1;     
    }

    entrada = fopen(argv[1], "rb"); // Abre o arquivo de origem para LEITURA

    // Se fopen falhou, entrada será NULL
    if(!entrada){printf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);

        return 1;   // Encerra o programa
    }

    saida = fopen(argv[2], "wb");   // Abre/cria o arquivo de destino para ESCRITA em modo binário
                                    // argv[2] contém o nome do arquivo de destino

    // Se não conseguiu abrir/criar o arquivo de saída
    if(!saida){
        fclose(entrada);            // Como já abrimos "entrada", precisamos fechá-lo antes de sair

        fprintf(stderr, "Arquivo %s não pode ser aberto para escrita\n", argv[2]);

        return 1;
    }

    // fread tenta ler até 8192 bytes do arquivo e coloca esses bytes dentro do buffer.
    // O retorno de fread é a quantidade de elementos que ele realmente conseguiu ler.
    // Exemplo:
    // qtd = 8192 → conseguiu ler 8192 bytes
    // qtd = 3000 → conseguiu ler 3000 bytes
    // qtd = 0    → não conseguiu ler mais nada
    qtd = fread(
                buffer,             // Onde os dados lidos serão armazenados
                sizeof(char),       // Tamanho de cada elemento que estamos lendo
                TAMANHO,            // Quantidade máxima de elementos que queremos ler
                entrada             // Arquivo de onde vamos ler
    );

    // Enquanto conseguimos ler ao menos 1 byte fwrite pega os dados do buffer e escreve no arquivo de saída.
    while(qtd > 0){
        fwrite(
            buffer,                 // Dados que estão no buffer
            sizeof(char),           // Tamanho de cada elemento
            qtd,                    // Quantos elementos devem ser escritos
            saida                   // Arquivo onde os dados serão escritos
        );

        // Depois de escrever o bloco anterior, lê o próximo bloco do arquivo.
        qtd = fread(
            buffer,                 // Coloca os próximos dados aqui
            sizeof(char),           // Cada elemento possui tamanho de char
            TAMANHO,                // Tenta ler novamente até 8192 bytes
            entrada                 // Do arquivo de entrada
        );
    }

    fclose(entrada);                // Fecha o arquivo de entrada
    fclose(saida);                  // Fecha o arquivo de saída

    return 0;                       // Programa terminou com sucesso
}