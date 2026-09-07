# Busca Binária em Arquivos e `fseek`

## 📚 Sumário

* [1. Ideia geral](#1-ideia-geral)
* [2. Arquivo e posição atual](#2-arquivo-e-posicao-atual)
* [3. `ftell()`](#3-ftell)
* [4. `fseek()`](#4-fseek)

  * [`SEEK_SET`](#seek_set)
  * [`SEEK_CUR`](#seek_cur)
  * [`SEEK_END`](#seek_end)
* [5. `fread()` e a posição do arquivo](#5-fread-e-a-posicao-do-arquivo)
* [6. `sizeof()` e tamanho dos registros](#6-sizeof-e-tamanho-dos-registros)
* [7. Convertendo bytes ↔ registros](#7-convertendo-bytes--registros)
* [8. Encontrando o meio do arquivo](#8-encontrando-o-meio-do-arquivo)
* [9. Como `fseek()` e `fread()` trabalham juntos](#9-como-fseek-e-fread-trabalham-juntos)
* [10. Busca sequencial × busca binária](#10-busca-sequencial--busca-binária)
* [11. Estrutura da busca binária](#11-estrutura-da-busca-binária)
* [12. Exemplo com `Endereco`](#12-exemplo-com-endereco)
* [13. Pontos importantes](#13-pontos-importantes)
* [14. Resumo](#14-resumo)

---

## 1. Ideia geral

Quando trabalhamos com arquivos binários contendo vários registros de uma `struct`, podemos acessar um registro específico usando sua **posição em bytes**.

Isso é especialmente útil para fazer **busca binária**.

A ideia é parecida com a busca binária em um vetor:

```text
[0] [1] [2] [3] [4] [5] [6] [7] [8]
                ↑
              meio
```

Em um arquivo, porém, não fazemos:

```c
arquivo[meio]
```

Em vez disso, precisamos:

1. descobrir onde está o registro;
2. converter essa posição em uma posição em bytes;
3. usar `fseek()` para ir até lá;
4. usar `fread()` para ler o registro.

> ⚠️ **Importante:** este material mostra a preparação e a lógica da busca binária em arquivos, mas o código estudado inicialmente **ainda não implementa uma busca binária completa**. Depois de acessar o meio, ele continua lendo os próximos registros sequencialmente, em vez de recalcular o meio e fazer novos `fseek()`.

---

## 2. Arquivo e posição atual

Um arquivo pode ser imaginado como uma sequência de bytes:

```text
[A][B][C][D][E][F][G][H]
 0  1  2  3  4  5  6  7
```

O arquivo possui uma **posição atual de leitura/escrita**.

Podemos imaginar uma "cabeça de leitura":

```text
[A][B][C][D][E][F][G][H]
         ↑
      posição atual
```

Essa posição pertence ao arquivo representado por:

```c
FILE *f;
```

### `fread()`

O `fread()` lê **a partir da posição atual**.

Depois de ler, a posição avança.

Por exemplo:

```text
[A][B][C][D][E][F]
 ↑
```

Se lermos 2 bytes:

```text
[A][B][C][D][E][F]
         ↑
```

A posição avançou 2 bytes.

### `fseek()`

O `fseek()` serve para **mudar essa posição**.

---

## 3. `ftell()`

```c
ftell(f);
```

O `ftell()` informa **qual é a posição atual do arquivo**.

Essa posição é dada como um deslocamento em bytes desde o início do arquivo, no caso de um arquivo binário.

Por exemplo:

```text
[A][B][C][D][E]
 0  1  2  3  4
```

Se a posição atual for 4:

```c
ftell(f);
```

retorna:

```text
4
```

Isso significa:

> A posição atual está a 4 bytes do início do arquivo.

### ⚠️ Importante

`ftell()` **não lê bytes**.

Ele apenas informa **onde a posição atual está**.

---

## 4. `fseek()`

A função possui a forma:

```c
fseek(f, deslocamento, origem);
```

Ela serve para **mover a posição atual do arquivo**.

Os três principais valores de origem são:

```c
SEEK_SET
SEEK_CUR
SEEK_END
```

---

### `SEEK_SET`

Usa o **início do arquivo** como referência.

```c
fseek(f, 0, SEEK_SET);
```

Significa:

> Vá para o início do arquivo.

Também podemos fazer:

```c
fseek(f, 3, SEEK_SET);
```

Significa:

> Vá para a posição 3, contando a partir do início.

```text
[A][B][C][D][E]
         ↑
         3
```

---

### `SEEK_CUR`

Usa a **posição atual** como referência.

```c
fseek(f, 2, SEEK_CUR);
```

Significa:

> Avance 2 bytes a partir da posição atual.

Também pode ser usado para voltar:

```c
fseek(f, -2, SEEK_CUR);
```

---

### `SEEK_END`

Usa o **final do arquivo** como referência.

```c
fseek(f, 0, SEEK_END);
```

Significa:

> Vá para o final do arquivo.

Isso é muito usado junto com `ftell()` para descobrir o tamanho do arquivo:

```c
fseek(f, 0, SEEK_END);

long tamanhoBytes = ftell(f);
```

A lógica é:

```text
fseek
 ↓
vai para o final

ftell
 ↓
pergunta onde está

resultado
 ↓
tamanho do arquivo em bytes
```

---

## 5. `fread()` e a posição do arquivo

A função:

```c
fread(&e, sizeof(Endereco), 1, f);
```

significa:

> Leia 1 elemento do tipo `Endereco`, a partir da posição atual do arquivo, e coloque os dados dentro de `e`.

Os parâmetros são:

```c
fread(
    &e,               // onde colocar os dados
    sizeof(Endereco), // tamanho de cada elemento
    1,                // quantidade de elementos
    f                 // arquivo
);
```

O `fread()` retorna a quantidade de elementos que conseguiu ler.

Por exemplo:

```c
qt = fread(&e, sizeof(Endereco), 1, f);
```

Se conseguiu ler:

```text
qt = 1
```

Se não conseguiu:

```text
qt = 0
```

### `fseek()` + `fread()`

Eles trabalham juntos:

```c
fseek(f, 600, SEEK_SET);
fread(&e, sizeof(Endereco), 1, f);
```

Primeiro:

```text
fseek
 ↓
move a posição para o byte 600
```

Depois:

```text
fread
 ↓
lê a partir do byte 600
```

Ou seja:

> **`fseek()` escolhe ONDE ler.**
> **`fread()` lê O QUE está naquele lugar.**

---

## 6. `sizeof()` e tamanho dos registros

Quando temos uma `struct`:

```c
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

Podemos descobrir o tamanho dela com:

```c
sizeof(Endereco)
```

Nesse exemplo:

```text
72 + 72 + 72 + 72 + 2 + 8 + 2
= 300 bytes
```

Portanto:

```c
sizeof(Endereco)
```

retorna:

```text
300
```

### Por que existe `lixo[2]`?

O campo:

```c
char lixo[2];
```

representa os 2 bytes finais existentes no formato do registro:

```text
espaço + quebra de linha
```

Ele ajuda a manter a `struct` com o mesmo tamanho/formato esperado no arquivo.

Assim:

```text
Endereco = 300 bytes
```

### ⚠️ Observação

O tamanho real de uma `struct` deve ser obtido com:

```c
sizeof(Endereco)
```

porque o compilador pode inserir bytes de **padding/alinhamento**.

---

## 7. Convertendo bytes ↔ registros

Essa é uma das partes mais importantes.

Suponha:

```text
cada Endereco = 300 bytes
arquivo inteiro = 300.000 bytes
```

### Bytes → quantidade de registros

Usamos:

```c
long tamanhoRegistros =
    tamanhoBytes / sizeof(Endereco);
```

Exemplo:

```text
300.000 bytes
÷
300 bytes por registro
=
1.000 registros
```

Portanto:

```text
tamanhoRegistros = 1000
```

### Regra:

```text
BYTES → REGISTROS
       ÷
```

Estamos perguntando:

> **"Quantos Enderecos cabem nesses bytes?"**

---

### Registros → bytes

Agora suponha que queremos acessar o registro:

```text
499
```

O `fseek()` trabalha com bytes, então precisamos converter:

```c
meio * sizeof(Endereco)
```

Exemplo:

```text
499 registros
×
300 bytes por registro
=
149.700 bytes
```

Então:

```c
fseek(f, 149700, SEEK_SET);
```

### Regra:

```text
REGISTROS → BYTES
       ×
```

Estamos perguntando:

> **"Quantos bytes preciso percorrer para chegar nesse registro?"**

### Resumindo:

```text
tamanhoBytes / sizeof(Endereco)
        ↓
     registros


meio * sizeof(Endereco)
        ↓
       bytes
```

---

## 8. Encontrando o meio do arquivo

Depois de descobrir a quantidade de registros:

```c
long tamanhoRegistros =
    tamanhoBytes / sizeof(Endereco);
```

podemos definir:

```c
long inicio = 0;
long fim = tamanhoRegistros - 1;
```

Se temos 1000 registros:

```text
0, 1, 2, 3, ..., 998, 999
```

Então:

```text
inicio = 0
fim = 999
```

Calculamos o meio:

```c
long meio = (inicio + fim) / 2;
```

```text
(0 + 999) / 2
= 499
```

Então:

```text
0 ---------------- 499 ---------------- 999
                   ↑
                  meio
```

---

## 9. Como `fseek()` e `fread()` trabalham juntos

Agora podemos juntar tudo:

```c
long meio = (inicio + fim) / 2;

fseek(
    f,
    meio * sizeof(Endereco),
    SEEK_SET
);

qt = fread(
    &e,
    sizeof(Endereco),
    1,
    f
);
```

Suponha:

```text
meio = 499
sizeof(Endereco) = 300
```

Então:

```text
499 × 300
= 149.700 bytes
```

O `fseek()` faz:

```text
fseek
 ↓
byte 149.700
```

E o `fread()` faz:

```text
byte 149.700
 ↓
lê 300 bytes
 ↓
Endereco 499
 ↓
e
```

Visualmente:

```text
ARQUIVO

[End 0][End 1] ... [End 498][End 499][End 500]
                               ↑
                             fseek
                               ↓
                             fread
                               ↓
                               e
```

Depois do `fread()`, `e` contém os dados do registro 499.

---

## 10. Busca sequencial × busca binária

### Busca sequencial

Na busca sequencial, começamos do início:

```text
0 → 1 → 2 → 3 → 4 → 5 → ...
```

Lemos um registro por vez até encontrar o procurado.

Exemplo:

```c
fread(&e, sizeof(Endereco), 1, f);
```

Depois:

```c
fread(&e, sizeof(Endereco), 1, f);
```

E assim por diante.

---

### Busca binária

Na busca binária, começamos pelo meio:

```text
0 ---------------- 499 ---------------- 999
                   ↑
                 começa
```

Comparamos o valor procurado com o registro 499.

Se o arquivo estiver ordenado pelo CEP:

```text
CEP procurado < CEP do meio
```

então sabemos que o CEP procurado só pode estar na metade esquerda.

```text
0 ---------------- 499 | 500 ---------------- 999
          ↑
      continuamos aqui
```

Se:

```text
CEP procurado > CEP do meio
```

continuamos na metade direita:

```text
0 ---------------- 499 | 500 ---------------- 999
                          ↑
                      continuamos aqui
```

Depois calculamos um novo meio.

---

## 11. Estrutura da busca binária

A lógica é:

```text
inicio = 0
fim = último registro

enquanto inicio <= fim:

    meio = (inicio + fim) / 2

    ir até o registro meio
        ↓
      fseek()

    ler o registro
        ↓
      fread()

    comparar

    se encontrou:
        terminou

    se procurado < meio:
        fim = meio - 1

    se procurado > meio:
        inicio = meio + 1
```

O ponto principal é que **a cada tentativa fazemos um novo `fseek()`**.

```text
          meio
            ↓
          fseek
            ↓
          fread
            ↓
        comparação
         ↙       ↘
    esquerda    direita
       ↓           ↓
   novo meio    novo meio
       ↓           ↓
    fseek        fseek
```

---

## 12. Exemplo com `Endereco`

Estrutura:

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

Tamanho:

```c
sizeof(Endereco)
```

```text
300 bytes
```

Imagine um arquivo com:

```text
300.000 bytes
```

Descobrimos:

```c
long tamanhoRegistros =
    tamanhoBytes / sizeof(Endereco);
```

```text
300.000 / 300
= 1.000 registros
```

Então:

```c
inicio = 0;
fim = 999;
```

Primeiro meio:

```c
meio = (0 + 999) / 2;
```

```text
meio = 499
```

Posição em bytes:

```c
meio * sizeof(Endereco)
```

```text
499 × 300
= 149.700 bytes
```

Então:

```c
fseek(f, 149700, SEEK_SET);
```

Agora:

```c
fread(&e, sizeof(Endereco), 1, f);
```

lê o registro 499.

Podemos então verificar:

```c
e.cep
```

e comparar com:

```c
argv[1]
```

---

## 13. Pontos importantes

### `fseek()` não lê

```c
fseek(f, ...);
```

Apenas **move a posição atual**.

---

### `ftell()` não move

```c
ftell(f);
```

Apenas **informa a posição atual**.

---

### `fread()` lê a partir da posição atual

```c
fread(..., f);
```

Ele lê de onde o arquivo `f` está atualmente.

---

### `fread()` avança a posição

Se:

```text
posição atual = 600
```

e lemos:

```text
300 bytes
```

a posição avança para:

```text
900
```

---

### `sizeof(Endereco)` é o tamanho de UM registro

```c
sizeof(Endereco)
```

não representa o tamanho do arquivo.

Representa:

```text
1 Endereco
```

---

### `tamanhoBytes` é o tamanho do arquivo inteiro

Depois de:

```c
fseek(f, 0, SEEK_END);

long tamanhoBytes = ftell(f);
```

temos:

```text
tamanhoBytes = arquivo inteiro em bytes
```

---

### `tamanhoRegistros` é a quantidade de registros

```c
tamanhoRegistros =
    tamanhoBytes / sizeof(Endereco);
```

---

### `meio` é número de registro, não número de bytes

Se:

```c
meio = 499;
```

isso significa:

> registro 499

Para transformar em bytes:

```c
meio * sizeof(Endereco)
```

---

### `fseek()` precisa da posição em bytes

Por isso:

```c
fseek(f, meio * sizeof(Endereco), SEEK_SET);
```

---

## 14. Resumo

As funções principais:

| Função             | O que faz                          |
| ------------------ | ---------------------------------- |
| `sizeof(Endereco)` | tamanho de um registro em bytes    |
| `ftell(f)`         | informa a posição atual do arquivo |
| `fseek(f, ...)`    | muda a posição atual               |
| `fread(...)`       | lê dados a partir da posição atual |

### Fluxo para acessar um registro

```text
QUERO O REGISTRO 499
        ↓
499 × sizeof(Endereco)
        ↓
posição em bytes
        ↓
fseek()
        ↓
posição do arquivo muda
        ↓
fread()
        ↓
registro é colocado em e
        ↓
posso acessar e.cep
```

### As duas conversões fundamentais

```text
                 ÷ sizeof(Endereco)
BYTES ─────────────────────────────→ REGISTROS


                 × sizeof(Endereco)
REGISTROS ──────────────────────────→ BYTES
```

### Ideia principal da busca binária

```text
        início ---------------- fim
                  ↓
                 meio
                  ↓
                fseek
                  ↓
                fread
                  ↓
              comparar
             ↙         ↘
        esquerda      direita
             ↓           ↓
          novo meio
             ↓
           fseek
             ↓
           fread
```

> **`fseek()` é o que permite "pular" diretamente para uma região do arquivo. É isso que torna possível fazer busca binária em um arquivo de registros de tamanho fixo.**
