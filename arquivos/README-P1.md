# 📁 Estrutura de Arquivos em C — Material de Prova

> Mesmo conteúdo do resumo anterior, reorganizado em 5 partes.
> **Parte 1** é a que vai para a folha de cola.

| Parte | O que tem | Quando usar |
| --- | --- | --- |
| **1. Funções** | Ficha de cada função: o que faz, parâmetros, retorno, cuidado | Folha de cola |
| **2. Conceitos** | Ponteiros, struct, memória, as duas contas | Entender o "porquê" |
| **3. Programas** | As receitas completas, passo a passo | Treinar para a prova |
| **4. Pegadinhas** | Checklist do que costumo errar | Revisão da véspera |
| **5. Folha de cola** | Tudo condensado, pronto para copiar | Montar a cola |

Marcadores usados: **⚠️ cuidado** (pegadinha) · **🎯 ponto fraco** (onde costumo errar)

---

## 📑 Sumário

- [Parte 1 — Funções principais](#parte-1--funções-principais)
  - [1.1 Abrir e fechar](#11-abrir-e-fechar-fopen-e-fclose)
  - [1.2 Ler e escrever 1 byte](#12-ler-e-escrever-1-byte-fgetc-e-fputc)
  - [1.3 Ler e escrever registros](#13-ler-e-escrever-registros-fread-e-fwrite)
  - [1.4 Posição no arquivo](#14-posição-no-arquivo-fseek-ftell-rewind-feof)
  - [1.5 Memória](#15-memória-malloc-free-sizeof-memset)
  - [1.6 Strings de tamanho fixo](#16-strings-strcpy-strncpy-strncmp-sprintf-printf)
  - [1.7 Ordenação](#17-ordenação-qsort-e-compara)
- [Parte 2 — Conceitos](#parte-2--conceitos)
- [Parte 3 — Programas](#parte-3--programas-as-receitas)
- [Parte 4 — Pegadinhas](#parte-4--checklist-de-pegadinhas)
- [Parte 5 — Folha de cola](#parte-5--folha-de-cola)

---

# Parte 1 — Funções principais

Cada função segue o mesmo formato: **o que faz → como escreve → recebe → devolve → cuidado**.

## 1.1 Abrir e fechar: `fopen` e `fclose`

### `fopen` — abre um arquivo

```c
FILE *f = fopen(nome, modo);
```

- **Recebe:** o nome do arquivo (texto) e o modo de abertura.
- **Devolve:** um `FILE *` (ponteiro para o arquivo aberto) ou **`NULL`** se falhar.

```c
FILE *f = fopen("cep.dat", "rb");
if (f == NULL) {                       // ou: if (!f)
    printf("Erro ao abrir arquivo\n");
    return 1;
}
```

**Modos:**

| Modo | Lê | Escreve | Cria se não existir | Apaga o conteúdo |
| --- | :-: | :-: | :-: | :-: |
| `rb` | ✅ | ❌ | ❌ (precisa existir) | ❌ |
| `wb` | ❌ | ✅ | ✅ | ⚠️ **SIM** |
| `a` | ❌ | ✅ (no final) | ✅ | ❌ |
| `r+b` | ✅ | ✅ | ❌ | ❌ |
| `w+` | ✅ | ✅ | ✅ | ⚠️ **SIM** |

Macete: `r` = read · `w` = write · `a` = append · `+` = lê **e** escreve · `b` = binary.

⚠️ **Cuidados**
- `w` **apaga** um arquivo que já existe.
- Arquivo de dados (`.dat`, structs) → sempre **binário** (`rb`, `wb`, `r+b`). No Windows o modo texto altera as quebras de linha.
- 🎯 `f = fopen(...)` ✅ — `*f = fopen(...)` ❌ (explicação na [Parte 2](#21-ponteiros-f-x-f)).

### `fclose` — fecha o arquivo

```c
fclose(f);
```

- **Recebe:** o `FILE *` (é `fclose(f)`, **nunca** `fclose(*f)`).
- **Faz:** avisa "terminei com esse arquivo" e garante que o que estava no buffer foi gravado no disco.

⚠️ **Cuidados**
- Todo `fopen` precisa do seu `fclose`.
- 🎯 Se o **segundo** `fopen` falhar, feche o **primeiro** antes do `return`, senão o `fclose` do final nunca roda:

```c
entrada = fopen(argv[1], "rb");
if (!entrada) return 1;

saida = fopen(argv[2], "wb");
if (!saida) {
    fclose(entrada);    // ← obrigatório aqui
    return 1;
}
```

- Na ordenação externa, as partes são **reabertas** depois, por isso precisam ser fechadas logo após gravadas.

---

## 1.2 Ler e escrever 1 byte: `fgetc` e `fputc`

### `fgetc` — lê 1 byte (ARQUIVO → MEMÓRIA)

```c
int c = fgetc(f);
```

- **Devolve:** o byte lido (0 a 255) **ou** `EOF` quando não há mais dados.

### `fputc` — escreve 1 byte (MEMÓRIA → ARQUIVO)

```c
fputc(c, f);
```

- **Recebe:** o byte e o arquivo (atenção à ordem: **primeiro o byte**, depois o arquivo).

⚠️ **Cuidados**
- 🎯 Use **`int c`**, não `char c`: o `fgetc` precisa devolver 256 valores de byte **mais** o `EOF`, e só o `int` comporta tudo.
- `EOF` (*End Of File*) **não é um caractere gravado no arquivo**. É um valor especial que a função devolve quando acabou.

---

## 1.3 Ler e escrever registros: `fread` e `fwrite`

```text
fread  → ARQUIVO ──► MEMÓRIA
fwrite → MEMÓRIA ──► ARQUIVO
```

### `fread` — lê vários itens de uma vez

```c
fread(destino, sizeof(Tipo), quantidade, f);
```

### `fwrite` — grava vários itens de uma vez

```c
fwrite(origem, sizeof(Tipo), quantidade, f);
```

**Os 4 parâmetros (iguais nas duas) — pergunta mental: ONDE? TAMANHO? QUANTOS? QUAL ARQUIVO?**

| # | Parâmetro | No `fread` | No `fwrite` |
| - | --- | --- | --- |
| 1 | endereço | onde **colocar** o que foi lido | de onde **pegar** o que vai gravar |
| 2 | `sizeof(Tipo)` | tamanho de **um** item | tamanho de **um** item |
| 3 | quantidade | quantos itens ler | quantos itens gravar |
| 4 | `FILE *` | arquivo já aberto | arquivo já aberto |

- **Devolve:** a quantidade de **ITENS** lidos/gravados.

**Exemplos:**

```c
Endereco e;                                    // uma struct
fread(&e, sizeof(Endereco), 1, f);             // lê 1 → precisa do &

Endereco *v = malloc(qtd * sizeof(Endereco));  // um bloco
fread(v, sizeof(Endereco), qtd, f);            // lê qtd → v já é endereço

Pessoa p[1000];                                // um array
fwrite(p, sizeof(Pessoa), 1000, f);            // p já é endereço

if (fread(v, sizeof(Endereco), qtd, f) == qtd) // conferir se leu tudo
    printf("Lido = OK\n");
```

⚠️ **Cuidados**
- 🎯 **Retorno = itens, não bytes.** 300 Pessoas de 52 bytes → devolve `300` ✅, não `15600` ❌.
- 🎯 **`&` só em variável simples/struct.** Array e ponteiro já são endereço.
- `fread` **não abre arquivo**: `fread(&e, sizeof(Endereco), 1, "cep_0.dat");` ❌
- `fread` lê **a partir da posição atual** e **avança** a posição. Chamadas seguidas leem registros seguidos.
- `fread` copia os bytes do registro **inteiro**; quem dá significado aos bytes é a `struct`.

---

## 1.4 Posição no arquivo: `fseek`, `ftell`, `rewind`, `feof`

Todo arquivo aberto tem uma **posição atual** (uma "cabeça de leitura") que anda sozinha a cada leitura/escrita.

### `fseek` — MOVE a posição

```c
fseek(f, deslocamento_em_bytes, origem);
```

| Origem | Conta a partir de | Exemplo | Significa |
| --- | --- | --- | --- |
| `SEEK_SET` | início | `fseek(f, 300, SEEK_SET)` | vá para o byte 300 |
| `SEEK_CUR` | posição atual | `fseek(f, -2, SEEK_CUR)` | volte 2 bytes |
| `SEEK_END` | final | `fseek(f, 0, SEEK_END)` | vá para o fim |

### `ftell` — INFORMA a posição

```c
long pos = ftell(f);    // bytes desde o início do arquivo
```

### `rewind` — VOLTA ao começo

```c
rewind(f);
```

### `feof` — o arquivo JÁ CHEGOU ao fim?

```c
while (!feof(f)) { ... }   // "enquanto não chegou ao fim"
```

**Combinação mais usada — tamanho do arquivo e quantidade de registros:**

```c
fseek(f, 0, SEEK_END);               // vai para o fim
long bytes = ftell(f);               // posição no fim = tamanho do arquivo
long qtd = bytes / sizeof(Endereco); // quantidade de registros
rewind(f);                           // volta para o começo
```

⚠️ **Cuidados**
- `fseek` **só move** (não lê). `ftell` **só informa** (não move). `fread` **lê e avança** (600 + 300 lidos → 900).
- 🎯 `fseek` trabalha em **BYTES**, nunca em número de registro: `fseek(f, n * sizeof(Endereco), SEEK_SET)`.
- 🎯 **Esquecer o `rewind`** depois do `SEEK_END` → o próximo `fread` começa no fim e não lê nada.
- **`fseek` escolhe ONDE ler; `fread` lê O QUE está lá.**
- `EOF` × `feof`:

| | O que é | Uso |
| --- | --- | --- |
| `EOF` | um **valor** devolvido pelo `fgetc` | `if (c == EOF)` |
| `feof(f)` | uma **função** que testa se o arquivo chegou ao fim | `while (!feof(f))` |

- 🎯 `feof` só fica verdadeiro **depois** que uma leitura falha. Por isso a regra é: **ler → testar → usar → ler de novo** (detalhes na [receita da intercalação](#35-ordenação-externa)).

---

## 1.5 Memória: `malloc`, `free`, `sizeof`, `memset`

### `malloc` — reserva memória em tempo de execução

```c
Endereco *e = malloc(qtd * sizeof(Endereco));
Endereco *e = (Endereco*) malloc(qtd * sizeof(Endereco));   // com casting (opcional em C)
```

- **Recebe:** quantos **bytes** reservar.
- **Devolve:** o endereço do início do bloco (tipo `void *`) ou **`NULL`** se faltar memória.
- O bloco vem **vazio**; quem preenche é o `fread`.

```c
if (e == NULL) {
    fprintf(stderr, "Erro ao alocar memoria\n");
    fclose(f);
    return 1;
}
```

### `free` — devolve a memória

```c
free(e);    // todo malloc tem o seu free
```

### `sizeof` — tamanho em bytes

```text
sizeof(Endereco)        → bytes de UM registro (300)  — NÃO é o tamanho do arquivo
1000 * sizeof(Pessoa)   → bytes de 1000 Pessoas (52 × 1000 = 52000)
```

### `memset` — preenche uma região de memória

```c
memset(endereco, valor, quantidade_de_BYTES);
memset(p, 0, 1000 * sizeof(Pessoa));
memset(p, 0, sizeof(p));      // p é array local → sizeof(p) = bytes do array todo
Pessoa p[1000] = {0};         // jeito mais simples de zerar um array
```

⚠️ **Cuidados**
- Sempre testar `malloc == NULL`.
- `FILE *` **nunca** leva `malloc`/`free` (quem cuida dele é `fopen`/`fclose`).
- Array local **não vem zerado**: pode ter lixo de memória.
- `memset` preenche qualquer região; `= {0}` é inicialização de array.

---

## 1.6 Strings: `strcpy`, `strncpy`, `strncmp`, `sprintf`, `printf`

### `strcpy` / `strncpy` — copiam texto para um `char[]`

```c
strcpy(p[0].nome, "Renato Mauro");     // copia até o '\0'
strncpy(indice[i].cep, e.cep, 8);      // copia exatamente 8 caracteres
fgets(p[0].nome, 40, stdin);           // lê do teclado
```

🎯 Array **não se atribui**: `p[0].nome = "Renato Mauro";` ❌

### `strncmp` — compara os primeiros N caracteres

```c
int r = strncmp(a, b, 8);
```

| Resultado | Significa |
| --- | --- |
| `r < 0` | `a` vem **antes** de `b` |
| `r == 0` | iguais |
| `r > 0` | `a` vem **depois** de `b` |

### `sprintf` — monta um texto dentro de um `char[]`

```c
char nome[20];
sprintf(nome, "cep_%d.dat", i);    // i = 3 → "cep_3.dat"
```

### `printf` com precisão — imprime campo de tamanho fixo

```c
printf("%.8s\n", e.cep);           // imprime no máximo 8 caracteres
printf("%c", 65);                  // A
printf("%d", 65);                  // 65  → mesmo valor, formato diferente
```

⚠️ **Cuidado:** os campos da struct (`cep[8]`, `logradouro[72]`...) têm tamanho fixo e **não têm `'\0'` garantido**. Por isso usamos **`strncmp`/`strncpy` com o tamanho** e **`%.Ns` no `printf`**. Sem isso, a função lê além do campo.

---

## 1.7 Ordenação: `qsort` e `compara`

### `qsort` — ordena um bloco na memória

```c
qsort(onde, quantidade, sizeof(Tipo), compara);
```

| # | Parâmetro | Exemplo |
| - | --- | --- |
| 1 | onde começam os itens | `e` |
| 2 | quantos itens | `qtd` |
| 3 | tamanho de **um** item | `sizeof(Endereco)` |
| 4 | função de comparação (**sem parênteses**) | `compara` |

```c
qsort(e,      qtd, sizeof(Endereco),  comparaEndereco);   // ordenando Endereco
qsort(indice, qtd, sizeof(IndiceCep), comparaIndice);     // ordenando IndiceCep
```

### `compara` — função que **você** escreve

```c
int compara(const void *e1, const void *e2) {
    return strncmp(((Endereco*)e1)->cep,
                   ((Endereco*)e2)->cep, 8);
}
```

Lendo por partes:

```text
const void *e1          → o qsort é genérico, então manda um ponteiro "sem tipo"
(Endereco*)e1           → casting: "trate como ponteiro para Endereco"
((Endereco*)e1)->cep    → acessa o campo cep (-> porque é ponteiro)
strncmp(..., ..., 8)    → devolve <0, 0 ou >0, que é exatamente o que o qsort espera
```

Chave **numérica** (não dá para usar `strncmp`):

```c
int comparaNumero(const void *a, const void *b) {
    long x = ((Registro*)a)->valor, y = ((Registro*)b)->valor;
    if (x < y) return -1;
    if (x > y) return  1;
    return 0;
}
```

⚠️ **Cuidados**
- 🎯 O `sizeof` e o casting dentro do `compara` são **do tipo que está sendo ordenado naquela chamada**. Errar corrompe os dados sem aviso.
- 🎯 Quem chama `compara` (e escolhe `e1` e `e2`) é o **`qsort`**. Você só entrega o nome da função:
  `qsort(..., compara)` ✅ (entrega a função) · `compara()` ❌ (executaria agora).
- Ordem decrescente → inverter os operandos.

---

# Parte 2 — Conceitos

## 2.1 Ponteiros: `f` x `*f`

`FILE` é um tipo da `stdio.h` que guarda o controle de um arquivo aberto (posição, buffer, erro, fim). Nunca mexemos nos campos dele, só usamos as funções.

```c
FILE *f;    // f é um PONTEIRO para FILE → guarda um endereço
```

Mesma lógica de `int`:

```text
int x = 10;
int *p = &x;

p  → endereço de x  (ex.: 1000)
*p → valor de x     (10)
```

| Expressão | Tipo | Significa |
| --- | --- | --- |
| `f` | `FILE *` | o endereço guardado |
| `*f` | `FILE` | a estrutura naquele endereço |

```text
f ───────► FILE        (f não aponta para si mesmo)
```

O `*` tem dois usos:

```c
FILE *f;    // na DECLARAÇÃO → "f é ponteiro"
*f          // numa EXPRESSÃO → "vá até o endereço"
```

**Por isso:** `fopen` devolve `FILE *` e `f` é `FILE *` → `f = fopen(...)`. Já `*f` é `FILE`, então `*f = fopen(...)` não bate. O mesmo vale para `fclose(f)`.

## 2.2 Struct e typedef

```c
typedef struct _Endereco Endereco;   // apelido: escrevo Endereco em vez de struct _Endereco

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];      // CHAVE de ordenação e busca
    char lixo[2];     // espaço + quebra de linha do formato do arquivo
};                    // 72×4 + 2 + 8 + 2 = 300 bytes
```

- O `lixo[2]` existe para a struct ter exatamente os 300 bytes do registro no arquivo.
- ⚠️ Use sempre `sizeof(Endereco)`: o compilador pode inserir bytes de alinhamento (*padding*).

## 2.3 🎯 `Tipo x;` ou `Tipo *x;`?

Pergunta que decide:

| Situação | Declaração | Precisa de `malloc`? | Acesso ao campo | No `fread` |
| --- | --- | :-: | --- | --- |
| **Um** registro por vez (lê, usa, sobrescreve) | `Endereco e;` | ❌ | `e.cep` | `&e` |
| **Vários** registros ao mesmo tempo, quantidade só conhecida ao rodar | `Endereco *e;` | ✅ | `e->cep` ou `e[i].cep` | `e` |
| Arquivo | `FILE *f;` | ❌ nunca (usa `fopen`) | — | — |

**Exemplo real — programa do índice usa os dois:**

```c
Endereco e;            // 1 registro temporário, reaproveitado a cada volta
IndiceCep *indice;     // TODAS as entradas, precisam ficar vivas para o qsort e a busca

indice = malloc(qtd * sizeof(IndiceCep));
for (i = 0; i < qtd; i++) {
    fread(&e, sizeof(Endereco), 1, f);   // &e porque e é struct
    strncpy(indice[i].cep, e.cep, 8);    // e.cep com ponto
    indice[i].posicao = i;
}
```

```text
volta 1: registro 0 → e
volta 2: registro 1 → e   (sobrescreve; tudo bem, a chave já foi copiada)
```

Na intercalação é igual: `Endereco ea, eb;` sem `malloc`, porque só importa o registro **atual** de cada arquivo.

Por que não `Endereco e[1000];`? Porque o arquivo pode ter 1.000.000 de registros, e só se sabe o tamanho **depois** de medir o arquivo.

## 2.4 `.` x `->` e `&` x `*`

```text
Tenho a struct      → e.cep
Tenho um ponteiro   → e->cep       (é o mesmo que (*e).cep)
Bloco apontado      → e[i].cep

Endereco e;     e = struct      &e = endereço da struct
Endereco *e;    e = endereço    *e = struct naquele endereço

Pessoa p[1000]; p = endereço do início do array    p[0] = primeira Pessoa
```

## 2.5 🎯 As duas contas de tudo

Só funcionam porque **todos os registros têm o mesmo tamanho**:

```text
BYTES ──── ÷ sizeof ────► REGISTROS    "quantos registros cabem?"
REGISTROS ── × sizeof ──► BYTES        "em que byte começa esse registro?"
```

Exemplo com registro de 300 bytes e arquivo de 300.000 bytes:

```text
300.000 ÷ 300 = 1.000 registros
registro 499 → 499 × 300 = 149.700 → fseek(f, 149700, SEEK_SET)
```

🎯 `meio`, `i`, `posicao` são **números de registro**. Só viram bytes na hora do `fseek`.

## 2.6 Bytes e ASCII

```text
1 byte = 8 bits → 2⁸ = 256 valores possíveis (0 a 255)
```

| Número | 48 | 65 | 66 | 97 | 98 |
| --- | --- | --- | --- | --- | --- |
| Caractere | `'0'` | `'A'` | `'B'` | `'a'` | `'b'` |

🎯 Nem todo byte é letra: existem `\n`, `\t` e caracteres de controle invisíveis.

## 2.7 `argc` e `argv`

```bash
./programa arquivo.txt saida.txt
```

```text
argc = 3               ← o nome do programa CONTA
argv[0] = "./programa"
argv[1] = "arquivo.txt"
argv[2] = "saida.txt"
```

```c
if (argc != 3) {       // programa + origem + destino   (argc != 2 → programa + 1 argumento)
    fprintf(stderr, "USO: %s origem destino\n", argv[0]);
    return 1;
}
```

⚠️ Conferir `argc` **antes** de usar `argv[1]`, `argv[2]`.

---

# Parte 3 — Programas (as receitas)

Visão geral:

| Receita | Ideia | Memória usada |
| --- | --- | --- |
| 3.1 Ler byte a byte | `fgetc` em laço | 1 byte |
| 3.2 Ordenar arquivo inteiro | `fread` tudo → `qsort` → `fwrite` | **todos** os registros |
| 3.3 Busca binária no arquivo | `fseek` no meio → `fread` → compara → repete | 1 registro |
| 3.4 Índice | guarda (chave, posição) → `qsort` → busca → `fseek` | só o índice |
| 3.5 Ordenação externa | divide → ordena partes → intercala 2 a 2 | 1 parte por vez |

```text
arquivos → binários → registros fixos → acesso direto (fseek)
        → ordenação (qsort) → busca binária → índice → ordenação externa
```

## 3.1 Ler byte a byte (copiar, contar linhas, contar bytes)

**Um molde só.** Muda apenas a linha do meio:

```c
int c;
c = fgetc(entrada);          // 1º: lê o PRIMEIRO byte antes de testar
while (c != EOF) {           // testa o que acabou de ler
    /* TAREFA */             // usa
    c = fgetc(entrada);      // 2º: lê o PRÓXIMO e volta ao teste
}
```

| Exercício | O que vai em `/* TAREFA */` | Antes do laço |
| --- | --- | --- |
| Copiar arquivo | `fputc(c, saida);` | abrir `entrada` e `saida` |
| Contar linhas | `if (c == '\n') count++;` | `int count = 0;` |
| Contar cada byte | `contador[c]++;` | `int contador[256] = {0};` |

- Sem o 1º `fgetc`, o `while` testaria um `c` vazio. Sem o 2º, `c` nunca muda e o laço não para.
- Contar linhas: `"Linha 1\nLinha 2\nLinha 3\n"` → `count = 3`.
- Contar bytes: `c = 65` → `contador[65]++` → mais uma letra `'A'`.

🎯 **Imprimir só letras** (filtrar os bytes invisíveis):

```c
for (int i = 0; i < 256; i++)
    if (contador[i] > 0 && ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z')))
        printf("%c: %d\n", i, contador[i]);
```

## 3.2 Ordenar o arquivo inteiro

**Fluxo:** `fread` carrega → `qsort` organiza → `fwrite` salva.

```c
f = fopen("cep.dat", "rb");                 if (!f) return 1;

fseek(f, 0, SEEK_END);                      // 1. mede
qtd = ftell(f) / sizeof(Endereco);

e = malloc(qtd * sizeof(Endereco));         // 2. reserva
if (!e) { fclose(f); return 1; }

rewind(f);                                  // 3. volta ao começo
fread(e, sizeof(Endereco), qtd, f);         // 4. carrega TUDO
qsort(e, qtd, sizeof(Endereco), compara);   // 5. ordena

saida = fopen("cep-ordenado.dat", "wb");    // 6. salva
fwrite(e, sizeof(Endereco), qtd, saida);

fclose(saida); fclose(f); free(e);          // 7. fecha e libera
```

```text
malloc (reserva) → fread (preenche) → qsort (organiza) → fwrite (salva) → free (libera)
```

## 3.3 Busca binária direto no arquivo

⚠️ **Pré-requisito:** o arquivo precisa estar **ordenado** pela chave (ex.: `cep-ordenado.dat`).
Não existe `arquivo[meio]`: o acesso é `fseek` + `fread`.

```c
long inicio = 0, fim = qtd - 1;
int achou = 0;

while (inicio <= fim) {
    long meio = (inicio + fim) / 2;                  // número de REGISTRO

    fseek(f, meio * sizeof(Endereco), SEEK_SET);     // registro → bytes
    fread(&e, sizeof(Endereco), 1, f);

    int r = strncmp(argv[1], e.cep, 8);
    if (r == 0)      { achou = 1; break; }           // achou
    else if (r > 0)  inicio = meio + 1;              // procurado é maior → direita
    else             fim = meio - 1;                 // procurado é menor → esquerda
}
if (!achou) printf("CEP nao encontrado\n");
```

**Simulação (1000 registros):**

```text
inicio = 0, fim = 999 → meio = 499 → fseek(499 × 300 = 149.700) → lê → compara
se procurado > CEP[499] → inicio = 500 → novo meio → NOVO fseek → ...
o laço acaba quando inicio > fim → a chave não existe
```

- 🎯 **Cada tentativa faz um novo `fseek`.** O primeiro código da aula fazia só um `fseek` no meio e depois lia em sequência: isso **não** é busca binária completa.
- Custo: 1.000.000 de registros → cerca de 20 comparações (a busca sequencial faria até 1.000.000).

## 3.4 Índice (chave → posição)

Um atalho para achar o registro **sem varrer o arquivo** e **sem alterar o arquivo original**.

```c
typedef struct indiceCep {
    char cep[8];      // chave
    long posicao;     // número do registro no arquivo ORIGINAL
} IndiceCep;

int compara(const void *a, const void *b) {       // compara IndiceCep, não Endereco!
    return strncmp(((IndiceCep*)a)->cep, ((IndiceCep*)b)->cep, 8);
}
```

**Passo a passo:**

```c
// 1. abrir e medir
f = fopen("cep.dat", "rb");                         if (!f) return 1;
fseek(f, 0, SEEK_END);
qtd = ftell(f) / sizeof(Endereco);

// 2. reservar o índice (o arquivo NUNCA vai inteiro para a memória)
indice = malloc(qtd * sizeof(IndiceCep));           if (!indice) { fclose(f); return 1; }
rewind(f);

// 3. montar o índice lendo 1 registro por vez
for (i = 0; i < qtd; i++) {
    fread(&e, sizeof(Endereco), 1, f);
    strncpy(indice[i].cep, e.cep, 8);
    indice[i].posicao = i;
}

// 4. ordenar o índice
qsort(indice, qtd, sizeof(IndiceCep), compara);

// 5. busca binária NO ÍNDICE (na memória)
long inicio = 0, fim = qtd - 1;
while (inicio <= fim) {
    long meio = (inicio + fim) / 2;
    int r = strncmp(argv[1], indice[meio].cep, 8);
    if (r == 0) {
        // 6. acesso direto ao registro
        long posicao = indice[meio].posicao;
        fseek(f, posicao * sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, f);
        printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",
               e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
        break;
    }
    else if (r > 0) inicio = meio + 1;
    else            fim = meio - 1;
}

// 7. liberar e fechar
free(indice);
fclose(f);
```

🎯 **Ordenar o índice não muda as posições.** Só muda a ordem das linhas:

| Antes do `qsort` | Depois do `qsort` |
| --- | --- |
| 22222222 → 0 | 11111111 → 1 |
| 11111111 → 1 | 22222222 → 0 ← continua dizendo "está no registro 0" |
| 55555555 → 2 | 55555555 → 2 |

**Busca direta × busca pelo índice:**

| | Busca direta (3.3) | Busca pelo índice (3.4) |
| --- | --- | --- |
| Arquivo precisa estar ordenado? | Sim | **Não** |
| Onde compara? | no disco | na memória |
| Quantos `fseek`? | um por tentativa | só um, no final |

## 3.5 Ordenação externa

Usada quando o arquivo **não cabe inteiro na memória**.

```text
DIVIDIR em partes → ORDENAR cada parte (qsort) → INTERCALAR 2 a 2 → ... → sobra 1 arquivo
```

### Etapa 1 — Dividir

```c
#define PARTES 8
long divisao = quantidade / PARTES;   // registros por parte
long resto   = quantidade % PARTES;   // o que sobrou
```

Exemplo com 100 registros: `divisao = 12`, `resto = 4`.

| Parte | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Registros | 13 | 13 | 13 | 13 | 12 | 12 | 12 | 12 |

O resto vai **um para cada uma das primeiras partes** (`if (i < resto) quantidadeParte++`).

🎯 **Por que `malloc((divisao + 1) * sizeof(Endereco))`?** Porque a maior parte pode ter `divisao + 1` registros. Um único bloco serve para todas.

### Etapa 2 — Ordenar e gravar cada parte

```c
e = malloc((divisao + 1) * sizeof(Endereco));

for (int i = 0; i < PARTES; i++) {
    long quantidadeParte = divisao;
    if (i < resto) quantidadeParte++;

    fread(e, sizeof(Endereco), quantidadeParte, cep);    // continua de onde parou
    qsort(e, quantidadeParte, sizeof(Endereco), compara);

    sprintf(nome, "cep_%d.dat", i);                       // cep_0.dat, cep_1.dat ...
    FILE *parte = fopen(nome, "wb");
    fwrite(e, sizeof(Endereco), quantidadeParte, parte);
    fclose(parte);                                        // será reaberto depois
}
free(e);
```

### Etapa 3 — A função de intercalação

Junta **dois arquivos já ordenados** num terceiro ordenado. Guarda **só o registro atual** de cada um (`ea` e `eb`).

```text
1. lê ea de A e eb de B
2. compara → grava o MENOR → lê o próximo SÓ do arquivo que forneceu o menor
3. quando um acabar → copia o resto do outro
```

**Simulação:** `A: 100 300 500 700` · `B: 200 400 600 800`

| ea | eb | Menor | Grava | Avança |
| --- | --- | --- | --- | --- |
| 100 | 200 | ea | 100 | A |
| 300 | 200 | eb | 200 | B |
| 300 | 400 | ea | 300 | A |
| ... | ... | ... | ... | ... |

Resultado: `100 200 300 400 500 600 700 800`

**Código da aula (com `feof`):**

```c
void IntercalaArquivos(char *arqA, char *arqB, char *arqSaida) {
    FILE *a, *b, *saida;
    Endereco ea, eb;

    a     = fopen(arqA, "rb");
    b     = fopen(arqB, "rb");
    saida = fopen(arqSaida, "wb");

    fread(&ea, sizeof(Endereco), 1, a);          // lê ANTES do laço
    fread(&eb, sizeof(Endereco), 1, b);

    while (!feof(a) && !feof(b)) {               // os dois ainda têm registro
        if (compara(&ea, &eb) < 0) {             // ea vem antes?
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread (&ea, sizeof(Endereco), 1, a); // lê o próximo de A
        } else {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread (&eb, sizeof(Endereco), 1, b); // lê o próximo de B
        }
    }
    while (!feof(a)) {                           // sobrou A
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread (&ea, sizeof(Endereco), 1, a);
    }
    while (!feof(b)) {                           // sobrou B
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread (&eb, sizeof(Endereco), 1, b);
    }
    fclose(a); fclose(b); fclose(saida);
}
```

🎯 **Por que funciona com `feof`:** a ordem é **ler → testar → gravar → ler de novo**. Quando a última leitura falha, o `feof` fica verdadeiro e o laço para antes de gravar outra vez.

O erro clássico é **testar antes de ler**:

```c
while (!feof(f)) {                   // ❌
    fread(&e, sizeof(e), 1, f);      // na última volta a leitura falha...
    fwrite(&e, sizeof(e), 1, out);   // ...e grava o último registro DUPLICADO
}
```

### Etapa 4 — Chamar as intercalações

🎯 **Quantas?** Cada intercalação transforma 2 arquivos em 1, ou seja, o total cai de 1 em 1:

```text
8 → 7 → 6 → 5 → 4 → 3 → 2 → 1    =   PARTES − 1 = 7 intercalações
```

```c
char nome1[20], nome2[20], saida[20];   // se existir FILE *saida no programa, use outro nome

for (int i = 0; i < (PARTES - 1) * 2; i += 2) {
    sprintf(nome1, "cep_%d.dat", i);
    sprintf(nome2, "cep_%d.dat", i + 1);
    sprintf(saida, "cep_%d.dat", PARTES + i / 2);
    IntercalaArquivos(nome1, nome2, saida);
}
```

Entendendo o `for`:

| Pedaço | Por quê |
| --- | --- |
| `i += 2` | cada intercalação consome **dois** arquivos |
| `PARTES - 1` | quantidade de intercalações (7) |
| `* 2` | cada intercalação "gasta" 2 unidades de `i` → limite 14 |
| `PARTES + i / 2` | nome da saída: 8, 9, 10, 11, 12, 13, 14 |

Com 8 partes: `i = 0, 2, 4, 6, 8, 10, 12` → 7 voltas. Em `i = 14`, `14 < 14` é falso e o laço para.

| `i` | Entradas | Saída |
| --- | --- | --- |
| 0 | cep_0 + cep_1 | cep_8 |
| 2 | cep_2 + cep_3 | cep_9 |
| 4 | cep_4 + cep_5 | cep_10 |
| 6 | cep_6 + cep_7 | cep_11 |
| 8 | cep_8 + cep_9 | cep_12 |
| 10 | cep_10 + cep_11 | cep_13 |
| 12 | cep_12 + cep_13 | **cep_14** ← arquivo final ordenado |

- Todo arquivo usado como entrada já foi criado numa volta anterior (`cep_8` nasce em `i = 0` e é lido em `i = 8`).
- O arquivo final é sempre `cep_(2 × PARTES − 2)`. Com 8 partes → `cep_14`; com 4 partes → `cep_6`.

⚠️ **Armadilha — NÃO subtrair o 1 duas vezes:**

```c
int quantidadeIntercala = PARTES - 1;                      // já é 7

for (int i = 0; i < quantidadeIntercala * 2; i += 2)       // ✅ i < 14
for (int i = 0; i < (quantidadeIntercala - 1) * 2; i += 2) // ❌ i < 12 → falta 1 intercalação,
                                                           //    sobram 2 arquivos
```

---

# Parte 4 — Checklist de pegadinhas

**Arquivos**
- [ ] `f = fopen(...)` e `fclose(f)` — **nunca** com `*f`.
- [ ] Testar `fopen == NULL`.
- [ ] Segundo `fopen` falhou → `fclose` do primeiro **antes** do `return`.
- [ ] `w`/`wb` **apaga** o arquivo. Dados → modo **binário**.
- [ ] `FILE *` nunca leva `malloc`/`free`.

**Leitura**
- [ ] `int c` no `fgetc` (precisa caber o `EOF`). `EOF` não está gravado no arquivo.
- [ ] `fgetc` antes do `while` **e** no fim de cada volta.
- [ ] Nem todo byte é letra → filtrar antes de imprimir com `%c`.
- [ ] `fread`/`fwrite` devolvem **itens**, não bytes.
- [ ] `&` só em variável simples/struct; array e ponteiro já são endereço.
- [ ] `fread` antes do `while(!feof)`. Testar antes de ler duplica o último registro.

**Posição**
- [ ] `fseek` em **bytes**: `registro × sizeof(Tipo)`.
- [ ] `meio`, `i`, `posicao` são números de **registro**.
- [ ] `sizeof(Tipo)` = **um** registro, não o arquivo.
- [ ] Depois de `SEEK_END` + `ftell` → **`rewind`**.
- [ ] `fseek` não lê · `ftell` não move · `fread` avança.

**Memória e strings**
- [ ] Todo `malloc` tem `free`.
- [ ] `.` para struct · `->` para ponteiro.
- [ ] Array não se atribui → `strcpy`/`strncpy`.
- [ ] Campos fixos → `strncmp`/`strncpy` com tamanho e `printf("%.8s")`.

**Ordenação e busca**
- [ ] `qsort`: `sizeof` e casting do tipo **daquela** chamada; função **sem parênteses**.
- [ ] Ordem invertida: `fread(onde, TAMANHO, QTD, f)` × `qsort(onde, QTD, TAMANHO, compara)`. Trocar compila, mas dá errado.
- [ ] Busca binária direta: arquivo **ordenado** e **um `fseek` por tentativa**.
- [ ] Ordenação externa: `malloc(divisao + 1)`, resto nas primeiras partes, `fclose` em cada parte.
- [ ] Intercalações = `PARTES − 1`; laço até `(PARTES − 1) × 2` com `i += 2`; não subtrair o 1 duas vezes.

---

# Parte 5 — Folha de cola

### Assinaturas

```c
FILE *f = fopen("arq", "rb");            if (!f) return 1;       // NULL se falhar
fclose(f);                                                       // nunca fclose(*f)

int c = fgetc(f);                        fputc(c, f);            // 1 byte · int c · EOF

fread (onde,   sizeof(T), qtd, f);       // ARQUIVO → MEMÓRIA · retorna ITENS
fwrite(origem, sizeof(T), qtd, f);       // MEMÓRIA → ARQUIVO · & só em struct simples

fseek(f, bytes, SEEK_SET / SEEK_CUR / SEEK_END);                 // MOVE (em bytes)
long pos = ftell(f);                                             // INFORMA
rewind(f);                                                       // VOLTA ao início
feof(f);                                                         // já chegou ao fim?

T *v = malloc(qtd * sizeof(T));          if (!v) {...}   free(v);
memset(p, 0, bytes);                     Pessoa p[1000] = {0};

strncpy(dest, orig, 8);   strncmp(a, b, 8);   /* <0 antes · 0 igual · >0 depois */
sprintf(nome, "cep_%d.dat", i);          printf("%.8s", e.cep);

qsort(v, qtd, sizeof(T), compara);       // compara SEM parênteses
```

### Contas

```c
fseek(f, 0, SEEK_END);  qtd = ftell(f) / sizeof(T);  rewind(f);   // bytes → registros
fseek(f, n * sizeof(T), SEEK_SET);                                // registro → bytes
divisao = qtd / PARTES;   resto = qtd % PARTES;                   // malloc(divisao + 1)
```

### Funções prontas

```c
int compara(const void *e1, const void *e2){
    return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}
```

```c
// molde fgetc — no meio: fputc(c,saida) | if(c=='\n') count++ | contador[c]++
c = fgetc(ent);
while (c != EOF) { /* tarefa */ c = fgetc(ent); }
```

```c
// busca binária (no índice: indice[meio].cep e fseek só quando achar)
while (inicio <= fim) {
    meio = (inicio + fim) / 2;
    fseek(f, meio * sizeof(Endereco), SEEK_SET);
    fread(&e, sizeof(Endereco), 1, f);
    r = strncmp(argv[1], e.cep, 8);
    if (r == 0) break;
    else if (r > 0) inicio = meio + 1;
    else fim = meio - 1;
}
```

```c
// índice
for (i = 0; i < qtd; i++) {
    fread(&e, sizeof(Endereco), 1, f);
    strncpy(indice[i].cep, e.cep, 8);
    indice[i].posicao = i;
}
qsort(indice, qtd, sizeof(IndiceCep), compara);
```

```c
// partes
for (i = 0; i < PARTES; i++) {
    qp = divisao;  if (i < resto) qp++;
    fread(e, sizeof(Endereco), qp, cep);
    qsort(e, qp, sizeof(Endereco), compara);
    sprintf(nome, "cep_%d.dat", i);
    p = fopen(nome, "wb");  fwrite(e, sizeof(Endereco), qp, p);  fclose(p);
}
```

```c
// intercala — lê ANTES do while
fread(&ea, sizeof(Endereco), 1, a);   fread(&eb, sizeof(Endereco), 1, b);
while (!feof(a) && !feof(b)) {
    if (compara(&ea, &eb) < 0) { fwrite(&ea, sizeof(Endereco), 1, s); fread(&ea, sizeof(Endereco), 1, a); }
    else                       { fwrite(&eb, sizeof(Endereco), 1, s); fread(&eb, sizeof(Endereco), 1, b); }
}
while (!feof(a)) { fwrite(&ea, sizeof(Endereco), 1, s); fread(&ea, sizeof(Endereco), 1, a); }
while (!feof(b)) { fwrite(&eb, sizeof(Endereco), 1, s); fread(&eb, sizeof(Endereco), 1, b); }
fclose(a); fclose(b); fclose(s);
```

```c
// chamar as intercalações — PARTES−1 vezes · final = cep_(2×PARTES−2)
for (i = 0; i < (PARTES - 1) * 2; i += 2) {
    sprintf(n1, "cep_%d.dat", i);
    sprintf(n2, "cep_%d.dat", i + 1);
    sprintf(ns, "cep_%d.dat", PARTES + i / 2);
    IntercalaArquivos(n1, n2, ns);
}
```

### Lembretes de uma linha

```text
f → endereço · *f → FILE           e.campo → struct · e->campo → ponteiro
fseek escolhe ONDE · fread lê O QUE      ONDE? TAMANHO? QUANTOS? QUAL ARQUIVO?
BYTES ÷ sizeof → REGISTROS               REGISTROS × sizeof → BYTES
rewind depois do SEEK_END                ler → testar → usar → ler de novo
busca direta: arquivo ordenado + 1 fseek por tentativa
índice: ordenar não muda posicao         não subtrair o 1 duas vezes
```

> **Ideia central:** como todos os registros têm o mesmo tamanho, dá para **calcular** onde cada um está. É isso que permite o `fseek` direto, a busca binária, o índice e a ordenação externa.
