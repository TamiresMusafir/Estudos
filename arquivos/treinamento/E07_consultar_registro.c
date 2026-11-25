//Crie o programa registro que recebe o arquivo e um número n (o primeiro registro é o de número 1) e imprime logradouro | cep desse registro. Use fseek.

#include <stdio.h>
#include <stdlib.h>

struct Endereco{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int main(int argc, char** argv){
    FILE *arquivo;
    Endereco posicao;

    if(argc != 3){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM] [NÚMERO].\n", argv[0]);
        return 1;
    }

    arquivo = fopen(argv[1], "rb");

    if(!arquivo){
        fprintf(stderr, "Não foi possível abrir o arquivo");
        return 1;
    }

    int numero = atoi(argv[2]);

    if(numero >= 1){
        fseek(arquivo, (numero-1) * sizeof(Endereco), SEEK_SET);

        if(fread(&posicao, sizeof(Endereco), 1, arquivo) == 1)
            printf("%.72s | %.8s\n", posicao.logradouro, posicao.cep);
        else{
            fprintf(stderr, "Não foi possível ler nenhum registro.\n");
            fclose(arquivo);
            return 1;
        }
    }else{
        fprintf(stderr, "Número inválido. Digite um número maior ou igual a 1.\n");
        fclose(arquivo);
        return 1;
    }

    fclose(arquivo);
    return 0;
}