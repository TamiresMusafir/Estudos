#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};


/*
    O índice guarda somente:

    CEP      → posição do registro no arquivo

    Exemplo:

    22222222 → 534821
*/
typedef struct _Indice Indice;

struct _Indice{
    char cep[8];
    long posicao;
};


/*
    Compara dois índices pelo CEP.

    O qsort() chama essa função para saber
    qual CEP vem primeiro.
*/
int compara(const void *a, const void *b)
{
    return strncmp(
        ((Indice*)a)->cep,
        ((Indice*)b)->cep,
        8
    );
}


int main(int argc, char **argv)
{
    FILE *f;
    FILE *indiceArquivo;

    Endereco e;

    Indice *indice;

    long tamanhoBytes;
    long qtd;
    long i;


    /*
        O programa espera:

        ./indice 22222222

        argv[1] = CEP procurado
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
        Vai para o final para descobrir
        o tamanho do arquivo.
    */
    fseek(f, 0, SEEK_END);

    tamanhoBytes = ftell(f);


    /*
        Descobre quantos Enderecos existem.
    */
    qtd = tamanhoBytes / sizeof(Endereco);


    /*
        Reserva memória para o índice.

        Não estamos reservando memória para Endereco.

        Estamos reservando memória para:

        CEP + posição
        CEP + posição
        CEP + posição
        ...
    */
    indice = malloc(qtd * sizeof(Indice));

    if(indice == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria\n");
        fclose(f);
        return 1;
    }


    /*
        Voltamos para o começo do arquivo.
    */
    rewind(f);


    /*
        Percorremos todos os Enderecos do arquivo.
    */
    for(i = 0; i < qtd; i++)
    {
        /*
            Lê um Endereco completo.
        */
        fread(&e, sizeof(Endereco), 1, f);


        /*
            Coloca no índice:

            o CEP do Endereco
            +
            a posição dele no arquivo
        */
        strncpy(indice[i].cep, e.cep, 8);

        indice[i].posicao = i;
    }


    /*
        Agora temos algo como:

        30000000 → 0
        10000000 → 1
        50000000 → 2
        20000000 → 3

        Vamos ordenar pelo CEP.
    */
    qsort(
        indice,
        qtd,
        sizeof(Indice),
        compara
    );


    /*
        Cria o arquivo do índice.
    */
    indiceArquivo = fopen("indice.dat", "wb");

    if(indiceArquivo == NULL)
    {
        fprintf(stderr, "Erro ao criar indice.dat\n");

        free(indice);
        fclose(f);

        return 1;
    }


    /*
        Salva o índice no arquivo.

        Memória → indice.dat
    */
    fwrite(
        indice,
        sizeof(Indice),
        qtd,
        indiceArquivo
    );

    fclose(indiceArquivo);


    /*
        Agora fazemos a busca binária
        pelo CEP informado pelo usuário.

        A busca é feita NO ÍNDICE,
        e não diretamente nos Enderecos.
    */

    long inicio = 0;
    long fim = qtd - 1;

    while(inicio <= fim)
    {
        long meio = (inicio + fim) / 2;


        /*
            Verifica o CEP que está no meio do índice.
        */
        int comparacao = strncmp(
            argv[1],
            indice[meio].cep,
            8
        );


        /*
            Encontrou o CEP!
        */
        if(comparacao == 0)
        {
            /*
                O índice nos diz onde está
                o Endereco dentro do cep.dat.
            */
            long posicao = indice[meio].posicao;


            /*
                Voltamos ao cep.dat.

                Vamos para a posição encontrada
                pelo índice.
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
                Mostramos o endereço.
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
            CEP procurado é maior.

            Então procuramos na metade direita.
        */
        else if(comparacao > 0)
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


    /*
        Libera a memória do índice.
    */
    free(indice);

    fclose(f);

    return 0;
}
