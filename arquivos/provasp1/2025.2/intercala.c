#include <stdio.h>

struct COVID{
    int dia;
    int novos_casos;
    int obitos;
};

typedef struct COVID COVID;

int compara(const void *a, const void *b){
    return(((COVID *)a)->dia - ((COVID*)b)->dia);
}

void intercala(char *arqA, char *arqb, char *arqSaida){
    FILE *a, *b, *saida;
    COVID ea, eb, ec;

    a = fopen(arqA, "rb");
    b = fopen(arqSaida, "rb");
    saida = fopen(arqSaida, "wb");

    if(!a || !b || !saida)
        fprintf(stderr, "Não foi possível abrir o arquivo.");

    fread(&ea, sizeof(COVID), 1, a);
    fread(&eb, sizeof(COVID), 1, b);

    while(!feof(a) && !feof(b)){
        if(compara(&ea, &eb) < 0){
            fwrite(&ea, sizeof(COVID), 1, saida);
            fread(&ea, sizeof(COVID), 1, a);
        }else if(compara(&ea, &eb) == 0){
            ec.dia = ea.dia;
            ec.novos_casos = ea.novos_casos + eb.novos_casos;
            ec.obitos = ea.obitos + eb.obitos;
            fwrite(&ec, sizeof(COVID), 1, saida);
            fread(&ea, sizeof(COVID), 1, a);
            fread(&eb, sizeof(COVID), 1, b);
        }else{
            fwrite(&eb, sizeof(COVID), 1, saida);
            fread(&eb, sizeof(COVID), 1, b);
        }
    }

    while(!feof(a)){
        fwrite(&ea, sizeof(COVID), 1, saida);
        fread(&ea, sizeof(COVID), 1, a);
    }

    while(!feof(b)){
        fwrite(&eb, sizeof(COVID), 1, saida);
        fread(&eb, sizeof(COVID), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}

int main(){
    
}
