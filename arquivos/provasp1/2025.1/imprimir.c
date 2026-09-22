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
    FILE *f = fopen("beneficiarios.dat", "rb");
    Pagamento p, maior, menor;

    int anoAtual = p.ano;

    while(fread(&p, sizeof(Pagamento), 1, f) == 1){
        if(anoAtual == p.ano){
            maior = p;
            menor = p;

            
        }
    }
}