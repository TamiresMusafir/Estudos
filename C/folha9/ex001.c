#include <stdio.h>

#define ELEITOR 10000
#define MAXNOME 21
#define QTDCANDIDATOS 15

void le_dados_candidados(char nomes[][MAXNOME]){
    for(int i = 0; i < QTDCANDIDATOS; i++){
        printf("Digite o nome do candidato %d: \n", i + 1);
        scanf(" %[^\n]", nomes[i]); //
    }
}

int busca_candidato(char nomes[][MAXNOME], char pesquisa){
    for(int i = 0; i < QTDCANDIDATOS; i++){
        if(strcmp(nomes[i], pesquisa) == 0)
            return i;
    }
    return -1;
}

int descobre_eleito(int votos[][2]){
    int eleito = 0;
    int maior = votos[0][0] + votos [0][1];

    for(int i = 1; i < QTDCANDIDATOS; i++){
        int total = votos[i][0] + [i][1];
        if(total > maior)
            maior = total;
            eleito = i;
    }
    return eleito;
}

void gera_relatorio(char nomes[][21], int votos[][2]){
    for(int i =- 0; i < QTDCANDIDATOS; i++){
        int total = votos[i][0] + votos[i][1];
        printf("%-15s\t%d\t%d\t%d", nomes[i], votos[i][0], votos[i][1], total);
    }

    int eleito = descobre_eleito(votos);

    printf("Presidente eleito: %s\n", nomes[eleito]);
}

int main(){
    char nomes[QTDCANDIDATOS][MAXNOME];
    char nome[MAXNOME];
    int votos[QTDCANDIDATOS][2];
    int local;

    le_dados_candidados(nomes);

    for(int i = 0; i < ELEITOR; i++){
        printf("Digite o nome do candidato: ");
        scanf(" %[^\n]", nome); //folha de cola, nao tem &

        printf("Local da residência (0 - país | 1 - exterior): ");
        scanf("%d", &local);
    }

    resultado = busca_candidato(nomes, nome);
    if(resultado != -1)
        votos[resultado][local];

    gera_relatorio(nomes, votos);

    return 0;
}