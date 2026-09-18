# 📁 Arquivos em C — Resumo de Caderno

## 1. Conceitos principais

### 1.1 Arquivo e posição atual

```c
FILE *f;
```

`f` é um ponteiro para o `FILE` que controla o arquivo.

Todo arquivo aberto possui uma **posição atual**.

```text
fgetc / fread → lê e AVANÇA
fseek         → MOVE a posição
ftell         → informa a posição
rewind        → volta ao início
```

---

### 1.2 `struct` e registros

Uma `struct` agrupa vários campos:

```c
typedef struct {
    char nome[20];
    char cep[8];
} Endereco;
```

Quando os registros têm **tamanho fixo**, podemos converter:

```text
bytes ÷ sizeof(Tipo) = quantidade de registros

registro × sizeof(Tipo) = posição em bytes
```

Exemplo:

```text
sizeof(Endereco) = 300

registro 0 → byte 0
registro 1 → byte 300
registro 2 → byte 600
```

⚠️ Use `sizeof(Tipo)` em vez de assumir o tamanho manualmente, pois pode existir *padding*.

Vetores começam em 0:

```text
1º → índice 0
2º → índice 1
nº → índice n - 1
```

---

### 1.3 Ponteiros: `*`, `&`, `.` e `->`

```c
Endereco e;
```

```text
e   → própria struct
&e  → endereço da struct
```

```c
Endereco *e;
```

```text
e   → endereço
*e  → conteúdo apontado
```

Acesso aos campos:

```c
e.cep       // struct
e->cep      // ponteiro para struct
```

`->` equivale a:

```c
(*e).cep
```

### Regra para `fread`

```text
struct simples → &e
ponteiro       → e
array          → nome do array
```

---

### 1.4 Bytes × registros

`fseek` trabalha em **bytes**.

Para ir ao registro `n`:

```c
fseek(f, n * sizeof(Endereco), SEEK_SET);
```

⚠️ Não:

```c
fseek(f, n, SEEK_SET);
```

porque `n` representa registros, enquanto `fseek` usa bytes.

Para descobrir a quantidade de registros:

```c
fseek(f, 0, SEEK_END);

long bytes = ftell(f);
long qtd = bytes / sizeof(Endereco);

rewind(f);
```

`SEEK_END` aponta para o **fim do arquivo**, não para o último registro.

Para ler o último:

```c
fseek(f, -(long)sizeof(Endereco), SEEK_END);
fread(&e, sizeof(Endereco), 1, f);
```

`ftell()` retorna `long`.

---

### 1.5 Memória

```c
Endereco e;
```

→ espaço para **1 registro**.

```c
Endereco *e;

e = malloc(qtd * sizeof(Endereco));
```

→ espaço para vários registros.

```text
malloc → reserva memória
free   → libera memória
```

Todo `malloc` deve:

```text
1. ser testado com NULL
2. ser liberado com free
```

Exemplo:

```c
e = malloc(qtd * sizeof(Endereco));

if(e == NULL){
    return 1;
}

/* usa */

free(e);
```

Diferença:

```text
FILE * → fopen / fclose
memória → malloc / free
```

`sizeof(Tipo)` = tamanho de **um item**, não do arquivo.

`memset` preenche memória em bytes:

```c
memset(v, 0, tamanho);
```

---

### 1.6 `EOF` × `feof`

Não são a mesma coisa:

```text
EOF      → valor especial retornado por fgetc
feof(f)  → verifica se ocorreu fim de arquivo
```

`EOF` não é um byte gravado no arquivo.

Para `fgetc`:

```c
int c;
```

e não `char`.

### Pegadinha do `feof`

`feof()` só fica verdadeiro **depois que uma leitura tenta passar do fim**.

Padrão:

```text
LER
 ↓
TESTAR
 ↓
USAR
 ↓
LER DE NOVO
```

---

### 1.7 `argc` e `argv`

Servem para receber argumentos do terminal.

```bash
./programa origem.dat destino.dat
```

