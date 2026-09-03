# Ordenação de Arquivos com `qsort` — C

## Sumário

1. [Objetivo do programa](#1-objetivo-do-programa)
2. [A struct `Endereco`](#2-a-struct-endereco)
3. [`Endereco` x `Endereco *e`](#3-endereco-x-endereco-e)
4. [`.` x `->`](#4--x--)
5. [`&` e `*`](#5--e-)
6. [`malloc`](#6-malloc)
7. [`fseek`, `ftell` e `rewind`](#7-fseek-ftell-e-rewind)
8. [`fread`](#8-fread)
9. [`qsort`](#9-qsort)
10. [A função `compara`](#10-a-função-compara)
11. [De onde vêm `e1` e `e2`](#11-de-onde-vêm-e1-e-e2)
12. [`fwrite`](#12-fwrite)
13. [`free`](#13-free)
14. [Fluxo completo do programa](#14-fluxo-completo-do-programa)
15. [Resumo dos conceitos](#15-resumo-dos-conceitos)
16. [Código completo comentado](#16-código-completo-comentado)

---

# 1. Objetivo do programa

O programa:

1. Abre o arquivo `cep.dat`;
2. Descobre quantos registros existem;
3. Reserva memória suficiente para armazenar todos eles;
4. Lê todos os registros para a memória;
5. Ordena os registros pelo CEP usando `qsort`;
6. Cria o arquivo `cep-ordenado.dat`;
7. Grava os registros ordenados nesse novo arquivo;
8. Libera a memória.

Fluxo:

```text
cep.dat
   ↓
fread()
   ↓
Registros na memória
   ↓
qsort()
   ↓
Registros ordenados pelo CEP
   ↓
fwrite()
   ↓
cep-ordenado.dat
```

> **`fread` carrega → `qsort` organiza → `fwrite` salva.**

---

# 2. A struct `Endereco`

```c
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
```

A `struct` define o formato de **um registro**.

Cada `Endereco` possui:

```text
Endereco
├── logradouro
├── bairro
├── cidade
├── uf
├── sigla
├── cep
└── lixo
```

O `typedef` permite usar:

```c
Endereco
```

em vez de:

```c
struct _Endereco
```

---

# 3. `Endereco` x `Endereco *e`

## `Endereco e`

```c
Endereco e;
```

Aqui `e` é uma **struct de verdade**.

```text
e
┌─────────────────────┐
│ logradouro          │
│ bairro              │
│ cidade              │
│ uf                  │
│ sigla               │
│ cep                 │
│ lixo                │
└─────────────────────┘
```

Para acessar seus campos:

```c
e.cep
```

---

## `Endereco *e`

```c
Endereco *e;
```

Aqui `e` é um **ponteiro**.

Ele guarda o endereço de memória onde existe um `Endereco`.

```text
e
│
│ guarda um endereço
↓
1000
┌─────────────────────┐
│ Endereco            │
│ cep = "20040000"    │
└─────────────────────┘
```

Por isso:

```c
e->cep
```

é usado para acessar o CEP através do ponteiro.

---

# 4. `.` x `->`

Regra para decorar:

```text
Tenho a struct:
    e.cep

Tenho um ponteiro para a struct:
    e->cep
```

Exemplo:

```c
Endereco e;

e.cep;
```

Usamos `.` porque `e` é a própria struct.

Já:

```c
Endereco *e;

e->cep;
```

Usamos `->` porque `e` é um ponteiro.

---

# 5. `&` e `*`

## `&` — endereço

O operador `&` significa:

> Pegue o endereço de uma variável.

Se temos:

```c
Endereco e;
```

então:

```c
&e
```

é o endereço de `e`.

```text
e  → a própria struct

&e → endereço da struct
```

Por isso:

```c
fread(&e, sizeof(Endereco), 1, f);
```

pode ser usado quando `e` é uma struct normal.

---

## `*` — acessar o conteúdo apontado

Se:

```c
Endereco *e;
```

então `e` guarda um endereço.

```c
*e
```

significa:

> Acesse o `Endereco` que está naquele endereço.

Resumo:

```text
Endereco e

e   → struct
&e  → endereço da struct
```

```text
Endereco *e

e   → endereço
*e  → struct naquele endereço
```

---

# 6. `malloc`

```c
e = (Endereco*) malloc(qtd * sizeof(Endereco));
```

`malloc` serve para **reservar memória dinamicamente**.

Não sabemos previamente quantos registros existem no arquivo.

Por isso não fazemos simplesmente:

```c
Endereco e[1000];
```

O arquivo pode ter 1.000, 50.000 ou 1.000.000 registros.

Primeiro descobrimos:

```c
qtd = posicao / sizeof(Endereco);
```

Depois reservamos exatamente o espaço necessário:

```c
malloc(qtd * sizeof(Endereco));
```

---

## O que o `malloc` retorna?

O `malloc` retorna um **endereço de memória**.

Por exemplo:

```text
malloc(...)
   ↓
1000
```

Então:

```c
e = malloc(...);
```

faz:

```text
e
↓
1000
┌──────────┬──────────┬──────────┐
│ Endereco │ Endereco │ Endereco │
└──────────┴──────────┴──────────┘
```

Nesse momento, temos espaço reservado, mas ainda não colocamos os dados do arquivo.

---

## `(Endereco*)` é casting?

Sim.

```c
(Endereco*) malloc(...)
```

é um **casting**.

O `malloc` retorna um `void *`, ou seja, um ponteiro genérico.

O casting diz:

> "Trate esse endereço como um ponteiro para `Endereco`."

Em C, o casting não é necessário:

```c
e = malloc(qtd * sizeof(Endereco));
```

já funciona.

---

# 7. `fseek`, `ftell` e `rewind`

O programa faz:

```c
fseek(f, 0, SEEK_END);
posicao = ftell(f);
```

## `fseek`

```c
fseek(f, 0, SEEK_END);
```

Move a posição atual do arquivo para o final.

```text
[registro][registro][registro][registro]
                                      ↑
                                    posição
```

---

## `ftell`

```c
posicao = ftell(f);
```

Informa a posição atual.

Como estamos no final do arquivo, essa posição representa o tamanho do arquivo em bytes.

---

## `rewind`

Depois de descobrir o tamanho, a posição do arquivo continua no final.

Por isso:

```c
rewind(f);
```

volta para o começo.

```text
Antes:

[registro][registro][registro]
                            ↑
                          final


Depois do rewind:

[registro][registro][registro]
 ↑
começo
```

Isso é necessário porque o próximo comando será:

```c
fread(...)
```

e o `fread` começa a ler **da posição atual do arquivo**.

Resumo:

```text
fseek → vai para o final
ftell → descobre o tamanho
rewind → volta para o começo
fread → lê os registros
```

---

# 8. `fread`

A chamada:

```c
fread(e, sizeof(Endereco), qtd, f);
```

possui quatro parâmetros:

```text
fread(
    onde,
    tamanho de cada elemento,
    quantidade,
    arquivo
);
```

### `e`

Onde os dados serão colocados.

Como `e` é um ponteiro, ele contém o endereço da memória reservada pelo `malloc`.

### `sizeof(Endereco)`

Tamanho de **um** `Endereco`.

O `fread` precisa saber isso para saber onde termina um registro e começa o próximo.

### `qtd`

Quantidade de `Endereco`s que queremos ler.

### `f`

Arquivo de onde os dados serão lidos.

---

## Exemplo

Se:

```text
sizeof(Endereco) = 300
qtd = 3
```

então:

```c
fread(e, sizeof(Endereco), qtd, f);
```

significa:

```text
300 bytes → Endereco 0
300 bytes → Endereco 1
300 bytes → Endereco 2
```

---

## O que acontece na memória?

Antes do `fread`:

```text
e
↓
┌──────────┬──────────┬──────────┐
│  vazio   │  vazio   │  vazio   │
└──────────┴──────────┴──────────┘
```

Depois:

```text
e
↓
┌────────────┬────────────┬────────────┐
│ Endereco 0 │ Endereco 1 │ Endereco 2 │
│ CEP = ...  │ CEP = ...  │ CEP = ...  │
└────────────┴────────────┴────────────┘
```

O `fread` coloca **o registro inteiro**, não apenas o CEP.

---

## Retorno do `fread`

`fread` retorna quantos elementos conseguiu ler.

Por isso:

```c
if(fread(e, sizeof(Endereco), qtd, f) == qtd)
```

significa:

> "A quantidade de elementos que consegui ler é igual à quantidade que esperava?"

Se sim:

```c
printf("Lido = OK\n");
```

---

# 9. `qsort`

```c
qsort(e, qtd, sizeof(Endereco), compara);
```

O `qsort` ordena os elementos que começam no endereço `e`.

Os parâmetros são:

```text
qsort(
    onde estão os elementos,
    quantidade,
    tamanho de cada elemento,
    função de comparação
);
```

Portanto:

```c
qsort(e, qtd, sizeof(Endereco), compara);
```

significa:

> "Ordene os `qtd` Enderecos que começam em `e`, sabendo que cada um possui `sizeof(Endereco)` bytes, usando `compara` para decidir a ordem."

---

# 10. A função `compara`

```c
int compara(const void *e1, const void *e2)
{
    return strncmp(
        ((Endereco*)e1)->cep,
        ((Endereco*)e2)->cep,
        8
    );
}
```

A função recebe dois elementos:

```text
e1 → primeiro elemento
e2 → segundo elemento
```

Mas o `qsort` é genérico e trabalha com `void *`.

Por isso fazemos o casting:

```c
(Endereco*)e1
```

e:

```c
(Endereco*)e2
```

Isso significa:

> "Trate esse endereço como um ponteiro para `Endereco`."

Então:

```c
((Endereco*)e1)->cep
```

significa:

```text
e1
 ↓
ponteiro para Endereco
 ↓
acessa o campo cep
```

Depois:

```c
strncmp(..., ..., 8)
```

compara os 8 caracteres dos dois CEPs.

---

## O que `compara` retorna?

```text
resultado < 0
→ primeiro CEP vem antes

resultado = 0
→ CEPs iguais

resultado > 0
→ primeiro CEP vem depois
```

O `qsort` usa esse resultado para saber como organizar os registros.

---

# 11. De onde vêm `e1` e `e2`?

Nós não criamos `e1` e `e2` no `main`.

Eles são **parâmetros da função `compara`**:

```c
int compara(const void *e1, const void *e2)
```

Quem chama `compara` é o próprio `qsort`.

Conceitualmente, ele pode fazer algo como:

```c
compara(&e[0], &e[1]);
```

Depois:

```c
compara(&e[2], &e[5]);
```

e assim por diante.

O `qsort` decide quais elementos precisa comparar.

Nós apenas fornecemos a função:

```c
qsort(e, qtd, sizeof(Endereco), compara);
```

---

## `compara` x `compara()`

```c
qsort(..., compara);
```

→ entrega a função para o `qsort`.

```c
compara();
```

→ executa a função.

Queremos que o `qsort` execute a função quando precisar.

---

# 12. `fwrite`

Depois que o `qsort` terminou:

```c
fwrite(e, sizeof(Endereco), qtd, saida);
```

faz o caminho contrário do `fread`.

```text
fread:
arquivo → memória

fwrite:
memória → arquivo
```

Os parâmetros são:

```text
fwrite(
    de onde pegar,
    tamanho de cada elemento,
    quantidade,
    arquivo
);
```

Então:

```c
fwrite(e, sizeof(Endereco), qtd, saida);
```

significa:

> "Pegue os `qtd` Enderecos que estão na memória começando em `e` e grave no arquivo `saida`."

---

# 13. `free`

Depois de terminar:

```c
free(e);
```

libera a memória que foi reservada pelo:

```c
malloc(...)
```

Fluxo:

```text
malloc
  ↓
reserva memória

fread
  ↓
preenche a memória

qsort
  ↓
organiza a memória

fwrite
  ↓
salva os dados

free
  ↓
libera a memória
```

---

# 14. Fluxo completo do programa

```text
                         cep.dat
                            │
                            ↓
                          fopen
                            │
                            ↓
                    fseek → final
                            │
                            ↓
                    ftell → tamanho
                            │
                            ↓
                       calcula qtd
                            │
                            ↓
                         malloc
                            │
                            ↓
                  reserva espaço na RAM
                            │
                            ↓
                         rewind
                            │
                            ↓
                     volta ao começo
                            │
                            ↓
                          fread
                            │
                            ↓
              todos os Enderecos na RAM
                            │
                            ↓
                          qsort
                            │
                            ↓
                ordena os Enderecos
                   usando o CEP
                            │
                            ↓
                         fwrite
                            │
                            ↓
                   cep-ordenado.dat
                            │
                            ↓
                          free
                            │
                            ↓
                    libera a memória
```

---

# 15. Resumo dos conceitos

## Ponteiros

```text
Endereco e
→ uma struct

Endereco *e
→ ponteiro para uma struct

&e
→ endereço de uma variável

*e
→ conteúdo apontado por e

e.cep
→ acessa campo quando e é uma struct

e->cep
→ acessa campo quando e é ponteiro
```

---

## Memória

```text
malloc()
→ reserva memória

free()
→ libera memória
```

---

## Arquivos

```text
fseek()
→ move a posição no arquivo

ftell()
→ informa a posição

rewind()
→ volta para o começo

fread()
→ arquivo → memória

fwrite()
→ memória → arquivo
```

---

## Ordenação

```c
qsort(e, qtd, sizeof(Endereco), compara);
```

```text
e
→ onde estão os elementos

qtd
→ quantos elementos

sizeof(Endereco)
→ tamanho de cada elemento

compara
→ regra usada para ordenar
```

Neste programa:

```text
regra = ordenar pelo CEP
```

---

# 16. Código completo comentado

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Cria um apelido para struct _Endereco.
typedef struct _Endereco Endereco;


// Define o formato de um registro.
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


// Função usada pelo qsort para comparar dois Enderecos.
int compara(const void *e1, const void *e2)
{
    // Converte os ponteiros genéricos para Endereco*
    // e compara os CEPs.
    return strncmp(
        ((Endereco*)e1)->cep,
        ((Endereco*)e2)->cep,
        8
    );
}


int main(int argc, char**argv)
{
    // f = arquivo original
    // saida = arquivo ordenado
    FILE *f, *saida;


    // Ponteiro para a área de memória
    // que armazenará os Enderecos.
    Endereco *e;


    long posicao, qtd;


    // Abre o arquivo original para leitura binária.
    f = fopen("cep.dat", "rb");


    // Vai para o final do arquivo.
    fseek(f, 0, SEEK_END);


    // Descobre o tamanho do arquivo em bytes.
    posicao = ftell(f);


    // Calcula quantos registros existem.
    qtd = posicao / sizeof(Endereco);


    // Reserva memória suficiente para todos os registros.
    e = (Endereco*) malloc(qtd * sizeof(Endereco));


    // Volta para o começo do arquivo.
    rewind(f);


    // Lê todos os registros para a memória.
    //
    // Se conseguiu ler exatamente qtd registros,
    // mostra uma mensagem de sucesso.
    if(fread(e, sizeof(Endereco), qtd, f) == qtd)
    {
        printf("Lido = OK\n");
    }


    // Ordena os registros na memória pelo CEP.
    qsort(e, qtd, sizeof(Endereco), compara);

    printf("Ordenado = OK\n");


    // Cria o arquivo que receberá os registros ordenados.
    saida = fopen("cep-ordenado.dat", "wb");


    // Grava os registros ordenados no novo arquivo.
    fwrite(e, sizeof(Endereco), qtd, saida);


    // Fecha o arquivo de saída.
    fclose(saida);


    // Libera a memória reservada pelo malloc.
    free(e);


    return 0;
}
```

---

## ⭐ A ideia mais importante

O programa trabalha em **três lugares**:

```text
┌─────────────────┐
│     cep.dat     │
│      ARQUIVO    │
└────────┬────────┘
         │
       fread
         ↓
┌─────────────────┐
│      e          │
│     MEMÓRIA     │
│                 │
│ Endereco 0      │
│ Endereco 1      │
│ Endereco 2      │
│ ...             │
└────────┬────────┘
         │
       qsort
         ↓
   registros
    ordenados
         │
       fwrite
         ↓
┌─────────────────┐
│cep-ordenado.dat │
│     ARQUIVO     │
└─────────────────┘
```

**`e` é o ponto central:** ele aponta para a área da memória onde todos os registros são carregados e onde o `qsort` trabalha.

