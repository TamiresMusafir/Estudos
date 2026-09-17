#include <stdio.h>
#include <stdlib.h>

struct Pagamento{
    char cpf[12];
    char nome[80];
    int mes;
    int ano;
    float valor;
};

typedef struct Pagamento Pagamento;

//a
//duvida: como nao estamos usando a linha de comando diretamente, 
//preciso fazer int argc e argv? ou posso apenas deixar void na main?
int main(int argc, char **argv){
    FILE *f = fopen("beneficios.dat", "rb");

    if(!f){
        fprintf(stderr, "Não foi possível abrir o arquivo.");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long totalBytes = ftell(f);
    long totalRegistros = totalBytes / sizeof(Pagamento);

    //duvida: quando usar fprintf ou printf.
    fprintf(stdout, "O total de byte presentes no arquivo é: %ld", totalBytes);
    fprintf(stdout, "O total de registros presentes no arquivo é: %ld", totalRegistros);

    fclose(f);

    return 0;
}

// b
int main(int argc, char **argv){
    FILE *origem = fopen("novos.dat", "rb");
    //duvida: pode usar append?
    FILE *destino = fopen("beneficios.dat", "ab");

    if(!origem || !destino){
        fprintf(stderr, "Não foi possível abrir os arquivos");
        return 1;
    }

    Pagamento p;

    while(fread(&p, sizeof(Pagamento), 1, origem) == 1){
        fwrite(&p, sizeof(Pagamento), 1, destino);    
    }

    fclose(origem);
    fclose(destino);

    //ou

    FILE *origem = fopen("novos.dat", "rb");
    //duvida: pode usar r+b?
    FILE *destino = fopen("beneficios.dat", "r+b");

    if(!origem || !destino){
        fprintf(stderr, "Não foi possível abrir os arquivos");
        return 1;
    }

    fseek(destino, 0, SEEK_END);
 
    Pagamento p;

    while(fread(&p, sizeof(Pagamento), 1, origem) == 1){
        fwrite(&p, sizeof(Pagamento), 1, destino);
    }

    rewind(destino);

    fclose(origem);
    fclose(destino);

    return 0;
}

//c

float total_pago_mes_ano(int mes, int ano){
    FILE *f = fopen("beneficios.dat", "rb");
    Pagamento p;
    float total = 0;

    while(fread(&p, sizeof(Pagamento), 1, f) == 1){

        if (p.ano < ano || (p.ano == ano && p.mes < mes))
            continue;

        if(p.ano == ano && p.mes == mes){
            total += p.valor;
        }

        if(p.ano > ano || (p.ano == ano && p.mes > mes))
            break;
    }

    fclose(f);

    return total;
}

int main(int argc, char **argv){
    FILE *f = fopen("beneficiarios.dat", "rb");
    Pagamento p;

    float maiorValor, menorValor = 0;
    int anoAtual;

    while(fread(&p, sizeof(Pagamento), 1, f) == 1){
        anoAtual = p.ano;
        
        
    }

    fclose(f);
}