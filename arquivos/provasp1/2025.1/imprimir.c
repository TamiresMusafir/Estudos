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

    while(fread(&p, sizeof(Pagamento), 1, f) == 1){
        int anoAtual = p.ano;
        maior = p;
        menor = p;

        while(anoAtual == p.ano){
            if(p.valor > maior.valor)
                maior = p;
            if(p.valor < menor.valor)
                menor = p;
            fread(&p, sizeof(Pagamento), 1, f);
        }

        printf("Ano: %d", anoAtual);
        printf("Beneficiário com maior valor: %s %s %d %2.f\n", maior.cpf, maior.nome, maior.mes, maior.valor);
        printf("Beneficiário com menor valor: %s %s %d %2.f\n", menor.cpf, menor.nome, menor.mes, menor.valor);        
    }

    fclose(f);
    return 0;
}