#include <stdio.h>
#include <stdlib.h>

#pragma pack(1)

typedef struct _BMP BMP;

struct _BMP {
    char magic[2]; // BM
    unsigned int tamanhoArquivo;
    unsigned int lixo; // 0
    unsigned int inicioArray; // 54
    unsigned int tamCab2; // 40
    unsigned int largura;
    unsigned int altura;
    unsigned short planes; // 1
    unsigned short bitsPorPixel; // 24
    unsigned int compressao; // 0
    unsigned int tamanhoImagem; // tamanhoArquivo - 54
    unsigned int resolucaoHorizontal; // 0
    unsigned int resolucaoVertical; // 0
    unsigned int numeroCores; // 0
    unsigned int coresImportantes; // 0
    unsigned char pixels[];
};

int main() 
{
    int largura = 600;
    int altura = 600;

    int tamanhoImagem = largura * altura * 3;
    int tamanhoArquivo = sizeof(BMP) + tamanhoImagem;

    BMP *b = (BMP*) malloc(tamanhoArquivo);

    if (b == NULL) {
        return 1;
    }

    b->magic[0] = 'B';
    b->magic[1] = 'M';

    b->tamanhoArquivo = tamanhoArquivo;
    b->lixo = 0;
    b->inicioArray = 54;
    b->tamCab2 = 40;

    b->largura = largura;
    b->altura = altura;

    b->planes = 1;
    b->bitsPorPixel = 24;
    b->compressao = 0;

    b->tamanhoImagem = tamanhoImagem;

    b->resolucaoHorizontal = 0;
    b->resolucaoVertical = 0;
    b->numeroCores = 0;
    b->coresImportantes = 0;

    int k = 0;
    for(int i=0; i<altura; i++) 
    {
        for(int j=0; j<largura; j++) {
            int intensidade = 255-((255*i)/(altura-1));
            b->pixels[k++] = 0; // Azul
            b->pixels[k++] = 0; // Verde
            b->pixels[k++] = intensidade; // Vermelho          
        }
    }


    FILE *f = fopen("seila.bmp","wb");
    fwrite(b,tamanhoArquivo,1,f);
    fclose(f);
    free(b);

    return 0;
}