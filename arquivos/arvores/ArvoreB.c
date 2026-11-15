#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ArvoreB.h"

// Convenções deste arquivo:
//  - todo "ponteiro" da árvore é um offset (posição em bytes) dentro do arquivo
//  - offset 0 = nulo (lá fica o cabeçalho, então nenhuma página começa nele)
//  - uma página é folha quando paginaEsquerda == 0
//  - página nova é sempre gravada no fim do arquivo
//  - a chave tem 8 bytes e NÃO tem '\0' no final: comparar sempre com strncmp

// --- 1. PÁGINAS NA MEMÓRIA ---

// Cria uma página vazia na RAM, com tudo zerado
ArvoreB_Pagina* ArvoreB_alocaPagina()
{
    int i;
    ArvoreB_Pagina* resp = (ArvoreB_Pagina*) malloc(sizeof(ArvoreB_Pagina)); // reserva a página na RAM (vem com lixo)
    resp->quantidadeElementos = 0;  // nenhum elemento em uso
    resp->paginaEsquerda = 0;       // sem filho esquerdo: nasce como folha
    for(i=0; i<TAM_PAG; i++)        // zera as 300 posições, para não gravar lixo no arquivo
    {
        memset(resp->elementos[i].chave,'\0',TAM_CHAVE);  // chave vazia (8 bytes zero)
        resp->elementos[i].paginaDireita = 0;             // sem filho à direita
        resp->elementos[i].posicaoRegistro = 0;           // sem registro
    }
    return resp;
}

// Libera a página da RAM (não mexe no arquivo)
void ArvoreB_desalocaPagina(ArvoreB_Pagina* p)
{
    if(p)
    {
        free(p);
    }
}

// --- 2. ABRIR, COMPARAR E FECHAR ---

// Abre o arquivo de índice; se não existir, cria com cabeçalho + uma raiz vazia
ArvoreB* ArvoreB_Abre(const char* nomeArquivo)
{
    ArvoreB* resp = (ArvoreB*) 0;
    ArvoreB_Cabecalho* cabecalho = (ArvoreB_Cabecalho*) 0;
    ArvoreB_Pagina* raiz = (ArvoreB_Pagina*) 0;
    FILE* f = fopen(nomeArquivo, "rb");     // tenta abrir só para ver se o arquivo já existe
    if(!f)                                  // não existe: cria
    {
        f = fopen(nomeArquivo,"wb");
        if(!f)
        {
            fprintf(stderr,"Arquivo %s não pode ser criado\n", nomeArquivo);
            return resp;                    // falhou: devolve NULL
        }
        cabecalho = (ArvoreB_Cabecalho*) malloc(sizeof(ArvoreB_Cabecalho));
        cabecalho->raiz = sizeof(ArvoreB_Cabecalho);        // a raiz fica logo depois do cabeçalho (offset 8)
        fwrite(cabecalho,sizeof(ArvoreB_Cabecalho),1,f);    // grava o cabeçalho no início do arquivo
        raiz = ArvoreB_alocaPagina();
        fwrite(raiz,sizeof(ArvoreB_Pagina),1,f);            // grava a primeira página (vazia, folha)
        ArvoreB_desalocaPagina(raiz);
        free(cabecalho);
    }
    fclose(f);
    f = fopen(nomeArquivo, "rb+");          // reabre para leitura e escrita, sem apagar nada
    resp = (ArvoreB*) malloc(sizeof(ArvoreB));
    resp->f = f;                            // guarda o arquivo aberto
    resp->cabecalho = (ArvoreB_Cabecalho*) malloc(sizeof(ArvoreB_Cabecalho));
    fread(resp->cabecalho,sizeof(ArvoreB_Cabecalho),1,f);   // carrega o cabeçalho do arquivo para a RAM
    return resp;
}

// Compara dois elementos pela chave (usada pelo qsort para ordenar)
int ArvoreB_Compara(const void *e1, const void* e2)
{
    return strncmp(((ArvoreB_Elemento*)e1)->chave,((ArvoreB_Elemento*)e2)->chave,TAM_CHAVE);
}

