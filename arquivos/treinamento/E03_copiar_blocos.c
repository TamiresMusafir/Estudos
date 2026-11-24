// Crie copiablocos, igual ao E2, mas com fread/fwrite e um buffer de 8192 bytes. Cuidado com o último bloco, que quase nunca tem 8192 bytes: grave só o que o fread devolveu.

#include <stdio.h>

#define MAX 8192

int main(int argc, char** argv){
    FILE *entrada, *saida;
    char buffer[MAX] = {0};
    int qtd;
    
     if(argc != 3){
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");

    if(!entrada){
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    saida = fopen(argv[2], "wb");

    if(!saida){
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", argv[2]);
        fclose(entrada);
        return 1;
    }

    qtd = fread(buffer, 1, sizeof(buffer), entrada);

    while(qtd > 0){
        fwrite(buffer, 1, qtd, saida);
        qtd = fread(buffer, 1, sizeof(buffer), entrada);
    }

    fclose(entrada);            
    fclose(saida);                

    return 0; 
}
