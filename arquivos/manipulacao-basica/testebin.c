#include <stdio.h>              // Biblioteca para manipulação de arquivos:
                                // FILE, fopen(), fwrite(), fclose(), etc.

#include <string.h>             // Biblioteca para manipulação de strings e memória:
                                // strcpy(), memset(), etc.

typedef struct _Pessoa Pessoa;  // Cria o apelido "Pessoa" para o tipo

struct _Pessoa {
    char nome[40];  // Vetor de caracteres para armazenar o nome da pessoa (até 39 caracteres + '\0')
    int idade;      // Idade da pessoa
    float altura;   // Altura da pessoa
};

int main(){
    FILE *f = fopen("saida.dat", "wb"); // Abre/cria o arquivo "saida.dat" para escrita em modo binário.
                                        // f representa o arquivo aberto.

    Pessoa p[1000];                     // Cria um ARRAY com espaço para 1000 pessoas.
                                        // Cada posição do array é uma struct Pessoa:
                                        // p[0] → Pessoa

    memset(p, 0, 1000 * sizeof(Pessoa));    // Preenche toda a memória ocupada pelo array com zeros.
                                            // p → endereço inicial do array
                                            // 0 → valor usado para preencher
                                            // 1000 * sizeof(Pessoa) → quantidade total de bytes que queremos zerar.
                                            // Depois disso, todas as 1000 Pessoas começam com seus bytes zerados.

    // p.nome = "Renato Mauro"; // Não podemos fazer isso. p é um ARRAY de Pessoa.
                                // Além disso, arrays de char não podem receber uma string usando = depois de criados.

    strcpy(p[0].nome, "Renato Mauro");  // Copia a string "Renato Mauro" para o campo nome da primeira Pessoa.
                                        // p[0] → primeira pessoa
                                        // p[0].nome → nome dessa pessoa
                                        // strcpy(destino, origem)

    p[0].idade = 51;                    // Coloca 51 no campo idade da primeira Pessoa.
    p[0].altura = 1.84;                 // Coloca 1.84 no campo altura da primeira Pessoa.

    fwrite(
            p,              // Endereço dos dados que queremos gravar.
                            // Como p é um array, representa o endereço do primeiro elemento.
            sizeof(Pessoa), // Tamanho de UMA Pessoa em bytes.
            1000,           // Quantidade de Pessoas que serão gravadas.
            f               // Arquivo onde os dados serão escritos.
    );
                            // Portanto:
                            //
                            // fwrite(p, sizeof(Pessoa), 1000, f);
                            //
                            // significa:
                            //
                            // "Grave 1000 estruturas Pessoa no arquivo f,
                            // cada uma ocupando sizeof(Pessoa) bytes."
                            //
                            // Mesmo que só tenhamos preenchido p[0],
                            // as outras 999 Pessoas também são gravadas.
                            //
                            // Como usamos memset(), essas outras posições
                            // estão zeradas.



    fclose(f);              // Fecha o arquivo depois de terminar a escrita.
    return 0;               // Programa terminou com sucesso.
}