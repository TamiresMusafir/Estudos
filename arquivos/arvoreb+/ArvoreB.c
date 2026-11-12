/*
 * ArvoreB.c - Árvore B gravada em disco (índice: chave -> posição do registro)
 *
 * COMO O ARQUIVO "arvore.dat" É ORGANIZADO
 * ----------------------------------------
 *   offset 0      -> Cabecalho (8 bytes): só guarda o offset da página raiz
 *   offset 8      -> página (primeira raiz)      cada página tem 7216 bytes
 *   offset 7224   -> página
 *   offset 14440  -> página
 *   ...
 *   (tamanhos de Linux 64 bits: int=4, long=8, e o compilador põe 4 bytes de
 *    padding depois do int; confira com sizeof no seu ambiente)
 *
 * CONVENÇÕES
 * ----------
 *  - Todo "ponteiro" da árvore é um offset em bytes dentro do arquivo (long).
 *  - Offset 0 significa NULO. Nenhuma página começa em 0 (lá fica o cabeçalho).
 *  - Uma página é FOLHA quando paginaEsquerda == 0.
 *  - Página nova sempre é gravada no FIM do arquivo (append).
 *  - A árvore cresce pela RAIZ: quando a raiz estoura, cria-se uma raiz nova
 *    e o cabeçalho passa a apontar para ela.
 *  - As chaves têm TAM_CHAVE bytes e NÃO têm '\0' no final. Por isso toda
 *    comparação usa strncmp com TAM_CHAVE, nunca strcmp.
 *  - Nada aqui verifica chave repetida: inserir duas vezes a mesma chave
 *    grava dois elementos.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ArvoreB.h"

/* ================== Páginas na memória (RAM) ================== */

// Cria uma página vazia na RAM, com tudo zerado.
// Zerar importa: a página inteira vai para o disco com fwrite, então não
// queremos gravar lixo de memória no arquivo.
ArvoreB_Pagina* ArvoreB_alocaPagina()
{
    int i;
    ArvoreB_Pagina* resp = (ArvoreB_Pagina*) malloc(sizeof(ArvoreB_Pagina));
    resp->quantidadeElementos = 0;  // nenhum elemento em uso
    resp->paginaEsquerda = 0;       // 0 = nulo => por padrão é folha
    for(i=0; i<TAM_PAG; i++)
    {
        memset(resp->elementos[i].chave,'\0',TAM_CHAVE);
        resp->elementos[i].paginaDireita = 0;
        resp->elementos[i].posicaoRegistro = 0;
    }
    return resp;
}

// Libera a página da RAM (não mexe no arquivo).
void ArvoreB_desalocaPagina(ArvoreB_Pagina* p)
{
    if(p)
    {
        free(p);
    }
}

/* ================== Abrir, comparar e fechar ================== */

// Abre o arquivo de índice. Se ele ainda não existir, cria já com:
//     [cabeçalho com raiz = 8] [uma página raiz vazia, que é folha]
// Devolve NULL se não conseguir criar o arquivo.
ArvoreB* ArvoreB_Abre(const char* nomeArquivo)
{
    ArvoreB* resp = (ArvoreB*) 0;
    ArvoreB_Cabecalho* cabecalho = (ArvoreB_Cabecalho*) 0;
    ArvoreB_Pagina* raiz = (ArvoreB_Pagina*) 0;
    // 1) Abre só para leitura, apenas para descobrir se o arquivo já existe.
    FILE* f = fopen(nomeArquivo, "rb");
    if(!f)
    {
        // 2) Não existe: cria ("wb" cria/apaga e abre para escrita).
        f = fopen(nomeArquivo,"wb");
        if(!f)
        {
            fprintf(stderr,"Arquivo %s não pode ser criado\n", nomeArquivo);
            return resp;
        }
        // O cabeçalho aponta a raiz para o byte logo depois dele mesmo.
        cabecalho = (ArvoreB_Cabecalho*) malloc(sizeof(ArvoreB_Cabecalho));
        cabecalho->raiz = sizeof(ArvoreB_Cabecalho);
        fwrite(cabecalho,sizeof(ArvoreB_Cabecalho),1,f);
        // Primeira página: vazia e com paginaEsquerda = 0, ou seja, folha.
        raiz = ArvoreB_alocaPagina();
        fwrite(raiz,sizeof(ArvoreB_Pagina),1,f);
        ArvoreB_desalocaPagina(raiz);
        free(cabecalho);
    }
    fclose(f);
    // 3) Reabre em "rb+": leitura E escrita, sem apagar o que já existe.
    f = fopen(nomeArquivo, "rb+");
    resp = (ArvoreB*) malloc(sizeof(ArvoreB));
    resp->f = f;
    // 4) Traz o cabeçalho para a RAM (é de lá que sai o offset da raiz).
    resp->cabecalho = (ArvoreB_Cabecalho*) malloc(sizeof(ArvoreB_Cabecalho));
    fread(resp->cabecalho,sizeof(ArvoreB_Cabecalho),1,f);
    return resp;
}

