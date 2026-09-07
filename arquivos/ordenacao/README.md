# Ordenação e Índice de Arquivos com `qsort` — C

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
14. [Índice de CEP](#14-índice-de-cep)
15. [`Endereco e` no índice](#15-endereco-e-no-índice)
16. [`IndiceCep *indice`](#16-indicecep-indice)
17. [Criando o índice](#17-criando-o-índice)
18. [Ordenando o índice](#18-ordenando-o-índice)
19. [Busca binária no índice](#19-busca-binária-no-índice)
20. [Usando a posição encontrada](#20-usando-a-posição-encontrada)
21. [Fluxo completo do índice](#21-fluxo-completo-do-índice)
22. [Resumo dos conceitos](#22-resumo-dos-conceitos)
23. [Código completo comentado — ordenação](#23-código-completo-comentado--ordenação)
24. [Código completo comentado — índice](#24-código-completo-comentado--índice)

---

# 1. Objetivo do programa

O programa de ordenação:

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

Ela possui espaço para **um único `Endereco`**.

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

## Importante

`Endereco e` e `Endereco *e` não significam a mesma coisa.

```text
Endereco e
→ uma variável que contém 1 Endereco

Endereco *e
→ uma variável que contém um endereço
  que aponta para um ou mais Enderecos
```

No programa de ordenação usamos:

```c
Endereco *e;
```

porque queremos guardar **todos os registros na memória ao mesmo tempo**.

No programa de índice usamos:

```c
Endereco e;
```

porque queremos ler **um registro por vez**.

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
fseek  → vai para o final

ftell  → descobre o tamanho

rewind → volta para o começo

fread  → lê os registros
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

## `e`

Onde os dados serão colocados.

Como `e` é um ponteiro, ele contém o endereço da memória reservada pelo `malloc`.

## `sizeof(Endereco)`

Tamanho de **um** `Endereco`.

O `fread` precisa saber isso para saber onde termina um registro e começa o próximo.

## `qtd`

Quantidade de `Enderecos` que queremos ler.

## `f`

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

# 14. Índice de CEP

Agora temos um segundo programa/tarefa:

> Criar um índice para o arquivo `cep.dat`.

Um índice funciona como um **atalho para encontrar um registro**.

Imagine que o arquivo seja:

```text
cep.dat

posição 0 → 22222222
posição 1 → 11111111
posição 2 → 55555555
```

Podemos criar um índice:

```text
CEP        posição
22222222 → 0
11111111 → 1
55555555 → 2
```

Esse índice guarda apenas as informações necessárias para localizar cada registro:

```text
CEP → posição no arquivo
```

---

# 15. `Endereco e` no índice

No programa do índice usamos:

```c
Endereco e;
```

Isso significa que temos espaço para **um único `Endereco`**.

Isso pode parecer estranho porque o arquivo possui muitos registros.

Mas não precisamos guardar todos os `Endereco` na memória.

Queremos apenas:

```text
ler um Endereco
      ↓
pegar seu CEP
      ↓
guardar o CEP no índice
      ↓
ler o próximo Endereco
      ↓
repetir
```

Então a mesma variável `e` é reutilizada.

Exemplo:

```text
1ª leitura:

arquivo → Endereco 0 → e


2ª leitura:

arquivo → Endereco 1 → e


3ª leitura:

arquivo → Endereco 2 → e
```

O conteúdo anterior de `e` é substituído pelo próximo registro.

Por isso não precisamos de `malloc` para `Endereco`.

---

# 16. `IndiceCep *indice`

Criamos uma nova estrutura para representar uma entrada do índice:

```c
struct indiceCep
{
    char cep[8];
    long posicao;
};

typedef struct indiceCep IndiceCep;
```

Cada `IndiceCep` possui:

```text
IndiceCep

├── cep
└── posicao
```

Agora precisamos guardar **vários `IndiceCep` ao mesmo tempo**.

Por isso usamos:

```c
IndiceCep *indice;
```

E:

```c
indice = malloc(qtd * sizeof(IndiceCep));
```

Agora temos espaço para `qtd` entradas:

```text
indice
  ↓
┌────────────────────────┐
│ indice[0]              │
├────────────────────────┤
│ indice[1]              │
├────────────────────────┤
│ indice[2]              │
├────────────────────────┤
│ ...                    │
├────────────────────────┤
│ indice[qtd - 1]        │
└────────────────────────┘
```

### Comparação importante

```text
Endereco e;

→ espaço para 1 Endereco
→ usado temporariamente
→ não precisa de malloc
```

```text
IndiceCep *indice;

→ espaço para vários IndiceCep
→ precisa armazenar todos os índices
→ usa malloc
```

---

# 17. Criando o índice

Depois de calcular `qtd`, fazemos:

```c
IndiceCep *indice;

indice = malloc(qtd * sizeof(IndiceCep));
```

Depois voltamos ao começo do arquivo:

```c
rewind(f);
```

E começamos a percorrer todos os registros:

```c
for(i = 0; i < qtd; i++)
{
    fread(&e, sizeof(Endereco), 1, f);

    strncpy(indice[i].cep, e.cep, 8);

    indice[i].posicao = i;
}
```

Vamos entender linha por linha.

---

## `for`

```c
for(i = 0; i < qtd; i++)
```

Percorre todas as posições.

Se:

```text
qtd = 4
```

temos:

```text
i = 0
i = 1
i = 2
i = 3
```

---

## `fread`

```c
fread(&e, sizeof(Endereco), 1, f);
```

Significa:

> "Leia 1 `Endereco` do arquivo e coloque dentro de `e`."

O `&e` é usado porque `fread` precisa do **endereço da variável onde vai colocar os dados**.

O `1` significa:

> leia apenas um `Endereco` nesta chamada.

O próximo `fread` vai continuar de onde o anterior parou.

Isso acontece porque o arquivo possui uma **posição atual de leitura**, que avança automaticamente depois de cada leitura.

---

## `strncpy`

```c
strncpy(indice[i].cep, e.cep, 8);
```

Pega o CEP do `Endereco` que acabamos de ler:

```c
e.cep
```

e copia para o índice:

```c
indice[i].cep
```

Exemplo:

```text
e.cep
  ↓
"22222222"

        ↓ copia

indice[0].cep
  ↓
"22222222"
```

---

## `indice[i].posicao = i`

```c
indice[i].posicao = i;
```

Guarda a posição daquele registro no arquivo original.

Por exemplo:

```text
i = 0

indice[0].cep = "22222222"
indice[0].posicao = 0
```

Depois:

```text
i = 1

indice[1].cep = "11111111"
indice[1].posicao = 1
```

E assim por diante.

No final:

```text
ÍNDICE

┌──────────┬─────────┐
│ CEP      │ posição │
├──────────┼─────────┤
│ 22222222 │    0    │
│ 11111111 │    1    │
│ 55555555 │    2    │
└──────────┴─────────┘
```

A posição é a posição **original no `cep.dat`**.

---

# 18. Ordenando o índice

Depois de criar o índice:

```c
qsort(indice, qtd, sizeof(IndiceCep), compara);
```

Agora estamos ordenando **`IndiceCep`**, e não `Endereco`.

Por isso:

```c
sizeof(IndiceCep)
```

e não:

```c
sizeof(Endereco)
```

A função `compara` também precisa comparar `IndiceCep`:

```c
int compara(const void *a, const void *b)
{
    return strncmp(
        ((IndiceCep*)a)->cep,
        ((IndiceCep*)b)->cep,
        8
    );
}
```

O `qsort` recebe:

```text
indice
   ↓
onde começa o array

qtd
   ↓
quantos elementos

sizeof(IndiceCep)
   ↓
tamanho de cada elemento

compara
   ↓
como decidir a ordem
```

---

## O resultado

Antes:

```text
CEP        posição
22222222 → 0
11111111 → 1
55555555 → 2
```

Depois do `qsort`:

```text
CEP        posição
11111111 → 1
22222222 → 0
55555555 → 2
```

Observe:

**A posição não foi alterada.**

Só mudamos a ordem das entradas do índice.

A entrada:

```text
22222222 → 0
```

continua dizendo:

> "O CEP 22222222 está na posição 0 do `cep.dat`."

---

# 19. Busca binária no índice

Depois de ordenar o índice, podemos procurar um CEP usando busca binária.

Começamos:

```c
long inicio = 0;
long fim = qtd - 1;
```

Se temos 5 entradas:

```text
posição:  0   1   2   3   4
```

então:

```text
inicio = 0
fim = 4
```

---

## `while`

```c
while(inicio <= fim)
```

Continua procurando enquanto ainda existir uma parte do índice para pesquisar.

---

## `meio`

```c
long meio = (inicio + fim) / 2;
```

Calcula a posição central.

Exemplo:

```text
inicio = 0
fim = 4

meio = (0 + 4) / 2

meio = 2
```

---

## Comparando o CEP

```c
int resultado = strncmp(
    argv[1],
    indice[meio].cep,
    8
);
```

`argv[1]` é o CEP digitado pelo usuário.

Por exemplo:

```text
./programa 33333333
```

Então:

```text
argv[1] = "33333333"
```

E:

```c
indice[meio].cep
```

é o CEP que está no meio do índice.

---

## Se `resultado == 0`

```c
if(resultado == 0)
```

Os CEPs são iguais.

Encontramos o CEP.

---

## Se `resultado > 0`

```c
else if(resultado > 0)
{
    inicio = meio + 1;
}
```

O CEP procurado é maior que o CEP do meio.

Então procuramos na metade da direita.

---

## Se `resultado < 0`

```c
else
{
    fim = meio - 1;
}
```

O CEP procurado é menor que o CEP do meio.

Então procuramos na metade da esquerda.

---

# 20. Usando a posição encontrada

Quando encontramos:

```c
if(resultado == 0)
```

pegamos:

```c
long posicao = indice[meio].posicao;
```

Por exemplo:

```text
indice[meio]:

CEP       = 33333333
posicao   = 7
```

Então:

```c
posicao = 7;
```

Isso significa:

> "O registro que eu quero está na posição 7 do `cep.dat`."

Agora usamos:

```c
fseek(f, posicao * sizeof(Endereco), SEEK_SET);
```

O `fseek` trabalha com **bytes**, e não com número de registros.

Se:

```text
sizeof(Endereco) = 300
posicao = 7
```

então:

```text
7 × 300 = 2100 bytes
```

O `fseek` vai para o byte 2100:

```text
cep.dat

registro 0
registro 1
registro 2
...
registro 7 ← posição encontrada
registro 8
...
```

Depois:

```c
fread(&e, sizeof(Endereco), 1, f);
```

lê esse `Endereco` para a variável temporária `e`.

Agora podemos mostrar seus dados:

```c
printf(
    "%.72s\n"
    "%.72s\n"
    "%.72s\n"
    "%.72s\n"
    "%.2s\n"
    "%.8s\n",

    e.logradouro,
    e.bairro,
    e.cidade,
    e.uf,
    e.sigla,
    e.cep
);
```

---

# 21. Fluxo completo do índice

```text
                         cep.dat

                            │

                            ↓

                          fopen

                            │

                            ↓

                    descobre qtd

                            │

                            ↓

                         malloc

                            │

                            ↓

                 cria espaço para
                  vários IndiceCep

                            │

                            ↓

                         rewind

                            │

                            ↓

                     começa o for

                            │

                            ↓

                 lê UM Endereco

                            │

                            ↓

                       Endereco e

                            │

                            ↓

                      pega e.cep

                            │

                            ↓

                  guarda no índice

                            │

                            ↓

                  guarda posição i

                            │

                            ↓

                    lê próximo

                            │

                            ↓

                    repete até qtd

                            │

                            ↓

                          qsort

                            │

                            ↓

                  índice ordenado
                       pelo CEP

                            │

                            ↓

                    busca binária

                            │

                            ↓

                   encontra posição

                            │

                            ↓

                         fseek

                            │

                            ↓

                 vai direto ao registro

                            │

                            ↓

                         fread

                            │

                            ↓

                    Endereco e

                            │

                            ↓

                         printf
```

---

# 22. Resumo dos conceitos

## Ponteiros

```text
Endereco e

→ uma struct

Endereco *e

→ ponteiro para uma struct

IndiceCep *indice

→ ponteiro para uma área com vários IndiceCep

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

Para `Endereco`:

```c
qsort(e, qtd, sizeof(Endereco), compara);
```

Para o índice:

```c
qsort(indice, qtd, sizeof(IndiceCep), compara);
```

O tipo passado para `sizeof` deve ser o tipo dos elementos que estão sendo ordenados.

---

## Índice

```text
IndiceCep

├── cep
└── posicao
```

O índice funciona como:

```text
CEP → posição no arquivo
```

Exemplo:

```text
11111111 → 1
22222222 → 0
55555555 → 2
```

A busca binária encontra o CEP rapidamente no índice.

Depois a `posicao` encontrada é usada pelo `fseek` para acessar diretamente o registro correspondente no `cep.dat`.

---

# 23. Código completo comentado — ordenação

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


int main(int argc, char **argv)
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

# 24. Código completo comentado — índice

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Cria um apelido para struct _Endereco.
typedef struct _Endereco Endereco;


// Define o formato de um registro do arquivo.
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


// Define uma entrada do índice.
//
// Cada entrada relaciona:
// CEP → posição no arquivo
struct indiceCep
{
    char cep[8];
    long posicao;
};


typedef struct indiceCep IndiceCep;


// Compara duas entradas do índice pelo CEP.
int compara(const void *a, const void *b)
{
    return strncmp(
        ((IndiceCep*)a)->cep,
        ((IndiceCep*)b)->cep,
        8
    );
}


int main(int argc, char **argv)
{
    FILE *f;

    // Guarda UM Endereco por vez.
    Endereco e;

    // Ponteiro para o espaço que armazenará
    // TODOS os IndiceCep.
    IndiceCep *indice;

    long tamanhoBytes;
    long qtd;
    long i;


    // Verifica se o usuário informou o CEP.
    if(argc != 2)
    {
        fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
        return 1;
    }


    // Abre o arquivo original.
    f = fopen("cep.dat", "rb");

    if(f == NULL)
    {
        fprintf(stderr, "Erro ao abrir cep.dat\n");
        return 1;
    }


    // Vai para o final para descobrir o tamanho.
    fseek(f, 0, SEEK_END);

    tamanhoBytes = ftell(f);


    // Calcula quantos Enderecos existem.
    qtd = tamanhoBytes / sizeof(Endereco);


    // Reserva memória para TODAS as entradas do índice.
    indice = malloc(qtd * sizeof(IndiceCep));

    if(indice == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria\n");

        fclose(f);

        return 1;
    }


    // Volta para o começo do arquivo.
    rewind(f);


    // Percorre todos os Enderecos do arquivo.
    for(i = 0; i < qtd; i++)
    {
        // Lê UM Endereco para a variável temporária e.
        fread(&e, sizeof(Endereco), 1, f);


        // Copia o CEP de e para a entrada atual do índice.
        strncpy(indice[i].cep, e.cep, 8);


        // Guarda a posição original do registro.
        indice[i].posicao = i;
    }


    // Ordena o índice pelo CEP.
    qsort(
        indice,
        qtd,
        sizeof(IndiceCep),
        compara
    );


    // Define os limites da busca binária.
    long inicio = 0;
    long fim = qtd - 1;


    // Continua enquanto houver elementos para procurar.
    while(inicio <= fim)
    {
        // Calcula o elemento do meio.
        long meio = (inicio + fim) / 2;


        // Compara o CEP procurado com o CEP do meio.
        int resultado = strncmp(
            argv[1],
            indice[meio].cep,
            8
        );


        // CEP encontrado.
        if(resultado == 0)
        {
            // Recupera a posição original no cep.dat.
            long posicao = indice[meio].posicao;


            // Vai diretamente para esse registro.
            fseek(
                f,
                posicao * sizeof(Endereco),
                SEEK_SET
            );


            // Lê o Endereco encontrado para e.
            fread(
                &e,
                sizeof(Endereco),
                1,
                f
            );


            // Mostra os dados do Endereco.
            printf(
                "%.72s\n"
                "%.72s\n"
                "%.72s\n"
                "%.72s\n"
                "%.2s\n"
                "%.8s\n",

                e.logradouro,
                e.bairro,
                e.cidade,
                e.uf,
                e.sigla,
                e.cep
            );


            // Já encontramos o registro.
            break;
        }


        // CEP procurado é maior que o CEP do meio.
        else if(resultado > 0)
        {
            // Procura na metade da direita.
            inicio = meio + 1;
        }


        // CEP procurado é menor que o CEP do meio.
        else
        {
            // Procura na metade da esquerda.
            fim = meio - 1;
        }
    }


    // Libera a memória do índice.
    free(indice);


    // Fecha o arquivo.
    fclose(f);


    return 0;
}
```

---

## ⭐ A ideia mais importante

O programa do índice trabalha com **dois tipos de informação diferentes**:

```text
┌──────────────────────────────┐
│          cep.dat             │
│                              │
│  vários Enderecos no arquivo │
└──────────────┬───────────────┘
               │
               │ lê UM por vez
               ↓
        ┌─────────────┐
        │ Endereco e  │
        │             │
        │ temporário  │
        └──────┬──────┘
               │
               │ pega CEP
               ↓
        ┌──────────────────────┐
        │   IndiceCep *indice  │
        │                      │
        │ CEP → posição        │
        │ CEP → posição        │
        │ CEP → posição        │
        │ ...                  │
        └──────────────────────┘
               │
               │ qsort
               ↓
        índice ordenado
               │
               │ busca binária
               ↓
        encontra posição
               │
               ↓
        fseek no cep.dat
               │
               ↓
        lê o Endereco
```

**A diferença fundamental é:**

```text
Endereco e
→ UM registro temporário
→ lê, usa e substitui

IndiceCep *indice
→ VÁRIAS entradas do índice
→ ficam todas na memória
→ por isso usa malloc
```

E o índice existe para transformar:

```text
"Quero o CEP 33333333"
```

em:

```text
"Ele está na posição 7 do cep.dat"
```

Depois o `fseek` usa essa posição para chegar diretamente ao registro.