// Grava o cabeçalho (da RAM) no início do arquivo; chamar sempre que a raiz mudar
void ArvoreB_escreveCabecalho(ArvoreB* arvore)
{
    fseek(arvore->f, 0, SEEK_SET);          // vai para o byte 0
    fwrite(arvore->cabecalho, sizeof(ArvoreB_Cabecalho), 1, arvore->f);
}

// Salva o cabeçalho, fecha o arquivo e libera a memória
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

// --- 3. INSERÇÃO ---

// Divide uma página CHEIA que recebeu mais um elemento (o "overflow").
// A página original fica com a metade menor, uma página nova (no fim do arquivo)
// fica com a metade maior, e o elemento do meio sobe: é ele que a função devolve,
// já apontando (paginaDireita) para a página nova. Quem chamou insere no pai e dá free.
//
// Exemplo com TAM_PAG = 3: página [10 20 30], overflow = 25
//   1. troca o 25 com o 30 e reordena      => página [10 20 25], overflow = 30
//   2. página nova recebe o 25 e o 30      => [25 30]
//   3. página original fica só com o 10    => [10]
//   4. o 20 (meio) sobe para o pai         => [10]  20  [25 30]
ArvoreB_Elemento* ArvoreB_Split(ArvoreB *arvore, long posicaoPagina, ArvoreB_Pagina* pagina, ArvoreB_Elemento* overflow)
{
    int i;
    ArvoreB_Elemento aux;
    ArvoreB_Elemento* resp;
    ArvoreB_Pagina* paginaSplit;
    // 1. Garante que o overflow seja o maior de todos
    // O elemento na área de overflow é menor que o ultimo elemento da página?
    if(ArvoreB_Compara(overflow,&pagina->elementos[pagina->quantidadeElementos-1])<0)
    {
        // Trocar o último com o elemento no overflow e reordenar a página.
        aux = *overflow;
        *overflow = pagina->elementos[pagina->quantidadeElementos-1];
        pagina->elementos[pagina->quantidadeElementos-1] = aux;
        qsort(pagina->elementos,pagina->quantidadeElementos,sizeof(ArvoreB_Elemento),ArvoreB_Compara);
    }
    // 2. Cria a página nova com a metade maior (depois do meio) + o overflow
    paginaSplit = ArvoreB_alocaPagina();
    for(i=TAM_PAG/2+1;i<TAM_PAG;i++)
    {
        paginaSplit->elementos[paginaSplit->quantidadeElementos] = pagina->elementos[i];
        paginaSplit->quantidadeElementos++;
    }
    paginaSplit->elementos[paginaSplit->quantidadeElementos] = *overflow;
    paginaSplit->quantidadeElementos++;
    // 3. A página original fica com a metade menor e é regravada no mesmo lugar
    //    (o elemento do meio continua no vetor, mas fora da contagem: é ignorado)
    pagina->quantidadeElementos = TAM_PAG/2;
    fseek(arvore->f, posicaoPagina, SEEK_SET);
    fwrite(pagina, sizeof(ArvoreB_Pagina),1,arvore->f);
    // 4. Monta o elemento do meio, que vai subir
    resp = (ArvoreB_Elemento*) malloc(sizeof(ArvoreB_Elemento));
    paginaSplit->paginaEsquerda = pagina->elementos[TAM_PAG/2].paginaDireita;   // o filho à direita do meio vira o filho esquerdo da página nova
    memcpy(resp->chave,pagina->elementos[TAM_PAG/2].chave,TAM_CHAVE);           // copia a chave do meio
    resp->posicaoRegistro = pagina->elementos[TAM_PAG/2].posicaoRegistro;       // e a posição do registro
    fseek(arvore->f,0,SEEK_END);                    // vai para o fim do arquivo
    resp->paginaDireita = ftell(arvore->f);         // o offset do fim é onde a página nova vai ficar
    fwrite(paginaSplit, sizeof(ArvoreB_Pagina),1,arvore->f);    // grava a página nova no fim
    ArvoreB_desalocaPagina(paginaSplit);
    return resp;
}

