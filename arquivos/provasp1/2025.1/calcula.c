#include <stdio.h>

struct Pagamento{
    char cpf[12];
    char nome[80];
    int mes;
    int ano; 
    float valor;
};

float total_pago_mes_ano(int mes, int ano){
    FILE *f = fopen("beneficios.dat", "rb");
    Pagamento p;

    float soma = 0;

    while(fread(&p, sizeof(Pagamento), 1, f)){
        if(p.ano == ano && p.mes == mes){
            soma += p.valor;
        }else if(p.ano > ano || (p.ano == ano && p.mes > mes)){
            break;
        }
    }

    return soma;
}

int main(){

}