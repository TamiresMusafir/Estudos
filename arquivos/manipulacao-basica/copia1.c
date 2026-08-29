#include <stdio.h>         // Biblioteca padrão de entrada e saída; contém FILE, fopen, fclose, fgetc, fputc, fprintf etc.
// stdout, stdin, stderr   // Canais padrão: entrada (stdin), saída (stdout) e erro (stderr)

// argc = quantidade de argumentos; argv = vetor com os argumentos passados no terminal
int main(int argc, char** argv){
    FILE *entrada, *saida;  // Ponteiros FILE que representam os arquivos que serão abertos
                            // "entrada" será o arquivo que vamos LER
                            // "saida" será o arquivo que vamos ESCREVER

    int c;  // Variável que armazenará o caractere/byte lido pelo fgetc()
            // É int porque fgetc() também precisa conseguir retornar EOF (fim do arquivo)

    // Esperamos 3 argumentos: nome do programa + arquivo origem + arquivo destino
    if(argc != 3){
        fprintf(stderr,"Erro na chamada do comando.\n");
        // %s recebe argv[0], que é o nome usado para executar o programa
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
        return 1;    
    }                       

    entrada = fopen(argv[1],"rb");  // Abre o arquivo de origem para LEITURA em modo binário
                                    // argv[1] contém o nome do arquivo de origem

    // Se fopen() falhou, entrada recebe NULL                                    
    if(!entrada){
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;                      
    }

    saida = fopen(argv[2],"wb");    // Abre/cria o arquivo de destino para ESCRITA em modo binário
                                    // argv[2] contém o nome do arquivo de destino

    // Verifica se conseguiu abrir/criar o arquivo de destino                                    
    if(!saida){                              
        fclose(entrada);            // Como já abrimos "entrada", precisamos fechá-lo antes de sair
        fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
        return 1;     
    }

    c = fgetc(entrada); // Lê UM caractere/byte do arquivo de entrada
                        // O valor lido é colocado dentro de c
                        // Se não houver mais nada para ler, fgetc() retorna EOF

    // Enquanto NÃO chegarmos ao fim do arquivo...
    while(c != EOF){
        fputc(c, saida);    // Escreve o caractere/byte que está em c no arquivo de saída

        c = fgetc(entrada); // Lê o PRÓXIMO caractere/byte
                            // Depois volta para o while e verifica novamente se é EOF
    }

    fclose(entrada);    // Fecha o arquivo de entrada; terminamos de usá-lo
    fclose(saida);      // Fecha o arquivo de saída; terminamos de usá-lo

    return 0;           // Encerra o programa indicando que terminou com sucesso
}