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
    FILE *f = fopen("beneficios.dat", "ab");
    FILE *novo = fopen("novos.dat", "rb");

    if(!f || !novo){
        fprintf(stderr, "Não foi possível abrir o arquivo");
        return 1;
    }

    Pagamento p;

    while(fread(&p, sizeof(Pagamento), 1, novo) == 1){
        fwrite(&p, sizeof(Pagamento), 1, f);
    }

    fclose(f);
    fclose(novo);

    return 0;
}