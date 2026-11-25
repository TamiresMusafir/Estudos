// Crie a função long contaRegistros(FILE *f), que descobre quantos registros o arquivo tem sem ler nenhum registro (use fseek, ftell e rewind). Crie o programa info que a usa e imprime três linhas: registros: N, primeiro: CEP e ultimo: CEP.

#include <stdio.h>

struct Endereco{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

typedef struct Endereco Endereco;

long contaRegistros(FILE *f){

    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    rewind(f);
    
    long registros = tamanho / sizeof(Endereco);

    return registros;
}

int main(int argc, char** argv){
    FILE *arquivo;
    Endereco primeiro, ultimo;

    if(argc != 2){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
        return 1;
    }

    arquivo = fopen(argv[1], "rb");

    if(!arquivo){
        fprintf(stderr, "Não foi possível abrir o arquivo");
        return 1;
    }

    long registros = contaRegistros(arquivo);

    if(registros == 0){
        fprintf(stderr, "Sem registros no arquivo.\n");
        fclose(arquivo);
        return 1;
    }

    fread(&primeiro, sizeof(Endereco), 1, arquivo);

    fseek(arquivo, -1 * sizeof(Endereco), SEEK_END);

    fread(&ultimo, sizeof(Endereco), 1, arquivo);

    printf("Quantidade de Registros: %ld\n", registros);
    printf("Primeiro cep: %.8s\n", primeiro.cep);
    printf("Último cep: %.8s\n", ultimo.cep);

    fclose(arquivo);

    return 0;
}
