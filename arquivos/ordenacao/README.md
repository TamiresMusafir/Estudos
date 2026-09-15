# Ordenação e Indexação de Arquivos Binários em C

Este material cobre as técnicas básicas para trabalhar com **arquivos binários de registros de tamanho fixo** em C:

- carregar um arquivo inteiro na memória e ordenar com `qsort`;
- construir um **índice** (chave → posição) para localizar registros sem varrer o arquivo;
- acessar um registro diretamente com `fseek`.

Os exemplos usam uma struct `Endereco` e o campo `cep` como chave, mas **tudo aqui vale para qualquer registro de tamanho fixo e qualquer campo usado como chave** — basta trocar o tipo e a função de comparação.

---

## Sumário

**Parte I — Fundamentos**
1. [As duas tarefas](#1-as-duas-tarefas)
2. [Registro de tamanho fixo](#2-registro-de-tamanho-fixo)
3. [`Tipo x;` x `Tipo *x;` — quando usar cada um](#3-tipo-x-x-tipo-x--quando-usar-cada-um)
4. [`.` x `->`](#4--x--)
5. [`&` e `*`](#5--e-)
6. [`malloc` e `free`](#6-malloc-e-free)

**Parte II — Navegando no arquivo**

7. [`fseek`, `ftell` e `rewind`](#7-fseek-ftell-e-rewind)
8. [`fread`](#8-fread)
9. [`fwrite`](#9-fwrite)

**Parte III — Ordenação**

10. [`qsort`](#10-qsort)
11. [A função de comparação](#11-a-função-de-comparação)
12. [De onde vêm os parâmetros da comparação](#12-de-onde-vêm-os-parâmetros-da-comparação)

**Parte IV — Índice**

13. [O que é um índice](#13-o-que-é-um-índice)
14. [A struct do índice](#14-a-struct-do-índice)
15. [Construindo o índice](#15-construindo-o-índice)
16. [Ordenando o índice](#16-ordenando-o-índice)
17. [Busca binária](#17-busca-binária)
18. [Acesso direto com `fseek`](#18-acesso-direto-com-fseek)
19. [Fluxo completo](#19-fluxo-completo)

**Parte V — Referência**

20. [Resumo dos conceitos](#20-resumo-dos-conceitos)
21. [Código comentado — ordenação](#21-código-comentado--ordenação)
22. [Código comentado — índice](#22-código-comentado--índice)
23. [A ideia mais importante](#23-a-ideia-mais-importante)

---

# Parte I — Fundamentos

## 1. As duas tarefas

### Ordenar o arquivo inteiro

```text
arquivo original
   ↓
fread()        carrega tudo na memória
   ↓
qsort()        organiza pela chave
   ↓
fwrite()       salva em um novo arquivo
```

> **`fread` carrega → `qsort` organiza → `fwrite` salva.**

O programa faz, em ordem:

1. Abre o arquivo original;
2. Descobre quantos registros existem;
3. Reserva memória suficiente para armazenar **todos** eles;
4. Lê todos os registros para a memória;
5. Ordena os registros pela chave usando `qsort`;
6. Cria o arquivo de saída;
7. Grava os registros ordenados nesse novo arquivo;
8. Libera a memória.

Exige memória para **todos** os registros ao mesmo tempo.

### Indexar o arquivo

```text
arquivo original
   ↓
lê UM registro por vez
   ↓
guarda (chave → posição) na memória
   ↓
qsort() no índice
   ↓
busca binária → fseek → lê só o registro desejado
```

Exige memória apenas para o **índice**, que é muito menor que o arquivo. O arquivo original não é alterado.

---

## 2. Registro de tamanho fixo

Um arquivo binário de registros fixos é apenas uma sequência de structs gravadas uma após a outra:

```text
[registro 0][registro 1][registro 2][registro 3]...
```

A struct define o formato de **um** registro:

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

O `typedef` permite escrever `Endereco` em vez de `struct _Endereco`.

Como todos os registros têm o mesmo tamanho, duas contas resolvem quase tudo:

```text
quantidade de registros = tamanho do arquivo / sizeof(Tipo)

byte do registro N      = N * sizeof(Tipo)
```

É exatamente isso que permite ordenar com `qsort` e pular direto para um registro com `fseek`.

---

## 3. `Tipo x;` x `Tipo *x;` — quando usar cada um

Esta é a decisão que mais confunde no começo. A regra prática é:

```text
Preciso de UM item por vez, que vai ser descartado/substituído?
    → variável normal:   Endereco e;

Preciso de VÁRIOS itens ao mesmo tempo, e a quantidade só é
conhecida em tempo de execução?
    → ponteiro + malloc: Endereco *e;
```

### `Endereco e;` — a struct de verdade

```c
Endereco e;
```

Aqui `e` **é** uma struct de verdade. Ela possui espaço para **um único** `Endereco`, já reservado pelo compilador.

```text
e
┌─────────────────────┐
│ logradouro          │
│ bairro               │
│ cidade               │
│ uf                   │
│ sigla                │
│ cep                  │
│ lixo                 │
└─────────────────────┘
```

Para acessar seus campos, usa-se ponto:

```c
e.cep
```

Use quando o dado é **temporário**: você lê, aproveita e sobrescreve com o próximo.

### `Endereco *e;` — um endereço

```c
Endereco *e;
```

Aqui `e` é um **ponteiro** — uma variável que guarda o endereço de memória onde existe um (ou vários) `Endereco`, e não o registro em si.

```text
e
│
│ guarda um endereço
↓
1000

┌─────────────────────┐
│ Endereco             │
│ cep = "20040000"     │
└─────────────────────┘
```

Por isso, para acessar um campo através do ponteiro, usa-se seta:

```c
e->cep
```

Sozinho, o ponteiro não aponta para lugar nenhum útil. Ele só serve depois que alguém lhe dá um endereço válido — normalmente o `malloc`:

```c
e = malloc(qtd * sizeof(Endereco));
```

Com vários registros no bloco, o acesso por índice também funciona:

```text
e
↓
1000
┌────────────┬────────────┬────────────┐
│ Endereco 0 │ Endereco 1 │ Endereco 2 │
└────────────┴────────────┴────────────┘
```

```c
e[3].cep      /* quarto registro do bloco */
```

### Importante: não são a mesma coisa

```text
Endereco e
→ uma variável que contém 1 Endereco

Endereco *e
→ uma variável que contém um endereço
  que aponta para um ou mais Enderecos
```

### Por que não usar um array fixo?

```c
Endereco e[1000];   /* e se o arquivo tiver 1.000.000 de registros? */
```

A quantidade de registros só é conhecida **depois** de abrir o arquivo e medir seu tamanho. Por isso `malloc`.

### Exemplo real: os dois juntos no programa do índice

O programa do índice usa **as duas formas ao mesmo tempo**, e cada uma pelo motivo certo:

```c
FILE *f;

Endereco e;              /* UM registro por vez → variável normal   */
IndiceCep *indice;       /* TODAS as entradas   → ponteiro + malloc */

f = fopen("cep.dat", "rb");

indice = malloc(qtd * sizeof(IndiceCep));

for(i = 0; i < qtd; i++)
{
    fread(&e, sizeof(Endereco), 1, f);   /* &e: e é struct → precisa do & */

    strncpy(indice[i].cep, e.cep, 8);    /* e.cep: ponto  → e é struct    */

    indice[i].posicao = i;               /* indice[i]: índice no bloco    */
}
```

O que acontece com `e` a cada volta do laço:

```text
1ª volta:  arquivo → registro 0 → e
2ª volta:  arquivo → registro 1 → e   (apaga o anterior)
3ª volta:  arquivo → registro 2 → e   (apaga o anterior)
```

`e` é reaproveitado porque o conteúdo antigo já não é mais necessário — o que interessa (a chave e a posição) já foi copiado para o índice. Uma única struct basta, e por isso `Endereco e` **não** precisa de `malloc`.

Já `indice` precisa manter **todas** as entradas vivas ao mesmo tempo, porque no final vamos ordená-las e fazer busca binária nelas. Por isso é ponteiro com `malloc`.

### O mesmo padrão em outro contexto: intercalação de arquivos

Numa intercalação de dois arquivos já ordenados, o mesmo padrão se repete: nenhum registro precisa ficar guardado, só o "atual" de cada arquivo.

```c
FILE *a, *b, *saida;
Endereco ea, eb;          /* um registro atual de cada arquivo */

a     = fopen(arqA, "rb");
b     = fopen(arqB, "rb");
saida = fopen(arqSaida, "wb");

fread(&ea, sizeof(Endereco), 1, a);
fread(&eb, sizeof(Endereco), 1, b);
```

Nenhum `malloc` aqui: `ea` e `eb` são structs normais, porque a cada comparação um deles é escrito na saída e imediatamente substituído pelo próximo registro do mesmo arquivo — exatamente o mesmo raciocínio do `Endereco e` do índice.

`FILE *a, *b, *saida` **são** ponteiros — mas não porque precisem de `malloc`: quem devolve o endereço da estrutura interna do arquivo é o `fopen`, não você. Por isso `FILE *` nunca leva `malloc`/`free`, só `fopen`/`fclose`.

### Resumo da decisão

```text
Endereco e;          → 1 registro, temporário, sem malloc, usa .  e &e
Endereco *e;         → N registros, com malloc,  usa ->  ou e[i]
FILE *f;             → ponteiro devolvido pelo fopen, nunca malloc/free
```

---

## 4. `.` x `->`

Regra para decorar:

```text
Tenho a struct        →  e.cep
Tenho um ponteiro     →  e->cep
```

Exemplo:

```c
Endereco e;
e.cep;          /* usamos . porque e é a própria struct */
```

```c
Endereco *e;
e->cep;         /* usamos -> porque e é um ponteiro      */
e[0].cep;       /* equivalente ao acima                  */
```

`e->cep` é apenas um atalho para `(*e).cep`.

---

## 5. `&` e `*`

### `&` — endereço de

O operador `&` significa: *pegue o endereço de uma variável.*

```c
Endereco e;
```

```text
e   → a própria struct
&e  → endereço da struct
```

Por isso, quando a variável é uma struct normal, o `fread` recebe `&e`: ele precisa saber **onde** colocar os bytes lidos.

```c
fread(&e, sizeof(Endereco), 1, f);
```

Quando a variável já é um ponteiro, o `&` não é usado — o valor dela já é um endereço:

```c
fread(e, sizeof(Endereco), qtd, f);
```

### `*` — acessar o conteúdo apontado

Se `e` é um ponteiro:

```c
Endereco *e;
```

então `*e` significa: *acesse o `Endereco` que está naquele endereço.*

### Resumo

```text
Endereco e
e   → struct
&e  → endereço da struct

Endereco *e
e   → endereço
*e  → struct naquele endereço
```

---

## 6. `malloc` e `free`

```c
e = malloc(qtd * sizeof(Endereco));
```

`malloc` serve para **reservar memória dinamicamente**. Não sabemos previamente quantos registros existem no arquivo — ele pode ter 1.000, 50.000 ou 1.000.000 de registros — por isso não fazemos um array fixo. Primeiro descobrimos a quantidade medindo o arquivo, depois reservamos exatamente o espaço necessário.

### O que o `malloc` retorna?

`malloc` reserva um bloco de memória e devolve o **endereço do início** desse bloco.

```text
malloc(...)
   ↓
 1000
```

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

Nesse momento, o espaço está reservado, mas ainda vazio — quem o preenche é o `fread`.

### O casting `(Endereco*)`

```c
e = (Endereco*) malloc(qtd * sizeof(Endereco));
```

Isso é um **casting**. O `malloc` retorna `void *`, um ponteiro genérico. O casting diz: *"trate esse endereço como um ponteiro para `Endereco`."*

Em C o casting é **opcional** — a conversão é automática:

```c
e = malloc(qtd * sizeof(Endereco));   /* também funciona */
```

### Verificar o retorno

`malloc` devolve `NULL` se não conseguir reservar a memória. Vale sempre checar:

```c
if(e == NULL)
{
    fprintf(stderr, "Erro ao alocar memoria\n");
    return 1;
}
```

### `free`

Toda memória de `malloc` deve ser devolvida no final:

```c
free(e);
```

Ciclo completo:

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

# Parte II — Navegando no arquivo

## 7. `fseek`, `ftell` e `rewind`

Todo arquivo aberto tem uma **posição atual de leitura/escrita**, que avança sozinha a cada operação.

### Descobrindo o tamanho

```c
fseek(f, 0, SEEK_END);

posicao = ftell(f);
```

**`fseek`** move a posição atual do arquivo para o final:

```text
[registro][registro][registro][registro]

                                      ↑
                                    posição
```

**`ftell`** informa a posição atual. Como estamos no final do arquivo, essa posição representa o tamanho do arquivo em bytes.

Daí:

```c
qtd = posicao / sizeof(Endereco);
```

### `rewind`

Depois de descobrir o tamanho, a posição do arquivo continua no final. Por isso:

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

Isso é necessário porque o próximo comando normalmente é `fread(...)`, e o `fread` começa a ler **da posição atual do arquivo**. Sem o `rewind`, ele não leria nada — já estaria no fim.

### `fseek` para acesso direto

`fseek` também serve para pular direto a um registro, não só para medir o arquivo. Os pontos de referência são:

```text
SEEK_SET → a partir do início
SEEK_CUR → a partir da posição atual
SEEK_END → a partir do final
```

O deslocamento é sempre em **bytes**, nunca em número de registros:

```c
fseek(f, posicao * sizeof(Endereco), SEEK_SET);
```

### Resumo

```text
fseek  → move a posição no arquivo (em bytes)
ftell  → descobre/informa a posição atual
rewind → volta para o começo
fread  → lê os registros
```

---

## 8. `fread`

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

**`e`** — onde os dados serão colocados. Se `e` for um ponteiro, ele já contém o endereço da memória reservada pelo `malloc`; se for uma struct normal, usa-se `&e`.

**`sizeof(Endereco)`** — tamanho de **um** registro. O `fread` precisa saber isso para saber onde termina um registro e começa o próximo.

**`qtd`** — quantidade de registros que se quer ler.

**`f`** — arquivo de onde os dados serão lidos.

Duas formas, conforme o destino:

```c
Endereco e;
fread(&e, sizeof(Endereco), 1, f);      /* 1 registro numa struct  */

Endereco *e = malloc(qtd * sizeof(Endereco));
fread(e, sizeof(Endereco), qtd, f);     /* qtd registros no bloco  */
```

### Exemplo

Se `sizeof(Endereco) = 300` e `qtd = 3`, então `fread(e, sizeof(Endereco), qtd, f)` significa:

```text
300 bytes → Endereco 0
300 bytes → Endereco 1
300 bytes → Endereco 2
```

### O que acontece na memória?

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

O `fread` copia o **registro inteiro**, não apenas o campo que interessa. E ele continua sempre da posição atual — por isso chamadas sucessivas leem registros consecutivos, sem precisar dizer explicitamente "leia o próximo".

### Retorno do `fread`

`fread` retorna quantos elementos conseguiu ler de fato. É a forma confiável de detectar fim de arquivo ou erro:

```c
if(fread(e, sizeof(Endereco), qtd, f) == qtd)
{
    printf("Lido = OK\n");
}
```

Ou seja: *"a quantidade de elementos que consegui ler é igual à quantidade que eu esperava?"*

---

## 9. `fwrite`

Depois que os registros estão prontos na memória (ordenados ou não), `fwrite` faz o caminho contrário do `fread`:

```c
fwrite(e, sizeof(Endereco), qtd, saida);
```

```text
fread   → arquivo → memória
fwrite  → memória → arquivo
```

Os parâmetros seguem o mesmo padrão:

```text
fwrite(
    de onde pegar,
    tamanho de cada elemento,
    quantidade,
    arquivo
);
```

Ou seja: *"pegue os `qtd` registros que estão na memória começando em `e` e grave no arquivo `saida`."*

---

# Parte III — Ordenação

## 10. `qsort`

```c
qsort(e, qtd, sizeof(Endereco), compara);
```

Os parâmetros são:

```text
qsort(
    onde estão os elementos,
    quantidade,
    tamanho de cada elemento,
    função de comparação
);
```

Ou seja: *"ordene os `qtd` elementos que começam em `e`, sabendo que cada um possui `sizeof(Endereco)` bytes, usando `compara` para decidir a ordem."*

O `qsort` funciona com **qualquer tipo**. O que muda de um uso para outro são apenas três coisas: o bloco, o `sizeof` e a função de comparação.

```c
qsort(e,      qtd, sizeof(Endereco),  comparaEndereco);
qsort(indice, qtd, sizeof(IndiceCep), comparaIndice);
```

> O tipo passado ao `sizeof` deve ser sempre o tipo dos elementos que estão sendo ordenados naquela chamada. Errar aqui corrompe os dados silenciosamente.

---

## 11. A função de comparação

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

A função recebe dois elementos — `e1`, o primeiro; `e2`, o segundo. Mas o `qsort` é genérico e trabalha com `void *`, por isso é preciso o casting:

```c
(Endereco*)e1
```

Isso significa: *"trate esse endereço como um ponteiro para `Endereco`."* Então:

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

Depois, `strncmp(..., ..., 8)` compara os 8 caracteres dos dois CEPs.

### O que `compara` retorna?

```text
resultado < 0
→ primeiro elemento vem antes

resultado = 0
→ elementos equivalentes

resultado > 0
→ primeiro elemento vem depois
```

`strncmp` já segue exatamente essa convenção, o que torna a comparação de campos `char[]` imediata. Para chaves numéricas, a lógica é a mesma, só que escrita manualmente:

```c
int comparaNumero(const void *a, const void *b)
{
    long x = ((Registro*)a)->valor;
    long y = ((Registro*)b)->valor;

    if(x < y) return -1;
    if(x > y) return  1;
    return 0;
}
```

Para ordem **decrescente**, basta inverter os operandos.

O `qsort` usa esse resultado para saber como organizar os registros.

---

## 12. De onde vêm os parâmetros da comparação

Não criamos `e1` e `e2` no `main`. Eles são **parâmetros da função `compara`**, e quem os preenche é o próprio `qsort`. Conceitualmente ele faz algo como:

```c
compara(&e[0], &e[1]);
compara(&e[2], &e[5]);
...
```

O `qsort` decide sozinho quais elementos precisa comparar; nós apenas fornecemos a função:

```c
qsort(e, qtd, sizeof(Endereco), compara);   /* entrega a função para o qsort */
compara();                                   /* executaria a função agora    */
```

Sem parênteses, o nome da função é apenas o endereço dela. Com parênteses, é uma chamada de fato. O `qsort` quer o endereço, para chamar quando precisar.

---

# Parte IV — Índice

## 13. O que é um índice

Um índice funciona como um **atalho para encontrar um registro**, sem precisar varrer o arquivo inteiro.

Imagine que o arquivo original (não ordenado) seja:

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

Esse índice guarda apenas as informações necessárias para localizar cada registro: **chave → posição no arquivo**. Vantagens:

- ocupa pouca memória (só chave + posição, não o registro inteiro);
- pode ser ordenado sem tocar no arquivo original;
- permite busca binária e acesso direto com `fseek`.

---

## 14. A struct do índice

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
├── cep      (a chave)
└── posicao  (onde o registro está no arquivo)
```

Como precisamos guardar **vários** `IndiceCep` ao mesmo tempo, usamos ponteiro:

```c
IndiceCep *indice;

indice = malloc(qtd * sizeof(IndiceCep));
```

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

IndiceCep *indice;
→ espaço para vários IndiceCep
→ precisa armazenar todos os índices
→ usa malloc
```

---

## 15. Construindo o índice

Depois de calcular `qtd`, reservamos o espaço e voltamos ao começo do arquivo:

```c
IndiceCep *indice;

indice = malloc(qtd * sizeof(IndiceCep));

rewind(f);
```

E percorremos todos os registros:

```c
for(i = 0; i < qtd; i++)
{
    fread(&e, sizeof(Endereco), 1, f);

    strncpy(indice[i].cep, e.cep, 8);

    indice[i].posicao = i;
}
```

Vamos entender linha por linha.

### `for`

```c
for(i = 0; i < qtd; i++)
```

Percorre todas as posições. Se `qtd = 4`, temos `i = 0, 1, 2, 3`.

### `fread(&e, sizeof(Endereco), 1, f)`

Significa: *"leia 1 `Endereco` do arquivo e coloque dentro de `e`."* O `&e` é usado porque `fread` precisa do **endereço da variável** onde vai colocar os dados. O `1` significa que apenas um registro é lido nesta chamada.

O próximo `fread` continua de onde o anterior parou, porque o arquivo mantém uma posição de leitura que avança sozinha depois de cada leitura.

### `strncpy(indice[i].cep, e.cep, 8)`

Pega o CEP do `Endereco` recém-lido (`e.cep`) e copia para o índice (`indice[i].cep`):

```text
e.cep
  ↓
"22222222"
        ↓ copia
indice[0].cep
  ↓
"22222222"
```

### `indice[i].posicao = i`

Guarda a posição **original** daquele registro no arquivo:

```text
i = 0
indice[0].cep = "22222222"
indice[0].posicao = 0

i = 1
indice[1].cep = "11111111"
indice[1].posicao = 1
```

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

A posição é sempre a posição **original** no arquivo, mesmo que o índice depois seja reordenado.

---

## 16. Ordenando o índice

```c
qsort(indice, qtd, sizeof(IndiceCep), compara);
```

Agora estamos ordenando **`IndiceCep`**, e não `Endereco`. Por isso `sizeof(IndiceCep)`, e não `sizeof(Endereco)`.

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

### O resultado

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

**A posição não foi alterada.** Só mudamos a ordem das entradas do índice. A entrada `22222222 → 0` continua dizendo *"o CEP 22222222 está na posição 0 do arquivo original"*. O arquivo em si nunca é tocado.

---

## 17. Busca binária

Depois de ordenar o índice, podemos procurar uma chave usando busca binária, que descarta metade dos candidatos a cada passo.

```c
long inicio = 0;
long fim = qtd - 1;
```

Se temos 5 entradas (posições 0 a 4): `inicio = 0`, `fim = 4`.

### `while`

```c
while(inicio <= fim)
```

Continua procurando enquanto ainda existir uma parte do índice para pesquisar.

### `meio`

```c
long meio = (inicio + fim) / 2;
```

Calcula a posição central. Exemplo: `inicio = 0`, `fim = 4` → `meio = 2`.

### Comparando a chave

```c
int resultado = strncmp(argv[1], indice[meio].cep, 8);
```

`argv[1]` é a chave digitada pelo usuário (por exemplo, `./programa 33333333` → `argv[1] = "33333333"`), e `indice[meio].cep` é a chave que está no meio do índice.

### Os três casos

```c
if(resultado == 0)
{
    /* CEPs iguais: encontramos a chave */
}
else if(resultado > 0)
{
    /* a chave procurada é maior: procura na metade da direita */
    inicio = meio + 1;
}
else
{
    /* a chave procurada é menor: procura na metade da esquerda */
    fim = meio - 1;
}
```

```text
resultado == 0  → achou
resultado >  0  → a chave é maior  → vai para a direita
resultado <  0  → a chave é menor  → vai para a esquerda
```

O laço termina quando `inicio` ultrapassa `fim`: nesse ponto, a chave não existe no índice.

> Numa varredura sequencial, 1.000.000 de registros exigem até 1.000.000 de comparações. Na busca binária, cerca de 20.

---

## 18. Acesso direto com `fseek`

Quando encontramos (`resultado == 0`), pegamos a posição guardada:

```c
long posicao = indice[meio].posicao;
```

Por exemplo, se `indice[meio].posicao = 7`, isso significa: *"o registro que eu quero está na posição 7 do arquivo original."*

Agora usamos:

```c
fseek(f, posicao * sizeof(Endereco), SEEK_SET);
```

Lembrando que `fseek` trabalha com **bytes**, não com número de registros. Se `sizeof(Endereco) = 300` e `posicao = 7`, então `7 × 300 = 2100` bytes:

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

lê esse registro para a variável temporária `e`. Agora podemos mostrar seus dados:

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

A precisão (`%.72s`, `%.8s`, etc.) é necessária porque os campos são `char[]` de tamanho fixo, sem garantia de terminador `'\0'` no fim — sem ela, o `printf` poderia ler além do campo.

---

## 19. Fluxo completo

```text
                         cep.dat
                            │
                            ↓
                          fopen
                            │
                            ↓
                  fseek/ftell → descobre qtd
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
                       pela chave
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
                            │
                            ↓
                   free + fclose
```

---

# Parte V — Referência

## 20. Resumo dos conceitos

### Ponteiros

```text
Endereco e
→ uma struct

Endereco *e
→ ponteiro para uma struct (ou várias)

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

e[i].cep
→ acessa campo de um elemento de um bloco apontado
```

### Memória

```text
malloc()  → reserva memória (verifique se retornou NULL)
free()    → libera memória
```

### Arquivos

```text
fopen()   → abre        ("rb" leitura binária, "wb" escrita binária)
fseek()   → move a posição no arquivo (em bytes)
ftell()   → informa a posição
rewind()  → volta para o começo
fread()   → arquivo → memória
fwrite()  → memória → arquivo
fclose()  → fecha
```

### Ordenação

Para os registros originais:

```c
qsort(e, qtd, sizeof(Endereco), compara);
```

Para o índice:

```c
qsort(indice, qtd, sizeof(IndiceCep), compara);
```

O tipo passado para `sizeof` deve ser o tipo dos elementos que estão sendo ordenados naquela chamada.

### Índice

```text
IndiceCep
├── cep
└── posicao
```

O índice funciona como:

```text
chave → posição no arquivo
```

Ordenar o índice **não** altera o arquivo original. A busca binária encontra a chave rapidamente; a `posicao` encontrada é usada pelo `fseek` para acessar diretamente o registro correspondente.

---

## 21. Código comentado — ordenação

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

    if(f == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }


    // Vai para o final do arquivo.
    fseek(f, 0, SEEK_END);


    // Descobre o tamanho do arquivo em bytes.
    posicao = ftell(f);


    // Calcula quantos registros existem.
    qtd = posicao / sizeof(Endereco);


    // Reserva memória suficiente para todos os registros.
    e = (Endereco*) malloc(qtd * sizeof(Endereco));

    if(e == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria\n");
        fclose(f);
        return 1;
    }


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


    // Fecha os arquivos.
    fclose(saida);
    fclose(f);


    // Libera a memória reservada pelo malloc.
    free(e);


    return 0;
}
```

---

## 22. Código comentado — índice

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


    // Reserva memória para TODAS as entradas do índice
    // — o arquivo inteiro nunca é carregado na memória.
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


    // Ordena o índice pelo CEP. O arquivo não é alterado.
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


            // Vai diretamente para esse registro (em bytes).
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
            // Precisão no printf porque os campos são
            // char[] de tamanho fixo, sem \0 garantido.
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

## 23. A ideia mais importante

O programa do índice trabalha com **dois tipos de informação diferentes**:

```text
┌──────────────────────────────┐
│          cep.dat             │
│                               │
│  vários Enderecos no arquivo │
└──────────────┬───────────────┘
               │
               │ lê UM por vez
               ↓
        ┌─────────────┐
        │ Endereco e  │
        │              │
        │ temporário   │
        └──────┬──────┘
               │
               │ pega o CEP
               ↓
        ┌──────────────────────┐
        │   IndiceCep *indice  │
        │                       │
        │ CEP → posição         │
        │ CEP → posição         │
        │ CEP → posição         │
        │ ...                   │
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
→ sem malloc

IndiceCep *indice
→ VÁRIAS entradas do índice
→ ficam todas na memória
→ por isso usa malloc
```

E o índice existe para transformar:

```text
"quero o CEP 33333333"
```

em:

```text
"ele está na posição 7 do cep.dat"
```

Depois o `fseek` usa essa posição para chegar diretamente ao registro correspondente, sem precisar varrer o arquivo.
