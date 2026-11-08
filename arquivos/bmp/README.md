# 🖼️ Imagens BMP — Material de Estudo

Material de consulta e revisão sobre o formato BMP, estrutura do arquivo, pixels, cores, cabeçalho, padding e geração de imagens em C e Java.

---

## 📑 Sumário

- [1. Entendendo uma imagem BMP](#1-entendendo-uma-imagem-bmp)
  - [1.1 O que é BMP?](#11-o-que-é-bmp)
  - [1.2 Como uma imagem é armazenada](#12-como-uma-imagem-é-armazenada)
  - [1.3 Bits, bytes e cores RGB](#13-bits-bytes-e-cores-rgb)
  - [1.4 Ordem BGR no arquivo](#14-ordem-bgr-no-arquivo)
- [2. Estrutura do arquivo BMP](#2-estrutura-do-arquivo-bmp)
  - [2.1 Visão geral](#21-visão-geral)
  - [2.2 Cabeçalho do arquivo — 14 bytes](#22-cabeçalho-do-arquivo--14-bytes)
  - [2.3 Cabeçalho da imagem — 40 bytes](#23-cabeçalho-da-imagem--40-bytes)
  - [2.4 Por que o cabeçalho tem 54 bytes?](#24-por-que-o-cabeçalho-tem-54-bytes)
- [3. Calculando o tamanho da imagem](#3-calculando-o-tamanho-da-imagem)
  - [3.1 Quantidade de pixels](#31-quantidade-de-pixels)
  - [3.2 Tamanho dos pixels](#32-tamanho-dos-pixels)
  - [3.3 O que é padding?](#33-o-que-é-padding)
  - [3.4 Calculando o padding passo a passo](#34-calculando-o-padding-passo-a-passo)
  - [3.5 Fórmulas para a prova](#35-fórmulas-para-a-prova)
- [4. Gerando uma imagem BMP em C](#4-gerando-uma-imagem-bmp-em-c)
  - [4.1 Bibliotecas e estrutura](#41-bibliotecas-e-estrutura)
  - [4.2 Definindo largura e altura](#42-definindo-largura-e-altura)
  - [4.3 Reservando memória](#43-reservando-memória)
  - [4.4 Preenchendo o cabeçalho](#44-preenchendo-o-cabeçalho)
  - [4.5 Preenchendo os pixels](#45-preenchendo-os-pixels)
  - [4.6 Gravando o arquivo](#46-gravando-o-arquivo)
  - [4.7 Entendendo o gradiente](#47-entendendo-o-gradiente)
- [5. Gerando uma imagem BMP em Java](#5-gerando-uma-imagem-bmp-em-java)
  - [5.1 Por que escrever os bytes manualmente?](#51-por-que-escrever-os-bytes-manualmente)
  - [5.2 Escrevendo inteiros em Little Endian](#52-escrevendo-inteiros-em-little-endian)
  - [5.3 Montando o cabeçalho](#53-montando-o-cabeçalho)
  - [5.4 Escrevendo os pixels](#54-escrevendo-os-pixels)
- [6. Comparação entre os códigos C e Java](#6-comparação-entre-os-códigos-c-e-java)
- [7. Pegadinhas e pontos de atenção](#7-pegadinhas-e-pontos-de-atenção)
- [8. Folha de cola](#8-folha-de-cola)
- [9. Exercícios rápidos](#9-exercícios-rápidos)

---

# 1. Entendendo uma imagem BMP

> Antes de olhar o código, precisamos entender o que existe dentro do arquivo. Um BMP não é apenas uma imagem: é um conjunto de bytes organizados em uma estrutura específica.

## 1.1 O que é BMP?

BMP significa **Bitmap**.

É um formato de imagem em que os pixels são armazenados no arquivo. Nos exemplos estudados, estamos usando:

- imagem sem compressão;
- 24 bits por pixel;
- 3 bytes por pixel;
- cabeçalho de 54 bytes;
- componentes de cor de 8 bits cada.

Essas características são do modelo utilizado nos códigos. Existem outros tipos de BMP com configurações diferentes.

## 1.2 Como uma imagem é armazenada

Uma imagem é formada por pequenos pontos chamados **pixels**.

Exemplo de uma imagem de 3 × 2:

```text
       largura = 3
       ┌────┬────┬────┐
linha 1│ P1 │ P2 │ P3 │
       ├────┼────┼────┤
linha 2│ P4 │ P5 │ P6 │
       └────┴────┴────┘
          altura = 2
```

Quantidade de pixels:

```text
largura × altura

3 × 2 = 6 pixels
```

Cada pixel representa uma cor.

## 1.3 Bits, bytes e cores RGB

No modelo de 24 bits usado nos códigos, cada pixel possui três componentes:

- R = Red (vermelho);
- G = Green (verde);
- B = Blue (azul).

Cada componente ocupa **8 bits**, ou seja, **1 byte**.

```text
1 byte = 8 bits

R → 8 bits = 1 byte
G → 8 bits = 1 byte
B → 8 bits = 1 byte

Total:
8 + 8 + 8 = 24 bits

24 bits ÷ 8 = 3 bytes por pixel
```

### Por que 8 bits?

Um bit pode assumir dois valores: 0 ou 1.

Com 8 bits, temos:

```text
2⁸ = 256 combinações
```

Assim, um componente de cor pode assumir 256 valores:

```text
0 até 255
```

Interpretação:

```text
0   → ausência daquela componente
255 → intensidade máxima daquela componente
```

Por exemplo, no RGB:

| Cor | R | G | B |
|---|---:|---:|---:|
| Vermelho | 255 | 0 | 0 |
| Verde | 0 | 255 | 0 |
| Azul | 0 | 0 | 255 |
| Branco | 255 | 255 | 255 |
| Preto | 0 | 0 | 0 |
| Amarelo | 255 | 255 | 0 |

**Atenção:** 8 bits por componente é uma escolha do formato/configuração usada aqui. Não significa que toda imagem digital precise usar 8 bits por componente.

## 1.4 Ordem BGR no arquivo

Embora normalmente falemos em RGB, no BMP de 24 bits os bytes dos pixels são gravados na ordem **BGR**:

```text
Ordem lógica da cor:
R → G → B

Ordem gravada no BMP:
B → G → R
```

Exemplo: vermelho puro.

```text
RGB = (255, 0, 0)

BMP armazena:
B = 0
G = 0
R = 255
```

Em bytes:

```text
[00000000] [00000000] [11111111]
     B          G          R
```

No código C:

```c
b->pixels[k++] = 0;           // Azul
b->pixels[k++] = 0;           // Verde
b->pixels[k++] = intensidade; // Vermelho
```

Portanto, esse trecho gera tons de vermelho, não de azul.

---

# 2. Estrutura do arquivo BMP

## 2.1 Visão geral

No modelo usado nos exemplos, o arquivo é organizado assim:

```text
┌──────────────────────────────────┐
│ Cabeçalho do arquivo             │ 14 bytes
├──────────────────────────────────┤
│ Cabeçalho da imagem              │ 40 bytes
├──────────────────────────────────┤
│ Dados dos pixels                 │ variável
└──────────────────────────────────┘
```

Os dois cabeçalhos juntos ocupam:

```text
14 + 40 = 54 bytes
```

Os pixels começam no byte de posição 54.

## 2.2 Cabeçalho do arquivo — 14 bytes

É a primeira parte do BMP.

| Campo | Tamanho | Para que serve |
|---|---:|---|
| `magic` | 2 bytes | Identifica o arquivo como BMP (`BM`) |
| `tamanhoArquivo` | 4 bytes | Tamanho total do arquivo |
| `lixo` / reservado | 4 bytes | Campo reservado; nos exemplos recebe 0 |
| `inicioArray` | 4 bytes | Posição em que começam os pixels |

Total:

```text
2 + 4 + 4 + 4 = 14 bytes
```

### Campo `magic`

```c
b->magic[0] = 'B';
b->magic[1] = 'M';
```

Os dois primeiros bytes são as letras `BM`.

Eles identificam o formato do arquivo.

### Campo `tamanhoArquivo`

Representa o tamanho total:

```text
tamanhoArquivo = cabeçalho + dados dos pixels
```

No exemplo sem padding:

```text
tamanhoArquivo = 54 + (largura × altura × 3)
```

### Campo `inicioArray`

```c
b->inicioArray = 54;
```

Indica que os dados dos pixels começam depois dos 54 bytes de cabeçalho.

Não é a quantidade de pixels: é uma posição dentro do arquivo.

## 2.3 Cabeçalho da imagem — 40 bytes

Nos códigos, esse cabeçalho possui os seguintes campos:

| Campo | Tamanho | Significado |
|---|---:|---|
| `tamCab2` | 4 bytes | Tamanho deste cabeçalho: 40 |
| `largura` | 4 bytes | Largura em pixels |
| `altura` | 4 bytes | Altura em pixels |
| `planes` | 2 bytes | Deve ser 1 |
| `bitsPorPixel` | 2 bytes | Profundidade de cor: 24 |
| `compressao` | 4 bytes | 0 = sem compressão |
| `tamanhoImagem` | 4 bytes | Tamanho dos dados dos pixels |
| `resolucaoHorizontal` | 4 bytes | Resolução horizontal |
| `resolucaoVertical` | 4 bytes | Resolução vertical |
| `numeroCores` | 4 bytes | Número de cores da paleta; 0 neste modelo |
| `coresImportantes` | 4 bytes | Cores importantes; 0 neste modelo |

Soma:

```text
4 + 4 + 4 + 2 + 2 + 4 + 4 + 4 + 4 + 4 + 4
= 40 bytes
```

### Campos que merecem atenção

```c
b->largura = largura;
b->altura = altura;
```

Definem as dimensões da imagem.

```c
b->planes = 1;
b->bitsPorPixel = 24;
```

Indicam uma imagem com 24 bits por pixel.

```c
b->compressao = 0;
```

Indica que os pixels estão armazenados sem compressão, no modelo usado.

## 2.4 Por que o cabeçalho tem 54 bytes?

Porque, neste modelo:

```text
Cabeçalho do arquivo = 14 bytes
Cabeçalho da imagem  = 40 bytes

Total = 14 + 40 = 54 bytes
```

Visualmente:

```text
Byte 0                                      Byte 53
  │                                           │
  ▼                                           ▼
  ┌──────────────────┬────────────────────────┐
  │ 14 bytes         │ 40 bytes               │
  │ File Header      │ Info Header            │
  └──────────────────┴────────────────────────┘
  │
  └── pixels começam no byte 54
```

**Atenção:** 54 bytes não é uma regra para absolutamente todo BMP. É o tamanho do cabeçalho utilizado nesses exemplos, sem paleta ou cabeçalhos adicionais.

---

# 3. Calculando o tamanho da imagem

## 3.1 Quantidade de pixels

Para descobrir quantos pixels existem:

```text
quantidade de pixels = largura × altura
```

Exemplo: imagem de 600 × 600.

```text
600 × 600 = 360.000 pixels
```

## 3.2 Tamanho dos pixels

Como cada pixel ocupa 3 bytes:

```text
dados dos pixels = quantidade de pixels × 3
```

Ou:

```text
dados dos pixels = largura × altura × 3
```

Exemplo: 600 × 600:

```text
600 × 600 × 3
= 360.000 × 3
= 1.080.000 bytes
```

Se somarmos os 54 bytes de cabeçalho:

```text
tamanho do arquivo = 54 + 1.080.000

tamanho do arquivo = 1.080.054 bytes
```

Isso vale quando não há bytes de padding nas linhas.

## 3.3 O que é padding?

O padding são bytes extras colocados **no final de cada linha de pixels**.

No BMP, cada linha de pixels deve ocupar um número de bytes múltiplo de 4.

Como cada pixel de 24 bits ocupa 3 bytes, algumas larguras deixam a linha com um tamanho que não é divisível por 4.

O padding completa essa linha até o próximo múltiplo de 4.

**Importante:** padding não é uma cor, não é um pixel e não altera a imagem visualmente. São bytes extras usados para alinhamento.

## 3.4 Calculando o padding passo a passo

Imagine uma imagem com:

```text
largura = 3 pixels
```

Cada pixel ocupa 3 bytes:

```text
3 pixels × 3 bytes = 9 bytes por linha
```

Mas 9 não é múltiplo de 4.

Os múltiplos de 4 próximos são:

```text
4, 8, 12, 16, 20...
```

O próximo múltiplo de 4 depois de 9 é 12.

Então:

```text
12 - 9 = 3 bytes de padding
```

A linha fica assim:

```text
┌────────┬────────┬────────┬────────────────┐
│ Pixel 1│ Pixel 2│ Pixel 3│ Padding        │
│ 3 bytes│ 3 bytes│ 3 bytes│ 3 bytes        │
└────────┴────────┴────────┴────────────────┘

Total da linha = 12 bytes
```

Se a imagem tiver 2 linhas:

```text
12 bytes × 2 linhas = 24 bytes
```

Separando:

```text
Pixels:  9 × 2 = 18 bytes
Padding: 3 × 2 =  6 bytes

Total:             24 bytes
```

### Mais exemplos

| Largura | Bytes dos pixels por linha | Padding | Total da linha |
|---:|---:|---:|---:|
| 1 | 3 | 1 | 4 |
| 2 | 6 | 2 | 8 |
| 3 | 9 | 3 | 12 |
| 4 | 12 | 0 | 12 |
| 5 | 15 | 1 | 16 |
| 6 | 18 | 2 | 20 |
| 7 | 21 | 3 | 24 |
| 8 | 24 | 0 | 24 |

Observe o padrão: o padding pode ser 0, 1, 2 ou 3 bytes.

### Exemplo com largura 5

```text
5 pixels × 3 bytes = 15 bytes

Próximo múltiplo de 4 = 16

16 - 15 = 1 byte de padding
```

Logo, a resposta é **1 byte**, não 3.

## 3.5 Fórmulas para a prova

Para BMP de 24 bits:

```text
bytes dos pixels por linha = largura × 3
```

Padding:

```text
padding = (4 - ((largura × 3) % 4)) % 4
```

Tamanho de uma linha:

```text
tamanhoLinha = (largura × 3) + padding
```

Tamanho total dos pixels:

```text
tamanhoImagem = tamanhoLinha × altura
```

Tamanho total do arquivo, neste modelo:

```text
tamanhoArquivo = 54 + tamanhoImagem
```

### Quando não existe padding?

Quando:

```text
(largura × 3) % 4 = 0
```

Nos exemplos estudados:

```text
largura = 600

600 × 3 = 1800
1800 % 4 = 0
padding = 0
```

```text
largura = 800

800 × 3 = 2400
2400 % 4 = 0
padding = 0
```

Por isso os dois códigos apresentados conseguem gravar os pixels sem adicionar padding.

---

# 4. Gerando uma imagem BMP em C

## 4.1 Bibliotecas e estrutura

O código usa:

```c
#include <stdio.h>
#include <stdlib.h>
```

- `stdio.h`: arquivo e funções como `fopen`, `fwrite` e `fclose`.
- `stdlib.h`: memória dinâmica, como `malloc` e `free`.

A estrutura representa o cabeçalho e, no final, os dados dos pixels:

```c
#pragma pack(1)

typedef struct _BMP BMP;

struct _BMP {
    char magic[2];
    unsigned int tamanhoArquivo;
    unsigned int lixo;
    unsigned int inicioArray;
    unsigned int tamCab2;
    unsigned int largura;
    unsigned int altura;
    unsigned short planes;
    unsigned short bitsPorPixel;
    unsigned int compressao;
    unsigned int tamanhoImagem;
    unsigned int resolucaoHorizontal;
    unsigned int resolucaoVertical;
    unsigned int numeroCores;
    unsigned int coresImportantes;
    unsigned char pixels[];
};
```

### O que significa `#pragma pack(1)`?

Pede ao compilador para não inserir bytes de alinhamento entre os campos da estrutura.

Isso é importante porque queremos que a estrutura tenha exatamente a organização esperada pelo cabeçalho BMP.

No código apresentado, o cabeçalho ocupa 54 bytes.

### O que significa `unsigned char pixels[]`?

É um membro de tamanho flexível: os pixels ficam depois dos campos do cabeçalho, no mesmo bloco de memória.

O tamanho dos pixels será reservado junto com a estrutura usando `malloc`.

## 4.2 Definindo largura e altura

```c
int largura = 600;
int altura = 600;
```

A imagem terá 600 pixels de largura e 600 pixels de altura.

Quantidade de pixels:

```text
600 × 600 = 360.000
```

## 4.3 Reservando memória

No código:

```c
int tamanhoImagem = largura * altura * 3;
int tamanhoArquivo = sizeof(BMP) + tamanhoImagem;

BMP *b = (BMP*) malloc(tamanhoArquivo);
```

Passo a passo:

1. Cada pixel ocupa 3 bytes.
2. Multiplicamos largura × altura × 3.
3. Somamos o tamanho do cabeçalho.
4. `malloc` reserva esse espaço na memória.

Com os valores do exemplo:

```text
tamanhoImagem = 600 × 600 × 3
tamanhoImagem = 1.080.000 bytes

tamanhoArquivo = 54 + 1.080.000
tamanhoArquivo = 1.080.054 bytes
```

O `sizeof(BMP)` representa o tamanho da estrutura sem os pixels flexíveis. Com o empacotamento usado no código, são 54 bytes.

Depois, o programa verifica:

```c
if (b == NULL) {
    return 1;
}
```

Se `malloc` não conseguir reservar memória, retorna `NULL`.

## 4.4 Preenchendo o cabeçalho

O código define os campos:

```c
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
```

A ideia é preencher os metadados que descrevem a imagem antes de escrever os pixels.

Resumo dos principais valores:

| Campo | Valor | Significado |
|---|---:|---|
| `magic` | `BM` | Arquivo BMP |
| `inicioArray` | 54 | Pixels começam no byte 54 |
| `tamCab2` | 40 | Cabeçalho de imagem com 40 bytes |
| `largura` | 600 | 600 pixels |
| `altura` | 600 | 600 pixels |
| `planes` | 1 | Valor exigido pelo formato |
| `bitsPorPixel` | 24 | 3 bytes por pixel |
| `compressao` | 0 | Sem compressão |

## 4.5 Preenchendo os pixels

Trecho do código:

```c
int k = 0;

for(int i = 0; i < altura; i++) {
    for(int j = 0; j < largura; j++) {
        int intensidade = 255 - ((255 * i) / (altura - 1));

        b->pixels[k++] = 0;           // Azul
        b->pixels[k++] = 0;           // Verde
        b->pixels[k++] = intensidade; // Vermelho
    }
}
```

Existem dois `for`:

- `i`: percorre as linhas;
- `j`: percorre os pixels de cada linha.

Para cada pixel, são gravados três bytes.

```text
B → 0
G → 0
R → intensidade
```

Como apenas o vermelho varia, a imagem apresenta tons de vermelho.

### Por que existe `k`?

`k` indica a posição atual dentro do vetor de bytes dos pixels.

A cada componente gravado, fazemos `k++`.

Um pixel ocupa três posições:

```text
pixels[k]     → B
pixels[k + 1] → G
pixels[k + 2] → R
```

Depois de gravar as três componentes, `k` avançou 3 posições.

## 4.6 Gravando o arquivo

```c
FILE *f = fopen("seila.bmp", "wb");

fwrite(b, tamanhoArquivo, 1, f);

fclose(f);
free(b);
```

Passo a passo:

1. `fopen` abre/cria o arquivo em modo binário para escrita.
2. `fwrite` grava o bloco inteiro: cabeçalho + pixels.
3. `fclose` fecha o arquivo.
4. `free` libera a memória reservada por `malloc`.

O modo `wb` cria o arquivo ou substitui seu conteúdo anterior.

**Atenção:** o código de aula não verifica se `fopen` retornou `NULL`. Em um programa mais robusto, essa verificação deve ser feita antes de chamar `fwrite`.

## 4.7 Entendendo o gradiente

A intensidade é calculada por:

```c
int intensidade = 255 - ((255 * i) / (altura - 1));
```

`i` representa a linha atual.

Com altura 600:

- na primeira linha (`i = 0`), a intensidade é 255;
- na última linha (`i = 599`), a intensidade é 0.

A conta da primeira linha:

```text
255 - ((255 × 0) / 599)
= 255 - 0
= 255
```

A conta da última linha:

```text
255 - ((255 × 599) / 599)
= 255 - 255
= 0
```

Isso cria uma variação gradual de vermelho.

### Atenção à orientação vertical do BMP

Quando a altura do BMP é positiva, as linhas são armazenadas de baixo para cima.

Por isso, a primeira linha gravada pelo laço corresponde à parte inferior da imagem.

No código:

```text
primeira linha gravada → vermelho máximo → parte inferior
última linha gravada   → vermelho zero   → parte superior
```

Visualmente, o gradiente aparece com a parte superior escura e a parte inferior vermelha.

---

# 5. Gerando uma imagem BMP em Java

## 5.1 Por que escrever os bytes manualmente?

No C, o programa preenche uma estrutura e grava seu conteúdo.

No Java, o exemplo escreve cada campo do cabeçalho diretamente no arquivo:

```java
OutputStream saida = new FileOutputStream("teste.bmp");
DataOutputStream dout = new DataOutputStream(saida);
```

O `DataOutputStream` oferece métodos para escrever números e bytes.

Mas existe um detalhe importante: `writeInt` escreve inteiros em **Big Endian** por padrão, enquanto os campos numéricos do BMP são armazenados em **Little Endian**.

Por isso o código cria métodos auxiliares para inverter a ordem dos bytes.

## 5.2 Escrevendo inteiros em Little Endian

### O que é Big Endian e Little Endian?

Imagine o número representado por quatro bytes:

```text
A1 B2 C3 D4
```

Big Endian grava primeiro o byte mais significativo:

```text
A1 B2 C3 D4
```

Little Endian grava primeiro o menos significativo:

```text
D4 C3 B2 A1
```

O BMP utilizado no exemplo espera Little Endian para os campos numéricos.

### Método para escrever 4 bytes

```java
public static void escreveIntInvertido(DataOutputStream dout, int x)
        throws IOException {

    int b4 = (x & 0xff000000) >> 24;
    int b3 = (x & 0x00ff0000) >> 16;
    int b2 = (x & 0x0000ff00) >> 8;
    int b1 = (x & 0x000000ff);

    dout.write(b1);
    dout.write(b2);
    dout.write(b3);
    dout.write(b4);
}
```

O método separa o inteiro em quatro bytes e escreve primeiro o byte menos significativo.

A ideia é:

```text
inteiro de 4 bytes
      ↓
separar em b1, b2, b3 e b4
      ↓
escrever b1 → b2 → b3 → b4
```

### Método para escrever 2 bytes

```java
public static void escreveInt2Invertido(DataOutputStream dout, int x)
        throws IOException {

    int b2 = (x & 0x0000ff00) >> 8;
    int b1 = (x & 0x000000ff);

    dout.write(b1);
    dout.write(b2);
}
```

Esse método é usado para campos de 2 bytes, como `planes` e `bitsPorPixel`.

### O que significam `&` e `>>`?

O operador `&` faz uma operação AND bit a bit. As máscaras selecionam a parte do inteiro que queremos extrair.

O operador `>>` desloca os bits para a direita.

Neste código, eles são usados para separar os bytes de um inteiro.

Não é necessário decorar toda a operação antes de entender a finalidade: **o método divide o número em bytes e os grava na ordem Little Endian**.

## 5.3 Montando o cabeçalho

O começo do `main`:

```java
dout.write((byte)'B');
dout.write((byte)'M');

escreveIntInvertido(dout, 800 * 600 * 3 + 54);
dout.writeInt(0);
escreveIntInvertido(dout, 54);

escreveIntInvertido(dout, 40);
escreveIntInvertido(dout, 800);
escreveIntInvertido(dout, 600);
escreveInt2Invertido(dout, 1);
escreveInt2Invertido(dout, 24);
escreveIntInvertido(dout, 0);
escreveIntInvertido(dout, 800 * 600 * 3);
escreveIntInvertido(dout, 0);
escreveIntInvertido(dout, 0);
escreveIntInvertido(dout, 0);
escreveIntInvertido(dout, 0);
```

A ordem de escrita segue a estrutura do BMP:

1. `BM`;
2. tamanho total do arquivo;
3. campo reservado;
4. posição inicial dos pixels;
5. tamanho do cabeçalho da imagem;
6. largura;
7. altura;
8. planos;
9. bits por pixel;
10. compressão;
11. tamanho dos pixels;
12. resolução horizontal;
13. resolução vertical;
14. número de cores;
15. cores importantes.

### Por que `dout.writeInt(0)` não usa o método auxiliar?

Porque o valor é zero.

Em qualquer ordem, seus quatro bytes continuam sendo:

```text
00 00 00 00
```

Então a ordem não altera o resultado.

### Conferindo os tamanhos do exemplo Java

```text
largura = 800
altura = 600

pixels = 800 × 600
pixels = 480.000

bytes dos pixels = 480.000 × 3
bytes dos pixels = 1.440.000

arquivo = 54 + 1.440.000
arquivo = 1.440.054 bytes
```

A largura 800 não precisa de padding:

```text
800 × 3 = 2400

2400 % 4 = 0
```

## 5.4 Escrevendo os pixels

Trecho:

```java
for(int i = 0; i < 600; i++) {
    int cor = ((600 - i) * 0xff) / 600;

    for(int j = 0; j < 800; j++) {
        dout.write(cor);
        dout.write(cor);
        dout.write(0);
    }
}
```

Novamente:

- `i` percorre as linhas;
- `j` percorre os pixels da linha;
- cada pixel recebe três bytes.

A ordem gravada é BGR:

```text
B = cor
G = cor
R = 0
```

Como azul e verde recebem o mesmo valor e vermelho recebe zero, a cor resultante varia entre tons de ciano e preto.

A variável `cor` muda conforme a linha:

```java
int cor = ((600 - i) * 0xff) / 600;
```

O valor começa próximo de 255 e diminui à medida que `i` aumenta.

Como a altura é positiva, a primeira linha gravada fica na parte inferior da imagem.

Ao final:

```java
dout.close();
saida.close();
```

O fechamento de `dout` já fecha o fluxo subjacente (`saida`), então chamar `saida.close()` depois é redundante, embora apareça no código de aula.

---

# 6. Comparação entre os códigos C e Java

| Etapa | C | Java |
|---|---|---|
| Criar arquivo | `fopen` | `FileOutputStream` |
| Escrever dados | `fwrite` | `DataOutputStream` |
| Cabeçalho | Preenche uma `struct` | Escreve campo por campo |
| Ordem dos bytes | Depende da representação da máquina; o código pressupõe o layout esperado | Métodos auxiliares escrevem Little Endian |
| Pixels | Vetor `pixels[]` | Chamadas a `dout.write` |
| Memória | `malloc` e `free` | Gerenciada pela JVM |
| Fechar | `fclose` | `close` |

### Diferença principal

No C:

```text
monta a estrutura na memória
          ↓
preenche os pixels
          ↓
grava o bloco inteiro
```

No Java:

```text
abre o fluxo de saída
          ↓
escreve o cabeçalho campo por campo
          ↓
escreve os pixels
```

Os dois códigos produzem um BMP, mas constroem o arquivo de maneiras diferentes.

---

# 7. Pegadinhas e pontos de atenção

## 📦 Pixels e cores

- 1 byte = 8 bits.
- 8 bits permitem 256 valores: 0 até 255.
- No BMP de 24 bits, cada componente ocupa 1 byte.
- Cada pixel ocupa 3 bytes.
- A ordem gravada é BGR, não RGB.
- 24 bits = 3 bytes.

## 📐 Dimensões e tamanho

- Quantidade de pixels = largura × altura.
- Bytes dos pixels por linha = largura × 3.
- Não esqueça o padding quando a linha não for múltipla de 4.
- O tamanho total dos pixels considera o padding de todas as linhas.
- O tamanho total do arquivo soma cabeçalho + dados dos pixels.

## 🧱 Cabeçalho

- No modelo dos exemplos, o cabeçalho tem 54 bytes.
- 14 bytes do cabeçalho do arquivo + 40 bytes do cabeçalho da imagem.
- `BM` identifica o arquivo.
- `inicioArray = 54` indica onde começam os pixels.
- `bitsPorPixel = 24` indica 3 bytes por pixel.
- `compressao = 0` indica ausência de compressão neste modelo.

## ⚠️ Padding

- Padding é colocado no final de cada linha.
- Não é pixel e não representa uma cor.
- Pode ter 0, 1, 2 ou 3 bytes.
- Largura 3 → 3 bytes de padding.
- Largura 5 → 1 byte de padding.
- Largura 4 → nenhum padding.
- Os exemplos com largura 600 e 800 não precisam de padding.

## 🧭 Orientação

- BMP com altura positiva armazena as linhas de baixo para cima.
- A primeira linha gravada corresponde à parte inferior.
- Não confunda a ordem em que o laço percorre as linhas com a orientação visual final.

## 💻 C e Java

- `#pragma pack(1)` evita padding entre os campos da `struct`.
- `unsigned char` representa um byte sem sinal.
- `malloc` reserva memória; `free` libera.
- `fwrite` grava o bloco de memória.
- `DataOutputStream.writeInt` usa Big Endian por padrão.
- O código Java usa métodos auxiliares para escrever campos numéricos em Little Endian.

---

# 8. Folha de cola

## 🧮 Bits e bytes

```text
1 byte = 8 bits

2⁸ = 256 valores

valores possíveis = 0 até 255

RGB:
R = 1 byte
G = 1 byte
B = 1 byte

24 bits = 3 bytes por pixel
```

## 🎨 Ordem das cores

```text
RGB lógico: R → G → B

BMP no arquivo: B → G → R

Vermelho:
RGB = (255, 0, 0)
BMP = (0, 0, 255)
```

## 📐 Tamanho

```text
quantidade de pixels = largura × altura

bytes por pixel = 3

bytes por linha = largura × 3

padding = (4 - ((largura × 3) % 4)) % 4

tamanho da linha = largura × 3 + padding

tamanho da imagem = tamanho da linha × altura

tamanho do arquivo = 54 + tamanho da imagem
```

## 🧱 Cabeçalho

```text
File Header = 14 bytes

Info Header = 40 bytes

Total = 54 bytes

pixels começam no byte 54
```

## 🧩 Padding — exemplos

```text
largura 1 → 3 bytes de pixels → 1 padding
largura 2 → 6 bytes de pixels → 2 padding
largura 3 → 9 bytes de pixels → 3 padding
largura 4 → 12 bytes de pixels → 0 padding
largura 5 → 15 bytes de pixels → 1 padding
largura 6 → 18 bytes de pixels → 2 padding
largura 7 → 21 bytes de pixels → 3 padding
largura 8 → 24 bytes de pixels → 0 padding
```

## 🔁 Orientação

```text
altura positiva → linhas armazenadas de baixo para cima

primeira linha gravada → parte inferior da imagem
última linha gravada   → parte superior da imagem
```

---

# 9. Exercícios rápidos

Tente responder antes de olhar o gabarito.

### 1. Quantos bytes ocupa um pixel neste BMP de 24 bits?

<details>
<summary>Ver resposta</summary>

3 bytes: 1 para vermelho, 1 para verde e 1 para azul.

</details>

### 2. Por que um componente de cor pode assumir valores de 0 a 255?

<details>
<summary>Ver resposta</summary>

Porque ele ocupa 8 bits. Com 8 bits existem 2⁸ = 256 combinações, numeradas de 0 até 255.

</details>

### 3. Uma imagem tem largura 4. Quantos bytes de pixels existem em cada linha? Precisa de padding?

<details>
<summary>Ver resposta</summary>

```text
4 × 3 = 12 bytes

12 é múltiplo de 4.

Padding = 0.
```

</details>

### 4. Uma imagem tem largura 5. Quanto padding existe por linha?

<details>
<summary>Ver resposta</summary>

```text
5 × 3 = 15 bytes

Próximo múltiplo de 4 = 16

16 - 15 = 1 byte de padding.
```

</details>

### 5. Qual é o tamanho dos dados dos pixels de uma imagem 10 × 2, considerando o padding?

<details>
<summary>Ver resposta</summary>

```text
Bytes de pixels por linha:
10 × 3 = 30

Padding:
(4 - (30 % 4)) % 4
= (4 - 2) % 4
= 2 bytes

Tamanho de cada linha:
30 + 2 = 32 bytes

Duas linhas:
32 × 2 = 64 bytes
```

</details>

### 6. Qual é o tamanho total do arquivo para essa imagem 10 × 2, no modelo de cabeçalho de 54 bytes?

<details>
<summary>Ver resposta</summary>

```text
54 + 64 = 118 bytes
```

</details>

### 7. No BMP, a sequência gravada para um pixel vermelho puro é RGB ou BGR?

<details>
<summary>Ver resposta</summary>

BGR.

Vermelho puro é RGB (255, 0, 0), mas os bytes no arquivo são (0, 0, 255).

</details>

---

# 🧠 Ideia central do BMP

Para entender os códigos, pense no arquivo em duas grandes partes:

```text
BMP
 │
 ├──► CABEÇALHO
 │       │
 │       ├── identifica o formato
 │       ├── informa largura e altura
 │       ├── informa bits por pixel
 │       └── informa onde os pixels começam
 │
 └──► PIXELS
         │
         ├── cada pixel tem 3 bytes
         ├── os bytes são gravados em BGR
         └── cada linha pode precisar de padding
```

A sequência de raciocínio para resolver exercícios é:

```text
1. Identificar largura e altura
          ↓
2. Identificar bits por pixel
          ↓
3. Descobrir bytes por pixel
          ↓
4. Calcular bytes de cada linha
          ↓
5. Calcular o padding
          ↓
6. Calcular o tamanho total dos pixels
          ↓
7. Somar o cabeçalho
```

O mais importante é não misturar três coisas diferentes:

```text
COR       → valores de R, G e B
PIXEL     → conjunto de 3 bytes
PADDING   → bytes extras no final de cada linha
```