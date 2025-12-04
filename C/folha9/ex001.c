#include <stdio.h>

#define ELEITOR 10000
#define MAXNOME 21
#define QTDCANDIDATOS

void le_dados_candidados(char nomes[]){
    for(int i = 0; i < QTDCANDIDATOS; i++){
        printf("Digite o nome do candidato %d: \n", i + 1);
        scanf(" %[^\n]", nomes[i]);
    }
}

int busca_candidato(){
    
}

int descobre_eleito(int votos[][2]){

}

void gera_relatorio(){

}

int main(){

}