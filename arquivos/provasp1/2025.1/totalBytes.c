#include <stdio.h>

struct Pagamento{
    char cpf[12];
    char nome[80];
    int mes;
    int ano; 
    float valor;
};

typedef struct Pagamento Pagamento;

int main(){
    FILE *f = fopen("beneficios.dat", "rb");

    if(!f){
        fprintf(stderr, "Não foi possível abrir o arquivo %s.\n", "covid.dat");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long totalBytes = ftell(f);
    long totalRegistros = totalBytes / sizeof(Pagamento);

    printf("Tamanho total de bytes: %ld", totalBytes);
    printf("Total de registros: %ld", totalRegistros);

    fclose(f);

    return 0;
}