// Compara dois elementos pela chave (8 bytes, sem '\0').
// Tem o formato que o qsort exige: negativo se e1<e2, 0 se iguais, positivo se e1>e2.
int ArvoreB_Compara(const void *e1, const void* e2)
{
    return strncmp(((ArvoreB_Elemento*)e1)->chave,((ArvoreB_Elemento*)e2)->chave,TAM_CHAVE);
}

// Regrava o cabeçalho (que mora na RAM) no início do arquivo.
// Precisa ser chamado sempre que a raiz mudar de lugar.
void ArvoreB_escreveCabecalho(ArvoreB* arvore)
{
    fseek(arvore->f, 0, SEEK_SET);
    fwrite(arvore->cabecalho, sizeof(ArvoreB_Cabecalho), 1, arvore->f);
}

// Salva o cabeçalho, fecha o arquivo e libera a memória.
void ArvoreB_Fecha(ArvoreB* arvore)
{
    if(arvore)
    {
        ArvoreB_escreveCabecalho(arvore);
        fclose(arvore->f);
        free(arvore->cabecalho);
        free(arvore);
    }
}

/* ================== Inserção ================== */

// Divide (split) uma página CHEIA que recebeu mais um elemento (o "overflow").
//
//   posicaoPagina: offset da página cheia no arquivo
//   pagina:        a página cheia, já lida para a RAM (TAM_PAG elementos)
//   overflow:      o elemento que não coube (seria o de número TAM_PAG+1)
//
// Resultado: a página original fica com a metade menor, uma página NOVA (no fim
// do arquivo) fica com a metade maior, e o elemento do MEIO sobe: a função o
// devolve (malloc) já apontando, em paginaDireita, para a página nova.
// Quem chamou deve inserir esse elemento no pai e depois dar free nele.
//
// Exemplo com TAM_PAG = 3:  página [10 20 30], overflow = 25
//   passo 1: 25 < 30, troca => página [10 20 25], overflow = 30  (overflow = maior de todos)
//   passo 2: nova página recebe elementos[2] (25) + overflow (30) => [25 30]
//   passo 3: página original fica com 1 elemento => [10]
//   passo 4: o elemento do meio (elementos[1] = 20) sobe
//   resultado:  [10]  20  [25 30]
ArvoreB_Elemento* ArvoreB_Split(ArvoreB *arvore, long posicaoPagina, ArvoreB_Pagina* pagina, ArvoreB_Elemento* overflow)
{
    int i;
    ArvoreB_Elemento aux;
    ArvoreB_Elemento* resp;
    ArvoreB_Pagina* paginaSplit;
    // Passo 1: garantir que "overflow" seja o MAIOR dos TAM_PAG+1 elementos.
    // O elemento na área de overflow é menor que o ultimo elemento da página?
    if(ArvoreB_Compara(overflow,&pagina->elementos[pagina->quantidadeElementos-1])<0)
    {
        // Trocar o último com o elemento no overflow e reordenar a página.
        aux = *overflow;
        *overflow = pagina->elementos[pagina->quantidadeElementos-1];
        pagina->elementos[pagina->quantidadeElementos-1] = aux;
        qsort(pagina->elementos,pagina->quantidadeElementos,sizeof(ArvoreB_Elemento),ArvoreB_Compara);
    }
    // Passo 2: a página nova recebe a metade MAIOR: os elementos depois do
    // meio (índices TAM_PAG/2+1 até o fim) e mais o overflow.
    paginaSplit = ArvoreB_alocaPagina();
    for(i=TAM_PAG/2+1;i<TAM_PAG;i++)
    {
        paginaSplit->elementos[paginaSplit->quantidadeElementos] = pagina->elementos[i];
        paginaSplit->quantidadeElementos++;
    }
    paginaSplit->elementos[paginaSplit->quantidadeElementos] = *overflow;
    paginaSplit->quantidadeElementos++;
    // Passo 3: a página original fica só com a metade MENOR (índices 0 até
    // TAM_PAG/2-1). O elemento do meio (índice TAM_PAG/2) continua fisicamente no
    // vetor, mas fora da contagem, então é ignorado (lixo). Grava de volta no disco.
    pagina->quantidadeElementos = TAM_PAG/2;
    fseek(arvore->f, posicaoPagina, SEEK_SET);
    fwrite(pagina, sizeof(ArvoreB_Pagina),1,arvore->f);
    // Passo 4: monta o elemento que vai subir (cópia do elemento do meio).
    resp = (ArvoreB_Elemento*) malloc(sizeof(ArvoreB_Elemento));
    // O filho que ficava à direita do elemento do meio vira o filho mais à
    // esquerda da página nova. (Em folhas isso é 0, e a página nova continua folha.)
    paginaSplit->paginaEsquerda = pagina->elementos[TAM_PAG/2].paginaDireita;
    memcpy(resp->chave,pagina->elementos[TAM_PAG/2].chave,TAM_CHAVE);
    resp->posicaoRegistro = pagina->elementos[TAM_PAG/2].posicaoRegistro;
    // A página nova será gravada no fim do arquivo; o offset do fim é o endereço dela.
    fseek(arvore->f,0,SEEK_END);
    resp->paginaDireita = ftell(arvore->f);
    fwrite(paginaSplit, sizeof(ArvoreB_Pagina),1,arvore->f);
    ArvoreB_desalocaPagina(paginaSplit);
    return resp;
}

