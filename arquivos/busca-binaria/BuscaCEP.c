// BUSCA SEQUENCIAL EM ARQUIVO
// O programa lê os registros um por um, do início ao fim,
// até encontrar o CEP procurado.

#include <stdio.h>      // printf(), fprintf(), FILE, fopen(), fread(), fclose()
#include <string.h>     // strncmp()

typedef struct _Endereco Endereco;    // Cria o apelido "Endereco" para struct _Endereco

struct _Endereco{
    char logradouro[72];   // Armazena o logradouro
    char bairro[72];       // Armazena o bairro
    char cidade[72];       // Armazena a cidade
    char uf[72];           // Armazena a unidade federativa
    char sigla[2];         // Armazena a sigla
    char cep[8];           // Armazena o CEP
    char lixo[2];          // Espaço no final da linha + quebra de linha
};

int main(int argc, char** argv){
    FILE *f;               // Ponteiro que representa o arquivo aberto
    Endereco e;            // Cria UMA variável do tipo Endereco. Receberá cada registro lido do arquivo
    int qt;                // Guarda quantos elementos o fread conseguiu ler
    int c;                 // Conta quantos registros já foram lidos/analisados

    // Verifica se o usuário passou exatamente 1 argumento além do nome do programa.
    // Exemplo de execução: ./programa 01001000
    // argc = 2
    // argv[0] = "./programa"
    // argv[1] = "01001000"
    if(argc != 2){
        fprintf(stderr, "USO: %s [CEP]", argv[0]); // Mostra como o programa deve ser usado
        return 1;                                  // Encerra indicando erro
    }

    c = 0;  // Começamos com 0 registros lidos

    // Mostra quantos bytes uma estrutura Endereco ocupa na memória.
    // %ld → usado aqui para imprimir o tamanho retornado por sizeof().
    // Tecnicamente, o formato mais adequado para sizeof() é %zu.
    printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));

    // Abre o arquivo "cep.dat" para leitura.
    // "r" = read (leitura)
    // f passa a representar o arquivo aberto.
    f = fopen("cep.dat", "r");

    // Lê 1 registro do arquivo e coloca dentro da variável e.
    //
    // &e               → endereço de memória de e, onde os dados serão colocados
    // sizeof(Endereco) → tamanho de UMA estrutura Endereco
    // 1                → quantidade de estruturas que queremos ler
    // f                → arquivo de onde vamos ler
    //
    // fread retorna quantos elementos conseguiu ler.
    //
    // Se conseguiu ler 1 Endereco:
    // qt = 1
    //
    // Se não conseguiu ler:
    // qt = 0
    qt = fread(&e, sizeof(Endereco), 1, f);

    // Enquanto conseguimos ler pelo menos 1 registro...
    // qt > 0 significa que o fread conseguiu ler um registro.
    while(qt > 0){
        c++;  // Conta mais um registro que foi lido/analisado

        // Compara o CEP informado pelo usuário (argv[1]) com o CEP do registro que acabamos de ler (e.cep).
        // strncmp(..., 8) compara os 8 primeiros caracteres.
        // == 0 significa que os dois CEPs são iguais.
		// Encontramos o CEP!
        if(strncmp(argv[1], e.cep, 8) == 0){
            
            // %.72s → imprime no máximo 72 caracteres
            // %.2s  → imprime no máximo 2 caracteres
            // %.8s  → imprime no máximo 8 caracteres
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", e.logradouro, e.bairro,e.cidade, e.uf, e.sigla, e.cep             );

            break;  // Para a busca porque já encontramos o CEP
        }

        // Se não encontrou o CEP: Lê o PRÓXIMO registro do arquivo e coloca novamente em e.
        // O arquivo já avançou automaticamente depois do fread anterior.
        //
        // Então agora:
        // e = próximo registro
        // qt = 1 → conseguiu ler
        // qt = 0 → chegou ao fim do arquivo
        qt = fread(&e, sizeof(Endereco), 1, f);
    }

    // Mostra quantos registros foram lidos/analisados.
    // Se encontrou o CEP no registro 500: c = 500
    // Se percorreu o arquivo inteiro: c = quantidade total de registros.
    printf("Total Lido: %d\n", c);

    // Fecha o arquivo depois que terminamos de utilizá-lo.
    fclose(f);

    // Encerra o programa.
    return 0;
}