```text
argc = 3

argv[0] → programa
argv[1] → origem.dat
argv[2] → destino.dat
```

O nome do programa conta.

Antes de usar:

```c
if(argc != 3){
    return 1;
}
```

Se o nome do arquivo estiver fixo no código:

```c
fopen("cep.dat", "rb");
```

não precisa de `argc`/`argv`.

---

### 1.8 Bytes e ASCII

```text
1 byte = 8 bits
       = 256 valores
       = 0 a 255
```

ASCII associa números a caracteres:

```text
65 → 'A'
97 → 'a'
48 → '0'
```

```c
printf("%c", 65);  // A
printf("%d", 65);  // 65
```

O valor é o mesmo; muda a interpretação.

---

# 2. Funções principais

## `fopen` / `fclose`

```c
FILE *f = fopen("arquivo.dat", "rb");

if(f == NULL){
    return 1;
}

fclose(f);
```

Modos:

```text
rb  → lê
wb  → escreve / cria / APAGA
r+b → lê + escreve
ab  → escreve no final
```

⚠️ Todo `fopen` deve ter `fclose`.

---

## `fgetc` / `fputc`

```c
int c = fgetc(f);
```

Lê **1 byte** e retorna:

```text
byte
ou
EOF
```

```c
fputc(c, f);
```

Escreve 1 byte.

Padrão:

```c
int c;

c = fgetc(f);

while(c != EOF){
    /* usa c */
    c = fgetc(f);
}
```

---

## `fread` / `fwrite`

```text
fread  → arquivo → memória
fwrite → memória → arquivo
```

Sintaxe:

```c
fread(destino, sizeof(Tipo), quantidade, arquivo);

fwrite(origem, sizeof(Tipo), quantidade, arquivo);
```

Pense:

```text
ONDE?
TAMANHO?
QUANTOS?
QUAL ARQUIVO?
```

O retorno é a quantidade de **itens**, não bytes.

Exemplo:

```c
fread(v, sizeof(Endereco), 100, f);
```

→ se leu tudo, retorna `100`.

Depois de `fread`, a posição do arquivo avança.

---

## `fseek` / `ftell` / `rewind`

```c
fseek(f, deslocamento, origem);
```

O deslocamento é em bytes.

```text
SEEK_SET → início
SEEK_CUR → posição atual
SEEK_END → fim
```

```c
long pos = ftell(f);
```

→ posição em bytes.

```c
rewind(f);
```

→ volta ao início.

---

## `malloc` / `free` / `sizeof`

```c
Endereco *e = malloc(qtd * sizeof(Endereco));
```

`malloc` recebe quantidade em **bytes**.

```c
free(e);
```

libera a memória.

```c
sizeof(Endereco)
```

→ tamanho de um `Endereco`.

---

## Strings

```c
strcpy(destino, origem);
strncpy(destino, origem, n);
```

Arrays não recebem string com `=`:

```c
p.nome = "Renato";        // ❌
strcpy(p.nome, "Renato"); // ✅
```

Comparação:

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
strncmp(e1.cep, e2.cep, 8);
```

Criar nome:

```c
sprintf(nome, "cep_%d.dat", i);
```

Imprimir campo fixo:

```c
printf("%.8s", e.cep);
```

---

## `qsort`

```c
qsort(v, qtd, sizeof(Tipo), compara);
```

Ordem dos parâmetros:

```text
ONDE
QUANTOS
TAMANHO
COMPARADOR
```

⚠️ `compara` vai **sem `()`**.

O tipo precisa ser consistente:

```text
qsort(... sizeof(Tipo), compara)
                 ↓
