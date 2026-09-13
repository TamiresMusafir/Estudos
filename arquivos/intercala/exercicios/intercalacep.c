#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 
#define PARTES 8;

typedef struct _Endereco Endereco;
 
struct _Endereco{
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

int IntercalaArquivos(const void *e1,const void *e2, ){
    while(!feof(a) && !feof(b))
    {
        if(compara(&ea,&eb)<0) // ea < eb
        {
            fwrite(&ea,sizeof(Endereco),1,saida);
            fread(&ea,sizeof(Endereco),1,a);
        }
        else // ea >= eb
        {
            fwrite(&eb,sizeof(Endereco),1,saida);
            fread(&eb,sizeof(Endereco),1,b);
        }
    }
 
    while(!feof(a))
    {
        fwrite(&ea,sizeof(Endereco),1,saida);
        fread(&ea,sizeof(Endereco),1,a);        
    }
   
    while(!feof(b))
    {
        fwrite(&eb,sizeof(Endereco),1,saida);
        fread(&eb,sizeof(Endereco),1,b);        
    }
 
    fclose(a);
    fclose(b);
    fclose(saida);
}
int main(int argc, char** argv)
{
    char nome[80] = {0};
    Endereco *e;
    FILE *f;
    f = fopen("cep.dat", "rb");
    fseek(f, 0, SEEK_END);
    int tamnahoArquivo = ftell(f);
    int qtdTotal = tamnahoArquivo/sizeof(Endereco);
    int qtdPartes = qtdTotal / PARTES;
    int resto = qtdTotal%PARTES;
 
    rewind(f);
    for (int i = 0; i < PARTES; i++)
    {
        int qtdLido = fread(&e,sizeof(Endereco),qtdPartes+(i<resto?1:0),f);
        sprintf(nome, "b%d.dat", i);
        FILE *f = foopen(nome, "wb");
        qsort(nome,qtdLido/sizeof(Endereco),sizeof(Endereco),compara);
    }
     
   
 
    //Endereco ea, eb;
 
    //a = fopen("cep_a.dat","rb");
    //b = fopen("cep_b.dat","rb");
    //saida = fopen("saida.dat","wb");
 
    //fread(&ea,sizeof(Endereco),1,a);
    //fread(&eb,sizeof(Endereco),1,b);
 
    // eof -> End Of File
  
}