// Insere a chave na subárvore cuja raiz está em posicaoPagina.
//
// Devolve:
//   NULL            -> inseriu e nada precisa subir
//   elemento (malloc) -> esta página estourou e sofreu split; o elemento devolvido
//                       deve ser inserido pelo CHAMADOR na página pai
ArvoreB_Elemento* ArvoreB_Insere_Recursiva(ArvoreB* arvore, long posicaoPagina, char chave[TAM_CHAVE], long posicaoRegistro)
{
    int i;
    long posicaoPaginaFilho;
//    ArvoreB_Elemento* resp = NULL;
    ArvoreB_Elemento* resp = (ArvoreB_Elemento*) 0;
    ArvoreB_Elemento *elementoSplit = (ArvoreB_Elemento*) 0;
    ArvoreB_Elemento overflow;
    // printf("Inserindo %.8s na página %ld\n", chave, posicaoPagina);
    // Lê a página atual do disco (UMA leitura por nível da árvore).
    ArvoreB_Pagina *pagina = ArvoreB_alocaPagina();
    fseek(arvore->f, posicaoPagina, SEEK_SET);
    fread(pagina, sizeof(ArvoreB_Pagina),1,arvore->f);
    if(pagina->paginaEsquerda == 0) // Folha
    {
        if(pagina->quantidadeElementos < TAM_PAG) // Cabe na folha
        {
            // Coloca no fim do vetor, reordena e grava a página de volta.
            // (Simples, mas faz um qsort a cada inserção; dá para otimizar.)
            memcpy(pagina->elementos[pagina->quantidadeElementos].chave,chave,TAM_CHAVE);
            pagina->elementos[pagina->quantidadeElementos].posicaoRegistro = posicaoRegistro;
            pagina->quantidadeElementos++;
            qsort(pagina->elementos,pagina->quantidadeElementos,sizeof(ArvoreB_Elemento),ArvoreB_Compara);
            fseek(arvore->f, posicaoPagina, SEEK_SET);
            fwrite(pagina, sizeof(ArvoreB_Pagina),1,arvore->f);
        }
        else // Não cabe na folha
        {
            // Folha cheia: o novo elemento vira "overflow" e a folha sofre split.
            memcpy(overflow.chave, chave, TAM_CHAVE);
            overflow.posicaoRegistro = posicaoRegistro;
            overflow.paginaDireita = 0;   // folha não tem filhos
            resp = ArvoreB_Split(arvore, posicaoPagina, pagina, &overflow);
        }
    }
    else // Não é folha
    {
        // Escolhe por qual filho descer: começa no mais à esquerda e avança
        // enquanto a chave for maior ou igual à chave do elemento i.
        posicaoPaginaFilho = pagina->paginaEsquerda;
        for(i=0; i<pagina->quantidadeElementos; i++)
        {
            // chave < pagina->elementos[i].chave
            if(strncmp(chave,pagina->elementos[i].chave,TAM_CHAVE)<0)
            {
                break;
            }
            posicaoPaginaFilho = pagina->elementos[i].paginaDireita;
        }
        // Desce. Se o filho sofreu split, ele devolve o elemento que subiu.
        elementoSplit = ArvoreB_Insere_Recursiva(arvore,posicaoPaginaFilho,chave,posicaoRegistro);
        if(elementoSplit) // Raiz da subarvore do filho deu split
        {
            if(pagina->quantidadeElementos < TAM_PAG) // Elemento do split do filho cabe
            {
                // Insere o elemento promovido nesta página (copiando a struct
                // inteira, inclusive a paginaDireita) e reordena por chave.
                pagina->elementos[pagina->quantidadeElementos] = *elementoSplit;
                pagina->quantidadeElementos++;
                qsort(pagina->elementos,pagina->quantidadeElementos,sizeof(ArvoreB_Elemento),ArvoreB_Compara);
                fseek(arvore->f,posicaoPagina,SEEK_SET);
                fwrite(pagina,sizeof(ArvoreB_Pagina),1,arvore->f);
                free(elementoSplit);
            }
            else // ... não cabe
            {
                // Esta página também está cheia: split de novo, propagando para cima.
                resp = ArvoreB_Split(arvore, posicaoPagina, pagina, elementoSplit);
                free(elementoSplit);
            }
        }
    }
    ArvoreB_desalocaPagina(pagina);
    return resp;
}

