# Ordenação Externa e Intercalação de Arquivos em C

Este material explica como ordenar um arquivo binário de endereços usando o campo **CEP** como chave, através de **ordenação externa**.

A ideia central é dividir um arquivo grande em várias partes, ordenar cada parte na memória e depois intercalar os arquivos ordenados até restar um único arquivo final também ordenado.

```text
DIVIDIR
   ↓
ORDENAR
   ↓
INTERCALAR
   ↓
INTERCALAR NOVAMENTE
   ↓
ATÉ SOBRAR 1 ARQUIVO
```

---

## Índice

**Parte I — Conceitos**
1. [Objetivo](#1-objetivo)
2. [O que é ordenação externa](#2-o-que-é-ordenação-externa)
3. [A estrutura `Endereco`](#3-a-estrutura-endereco)

**Parte II — Dividindo e ordenando as partes**

4. [Descobrindo a quantidade de registros](#4-descobrindo-a-quantidade-de-registros)
5. [Dividindo o arquivo em partes](#5-dividindo-o-arquivo-em-partes)
6. [Distribuindo o resto](#6-distribuindo-o-resto)
7. [Reservando memória com `malloc`](#7-reservando-memória-com-malloc)
8. [A função `compara`](#8-a-função-compara)
9. [Ordenando cada parte com `qsort`](#9-ordenando-cada-parte-com-qsort)
10. [Criando os arquivos das partes](#10-criando-os-arquivos-das-partes)
11. [Por que usar `fclose`](#11-por-que-usar-fclose)

**Parte III — A intercalação**

12. [O que é intercalação](#12-o-que-é-intercalação)
13. [Por que existem `ea` e `eb`](#13-por-que-existem-ea-e-eb)
14. [`FILE *` e `fopen`](#14-file--e-fopen)
15. [`fread` e `fwrite`](#15-fread-e-fwrite)
16. [`feof()` e `EOF`](#16-feof-e-eof)
17. [Funcionamento passo a passo](#17-funcionamento-passo-a-passo)
18. [Código-base da função](#18-código-base-da-função)

**Parte IV — Orquestrando as intercalações**

19. [Por que o número de intercalações é `PARTES - 1`](#19-por-que-o-número-de-intercalações-é-partes---1)
20. [Entendendo o `for` da intercalação](#20-entendendo-o-for-da-intercalação)
21. [Por que usar `(PARTES - 1) * 2`](#21-por-que-usar-partes---1--2)
22. [Exemplo completo com 8 partes](#22-exemplo-completo-com-8-partes)
23. [Fluxo completo](#23-fluxo-completo)
24. [Resumo das principais ideias](#24-resumo-das-principais-ideias)

---

# Parte I — Conceitos

## 1. Objetivo

Pegar um arquivo original:

```text
cep.dat
```

e produzir um novo arquivo com todos os registros ordenados pelo CEP.

Como o arquivo pode ser grande demais para ser carregado inteiro na memória, ele é dividido em partes menores. Cada parte é ordenada individualmente e, em seguida, os arquivos ordenados são intercalados.

---

## 2. O que é ordenação externa

A ordenação externa é utilizada quando temos uma quantidade de dados grande demais para caber na memória RAM de uma vez.

```text
cep.dat
   |
   v
divide em partes
   |
   v
cep_0.dat
cep_1.dat
cep_2.dat
...
cep_7.dat
   |
   v
ordena cada parte (na memória)
   |
   v
intercala os arquivos
   |
   v
arquivos maiores e ordenados
   |
   v
intercala novamente
   |
   v
um único arquivo final
```

A ordenação acontece em duas etapas:

1. **Ordenação das partes** na memória (com `qsort`).
2. **Intercalação** dos arquivos já ordenados (sem carregar tudo na memória).

---

## 3. A estrutura `Endereco`

O arquivo utiliza uma estrutura para representar cada endereço:

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

A estrutura define como os bytes de cada registro são organizados:

```text
Endereco
┌──────────────────────┐
│ logradouro  72 bytes │
├──────────────────────┤
│ bairro      72 bytes │
├──────────────────────┤
│ cidade      72 bytes │
├──────────────────────┤
│ uf          72 bytes │
├──────────────────────┤
│ sigla        2 bytes │
├──────────────────────┤
│ cep          8 bytes │
├──────────────────────┤
│ lixo         2 bytes │
└──────────────────────┘
```

O `fread` não precisa saber o significado de `logradouro`, `bairro` ou `cep` — ele apenas copia os bytes do arquivo para dentro de uma variável `Endereco`. A organização já é definida pela `struct`.

O campo **`cep` é a chave de ordenação**.

---

# Parte II — Dividindo e ordenando as partes

## 4. Descobrindo a quantidade de registros

Primeiro, o arquivo é aberto em modo binário:

```c
FILE *cep;

cep = fopen("cep.dat", "rb");
```

Depois vamos até o final do arquivo:

```c
fseek(cep, 0, SEEK_END);
```

A função `ftell()` informa a posição atual em bytes. Como estamos no final, essa posição é o tamanho total do arquivo:

```c
long tamanho = ftell(cep);
```

Para descobrir quantos registros existem:

```c
long quantidade = tamanho / sizeof(Endereco);
```

Isso funciona porque:

```text
 tamanho do arquivo
-------------------- = quantidade de registros
tamanho de 1 registro
```

---

## 5. Dividindo o arquivo em partes

Supondo:

```c
#define PARTES 8
```

Temos:

```c
long divisao = quantidade / PARTES;
long resto   = quantidade % PARTES;
```

- `divisao` → quantidade básica de registros de cada parte
- `resto` → registros que sobraram depois da divisão

Por exemplo, com 100 registros:

```text
100 / 8 = 12   → divisao = 12
100 % 8 = 4    → resto   = 4
```

---

## 6. Distribuindo o resto

O resto é distribuído entre as primeiras partes, uma unidade em cada:

```text
Parte 0 → 13
Parte 1 → 13
Parte 2 → 13
Parte 3 → 13
Parte 4 → 12
Parte 5 → 12
Parte 6 → 12
Parte 7 → 12
```

No código:

```c
long quantidadeParte = divisao;

if(i < resto)
{
    quantidadeParte++;
}
```

Enquanto `i` for menor que `resto`, a parte recebe um registro a mais.

---

## 7. Reservando memória com `malloc`

Precisamos de memória para armazenar temporariamente uma parte dos registros.

```c
Endereco *e;
```

Aqui temos apenas um ponteiro. A memória é reservada com:

```c
e = (Endereco*) malloc((divisao + 1) * sizeof(Endereco));
```

O `+1` existe por causa do resto: se `divisao = 12`, a maior parte poderá ter **13** registros. Então precisamos de espaço para pelo menos `divisao + 1` registros.

---

## 8. A função `compara`

A comparação entre dois registros usa o CEP:

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

### Por que `const void *`?

Porque essa função é usada pelo `qsort`, que é **genérica** — ela funciona com qualquer tipo de dado. Por isso recebe `void *`, um ponteiro que pode apontar para qualquer tipo.

Como sabemos que os dados são `Endereco`, fazemos o *casting*:

```c
(Endereco*)e1
```

que significa: *"trate esse endereço como um ponteiro para `Endereco`"*. Depois:

```c
((Endereco*)e1)->cep
```

acessa o campo `cep`.

O retorno segue a convenção do `strncmp`:

```text
< 0  → e1 vem antes de e2
= 0  → CEPs iguais
> 0  → e1 vem depois de e2
```

Essa mesma função é reaproveitada na intercalação.

---

## 9. Ordenando cada parte com `qsort`

Depois de ler uma parte do arquivo:

```c
fread(e, sizeof(Endereco), quantidadeParte, cep);
```

os registros são ordenados na memória:

```c
qsort(e, quantidadeParte, sizeof(Endereco), compara);
```

Assim o `qsort()` organiza os registros em ordem crescente de CEP.

---

## 10. Criando os arquivos das partes

Para criar nomes diferentes para cada parte:

```c
sprintf(nome, "cep_%d.dat", i);
```

Por exemplo:

```text
i = 0 → cep_0.dat
i = 1 → cep_1.dat
i = 2 → cep_2.dat
```

Depois o arquivo é aberto, gravado e fechado:

```c
FILE *parte = fopen(nome, "wb");

fwrite(e, sizeof(Endereco), quantidadeParte, parte);

fclose(parte);
```

---

## 11. Por que usar `fclose`

Sempre que abrimos um arquivo com `fopen()`, devemos fechá-lo quando terminarmos:

```text
fopen()  → abre
fwrite() → escreve
fclose() → fecha
```

No caso das partes isso é especialmente importante, porque esses arquivos serão **abertos novamente** pela função de intercalação. Fechar garante que tudo que estava no buffer foi realmente gravado em disco.

---

# Parte III — A intercalação

## 12. O que é intercalação

Intercalação (*merge*) é o processo de juntar **dois arquivos que já estão ordenados** em um terceiro arquivo também ordenado.

```text
Arquivo A: 01000 03000 05000 07000
Arquivo B: 02000 04000 06000 08000

Saída:     01000 02000 03000 04000 05000 06000 07000 08000
```

Aplicado às partes:

```text
cep_0.dat + cep_1.dat → cep_8.dat
cep_2.dat + cep_3.dat → cep_9.dat
...
```

O programa **não precisa carregar os dois arquivos inteiros na memória**. Ele mantém apenas um registro atual de cada arquivo, compara os dois e escreve o menor.

```text
             Arquivo A
                 ↓
                ea
                 │
                 │ compara
                 ↓
              menor CEP
                 ↑
                 │
                eb
                 ↑
             Arquivo B
```

Depois de escrever, o programa lê o próximo registro **somente do arquivo que forneceu o menor registro**.

---

## 13. Por que existem `ea` e `eb`

Na função de intercalação usamos:

```c
Endereco ea, eb;
```

São duas variáveis temporárias, cada uma guardando **um registro atual** de um dos arquivos:

```text
Arquivo A                    Arquivo B
    │                            │
    │ fread                      │ fread
    ↓                            ↓
   ea                           eb
    │                            │
    └────────── compara ─────────┘
```

Não precisamos guardar todos os registros na memória. Só precisamos saber qual é o registro atual de `A` e qual é o registro atual de `B`.

---

## 14. `FILE *` e `fopen`

Para trabalhar com arquivos em C utilizamos:

```c
FILE *a, *b, *saida;
```

Essas variáveis representam os arquivos **depois** de abertos:

```text
a     → arquivo A aberto
b     → arquivo B aberto
saida → arquivo de saída aberto
```

A função recebe os nomes dos arquivos e os abre:

```c
void IntercalaArquivos(char *arqA, char *arqB, char *arqSaida)
{
    FILE *a, *b, *saida;

    a     = fopen(arqA, "rb");
    b     = fopen(arqB, "rb");
    saida = fopen(arqSaida, "wb");

    ...
}
```

Por exemplo, se chamarmos:

```c
IntercalaArquivos("cep_0.dat", "cep_1.dat", "cep_8.dat");
```

então:

```text
arqA     → "cep_0.dat"   (leitura)
arqB     → "cep_1.dat"   (leitura)
arqSaida → "cep_8.dat"   (escrita)
```

### Modos utilizados

```text
"rb" → read binary  → leitura binária
"wb" → write binary → escrita binária
```

---

## 15. `fread` e `fwrite`

### Por que `fread` não recebe `"arquivo.dat"`?

Porque o `fread` **não abre arquivos**. O último argumento dele é um `FILE *`, ou seja, um arquivo já aberto:

```text
"cep_0.dat"
      ↓
    fopen()
      ↓
    FILE *a
      ↓
    fread()
```

Portanto isto está **errado**:

```c
fread(&ea, sizeof(Endereco), 1, "cep_0.dat");   /* errado */
```

### Os argumentos do `fread`

```c
fread(&ea, sizeof(Endereco), 1, a);
```

```text
fread(
    &ea,              → onde colocar
    sizeof(Endereco), → tamanho de cada registro
    1,                → quantidade de registros
    a                 → de qual arquivo ler
)
```

O `&` em `&ea` significa *"endereço de `ea`"*. Estamos dizendo ao `fread`: *"coloque os bytes que você ler no endereço de memória de `ea`"*.

Sobre o `sizeof`: também poderíamos escrever `sizeof(ea)`, já que `ea` é uma variável do tipo `Endereco`.

### `fwrite`

Depois de descobrir qual registro tem o menor CEP:

```c
fwrite(&ea, sizeof(Endereco), 1, saida);
```

Ou seja: *pegue o registro `ea` e escreva-o no arquivo de saída*.

As direções são opostas:

```text
fread  → arquivo → memória
fwrite → memória → arquivo
```

---

## 16. `feof()` e `EOF`

Como estamos trabalhando com **dois arquivos**, precisamos saber quando cada um chegou ao fim.

```c
while(!feof(a) && !feof(b))
```

significa: *continue enquanto os dois arquivos ainda não tiverem chegado ao fim.*

```text
!feof(a) → A ainda não chegou ao fim
!feof(b) → B ainda não chegou ao fim
&&       → E
```

### Diferença entre `EOF` e `feof()`

`EOF` é um **valor especial** retornado por algumas funções de leitura:

```c
int c = fgetc(a);

if(c == EOF)
{
    ...
}
```

`feof(a)` é uma **função** que verifica o indicador de fim de arquivo:

```text
EOF      → valor especial
feof(a)  → função que verifica o estado de fim do arquivo a
```

---

## 17. Funcionamento passo a passo

Imagine:

```text
A: 100 300 500 700
B: 200 400 600 800
```

Leitura inicial:

```text
ea = 100
eb = 200
```

Compara `100 < 200` → escreve `100` e avança **apenas A**:

```text
ea = 300
eb = 200
```

Compara `200 < 300` → escreve `200` e avança **apenas B**:

```text
ea = 300
eb = 400
```

E continua até um dos arquivos acabar. Os registros restantes do outro arquivo são copiados direto para a saída.

Resultado:

```text
100 200 300 400 500 600 700 800
```

---

## 18. Código-base da função

```c
void IntercalaArquivos(char *arqA, char *arqB, char *arqSaida)
{
    FILE *a, *b, *saida;

    Endereco ea, eb;

    a     = fopen(arqA, "rb");
    b     = fopen(arqB, "rb");
    saida = fopen(arqSaida, "wb");

    fread(&ea, sizeof(Endereco), 1, a);
    fread(&eb, sizeof(Endereco), 1, b);

    while(!feof(a) && !feof(b))
    {
        if(compara(&ea, &eb) < 0)
        {
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, a);
        }
        else
        {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, b);
        }
    }

    while(!feof(a))
    {
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread(&ea, sizeof(Endereco), 1, a);
    }

    while(!feof(b))
    {
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread(&eb, sizeof(Endereco), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}
```

A linha:

```c
if(compara(&ea, &eb) < 0)
```

pergunta: *o CEP de `ea` vem antes do CEP de `eb`?* Se sim, escrevemos `ea`.

> **Observação:** esse é o modelo estudado em aula. Em código de produção, é mais seguro verificar diretamente o retorno de `fread()` (que devolve quantos registros foram lidos) em vez de depender de `feof()`, porque `feof()` só passa a ser verdadeiro **depois** de uma leitura falhar — o que pode causar a gravação repetida do último registro.

---

# Parte IV — Orquestrando as intercalações

## 19. Por que o número de intercalações é `PARTES - 1`

Cada intercalação transforma 2 arquivos em 1, ou seja, **reduz a quantidade total de arquivos em 1**.

Começando com 8 arquivos e querendo terminar com 1:

```text
8 → 7 → 6 → 5 → 4 → 3 → 2 → 1
```

Portanto são necessárias:

```text
PARTES - 1  =  8 - 1  =  7 intercalações
```

---

## 20. Entendendo o `for` da intercalação

O laço utilizado é:

```c
for(int i = 0; i < (PARTES - 1) * 2; i += 2)
{
    sprintf(nome1,  "cep_%d.dat", i);
    sprintf(nome2,  "cep_%d.dat", i + 1);
    sprintf(saida,  "cep_%d.dat", PARTES + i/2);

    IntercalaArquivos(nome1, nome2, saida);
}
```

A expressão se divide em três partes:

### `int i = 0`

O `i` é usado para escolher os dois arquivos de entrada:

```text
i = 0 → nome1 = cep_0.dat
        nome2 = cep_1.dat
```

### `i += 2`

Como consumimos **dois arquivos por vez**, o `i` avança de dois em dois:

```text
0, 2, 4, 6, 8, 10, 12
```

Primeira rodada (partes originais):

```text
i = 0 → cep_0 + cep_1
i = 2 → cep_2 + cep_3
i = 4 → cep_4 + cep_5
i = 6 → cep_6 + cep_7
```

Depois o laço continua usando os arquivos que acabaram de ser criados:

```text
i = 8  → cep_8  + cep_9
i = 10 → cep_10 + cep_11
i = 12 → cep_12 + cep_13
```

### `i < (PARTES - 1) * 2`

Explicado a seguir.

---

## 21. Por que usar `(PARTES - 1) * 2`

Esta é a parte mais importante do laço.

`PARTES - 1` é a quantidade de intercalações necessárias:

```text
8 - 1 = 7
```

Mas como o `i` anda de 2 em 2, cada intercalação consome **duas unidades** de `i`. Por isso multiplicamos por 2:

```text
(8 - 1) * 2  =  7 * 2  =  14
```

O `for` fica:

```c
for(int i = 0; i < 14; i += 2)
```

Os valores de `i` serão:

```text
0, 2, 4, 6, 8, 10, 12
```

São exatamente 7 iterações. Quando `i` vira 14, a condição `14 < 14` é falsa e o laço termina.

> **Atenção:** se você guardar o número de intercalações numa variável, escreva a condição de forma coerente. Com `quantidadeIntercala = PARTES - 1`, a condição correta é `i < quantidadeIntercala * 2` — e **não** `i < (quantidadeIntercala - 1) * 2`, que faria uma intercalação a menos e deixaria dois arquivos no final.

---

## 22. Exemplo completo com 8 partes

Inicialmente:

```text
cep_0.dat  cep_1.dat  cep_2.dat  cep_3.dat
cep_4.dat  cep_5.dat  cep_6.dat  cep_7.dat
```

**Primeira etapa** (`i = 0, 2, 4, 6`):

```text
cep_0 + cep_1 → cep_8
cep_2 + cep_3 → cep_9
cep_4 + cep_5 → cep_10
cep_6 + cep_7 → cep_11
```

**Segunda etapa** (`i = 8, 10`):

```text
cep_8  + cep_9  → cep_12
cep_10 + cep_11 → cep_13
```

**Última etapa** (`i = 12`):

```text
cep_12 + cep_13 → cep_14
```

Resultado final:

```text
cep_14.dat
```

Esse arquivo contém todos os registros do `cep.dat` ordenados por CEP.

---

## 23. Fluxo completo

```text
                    cep.dat
                       |
                       v
              Descobre quantidade
                       |
                       v
                Divide em PARTES
                       |
                       v
          +------------+------------+
          |            |            |
          v            v            v
       Parte 0      Parte 1      Parte 2 ...
          |            |            |
          v            v            v
       qsort()      qsort()      qsort()
          |            |            |
          v            v            v
     cep_0.dat    cep_1.dat    cep_2.dat ...
          \            /
           \          /
            v        v
             intercala
                 |
                 v
               cep_8
                 |
                 v
             intercala
                 |
                 v
              cep_12
                 |
                 v
             intercala
                 |
                 v
              cep_14
```

E, dentro de cada intercalação:

```text
        arquivo A             arquivo B
            ↓                     ↓
          fread                 fread
            ↓                     ↓
           ea                    eb
             \                   /
              \── compara ──────/
                     ↓
                 menor CEP
                     ↓
                  fwrite
                     ↓
              arquivo saída
```

---

## 24. Resumo das principais ideias

### Funções e tipos

```text
fopen()     → abre o arquivo
FILE *      → representa o arquivo aberto
Endereco    → representa um registro
fread()     → arquivo → memória
fwrite()    → memória → arquivo
feof()      → verifica o fim do arquivo
fclose()    → fecha o arquivo
compara()   → compara os CEPs
qsort()     → ordena uma parte na memória
IntercalaArquivos() → junta dois arquivos ordenados em um terceiro
```

### Quantidade de registros

```c
quantidade = tamanho / sizeof(Endereco);
```

### Divisão em partes

```c
divisao = quantidade / PARTES;
resto   = quantidade % PARTES;
```

### Distribuição do resto

```c
long quantidadeParte = divisao;

if(i < resto)
{
    quantidadeParte++;
}
```

### Ordenação de cada parte

```c
qsort(e, quantidadeParte, sizeof(Endereco), compara);
```

### Nome dos arquivos

```c
sprintf(nome, "cep_%d.dat", i);
```

### Número de intercalações

```text
PARTES - 1
```

### Laço da intercalação

```c
for(int i = 0; i < (PARTES - 1) * 2; i += 2)
```

O `-1` representa a quantidade de intercalações necessárias; o `*2` existe porque `i` avança de dois em dois.

---

A intercalação permite trabalhar com arquivos grandes sem precisar carregar todos os registros na memória ao mesmo tempo — essa é a essência da ordenação externa.
