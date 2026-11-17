#include <stdio.h>

#define MAX 256                     // quantos valores um byte pode ter (2^8 = 256, de 0 a 255)

/* Conta quantas vezes cada byte aparece em um arquivo (a "tabela de frequências").
   É o PASSO 1 do Huffman: sem as frequências não dá para montar a árvore.
   Uso:  ./frequencias arquivo > resultado.txt     (o resultado alimenta histograma.py) */
int main(int argc, char** argv){
    FILE *entrada;
    int c;                          // int (e não char) porque fgetc devolve 0..255 OU EOF (-1)
    int total = 0;                  // total de bytes lidos = soma de todas as frequências
    int count[MAX] = {0};           // count[b] = frequência do byte b; começa tudo zerado

    // argc = nº de argumentos; precisa de exatamente 2: o nome do programa e o arquivo
    if(argc != 2){
        fprintf(stderr,"Erro na chamada do comando.\n");
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);   // argv[0] = nome do programa
        return 1;                   // erros vão para stderr, para não misturar com a tabela impressa
    }

    entrada = fopen(argv[1],"rb");  // "rb" = leitura em modo binário: lê qualquer tipo de arquivo, byte a byte

    if(!entrada){                   // fopen devolve NULL se não conseguiu abrir
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    c = fgetc(entrada);             // lê 1 byte (devolve EOF no fim do arquivo)

    while(c != EOF){
        count[c]++;                 // o valor do byte é o próprio índice do vetor
        total++;
        c = fgetc(entrada);         // próximo byte
    }

    // imprime "byte: frequência", uma linha por valor possível (inclusive os com 0)
    for(int i = 0; i < MAX; i++){
        printf("%d: %d\n", i, count[i]);
    }

    printf("Total de impressões: %d\n", total);   // esta linha o histograma.py ignora

    fclose(entrada);
    return 0;                       // 0 = terminou sem erro
}