// Insere uma chave e a posição do seu registro no arquivo de dados.
// Se o split chegar até a raiz, cria uma RAIZ NOVA: é assim que a árvore cresce
// em altura (sempre por cima, por isso todas as folhas ficam no mesmo nível).
void ArvoreB_Insere(ArvoreB* arvore, char chave[TAM_CHAVE], long posicaoRegistro )
{
    ArvoreB_Pagina *novaRaiz;
    ArvoreB_Elemento *elementoSplit;

    elementoSplit = ArvoreB_Insere_Recursiva(arvore, arvore->cabecalho->raiz, chave, posicaoRegistro);
    if(elementoSplit)
    {
        // A raiz antiga estourou. A raiz nova tem 1 elemento (o que subiu):
        //   paginaEsquerda    = raiz antiga (metade menor)
        //   paginaDireita     = página criada no split (metade maior)
        novaRaiz = ArvoreB_alocaPagina();
        novaRaiz->quantidadeElementos = 1;
        novaRaiz->elementos[0] = *elementoSplit;
        novaRaiz->paginaEsquerda = arvore->cabecalho->raiz;
        // Grava a raiz nova no fim do arquivo e atualiza o cabeçalho (RAM e disco).
        fseek(arvore->f, 0, SEEK_END);
        arvore->cabecalho->raiz = ftell(arvore->f);
        fwrite(novaRaiz,sizeof(ArvoreB_Pagina),1,arvore->f);
        ArvoreB_escreveCabecalho(arvore);
        ArvoreB_desalocaPagina(novaRaiz);
        free(elementoSplit);
    }
}

