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

    Pagamento p;

    fseek(f, 4 * sizeof(Pagamento), SEEK_SET);
    fseek(f, 7 * sizeof(Pagamento), SEEK_SET);

    fread(&p, sizeof(Pagamento), 1, f);
    
     printf("CPF: %s - Valor; %f", p.cpf, p.valor);

    fseek(f, -3 * sizeof(Pagamento), SEEK_CUR);

    fread(&p, sizeof(Pagamento), 1, f);

    printf("CPF: %s - Valor; %f", p.nome, p.valor);

    fseek(f, -1 * sizeof(Pagamento), SEEK_END);

    fread(&p, sizeof(Pagamento), 1, f);
    
    printf("CPF: %s - Valor; %f", p.cpf, p.valor);
}