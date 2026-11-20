#include <stdio.h>               // Biblioteca que permite usar printf()

int main(int argc, char** argv){
    // argc = "argument count"
    // É a QUANTIDADE de argumentos passados pela linha de comando.
    //
    // Importante: o próprio nome do programa conta como argumento.
    //
    // Exemplo:
    //
    // ./programa arquivo.txt saida.txt
    //
    // argc = 3

    // argv = "argument vector"
    // É um ARRAY de strings contendo os argumentos.
    //
    // argv[0] → nome do programa
    // argv[1] → primeiro argumento informado
    // argv[2] → segundo argumento informado
    // ...
    //
    // Por isso argv é usado como:
    // argv[1], argv[2], etc.

    // Percorre todos os argumentos
    for(int i = 0; i < argc; i++){
        printf(
            "argumento %d = %s\n",
            i,                     // Número/posição do argumento
            argv[i]                // Texto armazenado naquela posição
        );
    }

    return 0;                      // Programa terminou com sucesso
}