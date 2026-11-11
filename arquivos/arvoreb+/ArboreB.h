#ifndef __ARVORE_B__
#define __ARVORE_B__

// Define o tamanho da chave (ex: 8 bytes para o CEP, ex: "20010000")
#define TAM_CHAVE 8

// Define a capacidade máxima de elementos por "Página" (nó) da árvore. 
// Em arquivos, cada página costuma ser grande para aproveitar o bloco do disco.
#define TAM_PAG 300

#include <stdio.h>

// Declarações opacas (forward declarations) das estruturas usadas na Árvore B
typedef struct _ArvoreB ArvoreB;
typedef struct _ArvoreB_Cabecalho ArvoreB_Cabecalho;
typedef struct _ArvoreB_Elemento ArvoreB_Elemento;
typedef struct _ArvoreB_Pagina ArvoreB_Pagina;

// 1. CABEÇALHO DA ÁRVORE (Geralmente fica salvo bem no início do arquivo de índice)
struct _ArvoreB_Cabecalho
{
    long raiz; // Guarda o endereço (offset no arquivo) onde começa a página raiz da Árvore B
};

// 2. ESTRUTURA PRINCIPAL DE CONTROLE (Fica na memória RAM enquanto o programa roda)
struct _ArvoreB
{
    ArvoreB_Cabecalho* cabecalho; // Ponteiro para o cabeçalho carregado em memória
    FILE* f;                      // Ponteiro para o arquivo físico de índice no disco (.dat)
};

// 3. O ELEMENTO / CHAVE dentro da página (O dado em si que a árvore guarda)
struct _ArvoreB_Elemento
{
    char chave[TAM_CHAVE];   // A chave de busca (ex: o CEP)
    long posicaoRegistro;    // Onde esse registro está lá no arquivo de dados principal (o 'pos' que vimos antes)
    long paginaDireita;      // Ponteiro (offset no arquivo) para a página filha à direita deste elemento
};

// 4. A PÁGINA (NÓ) DA ÁRVORE B (É o bloco de dados que é lido/gravado no disco)
struct _ArvoreB_Pagina
{
    int quantidadeElementos;            // Quantos elementos (chaves) esta página está guardando no momento
    long paginaEsquerda;                // Ponteiro (offset no arquivo) para a primeira página filha à esquerda
    ArvoreB_Elemento elementos[TAM_PAG];// O vetor de elementos/chaves armazenados nesta página (até 300)
};

// --- FUNÇÕES DA API DA ÁRVORE B ---

// Abre ou cria o arquivo de índice da Árvore B no disco
ArvoreB* ArvoreB_Abre(const char* nomeArquivo);

// Fecha o arquivo e libera a memória alocada
void ArvoreB_Fecha(ArvoreB* arvore);

// Insere uma nova chave e a posição do seu registro no arquivo de dados
void ArvoreB_Insere(ArvoreB* arvore, char chave[TAM_CHAVE], long posicaoRegistro);

// Imprime a estrutura da árvore no terminal (muito útil para debugar e ver os nós)
void ArvoreB_PrintDebug(ArvoreB* arvore);

// Busca uma chave na árvore e retorna a posição do registro no arquivo de dados (-1 se não achar)
long ArvoreB_Busca(ArvoreB* arvore, char chave[TAM_CHAVE]);

#endif