compara → (Tipo*)
```

---

# 3. Pegadinhas essenciais

### 📁 Arquivos

```text
fopen → FILE* ou NULL
fclose(f), não fclose(*f)
wb → apaga conteúdo anterior
ab → adiciona no final
FILE* → fopen/fclose
```

### 📖 Leitura

```text
fgetc → int
EOF → não é byte do arquivo
fread/fwrite → retornam itens
fread → lê e avança
```

### 📍 Posição

```text
fseek → bytes
registro n → n * sizeof(Tipo)
ftell → long
%ld → long
SEEK_END → fim, não último registro
```

### 🧠 Memória

```text
malloc → reserva
free → libera
malloc → testar NULL
Endereco e → 1 registro
Endereco *e → vários registros
```

### 🔤 Struct / ponteiros

```text
struct → .
ponteiro → ->
&e → endereço
*e → conteúdo apontado
```

### 🔤 Strings

```text
array não recebe string com =
strcpy/strncpy → copiar
strncmp → comparar
campo fixo pode não ter '\0'
```

### 🔢 Ordenação

```text
qsort(v, qtd, sizeof(Tipo), compara)

compara sem ()
sizeof e casting devem corresponder ao tipo
```

---

# 4. Ideias que preciso saber explicar

## Busca sequencial

```text
ler
 ↓
comparar
 ↓
achou? → para
não? → próximo
```

Se o arquivo estiver ordenado:

```text
ANTES  → continua
IGUAL  → faz
DEPOIS → break
```

---

## Busca binária

Arquivo precisa estar **ordenado**.

```text
início ─────── meio ─────── fim
                ↓
             fseek
                ↓
             fread
                ↓
            comparar
```

```text
igual → achou
maior → direita
menor → esquerda
```

Cada tentativa faz um novo:

```c
fseek(...)
```

---

## Índice

Índice =

```text
CHAVE + POSIÇÃO ORIGINAL
```

Exemplo:

```text
arquivo:

posição 0 → 22222222
posição 1 → 11111111
posição 2 → 55555555

índice ordenado:

11111111 → 1
22222222 → 0
55555555 → 2
```

Ordenar o índice **não muda as posições do arquivo original**.

Fluxo:

```text
buscar no índice
      ↓
encontrar posição
      ↓
fseek no arquivo original
      ↓
fread
```

---

## Ordenação externa

Usada quando o arquivo **não cabe inteiro na memória**.

```text
arquivo grande
      ↓
    dividir
      ↓
 qsort cada parte
      ↓
partes ordenadas
      ↓
intercalar 2 a 2
      ↓
repetir
      ↓
arquivo final
```

Divisão:

```text
divisao = quantidade / PARTES
resto   = quantidade % PARTES
```

As primeiras `resto` partes recebem 1 registro a mais.

Memória suficiente para a maior parte:

```c
malloc((divisao + 1) * sizeof(Endereco));
```

Intercalação:

```text
ler atual de A
ler atual de B
      ↓
comparar
      ↓
gravar o menor
      ↓
ler novamente daquele arquivo
```

Cada intercalação:

```text
2 arquivos → 1 arquivo
```

Logo:

```text
intercalações = PARTES - 1
```

Com 8 partes:

```text
8 → 4 → 2 → 1
```

São **7 intercalações** no total.

---

# 🧠 Ideia central

A matéria gira muito em torno de:

```text
REGISTROS DE TAMANHO FIXO
          ↓
     sizeof(Tipo)
          ↓
 ┌────────┴────────┐
 ↓                 ↓
bytes          registros
 ↓                 ↓
fseek           quantidade
 ↓
acesso direto
```

Por isso conseguimos fazer:

```text
bytes / sizeof(Tipo) = quantidade

registro × sizeof(Tipo) = posição em bytes
```

E isso permite:

```text
fseek
  ↓
busca binária
  ↓
índice
```

ou:

```text
quantidade
    ↓
dividir
    ↓
ordenar partes
    ↓
intercalar
    ↓
ordenação externa
```

### Pergunta-chave antes de programar

```text
É byte por byte?
→ fgetc

É registro por registro?
→ fread

Arquivo inteiro cabe na memória?
→ malloc + qsort

Arquivo ordenado e busca específica?
→ busca binária

Arquivo não ordenado, mas precisa buscar rápido?
→ índice

Arquivo não cabe na memória?
→ ordenação externa
```
