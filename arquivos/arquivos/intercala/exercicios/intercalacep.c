#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARTES 8

typedef struct _Endereco Endereco;

struct _Endereco
{
 char logradouro[72];
 char bairro[72];
 char cidade[72];
 char uf[72];
 char sigla[2];
 char cep[8];
 char lixo[2];
};

int compara(const void *e1, const void *e2){
 return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int IntercalaArquivos(char e1[],char e2[], char s[]){
    Endereco ea, eb;
    FILE *a = fopen(e1, "rb");
    FILE *b = fopen(e2, "rb");
    FILE *saida = fopen(s, "wb");  

    if(!a || !b || !saida){
        fprintf(stderr, "arquivo nao pode ser aberto.\n");
        return 1;  
    }

    fread(&ea,sizeof(Endereco),1,a);
    fread(&eb,sizeof(Endereco),1,b);

    while(!feof(a) && !feof(b)){
        if(compara(&ea,&eb)<0){ // ea < eb
            fwrite(&ea,sizeof(Endereco),1,saida);
            fread(&ea,sizeof(Endereco),1,a);
        }else{ // ea >= eb
            fwrite(&eb,sizeof(Endereco),1,saida);
            fread(&eb,sizeof(Endereco),1,b);
        }
    }

    while(!feof(a)){
        fwrite(&ea,sizeof(Endereco),1,saida);
        fread(&ea,sizeof(Endereco),1,a); 
    }

    while(!feof(b)){
        fwrite(&eb,sizeof(Endereco),1,saida);
        fread(&eb,sizeof(Endereco),1,b); 
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}

int main(int argc, char** argv){
 char nome[80] = {0};
 FILE *f = fopen("cep.dat", "rb");

    if(!f){
        fprintf(stderr, "Erro ao abrir cep.dat\n");
        return 1;
    }

 fseek(f, 0, SEEK_END);
 int tamnahoArquivo = ftell(f);
 int qtdTotal = tamnahoArquivo/sizeof(Endereco);
 int qtdPartes = qtdTotal / PARTES;
 int resto = qtdTotal%PARTES;
 rewind(f);

 Endereco e = (Endereco) malloc((qtdPartes + 1) * sizeof(Endereco));

 for (int i = 0; i < PARTES; i++){
    int quantidade = qtdPartes+(i<resto?1:0);
    int qtdLido = fread(e, sizeof(Endereco), quantidade ,f);

    sprintf(nome, "b%d.dat", i);

    FILE *out = fopen(nome, "wb");
    qsort(e, qtdLido, sizeof(Endereco), compara);
    
    fwrite(e, sizeof(Endereco), qtdLido, out);
    fclose(out);
 }
 fclose(f);
 free(e);

 char a[80] = {0}, b[80] = {0}, s[80] = {0};
 int intercalacoes = PARTES-1;
 for(int j = 0;j < intercalacoes;j++){
    sprintf(a, "b%d.dat", j*2);
    sprintf(b, "b%d.dat", j*2+1);

    if( j == intercalacoes - 1){
        strcpy(s, "cep_ordenado_intercalado.dat");
    }else{
        sprintf(s, "b%d.dat", (PARTES)+j);
    }
        IntercalaArquivos(a, b, s);
 }
    return 0;
}
