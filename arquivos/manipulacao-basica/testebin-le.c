#include <stdio.h>              // Biblioteca para entrada/saída e manipulação de arquivos

typedef struct _Pessoa Pessoa;  // Cria o apelido "Pessoa" para struct _Pessoa.

struct _Pessoa {
    char nome[40];   // Guarda o nome da pessoa 40 posições: até 39 caracteres + '\0'
    int idade;       // Guarda a idade
    float altura;    // Guarda a altura
};

int main(){
    FILE *f = fopen("pessoas.dat", "rb");   // Abre o arquivo pessoas.dat para LEITURA em binário.
                                            // f representa o arquivo aberto.

    Pessoa p[1000];                         // Cria espaço na memória para 1000 registros Pessoa.
                                            // p[0]    → primeira pessoa
                                            // p[1]    → segunda pessoa

    // fread retorna QUANTOS registros conseguiu ler.
    // Se o arquivo tiver 1000 Pessoas: qt = 1000
    // Se tiver 300 Pessoas: qt = 300
    // Se o arquivo estiver vazio: qt = 0                                            
    int qt = fread(
                    p,              // Onde os registros lidos serão armazenados.
                                    // Como p é um array, corresponde ao endereço do primeiro elemento.
                    sizeof(Pessoa), // Tamanho de cada registro Pessoa em bytes.
                    1000,           // Quantidade máxima de registros que queremos ler.
                    f               // Arquivo de onde os registros serão lidos.
    );           

    printf("%d\n", qt);             // Mostra a quantidade de registros que foram lidos.

    printf("%s,%d,%f\n", p[0].nome, p[0].idade, p[0].altura);

    fclose(f);                      // Fecha o arquivo depois de terminar a leitura.

    return 0;                       // Programa terminou com sucesso.
}
