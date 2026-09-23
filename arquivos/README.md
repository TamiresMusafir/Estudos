# 📁 Estrutura de Arquivos em C — Material de Prova

Material de consulta e revisão sobre arquivos, registros, memória, ponteiros, busca, índices e ordenação externa em C.

## 📑 Sumário

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

if(f == NULL){
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
return valor; → função retorna um valor
return 0;     → retorna 0 (ex.: sucesso)
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
