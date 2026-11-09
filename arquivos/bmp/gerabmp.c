#include <stdio.h>
#include <stdlib.h>

// Impede que o compilador coloque espaços de preenchimento
// entre os atributos da struct.
#pragma pack(1)

// Cria um apelido BMP para a estrutura _BMP.
typedef struct _BMP BMP;

// Estrutura que representa o cabeçalho e os pixels de uma imagem BMP.
struct _BMP {
    char magic[2];                  // Identificação do arquivo: BM
    unsigned int tamanhoArquivo;    // Tamanho total do arquivo em bytes
    unsigned int lixo;              // Reservado: 0
    unsigned int inicioArray;       // Onde começam os pixels: 54
    unsigned int tamCab2;           // Tamanho do segundo cabeçalho: 40
    unsigned int largura;           // Largura da imagem
    unsigned int altura;            // Altura da imagem
    unsigned short planes;          // Sempre 1
    unsigned short bitsPorPixel;    // 24 bits (RGB)
    unsigned int compressao;        // 0 = sem compressão
    unsigned int tamanhoImagem;     // Tamanho dos dados dos pixels
    unsigned int resolucaoHorizontal; // Resolução horizontal
    unsigned int resolucaoVertical;   // Resolução vertical
    unsigned int numeroCores;       // 0 = padrão
    unsigned int coresImportantes;  // 0 = todas importantes

    unsigned char pixels[];         // Array flexível que armazenará os pixels
};

int main()
{
    // Define as dimensões da imagem.
    int largura = 600;
    int altura = 600;

    // Cada pixel ocupa 3 bytes (B, G e R).
    int tamanhoImagem = largura * altura * 3;

    // Soma o tamanho do cabeçalho com o tamanho dos pixels.
    int tamanhoArquivo = sizeof(BMP) + tamanhoImagem;

    // Reserva dinamicamente memória suficiente para o arquivo inteiro.
    BMP *b = (BMP*) malloc(tamanhoArquivo);

    // Verifica se a memória foi alocada corretamente.
    if (b == NULL) {
        return 1;
    }

    // Preenche a identificação do arquivo BMP.
    b->magic[0] = 'B';
    b->magic[1] = 'M';

    // Preenche os dados do cabeçalho.
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

    // Variável que controla a posição dentro do array de pixels.
    int k = 0;

    // Percorre todas as linhas da imagem.
    for (int i = 0; i < altura; i++)
    {
        // Percorre todas as colunas da imagem.
        for (int j = 0; j < largura; j++) {

            // Calcula a intensidade do vermelho.
            // Começa em 255 e diminui até chegar a 0.
            int intensidade = 255 - ((255 * i) / (altura - 1));

            // Cada pixel possui 3 componentes: B, G e R.
            b->pixels[k++] = 0;           // Azul
            b->pixels[k++] = 0;           // Verde
            b->pixels[k++] = intensidade; // Vermelho
        }
    }

    // Abre um arquivo para escrita binária.
    FILE *f = fopen("seila.bmp", "wb");

    // Escreve toda a estrutura no arquivo.
    fwrite(b, tamanhoArquivo, 1, f);

    // Fecha o arquivo.
    fclose(f);

    // Libera a memória alocada pelo malloc.
    free(b);

    return 0;
}