// Insere a chave na subárvore que começa em posicaoPagina (desce recursivamente).
// Devolve NULL se não precisa subir nada, ou o elemento que o pai deve inserir
// (quando esta página estourou e sofreu split)
ArvoreB_Elemento* ArvoreB_Insere_Recursiva(ArvoreB* arvore, long posicaoPagina, char chave[TAM_CHAVE], long posicaoRegistro)
{
    int i;
    long posicaoPaginaFilho;
//    ArvoreB_Elemento* resp = NULL;
    ArvoreB_Elemento* resp = (ArvoreB_Elemento*) 0;
    ArvoreB_Elemento *elementoSplit = (ArvoreB_Elemento*) 0;
    ArvoreB_Elemento overflow;
    // printf("Inserindo %.8s na página %ld\n", chave, posicaoPagina);
    ArvoreB_Pagina *pagina = ArvoreB_alocaPagina();
    fseek(arvore->f, posicaoPagina, SEEK_SET);
    fread(pagina, sizeof(ArvoreB_Pagina),1,arvore->f);      // lê a página atual do disco
    if(pagina->paginaEsquerda == 0) // Folha
    {
        if(pagina->quantidadeElementos < TAM_PAG) // Cabe na folha
        {
            // Coloca no fim do vetor, reordena e grava a página de volta
            memcpy(pagina->elementos[pagina->quantidadeElementos].chave,chave,TAM_CHAVE);
            pagina->elementos[pagina->quantidadeElementos].posicaoRegistro = posicaoRegistro;
            pagina->quantidadeElementos++;
            qsort(pagina->elementos,pagina->quantidadeElementos,sizeof(ArvoreB_Elemento),ArvoreB_Compara);
            fseek(arvore->f, posicaoPagina, SEEK_SET);
            fwrite(pagina, sizeof(ArvoreB_Pagina),1,arvore->f);
        }
        else // Não cabe na folha
        {
            // Folha cheia: o elemento novo vira overflow e a folha sofre split
            memcpy(overflow.chave, chave, TAM_CHAVE);
            overflow.posicaoRegistro = posicaoRegistro;
            overflow.paginaDireita = 0;
            resp = ArvoreB_Split(arvore, posicaoPagina, pagina, &overflow);
        }
    }
    else // Não é folha
    {
        // Escolhe o filho por onde descer: o primeiro à direita do último elemento menor ou igual à chave
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
        // Desce; se o filho sofreu split, devolve o elemento que subiu
        elementoSplit = ArvoreB_Insere_Recursiva(arvore,posicaoPaginaFilho,chave,posicaoRegistro);
        if(elementoSplit) // Raiz da subarvore do filho deu split
        {
            if(pagina->quantidadeElementos < TAM_PAG) // Elemento do split do filho cabe
            {
                // Insere o elemento que subiu nesta página, reordena e grava
                pagina->elementos[pagina->quantidadeElementos] = *elementoSplit;
                pagina->quantidadeElementos++;
                qsort(pagina->elementos,pagina->quantidadeElementos,sizeof(ArvoreB_Elemento),ArvoreB_Compara);
                fseek(arvore->f,posicaoPagina,SEEK_SET);
                fwrite(pagina,sizeof(ArvoreB_Pagina),1,arvore->f);
                free(elementoSplit);
            }
            else // ... não cabe
            {
                // Esta página também está cheia: split de novo, subindo mais um nível
                resp = ArvoreB_Split(arvore, posicaoPagina, pagina, elementoSplit);
                free(elementoSplit);
            }
        }
    }
    ArvoreB_desalocaPagina(pagina);
    return resp;
}