/* ================== Depuração ================== */

// Imprime todas as páginas na ORDEM FÍSICA do arquivo (não na ordem da árvore).
// Formato de cada linha:
//   [*] offset => paginaEsquerda |(chave)| paginaDireita |(chave)| paginaDireita ...
// O "*" marca a página raiz.
void ArvoreB_PrintDebug(ArvoreB* arvore)
{
    long posicaoPagina;
    int i;
    ArvoreB_Pagina *pagina = ArvoreB_alocaPagina();
    // Pula o cabeçalho e lê página por página até o fim do arquivo.
    fseek(arvore->f, sizeof(ArvoreB_Cabecalho), SEEK_SET);
    posicaoPagina = ftell(arvore->f);
    while(fread(pagina,sizeof(ArvoreB_Pagina),1,arvore->f))
    {
        if(posicaoPagina == arvore->cabecalho->raiz)
        {
            printf("* ");
        }
        else
        {
            printf("  ");
        }
        printf("%5ld => %5ld|",posicaoPagina, pagina->paginaEsquerda);
        for(i=0; i<pagina->quantidadeElementos; i++)
        {

            printf("(%.8s)|%5ld|",pagina->elementos[i].chave, pagina->elementos[i].paginaDireita);
        }
        printf("\n");
        posicaoPagina = ftell(arvore->f);
    }
}

/* ================== Busca ================== */

// Procura a chave na subárvore que começa em posicaoPagina.
// Devolve a posicaoRegistro (no arquivo de dados) ou -1 se não existir.
long ArvoreB_Busca_Recursiva(ArvoreB* arvore, long posicaoPagina, char chave[TAM_CHAVE])
{
    // Offset 0 = nulo: desceu além de uma folha, então a chave não existe.
    if(posicaoPagina == 0)
    {
        return -1;
    }
    // Lê a página (uma leitura de disco por nível).
    ArvoreB_Pagina *pagina = ArvoreB_alocaPagina();
    fseek(arvore->f, posicaoPagina, SEEK_SET);
    fread(pagina, sizeof(ArvoreB_Pagina),1,arvore->f);
    // Varre os elementos em ordem (busca linear, em RAM, é barata perto do disco).
    long posicaoPaginaFilho = pagina->paginaEsquerda;
    for(int i=0; i<pagina->quantidadeElementos; i++)
    {
        if(strncmp(chave,pagina->elementos[i].chave,TAM_CHAVE)==0)
        {
            // Achei
            long resp = pagina->elementos[i].posicaoRegistro;
            ArvoreB_desalocaPagina(pagina);
            return resp;
        }
        // Chave menor que a do elemento i: ela está no filho à esquerda dele,
        // que é o que já está em posicaoPaginaFilho.
        if(strncmp(chave,pagina->elementos[i].chave,TAM_CHAVE)<0)
        {
            break;
        }
        // Chave maior: o candidato passa a ser o filho à direita do elemento i.
        posicaoPaginaFilho = pagina->elementos[i].paginaDireita;
    }
    ArvoreB_desalocaPagina(pagina);
    // Desce para o filho escolhido. Numa folha esse filho é 0, e a chamada
    // devolve -1 (não achou).
    return ArvoreB_Busca_Recursiva(arvore, posicaoPaginaFilho, chave);
}

// Função pública: começa a busca pela raiz.
long ArvoreB_Busca(ArvoreB* arvore, char chave[TAM_CHAVE])
{
    return ArvoreB_Busca_Recursiva(arvore, arvore->cabecalho->raiz, chave);
}
