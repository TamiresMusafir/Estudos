# 📁 Estrutura de Arquivos em C

> Material de estudo consolidado — conceitos, funções, exercícios e principais dificuldades

---

## 📑 Sumário

1. [O que é manipulação de arquivos](#1)
2. [O tipo `FILE`](#2)
3. [`FILE *entrada` — ponteiro para arquivo](#3)
4. [`entrada` x `*entrada`](#4)
5. [Por que `entrada = fopen(...)`](#5)
6. [`fopen()`](#6)
7. [Modos de abertura](#7)
8. [Texto x binário](#8)
9. [`fclose()`](#9)
10. [Fechar antes do `return`](#10)
11. [`fgetc()` e `fputc()`](#11)
12. [`int c` e `EOF`](#12)
13. [`fread()` e `fwrite()`](#13)
14. [Memória: struct, array, `sizeof`, `memset`, `strcpy`](#14)
15. [`argc` e `argv`](#15)
16. [Exercícios resolvidos](#16)
17. [Bytes e caracteres (ASCII)](#17)
18. [`fseek()`, `ftell()` e acesso direto](#18)
19. [Registros e busca binária](#19)
20. [Mapa mental e resumo final](#20)

---

<a id="1"></a>

# 🧠 1. O que é manipulação de arquivos?

Um arquivo pode ser entendido como uma sequência de **bytes armazenados no disco**.

Um programa pode:

* 📂 abrir um arquivo;
* 📖 ler dados;
* ✍️ escrever dados;
* 🔀 mudar a posição de leitura/escrita dentro do arquivo;
* ❌ fechar o arquivo.

A biblioteca principal usada é:

```c
#include <stdio.h>
```

Ela fornece funções como:

```c
fopen()
fclose()
fgetc()
fputc()
fread()
fwrite()
fseek()
ftell()
```

---

<a id="2"></a>

# 📌 2. O tipo `FILE`

`FILE` é um **tipo fornecido pela biblioteca padrão do C**, usado para representar e controlar um arquivo aberto.

De forma simplificada, podemos imaginar que um `FILE` guarda informações como:

* qual arquivo está sendo usado;
* modo de abertura;
* posição atual dentro do arquivo;
* informações de buffer;
* estado de erro;
* indicação de fim de arquivo.

> ⚠️ **Não precisamos conhecer os campos internos de `FILE`.** Trabalhamos sempre através das funções da biblioteca.

Declaração típica:

```c
FILE *f;
```

Aqui:

```text
FILE
 ↓
é um tipo

f
 ↓
é uma variável

*
 ↓
indica que f é um ponteiro
```

Portanto:

> `f` é um ponteiro para um `FILE`.

Podemos imaginar:

```text
f
│
│ endereço
▼
┌──────────────┐
│     FILE     │
│              │
│ informações  │
│ do arquivo   │
└──────────────┘
```

---

<a id="3"></a>

# 🔗 3. `FILE *entrada` — ponteiro para arquivo

Quando fazemos:

```c
FILE *entrada;
```

estamos criando uma variável chamada `entrada` que é um **ponteiro para `FILE`**.

```text
entrada → endereço de um FILE
```

`entrada` **NÃO é o arquivo diretamente**. Ele guarda o endereço de uma estrutura `FILE` usada para controlar o arquivo.

---

<a id="4"></a>

# ⭐ 4. A diferença entre `entrada` e `*entrada`

Essa é uma das partes mais importantes — e mais confusas.

Comparando com um caso simples:

```c
int x = 10;
int *p = &x;
```

Temos:

```text
p  → endereço de x
*p → valor de x
```

Por exemplo:

```text
p  = 1000       ← endereço
*p = 10         ← valor naquele endereço
```

A mesma ideia vale para:

```c
FILE *entrada;
```

Podemos imaginar:

```text
entrada
   │
   │ endereço
   ▼
  FILE
```

| Expressão  | Significado                      |
| ---------- | -------------------------------- |
| `entrada`  | endereço armazenado no ponteiro  |
| `*entrada` | acessa o `FILE` naquele endereço |

⚠️ **`entrada` não aponta para si mesma.**

É:

```text
entrada ───────────► FILE
```

### Dois usos diferentes do `*`

```c
FILE *entrada;   // aqui o * DECLARA que entrada é um ponteiro
```

```c
*entrada         // aqui o * é o operador de DESREFERENCIAÇÃO:
                 // "vá até o endereço armazenado no ponteiro"
```

---

<a id="5"></a>

# 🔑 5. Por que usamos `entrada = fopen(...)`?

A função `fopen()` retorna um:

```c
FILE *
```

Por exemplo:

```c
FILE *entrada;

entrada = fopen("arquivo.txt", "rb");
```

O fluxo é:

```text
             fopen()
                │
                ▼
             FILE *
                │
                ▼
            entrada
```

Por isso usamos:

```c
entrada = fopen(...);
```

e **não**:

```c
*entrada = fopen(...);   // ❌
```

Porque:

```text
entrada  → FILE *
*entrada → FILE
```

Enquanto `fopen()` retorna:

```text
FILE *
```

Então queremos atribuir:

```text
FILE * → FILE *
```

### Formas equivalentes de escrever

Separado:

```c
FILE *entrada;
entrada = fopen("arquivo.txt", "rb");
```

Em uma linha só:

```c
FILE *entrada = fopen("arquivo.txt", "rb");
```

Com argumento da linha de comando:

```c
entrada = fopen(argv[1], "rb");
```

Os três são equivalentes.

---

<a id="6"></a>

# 📂 6. `fopen()`

A função:

```c
fopen(nome, modo);
```

abre um arquivo e retorna um `FILE *`.

Exemplo:

```c
FILE *f = fopen("dados.dat", "rb");
```

Podemos pensar:

```text
arquivo no disco
       │
       ▼
    fopen()
       │
       ▼
     FILE *
       │
       ▼
       f
```

Se não conseguir abrir o arquivo:

```text
fopen()
   ↓
NULL
```

Por isso **sempre** verificamos:

```c
if(!f)
{
    printf("Erro ao abrir arquivo");
    return 1;
}
```

> `!f` significa que `f` é `NULL`.

---

<a id="7"></a>

# 🛠️ 7. Modos do `fopen()`

O segundo parâmetro informa **como queremos abrir o arquivo**.

## `r` — Read

```c
fopen("arquivo.txt", "r");
```

📖 Abre para **leitura**.

* O arquivo precisa existir.
* Não é usado para escrita.

---

## `w` — Write

```c
fopen("arquivo.txt", "w");
```

✍️ Abre para **escrita**.

* Cria o arquivo se ele não existir.
* ⚠️ Se o arquivo já existir, seu conteúdo é **apagado/truncado**.
* Cuidado: `w` pode destruir o conteúdo existente.

---

## `a` — Append

```c
fopen("arquivo.txt", "a");
```

➕ Abre para escrita no **final do arquivo**.

* Preserva o conteúdo existente.
* Cria o arquivo se necessário.
* Útil para adicionar informações sem apagar o que já existe.

---

## `r+` — Read + Write

```c
fopen("arquivo.txt", "r+");
```

📖✍️ Permite ler e escrever.

* O arquivo precisa existir.
* O conteúdo existente **não** é apagado ao abrir.

---

## `w+` — Write + Read

```c
fopen("arquivo.txt", "w+");
```

📖✍️ Permite escrever e ler.

* Cria o arquivo se não existir.
* ⚠️ Se já existir, o conteúdo é **apagado/truncado**.

---

## `rb` — Read Binary

```c
fopen("arquivo.dat", "rb");
```

É:

```text
r = read
b = binary
```

> 📖 Ler um arquivo em modo binário.

Muito utilizado quando queremos trabalhar diretamente com **bytes**.

---

## `r+b` — Read + Write Binary

```c
fopen("arquivo.dat", "r+b");
```

É:

```text
r = read
+ = leitura + escrita
b = binary
```

Permite ler e escrever em um arquivo binário existente.

---

## 📋 Resumo dos modos

| Modo  | Leitura | Escrita | Cria | Apaga conteúdo |
| ----- | :-----: | :-----: | :--: | :------------: |
| `r`   |    ✅    |    ❌    |   ❌  |        ❌       |
| `w`   |    ❌    |    ✅    |   ✅  |     ⚠️ Sim     |
| `a`   |    ❌    |    ✅    |   ✅  |        ❌       |
| `r+`  |    ✅    |    ✅    |   ❌  |        ❌       |
| `w+`  |    ✅    |    ✅    |   ✅  |     ⚠️ Sim     |
| `rb`  |    ✅    |    ❌    |   ❌  |        ❌       |
| `wb`  |    ❌    |    ✅    |   ✅  |     ⚠️ Sim     |
| `r+b` |    ✅    |    ✅    |   ❌  |        ❌       |

### 🧠 Macete

```text
r → read
w → write
a → append

+ → leitura E escrita
b → binary
```

---

<a id="8"></a>

# 💾 8. Texto x Binário

Os modos podem ou não ter o `b`:

```text
r    →  rb
w    →  wb
r+   →  r+b
```

O `b` significa:

> **binary**

Em arquivos binários, trabalhamos diretamente com os bytes armazenados.

⚠️ Em sistemas como o Windows existe uma diferença importante entre o modo texto e o modo binário, especialmente na representação das **quebras de linha**. Por isso, para arquivos de dados, usamos normalmente:

```c
"rb"
"wb"
"r+b"
```

O modo binário é especialmente importante quando trabalhamos com:

* estruturas;
* registros;
* arquivos `.dat`;
* índices;
* acesso direto;
* busca binária em arquivos.

---

<a id="9"></a>

# ❌ 9. `fclose()`

```c
fclose(f);
```

Fecha o arquivo que foi aberto.

⚠️ Isso **não significa apertar o X de uma janela**. É uma operação do programa, que informa à biblioteca:

> "Terminei de trabalhar com esse arquivo."

O arquivo deixa de ficar aberto pelo programa. Todo arquivo aberto deve ser fechado.

> 📌 `fclose()` recebe um `FILE *`. Por isso é `fclose(f);` e **nunca** `fclose(*f);`

---

<a id="10"></a>

# ⚠️ 10. Por que às vezes precisamos fechar antes do final?

Exemplo:

```c
entrada = fopen(...);

if(!entrada)
{
    return 1;
}

saida = fopen(...);

if(!saida)
{
    fclose(entrada);   // ← fechamos aqui!
    return 1;
}
```

Imagine:

```text
entrada → abriu ✅
saida   → falhou ❌
```

Como o programa vai executar:

```c
return 1;
```

ele **não chegará** ao `fclose(entrada);` que está no final do programa.

Por isso fazemos `fclose(entrada);` **antes do `return`**.

---

<a id="11"></a>

# 📖 11. `fgetc()` e `fputc()`

## `fgetc()` — lê um byte

```c
c = fgetc(entrada);
```

Lê **um byte por vez** do arquivo.

Imagine um arquivo contendo:

```text
ABC
```

A leitura seria aproximadamente:

```text
fgetc() → A
fgetc() → B
fgetc() → C
fgetc() → \n
fgetc() → EOF
```

## `fputc()` — escreve um byte

```c
fputc(c, saida);
```

Escreve um byte/caractere no arquivo.

## Direção dos dados

```text
fgetc()
ARQUIVO ───────► MEMÓRIA

fputc()
MEMÓRIA ───────► ARQUIVO
```

## Programa de cópia (ideia central)

```text
ARQUIVO DE ENTRADA
        ↓
      fgetc
        ↓
        c
        ↓
      fputc
        ↓
ARQUIVO DE SAÍDA
```

Em código:

```c
int c;

c = fgetc(entrada);

while(c != EOF)
{
    fputc(c, saida);
    c = fgetc(entrada);
}
```

O programa repete isso até chegar ao `EOF`.

---

<a id="12"></a>

# 🤔 12. Por que `int c` e não `char c`? E o que é `EOF`?

## Por que `int`

Mesmo lendo um único caractere/byte, usamos:

```c
int c;
```

porque `fgetc()` precisa conseguir retornar **duas coisas diferentes**:

1. um valor correspondente ao byte lido (0 a 255);
2. ou `EOF`.

Então:

```c
c = fgetc(entrada);
```

pode resultar em:

```text
byte
```

ou:

```text
EOF
```

Um `int` consegue representar tanto os valores dos bytes quanto o valor especial `EOF`. Por isso o padrão é:

```c
int c;

c = fgetc(entrada);

while(c != EOF)
{
    ...
    c = fgetc(entrada);
}
```

## 🚩 `EOF`

`EOF` significa:

> **End Of File** — fim do arquivo.

⚠️ `EOF` **não é um caractere comum armazenado no arquivo**. É um valor especial retornado pelas funções de leitura para indicar que **não há mais dados**.

Por isso:

```c
while(c != EOF)
```

significa:

> Continue enquanto não chegamos ao fim do arquivo.

---

<a id="13"></a>

# 📦 13. `fread()` e `fwrite()`

Essas funções permitem trabalhar com **blocos de dados**, em vez de um byte por vez.

## Direção — a coisa mais importante para memorizar

```text
┌──────────────┐
│   ARQUIVO    │
└──────┬───────┘
       │
       │ fread
       ▼
┌──────────────┐
│    MEMÓRIA   │
└──────────────┘
```

`fread()`:

> 📂 Arquivo → Memória

```text
┌──────────────┐
│    MEMÓRIA   │
└──────┬───────┘
       │
       │ fwrite
       ▼
┌──────────────┐
│   ARQUIVO    │
└──────────────┘
```

`fwrite()`:

> 💾 Memória → Arquivo

---

## 🧩 Parâmetros do `fread()`

Formato:

```c
fread(destino, tamanho, quantidade, arquivo);
```

Pense sempre:

```text
ONDE COLOCAR OS DADOS?
QUANTO CADA UM?
QUANTOS?
DE QUAL ARQUIVO?
```

Exemplo:

```c
fread(
    p,
    sizeof(Pessoa),
    1000,
    f
);
```

Significa:

> Leia até 1000 estruturas `Pessoa` do arquivo `f` e coloque os dados começando em `p`.

---

## 🧩 Parâmetros do `fwrite()`

Formato:

```c
fwrite(origem, tamanho, quantidade, arquivo);
```

Pense:

```text
O QUE GRAVAR?
QUANTO CADA UM?
QUANTOS?
EM QUAL ARQUIVO?
```

Exemplo:

```c
fwrite(
    p,
    sizeof(Pessoa),
    1000,
    f
);
```

Visualmente:

```text
                          tamanho        quantidade
                              ↓               ↓

fwrite(          p,       sizeof(Pessoa),   1000,   f);
                 ↑                                  ↑
          início dos dados                       arquivo
```

Significa:

> Grave 1000 estruturas `Pessoa` no arquivo `f`, considerando que cada uma possui `sizeof(Pessoa)` bytes.

### Gravando uma única estrutura

```c
fwrite(&p, sizeof(Pessoa), 1, f);   // uma Pessoa (variável simples → precisa do &)
fwrite(p,  sizeof(Pessoa), 1000, f); // 1000 Pessoas (array → já é endereço)
```

---

## 📂 Lendo estruturas com `fread`

```c
int qt = fread(
    p,
    sizeof(Pessoa),
    1000,
    f
);
```

O fluxo é:

```text
ARQUIVO
   │
   │ fread
   ▼
MEMÓRIA
   │
   ▼
p[0]
p[1]
p[2]
...
```

O retorno de `fread()` informa quantos **itens completos** foram lidos.

Se o arquivo possui 300 Pessoas:

```c
qt = 300;
```

---

## ⚠️ `fread()` não retorna bytes

Observe:

```c
fread(p, sizeof(Pessoa), 1000, f);
```

O segundo parâmetro é o **tamanho de cada item** e o terceiro é a **quantidade de itens**. O retorno é a quantidade de **itens** lidos, não de bytes.

Se:

```text
sizeof(Pessoa) = 52
```

e foram lidas 300 Pessoas:

```text
retorno = 300      ✅
```

e **não**:

```text
15600              ❌ (isso seria a quantidade de bytes)
```

---

## 🔄 Tabelas comparativas

| Função   | Direção                 |
| -------- | ----------------------- |
| `fread`  | 📂 Arquivo → 🧠 Memória |
| `fwrite` | 🧠 Memória → 📂 Arquivo |

| Função   | Quantidade     |
| -------- | -------------- |
| `fgetc`  | 1 byte por vez |
| `fputc`  | 1 byte por vez |
| `fread`  | vários itens   |
| `fwrite` | vários itens   |

---

<a id="14"></a>

# 🧠 14. Memória: struct, array, `sizeof`, `memset`, `strcpy`

## 👤 `struct Pessoa`

Podemos definir:

```c
struct _Pessoa {
    char nome[40];
    int idade;
    float altura;
};
```

E criar um apelido com `typedef`:

```c
typedef struct _Pessoa Pessoa;
```

Agora podemos usar:

```c
Pessoa p;
```

em vez de:

```c
struct _Pessoa p;
```

---

## 👥 Array de `Pessoa`

```c
Pessoa p[1000];
```

Cria espaço para 1000 estruturas:

```text
p[0]    → Pessoa
p[1]    → Pessoa
p[2]    → Pessoa
...
p[999]  → Pessoa
```

Cada Pessoa possui:

```text
nome
idade
altura
```

---

## 📦 `p` x `p[0]`

Se temos `Pessoa p[1000];` então:

```text
p       → início/endereço do array
p[0]    → primeira Pessoa
p[1]    → segunda Pessoa
p[2]    → terceira Pessoa
```

Por isso:

```c
fwrite(p, sizeof(Pessoa), 1000, f);
```

usa `p` como ponto inicial dos dados — a gravação começa no primeiro elemento do array.

---

## 📏 `sizeof()`

`sizeof()` informa o tamanho de algo em **bytes**.

```c
sizeof(Pessoa)
```

pergunta:

> Quantos bytes uma `Pessoa` ocupa?

Se:

```text
sizeof(Pessoa) = 52
```

então:

```text
1 Pessoa = 52 bytes
```

---

## ✖️ `1000 * sizeof(Pessoa)`

Se temos `Pessoa p[1000];`, então:

```c
1000 * sizeof(Pessoa)
```

significa:

> Quantos bytes são necessários para armazenar as 1000 Pessoas.

Exemplo:

```text
sizeof(Pessoa) = 52

1000 × 52
     ↓
52000 bytes
```

---

## 🧹 `memset()`

`memset()` serve para preencher uma região da memória com determinado valor.

Formato:

```c
memset(endereco, valor, quantidade_de_bytes);
```

Exemplo:

```c
memset(p, 0, 1000 * sizeof(Pessoa));
```

Significa:

> Começando no endereço `p`, preencha `1000 * sizeof(Pessoa)` bytes com zero.

### 💡 Por que usar `memset()`?

Quando fazemos:

```c
Pessoa p[1000];
```

a memória **não deve ser tratada como se automaticamente estivesse zerada** — ela pode conter valores que já estavam naquele espaço.

Podemos inicializá-la:

```c
memset(p, 0, sizeof(p));
```

Neste caso específico, também podemos simplesmente fazer:

```c
Pessoa p[1000] = {0};
```

que é uma maneira mais simples de inicializar o array com zero.

### 🧠 Diferença de ideia

```text
Pessoa p[1000] = {0};
        ↓
inicialização do array

memset(...)
        ↓
preenchimento de uma região da memória
```

`memset()` é útil de conhecer porque é uma função **geral** para preencher qualquer região de memória.

---

## ✏️ `strcpy()`

```c
strcpy(p[0].nome, "Renato Mauro");
```

Copia a string:

```text
"Renato Mauro"
      ↓
p[0].nome
```

Não podemos fazer:

```c
p[0].nome = "Renato Mauro";   // ❌
```

porque `nome` é um **array de `char`** (não se atribui array diretamente).

Para receber o nome pelo teclado, podemos utilizar:

```c
fgets(p[0].nome, 40, stdin);
```

---

<a id="15"></a>

# 🔢 15. `argc` e `argv`

Quando executamos:

```bash
./programa arquivo.txt saida.txt
```

temos:

```text
argc = 3
```

Porque **o nome do programa também conta**.

```text
argv[0] → ./programa
argv[1] → arquivo.txt
argv[2] → saida.txt
```

## `argc`

> **argument count** — quantidade de argumentos.

## `argv`

> **argument vector** — array de strings contendo os argumentos.

---

## 📌 Por que verificar `argc`?

Se o programa espera:

```text
programa + arquivo
```

usamos:

```c
if(argc != 2)
```

Se espera:

```text
programa + origem + destino
```

usamos:

```c
if(argc != 3)
```

Isso evita tentar acessar `argv[1]` ou `argv[2]` quando esses argumentos **não foram fornecidos**.

---

<a id="16"></a>

# 📝 16. Exercícios resolvidos

## 16.1 Contar linhas

A ideia é:

> Contar quantas vezes aparece o caractere de quebra de linha `'\n'`.

```c
int c;
int count = 0;

c = fgetc(entrada);

while(c != EOF)
{
    if(c == '\n')
        count++;

    c = fgetc(entrada);
}
```

Se o arquivo for:

```text
Linha 1
Linha 2
Linha 3
```

internamente ele é:

```text
Linha 1\n
Linha 2\n
Linha 3\n
```

Então:

```text
count = 3
```

---

## 16.2 Contar ocorrências de bytes

Um arquivo pode conter **256 valores diferentes de byte**:

### 💡 Por que 256?

Um byte possui **8 bits**:

```text
1 byte = 8 bits

```text
0 ─────────────────────────────── 255
```

Por isso criamos:

```c
int contador[256] = {0};
```

Cada posição representa um possível valor de byte:

```text
contador[0]   → quantas vezes apareceu o byte 0
contador[1]   → quantas vezes apareceu o byte 1
contador[2]   → quantas vezes apareceu o byte 2
...
contador[65]  → quantas vezes apareceu o byte 65
...
contador[255] → quantas vezes apareceu o byte 255
```

### 🔁 `contador[c]++`

Durante a leitura:

```c
c = fgetc(entrada);

while(c != EOF)
{
    contador[c]++;
    c = fgetc(entrada);
}
```

Suponha:

```text
c = 65
```

Então:

```c
contador[65]++;
```

A contagem do byte 65 aumenta em 1. Como em ASCII `65 → 'A'`, isso corresponde à quantidade de letras `A`.

### Imprimindo o resultado

```c
printf("%c: %d\n", i, contador[i]);
```

⚠️ Isso mostra o byte como caractere — ver a seção seguinte sobre a armadilha disso.

---

<a id="17"></a>

# 🔤 17. Bytes e caracteres (ASCII)

Um `char` normalmente representa um byte. Em ASCII, alguns valores são:

| Número | Caractere |
| -----: | :-------: |
|   `48` |    `0`    |
|   `65` |    `A`    |
|   `66` |    `B`    |
|   `67` |    `C`    |
|   `97` |    `a`    |
|   `98` |    `b`    |

Por isso:

```c
printf("%c", 65);
```

mostra:

```text
A
```

Enquanto:

```c
printf("%d", 65);
```

mostra:

```text
65
```

> O valor é o mesmo. **O que muda é o formato de impressão.**

---

## ⚠️ Nem todo byte é uma letra

Existem 256 valores possíveis de byte, mas nem todos representam caracteres imprimíveis. Alguns correspondem a:

* caracteres de controle;
* `\n` (quebra de linha);
* `\t` (tabulação);
* outros valores não visíveis.

Por isso, se o exercício pede **apenas letras**, precisamos filtrar o que será impresso.

---

<a id="18"></a>

# 📍 18. `fseek()`, `ftell()` e acesso direto

Essas funções são a base do **acesso direto** aos arquivos.

## `ftell()`

```c
long pos = ftell(f);
```

Informa a **posição atual** dentro do arquivo.

---

## `fseek()`

```c
fseek(f, posicao, SEEK_SET);
```

**Move** a posição atual.

Por exemplo:

```c
fseek(f, 300, SEEK_SET);
```

significa:

> Vá para o byte 300 do arquivo.

---

## ⚡ Acesso direto

Sem acesso direto (leitura sequencial):

```text
começo
  ↓
registro 1
  ↓
registro 2
  ↓
registro 3
  ↓
registro 4
```

Com `fseek()`:

```text
começo ───────────────────────► registro 4
                                 ↑
                              fseek()
```

Podemos pular **diretamente** para determinada posição, sem ler tudo desde o começo.

---

<a id="19"></a>

# 🔎 19. Registros e busca binária

## Por que arquivos binários importam

Podemos organizar um arquivo como uma sequência de **registros de tamanho conhecido**:

```text
pessoas.dat

[Pessoa 0]
[Pessoa 1]
[Pessoa 2]
...
```

Cada registro possui tamanho `sizeof(Pessoa)`.

Se cada registro tiver 100 bytes:

```text
registro 0 → posição 0
registro 1 → posição 100
registro 2 → posição 200
registro 3 → posição 300
```

Ou seja: **a posição de qualquer registro pode ser calculada**:

```text
posicao = numero_do_registro * sizeof(Registro)
```

Isso permite localizar um registro pelo seu número usando `fseek()`.

---

## Busca binária em arquivo

Se temos um arquivo ordenado:

```text
[registro 0]
[registro 1]
[registro 2]
[registro 3]
[registro 4]
[registro 5]
[registro 6]
```

podemos calcular:

```text
início
fim
meio
```

e usar `fseek()` para ir diretamente ao registro do meio — **sem ler o arquivo inteiro**.

```text
            ARQUIVO ORDENADO
                    │
                    ▼
              ┌───────────┐
              │ busca     │
              │ binária   │
              └─────┬─────┘
                    │
                  fseek()
                    │
                    ▼
            registro desejado
```

Exemplo conceitual com arquivo ordenado por CEP:

```text
[00001]
[00002]
[00003]
[00004]  ← meio
[00005]
[00006]
[00007]

fseek() → vai diretamente até o registro
```

Isso conecta toda a matéria:

```text
Manipulação de arquivos
          ↓
Arquivos binários
          ↓
Registros
          ↓
Acesso direto
          ↓
Ordenação
          ↓
Busca binária
```

---

<a id="20"></a>

# 🧠 20. Mapa mental e resumo final

## Visão geral da matéria

```text
                 ESTRUTURA DE ARQUIVOS
                          │
          ┌───────────────┴───────────────┐
          │                               │
       MEMÓRIA                         ARQUIVO
          │                               │
     ┌────┴────┐                     ┌────┴────┐
     │         │                     │         │
   struct    array                 texto    binário
     │         │                               │
     └────┬────┘                            registros
          │                                     │
       ponteiros                           fread/fwrite
          │                                     │
        sizeof                                  │
          │                                     │
        memset                                  │
          │                                     │
          └──────────────┬──────────────────────┘
                         │
                   acesso direto
                         │
                   fseek / ftell
                         │
                ┌────────┴────────┐
                │                 │
            ordenação       busca binária
```

---

## 📚 O que decorar de cada função

| Função     | O que faz                      |
| ---------- | ------------------------------ |
| `fopen()`  | Abre um arquivo (retorna `FILE *`) |
| `fclose()` | Fecha um arquivo               |
| `fgetc()`  | Lê 1 byte                      |
| `fputc()`  | Escreve 1 byte                 |
| `fread()`  | Lê vários itens (arquivo → memória) |
| `fwrite()` | Escreve vários itens (memória → arquivo) |
| `fseek()`  | Move a posição no arquivo      |
| `ftell()`  | Informa a posição atual        |
| `memset()` | Preenche uma região da memória |
| `sizeof()` | Informa o tamanho em bytes     |
| `strcpy()` | Copia uma string               |

### Assinaturas essenciais

```c
FILE *f = fopen("arquivo", "rb");
fclose(f);

c = fgetc(f);
fputc(c, f);

fread(destino, tamanho, quantidade, f);
fwrite(origem,  tamanho, quantidade, f);

fseek(f, posicao, SEEK_SET);
ftell(f);
```

---

## ⚠️ As principais coisas que não posso confundir

### `FILE *f`

`f` é um **ponteiro para `FILE`**.

```text
f  ─────────► FILE
```

* `f` → o endereço armazenado no ponteiro
* `*f` → acessar o `FILE` naquele endereço

### `fopen()` retorna `FILE *`

Por isso: `f = fopen(...)` ✅ e não `*f = fopen(...)` ❌

### `fclose()` recebe `FILE *`

Por isso: `fclose(f);` ✅ e não `fclose(*f);` ❌

### Direção dos dados

```text
fread
ARQUIVO ─────────► MEMÓRIA

fwrite
MEMÓRIA ─────────► ARQUIVO
```

### Um byte x vários itens

```text
fgetc  → 1 byte
fputc  → 1 byte

fread  → vários itens
fwrite → vários itens
```

### `EOF`

Não é um caractere comum do arquivo. É um valor especial que indica fim de leitura.

### `int c`

`fgetc()` usa `int` porque precisa representar tanto os valores dos bytes quanto `EOF`.

### `sizeof(Pessoa)` x `1000 * sizeof(Pessoa)`

* `sizeof(Pessoa)` → tamanho de **uma** Pessoa em bytes
* `1000 * sizeof(Pessoa)` → tamanho total de **1000** Pessoas em bytes

### Retorno do `fread`

É a quantidade de **itens**, não de bytes.

### `argc` / `argv`

* `argc` → quantidade de argumentos (inclui o nome do programa)
* `argv` → array com os argumentos

---

## 🎯 Macetes finais

```text
┌────────────────────────────────────────────┐
│              ARQUIVO                       │
│                                            │
│  fopen() → abre                            │
│     ↓                                      │
│  fread/fgetc → lê                          │
│     ↓                                      │
│  fwrite/fputc → escreve                    │
│     ↓                                      │
│  fclose() → fecha                          │
└────────────────────────────────────────────┘
```

### Ponteiro

```text
int *p

p  → endereço
*p → valor naquele endereço
```

### Modos

```text
r → read
w → write
a → append
+ → leitura e escrita
b → binary
```

### Parâmetros de `fread` / `fwrite`

```text
fread(onde colocar, tamanho de cada item, quantidade, arquivo)

fwrite(o que gravar, tamanho de cada item, quantidade, arquivo)
```

A ideia principal é sempre:

```text
ONDE?
TAMANHO?
QUANTOS?
QUAL ARQUIVO?
```

---

# 🚀 Por que isso importa?

Manipulação de arquivos não é apenas "abrir um `.txt`".

Ela é a base para trabalhar com **grandes quantidades de dados armazenados permanentemente**.

A partir desses conceitos aparecem:

```text
arquivos
   ↓
registros
   ↓
arquivos binários
   ↓
acesso direto
   ↓
índices
   ↓
ordenação
   ↓
busca binária
```

Ou seja: os primeiros exercícios parecem simples, mas estão preparando o terreno para a parte mais importante de **Estrutura de Arquivos**.
