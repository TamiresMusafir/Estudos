#include <stdio.h>

struct Pagamento{
    char cpf[12];
    char nome[80];
    int mes;
    int ano; 
    float valor;
};

int main(){
    FILE *f = fopen("beneficiarios.dat", "rb");
    Pagamento p;

    float maiorValor = 0;
    int anoAtual;

    while(fread(&p, sizeof(Pagamento), 1, f) == 1){
        anoAtual = p.ano;

        if(p.valor > maiorValor)
            maiorValor = p.valor;


        primeiro, pegar o ano. ir colocando no maior valor. 
        Ver qual foi o beneficiario desse valor e guardar
        imprimir
        fazer isso com cada ano
    }
}