# 📁 Estrutura de Arquivos em C — Material de Prova

Material de consulta e revisão sobre arquivos, registros, memória, ponteiros, busca, índices e ordenação externa em C.

## 📑 Sumário

O material é um só, em duas partes: **P1** (arquivos em C) e **P2** (árvores B/B+, hash e Huffman). No fim há a [Ideia central da matéria](#-ideia-central-da-matéria), que junta as duas.

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
  - [6.7 Pontos básicos da P1 que a P2 usa](#67-pontos-básicos-da-p1-que-a-p2-usa)
  - [6.8 Lembretes da P1 (contas e últimos lembretes)](#68-lembretes-da-p1-contas-e-últimos-lembretes)
  - [6.9 Checklist — antes de entregar a P2](#69-checklist--antes-de-entregar-a-p2)

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
| Lembrar rápido `fopen`, `fseek`, `fread`, `malloc`, `qsort` | [6.7](#67-pontos-básicos-da-p1-que-a-p2-usa) |
| Contas e lembretes da P1 | [6.8](#68-lembretes-da-p1-contas-e-últimos-lembretes) |

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

## 6.7 Pontos básicos da P1 que a P2 usa

> Tudo aqui já aparece nas seções 1 a 5; este é o resumo **num lugar só**, para quando o enunciado da P2 (árvore B, índice, busca) pedir "leia o registro", "volte ao início", "ordene" ou "aloque".

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

## 6.8 Lembretes da P1 (contas e últimos lembretes)

> Mesmos lembretes da [seção 5.14](#514-contas-e-lembretes), mais as anotações do `anotacao.txt`. Os programas para copiar e colar (copiar byte a byte e em blocos, busca, índice, ordenação externa, intercalação) estão na [seção 5.13](#513-programas-para-copiar-e-colar).

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

## 6.9 Checklist — antes de entregar a P2

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
