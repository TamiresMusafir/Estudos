#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};


/*
    Índice do CEP.

    Guarda:
    - cep      → o CEP do endereço
    - posicao  → onde esse endereço está no cep.dat
*/
struct indiceCep {
    char cep[8];
    long posicao;
};

typedef struct indiceCep IndiceCep;


/*
    Compara dois índices pelo CEP.
*/
int compara(const void *a, const void *b)
{
    return strncmp(
        ((IndiceCep*)a)->cep,
        ((IndiceCep*)b)->cep,
        8
    );
}


int main(int argc, char **argv)
{
    FILE *f;

    Endereco e;

    IndiceCep *indice;

    long tamanhoBytes;
    long qtd;
    long i;


    /*
        O programa recebe o CEP que queremos procurar.

        Exemplo:

        ./indice 22222222
    */
    if(argc != 2)
    {
        fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
        return 1;
    }


    /*
        Abre o arquivo original.
    */
    f = fopen("cep.dat", "rb");

    if(f == NULL)
    {
        fprintf(stderr, "Erro ao abrir cep.dat\n");
        return 1;
    }


    /*
        Vai para o final do arquivo para descobrir
        seu tamanho.
    */
    fseek(f, 0, SEEK_END);

    tamanhoBytes = ftell(f);


    /*
        Descobre quantos registros Endereco existem.
    */
    qtd = tamanhoBytes / sizeof(Endereco);


    /*
        Reserva memória para TODOS os elementos do índice.

        Cada elemento possui:

        char cep[8]
        long posicao
    */
    indice = malloc(qtd * sizeof(IndiceCep));

    if(indice == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria\n");
        fclose(f);
        return 1;
    }


    /*
        Voltamos para o início do arquivo.
    */
    rewind(f);


    /*
        Percorremos todos os registros do cep.dat.
    */
    for(i = 0; i < qtd; i++)
    {
        /*
            Lê um Endereco completo do arquivo
            e coloca dentro de e.
        */
        fread(&e, sizeof(Endereco), 1, f);


        /*
            Cria o índice correspondente:

            CEP do endereço
            +
            posição do endereço no arquivo
        */
        strncpy(indice[i].cep, e.cep, 8);

        indice[i].posicao = i;
    }


    /*
        Agora ordenamos o índice pelo CEP.

        Exemplo antes:

        30000000 → 0
        10000000 → 1
        50000000 → 2

        Depois:

        10000000 → 1
        30000000 → 0
        50000000 → 2
    */
    qsort(
        indice,
        qtd,
        sizeof(IndiceCep),
        compara
    );


    /*
        Agora fazemos a busca binária NO ÍNDICE.
    */

    long inicio = 0;
    long fim = qtd - 1;

    while(inicio <= fim)
    {
        long meio = (inicio + fim) / 2;


        /*
            Compara o CEP que o usuário passou
            com o CEP que está no meio do índice.
        */
        int resultado = strncmp(
            argv[1],
            indice[meio].cep,
            8
        );


        /*
            Encontrou!
        */
        if(resultado == 0)
        {
            /*
                O índice nos diz a posição
                do Endereco dentro do cep.dat.
            */
            long posicao = indice[meio].posicao;


            /*
                Agora vamos até essa posição
                dentro do arquivo original.
            */
            fseek(
                f,
                posicao * sizeof(Endereco),
                SEEK_SET
            );


            /*
                Lemos o Endereco completo.
            */
            fread(
                &e,
                sizeof(Endereco),
                1,
                f
            );


            /*
                Mostramos o resultado.
            */
            printf(
                "%.72s\n"
                "%.72s\n"
                "%.72s\n"
                "%.72s\n"
                "%.2s\n"
                "%.8s\n",
                e.logradouro,
                e.bairro,
                e.cidade,
                e.uf,
                e.sigla,
                e.cep
            );

            break;
        }


        /*
            CEP procurado é maior que o CEP do meio.

            Então procuramos na metade direita.
        */
        else if(resultado > 0)
        {
            inicio = meio + 1;
        }


        /*
            CEP procurado é menor.

            Então procuramos na metade esquerda.
        */
        else
        {
            fim = meio - 1;
        }
    }


    free(indice);
    fclose(f);

    return 0;
}
