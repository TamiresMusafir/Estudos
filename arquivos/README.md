# 📁 Estrutura de Arquivos em C — Material de Prova

Material de consulta e revisão sobre arquivos, registros, memória, ponteiros, busca, índices e ordenação externa em C.

## 📑 Sumário

O material é um só, em duas partes: **P1** (arquivos em C) e **P2** (árvores B/B+, hash e Huffman). Depois vem o [Guia de Estudos por Exercício](#7-guia-de-estudos-por-exercício) (E1 a E28, com código testado). No fim há a [Ideia central da matéria](#-ideia-central-da-matéria), que junta tudo.

### 📘 P1 — Arquivos em C

- [1. Conceitos principais](#1-conceitos-principais)
  - [1.1 Arquivo, `FILE *` e posição atual](#11-arquivo-file--e-posição-atual)
  - [1.2 `struct`, registros e tamanho fixo](#12-struct-registros-e-tamanho-fixo)
  - [1.3 Ponteiros: `*`, `&`, `.` e `->`](#13-ponteiros--e-)
  - [1.4 Bytes × registros](#14-bytes--registros)
  - [1.5 Memória: `Tipo x` × `Tipo *x`](#15-memória-tipo-x--tipo-x)
  - [1.6 `EOF` × `feof`](#16-eof--feof)
  - [1.7 `argc` e `argv`](#17-argc-e-argv)
  - [1.8 Bytes e ASCII](#18-bytes-e-ascii)
- [2. Funções principais](#2-funções-principais)
  - [2.1 `fopen` / `fclose`](#21-fopen--fclose)
  - [2.2 `fgetc` / `fputc`](#22-fgetc--fputc)
  - [2.3 `fread` / `fwrite`](#23-fread--fwrite)
  - [2.4 `fseek` / `ftell` / `rewind` / `feof`](#24-fseek--ftell--rewind--feof)
  - [2.5 `malloc` / `free` / `sizeof` / `memset`](#25-malloc--free--sizeof--memset)
  - [2.6 Strings](#26-strings)
  - [2.7 `qsort` / `compara`](#27-qsort--compara)
- [3. Padrões de programas](#3-padrões-de-programas)
  - [3.1 Leitura sequencial byte a byte](#31-leitura-sequencial-byte-a-byte)
  - [3.2 Leitura sequencial de registros](#32-leitura-sequencial-de-registros)
  - [3.3 Ordenar arquivo inteiro](#33-ordenar-arquivo-inteiro)
  - [3.4 Busca binária direta](#34-busca-binária-direta)
  - [3.5 Índice](#35-índice)
  - [3.6 Ordenação externa](#36-ordenação-externa)
  - [3.7 Busca sequencial em arquivo de registros](#37-busca-sequencial-em-arquivo-de-registros)
  - [3.8 Outros padrões de enunciado](#38-outros-padrões-de-enunciado)
- [4. Pegadinhas e lógica](#4-pegadinhas-e-lógica)
- [5. Folha de cola](#5-folha-de-cola)
  - [5.1 Bibliotecas](#51-bibliotecas)
  - [5.2 Struct](#52-struct)
  - [5.3 argc / argv](#53-argc--argv)
  - [5.4 Arquivos](#54-arquivos)
  - [5.5 fgetc / fputc](#55-fgetc--fputc)
  - [5.6 fread / fwrite](#56-fread--fwrite)
  - [5.7 fseek / ftell / rewind](#57-fseek--ftell--rewind)
  - [5.8 Ponteiros](#58-ponteiros)
  - [5.9 malloc / free / memset](#59-malloc--free--memset)
  - [5.10 Strings](#510-strings)
  - [5.11 qsort](#511-qsort)
  - [5.12 return](#512-return)
  - [5.13 Programas para copiar e colar](#513-programas-para-copiar-e-colar)
  - [5.14 Contas e lembretes](#514-contas-e-lembretes)
  - [5.15 Checklist — antes de entregar](#515-checklist--antes-de-entregar)

### 📗 P2 — Árvores B e B+, hash e Huffman

- [P2. Visão geral da P2](#-p2--árvores-b-e-b-hash-e-huffman)
  - [P2.1 Árvores B e B+](#p21-árvores-b-e-b)
  - [P2.2 Hash](#p22-hash)
  - [P2.3 Código e árvore de Huffman](#p23-código-e-árvore-de-huffman)
  - [P2.4 Mapa: questão → guia de estudo](#p24-mapa-questão--guia-de-estudo)
- Guias completos, nas pastas: [`arvores/`](arvores/README.md) · [`hash/`](hash/README.md) · [`arvore-huf/`](arvore-huf/README.md) · [`provasp2/`](provasp2/README.md)

- [6. Folha de cola da P2](#6-folha-de-cola-da-p2)
  - [6.1 Respostas objetivas (para copiar)](#61-respostas-objetivas-para-copiar)
  - [6.2 Pior caso e melhor caso](#62-pior-caso-e-melhor-caso)
  - [6.3 Árvore B e B+: como funciona e as contas](#63-árvore-b-e-b-como-funciona-e-as-contas)
  - [6.4 Hash com encadeamento externo](#64-hash-com-encadeamento-externo)
  - [6.5 Huffman](#65-huffman)
  - [6.6 Código com índice em árvore B (questão 4 da P2)](#66-código-com-índice-em-árvore-b-questão-4-da-p2)
  - [6.7 Checklist — antes de entregar a P2](#67-checklist--antes-de-entregar-a-p2)

### 📙 Guia de Estudos por Exercício

- [7. Guia de Estudos por Exercício](#7-guia-de-estudos-por-exercício)
  - [7.1 Conceitos básicos de arquivos](#71-conceitos-básicos-de-arquivos)
  - [7.2 E1 — Leitura de bytes, linhas e histograma](#72-e1--leitura-de-bytes-linhas-e-histograma)
  - [7.3 E2 — Cópia byte a byte](#73-e2--cópia-byte-a-byte)
  - [7.4 E3 — Cópia em blocos](#74-e3--cópia-em-blocos)
  - [7.5 Balanceamento de chaves `{}`](#75-balanceamento-de-chaves-)
  - [7.6 E6 — Quantidade de registros e tamanho do arquivo](#76-e6--quantidade-de-registros-e-tamanho-do-arquivo)
  - [7.7 E7 — Acesso direto a registros](#77-e7--acesso-direto-a-registros)
  - [7.8 Ordenação externa](#78-ordenação-externa)
  - [7.9 `malloc` — Alocação dinâmica](#79-malloc--alocação-dinâmica)
  - [7.10 `qsort` e função comparadora](#710-qsort-e-função-comparadora)
  - [7.11 E12 — Busca sequencial](#711-e12--busca-sequencial)
  - [7.12 E13 — Ordenação em memória](#712-e13--ordenação-em-memória)
  - [7.13 E14 — Busca binária em arquivo](#713-e14--busca-binária-em-arquivo)
  - [7.14 E15 — Índice em vetor](#714-e15--índice-em-vetor)
  - [7.15 Árvores B — Conceitos](#715-árvores-b--conceitos)
  - [7.16 Árvore B — Exercício A: criação do índice](#716-árvore-b--exercício-a-criação-do-índice)
  - [7.17 Árvore B — Exercício B: busca e impressão](#717-árvore-b--exercício-b-busca-e-impressão)
  - [7.18 Árvore B — Exercício C: diferença entre arquivos](#718-árvore-b--exercício-c-diferença-entre-arquivos)
  - [7.19 Resumo de funções importantes](#719-resumo-de-funções-importantes)
  - [7.20 Como identificar qual técnica usar na prova](#720-como-identificar-qual-técnica-usar-na-prova)
  - [7.21 Exercícios do treino que faltam — Bloco 1 (E4, E5)](#721-exercícios-do-treino-que-faltam--bloco-1-e4-e5)
  - [7.22 Bloco 2 — registros: E8, E9, E10, E11](#722-bloco-2--registros-e8-e9-e10-e11)
  - [7.23 Bloco 3 — E16: índice gravado em arquivo](#723-bloco-3--e16-índice-gravado-em-arquivo)
  - [7.24 Bloco 4 — intercalação: E17, E18, E19](#724-bloco-4--intercalação-e17-e18-e19)
  - [7.25 Bloco 5 — agrupamento, lacuna e janela: E20, E21, E22](#725-bloco-5--agrupamento-lacuna-e-janela-e20-e21-e22)
  - [7.26 Bloco 6 — imagens BMP: E23 a E28](#726-bloco-6--imagens-bmp-e23-a-e28)
  - [7.27 Mais enunciados → técnica (complementa o 7.20)](#727-mais-enunciados--técnica-complementa-o-720)
  - [7.28 Mapa: API da prova × `ArvoreB.c` de estudo](#728-mapa-api-da-prova--arvorebc-de-estudo)
  - [7.29 Checklist — antes de entregar um exercício de programação](#729-checklist--antes-de-entregar-um-exercício-de-programação)
  - [7.30 Pontos básicos da P1 que a P2 usa (resumo para consulta)](#730-pontos-básicos-da-p1-que-a-p2-usa-resumo-para-consulta)
  - [7.31 Lembretes da P1 (contas e últimos lembretes)](#731-lembretes-da-p1-contas-e-últimos-lembretes)

### 🧠 Fechamento

- [Ideia central da matéria (P1 + P2)](#-ideia-central-da-matéria)

---

# 1. Conceitos principais

> Esta parte concentra os fundamentos que mais aparecem nos exercícios. As funções ficam na Parte 2; aqui importa entender **o que está acontecendo**.

## 1.1 Arquivo, `FILE *` e posição atual

Um arquivo aberto é controlado por um `FILE`.

```c
FILE *f;
```

`f` é um **ponteiro para `FILE`**. O `FILE` guarda informações como posição atual, buffer e estado do arquivo.

Quando fazemos:

```c
f = fopen("cep.dat", "rb");
```

`fopen` devolve um `FILE *`.

Todo arquivo aberto possui uma **posição atual**:

```text
ARQUIVO
┌────┬────┬────┬────┬────┬────┐
│ 00 │ 01 │ 02 │ 03 │ 04 │ 05 │
└────┴────┴────┴────┴────┴────┘
  ↑
posição atual
```

Uma leitura avança essa posição. Um `fseek` muda a posição.

### Resumo

```text
fread  → lê e AVANÇA
fgetc  → lê 1 byte e AVANÇA
fseek  → MOVE a posição
ftell  → INFORMA a posição
rewind → VOLTA ao início
```

---

## 1.2 `struct`, registros e tamanho fixo

Uma `struct` agrupa campos:

```c
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
```

Neste exercício:

```text
72 + 72 + 72 + 72 + 2 + 8 + 2
= 300 bytes
```

Mas, no código, prefira:

```c
sizeof(Endereco)
```

porque o compilador pode inserir bytes de alinhamento (*padding*).

O `cep` é a **chave** usada para ordenar e buscar.

Os registros têm tamanho fixo. Essa é a ideia que permite:

```text
BYTES ÷ sizeof(Tipo) → quantidade de registros
REGISTROS × sizeof(Tipo) → posição em bytes
```

### Vetores começam em 0

```text
1º registro → índice 0
2º registro → índice 1
5º registro → índice 4
nº registro → índice n - 1
```

Isso vale para vetores e blocos de `malloc`.

---

## 1.3 Ponteiros: `*`, `&`, `.` e `->`

### `*` na declaração

```c
Endereco *e;
```

significa:

> `e` é um ponteiro para `Endereco`.

### `*` em uma expressão

```c
*e
```

significa:

> conteúdo que está no endereço guardado em `e`.

### `&`

```c
Endereco e;
&e
```

significa:

> endereço de `e`.

### `.`

Usado quando temos a própria struct:

```c
Endereco e;
e.cep
```

### `->`

Usado quando temos um ponteiro para a struct:

```c
Endereco *e;
e->cep
```

É equivalente a:

```c
(*e).cep
```

### Regra visual

```text
Endereco e;

e   → struct
&e  → endereço da struct
```

```text
Endereco *e;

e   → endereço
*e  → struct apontada
```

---

## 1.4 Bytes × registros

`fseek` trabalha em **bytes**.

Se cada `Endereco` ocupa 300 bytes:

```text
registro 0 → byte 0
registro 1 → byte 300
registro 2 → byte 600
registro 499 → byte 149700
```

Logo:

```c
fseek(f, 499 * sizeof(Endereco), SEEK_SET);
```

vai para o registro 499.

### Medir um arquivo de registros

```c
fseek(f, 0, SEEK_END);

long bytes = ftell(f);
long qtd = bytes / sizeof(Endereco);

rewind(f);
```

Se:

```text
300000 bytes
```

e:

```text
sizeof(Endereco) = 300
```

então:

```text
300000 / 300 = 1000 registros
```

### `SEEK_END` não é o último registro

```c
fseek(f, 0, SEEK_END);
```

vai para o **fim do arquivo**, depois do último byte.

Para ler o último registro:

```c
fseek(f, -(long)sizeof(Endereco), SEEK_END);
fread(&e, sizeof(Endereco), 1, f);
```

### `ftell` retorna `long`

```c
long pos = ftell(f);
printf("%ld\n", pos);
```

Use `long` também para tamanho/quantidade derivados de `ftell`.

---

## 1.5 Memória: `Tipo x` × `Tipo *x`

### Um registro

```c
Endereco e;
```

Um único registro. Não precisa de `malloc`.

```c
fread(&e, sizeof(Endereco), 1, f);
```

### Vários registros

```c
Endereco *e;

e = malloc(qtd * sizeof(Endereco));
```

Agora existe espaço para `qtd` registros:

```c
e[i].cep
```

O bloco pode ser liberado com:

```c
free(e);
```

### Por que usar `malloc`?

Quando a quantidade só é conhecida durante a execução:

```c
long qtd = tamanhoBytes / sizeof(Endereco);

Endereco *e = malloc(qtd * sizeof(Endereco));
```

### Regra

```text
malloc → reserva
free   → libera
```

Todo `malloc` deve ter seu `free`.

Sempre teste:

```c
if(e == NULL){
    fprintf(stderr, "Erro ao alocar memoria\n");
    return 1;
}
```

`FILE *` é diferente:

```text
FILE * → fopen / fclose
memória → malloc / free
```

Não fazemos `malloc`/`free` para o `FILE *` devolvido por `fopen`.

### `memset`

Preenche uma região da memória em bytes:

```c
memset(p, 0, quantidade_de_bytes);
```

Exemplo:

```c
Pessoa p[1000];

memset(p, 0, sizeof(p));
```

---

## 1.6 `EOF` × `feof`

Não são a mesma coisa.

```text
EOF      → valor especial retornado por fgetc/getc
feof(f)  → função que testa o estado de fim do arquivo
```

`EOF` não é um byte gravado no arquivo.

Para `fgetc`, use:

```c
int c;
```

e não `char`, porque `fgetc` precisa conseguir representar os valores dos bytes **e** `EOF`.

### Pegadinha do `feof`

`feof(f)` só fica verdadeiro **depois que uma leitura tenta passar do fim**.

Por isso, no modelo usado na intercalação:

```text
LER
 ↓
TESTAR
 ↓
USAR
 ↓
LER DE NOVO
```

Evite:

```c
while(!feof(f)){
    fread(&e, sizeof(e), 1, f);
    fwrite(&e, sizeof(e), 1, out);
}
```

A leitura pode falhar e o código ainda usar o registro anterior.

---

## 1.7 `argc` e `argv`

Servem para receber argumentos do terminal.

Com:

```bash
./programa origem.dat destino.dat
```

temos:

```text
argc = 3

argv[0] = "./programa"
argv[1] = "origem.dat"
argv[2] = "destino.dat"
```

O nome do programa conta.

Sempre confira `argc` antes de usar os argumentos:

```c
if(argc != 3){
    fprintf(stderr, "USO: %s origem destino\n", argv[0]);
    return 1;
}
```

Se o programa usa um nome fixo:

```c
fopen("cep.dat", "rb");
```

não precisa de `argc`/`argv` para esse nome.

---

## 1.8 Bytes e ASCII

Um byte tem:

```text
8 bits
2⁸ = 256 valores
0 até 255
```

Alguns valores ASCII:

| Valor | 48 | 65 | 66 | 97 | 98 |
|---|---:|---:|---:|---:|---:|
| Caractere | `'0'` | `'A'` | `'B'` | `'a'` | `'b'` |

Por exemplo:

```c
printf("%c", 65);   // A
printf("%d", 65);   // 65
```

O valor é o mesmo; muda a interpretação usada na impressão.

---

# 2. Funções principais

> Consulte esta parte quando esquecer **sintaxe, parâmetros, retorno ou cuidado** de uma função.

## 2.1 `fopen` / `fclose`

### `fopen`

```c
FILE *f = fopen(nome, modo);
```

Recebe:

```text
nome do arquivo
modo
```

Retorna:

```text
FILE * → sucesso
NULL   → falha
```

Exemplo:

```c
FILE *f = fopen("cep.dat", "rb");

if(f == NULL){
    fprintf(stderr, "Erro ao abrir arquivo\n");
    return 1;
}
```

### Modos mais usados

| Modo | Lê | Escreve | Cria | Apaga conteúdo |
|---|:---:|:---:|:---:|:---:|
| `rb` | ✅ | ❌ | ❌ | ❌ |
| `wb` | ❌ | ✅ | ✅ | ⚠️ sim |
| `r+b` | ✅ | ✅ | ❌ | ❌ |
| `ab` | ❌ | ✅ no final | ✅ | ❌ |
| `w+` | ✅ | ✅ | ✅ | ⚠️ sim |

```text
r = read
w = write
a = append
+ = lê e escreve
b = binary
```

Arquivos de registros/structs:

```text
rb / wb / r+b / ab
```

### `fclose`

```c
fclose(f);
```

Todo `fopen` deve ter um `fclose`.

Errado:

```c
fclose(*f);
```

Certo:

```c
fclose(f);
```

Se um segundo `fopen` falhar, feche o primeiro:

```c
saida = fopen("saida.dat", "wb");

if(!saida){
    fclose(entrada);
    return 1;
}
```

---

## 2.2 `fgetc` / `fputc`

### `fgetc`

Lê **1 byte**:

```c
int c = fgetc(f);
```

Retorna:

```text
byte lido
ou
EOF
```

### `fputc`

Escreve 1 byte:

```c
fputc(c, f);
```

Ordem:

```c
fputc(byte, arquivo);
```

### Molde

```c
int c;

c = fgetc(entrada);

while(c != EOF){
    /* usa c */
    c = fgetc(entrada);
}
```

---

## 2.3 `fread` / `fwrite`

Trabalham com itens/registros/blocos.

```text
fread  → ARQUIVO → MEMÓRIA
fwrite → MEMÓRIA → ARQUIVO
```

### Sintaxe

```c
fread(destino, sizeof(Tipo), quantidade, arquivo);

fwrite(origem, sizeof(Tipo), quantidade, arquivo);
```

Lembre:

```text
ONDE? TAMANHO? QUANTOS? QUAL ARQUIVO?
```

### Retorno

Retornam a quantidade de **itens**, não bytes.

```c
fread(v, sizeof(Endereco), 100, f);
```

Se leu 100 registros:

```text
retorno = 100
```

### `&`

Struct simples:

```c
Endereco e;

fread(&e, sizeof(Endereco), 1, f);
```

Ponteiro:

```c
Endereco *e;

fread(e, sizeof(Endereco), qtd, f);
```

Array:

```c
Pessoa p[1000];

fwrite(p, sizeof(Pessoa), 1000, f);
```

Regra:

```text
struct simples → &e
ponteiro       → e
array          → array
```

### `fread` avança

```c
fread(&e, sizeof(Endereco), 1, f);
```

Depois da leitura, a posição já está no próximo registro.

---

## 2.4 `fseek` / `ftell` / `rewind` / `feof`

### `fseek`

```c
fseek(arquivo, deslocamento, origem);
```

O deslocamento é em **bytes**.

| Origem | A partir de |
|---|---|
| `SEEK_SET` | início |
| `SEEK_CUR` | posição atual |
| `SEEK_END` | fim |

Exemplos:

```c
fseek(f, 300, SEEK_SET);     // byte 300
fseek(f, -300, SEEK_CUR);    // volta 300 bytes
fseek(f, 0, SEEK_END);       // fim
```

Para registro `n`:

```c
fseek(f, n * sizeof(Endereco), SEEK_SET);
```

Não:

```c
fseek(f, n, SEEK_SET);       // ❌ n é registro, fseek quer bytes
```

### `ftell`

```c
long pos = ftell(f);
```

Informa a posição em bytes desde o início.

```c
printf("%ld\n", pos);
```

### `rewind`

```c
rewind(f);
```

Volta ao começo.

Muito usado depois de medir:

```c
fseek(f, 0, SEEK_END);
long bytes = ftell(f);
rewind(f);
```

### `feof`

```c
feof(f)
```

Testa o estado de fim do arquivo, mas só fica verdadeiro depois de uma tentativa de leitura que passa do fim.

---

## 2.5 `malloc` / `free` / `sizeof` / `memset`

### `malloc`

```c
Endereco *e = malloc(qtd * sizeof(Endereco));
```

Recebe **bytes** e devolve o endereço do bloco.

```c
if(e == NULL){
    fprintf(stderr, "Erro ao alocar memoria\n");
    return 1;
}
```

### `free`

```c
free(e);
```

Libera memória reservada por `malloc`.

### `sizeof`

```c
sizeof(Endereco)
```

= tamanho de **um** `Endereco`, em bytes.

Não é o tamanho do arquivo.

### `memset`

```c
memset(destino, valor, quantidade_de_bytes);
```

Exemplo:

```c
memset(v, 0, qtd * sizeof(Endereco));
```

---

## 2.6 Strings

Funções usadas:

```text
strcpy
strncpy
strncmp
sprintf
printf
fgets
```

### Copiar

```c
strcpy(destino, origem);
```

ou:

```c
strncpy(destino, origem, tamanho);
```

Array não recebe string com `=`:

```c
p.nome = "Renato";       // ❌
strcpy(p.nome, "Renato"); // ✅
```

### Comparar

```c
int r = strncmp(a, b, 8);
```

```text
r < 0 → a vem antes
r = 0 → iguais
r > 0 → a vem depois
```

Para CEP:

```c
strncmp(e1.cep, e2.cep, 8)
```

### `sprintf`

Monta uma string:

```c
char nome[20];

sprintf(nome, "cep_%d.dat", i);
```

### `printf` com precisão

```c
printf("%.8s\n", e.cep);
```

Imprime no máximo 8 caracteres.

Para campos fixos:

```c
char cep[8];
```

não conte necessariamente com `'\0'` dentro dos 8 bytes. Por isso o tamanho precisa ser tratado explicitamente.

### Especificadores usados

```text
%d   → int
%ld  → long
%c   → caractere
%s   → string
%.Ns → no máximo N caracteres
%f   → float/double
```

---

## 2.7 `qsort` / `compara`

### `qsort`

```c
qsort(onde, quantidade, sizeof(Tipo), compara);
```

Exemplo:

```c
qsort(e, qtd, sizeof(Endereco), compara);
```

Os parâmetros são:

```text
ONDE
QUANTOS
TAMANHO
COMPARADOR
```

A função vai **sem parênteses**:

```c
qsort(e, qtd, sizeof(Endereco), compara);   // ✅
qsort(e, qtd, sizeof(Endereco), compara()); // ❌
```

### Comparar `Endereco`

```c
int compara(const void *a, const void *b){
    return strncmp(
        ((Endereco*)a)->cep,
        ((Endereco*)b)->cep,
        8
    );
}
```

O `qsort` é genérico e recebe `const void *`. O casting diz qual é o tipo real:

```c
(Endereco*)a
```

### Comparar índice

Se o bloco é `IndiceCep`, o casting também deve ser `IndiceCep*`:

```c
int compara(const void *a, const void *b){
    return strncmp(
        ((IndiceCep*)a)->cep,
        ((IndiceCep*)b)->cep,
        8
    );
}
```

Regra:

```text
qsort(..., sizeof(Tipo), compara)
                 ↓
compara faz casting para Tipo*
```

Para chave numérica:

```c
int comparaNumero(const void *a, const void *b){
    long x = ((Registro*)a)->valor;
    long y = ((Registro*)b)->valor;

    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}
```

---

# 3. Padrões de programas

> Aqui ficam as **receitas**. A Parte 2 explica as funções; esta parte mostra como combiná-las.

## 3.1 Leitura sequencial byte a byte

Use quando o exercício trabalha com caracteres/bytes:

```text
LER → TESTAR → USAR → LER DE NOVO
```

Molde:

```c
int c;

c = fgetc(entrada);

while(c != EOF){
    /* tarefa */
    c = fgetc(entrada);
}
```

### Copiar

```c
fputc(c, saida);
```

### Contar linhas

```c
if(c == '\n'){
    count++;
}
```

### Contar cada byte

```c
int contador[256] = {0};

contador[c]++;
```

Depois:

```c
for(int i = 0; i < 256; i++){
    if(contador[i] > 0){
        printf("%c: %d\n", i, contador[i]);
    }
}
```

Se o exercício pedir somente letras:

```c
if(contador[i] > 0 &&
   ((i >= 'A' && i <= 'Z') ||
    (i >= 'a' && i <= 'z'))){
    printf("%c: %d\n", i, contador[i]);
}
```

---

## 3.2 Leitura sequencial de registros

Para ler um registro por vez:

```c
Endereco e;

fread(&e, sizeof(Endereco), 1, f);

while(!feof(f)){
    /* tarefa */
    fread(&e, sizeof(Endereco), 1, f);
}
```

Forma alternativa, sem `feof`:

```c
while(fread(&e, sizeof(Endereco), 1, f) == 1){
    /* tarefa */
}
```

### Regra importante

```text
Endereco e
```

é suficiente quando só precisamos do registro atual.

Não use:

```c
Endereco *e = malloc(qtd * sizeof(Endereco));
```

se o exercício diz para processar um registro por vez.

---

## 3.3 Ordenar arquivo inteiro

Use quando o arquivo inteiro cabe na memória.

Fluxo:

```text
medir arquivo
    ↓
malloc
    ↓
fread
    ↓
qsort
    ↓
fwrite
    ↓
free
```

Modelo:

```c
f = fopen("cep.dat", "rb");

fseek(f, 0, SEEK_END);
long bytes = ftell(f);
long qtd = bytes / sizeof(Endereco);
rewind(f);

Endereco *e = malloc(qtd * sizeof(Endereco));

if(e == NULL){
    fclose(f);
    return 1;
}

fread(e, sizeof(Endereco), qtd, f);

qsort(e, qtd, sizeof(Endereco), compara);

saida = fopen("cep-ordenado.dat", "wb");
fwrite(e, sizeof(Endereco), qtd, saida);

fclose(saida);
fclose(f);
free(e);
```

### Ideia

```text
ARQUIVO
   ↓ fread
MEMÓRIA
   ↓ qsort
MEMÓRIA ORDENADA
   ↓ fwrite
ARQUIVO ORDENADO
```

---

## 3.4 Busca binária direta

### Pré-requisito

O arquivo precisa estar **ordenado pela chave**.

Não existe:

```c
arquivo[meio]
```

porque o arquivo está no disco.

A busca usa:

```text
fseek → fread → compara
```

a cada tentativa.

Modelo:

```c
long inicio = 0;
long fim = qtd - 1;

while(inicio <= fim){
    long meio = (inicio + fim) / 2;

    fseek(f, meio * sizeof(Endereco), SEEK_SET);
    fread(&e, sizeof(Endereco), 1, f);

    int resultado = strncmp(argv[1], e.cep, 8);

    if(resultado == 0){
        /* achou */
        break;
    }else if(resultado > 0){
        inicio = meio + 1;
    }else{
        fim = meio - 1;
    }
}
```

### Lógica

```text
procurado == atual → achou
procurado > atual  → direita
procurado < atual  → esquerda
```

### Atenção

Cada tentativa precisa de um novo:

```c
fseek(...)
```

Se o código só faz um `fseek` até o meio e depois continua lendo sequencialmente, não está fazendo a busca binária completa.

---

## 3.5 Índice

O índice é um atalho:

```text
CHAVE → POSIÇÃO NO ARQUIVO ORIGINAL
```

Estrutura:

```c
struct indiceCep{
    char cep[8];
    long posicao;
};

typedef struct indiceCep IndiceCep;
```

### Construção

O arquivo original não precisa ser carregado inteiro.

```c
Endereco e;
IndiceCep *indice;

fseek(f, 0, SEEK_END);

long bytes = ftell(f);
long qtd = bytes / sizeof(Endereco);

indice = malloc(qtd * sizeof(IndiceCep));

rewind(f);

for(long i = 0; i < qtd; i++){
    fread(&e, sizeof(Endereco), 1, f);

    strncpy(indice[i].cep, e.cep, 8);
    indice[i].posicao = i;
}
```

Visualmente:

```text
registro 0 → e → indice[0]
registro 1 → e → indice[1]
registro 2 → e → indice[2]
```

O `e` é reutilizado.

### Ordenar

```c
qsort(indice, qtd, sizeof(IndiceCep), compara);
```

### Buscar no índice

```c
long inicio = 0;
long fim = qtd - 1;

while(inicio <= fim){
    long meio = (inicio + fim) / 2;

    int resultado =
        strncmp(argv[1], indice[meio].cep, 8);

    if(resultado == 0){
        long posicao = indice[meio].posicao;

        fseek(
            f,
            posicao * sizeof(Endereco),
            SEEK_SET
        );

        fread(&e, sizeof(Endereco), 1, f);

        break;
    }else if(resultado > 0){
        inicio = meio + 1;
    }else{
        fim = meio - 1;
    }
}
```

### O ponto mais importante

Ordenar o índice **não muda** a posição armazenada.

Antes:

```text
22222222 → 0
11111111 → 1
55555555 → 2
```

Depois do `qsort`:

```text
11111111 → 1
22222222 → 0
55555555 → 2
```

A entrada mudou de lugar no índice, mas `22222222` continua apontando para o registro 0 do arquivo original.

### Busca direta × índice

| | Busca binária direta | Índice |
|---|---|---|
| Arquivo original ordenado? | Sim | Não |
| Onde compara? | Arquivo | Índice na memória |
| `fseek` | A cada tentativa | Só depois de encontrar |
| Guarda arquivo inteiro na memória? | Não | Não |
| Guarda índice na memória? | Não | Sim |

---

## 3.6 Ordenação externa

Use quando o arquivo inteiro **não cabe na memória**.

Fluxo:

```text
arquivo grande
     ↓
contar registros
     ↓
dividir em partes
     ↓
qsort de cada parte
     ↓
arquivos temporários ordenados
     ↓
intercalar 2 a 2
     ↓
repetir
     ↓
1 arquivo final
```

### Divisão

```c
#define PARTES 8

fseek(cep, 0, SEEK_END);

long tamanho = ftell(cep);
long quantidade = tamanho / sizeof(Endereco);

long divisao = quantidade / PARTES;
long resto = quantidade % PARTES;

rewind(cep);
```

Exemplo com 100 registros:

```text
100 / 8 = 12
100 % 8 = 4
```

Então:

```text
13 13 13 13 12 12 12 12
```

O resto vai para as primeiras partes.

```c
long quantidadeParte = divisao;

if(i < resto){
    quantidadeParte++;
}
```

### Memória

A maior parte pode ter:

```text
divisao + 1
```

registros.

Então:

```c
e = malloc((divisao + 1) * sizeof(Endereco));
```

### Ordenar cada parte

```c
for(int i = 0; i < PARTES; i++){
    long quantidadeParte = divisao;

    if(i < resto){
        quantidadeParte++;
    }

    fread(e, sizeof(Endereco), quantidadeParte, cep);

    qsort(
        e,
        quantidadeParte,
        sizeof(Endereco),
        compara
    );

    sprintf(nome, "cep_%d.dat", i);

    FILE *parte = fopen(nome, "wb");

    fwrite(
        e,
        sizeof(Endereco),
        quantidadeParte,
        parte
    );

    fclose(parte);
}
```

Não precisamos de `fseek` entre as partes porque cada `fread` continua de onde o anterior parou.

### Intercalação

Dois arquivos ordenados:

```text
A: 100 300 500 700
B: 200 400 600 800
```

Comparamos os atuais:

```text
100 × 200 → grava 100 → lê próximo de A
300 × 200 → grava 200 → lê próximo de B
300 × 400 → grava 300 → lê próximo de A
...
```

Precisamos apenas de:

```c
Endereco ea, eb;
```

Um registro atual de cada arquivo.

### Modelo

```c
void intercala(char *arqA, char *arqB, char *arqSaida){
    FILE *a, *b, *saida;
    Endereco ea, eb;

    a = fopen(arqA, "rb");
    b = fopen(arqB, "rb");
    saida = fopen(arqSaida, "wb");

    if(!a || !b || !saida){
        fprintf(stderr, "Arquivo nao pode ser aberto.\n");
        return;
    }

    fread(&ea, sizeof(Endereco), 1, a);
    fread(&eb, sizeof(Endereco), 1, b);

    while(!feof(a) && !feof(b)){
        if(compara(&ea, &eb) < 0){
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, a);
        }else{
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, b);
        }
    }

    while(!feof(a)){
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread(&ea, sizeof(Endereco), 1, a);
    }

    while(!feof(b)){
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread(&eb, sizeof(Endereco), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}
```

A lógica da intercalação é:

```text
LER os dois
   ↓
TESTAR
   ↓
gravar o menor
   ↓
ler novamente daquele arquivo
```

### Quantidade de intercalações

Cada intercalação faz:

```text
2 arquivos → 1 arquivo
```

Portanto:

```text
PARTES - 1
```

intercalações.

Com 8:

```text
8 → 7 → 6 → 5 → 4 → 3 → 2 → 1
```

São 7 intercalações.

### Nomes com `PARTES = 8`

```text
cep_0 + cep_1   → cep_8
cep_2 + cep_3   → cep_9
cep_4 + cep_5   → cep_10
cep_6 + cep_7   → cep_11

cep_8 + cep_9   → cep_12
cep_10 + cep_11 → cep_13

cep_12 + cep_13 → cep_14
```

O arquivo final é:

```text
cep_14.dat
```

O `for` usado no modelo:

```c
int arquivoNome = PARTES;

for(int i = 0; i < (PARTES - 1) * 2; i += 2){
    char nome1[20];
    char nome2[20];
    char nome3[20];

    sprintf(nome1, "cep_%d.dat", i);
    sprintf(nome2, "cep_%d.dat", i + 1);
    sprintf(nome3, "cep_%d.dat", arquivoNome);

    intercala(nome1, nome2, nome3);

    arquivoNome++;
}
```

Por que:

```c
i += 2
```

Porque usamos dois arquivos por vez.

Com 8:

```text
(PARTES - 1) * 2
= 7 * 2
= 14
```

Então:

```text
i = 0, 2, 4, 6, 8, 10, 12
```

São exatamente 7 voltas.

---

## 3.7 Busca sequencial em arquivo de registros

### Arquivo não ordenado

Lemos até encontrar ou acabar:

```c
Endereco e;
int achou = 0;

fread(&e, sizeof(Endereco), 1, f);

while(!feof(f)){
    if(strncmp(argv[1], e.cep, 8) == 0){
        achou = 1;
        break;
    }

    fread(&e, sizeof(Endereco), 1, f);
}
```

Não precisa de `fseek`.

### Arquivo ordenado

Podemos parar quando passarmos da chave:

```text
ANTES  → continua
IGUAL  → faz
DEPOIS → break
```

```c
fread(&e, sizeof(Endereco), 1, f);

while(!feof(f)){
    int r = strncmp(argv[1], e.cep, 8);

    if(r == 0){
        achou = 1;
        break;
    }else if(r < 0){
        break;
    }

    fread(&e, sizeof(Endereco), 1, f);
}
```

Se houver chave repetida e o exercício pedir soma/contagem:

```text
IGUAL → faz e CONTINUA
DEPOIS → break
```

---

## 3.8 Outros padrões de enunciado

### Agrupamento: "para cada ano"

Se os registros estão ordenados pela chave:

```text
1. pegar o primeiro grupo
2. ler enquanto a chave for igual
3. quando mudar, fechar o grupo
4. começar o próximo
5. depois do laço, tratar o último grupo
```

Atenção:

> O último grupo não tem uma mudança depois dele para disparar o processamento. Por isso ele precisa ser tratado depois do laço.

### Ano + mês

Se precisa ordenar/comparar ano e mês juntos:

```c
int chave = ano * 100 + mes;
```

Exemplo:

```text
2026 / 09 → 202609
2026 / 10 → 202610
```

### Adicionar no final

Use:

```c
fopen("arquivo.dat", "ab");
```

Não:

```c
fopen("arquivo.dat", "wb");
```

porque `wb` apaga o conteúdo existente.

### Último registro

```c
fseek(f, -(long)sizeof(Endereco), SEEK_END);
fread(&e, sizeof(Endereco), 1, f);
```

### Voltar depois de `fread`

Se acabou de ler um registro, a posição já está **depois dele**.

Para voltar um registro:

```c
fseek(f, -(long)sizeof(Endereco), SEEK_CUR);
```

### Lacuna

Se os valores deveriam ser consecutivos:

```c
if(atual != anterior + 1){
    /* existe lacuna */
}
```

### Janela móvel

Se o exercício pede uma janela de tamanho `k`:

```text
lê k registros
processa
volta k - 1 registros
avança a janela
```

A ideia do deslocamento:

```c
fseek(f, -(long)((k - 1) * sizeof(Tipo)), SEEK_CUR);
```

### Intercalação com soma

Se duas chaves são iguais:

```text
IGUAL → soma → avança os dois arquivos
```

---

# 4. Pegadinhas e lógica

## 📁 Arquivos

- `fopen` devolve `FILE *` ou `NULL`.
- `fclose(f)`, nunca `fclose(*f)`.
- Todo `fopen` precisa de `fclose`.
- Se o segundo `fopen` falhar, feche o primeiro.
- `wb` apaga o conteúdo anterior.
- `ab` adiciona no final.
- Arquivos de registros usam modo binário.
- `FILE *` usa `fopen`/`fclose`, não `malloc`/`free`.

## 📖 Leitura

- `fgetc` → `int`, não `char`.
- `EOF` não é um byte gravado.
- `feof` só fica verdadeiro depois de uma tentativa de leitura além do fim.
- No padrão com `feof`: **ler → testar → usar → ler de novo**.
- `fread`/`fwrite` retornam **itens**, não bytes.
- `fread` lê da posição atual e avança.
- Struct simples → `&e`.
- Ponteiro → `e`.
- Array → nome do array.

## 📍 Posição

- `fseek` trabalha em bytes.
- Registro → bytes: `registro * sizeof(Tipo)`.
- `meio`, `i` e `posicao` normalmente representam **número de registro**, começando em 0.
- `SEEK_END` vai para o fim, não para o último registro.
- Depois de `SEEK_END` + `ftell`, use `rewind` se for voltar a ler desde o começo.
- `ftell` retorna `long`.
- `%ld` para `long`.
- Depois de `fread`, a posição já avançou.

## 🧠 Memória

- `malloc` reserva.
- `free` libera.
- Todo `malloc` deve ter `free`.
- Teste `malloc == NULL`.
- `Endereco e` → um registro.
- `Endereco *e` → bloco de registros.
- Vetores começam em índice 0.
- `sizeof(Tipo)` → tamanho de um item, não do arquivo.
- `memset` trabalha em bytes.

## 🔤 Strings

- Array não recebe string com `=`.
- `strcpy`/`strncpy` copiam.
- `strncmp(a, b, 8)` compara 8 caracteres.
- `printf("%.8s", ...)` limita a impressão.
- Campos fixos podem não possuir `'\0'`.
- `.` → struct.
- `->` → ponteiro para struct.

## 🔢 Ordenação

- `qsort(v, qtd, sizeof(Tipo), compara)`.
- `compara` vai sem `()`.
- `sizeof` precisa corresponder ao tipo ordenado.
- O casting de `compara` também precisa corresponder ao tipo ordenado.
- CEP → `strncmp`.
- Chave numérica → comparação numérica.

## 🔎 Busca

- Busca binária direta exige arquivo ordenado.
- Cada tentativa da busca binária faz um novo `fseek`.
- `meio` começa em 0.
- `fseek` recebe `meio * sizeof(Endereco)`.
- Busca sequencial não precisa de `fseek`.
- Arquivo ordenado: **ANTES continua · IGUAL faz · DEPOIS break**.

## 📇 Índice

- Índice = **chave + posição**.
- A posição é do arquivo original.
- Ordenar o índice não altera as posições.
- A busca binária acontece no índice.
- Depois de encontrar, `fseek` vai até a posição no arquivo original.

## 📦 Ordenação externa

- Usada quando o arquivo não cabe inteiro na memória.
- Divide em `PARTES`.
- `divisao = quantidade / PARTES`.
- `resto = quantidade % PARTES`.
- Resto vai para as primeiras partes.
- `malloc((divisao + 1) * sizeof(Endereco))` comporta a maior parte.
- `qsort` cada parte.
- Fecha cada arquivo temporário.
- Intercala 2 a 2.
- Cada intercalação reduz 1 arquivo.
- Intercalações = `PARTES - 1`.
- Com 8 partes → 7 intercalações.
- `i += 2`.
- Com 8 partes → `i < (PARTES - 1) * 2`.
- Não subtraia o `1` duas vezes.
- Resultado final com 8 partes → `cep_14.dat`.

## 🧭 Como transformar o enunciado em código

Antes de escrever, pergunte:

```text
É leitura de bytes?
É leitura sequencial de registros?
Preciso acessar um registro específico?
O arquivo está ordenado?
Preciso de busca binária?
Preciso de índice?
O arquivo cabe na memória?
Preciso de ordenação externa?
É uma janela?
É agrupamento por uma chave?
```

Depois identifique os três casos:

```text
ANTES  → continua
IGUAL  → faz
DEPOIS → break
```

Essa divisão resolve muitos exercícios de busca ordenada.

## ✅ Antes de entregar

```text
[ ] Todo fopen foi testado?
[ ] Todo fopen tem fclose?
[ ] Todo malloc foi testado?
[ ] Todo malloc tem free?
[ ] ftell está em long?
[ ] %ld para long?
[ ] fgetc usa int?
[ ] fseek recebeu bytes?
[ ] Registro começa em índice 0?
[ ] Usei & quando precisava?
[ ] Usei . ou -> corretamente?
[ ] qsort recebeu compara sem ()?
[ ] sizeof corresponde ao tipo?
[ ] return 0; no final do main?
```

---

# 5. Folha de Cola

## 5.1 Bibliotecas

```c
#include <stdio.h>      // FILE, fopen, fclose, fgetc, fputc,
                        // fread, fwrite, fseek, ftell, rewind,
                        // feof, printf, fprintf, sprintf

#include <stdlib.h>     // malloc, free, qsort

#include <string.h>     // strcpy, strncpy, strncmp, memset
```

---

## 5.2 Struct

### Exemplo

```c
struct Casos{
    int dia;
    int novos_casos;
    int obitos;
};
typedef struct Casos Casos;
```

### Acesso

```c
Endereco e;
Endereco *p;
```

```text
e.cep   → quando você tem a struct em si (Endereco e;)
p->cep  → quando você tem um ponteiro para a struct
```

---

## 5.3 `argc` / `argv`

```c
int main(int argc, char **argv)
```

```c
if(argc != 3){
    fprintf(stderr, "USO: %s origem destino\n", argv[0]);
    return 1;
}

fopen(argv[1], "rb");
fopen(argv[2], "wb");
```

---

## 5.4 Arquivos

### Abrir / testar / fechar

```c
FILE *f;

f = fopen("arquivo.dat", "rb");

if(!f){
    fprintf(stderr, "Erro ao abrir arquivo.\n");
    return 1;
}

fclose(f);
```

### Modos

```text
"rb"  → lê
"wb"  → escreve / cria / APAGA
"r+b" → lê + escreve
"ab"  → adiciona no final
```

### Dois arquivos — se o 2º falhar, feche o 1º

```c
saida = fopen(argv[2], "wb");

if(!saida){
    fclose(entrada);   // <- a diferença: fecha o que já tinha aberto
    fprintf(stderr, "Erro ao abrir arquivo de saida\n");
    return 1;
}
```

---

## 5.5 `fgetc` / `fputc`

```c
int c;

c = fgetc(f);

while(c != EOF){
    /* tarefa, ex: fputc(c, saida); */
    c = fgetc(f);
}
```

```text
fgetc → 1 byte → int
fputc → 1 byte
```

### Contar linhas

```c
int c;
int count = 0;

c = fgetc(f);

while(c != EOF){
    if(c == '\n'){
        count++;
    }
    c = fgetc(f);
}
```

### Contar cada byte

```c
int contador[256] = {0};
int c;

c = fgetc(f);

while(c != EOF){
    contador[c]++;
    c = fgetc(f);
}

for(int i = 0; i < 256; i++){
    if(contador[i] > 0){
        printf("%c: %d\n", i, contador[i]);
    }
}
```

---

## 5.6 `fread` / `fwrite`

```c
fread(&e, sizeof(Endereco), 1, f);      // um registro (struct simples → &)

fread(v, sizeof(Endereco), qtd, f);     // vários registros (ponteiro/array → sem &)
fwrite(v, sizeof(Endereco), qtd, f);
```

Ler até acabar:

```c
while(fread(&e, sizeof(Endereco), 1, f) == 1){
    /* tarefa */
}
```

---
## 5.7 `fseek` / `ftell` / `rewind`

```c
fseek(f, deslocamento, SEEK_SET); // início
fseek(f, deslocamento, SEEK_CUR); // posição atual
fseek(f, deslocamento, SEEK_END); // fim

// 5º registro → posição 4 (primeiro = posição 0)
fseek(f, 4 * sizeof(Pagamento), SEEK_SET);

// n-ésimo registro a partir do início
fseek(f, (n - 1) * sizeof(Pagamento), SEEK_SET);

// voltar n registros a partir da posição atual
fseek(f, -n * sizeof(Pagamento), SEEK_CUR);

// avançar n registros a partir da posição atual
fseek(f, n * sizeof(Pagamento), SEEK_CUR);

// n-ésimo registro a partir do fim
fseek(f, -n * sizeof(Pagamento), SEEK_END);

long pos = ftell(f); // posição atual

rewind(f); // volta ao início
```

⚠️ **Atenção ao `fread`:** ele lê o registro e **avança 1 posição**.  

```c
fread(&p, sizeof(Pagamento), 1, f); // lê → ponteiro avança 1
```

Se precisar voltar até um registro específico depois de um `fread`, pode ser necessário usar **`fseek`**.

Ex.: leu o 8º e quer ler o 6º:

```c
fseek(f, -3 * sizeof(Pagamento), SEEK_CUR);
fread(&p, sizeof(Pagamento), 1, f);
```

Caso após um `fread` tenha que fazer um `fwrite` **no mesmo registro lido**, faça:

```c
fseek(f, -1 * sizeof(Registro), SEEK_CUR);
fwrite(&r, sizeof(Registro), 1, f);
```

---

## 5.8 Ponteiros

```c
Tipo x;

x   → conteúdo
&x  → endereço
```

```c
Tipo *p;

p   → endereço
*p  → conteúdo apontado
```

```c
Endereco *e;

fread(e, sizeof(Endereco), 1, f);   // ponteiro → SEM &
```

---

## 5.9 `malloc` / `free` / `memset`

```c
Endereco *e;

e = malloc(qtd * sizeof(Endereco));

if(e == NULL){
    fprintf(stderr, "Erro ao alocar memoria\n");
    return 1;
}

free(e);
```

```text
o mesmo padrão vale pra qualquer tipo (ex: IndiceCep *indice = malloc(qtd * sizeof(IndiceCep));)
```

`memset`:

```c
memset(p, 0, 1000 * sizeof(Struct));
```

---

## 5.10 Strings

```c
strcpy(destino, origem);
strncpy(destino, origem, n);

int r = strncmp(a, b, n);
```

```text
< 0 → a antes de b
= 0 → iguais
> 0 → a depois de b
```

Criar nome:

```c
sprintf(nome, "cep_%d.dat", i);
```

Imprimir quantidade fixa:

```c
printf("%.8s", e.cep);
```

Imprimir saída de erro:

```c
fprintf(stderr, "Não foi possível abrir o arquivo %s.\n", "arquivo.dat");
```

---

## 5.11 `qsort`

```c
qsort(v, qtd, sizeof(Tipo), compara);
```

---

## 5.12 Return

```c
return        → void
return valor; → função retorna um valor
return 0;     → retorna 0 (ex.: sucesso)
return 1;     → retorna 1 (ex.: erro)
return -1;    → retorna -1 (ex.: não encontrou)
```

## 5.13 Programas para copiar e colar

### A. Copiar arquivo byte a byte

```c
#include <stdio.h>

int main(int argc, char **argv){
    FILE *entrada, *saida;
    int c;

    if(argc != 3){
        fprintf(stderr, "USO: %s origem destino\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");

    if(!entrada){
        fprintf(stderr, "Erro ao abrir arquivo de entrada\n");
        return 1;
    }

    saida = fopen(argv[2], "wb");

    if(!saida){
        fclose(entrada);
        fprintf(stderr, "Erro ao abrir arquivo de saida\n");
        return 1;
    }

    c = fgetc(entrada);

    while(c != EOF){
        fputc(c, saida);
        c = fgetc(entrada);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
```

### B. Copiar arquivo em blocos

```c
#include <stdio.h>

#define TAMANHO 8192

int main(int argc, char **argv){
    FILE *entrada, *saida;
    char buffer[TAMANHO];
    int qtd;

    if(argc != 3){
        fprintf(stderr, "USO: %s origem destino\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");

    if(!entrada){
        fprintf(stderr, "Erro ao abrir arquivo de entrada\n");
        return 1;
    }

    saida = fopen(argv[2], "wb");

    if(!saida){
        fclose(entrada);
        fprintf(stderr, "Erro ao abrir arquivo de saida\n");
        return 1;
    }

    qtd = fread(buffer, sizeof(char), TAMANHO, entrada);

    while(qtd > 0){
        fwrite(buffer, sizeof(char), qtd, saida);
        qtd = fread(buffer, sizeof(char), TAMANHO, entrada);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
```

⚠️ No último bloco: `fwrite(buffer, sizeof(char), qtd, saida);` — é `qtd`, não `TAMANHO`.

### C. Busca sequencial

**Não ordenado → só verifica se achou**

**`char[]`:**

```c
Endereco e;

while(fread(&e, sizeof(Endereco), 1, f) == 1){
    if(strncmp(chave, e.cep, 8) == 0){
        /* achou */
        break;
    }
}
```

**`int`:**

```c
Registro r;

while(fread(&r, sizeof(Registro), 1, f) == 1){
    if(id == r.id){
        /* achou */
        break;
    }
}
```

**Ordenado → pode parar quando passar da chave**

```c
int r = strncmp(chave, e.cep, 8);

if(r == 0)
    break;       // achou
else if(r < 0)
    break;       // passou da chave
// r > 0 → continua
```

Para `int`:

```c
if(id == r.id)
    break;       // achou
else if(id < r.id)
    break;       // passou
```

### D. Busca binária

**Arquivo precisa estar ordenado.**

```c
long inicio = 0, fim = qtd - 1;

while(inicio <= fim){
    long meio = (inicio + fim) / 2;

    fseek(f, meio * sizeof(Endereco), SEEK_SET);
    fread(&e, sizeof(Endereco), 1, f);

    int r = strncmp(chave, e.cep, 8);

    if(r == 0){
        /* achou */
        break;
    }else if(r > 0){
        inicio = meio + 1;
    }else{
        fim = meio - 1;
    }
}
```

```text
Binária → cada tentativa = fseek + fread
r > 0 → direita
r < 0 → esquerda
```

### E. Compara

```c
int compara(const void *a, const void *b){
    return strncmp(
        ((Endereco*)a)->cep,
        ((Endereco*)b)->cep,
        8
    );
}
```
Para int:

```c
return ((COVID *)a)->dia - ((COVID *)b)->dia;
```

### F. Índice

Estrutura:

```c
struct indiceCep{
    char cep[8];
    long posicao;
};

typedef struct indiceCep IndiceCep;
```

Construção:

```c
Endereco e;
IndiceCep *indice;

indice = malloc(qtd * sizeof(IndiceCep));

if(indice == NULL){
    return 1;
}

rewind(f);

for(long i = 0; i < qtd; i++){
    fread(&e, sizeof(Endereco), 1, f);

    strncpy(indice[i].cep, e.cep, 8);
    indice[i].posicao = i;
}

qsort(indice, qtd, sizeof(IndiceCep), compara);
```

Acessar arquivo original depois de achar, e liberar:

```c
long posicao = indice[meio].posicao;

fseek(f, posicao * sizeof(Endereco), SEEK_SET);
fread(&e, sizeof(Endereco), 1, f);

free(indice);
fclose(f);
```

```text
ordenar o índice NÃO muda a posição guardada (ela é do arquivo original)
```

### G. Ordenação externa — divisão

```c
#define PARTES 8

fseek(cep, 0, SEEK_END);

long quantidade =
    ftell(cep) / sizeof(Endereco);

long divisao = quantidade / PARTES;
long resto = quantidade % PARTES;

rewind(cep);

Endereco *e =
    malloc((divisao + 1) * sizeof(Endereco));
```

Ordenar cada parte:

```c
for(int i = 0; i < PARTES; i++){
    long quantidadeParte = divisao;

    if(i < resto){
        quantidadeParte++;
    }

    fread(e, sizeof(Endereco), quantidadeParte, cep);

    qsort(e, quantidadeParte, sizeof(Endereco), compara);

    char nome[20];
    sprintf(nome, "cep_%d.dat", i);

    FILE *parte = fopen(nome, "wb");

    fwrite(e, sizeof(Endereco), quantidadeParte, parte);

    fclose(parte);
}

free(e);
```

```text
divisao = quantidade / PARTES        i < resto  → parte com divisao + 1
resto   = quantidade % PARTES        i >= resto → parte com divisao
```

### H. Intercalação

```c
void intercala(char *arqA, char *arqB, char *arqSaida){
    FILE *a, *b, *saida;
    Endereco ea, eb;

    a = fopen(arqA, "rb");
    b = fopen(arqB, "rb");
    saida = fopen(arqSaida, "wb");

    if(!a || !b || !saida){
        fprintf(stderr, "Arquivo nao pode ser aberto.\n");
        return;
    }

    fread(&ea, sizeof(Endereco), 1, a);
    fread(&eb, sizeof(Endereco), 1, b);

    while(!feof(a) && !feof(b)){
        if(compara(&ea, &eb) < 0){
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, a);
        }else{
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, b);
        }
    }

    while(!feof(a)){
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread(&ea, sizeof(Endereco), 1, a);
    }

    while(!feof(b)){
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread(&eb, sizeof(Endereco), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}
```

### I. Intercalações — `PARTES = 8`

```c
int arquivoNome = PARTES;

for(int i = 0; i < (PARTES - 1) * 2; i += 2){
    char nome1[20];
    char nome2[20];
    char nome3[20];

    sprintf(nome1, "cep_%d.dat", i);
    sprintf(nome2, "cep_%d.dat", i + 1);
    sprintf(nome3, "cep_%d.dat", arquivoNome);

    intercala(nome1, nome2, nome3);

    arquivoNome++;
}
```

```text
PARTES = 8
intercalações = PARTES - 1 = 7
arquivo final = cep_14.dat
```
---

## 5.14 Contas e lembretes

### 📍 Posição

```text
registro n → n * sizeof(Tipo) bytes

fseek(f, n * sizeof(Tipo), SEEK_SET);
```

### 📦 Quantidade

```text
bytes / sizeof(Tipo) → registros
registros * sizeof(Tipo) → bytes
```

### 🧠 Ponteiros

```text
Tipo x;
x   → conteúdo
&x  → endereço
```

```text
Tipo *x;
x   → endereço
*x  → conteúdo apontado
```

```text
struct       → .
ponteiro     → ->
```

### 📖 Leitura

```text
fgetc → 1 byte
fread → itens/registros
```

```text
ler → testar → usar → ler de novo
```

### 🔎 Busca

```text
sequencial:
fread → compara → continua/para

binária:
meio → fseek → fread → compara
```

```text
ANTES  → continua
IGUAL  → faz
DEPOIS → break
```

### 📇 Índice

```text
índice = chave + posição original
```

```text
busca no índice → encontra posição → fseek no arquivo original → fread
```

### 📦 Ordenação externa

```text
arquivo grande → dividir → qsort cada parte →
intercalar 2 a 2 → repetir → 1 arquivo
```

```text
PARTES = 8
intercalações = PARTES - 1 = 7
arquivo final = cep_14.dat
```

### 🧮 Divisão das partes

```text
divisao = quantidade / PARTES
resto   = quantidade % PARTES

i < resto  → divisao + 1
i >= resto → divisao
```

### ⚠️ Últimos lembretes

```text
fseek(SEEK_END) → fim, não último registro
ftell() → long
fgetc() → int
fread() → retorna itens
malloc() → bytes
free() → depois do último uso
qsort(..., compara) → sem ()
wb → apaga
ab → adiciona no final
return 0 → final do main
```

---

## 5.15 CHECKLIST — ANTES DE ENTREGAR

```text
[ ] Todo fopen/malloc foi testado (== NULL)?
[ ] Todo fopen tem fclose? Todo malloc tem free?
[ ] sizeof(Tipo) bate em TODO lugar — fread, fwrite, malloc,
    fseek (n*sizeof), qsort e memset?
[ ] fseek recebeu posição em BYTES, não em "número do registro"?
[ ] ftell está em long, com %ld?   fgetc está em int?
[ ] Registro começa no índice 0?
[ ] Usei & quando precisava (struct simples)? . pra struct, -> pra ponteiro?
[ ] qsort recebeu compara SEM ()? Critério de ordenação certo?
[ ] Arquivo está ordenado quando a busca exige isso?
[ ] Não comparei strings com ==? Reservei espaço pro '\0'?
[ ] Conferi argc? argv[1]/argv[2] corretos?
[ ] return 0; no final do main?
[ ] Não li além do fim do arquivo? Nenhum ponteiro ficou sem inicializar?
```

---

# 🧪 P2 — Árvores B e B+, hash e Huffman

> Esta parte é **só da P2**. Tudo acima dela é P1. Cada assunto tem um guia completo na sua pasta; aqui fica o resumo e o caminho. A prova de base é a [P2 2026.1](provasp2/p2-2026.1.pdf) e o [mapa questão → onde estudar](provasp2/README.md#mapa-da-prova-p2-20261-questão--onde-estudar) está na pasta `provasp2/`.

## P2.1 Árvores B e B+

Guia completo: [`arvores/README.md`](arvores/README.md). Código de estudo: [`ArvoreB.c`](arvores/ArvoreB.c) e [`ArboreB.h`](arvores/ArboreB.h).

- Árvore B/B+ é um **índice em disco**: o custo é **ler bloco**, então custo da busca = **altura**.
- **Nó = um bloco.** `n` = máximo de ponteiros para filhos; chaves por nó = `n − 1`.
- **B:** chave **e** ponteiro de dado em todo nó. **B+:** ponteiro de dado **só nas folhas**, folhas **encadeadas**, mais baixa e boa para faixa.
- **Split:** o nó estoura, a chave do meio **sobe** (na folha da B+, a chave é **copiada**). Por isso todo nó não raiz fica com pelo menos `⌈n/2⌉ − 1` chaves.
- **Conta do bloco:** B `n·Pb + (n−1)(Pr+V) ≤ B`; B+ interno `n·Pb + (n−1)·V ≤ B`; folha B+ `k(V+Pr) + Pb ≤ B`. Os tamanhos `B`, `V`, `Pr`, `Pb` vêm do enunciado.
- **Código da prova (questão 4):** a árvore é um índice **chave → offset em bytes**. Pegue o offset com `ftell` **antes** do `fread`. Veja a [seção 15](arvores/README.md#15-código-da-p2-usar-a-árvore-b-como-caixa-preta).

## P2.2 Hash

Guia completo: [`hash/README.md`](hash/README.md). Scripts do trabalho dos CEPs: [`hash2.py`](hash/hash2.py), [`CriaIndice.py`](hash/CriaIndice.py), [`ProcuraIndice.py`](hash/ProcuraIndice.py), [`NUmeroColisoes.py`](hash/NUmeroColisoes.py), [`leArquivoCEP.py`](hash/leArquivoCEP.py).

- `h(k) = k mod m`, e o registro vai para `seek(posição × tamanho da entrada)`.
- **Encadeamento externo:** a área de colisão começa na posição `m`. `Próximo = 0` é o fim da lista, e o novo registro entra logo após a entrada primária.
- **Fator de carga** `α = n/m`. Acessos médios com sucesso ≈ `1 + α/2`.
- **Hash x B+:** hash é ótimo para **igualdade**, mas não serve para **faixa** nem **ordem**.
- Exemplo resolvido: [P2 2026.1 questão 2](hash/README.md#8-exemplo-completo-p2-questão-2) (11 posições primárias, 10 chaves do enunciado).

## P2.3 Código e árvore de Huffman

Guia completo: [`arvore-huf/README.md`](arvore-huf/README.md). Programas de estudo: [`contafrequencia.c`](arvore-huf/contafrequencia.c) (conta os 256 valores de byte) e [`histograma.py`](arvore-huf/histograma.py) (desenha o gráfico).

- **Algoritmo guloso com heap mínimo:** junte sempre os dois nós de **menor frequência** até sobrar um. Esquerda = 0, direita = 1, e o código é **livre de prefixo**.
- **Custo** = soma de (frequência × tamanho do código) = soma dos pesos dos nós internos. Com `n` símbolos há `n − 1` junções e `2n − 1` nós.
- **Empates** geram árvores diferentes, mas com o **mesmo custo**.
- Exemplo resolvido: [P2 2026.1 questão 1](arvore-huf/README.md#11-exercício-resolvido-p2-questão-1) (símbolos A–H do enunciado, custo 444 bits contra 492 bits com 3 bits fixos por símbolo).

## P2.4 Mapa: questão → guia de estudo

| Se a questão pede... | Faça | Guia |
|---|---|---|
| Árvore de Huffman e códigos | Heap mínimo, junte os 2 menores, esquerda 0 e direita 1 | [Huffman](arvore-huf/README.md#11-exercício-resolvido-p2-questão-1) |
| Tabela de hash com colisões | `k mod m`, colisão vai para a próxima posição livre da área de colisão e encadeia | [Hash](hash/README.md#8-exemplo-completo-p2-questão-2) |
| Desenhar árvore B ou B+ | Insira em ordem, split ao estourar, escreva a convenção usada | [B/B+](arvores/README.md#6-árvore-b-inserção) |
| Calcular `n` pelo bloco | Monte a soma de bytes, isole `n`, arredonde para baixo e faça a prova real | [B/B+](arvores/README.md#10-a-conta-do-bloco-explicada-passo-a-passo) |
| Diferença B x B+, hash, heap, split | Respostas curtas | [B/B+](arvores/README.md#14-teoria-cobrada-na-p2-respostas-modelo) |
| Código com índice em árvore B | `ftell` antes do `fread`, `insertKey`, `findKey`, `fseek` | [B/B+](arvores/README.md#15-código-da-p2-usar-a-árvore-b-como-caixa-preta) |

---

# 6. Folha de Cola da P2

> Folha para consulta na prova, no mesmo formato da [seção 5](#5-folha-de-cola) (que é a folha da P1 e cobre arquivos em C: `fseek`, `ftell`, `fread`, `qsort`, busca, índice, ordenação externa; o código da P2 reaproveita tudo isso). Aqui ficam as respostas objetivas, pior e melhor caso, funcionamento de árvore B/B+, hash e Huffman, e o código da questão 4.

| Se a questão pede... | Vá a |
|---|---|
| Explicar / diferença B × B+, hash × árvore, heap, split | [6.1](#61-respostas-objetivas-para-copiar) |
| Múltipla escolha de árvore B/B+ | 6.1.2 |
| Pior caso / melhor caso / custo | [6.2](#62-pior-caso-e-melhor-caso) |
| Calcular n pelo bloco, quantas chaves, altura | 6.3.2 e 6.3.3 |
| Desenhar inserção ou remoção em árvore B | 6.3.4 e 6.3.5 |
| Tabela de hash com colisões | [6.4](#64-hash-com-encadeamento-externo) |
| Árvore e códigos de Huffman | [6.5](#65-huffman) |
| Código com índice em árvore B (`openTree`, `findKey`...) | [6.6](#66-código-com-índice-em-árvore-b-questão-4-da-p2) |
| Qualquer código em C (arquivos, busca, `qsort`...) | [seção 5](#5-folha-de-cola) |

## 6.1 Respostas objetivas (para copiar)

### 6.1.1 Diferença entre árvore B e árvore B+

```text
ÁRVORE B   chaves E dados (ou ponteiros p/ dados) ficam em TODOS os nós,
           internos e folhas. Cada chave aparece uma vez só.

ÁRVORE B+  nós internos só têm chaves-guia (servem para direcionar a busca),
           SEM dados. Todos os dados (ou ponteiros) ficam SÓ NAS FOLHAS.
           As folhas são ENCADEADAS entre si em ordem.

POR QUE A B+ É MAIS EFICIENTE EM ARQUIVO INDEXADO
 1. nó interno sem dados → cabem MAIS chaves por bloco (fan-out maior)
    → árvore mais BAIXA → MENOS leituras de bloco
 2. folhas encadeadas → varredura sequencial e consulta por INTERVALO
    sem voltar à raiz
 3. toda busca desce até a folha → custo parecido para qualquer chave
```

### 6.1.2 Múltipla escolha (A10)

```text
Onde ficam as chaves reais (com dados) na B+?        (b) apenas nas folhas
Principal vantagem da B+ sobre a B?                  (a) busca sequencial
                                                         (folhas encadeadas)
O que é exclusivo da B e não da B+?                  (a) chaves nos nós internos
```

### 6.1.3 Hash como índice: vantagens e desvantagens

```text
VANTAGENS
  consulta por IGUALDADE: calcula h(k) e vai direto → O(1) em média
  simples e rápida quando há poucas colisões

DESVANTAGENS
  NÃO mantém a ORDEM das chaves
  NÃO atende consulta por INTERVALO (teria de varrer tudo)
  muitas colisões → listas longas → pode chegar a O(n)
```

### 6.1.4 Hash × árvore B/B+

```text
Organização  árvore: nós ligados por ponteiros      hash: função calcula a posição
Acesso       árvore: raiz → segue ponteiros         hash: vai direto à posição
                                                          (colisão: segue a lista)
Ordenação    árvore: mantém as chaves em ordem      hash: não mantém
Custo        árvore: O(log n)                       hash: O(1) médio, O(n) pior caso

Árvore B/B+ é melhor para: INTERVALO e resultado em ORDEM
   (ex.: notas entre 7 e 10; listar alunos por matrícula)
Hash é melhor para: IGUALDADE
   (ex.: buscar o aluno de matrícula 2025001)

A ordem de inserção se perde no hash porque a posição vem de h(k),
não da ordem de chegada.
```

### 6.1.5 Split e o mínimo de 50% de ocupação

```text
O nó só divide quando ESTOURA (n chaves, sendo n o grau).
A chave do meio sobe e as outras n − 1 se repartem em duas metades:
cada metade fica com pelo menos ⌈n/2⌉ − 1 chaves = o mínimo permitido.

Ex.: grau 5 → estoura com 5 chaves → 2 + (1 que sobe) + 2   (mínimo = 2) ✓
```

### 6.1.6 Huffman

```text
POR QUE USAR HEAP: a cada passo é preciso achar os 2 menores pesos e devolver
o nó novo. O heap mínimo extrai o menor e insere em O(log n); numa lista
isso custa O(n). Total: O(n log n).

QUANDO COMPENSA: quando alguns símbolos são muito mais frequentes que outros
(frequentes → código curto).

ARQUIVO JÁ COMPACTADO: bytes com frequências quase uniformes → códigos quase
todos com ~8 bits → ganho ≈ 0.

CÓDIGO LIVRE DE PREFIXO: nenhum código é começo de outro → dá para decodificar
sem separador.
```

### 6.1.7 Por que a árvore B é um bom índice em disco

```text
Cada nó = 1 bloco = 1 leitura de disco.
Custo da busca = ALTURA da árvore.
Nó grande (muitas chaves) → árvore BAIXA → poucas leituras.
Balanceada: todas as folhas no mesmo nível; cresce pela RAIZ.
```

### 6.1.8 Índice (chave → posição)

```text
O arquivo de dados não muda; o índice guarda pares (chave, posição em bytes).
Busca: acha a chave no índice → pega a posição → fseek + fread.
Vantagem: busca rápida sem ordenar o arquivo de dados.
Custo: espaço extra, e se o arquivo for reordenado o índice precisa ser refeito.
```

### 6.1.9 Custo de "arquivo2 menos arquivo1" com árvore B (D2d)

```text
uma busca na árvore B para CADA registro de arquivo2:  n2 × O(log n1)
mais a leitura sequencial de arquivo2 e a escrita da saída
→ O(n2 · log n1)
(se o índice do arquivo1 ainda precisar ser construído: O((n1 + n2) · log n1))
```


## 6.2 Pior caso e melhor caso

| Operação | Melhor caso | Pior caso |
|---|---|---|
| Busca sequencial no arquivo | 1 leitura (é o 1º registro) | n leituras (é o último ou não existe). Médio ≈ n/2 |
| Busca sequencial em arquivo **ordenado** | 1 leitura | n leituras, mas para ao passar da chave (DEPOIS → break) |
| Busca binária no arquivo | 1 (acha no meio) | ⌊log₂ n⌋ + 1 leituras, ou seja, O(log n) |
| Acesso direto por posição (`fseek` + `fread`) | O(1) | O(1) |
| Busca em árvore B | 1 leitura (chave na raiz) | h leituras (h = altura) |
| Busca em árvore B+ | h (sempre desce até a folha) | h |
| Inserção em árvore B | sem divisão: só grava a folha | divisão em **todos** os níveis: **h páginas novas + 1 raiz nova** (A6: 8 + 1 = 9) |
| Remoção em árvore B | folha com sobra: só tira a chave | fusões até a raiz (altura − 1) |
| Busca em hash | 1 acesso (sem colisão) | n acessos: todas as chaves na mesma posição, lista única (B4: 10 chaves na posição 4, 9 colisões) |
| Hash, caso médio | ≈ 1 + α/2 acessos, com α = n/m | |
| Huffman (construção) | O(n log n) com heap | O(n²) com lista sem ordem |
| Huffman (árvore) | frequências iguais → árvore equilibrada, códigos ≈ log₂ n bits | frequências muito desiguais → árvore "em escada", código de até n − 1 bits |
| Intercalação de 2 arquivos ordenados | lê cada registro **uma vez**: O(n + m) | O(n + m) |
| Ordenação externa | PARTES − 1 intercalações, cada uma percorre o arquivo todo | |

```text
altura h de uma árvore com N chaves e m filhos por nó ≈ log_m (N)
árvore cheia: N = m^h − 1  →  h = log_m (N + 1)
```


## 6.3 Árvore B e B+: como funciona e as contas

### 6.3.1 Grau, chaves e filhos

O grau **n** é o máximo de **filhos (ponteiros)**. As chaves ficam entre os ponteiros: sempre uma a menos.

```text
máximo            → n filhos   e  n − 1 chaves
mínimo (não raiz) → ⌈n/2⌉ filhos  e  ⌈n/2⌉ − 1 chaves
raiz              → mínimo 1 chave (2 filhos)
todas as folhas no mesmo nível
```

| Grau n | Chaves (máx) | Chaves (mín, não raiz) | Filhos (mín) |
|---:|---:|---:|---:|
| 3 | 2 | 1 | 2 |
| 4 | 3 | 1 | 2 |
| 5 | 4 | 2 | 3 |
| 6 | 5 | 2 | 3 |
| 7 | 6 | 3 | 4 |

⚠️ 1 chave é válido em grau 3 e 4. **0 chaves** fora da raiz não é (é o que a remoção precisa consertar).

### 6.3.2 Conta do bloco (A1, A9)

O nó inteiro tem que **caber em um bloco**. Some os bytes, isole `n` e **arredonde para baixo**.

```text
Árvore B:   n·Pb + (n−1)·(V + Pr) ≤ B
B+ interno: n·Pb + (n−1)·V ≤ B           (sem ponteiro de dados)
B+ folha:   k·(V + Pr) + Pb ≤ B          (k chaves; Pb = próxima folha)

V  = tamanho da chave          Pr = ponteiro p/ registro (arquivo de dados)
Pb = ponteiro p/ outro bloco   B  = tamanho do bloco
```

```text
A1: V=9  Pr=7  Pb=6  B=512
    6n + 16(n−1) ≤ 512  →  22n ≤ 528  →  n = 24
    prova: 24·6 + 23·16 = 144 + 368 = 512 ≤ 512 ✓
    máx 23 chaves · mín ⌈24/2⌉ − 1 = 11

B+ com os mesmos dados:  6n + 9(n−1) ≤ 512  →  15n ≤ 521  →  n = 34
    prova: 34·6 + 33·9 = 501 ✓   (com 35 daria 516 > 512)
```

Struct em C (A9), `int` = 4 bytes:

```c
struct { int qt; int chaves[N]; int valores[N]; int filhos[N+1]; }
// 4·(1 + N + N + N+1) = 12N + 8 ≤ 1024  →  N ≤ 84,67  →  N = 84
// prova: 12·84 + 8 = 1016 ≤ 1024 ✓   (N = 85 → 1028 > 1024)
```

⚠️ **n** = ponteiros; **N** da struct = chaves. "Adequado" = o **maior** que cabe. Confira se o tamanho vem em bytes ou em `int`.

### 6.3.3 Quantas chaves cabem · altura · páginas novas

Nó cheio com **N chaves** tem **m = N + 1 filhos**. Cada nível multiplica os nós por **m**.

```text
árvore cheia, h níveis (raiz = nível 1):   chaves = m^h − 1

A9 (N = 84, m = 85, 3 níveis):
  nível 1:   1 nó            × 84 =      84
  nível 2:  85 nós           × 84 =   7.140
  nível 3:  85² = 7.225 nós  × 84 = 606.900
  total = 614.124  (= 85³ − 1)
```

```text
A1c (ocupação média 70%, n = 24):
  0,7 × 23 = 16,1 ≈ 16 chaves/nó  →  17 filhos
  nível 3 = 17 × 17 = 289 nós × 16 = 4.624 chaves

A2 (altura 3, grau 3, MÍNIMO de chaves):
  todos os nós no mínimo → 1 + 2 + 4 = 7 chaves

A6 (folhas no nível 7, raiz no nível 0, inserir 1 chave):
  caminho = níveis 0 a 7 = 8 páginas
  pior caso: todas cheias → 8 divisões (8 páginas novas) + 1 raiz nova = 9
```

⚠️ Nível 3 = 17 **×** 17 (não 17 + 1). Raiz no nível 0 ou 1? **Conte os níveis.**

### 6.3.4 Inserção (split)

```text
1. desce até a folha e insere EM ORDEM
2. passou do máximo (n − 1)?  DIVIDE: a chave do meio SOBE para o pai,
   cada metade vira um nó
3. o pai passou do máximo?  repete
4. a raiz dividiu?  nasce raiz nova (altura + 1)
```

```text
A3 (grau 5, máx 4 chaves): inserir 6 na folha [2 3 5 7]

  [2 3 5 6 7]  → estourou (5 chaves), meio = 5
  o 5 SOBE;  ficam [2 3]  e  [6 7]
```

⚠️ Estouro **par** (ex.: grau 4 com 4 chaves) tem **duas** chaves do meio: escolha uma (ex.: a da direita) e **escreva qual**.

⚠️ O nó não precisa estar cheio para a árvore crescer. A árvore B cresce **pela raiz**.

⚠️ Na **B+**, ao dividir uma folha a chave do meio é **copiada** para o pai (continua na folha).

### 6.3.5 Remoção

```text
1. tira a chave da folha. Ainda tem o mínimo?  PARE.
2. um irmão tem MAIS que o mínimo?  EMPRESTA (rotação):
      o separador do PAI desce  ·  a chave do irmão sobe
3. senão FUNDE:  folha + separador do pai + irmão  = um nó só
4. o pai perdeu uma chave: volta ao passo 1 no pai.
   raiz vazia some (altura − 1)
```

```text
Empréstimo (A5c, grau 5, mín 2):
  raiz [65]   folhas [40 50 60]  [70 80]      remover 80
  [70] ficou com 1 (< 2); irmão [40 50 60] tem 3 → empresta
  o 65 DESCE · o 60 SOBE  →  raiz [60]   folhas [40 50]  [65 70]

Fusão (A4, grau 4, mín 1):
  raiz [70]   folhas [60]  [80]               remover 60
  [60] fica VAZIA; irmão [80] só tem o mínimo → não empresta
  funde: vazia + 70 + [80] = [70 80]; a raiz fica sem chaves e some
```

⚠️ Confira que a chave removida **sumiu** (nem como separador).

⚠️ Itens "**independentes**" partem **sempre da árvore original**; "**em seguida**" parte do resultado anterior.

⚠️ Irmão com exatamente o mínimo **não** empresta.

### 6.3.6 B+ em resumo

```text
B+  → dados SÓ nas folhas
      nós internos só com chaves-guia
      folhas ENCADEADAS em ordem
      → mais chaves por bloco, árvore mais baixa
      → intervalo: acha o primeiro e segue as folhas, sem subir
B   → chave e ponteiro de dado em todo nó
```


## 6.4 Hash com encadeamento externo

```text
h(k) = k mod 11      posições 0 a 10
área de colisão      a partir da posição 11
colunas              Chave · Valor · Próximo     (Próximo 0 = fim da lista)
colisão              chaves DIFERENTES na mesma posição
```

Inserir:

```text
posição livre   → a chave entra, Próximo = 0
posição ocupada → vai para a PRÓXIMA POSIÇÃO LIVRE DA ÁREA e é ligada
                  logo depois do 1º da lista, NESTA ORDEM:
                      Próximo(novo)     = Próximo(primeiro)
                      Próximo(primeiro) = posição do novo
```

```text
B5: 43, 27, 34, 70, 21, 84, 55, 38

  43→10   27→5   34→1   70→4
  21→10   colide com 43  → vai p/ 11;  Próximo(11)=0;  Próximo(10)=11
  84→7    55→0 (múltiplo de 11)
  38→5    colide com 27  → vai p/ 12;  Próximo(12)=0;  Próximo(5)=12
```

| Posição | Chave | Próximo |
|---:|---:|---:|
| 0 | 55 | 0 |
| 1 | 34 | 0 |
| 4 | 70 | 0 |
| 5 | 27 | 12 |
| 7 | 84 | 0 |
| 10 | 43 | 11 |
| 11 | 21 | 0 |
| 12 | 38 | 0 |

```text
B6: 32, 65, 76 caem na posição 10  →  lista  32 → 76 → 65
    (o último a chegar fica em 2º)
```

⚠️ Múltiplos de 11 → posição **0**. Chaves que diferem de 11 em 11 → **mesma** posição.

⚠️ Se o enunciado disser "no início" ou "no fim" da lista, **siga o enunciado**.

```text
No arquivo: posição da entrada = h(k) × tamanho da entrada
Fator de carga  α = n / m      acessos médios com sucesso ≈ 1 + α/2
Perguntas comuns: nº de colisões · tamanho da maior lista · onde ela começa
```


## 6.5 Huffman

```text
1. liste os símbolos com as frequências
2. pegue os 2 MENORES, some, crie um pai com a soma
3. devolva o pai ao conjunto; repita até sobrar 1 nó (a raiz)
4. ESQUERDA = 0 · DIREITA = 1
5. código = caminho raiz → folha · tamanho = nº de ligações
```

```text
C1: A4 B7 C10 D15 E20 F28 G33 H47

  4+7=11 · 10+11=21 · 15+20=35 · 21+28=49 · 33+35=68 · 47+49=96 · 68+96=164
```

| Símbolo | Freq. | Código | Tamanho | Freq × tamanho |
|---|---:|---|---:|---:|
| A | 4 | 11010 | 5 | 20 |
| B | 7 | 11011 | 5 | 35 |
| C | 10 | 1100 | 4 | 40 |
| D | 15 | 010 | 3 | 45 |
| E | 20 | 011 | 3 | 60 |
| F | 28 | 111 | 3 | 84 |
| G | 33 | 00 | 2 | 66 |
| H | 47 | 10 | 2 | 94 |
| **Total** | 164 | | | **444** |

```text
custo = Σ (freq × tamanho) = soma dos nós internos
      = 11+21+35+49+68+96+164 = 444 bits     (3 bits fixos: 3 × 164 = 492)
n símbolos → n − 1 junções · 2n − 1 nós
```

⚠️ Custo **não** é só o peso da raiz. Empate muda a árvore, **não** o custo. Escreva qual lado é 0.


## 6.6 Código com índice em árvore B (questão 4 da P2)

A árvore é um índice em disco: **chave → posição em bytes** do registro no arquivo de dados. Na prova (P2 2026.1) vêm prontas estas funções:

```c
void* openTree(const char* nomeArquivo);
bool  findKey(void* tree, long key, long* offset);   // true = achou (offset preenchido)
void  insertKey(void* tree, long key, long offset);
void  closeTree(void* tree);

typedef struct { long chave; char dados[1000]; } Registro;
```

**(a)** Construir o índice:

```c
void indexaArquivo(const char *nomeDados, const char *nomeIndice){
    FILE *f = fopen(nomeDados, "rb");
    void *tree = openTree(nomeIndice);
    Registro r;
    long pos;

    if(!f || !tree){ fprintf(stderr, "Erro ao abrir\n"); return; }

    while(1){
        pos = ftell(f);                                   // ANTES do fread
        if(fread(&r, sizeof(Registro), 1, f) != 1) break;
        insertKey(tree, r.chave, pos);
    }

    closeTree(tree);
    fclose(f);
}
```

**(b)** Buscar e imprimir:

```c
void imprimeDados(const char *nomeDados, const char *nomeIndice, long chave){
    void *tree = openTree(nomeIndice);
    FILE *f = fopen(nomeDados, "rb");
    Registro r;
    long off;

    if(!findKey(tree, chave, &off)){
        printf("Chave nao encontrada\n");
    }else{
        fseek(f, off, SEEK_SET);                          // off JÁ é em bytes
        fread(&r, sizeof(Registro), 1, f);
        printf("%.1000s\n", r.dados);                     // dados pode não ter '\0'
    }

    closeTree(tree);
    fclose(f);
}
```

**(c)** Registros de arquivo2 que **não estão** em arquivo1 (índice do arquivo1 já existe):

```c
void diferencaArquivos(const char *arq1, const char *arq2,
                       const char *indice1, const char *saida){
    void *tree = openTree(indice1);
    FILE *f2 = fopen(arq2, "rb");
    FILE *out = fopen(saida, "wb");
    Registro r;
    long off;

    while(fread(&r, sizeof(Registro), 1, f2) == 1){
        if(!findKey(tree, r.chave, &off)){                // não existe no arquivo1
            fwrite(&r, sizeof(Registro), 1, out);
        }
    }

    closeTree(tree);
    fclose(f2);
    fclose(out);
}
```

```text
custo: n2 buscas na árvore, cada uma O(log n1)  →  O(n2 · log n1)
```

⚠️ **`ftell` ANTES do `fread`.** Depois, a posição seria a do registro seguinte.

⚠️ A posição guardada na árvore é em **bytes**: `fseek(f, off, SEEK_SET)` **sem** multiplicar. O índice em memória da P1 (seção 5.13 F) guarda o **número do registro** e multiplica por `sizeof`. **Não misture.**

⚠️ Se a chave da árvore é inteira e o campo é texto (CEP, 8 caracteres sem `'\0'`), converta:

```c
char tmp[9];
memcpy(tmp, e.cep, 8);  tmp[8] = '\0';
long chave = atol(tmp);
```

⚠️ Reordenou o arquivo de dados? As posições mudam: **refaça o índice**.

⚠️ Diferença de dois arquivos **ordenados** (D4): leia uma linha de cada; menor → está só no 1º: grave e avance **só ele**; igual → avance **os dois**; maior → avance **só o 2º**. Quando o 2º acabar, grave o **resto** do 1º.

Nota de estudo: o `ArvoreB.c` do guia usa nomes diferentes (`ArvoreB_Abre`, `ArvoreB_Insere(arvore, chave, pos)`, `ArvoreB_Busca` devolve **-1** se não achar; o 0 é posição válida). Na prova, use as funções que o enunciado der.

## 6.7 Checklist — antes de entregar a P2

```text
[ ] Raiz no nível 0 ou 1?
[ ] Itens (a) (b) (c) independentes ou em sequência?
[ ] Escrevi a convenção usada (estouro par, lado do 0/1, início da lista)?
[ ] Arredondei PARA BAIXO o que não pode passar do bloco?
[ ] Conferi mínimo e máximo de chaves de TODO nó?
[ ] A chave removida sumiu da árvore?
[ ] Hash: colisão foi para a próxima posição livre da área (≥ 11)?
[ ] Hash: Próximo(novo) antes de Próximo(primeiro)?
[ ] Huffman: somei os 2 MENORES? Escrevi qual lado é 0?
[ ] ftell ANTES do fread ao guardar a posição?
[ ] Resposta teórica: citei onde ficam chaves/dados, ordem, e o custo?
```

---

# 7. Guia de Estudos por Exercício

Guia completo, **exercício por exercício** (E1 a E28 do treino), com a técnica, o código e o porquê de cada passo. Os subtópicos **7.1 a 7.20** são o seu *Guia de Estudos* mantido como está, com acréscimos marcados com ➕ (7.12, 7.16 e 7.20). Os subtópicos **7.21 a 7.31** são parte nova: exercícios que faltavam, mapa enunciado → técnica, checklist, o resumo dos pontos básicos da P1 e os lembretes da P1.

> **Sobre os números dos exemplos:** valores como "registro de 100 bytes", "chaves 10 / 20 / 30" e "offsets 0, 100, 200" são **inventados só para ilustrar**. Tamanhos reais: `Endereco` = **300 bytes** (72+72+72+72+2+8+2); `Registro` da P2 = **1008 bytes** (8 do `long` + 1000 do `char dados[1000]`).

## 7.1 Conceitos básicos de arquivos

### Abrindo arquivos

```c
FILE *f = fopen("arquivo.dat", "rb");

if (f == NULL) {
    printf("Erro ao abrir arquivo.\n");
    return 1;
}
```

| Modo | Significado |
|---|---|
| `"r"` | Leitura de arquivo texto |
| `"w"` | Escrita de arquivo texto, apagando conteúdo anterior |
| `"a"` | Escrita no final do arquivo |
| `"rb"` | Leitura de arquivo binário |
| `"wb"` | Escrita de arquivo binário, apagando conteúdo anterior |
| `"ab"` | Escrita no final de arquivo binário |
| `"r+b"` | Leitura e escrita em arquivo existente |
| `"w+b"` | Leitura e escrita, criando ou apagando o arquivo |

**Importante:** arquivos binários que armazenam `struct` normalmente devem ser abertos com `"rb"` e `"wb"`.

### Fechando arquivos

```c
fclose(f);
```

Sempre feche os arquivos que foram abertos, inclusive quando ocorrer um erro no meio da execução.

### `fgetc` e `fputc`

- `fgetc(f)`: lê um byte.
- `fputc(c, f)`: escreve um byte.
- `EOF`: indica que não há mais dados para ler.

Use `int` para armazenar o retorno de `fgetc`, pois ele precisa representar todos os valores de byte e também `EOF`.

```c
int c;

while ((c = fgetc(f)) != EOF) {
    // processa o byte
}
```

Não use `while (!feof(f))` como condição principal de leitura. O ideal é testar diretamente o retorno de `fgetc` ou `fread`.

### `fread` e `fwrite`

São utilizados para ler e escrever blocos de dados.

```c
fread(&registro, sizeof(Registro), 1, f);
fwrite(&registro, sizeof(Registro), 1, f);
```

Formato:

```c
fread(endereco, tamanho, quantidade, arquivo);
fwrite(endereco, tamanho, quantidade, arquivo);
```

Exemplo:

```c
Endereco e;

while (fread(&e, sizeof(Endereco), 1, f) == 1) {
    // processa um registro
}
```

O retorno de `fread` informa quantos elementos completos foram lidos.

## 7.2 E1 — Leitura de bytes, linhas e histograma

Objetivo: percorrer um arquivo e contar seus bytes, suas quebras de linha e a frequência de cada valor de byte.

```c
int contador[256] = {0};
int c;
long totalBytes = 0;
long linhas = 0;

while ((c = fgetc(f)) != EOF) {
    totalBytes++;
    contador[(unsigned char)c]++;

    if (c == '\n') {
        linhas++;
    }
}
```

#### Entendendo

- `contador[256]`: guarda a quantidade de ocorrências de cada valor de byte.
- `contador[c]++`: incrementa o contador correspondente ao byte lido.
- `totalBytes++`: cada leitura bem-sucedida representa um byte.
- `c == '\n'`: verifica se o byte é uma quebra de linha.

Por que 256 posições?

Porque um byte pode representar 256 valores diferentes: de 0 a 255.

Para imprimir o histograma:

```c
for (int i = 0; i < 256; i++) {
    if (contador[i] > 0) {
        printf("%d: %d\n", i, contador[i]);
    }
}
```

**Atenção:** contar `'\n'` não é necessariamente o mesmo que contar linhas lógicas. Se o arquivo terminar com uma linha sem quebra de linha, ela também deve ser considerada uma linha.

## 7.3 E2 — Cópia byte a byte

Objetivo: copiar o conteúdo de um arquivo para outro lendo um byte por vez.

```c
int c;

while ((c = fgetc(entrada)) != EOF) {
    fputc(c, saida);
}
```

#### Funcionamento visual

```text
Arquivo original
       |
       v
     fgetc
       |
       v
  Lê um byte
       |
       v
     fputc
       |
       v
Arquivo destino
```

A cada repetição:
1. Lê um byte do arquivo original.
2. Escreve esse byte no arquivo destino.
3. Continua até chegar ao `EOF`.

## 7.4 E3 — Cópia em blocos

Em vez de copiar um byte por vez, podemos ler vários bytes de uma vez.

```c
char buffer[1024];
size_t lidos;

while ((lidos = fread(buffer, 1, sizeof(buffer), entrada)) > 0) {
    fwrite(buffer, 1, lidos, saida);
}
```

#### O que é `buffer`?

É uma área temporária na memória RAM.

```text
Arquivo original
       |
       v
  fread (1024 bytes)
       |
       v
   buffer[1024]
       |
       v
  fwrite (lidos bytes)
       |
       v
Arquivo destino
```

#### Por que usar `lidos` no `fwrite`?

Porque o último bloco pode ter menos de 1024 bytes.

Exemplo:

```text
Tamanho do arquivo: 2500 bytes

1ª leitura: 1024 bytes
2ª leitura: 1024 bytes
3ª leitura:  452 bytes
```

Na última escrita, precisamos escrever apenas os 452 bytes realmente lidos.

## 7.5 Balanceamento de chaves `{}`

Objetivo: verificar se todas as chaves abertas foram fechadas corretamente.

```c
int c;
int saldo = 0;
int valido = 1;

while ((c = fgetc(f)) != EOF) {

    if (c == '{') {
        saldo++;
    }
    else if (c == '}') {
        saldo--;

        if (saldo < 0) {
            valido = 0;
            break;
        }
    }
}

if (saldo != 0) {
    valido = 0;
}
```

#### Ideia visual

```text
{  -> saldo = 1
{  -> saldo = 2
}  -> saldo = 1
{  -> saldo = 2
}  -> saldo = 1
}  -> saldo = 0
```

O arquivo é válido se:

- O saldo nunca ficar negativo.
- O saldo terminar em zero.

Exemplos:

```text
{{{}}}   -> válido
{}{}     -> válido
{}}{     -> inválido
{{}      -> inválido
```

Se o saldo ficar negativo, apareceu um `}` sem um `{` correspondente antes dele.

## 7.6 E6 — Quantidade de registros e tamanho do arquivo

Quando um arquivo possui registros de tamanho fixo, podemos descobrir quantos existem dividindo o tamanho total pelo tamanho de cada registro.

```c
fseek(f, 0, SEEK_END);

long bytes = ftell(f);

long quantidade = bytes / sizeof(Endereco);

rewind(f);
```

#### Funções utilizadas

| Função | Para que serve |
|---|---|
| `fseek` | Move o cursor do arquivo |
| `ftell` | Informa a posição atual do cursor |
| `rewind` | Volta o cursor para o início |
| `sizeof` | Informa o tamanho de uma estrutura em bytes |

#### Exemplo

Imagine:

```c
sizeof(Endereco) = 100
```

E o arquivo possui 5000 bytes.

```text
5000 / 100 = 50 registros
```

Portanto:

```c
quantidade = 50;
```

**Atenção:** essa conta pressupõe que todos os registros possuem o mesmo tamanho e que o arquivo não contém bytes extras.

## 7.7 E7 — Acesso direto a registros

Podemos acessar um registro específico sem precisar ler todos os anteriores.

```c
long offset = (numero - 1) * sizeof(Endereco);

fseek(f, offset, SEEK_SET);

Endereco e;

fread(&e, sizeof(Endereco), 1, f);
```

#### Por que `numero - 1`?

Porque normalmente o usuário informa o registro começando em 1, mas as posições começam em 0.

```text
Registro 1 -> posição 0
Registro 2 -> posição 1
Registro 3 -> posição 2
Registro 4 -> posição 3
```

#### Exemplo

Se cada registro possui 100 bytes:

```text
Registro 1 -> offset 0
Registro 2 -> offset 100
Registro 3 -> offset 200
Registro 4 -> offset 300
```

A fórmula é:

```c
offset = (numero - 1) * sizeof(Endereco);
```

#### Tipos de referência do `fseek`

| Referência | Significado |
|---|---|
| `SEEK_SET` | Início do arquivo |
| `SEEK_CUR` | Posição atual |
| `SEEK_END` | Final do arquivo |

## 7.8 Ordenação externa

A ordenação externa é utilizada quando o arquivo é grande demais para ser carregado inteiro na memória.

A ideia é dividir o arquivo em partes menores, ordenar cada parte na RAM e depois intercalar os arquivos ordenados.

#### Exemplo: dividir em 8 partes

```text
Arquivo original
       |
       v
  Divide em 8 partes
       |
       v
+------+------+------+------+
| P1   | P2   | P3   | P4   |
+------+------+------+------+
| P5   | P6   | P7   | P8   |
+------+------+------+------+
       |
       v
Ordena cada parte com qsort
       |
       v
Intercala os pares
       |
       v
8 -> 4 -> 2 -> 1
       |
       v
Arquivo final ordenado
```

### Divisão das partes

```c
int PARTES = 8;

long divisao = quantidade / PARTES;
long resto = quantidade % PARTES;
```

Para distribuir os registros:

```c
for (int i = 0; i < PARTES; i++) {

    long quantidadeParte = divisao;

    if (i < resto) {
        quantidadeParte++;
    }

    // Aloca, lê, ordena e grava a parte
}
```

Por que existe `resto`?

Exemplo:

```text
Quantidade total = 83
Partes = 8

83 / 8 = 10
Resto = 3
```

Distribuição:

```text
P1 = 11
P2 = 11
P3 = 11
P4 = 10
P5 = 10
P6 = 10
P7 = 10
P8 = 10
```

**Importante:** recrie `quantidadeParte` a cada repetição. Não altere `divisao` permanentemente com `divisao++`.

### Alocando e ordenando cada parte

```c
Endereco *e = malloc(quantidadeParte * sizeof(Endereco));

if (e == NULL && quantidadeParte > 0) {
    // Erro de alocação
}

fread(e, sizeof(Endereco), quantidadeParte, entrada);

qsort(e, quantidadeParte, sizeof(Endereco), compara);

fwrite(e, sizeof(Endereco), quantidadeParte, saida);

free(e);
```

A ideia é ordenar cada parte separadamente na memória.

### Intercalação

A função recebe dois arquivos já ordenados e gera um terceiro arquivo também ordenado.

```c
void intercala(char *arqA, char *arqB, char *arqSaida) {

    FILE *a = fopen(arqA, "rb");
    FILE *b = fopen(arqB, "rb");
    FILE *saida = fopen(arqSaida, "wb");

    Endereco ea, eb;

    int temA = fread(&ea, sizeof(Endereco), 1, a) == 1;
    int temB = fread(&eb, sizeof(Endereco), 1, b) == 1;

    while (temA && temB) {

        if (strncmp(ea.cep, eb.cep, 8) <= 0) {
            fwrite(&ea, sizeof(Endereco), 1, saida);
            temA = fread(&ea, sizeof(Endereco), 1, a) == 1;
        }
        else {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            temB = fread(&eb, sizeof(Endereco), 1, b) == 1;
        }
    }

    while (temA) {
        fwrite(&ea, sizeof(Endereco), 1, saida);
        temA = fread(&ea, sizeof(Endereco), 1, a) == 1;
    }

    while (temB) {
        fwrite(&eb, sizeof(Endereco), 1, saida);
        temB = fread(&eb, sizeof(Endereco), 1, b) == 1;
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}
```

O exemplo pressupõe que os arquivos foram abertos corretamente; na implementação final, verifique os retornos de `fopen`.

#### Como funciona a comparação?

Imagine:

```text
Arquivo A: 100, 300, 500
Arquivo B: 200, 400, 600
```

Comparamos os primeiros elementos:

```text
100 x 200 -> escreve 100
300 x 200 -> escreve 200
300 x 400 -> escreve 300
500 x 400 -> escreve 400
500 x 600 -> escreve 500
```

Quando um arquivo acaba, escrevemos o restante do outro.

#### Rodadas de intercalação

```text
Rodada 1:
P1 + P2
P3 + P4
P5 + P6
P7 + P8

Rodada 2:
R1 + R2
R3 + R4

Rodada 3:
R5 + R6
```

Resultado: um único arquivo ordenado.

## 7.9 `malloc` — Alocação dinâmica

`malloc` reserva espaço na memória RAM durante a execução do programa.

Exemplo:

```c
Endereco *e;

e = malloc(quantidade * sizeof(Endereco));
```

Imagine que queremos armazenar 100 registros:

```text
100 registros × tamanho de Endereco
```

O `malloc` reserva esse espaço e devolve um ponteiro para o início da região.

#### Verificando se a alocação funcionou

```c
e = malloc(quantidade * sizeof(Endereco));

if (e == NULL && quantidade > 0) {
    printf("Erro ao alocar memória.\n");
    return 1;
}
```

Por que `quantidade > 0`?

Porque `malloc(0)` pode retornar `NULL` ou um ponteiro especial. Uma quantidade igual a zero não significa necessariamente que ocorreu falta de memória.

#### Liberando memória

```c
free(e);
```

Quando terminamos de usar a região alocada, devemos liberá-la.

#### Diferença entre variável normal e `malloc`

```c
Endereco e;
```

Reserva espaço para apenas um registro, normalmente na pilha.

```c
Endereco *e = malloc(100 * sizeof(Endereco));
```

Reserva espaço para 100 registros na memória dinâmica.

#### Como acessar os elementos?

```c
e[0]
e[1]
e[2]
```

Mesmo sendo um ponteiro, podemos usar a notação de vetor porque o espaço reservado é contínuo.

## 7.10 `qsort` e função comparadora

`qsort` ordena os elementos de um vetor.

```c
qsort(vetor, quantidade, tamanhoElemento, compara);
```

Exemplo:

```c
qsort(e, quantidade, sizeof(Endereco), compara);
```

Os argumentos são:

| Argumento | Significado |
|---|---|
| `e` | Vetor que será ordenado |
| `quantidade` | Número de elementos |
| `sizeof(Endereco)` | Tamanho de cada elemento |
| `compara` | Função que determina a ordem |

### Função comparadora

Como `qsort` é genérico, ele recebe os elementos como `void *`.

Para ordenar pelo CEP:

```c
int compara(const void *a, const void *b) {

    const Endereco *e1 = (const Endereco *)a;
    const Endereco *e2 = (const Endereco *)b;

    return strncmp(e1->cep, e2->cep, 8);
}
```

#### O que acontece aqui?

1. `a` aponta para um elemento do vetor.
2. `b` aponta para outro elemento.
3. Convertemos os ponteiros para `Endereco *`.
4. Comparamos os CEPs.

#### Por que `->`?

Porque `e1` e `e2` são ponteiros para estruturas.

```c
e1->cep
```

É equivalente a:

```c
(*e1).cep
```

#### O que a comparação precisa retornar?

| Retorno | Significado |
|---|---|
| Negativo | Primeiro elemento vem antes |
| Zero | Elementos iguais |
| Positivo | Primeiro elemento vem depois |

Para comparar um campo numérico:

```c
int compara(const void *a, const void *b) {

    const Endereco *e1 = a;
    const Endereco *e2 = b;

    if (e1->numero < e2->numero) return -1;
    if (e1->numero > e2->numero) return 1;

    return 0;
}
```

**Dica:** não faça simplesmente `return e1->numero - e2->numero` para qualquer tipo numérico, pois a subtração pode causar problemas de overflow.

## 7.11 E12 — Busca sequencial

A busca sequencial percorre os registros um por um até encontrar a chave desejada.

```c
long buscaSequencial(FILE *f, char *cep, long *lidos) {

    Endereco registro;
    long pos = 0;

    while (fread(&registro, sizeof(Endereco), 1, f) == 1) {

        (*lidos)++;

        if (strncmp(registro.cep, cep, 8) == 0) {
            return pos;
        }

        pos++;
    }

    return -1;
}
```

#### Exemplo visual

Arquivo:

```text
Posição 0 -> CEP 100
Posição 1 -> CEP 200
Posição 2 -> CEP 300
Posição 3 -> CEP 400
```

Buscando CEP 300:

```text
Lê posição 0 -> não encontrou
Lê posição 1 -> não encontrou
Lê posição 2 -> encontrou!
```

Retorna:

```c
2
```

Se não encontrar, retorna `-1`.

#### Por que `long *lidos`?

Porque queremos alterar a variável que foi criada fora da função.

Na função principal:

```c
long lidos = 0;

long pos = buscaSequencial(f, cep, &lidos);
```

Dentro da função:

```c
(*lidos)++;
```

- `lidos` é um ponteiro.
- `*lidos` acessa o valor apontado.
- `(*lidos)++` incrementa a variável original.

**Atenção:** inicialize `lidos = 0` antes de chamar a função.

## 7.12 E13 — Ordenação em memória

Objetivo: carregar todos os registros do arquivo para a RAM, ordenar com `qsort` e gravar novamente no arquivo.

```c
fseek(f, 0, SEEK_END);

long quantidade = ftell(f) / sizeof(Endereco);

rewind(f);

Endereco *vetor = malloc(quantidade * sizeof(Endereco));

if (vetor == NULL && quantidade > 0) {
    printf("Erro de memória.\n");
    return;
}

size_t lidos = fread(vetor, sizeof(Endereco), quantidade, f);

qsort(vetor, lidos, sizeof(Endereco), compara);

rewind(f);

fwrite(vetor, sizeof(Endereco), lidos, f);

free(vetor);
```

> ➕ **Acréscimo — modo de abertura:** este código lê **e depois regrava no mesmo arquivo** (`rewind` + `fwrite`), então o arquivo precisa estar aberto com `"r+b"`. Com `"rb"` o `fwrite` falha; com `"wb"` o arquivo seria apagado antes de ler. Se o enunciado pedir gravar **em outro arquivo** (como o `ordena cep.dat ord.dat` do treino), abra a origem com `"rb"` e o destino com `"wb"`, e use `memcmp(a->cep, b->cep, 8)` no comparador (o CEP tem 8 bytes e **não tem `'\0'`**).

#### Passo a passo

```text
1. Descobre quantos registros existem
2. Volta ao início
3. Aloca memória para os registros
4. Lê o arquivo para o vetor
5. Ordena com qsort
6. Volta ao início do arquivo
7. Grava os registros ordenados
8. Libera a memória
```

#### Diferença entre E13 e ordenação externa

| E13 | Ordenação externa |
|---|---|
| Carrega tudo na RAM | Divide em partes |
| Ordena um vetor | Ordena vários vetores menores |
| Usa `qsort` | Usa `qsort` em cada parte |
| Grava o resultado | Intercala os arquivos ordenados |

## 7.13 E14 — Busca binária em arquivo

A busca binária só funciona quando o arquivo está ordenado pela chave pesquisada.

Em vez de ler todos os registros, ela vai eliminando metade do intervalo a cada comparação.

```c
long buscaBinaria(FILE *f, char *cep, long quantidade) {

    long inicio = 0;
    long fim = quantidade - 1;

    Endereco e;

    while (inicio <= fim) {

        long meio = (inicio + fim) / 2;

        fseek(f, meio * sizeof(Endereco), SEEK_SET);

        if (fread(&e, sizeof(Endereco), 1, f) != 1) {
            return -1;
        }

        int resultado = strncmp(cep, e.cep, 8);

        if (resultado == 0) {
            return meio;
        }

        if (resultado < 0) {
            fim = meio - 1;
        }
        else {
            inicio = meio + 1;
        }
    }

    return -1;
}
```

#### Exemplo visual

Arquivo ordenado:

```text
100  200  300  400  500  600  700
```

Queremos encontrar `600`.

Primeira tentativa:

```text
100  200  300  400  500  600  700
               ^
             meio
```

O meio é 400.

Como 600 é maior, descartamos a metade esquerda.

Segunda tentativa:

```text
500  600  700
      ^
    meio
```

Encontramos 600.

#### Atualização dos limites

| Comparação | O que fazer |
|---|---|
| Chave igual | Encontrou |
| Chave procurada menor | `fim = meio - 1` |
| Chave procurada maior | `inicio = meio + 1` |

Complexidade: O(log n) comparações e acessos ao arquivo.

## 7.14 E15 — Índice em vetor

Em vez de ordenar o arquivo original, podemos criar um vetor auxiliar que guarda a chave e a posição do registro original.

```c
typedef struct {
    char cep[8];
    long posicao;
} IndiceCep;
```

#### Exemplo

Arquivo original:

```text
Posição 0 -> CEP 300
Posição 1 -> CEP 100
Posição 2 -> CEP 200
```

Vetor de índices:

```text
CEP 300 -> posição 0
CEP 100 -> posição 1
CEP 200 -> posição 2
```

Ordenamos apenas o vetor:

```text
CEP 100 -> posição 1
CEP 200 -> posição 2
CEP 300 -> posição 0
```

O arquivo original continua na mesma ordem!

#### Por que guardar a posição?

Porque depois da busca binária no índice, precisamos recuperar o registro original.

```c
fseek(arquivo, indice[meio].posicao * sizeof(Endereco), SEEK_SET);

fread(&e, sizeof(Endereco), 1, arquivo);
```

#### Comparador do índice

```c
int comparaIndice(const void *a, const void *b) {

    const IndiceCep *i1 = a;
    const IndiceCep *i2 = b;

    return strncmp(i1->cep, i2->cep, 8);
}
```

#### Diferença entre índice e arquivo

```text
ARQUIVO ORIGINAL
300
100
200

ÍNDICE ORDENADO
100 -> posição 1
200 -> posição 2
300 -> posição 0
```

O índice permite pesquisar rapidamente sem precisar reorganizar os registros originais.

**Atenção:** nesse exemplo, `posicao` representa o número do registro. Por isso multiplicamos por `sizeof(Endereco)`. Se armazenássemos o offset em bytes, usaríamos diretamente o valor no `fseek`.

## 7.15 Árvores B — Conceitos

Uma árvore B é uma estrutura de dados que organiza chaves em páginas, permitindo buscas eficientes.

Diferentemente de uma árvore binária, uma página pode armazenar várias chaves e possuir vários filhos.

#### Exemplo visual simplificado

```text
              [30 | 60]
             /    |    \
            /     |     \
       [10,20] [40,50] [70,80]
```

A raiz possui duas chaves:

- Menores que 30 ficam à esquerda.
- Entre 30 e 60 ficam no filho do meio.
- Maiores que 60 ficam à direita.

A árvore organiza as chaves para evitar a leitura de todos os registros.

### Árvore B como índice de arquivo

Imagine que temos um arquivo de dados:

```text
Registro 0 -> chave 10
Registro 1 -> chave 20
Registro 2 -> chave 30
Registro 3 -> chave 40
```

A árvore não precisa guardar os registros completos. Ela pode guardar:

```text
Chave 10 -> offset 0
Chave 20 -> offset 100
Chave 30 -> offset 200
Chave 40 -> offset 300
```

Assim, a árvore funciona como um índice.

#### O que é offset?

É a posição, em bytes, onde um registro começa dentro do arquivo.

Se cada registro possui 100 bytes:

```text
Registro 0 -> offset 0
Registro 1 -> offset 100
Registro 2 -> offset 200
Registro 3 -> offset 300
```

Para recuperar o registro:

```c
fseek(dados, offset, SEEK_SET);
fread(&r, sizeof(Registro), 1, dados);
```

## 7.16 Árvore B — Exercício A: criação do índice

Objetivo: percorrer um arquivo de dados e inserir na árvore cada chave junto com seu offset.

Estrutura:

```c
typedef struct {
    long chave;
    char dados[1000];
} Registro;
```

Funções fornecidas:

```c
void* openTree(const char* nomeArquivo);

bool findKey(void* tree, long key, long* offset);

void insertKey(void* tree, long key, long offset);

void closeTree(void* tree);
```

Lembre-se de incluir:

```c
#include <stdbool.h>
```

> ➕ **Números de exemplo:** "offset 100, 200…" nas figuras abaixo é só ilustração (registros de 100 bytes inventados). Na prova, `sizeof(Registro)` = 8 (`long`) + 1000 (`char dados[1000]`) = **1008 bytes**, então os offsets reais seriam 0, 1008, 2016… Quem calcula isso é o `ftell`, nunca você.

#### Código principal

```c
void indexaArquivo(const char *arquivoDados,
                   const char *arquivoIndice) {

    FILE *dados = fopen(arquivoDados, "rb");

    if (dados == NULL) {
        return;
    }

    void *tree = openTree(arquivoIndice);

    if (tree == NULL) {
        fclose(dados);
        return;
    }

    Registro r;

    long offset = ftell(dados);

    while (fread(&r, sizeof(Registro), 1, dados) == 1) {

        insertKey(tree, r.chave, offset);

        offset = ftell(dados);
    }

    closeTree(tree);
    fclose(dados);
}
```

#### Entendendo o offset

Antes de ler o primeiro registro:

```c
long offset = ftell(dados);
```

Como o arquivo acabou de ser aberto, o cursor está na posição zero.

Depois de ler um registro:

```c
fread(&r, sizeof(Registro), 1, dados);
```

O cursor avança para o início do próximo registro.

Por isso:

```c
offset = ftell(dados);
```

Na próxima repetição, temos o offset do próximo registro.

#### Visualização

```text
Arquivo:
+----------------+
| Registro 0     | offset 0
+----------------+
| Registro 1     | offset 100
+----------------+
| Registro 2     | offset 200
+----------------+

Árvore:
Chave 10 -> 0
Chave 20 -> 100
Chave 30 -> 200
```

A árvore guarda a chave e a posição, não o conteúdo inteiro de `dados`.

## 7.17 Árvore B — Exercício B: busca e impressão

Objetivo: procurar uma chave na árvore e, se ela existir, recuperar o registro completo no arquivo.

```c
void imprimeDados(const char *arquivoDados,
                  const char *arquivoIndice,
                  long chave) {

    FILE *dados = fopen(arquivoDados, "rb");

    if (dados == NULL) {
        return;
    }

    void *tree = openTree(arquivoIndice);

    if (tree == NULL) {
        fclose(dados);
        return;
    }

    Registro r;
    long offset;

    bool achou = findKey(tree, chave, &offset);

    if (!achou) {
        printf("Chave não encontrada.\n");

        closeTree(tree);
        fclose(dados);
        return;
    }

    if (fseek(dados, offset, SEEK_SET) == 0 &&
        fread(&r, sizeof(Registro), 1, dados) == 1) {

        printf("%.1000s\n", r.dados);
    }

    closeTree(tree);
    fclose(dados);
}
```

#### Como funciona?

```text
Usuário informa a chave
          |
          v
      findKey()
          |
          v
  A árvore encontra a chave?
       /       \
     NÃO       SIM
      |          |
      v          v
  Informa     Retorna
  ausência    offset
                 |
                 v
          fseek(dados, offset)
                 |
                 v
          fread(&r, ...)
                 |
                 v
          Imprime os dados
```

#### Entendendo `findKey`

```c
bool achou = findKey(tree, chave, &offset);
```

A função recebe:

- `tree`: árvore que será pesquisada.
- `chave`: chave procurada.
- `&offset`: endereço da variável que receberá o offset.

Ela retorna:

- `true`: encontrou.
- `false`: não encontrou.

**Importante:** `findKey` não retorna o registro completo. Ela retorna o offset por referência. Depois precisamos usar `fseek` e `fread`.

## 7.18 Árvore B — Exercício C: diferença entre arquivos

Enunciado: gerar um terceiro arquivo com os registros cujas chaves aparecem no arquivo 2, mas não aparecem no arquivo 1.

A ideia é:

1. Criar uma árvore com as chaves do arquivo 1.
2. Percorrer o arquivo 2.
3. Procurar cada chave do arquivo 2 na árvore.
4. Se não encontrar, escrever o registro no arquivo de saída.

#### Exemplo

Arquivo 1:

```text
10
20
30
```

Arquivo 2:

```text
20
40
50
```

Árvore construída com o arquivo 1:

```text
[10 | 20 | 30]
```

Consultas:

```text
20 -> encontrou -> não escreve
40 -> não encontrou -> escreve
50 -> não encontrou -> escreve
```

Resultado:

```text
Arquivo 3:
40
50
```

#### Código-base

```c
void diferencaArquivos(const char *arquivo1,
                       const char *arquivo2,
                       const char *arquivoSaida,
                       const char *arquivoIndice) {

    FILE *dados1 = fopen(arquivo1, "rb");

    if (dados1 == NULL) {
        return;
    }

    FILE *dados2 = fopen(arquivo2, "rb");

    if (dados2 == NULL) {
        fclose(dados1);
        return;
    }

    FILE *saida = fopen(arquivoSaida, "wb");

    if (saida == NULL) {
        fclose(dados1);
        fclose(dados2);
        return;
    }

    void *tree = openTree(arquivoIndice);

    if (tree == NULL) {
        fclose(dados1);
        fclose(dados2);
        fclose(saida);
        return;
    }

    Registro r1, r2;
    long offset = ftell(dados1);

    // 1. Insere as chaves do arquivo 1 na árvore
    while (fread(&r1, sizeof(Registro), 1, dados1) == 1) {

        insertKey(tree, r1.chave, offset);

        offset = ftell(dados1);
    }

    // 2. Percorre o arquivo 2 e consulta a árvore
    while (fread(&r2, sizeof(Registro), 1, dados2) == 1) {

        long offsetEncontrado;

        bool achou = findKey(tree, r2.chave, &offsetEncontrado);

        // 3. Só escreve se a chave não existir no arquivo 1
        if (!achou) {
            fwrite(&r2, sizeof(Registro), 1, saida);
        }
    }

    closeTree(tree);

    fclose(dados1);
    fclose(dados2);
    fclose(saida);
}
```

#### Por que só precisamos de uma árvore?

Porque a pergunta é:

> A chave do arquivo 2 existe no arquivo 1?

Então construímos o índice do arquivo 1 e usamos esse índice para consultar as chaves do arquivo 2.

Não precisamos criar uma segunda árvore.

#### Por que o `fwrite` usa `saida`?

Porque queremos gravar os registros encontrados no terceiro arquivo:

```c
fwrite(&r2, sizeof(Registro), 1, saida);
```

Não devemos escrever em `dados2`, pois ele é o arquivo que estamos lendo.

#### Atenção aos retornos

A função está declarada como `void`, portanto usa apenas:

```c
return;
```

Se quisermos retornar códigos de sucesso ou erro, precisamos declarar a função como `int` e usar os retornos de maneira consistente.

Também precisamos garantir que o índice esteja vazio ou seja reinicializado antes de reconstruí-lo, conforme o comportamento de `openTree`.

## 7.19 Resumo de funções importantes

| Função | O que faz |
|---|---|
| `fopen` | Abre um arquivo |
| `fclose` | Fecha um arquivo |
| `fgetc` | Lê um byte |
| `fputc` | Escreve um byte |
| `fread` | Lê dados em blocos |
| `fwrite` | Escreve dados em blocos |
| `fseek` | Move o cursor |
| `ftell` | Retorna a posição atual |
| `rewind` | Volta ao início |
| `sizeof` | Retorna o tamanho de um tipo |
| `malloc` | Aloca memória dinamicamente |
| `free` | Libera memória alocada |
| `qsort` | Ordena um vetor |
| `strncmp` | Compara uma quantidade definida de caracteres |
| `strcmp` | Compara strings terminadas em `\0` |
| `findKey` | Pesquisa uma chave na árvore |
| `insertKey` | Insere uma chave e seu offset |
| `openTree` | Abre ou cria o índice em árvore |
| `closeTree` | Fecha a árvore |

### Diferenças que costumam confundir

#### `fseek` x `ftell`

```c
fseek(f, 100, SEEK_SET);
```

Move o cursor para o byte 100.

```c
long pos = ftell(f);
```

Descobre em qual byte o cursor está.

#### `rewind` x `fseek`

```c
rewind(f);
```

Volta ao início.

```c
fseek(f, 0, SEEK_SET);
```

Também volta ao início.

#### `fread` x `fgetc`

- `fgetc`: lê um byte.
- `fread`: lê um ou mais elementos de determinado tamanho.

#### `fwrite` x `fputc`

- `fputc`: escreve um byte.
- `fwrite`: escreve elementos ou blocos.

#### `malloc` x `sizeof`

- `sizeof`: calcula quantos bytes são necessários.
- `malloc`: reserva esses bytes na memória.

#### `qsort` x busca binária

- `qsort`: coloca os elementos em ordem.
- Busca binária: procura um elemento em uma sequência já ordenada.

## 7.20 Como identificar qual técnica usar na prova

| Se o enunciado pedir... | Pense em... |
|---|---|
| Contar bytes ou caracteres | `fgetc` |
| Copiar arquivo byte a byte | `fgetc` + `fputc` |
| Copiar arquivo em blocos | `fread` + `fwrite` |
| Contar registros | `fseek` + `ftell` + `sizeof` |
| Acessar registro específico | `fseek` + `fread` |
| Procurar sem ordenação | Busca sequencial |
| Ordenar registros em RAM | `malloc` + `qsort` |
| Ordenar arquivo muito grande | Ordenação externa |
| Procurar em arquivo ordenado | Busca binária |
| Criar índice em vetor | Struct com chave + posição |
| Criar índice em árvore B | `insertKey` |
| Consultar índice em árvore B | `findKey` |
| Recuperar registro após busca na árvore | `fseek` + `fread` |

### Três ideias fundamentais para lembrar

**1. Posição não é a mesma coisa que offset.**

- Posição: número do registro, como 0, 1, 2...
- Offset: posição em bytes dentro do arquivo.

Se cada registro possui 100 bytes:

```text
posição 0 -> offset 0
posição 1 -> offset 100
posição 2 -> offset 200
```

**2. Um índice não precisa guardar o registro inteiro.**

Ele pode guardar somente:

```text
chave -> posição
```

Assim, encontramos a posição rapidamente e depois buscamos o registro completo no arquivo.

**3. Ordenar e pesquisar são operações diferentes.**

- Primeiro podemos ordenar com `qsort`.
- Depois podemos pesquisar com busca binária.
- Se não pudermos carregar tudo na memória, podemos usar ordenação externa.
- Se tivermos um índice, podemos consultar a chave sem percorrer o arquivo inteiro.

> ➕ **Acréscimo:** os exercícios que o guia ainda não trazia (E4, E5, E8–E11, E16–E28) estão nos subtópicos 7.21 a 7.26, com os enunciados do treino e códigos testados.

## 7.21 Exercícios do treino que faltam — Bloco 1 (E4, E5)

> ➕ **Parte nova.** Os subtópicos 7.21 a 7.26 cobrem os exercícios do treino que o guia acima não trazia (E4, E5, E8–E11, E16–E28). Todos os códigos foram **compilados e testados** contra uma versão em Python do que cada exercício espera. Os arquivos de teste eram sintéticos (1003 registros de 300 bytes), por isso números como "1003" **não são do seu `cep.dat`**.

**Cabeçalho comum** dos programas com `Endereco` (copie no início de cada um):

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char logradouro[72], bairro[72], cidade[72], uf[72];
    char sigla[2];
    char cep[8];      // chave, sem '\0'
    char lixo[2];
} Endereco;           // 72+72+72+72+2+8+2 = 300 bytes
```

### E4 — Maiúsculas (sem `toupper`)

Trocar `a`–`z` por `A`–`Z` pela diferença da tabela ASCII (`'a' - 'A'` = 32).

```c
#include <stdio.h>
int main(int argc, char **argv) {
    if (argc != 3) { printf("uso: %s origem destino\n", argv[0]); return 1; }
    FILE *e = fopen(argv[1], "rb");
    if (e == NULL) { printf("erro ao abrir origem\n"); return 1; }
    FILE *s = fopen(argv[2], "wb");
    if (s == NULL) { printf("erro ao abrir destino\n"); fclose(e); return 1; }
    int c;                                   // int, para caber o EOF
    while ((c = fgetc(e)) != EOF) {
        if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';   // ou c - 32
        fputc(c, s);
    }
    fclose(e); fclose(s);
    return 0;
}
```

- `c` é **`int`**, não `char`, para caber o `EOF`.
- Só mexe de `'a'` a `'z'`; o resto passa igual (inclusive bytes de acento, que não são letras ASCII).
- Conferir: `tr a-z A-Z < exemplo.c | cmp - saida.txt`.

### E5 — Histograma de bytes

```c
#include <stdio.h>
int main(int argc, char **argv) {
    if (argc != 2) { printf("uso: %s arquivo\n", argv[0]); return 1; }
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    int contador[256] = {0};
    int c;
    while ((c = fgetc(f)) != EOF)
        contador[c]++;
    for (int v = 0; v < 256; v++)
        if (contador[v] > 0)
            printf("%d %d\n", v, contador[v]);
    fclose(f);
    return 0;
}
```

- O byte lido **é o índice** do vetor: `contador[c]++`.
- `int c` também aqui: com `char` signed, o byte 255 viraria `-1` (= `EOF`) e o laço pararia no meio.
- Vetor começa zerado (`= {0}`); índices de 0 a 255 (256 posições).

## 7.22 Bloco 2 — registros: E8, E9, E10, E11

### E8 — Inverter o arquivo

Lê **um registro por vez**, de trás para frente (não carrega o arquivo na memória).

```c
// (começa com o cabeçalho comum do 7.21)
int main(int argc, char **argv) {
    if (argc != 3) { printf("uso: %s origem destino\n", argv[0]); return 1; }
    FILE *e = fopen(argv[1], "rb");
    if (e == NULL) { printf("erro ao abrir origem\n"); return 1; }
    FILE *s = fopen(argv[2], "wb");
    if (s == NULL) { printf("erro ao abrir destino\n"); fclose(e); return 1; }
    fseek(e, 0, SEEK_END);
    long n = ftell(e) / sizeof(Endereco);        // quantidade de registros
    Endereco r;
    for (long i = n - 1; i >= 0; i--) {          // do último (n-1) ao primeiro (0)
        fseek(e, i * sizeof(Endereco), SEEK_SET);
        fread(&r, sizeof(Endereco), 1, e);
        fwrite(&r, sizeof(Endereco), 1, s);
    }
    fclose(e); fclose(s);
    return 0;
}
```

- Último registro = `n - 1`; primeiro = `0`.
- `i` é `long` e o laço vai até `i >= 0`: com `unsigned` ele nunca ficaria negativo e o laço não terminaria.

### E9 — Amostra (1 a cada k)

```c
// (começa com o cabeçalho comum do 7.21)
int main(int argc, char **argv) {
    if (argc != 4) { printf("uso: %s origem destino k\n", argv[0]); return 1; }
    long k = atol(argv[3]);
    if (k <= 0) { printf("k deve ser > 0\n"); return 1; }
    FILE *e = fopen(argv[1], "rb");
    if (e == NULL) { printf("erro ao abrir origem\n"); return 1; }
    FILE *s = fopen(argv[2], "wb");
    if (s == NULL) { printf("erro ao abrir destino\n"); fclose(e); return 1; }
    Endereco r;
    while (fread(&r, sizeof(Endereco), 1, e) == 1) {     // lê o registro 0, k, 2k...
        fwrite(&r, sizeof(Endereco), 1, s);
        fseek(e, (k - 1) * sizeof(Endereco), SEEK_CUR);  // pula os k-1 seguintes
    }
    fclose(e); fclose(s);
    return 0;
}
```

- Depois de ler 1 registro, o cursor já está no seguinte: pula só `k - 1` (`SEEK_CUR`).
- Registros copiados: posições `0, k, 2k…`.
- Teste `k <= 0` antes (k = 0 daria `fseek` para trás e laço infinito).

### E10 — Alterar um registro no lugar

```c
// (começa com o cabeçalho comum do 7.21)
int main(int argc, char **argv) {
    if (argc != 4) { printf("uso: %s arquivo n cep\n", argv[0]); return 1; }
    long n = atol(argv[2]);                      // o primeiro é o 1
    FILE *f = fopen(argv[1], "r+b");             // ler E gravar sem apagar
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    Endereco r;
    fseek(f, (n - 1) * sizeof(Endereco), SEEK_SET);
    if (fread(&r, sizeof(Endereco), 1, f) != 1) { printf("registro nao existe\n"); fclose(f); return 1; }
    memcpy(r.cep, argv[3], 8);                   // 8 bytes, sem '\0'
    fseek(f, -(long)sizeof(Endereco), SEEK_CUR); // o fread avançou: volta 1 registro
    fwrite(&r, sizeof(Endereco), 1, f);
    fclose(f);
    return 0;
}
```

- Modo **`"r+b"`**: lê e grava no mesmo arquivo, sem apagar.
- O `fread` **avança** o cursor; antes do `fwrite` volte 1 registro: `fseek(f, -(long)sizeof(Endereco), SEEK_CUR)`. O cast `(long)` é obrigatório: `sizeof` é sem sinal, e negar dá um número gigante.
- CEP novo com `memcpy(..., 8)`: o campo tem 8 bytes e **sem `'\0'`**. Valide `strlen(argv[3]) == 8` se quiser ser seguro.
- Teste sempre numa cópia: `cp cep.dat teste.dat`.

### E11 — Acrescentar no final

```c
// (começa com o cabeçalho comum do 7.21)
int main(int argc, char **argv) {
    if (argc != 4) { printf("uso: %s arquivo cep logradouro\n", argv[0]); return 1; }
    FILE *f = fopen(argv[1], "ab");              // sempre grava no fim
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    Endereco r;
    memset(&r, 0, sizeof(Endereco));             // zera tudo (nada de lixo)
    memcpy(r.cep, argv[2], 8);
    strncpy(r.logradouro, argv[3], 71);          // cabe em 72 e deixa o '\0'
    fwrite(&r, sizeof(Endereco), 1, f);
    fclose(f);
    return 0;
}
```

- Modo **`"ab"`**: toda gravação vai para o fim; `fseek` não muda isso.
- `memset` zera a struct antes de preencher: sem isso os campos não preenchidos gravam **lixo de memória** no arquivo.
- `strncpy(r.logradouro, ..., 71)` deixa pelo menos 1 byte `'\0'` no fim do campo de 72.

## 7.23 Bloco 3 — E16: índice gravado em arquivo

Mesmo índice do E15 (7.15), mas **salvo em disco** (`cep.idx`) para reaproveitar sem recalcular.

```c
typedef struct {
    char cep[8];
    long posicao;      // número do registro (0, 1, 2...)
} IndiceCep;           // 8 + 8 = 16 bytes
int comparaIdx(const void *a, const void *b) {
    return memcmp(((const IndiceCep*)a)->cep, ((const IndiceCep*)b)->cep, 8);
}
```

**`criaidx cep.dat cep.idx`** — monta, ordena e grava com **um** `fwrite`:

```c
// (cabeçalho comum do 7.21 + struct IndiceCep do E15)
int main(int argc, char **argv) {
    if (argc != 3) { printf("uso: %s cep.dat cep.idx\n", argv[0]); return 1; }
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Endereco);
    rewind(f);
    IndiceCep *v = malloc(n * sizeof(IndiceCep));
    if (v == NULL) { fclose(f); return 1; }
    Endereco r;
    for (long i = 0; i < n; i++) {               // lê um por vez: só guarda cep + posição
        fread(&r, sizeof(Endereco), 1, f);
        memcpy(v[i].cep, r.cep, 8);
        v[i].posicao = i;
    }
    fclose(f);
    qsort(v, n, sizeof(IndiceCep), comparaIdx);
    FILE *s = fopen(argv[2], "wb");
    if (s == NULL) { free(v); return 1; }
    fwrite(v, sizeof(IndiceCep), n, s);          // um único fwrite
    fclose(s); free(v);
    return 0;
}
```

**`buscaidx cep.dat cep.idx CEP`** — carrega o índice, busca binária na RAM, lê o registro no `cep.dat`:

```c
// (cabeçalho comum do 7.21 + struct IndiceCep do E15)
int main(int argc, char **argv) {
    if (argc != 4) { printf("uso: %s cep.dat cep.idx CEP\n", argv[0]); return 1; }
    FILE *fi = fopen(argv[2], "rb");
    if (fi == NULL) { printf("erro ao abrir indice\n"); return 1; }
    fseek(fi, 0, SEEK_END);
    long n = ftell(fi) / sizeof(IndiceCep);      // quantidade pelo tamanho do arquivo
    rewind(fi);
    IndiceCep *v = malloc(n * sizeof(IndiceCep));
    if (v == NULL) { fclose(fi); return 1; }
    fread(v, sizeof(IndiceCep), n, fi);
    fclose(fi);
    long ini = 0, fim = n - 1, achou = -1;
    while (ini <= fim) {                         // busca binária no vetor (RAM)
        long meio = (ini + fim) / 2;
        int c = memcmp(argv[3], v[meio].cep, 8);
        if (c == 0) { achou = meio; break; }
        if (c < 0) fim = meio - 1; else ini = meio + 1;
    }
    if (achou < 0) { printf("nao achou\n"); free(v); return 0; }
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) { free(v); return 1; }
    Endereco r;
    fseek(f, v[achou].posicao * sizeof(Endereco), SEEK_SET);   // posição × sizeof
    fread(&r, sizeof(Endereco), 1, f);
    printf("achou na posicao %ld\n%.72s | %.8s\n", v[achou].posicao, r.logradouro, r.cep);
    fclose(f); free(v);
    return 0;
}
```

- Quantidade de entradas do índice = `tamanho do cep.idx / sizeof(IndiceCep)` (aqui 16 bytes por entrada).
- No `cep.dat`: `fseek(f, posicao * sizeof(Endereco), SEEK_SET)`. A posição guardada é de **registro**, então multiplica; no índice em **árvore B** o que se guarda é **byte offset**, e aí **não** multiplica.
- Conferir o tamanho: `ls -l cep.idx` deve dar `registros × 16`.

## 7.24 Bloco 4 — intercalação: E17, E18, E19

### E17 — Intercalar dois arquivos ordenados

```c
// (começa com o cabeçalho comum do 7.21)
void intercala(char *arqA, char *arqB, char *arqSaida) {
    FILE *a = fopen(arqA, "rb");
    FILE *b = fopen(arqB, "rb");
    FILE *s = fopen(arqSaida, "wb");
    if (a == NULL || b == NULL || s == NULL) {
        printf("erro ao abrir\n");
        if (a) fclose(a);
        if (b) fclose(b);
        if (s) fclose(s);
        return;
    }
    Endereco ra, rb;
    int temA = fread(&ra, sizeof(Endereco), 1, a);   // 1 = tem registro, 0 = acabou
    int temB = fread(&rb, sizeof(Endereco), 1, b);
    while (temA && temB) {
        if (memcmp(ra.cep, rb.cep, 8) <= 0) {        // <= mantém a estabilidade
            fwrite(&ra, sizeof(Endereco), 1, s);
            temA = fread(&ra, sizeof(Endereco), 1, a);
        } else {
            fwrite(&rb, sizeof(Endereco), 1, s);
            temB = fread(&rb, sizeof(Endereco), 1, b);
        }
    }
    while (temA) {                                   // sobrou em A
        fwrite(&ra, sizeof(Endereco), 1, s);
        temA = fread(&ra, sizeof(Endereco), 1, a);
    }
    while (temB) {                                   // sobrou em B
        fwrite(&rb, sizeof(Endereco), 1, s);
        temB = fread(&rb, sizeof(Endereco), 1, b);
    }
    fclose(a); fclose(b); fclose(s);
}
int main(int argc, char **argv) {
    if (argc != 4) { printf("uso: %s A B saida\n", argv[0]); return 1; }
    intercala(argv[1], argv[2], argv[3]);
    return 0;
}
```

- `temA` / `temB` guardam se ainda existe registro. **Não** use `feof` como condição do laço.
- `<= 0` na comparação mantém a ordem original quando as chaves são iguais.
- Depois do laço principal, **copie o que sobrou** do arquivo que não acabou (os dois `while` finais).
- Todo `fopen` testado; se um falhar, feche os que abriram.
- Conferir: dividir o `ord.dat` ao meio e reintercalar deve dar um arquivo idêntico (`cmp`).

### E18 — União sem repetir

Igual ao E17, mas com **três** casos: menor em A, menor em B, **iguais**.

```c
// (começa com o cabeçalho comum do 7.21)
int main(int argc, char **argv) {
    if (argc != 4) { printf("uso: %s A B saida\n", argv[0]); return 1; }
    FILE *a = fopen(argv[1], "rb");
    FILE *b = fopen(argv[2], "rb");
    FILE *s = fopen(argv[3], "wb");
    if (a == NULL || b == NULL || s == NULL) {
        printf("erro ao abrir\n");
        if (a) fclose(a);
        if (b) fclose(b);
        if (s) fclose(s);
        return 1;
    }
    Endereco ra, rb;
    int temA = fread(&ra, sizeof(Endereco), 1, a);
    int temB = fread(&rb, sizeof(Endereco), 1, b);
    while (temA && temB) {
        int c = memcmp(ra.cep, rb.cep, 8);
        if (c < 0) {
            fwrite(&ra, sizeof(Endereco), 1, s);
            temA = fread(&ra, sizeof(Endereco), 1, a);
        } else if (c > 0) {
            fwrite(&rb, sizeof(Endereco), 1, s);
            temB = fread(&rb, sizeof(Endereco), 1, b);
        } else {                                     // iguais: grava UM e avança OS DOIS
            fwrite(&ra, sizeof(Endereco), 1, s);
            temA = fread(&ra, sizeof(Endereco), 1, a);
            temB = fread(&rb, sizeof(Endereco), 1, b);
        }
    }
    while (temA) { fwrite(&ra, sizeof(Endereco), 1, s); temA = fread(&ra, sizeof(Endereco), 1, a); }
    while (temB) { fwrite(&rb, sizeof(Endereco), 1, s); temB = fread(&rb, sizeof(Endereco), 1, b); }
    fclose(a); fclose(b); fclose(s);
    return 0;
}
```

- Iguais → grava **um** e avança **os dois** arquivos.
- Sem esse terceiro caso, a chave repetida sairia duas vezes.

### E19 — Ordenação externa completa

Divide em `PARTES`, ordena cada uma na RAM, grava `cep_0.dat … cep_(PARTES-1).dat` e intercala **dois a dois**; cada resultado ganha o próximo número. Reaproveita a `intercala` do E17.

```c
int compara(const void *a, const void *b) {
    return memcmp(((const Endereco*)a)->cep, ((const Endereco*)b)->cep, 8);
}
int main(int argc, char **argv) {
    if (argc != 3) { printf("uso: %s cep.dat partes\n", argv[0]); return 1; }
    int PARTES = atoi(argv[2]);
    if (PARTES < 1) return 1;
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    fseek(f, 0, SEEK_END);
    long total = ftell(f) / sizeof(Endereco);
    rewind(f);
    long divisao = total / PARTES, resto = total % PARTES;
    // 1) divide, ordena cada parte e grava cep_0.dat ... cep_(PARTES-1).dat
    Endereco *v = malloc((divisao + 1) * sizeof(Endereco));   // +1 por causa do resto
    if (v == NULL) { fclose(f); return 1; }
    char nome[64];
    for (int i = 0; i < PARTES; i++) {
        long qtd = divisao + (i < resto ? 1 : 0);              // resto vai para as primeiras
        fread(v, sizeof(Endereco), qtd, f);
        qsort(v, qtd, sizeof(Endereco), compara);
        sprintf(nome, "cep_%d.dat", i);
        FILE *p = fopen(nome, "wb");
        if (p == NULL) { free(v); fclose(f); return 1; }
        fwrite(v, sizeof(Endereco), qtd, p);
        fclose(p);
    }
    free(v); fclose(f);
    // 2) intercala dois a dois; o resultado ganha o próximo número
    int proximo = PARTES;                // nome do próximo arquivo a ser criado
    for (int i = 0; i < proximo - 1; i += 2) {   // i e i+1 são o par da vez
        char a[64], b[64], s[64];
        sprintf(a, "cep_%d.dat", i);
        sprintf(b, "cep_%d.dat", i + 1);
        sprintf(s, "cep_%d.dat", proximo);
        intercala(a, b, s);
        proximo++;
    }
    printf("arquivo final: cep_%d.dat\n", proximo - 1);   // = 2*PARTES - 2
    return 0;
}
```

- Arquivo final = **`cep_(2·PARTES − 2).dat`**: com 8 partes é `cep_14.dat`, com 5 é `cep_8.dat`, com 1 é `cep_0.dat` (testei 1, 3, 5, 7 e 8).
- Número de intercalações = `PARTES − 1`.
- O **resto** da divisão vai para as primeiras partes (`i < resto ? +1 : +0`); por isso o `malloc` é de `(divisao + 1)` registros.
- O laço `i += 2` percorre o par da vez; como `proximo` cresce, ele alcança também os arquivos novos.
- Limpar os temporários: `rm cep_*.dat` (o `cep.dat` não tem `_`, não é apagado).

## 7.25 Bloco 5 — agrupamento, lacuna e janela: E20, E21, E22

### E20 — Agrupar por sigla (ordenar e depois contar grupos)

```c
// (começa com o cabeçalho comum do 7.21)
int comparaSigla(const void *a, const void *b) {
    return memcmp(((const Endereco*)a)->sigla, ((const Endereco*)b)->sigla, 2);
}
int main(int argc, char **argv) {
    if (argc != 2) { printf("uso: %s cep.dat\n", argv[0]); return 1; }
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Endereco);
    rewind(f);
    Endereco *v = malloc(n * sizeof(Endereco));
    if (v == NULL) { fclose(f); return 1; }
    fread(v, sizeof(Endereco), n, f);
    fclose(f);
    qsort(v, n, sizeof(Endereco), comparaSigla);          // (1) ordena pela sigla
    FILE *s = fopen("por-sigla.dat", "wb");
    if (s == NULL) { free(v); return 1; }
    fwrite(v, sizeof(Endereco), n, s);
    fclose(s); free(v);

    f = fopen("por-sigla.dat", "rb");                     // (2) agrupa lendo 1 por vez
    if (f == NULL) return 1;
    Endereco r;
    char atual[2] = {0, 0};
    long cont = 0;
    while (fread(&r, sizeof(Endereco), 1, f) == 1) {
        if (cont > 0 && memcmp(r.sigla, atual, 2) != 0) { // mudou de grupo: fecha o anterior
            printf("%.2s: %ld\n", atual, cont);
            cont = 0;
        }
        memcpy(atual, r.sigla, 2);
        cont++;
    }
    if (cont > 0) printf("%.2s: %ld\n", atual, cont);     // ÚLTIMO grupo, depois do laço
    fclose(f);
    return 0;
}
```

- Padrão de **grupo**: compara o registro atual com o grupo atual; mudou → imprime e zera.
- **O último grupo só é impresso depois do laço**. Esquecer isso é a pegadinha clássica.
- Comparador novo, pela sigla de 2 bytes: `memcmp(..., 2)`; impressão `%.2s` (sem `'\0'`).

### E21 — Lacunas

Arquivo de `long` (8 bytes cada). Imprime `lacuna entre A e B` quando um valor não é o anterior `+ 1`.

```c
#include <stdio.h>
int main(int argc, char **argv) {
    if (argc != 2) { printf("uso: %s numeros.dat\n", argv[0]); return 1; }
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    long ant, atual;
    if (fread(&ant, sizeof(long), 1, f) == 1) {           // o primeiro não tem anterior
        while (fread(&atual, sizeof(long), 1, f) == 1) {
            if (atual != ant + 1)
                printf("lacuna entre %ld e %ld\n", ant, atual);
            ant = atual;
        }
    }
    fclose(f);
    return 0;
}
```

- O **primeiro** valor não tem anterior: lê fora do laço.
- Dentro do laço: compara, depois `ant = atual`.
- Com `1 2 3 4 7 8 9 15 16` (valores do teste, ilustrativos) saem as lacunas `4→7` e `9→15`.

### E22 — Janela móvel

Soma de cada janela de `k` registros seguidos.

```c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    if (argc != 3) { printf("uso: %s numeros.dat k\n", argv[0]); return 1; }
    long k = atol(argv[2]);
    if (k <= 0) return 1;
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    long v, soma;
    while (1) {
        soma = 0;
        long i;
        for (i = 0; i < k; i++) {                         // lê k valores
            if (fread(&v, sizeof(long), 1, f) != 1) break;
            soma += v;
        }
        if (i < k) break;                                 // janela incompleta: acabou
        printf("%ld\n", soma);
        fseek(f, -(long)((k - 1) * sizeof(long)), SEEK_CUR);  // volta k-1 registros
    }
    fclose(f);
    return 0;
}
```

- Lê `k`, soma, **volta `k − 1`** registros: `fseek(f, -(long)((k - 1) * sizeof(long)), SEEK_CUR)`.
- Sem o `-(long)` o `sizeof` (sem sinal) quebra o recuo.
- Janela incompleta no fim: não imprime. Quantidade de janelas = `n − k + 1` (9 valores e `k=3` → 7 somas).

## 7.26 Bloco 6 — imagens BMP: E23 a E28

**Cabeçalho comum** (54 bytes; a struct do seu `gerabmp.c` sem o `pixels[]`):

```c
#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)                 // sem isso o compilador coloca enchimento e sizeof != 54
typedef struct {
    char magic[2];                                  // "BM"
    unsigned int tamanhoArquivo, lixo, inicioArray, tamCab2, largura, altura;
    unsigned short planes, bitsPorPixel;
    unsigned int compressao, tamanhoImagem, resH, resV, numeroCores, coresImportantes;
} CabBMP;
#pragma pack()
int padding(int largura) { return (4 - (largura * 3) % 4) % 4; }
long tamanhoArquivo(int largura, int altura) {
    return 54 + (long)altura * (largura * 3 + padding(largura));
}
```

> **Lembretes do formato:** cada pixel = 3 bytes na ordem **B, G, R**. Cada linha ocupa `largura × 3` bytes **mais o padding**, para fechar múltiplo de 4. `padding = (4 − (largura×3) % 4) % 4`. Os pixels começam no byte 54.

### E23 — Ler o cabeçalho

```c
// (começa com o cabeçalho BMP do 7.26)
int main(int argc, char **argv) {
    if (argc != 2) { printf("uso: %s arq.bmp\n", argv[0]); return 1; }
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) { printf("erro ao abrir\n"); return 1; }
    CabBMP c;
    if (fread(&c, sizeof(CabBMP), 1, f) != 1 || c.magic[0] != 'B' || c.magic[1] != 'M') {
        printf("nao e BMP\n"); fclose(f); return 1;
    }
    printf("largura: %u\naltura: %u\nbits por pixel: %u\npixels comecam em: %u\ntamanho (cabecalho): %u\n",
           c.largura, c.altura, c.bitsPorPixel, c.inicioArray, c.tamanhoArquivo);
    fclose(f);
    return 0;
}
```

### E24 — Padding

```c
// (começa com o cabeçalho BMP do 7.26)
int main(void) {
    for (int l = 1; l <= 8; l++)
        printf("%d %d %ld\n", l, padding(l), tamanhoArquivo(l, 3));
    return 0;
}
```

Saída (largura, padding, tamanho com altura 3): `1 1 66 · 2 2 78 · 3 3 90 · 4 0 90 · 5 1 102 · 6 2 114 · 7 3 126 · 8 0 126` (confere com a tabela do enunciado).

### E25 — Gerar um BMP de qualquer largura (degradê)

```c
// (começa com o cabeçalho BMP do 7.26)
int main(int argc, char **argv) {
    if (argc != 4) { printf("uso: %s saida.bmp largura altura\n", argv[0]); return 1; }
    int L = atoi(argv[2]), A = atoi(argv[3]);
    if (L <= 0 || A <= 0) return 1;
    FILE *f = fopen(argv[1], "wb");
    if (f == NULL) { printf("erro ao criar\n"); return 1; }
    CabBMP c = {0};                                       // zera tudo
    c.magic[0] = 'B'; c.magic[1] = 'M';
    c.tamanhoArquivo = tamanhoArquivo(L, A);
    c.inicioArray = 54; c.tamCab2 = 40;
    c.largura = L; c.altura = A;
    c.planes = 1; c.bitsPorPixel = 24;
    c.tamanhoImagem = c.tamanhoArquivo - 54;
    fwrite(&c, sizeof(CabBMP), 1, f);
    int pad = padding(L);
    unsigned char zero[3] = {0, 0, 0};
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < L; j++) {
            unsigned char px[3];
            px[0] = j * 255 / L;                          // B
            px[1] = i * 255 / A;                          // G
            px[2] = 128;                                  // R
            fwrite(px, 1, 3, f);
        }
        fwrite(zero, 1, pad, f);                          // padding de cada linha
    }
    fclose(f);
    return 0;
}
```

- `CabBMP c = {{0}};` zera tudo; preencha só o que importa.
- Depois de **cada linha** grave o padding (bytes `0`).
- Pixel: `B = j·255/largura`, `G = i·255/altura`, `R = 128`, nessa ordem de bytes.
- Confira com `file g5.bmp` (deve dizer `5 x 3 x 24`, `cbSize 102`).

### E26, E27, E28 — Negativo, cinza e espelho (mesma estrutura)

Os três **lêem linha por linha** (pixels **+ padding**), alteram só os pixels e gravam a linha inteira. O cabeçalho é copiado igual. Escreva uma vez a função `processa` e troque só a função de linha:

```c
// (começa com o cabeçalho BMP acima)
typedef void (*Func)(unsigned char *linha, int largura);
int processa(char *ent, char *sai, Func f) {
    FILE *e = fopen(ent, "rb");
    if (e == NULL) { printf("erro ao abrir entrada\n"); return 1; }
    FILE *s = fopen(sai, "wb");
    if (s == NULL) { printf("erro ao criar saida\n"); fclose(e); return 1; }
    CabBMP c;
    fread(&c, sizeof(CabBMP), 1, e);
    fwrite(&c, sizeof(CabBMP), 1, s);                 // cabeçalho igual
    int bytes = c.largura * 3, pad = padding(c.largura);
    unsigned char *linha = malloc(bytes + pad);
    if (linha == NULL) { fclose(e); fclose(s); return 1; }
    for (unsigned i = 0; i < c.altura; i++) {
        fread(linha, 1, bytes + pad, e);              // pixels + padding
        f(linha, c.largura);                          // mexe só nos pixels
        fwrite(linha, 1, bytes + pad, s);
    }
    free(linha); fclose(e); fclose(s);
    return 0;
}
```

**E26 — negativo** (`255 − valor` em cada componente):

```c
void neg(unsigned char *l, int w) { for (int i = 0; i < w * 3; i++) l[i] = 255 - l[i]; }
int main(int argc, char **argv) {
    if (argc != 3) { printf("uso: %s ent.bmp sai.bmp\n", argv[0]); return 1; }
    return processa(argv[1], argv[2], neg);
}
```

**E27 — tons de cinza** (média inteira dos três):

```c
void cz(unsigned char *l, int w) {
    for (int i = 0; i < w; i++) {
        int m = (l[3*i] + l[3*i+1] + l[3*i+2]) / 3;   // divisão de inteiros
        l[3*i] = l[3*i+1] = l[3*i+2] = m;
    }
}
```

**E28 — espelho** (inverte cada linha):

```c
void esp(unsigned char *l, int w) {
    for (int i = 0; i < w / 2; i++)
        for (int k = 0; k < 3; k++) {                // troca o PIXEL i com o w-1-i
            unsigned char t = l[3*i + k];
            l[3*i + k] = l[3*(w-1-i) + k];
            l[3*(w-1-i) + k] = t;
        }
}
```

- **Padding não é pixel**: nas funções acima ele fica de fora, porque só vão até `w * 3` (ou `w` pixels).
- E28: troque **pixels inteiros** (3 bytes), não bytes soltos; senão B, G e R de cada pixel se invertem entre si e as cores mudam.
- Teste de sanidade: negativo duas vezes e espelho duas vezes devolvem o arquivo **idêntico** ao original (`cmp`). Testei com 5×3 (padding 1) e 200×100 (padding 0).
- Teste com **largura que não é múltipla de 4** (a `g5.bmp` do E25): é aí que o padding aparece.

## 7.27 Mais enunciados → técnica (complementa o 7.20)

| Se o enunciado pedir... | Pense em... |
|---|---|
| Trocar letras (maiúsculas) | `fgetc` com `int c` + conta na tabela ASCII + `fputc` |
| Contar quantas vezes cada byte aparece | `int contador[256]`, `contador[c]++` |
| Último registro / ordem inversa | `fseek` para `(n-1) × sizeof` e ir descendo, 1 registro por vez |
| 1 a cada `k` registros | `fread` + `fseek(..., (k-1) × sizeof, SEEK_CUR)` |
| Alterar um campo "no lugar", sem outro arquivo | `"r+b"` + `fseek` + `fread` + **volta 1 registro** + `fwrite` |
| Acrescentar registro no fim | `"ab"` + `memset` + `fwrite` |
| Salvar o índice para usar depois | `fwrite` do vetor inteiro; ler com `tamanho / sizeof(IndiceCep)` |
| Juntar dois arquivos ordenados | Intercalação com `temA` / `temB` + copiar o resto |
| Juntar sem repetir | Intercalação com 3 casos (menor A, menor B, **iguais**) |
| "Não cabe na memória" | Ordenação externa: partes → `qsort` → intercala 2 a 2 |
| Contar por grupo (sigla, UF…) | Ordenar pelo campo + laço com "grupo atual" + **tratar o último grupo** |
| Achar buracos em sequência | Guardar o anterior; imprimir quando `atual != anterior + 1` |
| Soma de k vizinhos | Ler k, somar, `fseek` de volta `k-1` |
| Imagem BMP | Cabeçalho de 54 bytes + linhas com **padding** |
| Quais chaves de B não estão em A (árvore B) | Indexar A (`insertKey`), percorrer B, `findKey`; só grava se `!achou` |

## 7.28 Mapa: API da prova × `ArvoreB.c` de estudo

O que aparece na prova (7.16 a 7.18) tem correspondente no `ArvoreB.c` que você estudou. A ideia é a mesma: **chave → offset em bytes**.

| Na prova | No `ArvoreB.c` de estudo | Observação |
|---|---|---|
| `openTree(nome)` | `ArvoreB_Abre(nome)` | Cria o arquivo da árvore se não existir |
| `insertKey(tree, long key, long offset)` | `ArvoreB_Insere(arvore, char chave[8], long pos)` | Na prova a chave é `long`; no estudo, 8 bytes de `char` |
| `findKey(tree, key, &offset)` → `bool` | `ArvoreB_Busca(arvore, chave)` → offset ou `-1` | Na prova o offset sai **por referência** |
| `closeTree(tree)` | `ArvoreB_Fecha(arvore)` | Sempre chamar antes de sair |

Por isso, na prova, **não** reimplemente a árvore: use só essas 4 funções. O custo de cada `insertKey` / `findKey` é o da altura da árvore (O(log n)).

## 7.29 Checklist — antes de entregar um exercício de programação

```text
[ ] Todos os #include certos? (stdio, stdlib, string; stdbool se usar bool)
[ ] argc conferido e cada fopen / malloc testado?
[ ] Modo de abertura certo? rb leitura · wb novo/apaga · r+b ler e alterar · ab acrescenta
[ ] fgetc guardado em int (não char)?
[ ] Passei &variável (e não a variável) no fread / fwrite / findKey?
[ ] sizeof(struct), e não sizeof do ponteiro?
[ ] fseek em BYTES: registro n → n × sizeof(Endereco)?
[ ] ftell ANTES do fread ao guardar o offset?
[ ] Depois do fread o cursor avançou: precisei voltar?
[ ] Comparador com cast certo e sem subtração que estoure?
[ ] CEP sem '\0': memcmp / memcpy com 8, nunca strcmp / strcpy?
[ ] Tratei o último grupo / o resto da intercalação?
[ ] Fechei os arquivos e dei free no que alocei?
[ ] return 0 no fim do main?
```

## 7.30 Pontos básicos da P1 que a P2 usa (resumo para consulta)

> Tudo aqui já aparece nos subtópicos anteriores e na seção 5; este é o resumo **num lugar só**, para quando o enunciado da P2 (árvore B, índice, busca) pedir "leia o registro", "volte ao início", "ordene" ou "aloque".

### `fopen` — modos

| Modo | Faz | Quando usar |
|---|---|---|
| `"rb"` | só lê; o arquivo precisa existir | ler dados / índice |
| `"wb"` | cria ou **APAGA** e escreve | arquivo de saída novo |
| `"r+b"` | lê **e** escreve; não apaga; precisa existir | alterar registro no lugar |
| `"ab"` | escreve **sempre no fim** (`fseek` não muda isso) | acrescentar registro |
| `"w+b"` | lê e escreve; cria ou **APAGA** | arquivo novo que também será relido |

Sempre `if (f == NULL) {...}` depois do `fopen`; se o **2º** `fopen` falhar, feche o 1º antes de sair.

### `fgetc` / `fputc` — byte a byte

```c
int c;                              // int, nunca char (precisa caber o EOF = -1)
while ((c = fgetc(f)) != EOF)
    fputc(c, saida);
```

### `fread` / `fwrite` — registros

```c
fread(&r, sizeof(Registro), 1, f);        // 1 registro numa variável → com &
fread(v, sizeof(Registro), qtd, f);       // vários num vetor/malloc → SEM &
fwrite(&r, sizeof(Registro), 1, saida);

while (fread(&r, sizeof(Registro), 1, f) == 1) { /* processa r */ }
```

- Os dois **devolvem quantos itens** leram/gravaram (não bytes). Compare com `== 1` (ou com `qtd`).
- Os dois **avançam o cursor** pelo que leram/gravaram.
- `feof(f)` só vira verdadeiro **depois** de uma leitura que falhou: não use como condição do laço.

### `fseek`, `ftell`, `rewind`

```c
fseek(f, deslocamento, SEEK_SET);   // conta a partir do INÍCIO do arquivo
fseek(f, deslocamento, SEEK_CUR);   // conta a partir da posição ATUAL (pode ser negativo)
fseek(f, deslocamento, SEEK_END);   // conta a partir do FIM
long pos = ftell(f);                // posição atual em BYTES (devolve long)
rewind(f);                          // volta ao início
```

| Comparação | Diferença |
|---|---|
| `fseek` × `ftell` | `fseek` **muda** a posição; `ftell` só **informa** a posição atual |
| `rewind(f)` × `fseek(f, 0, SEEK_SET)` | Mesmo efeito na posição; o `rewind` ainda limpa o indicador de fim/erro e não devolve valor |

Fórmulas (registros de tamanho fixo):

```text
quantidade de registros = tamanho do arquivo / sizeof(Registro)
registro número i (primeiro = 0)  → offset = i * sizeof(Registro)
registro número n (primeiro = 1)  → offset = (n - 1) * sizeof(Registro)
tamanho do arquivo:  fseek(f, 0, SEEK_END);  long tam = ftell(f);  rewind(f);
```

Pegadinhas:

- `fseek(f, 0, SEEK_END)` leva ao **fim** (depois do último registro), não **ao** último registro. O último é `fseek(f, -(long)sizeof(Registro), SEEK_END)`.
- Deslocamento **negativo**: `-(long)sizeof(Registro)`. O `sizeof` é sem sinal, então escreva sempre o cast `(long)`.
- Depois de `fread` de 1 registro o cursor já está no **seguinte**. Para reescrever o mesmo: `fseek(f, -(long)sizeof(Registro), SEEK_CUR)` e então `fwrite`.
- Guardar a posição de um registro: `long offset = ftell(f);` **antes** do `fread` (é o que se passa ao `insertKey` da árvore B).
- Ler um registro pelo offset (vindo da árvore): `fseek(f, offset, SEEK_SET); fread(&r, sizeof(Registro), 1, f);` (offset já está em **bytes**: não multiplique).

### `malloc` / `free` / `sizeof`

```c
Registro *v = malloc(qtd * sizeof(Registro));
if (v == NULL) { /* erro: feche o que abriu e saia */ }
/* ... usa v[0] ... v[qtd-1] ... */
free(v);
```

- `sizeof(Registro)` = tamanho de **um** elemento; `sizeof(v)` com `v` ponteiro é o tamanho do **ponteiro** (errado aqui).
- Vetores começam no **0**: o último é `v[qtd - 1]`.
- Um único `fread(v, sizeof(Registro), qtd, f)` enche o vetor.

### `qsort` e comparador

```c
qsort(v, qtd, sizeof(Registro), compara);      // compara SEM parênteses
```

```c
int compara(const void *a, const void *b) {
    const Registro *x = (const Registro*) a;   // cast para o MESMO tipo do vetor
    const Registro *y = (const Registro*) b;
    if (x->chave < y->chave) return -1;        // negativo: x vem antes
    if (x->chave > y->chave) return  1;        // positivo: x vem depois
    return 0;                                  // zero: iguais
}
```

- Chave `long`/`int`: compare com `<` e `>`. Não devolva `x - y`: a subtração pode **estourar**.
- Chave de **bytes sem `'\0'`** (como o `cep[8]`): `return memcmp(x->cep, y->cep, 8);`. Nunca `strcmp`.
- O `sizeof` do `qsort` tem de combinar com o tipo do vetor e com o cast do comparador.
- `qsort` **ordena**; busca binária **procura** num vetor/arquivo **já ordenado**. São coisas diferentes.

### Resto do básico

| Assunto | Lembrete |
|---|---|
| `argc` / `argv` | `if (argc != N) {...}`; `argv[0]` é o nome do programa, `argv[1]` o 1º argumento |
| `struct` | `e.campo` (variável) · `p->campo` (ponteiro para struct) |
| Ponteiro | `x` conteúdo, `&x` endereço; `p` endereço, `*p` conteúdo apontado |
| `memset(&r, 0, sizeof(r))` | zera a struct antes de preencher (senão grava lixo de memória no arquivo) |
| `return` | `return 1;` ao falhar · `return 0;` no fim do `main` · `return;` em função `void` |
| Bytes × registros | `fseek`/`ftell` contam **bytes**; `fread`/`fwrite` contam **itens** |

## 7.31 Lembretes da P1 (contas e últimos lembretes)

> Mesmos lembretes da seção 5.14, mais as suas anotações (`anotacao.txt`). Os programas para copiar e colar (copiar byte a byte e em blocos, busca, índice, ordenação externa, intercalação) continuam na seção 5.13.

### 📍 Posição e quantidade

```text
registro n (primeiro = 0)  → n * sizeof(Tipo) bytes
fseek(f, n * sizeof(Tipo), SEEK_SET);

bytes / sizeof(Tipo)       → quantidade de registros
registros * sizeof(Tipo)   → bytes
```

### 🧠 Ponteiros

```text
Tipo x;      x → conteúdo      &x → endereço
Tipo *x;     x → endereço      *x → conteúdo apontado
struct       → .
ponteiro     → ->
```

### 📖 Leitura

```text
fgetc → 1 byte → int
fread → itens/registros
ler → testar → usar → ler de novo
```

- `fread` **avança** o cursor; `ftell` acompanha isso (depois do `fread` ele já informa o início do **próximo** registro).
- `EOF` **não** é `feof`: `EOF` é o valor que o `fgetc` devolve; `feof(f)` só fica verdadeiro **depois** de uma leitura que tentou passar do fim.
- `ftell` devolve **`long`**: guarde em `long` e imprima com `%ld`.

### 🔎 Busca

```text
sequencial:  fread → compara → continua/para
binária:     meio → fseek → fread → compara      (arquivo ORDENADO)

ANTES  → continua
IGUAL  → faz
DEPOIS → break
```

### 📇 Índice

```text
índice = chave + posição original
busca no índice → encontra a posição → fseek no arquivo original → fread
ordenar o índice NÃO muda a posição guardada
```

### 📦 Ordenação externa

```text
arquivo grande → dividir → qsort cada parte → intercalar 2 a 2 → repetir → 1 arquivo

divisao = quantidade / PARTES        i < resto  → parte com divisao + 1
resto   = quantidade % PARTES        i >= resto → parte com divisao

PARTES = 8  →  intercalações = PARTES − 1 = 7  →  arquivo final = cep_14.dat
(fórmula geral: arquivo final = cep_(2·PARTES − 2).dat)
```

### ⚠️ Últimos lembretes

```text
fseek(SEEK_END)   → vai para o FIM, não para o último registro
ftell()           → long
fgetc()           → int
fread()/fwrite()  → devolvem itens, não bytes
malloc()          → recebe BYTES (qtd * sizeof)
free()            → depois do último uso
qsort(..., compara) → sem ()
wb                → apaga
ab                → adiciona no final
vetores           → começam no 0
return 0          → fim do main (não esquecer)
```

---

# 🧠 Ideia central da matéria

Quase tudo se apoia em uma mesma ideia:

> **Os registros têm tamanho fixo.**

Então conseguimos transformar:

```text
BYTES ↔ REGISTROS
```

com:

```text
quantidade de registros = tamanho do arquivo / sizeof(Endereco)

posição em bytes = número do registro * sizeof(Endereco)
```

Isso permite:

```text
tamanho fixo
   │
   ├──► fseek → acesso direto
   │          │
   │          ├── busca binária
   │          └── índice
   │
   └──► contar registros
              │
              └── ordenação externa
```

E a escolha do programa vem do enunciado:

```text
1 byte por vez?
    → fgetc/fputc

1 registro por vez?
    → fread/fwrite

arquivo inteiro cabe na memória?
    → malloc + fread + qsort + fwrite

arquivo já ordenado e precisa buscar?
    → busca binária + fseek

arquivo não está ordenado, mas quer buscar rápido?
    → índice

arquivo não cabe na memória?
    → ordenação externa

precisa comparar registros em sequência?
    → busca sequencial
```

---

## 🔗 Onde a P2 se encaixa

A P2 não é outra matéria solta: ela **continua** a ideia dos registros de tamanho fixo. Cada assunto da P2 é uma versão "grande" de algo que já existe na P1.

```text
P1: registros de tamanho fixo → posição = n × sizeof(Tipo) → fseek
         │
         ├── índice em MEMÓRIA (3.5)    ──► índice em DISCO: árvore B / B+
         │                                  (chave → offset em bytes)
         │
         ├── posição = n × sizeof(Tipo) ──► hash: posição = h(k) × tamanho da entrada
         │                                  (a função de hash escolhe o n)
         │
         └── contador[256] de bytes     ──► Huffman: as frequências dos bytes
             (3.1, "contar cada byte")      viram o código de cada símbolo
```

- **Árvore B/B+:** o índice da P1 fica na memória. Quando ele não cabe, ele vai para o disco, em blocos, e a árvore B/B+ é essa organização. O que ela guarda continua sendo a **posição em bytes** do registro (por isso `ftell` **antes** do `fread` na questão 4 da P2).
- **Hash:** é a mesma conta de posição da P1, mas o número do registro não vem de uma contagem: vem de `h(k)`. Se dois registros caem na mesma posição, há **colisão**, tratada aqui por **encadeamento externo**.
- **Huffman:** a entrada dele é o mesmo `contador[256]` do item 3.1 da P1. Quanto mais frequente o byte, mais curto o código.

## 🧭 Do enunciado ao método (P1 + P2)

```text
achar 1 registro por chave, num arquivo sem ordem?
    → busca sequencial                              (P1)

arquivo ordenado e quer achar um registro?
    → busca binária + fseek                         (P1)

o índice cabe na memória?
    → índice em memória + qsort                     (P1)

índice grande, no disco, e preciso de FAIXA ou de ORDEM?
    → árvore B+                                     (P2)

só IGUALDADE, sem faixa e sem ordem?
    → hash com encadeamento externo                 (P2)

reduzir o tamanho do arquivo usando a frequência dos bytes?
    → código de Huffman (heap + algoritmo guloso)   (P2)
```

E, dentro da P2, o que cada estrutura entrega:

| | Árvore B+ | Hash | Huffman |
|---|---|---|---|
| Para que serve | achar registro, faixa e ordem | achar registro por igualdade | comprimir |
| O que decide a posição | comparação de chaves, descendo a árvore | `h(k)` | a frequência de cada símbolo |
| O que custa | altura da árvore (leituras de bloco) | tamanho da lista de colisões | soma de frequência × tamanho do código |
| Guia | [`arvores/`](arvores/README.md) | [`hash/`](hash/README.md) | [`arvore-huf/`](arvore-huf/README.md) |