// Insere uma chave e a posição do seu registro no arquivo de dados.
// Se o split chegar até a raiz, cria uma raiz nova (a árvore cresce em altura)
void ArvoreB_Insere(ArvoreB* arvore, char chave[TAM_CHAVE], long posicaoRegistro )
{
    ArvoreB_Pagina *novaRaiz;
    ArvoreB_Elemento *elementoSplit;

    // Começa a descida pela raiz (o offset dela está no cabeçalho)
    elementoSplit = ArvoreB_Insere_Recursiva(arvore, arvore->cabecalho->raiz, chave, posicaoRegistro);
    if(elementoSplit)       // a raiz estourou
    {
        // Raiz nova com 1 elemento (o que subiu): esquerda = raiz antiga, direita = página criada no split
        novaRaiz = ArvoreB_alocaPagina();
        novaRaiz->quantidadeElementos = 1;
        novaRaiz->elementos[0] = *elementoSplit;
        novaRaiz->paginaEsquerda = arvore->cabecalho->raiz;
        fseek(arvore->f, 0, SEEK_END);                  // grava a raiz nova no fim do arquivo
        arvore->cabecalho->raiz = ftell(arvore->f);     // e o cabeçalho passa a apontar para ela
        fwrite(novaRaiz,sizeof(ArvoreB_Pagina),1,arvore->f);
        ArvoreB_escreveCabecalho(arvore);
        ArvoreB_desalocaPagina(novaRaiz);
        free(elementoSplit);
    }
}

// --- 4. DEPURAÇÃO ---

// Imprime as páginas na ordem em que estão no arquivo; "*" marca a raiz.
// Cada linha: offset => paginaEsquerda |(chave)| paginaDireita |(chave)| paginaDireita ...
void ArvoreB_PrintDebug(ArvoreB* arvore)
{
    long posicaoPagina;
    int i;
    ArvoreB_Pagina *pagina = ArvoreB_alocaPagina();
    fseek(arvore->f, sizeof(ArvoreB_Cabecalho), SEEK_SET);  // pula o cabeçalho
    posicaoPagina = ftell(arvore->f);
    while(fread(pagina,sizeof(ArvoreB_Pagina),1,arvore->f)) // lê uma página por volta, até o fim do arquivo
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

// --- 5. BUSCA ---

// Procura a chave na subárvore que começa em posicaoPagina.
// Devolve a posição do registro no arquivo de dados, ou -1 se não existir
long ArvoreB_Busca_Recursiva(ArvoreB* arvore, long posicaoPagina, char chave[TAM_CHAVE])
{
    if(posicaoPagina == 0)      // desceu além de uma folha: não existe
    {
        return -1;
    }
    ArvoreB_Pagina *pagina = ArvoreB_alocaPagina();
    fseek(arvore->f, posicaoPagina, SEEK_SET);
    fread(pagina, sizeof(ArvoreB_Pagina),1,arvore->f);      // lê a página do disco
    long posicaoPaginaFilho = pagina->paginaEsquerda;       // filho candidato (começa no mais à esquerda)
    for(int i=0; i<pagina->quantidadeElementos; i++)
    {
        if(strncmp(chave,pagina->elementos[i].chave,TAM_CHAVE)==0)
        {
            // Achei
            long resp = pagina->elementos[i].posicaoRegistro;
            ArvoreB_desalocaPagina(pagina);
            return resp;
        }
        if(strncmp(chave,pagina->elementos[i].chave,TAM_CHAVE)<0)
        {
            break;              // a chave é menor: o candidato atual é o filho certo
        }
        posicaoPaginaFilho = pagina->elementos[i].paginaDireita;    // a chave é maior: candidato passa a ser o filho à direita
    }
    ArvoreB_desalocaPagina(pagina);
    return ArvoreB_Busca_Recursiva(arvore, posicaoPaginaFilho, chave);  // desce para o filho escolhido
}

// Busca uma chave na árvore (começa pela raiz)
long ArvoreB_Busca(ArvoreB* arvore, char chave[TAM_CHAVE])
{
    return ArvoreB_Busca_Recursiva(arvore, arvore->cabecalho->raiz, chave);
}
