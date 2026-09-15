# 📁 Estrutura de Arquivos em C — Resumo para a Prova

> Fusão dos 4 materiais (fundamentos, busca binária, ordenação/índice e ordenação externa), mantendo só o que cai na prova.
> Legenda: **⚠️ Atenção** = pegadinha · **🎯 Ponto fraco** = onde costumo errar · **💻 Exemplo** = código para lembrar

---

## 📑 Sumário

1. [Mapa geral da matéria](#1-mapa-geral-da-matéria)
2. [`FILE *` e ponteiros](#2-file--e-ponteiros)
3. [`fopen`, modos e `fclose`](#3-fopen-modos-e-fclose)
4. [`fgetc`, `fputc`, `int c` e `EOF`](#4-fgetc-fputc-int-c-e-eof)
5. [`fread` e `fwrite`](#5-fread-e-fwrite)
6. [Memória: struct, `.`/`->`, `&`/`*`, `malloc`, `sizeof`](#6-memória-struct----malloc-sizeof)
7. [`argc` e `argv`](#7-argc-e-argv)
8. [`fseek`, `ftell`, `rewind` e as conversões bytes ↔ registros](#8-fseek-ftell-rewind-e-as-conversões-bytes--registros)
9. [Busca binária direto no arquivo](#9-busca-binária-direto-no-arquivo)
10. [Ordenação na memória com `qsort`](#10-ordenação-na-memória-com-qsort)
11. [Índice (chave → posição)](#11-índice-chave--posição)
12. [Ordenação externa e intercalação](#12-ordenação-externa-e-intercalação)
13. [Checklist de pegadinhas](#13-checklist-de-pegadinhas)
14. [Colinha final](#14-colinha-final)

---

## 1. Mapa geral da matéria

```text
arquivos → binários → registros de tamanho fixo → acesso direto (fseek)
        → ordenação (qsort) → busca binária → índice → ordenação externa
```

Tudo se apoia em **duas contas** (só valem para registros de tamanho fixo):

```text
quantidade de registros = tamanho do arquivo (bytes) / sizeof(Tipo)
byte do registro N      = N * sizeof(Tipo)
```

Três "receitas" que podem cair:

| Tarefa | Fluxo | Memória usada |
| --- | --- | --- |
| Ordenar arquivo inteiro | `fread` tudo → `qsort` → `fwrite` | **todos** os registros |
| Índice | lê 1 por vez → guarda (chave, posição) → `qsort` no índice → busca binária → `fseek` | só o índice |
| Ordenação externa | divide em partes → `qsort` em cada → intercala 2 a 2 até sobrar 1 | só uma parte por vez |

---

## 2. `FILE *` e ponteiros

`FILE` é um tipo da `stdio.h` que controla um arquivo aberto (posição atual, buffer, erro, fim de arquivo). **Nunca mexemos nos campos dele** — só usamos as funções.

```c
FILE *f;   // f é um PONTEIRO para FILE (guarda um endereço)
```

### 🎯 Ponto fraco: `f` x `*f`

Mesma lógica de `int *p`:

```text
int x = 10;  int *p = &x;
p  → endereço de x   (ex.: 1000)
*p → valor de x      (10)
```

| Expressão | É do tipo | Significado |
| --- | --- | --- |
| `f` | `FILE *` | endereço guardado no ponteiro |
| `*f` | `FILE` | a estrutura naquele endereço |

```text
f ───────────► FILE      (f NÃO aponta para si mesmo)
```

**Dois usos do `*`:**

```c
FILE *f;   // na DECLARAÇÃO: "f é ponteiro"
*f         // numa EXPRESSÃO: "vá até o endereço" (desreferenciação)
```

### ⚠️ Por isso:

```c
f = fopen("a.dat", "rb");   // ✅ fopen retorna FILE*, f é FILE*
*f = fopen("a.dat", "rb");  // ❌ *f é FILE, tipos não batem
fclose(f);                  // ✅ fclose recebe FILE*
fclose(*f);                 // ❌
```

> `FILE *` **nunca** leva `malloc`/`free`. Quem dá o endereço é o `fopen`; quem libera é o `fclose`.

---

## 3. `fopen`, modos e `fclose`

```c
FILE *f = fopen(nome, modo);   // retorna FILE* ou NULL se falhar
```

**Sempre verificar:**

```c
if (!f) {                 // !f  ⇔  f == NULL
    printf("Erro ao abrir arquivo\n");
    return 1;
}
```

### Modos

| Modo | Lê | Escreve | Cria | Apaga conteúdo |
| --- | :-: | :-: | :-: | :-: |
| `r` / `rb` | ✅ | ❌ | ❌ (precisa existir) | ❌ |
| `w` / `wb` | ❌ | ✅ | ✅ | ⚠️ **SIM** |
| `a` | ❌ | ✅ (no final) | ✅ | ❌ |
| `r+` / `r+b` | ✅ | ✅ | ❌ | ❌ |
| `w+` | ✅ | ✅ | ✅ | ⚠️ **SIM** |

```text
r = read · w = write · a = append · + = lê E escreve · b = binary
```

- ⚠️ `w` **destrói** o conteúdo de um arquivo existente.
- Para arquivos de dados (`.dat`, structs, registros) usar **sempre** o modo binário (`rb`, `wb`, `r+b`). No Windows o modo texto altera as quebras de linha.

### `fclose` e o `return` no meio

`fclose(f)` = "terminei com esse arquivo" (garante que o buffer foi gravado no disco). Todo arquivo aberto deve ser fechado.

🎯 **Se um segundo `fopen` falhar, feche o primeiro antes do `return`**, senão o `fclose` do final nunca é executado:

```c
entrada = fopen(argv[1], "rb");
if (!entrada) return 1;

saida = fopen(argv[2], "wb");
if (!saida) {
    fclose(entrada);   // ← obrigatório aqui
    return 1;
}
```

> Na ordenação externa isso é ainda mais importante: as partes são **reabertas** pela intercalação, então precisam ter sido fechadas (gravadas) antes.

---

## 4. `fgetc`, `fputc`, `int c` e `EOF`

```text
fgetc(f)     → lê 1 byte    ARQUIVO → MEMÓRIA
fputc(c, f)  → escreve 1 byte  MEMÓRIA → ARQUIVO
```

### 🎯 Por que `int c` e não `char c`?

`fgetc` precisa devolver **duas coisas diferentes**: um byte (0 a 255) **ou** `EOF`. Um `char` não comporta os 256 valores + o `EOF`; um `int` comporta.

### ⚠️ `EOF`

- `EOF` = *End Of File*.
- **Não é um caractere gravado no arquivo.** É um valor especial devolvido pela função de leitura quando não há mais dados.

### 💻 Padrão de leitura (decorar)

```c
int c;
c = fgetc(entrada);
while (c != EOF) {
    /* usa c */
    c = fgetc(entrada);
}
```

### 💻 Copiar arquivo

```c
c = fgetc(entrada);
while (c != EOF) {
    fputc(c, saida);
    c = fgetc(entrada);
}
```

### 💻 Contar linhas = contar `'\n'`

```c
int count = 0;
c = fgetc(entrada);
while (c != EOF) {
    if (c == '\n') count++;
    c = fgetc(entrada);
}
```

`"Linha 1\nLinha 2\nLinha 3\n"` → `count = 3`.

### 💻 Contar ocorrências de cada byte

```text
1 byte = 8 bits → 2⁸ = 256 valores (0..255) → vetor de 256 posições
```

```c
int contador[256] = {0};
c = fgetc(entrada);
while (c != EOF) {
    contador[c]++;          // c = 65 → contador[65]++ (letra 'A')
    c = fgetc(entrada);
}
```

### ⚠️ ASCII e impressão

| Número | 48 | 65 | 66 | 97 |
| --- | --- | --- | --- | --- |
| Caractere | `'0'` | `'A'` | `'B'` | `'a'` |

```c
printf("%c", 65);   // A
printf("%d", 65);   // 65   → o valor é o mesmo, muda só o formato
```

🎯 **Nem todo byte é letra** (há `\n`, `\t`, caracteres de controle). Se o exercício pede "só letras", **filtrar** antes de imprimir:

```c
for (int i = 0; i < 256; i++)
    if (contador[i] > 0 && ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z')))
        printf("%c: %d\n", i, contador[i]);
```

---

## 5. `fread` e `fwrite`

### Direção (a coisa mais importante)

```text
fread  → 📂 ARQUIVO → 🧠 MEMÓRIA
fwrite → 🧠 MEMÓRIA → 📂 ARQUIVO
```

### Parâmetros — pergunta mental: **ONDE? TAMANHO? QUANTOS? QUAL ARQUIVO?**

```c
fread (destino, sizeof(Tipo), quantidade, f);   // onde colocar
fwrite(origem,  sizeof(Tipo), quantidade, f);   // o que gravar
```

### 🎯 Quando usar `&`

```c
Pessoa p;              fwrite(&p, sizeof(Pessoa), 1, f);     // variável simples → &
Pessoa v[1000];        fwrite(v,  sizeof(Pessoa), 1000, f);  // array → já é endereço
Endereco *e = malloc…; fread (e,  sizeof(Endereco), qtd, f); // ponteiro → já é endereço
```

### ⚠️ Retorno = quantidade de **ITENS**, não de bytes

```c
int qt = fread(p, sizeof(Pessoa), 1000, f);
```

Arquivo com 300 Pessoas de 52 bytes → `qt = 300` ✅ (e **não** 15600 ❌).

Uso prático para checar se leu tudo / fim de arquivo:

```c
if (fread(e, sizeof(Endereco), qtd, f) == qtd) printf("Lido = OK\n");
```

### ⚠️ Outras observações

- `fread` **não abre arquivo**: o último parâmetro é um `FILE *` já aberto.
  `fread(&ea, sizeof(Endereco), 1, "cep_0.dat");` ❌
- `fread` lê **a partir da posição atual** e **avança** a posição. Chamadas seguidas leem registros consecutivos.
- `fread` copia os **bytes do registro inteiro**; quem dá significado aos bytes é a `struct`.

| Função | Quantidade |
| --- | --- |
| `fgetc` / `fputc` | 1 byte |
| `fread` / `fwrite` | vários itens |

---

## 6. Memória: struct, `.`/`->`, `&`/`*`, `malloc`, `sizeof`

### struct + typedef

```c
typedef struct _Endereco Endereco;   // apelido: Endereco em vez de struct _Endereco

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];      // ← CHAVE de ordenação/busca
    char lixo[2];     // espaço + quebra de linha do formato do arquivo
};                    // 72*4 + 2 + 8 + 2 = 300 bytes
```

⚠️ O tamanho real **sempre** com `sizeof(Endereco)` — o compilador pode inserir *padding* (alinhamento). O `lixo[2]` existe para a struct bater com os 300 bytes do registro no arquivo.

### 🎯 `Tipo x;` x `Tipo *x;` — a decisão que mais confunde

```text
Preciso de UM item por vez, que vou ler, usar e sobrescrever?
    → Endereco e;          (struct de verdade, sem malloc, usa  .  e  &e)

Preciso de VÁRIOS itens ao mesmo tempo, e a quantidade só aparece
em tempo de execução?
    → Endereco *e;         (ponteiro + malloc, usa  ->  ou  e[i].)

Arquivo?
    → FILE *f;             (ponteiro vindo do fopen, NUNCA malloc/free)
```

💻 **Exemplo real (programa do índice) usando as duas formas:**

```c
Endereco e;            // 1 registro temporário — reaproveitado a cada volta
IndiceCep *indice;     // TODAS as entradas — precisam ficar vivas p/ qsort e busca

indice = malloc(qtd * sizeof(IndiceCep));
for (i = 0; i < qtd; i++) {
    fread(&e, sizeof(Endereco), 1, f);   // &e   → e é struct
    strncpy(indice[i].cep, e.cep, 8);    // e.cep → ponto
    indice[i].posicao = i;
}
```

```text
1ª volta: registro 0 → e
2ª volta: registro 1 → e  (sobrescreve — tudo bem, a chave já foi copiada)
```

Mesma lógica na intercalação: `Endereco ea, eb;` sem `malloc`, porque só o **registro atual** de cada arquivo importa.

⚠️ Por que não `Endereco e[1000];`? Porque o arquivo pode ter 1.000.000 de registros — só se sabe o tamanho **depois** de medir o arquivo.

### `.` x `->`

```text
Tenho a struct      → e.cep
Tenho um ponteiro   → e->cep     ( = (*e).cep )
Bloco apontado      → e[i].cep
```

### `&` x `*`

```text
Endereco e;     e → struct        &e → endereço da struct
Endereco *e;    e → endereço      *e → struct naquele endereço
```

### Array: `p` x `p[0]`

```text
Pessoa p[1000];
p     → endereço do início do array  (por isso fwrite(p, ...) sem &)
p[0]  → primeira Pessoa
```

### `malloc` / `free`

```c
e = malloc(qtd * sizeof(Endereco));            // devolve void* (endereço do início)
e = (Endereco*) malloc(qtd * sizeof(Endereco)); // casting é OPCIONAL em C

if (e == NULL) {                                // ⚠️ sempre checar
    fprintf(stderr, "Erro ao alocar memoria\n");
    fclose(f);
    return 1;
}
/* ... */
free(e);                                        // ⚠️ toda memória de malloc volta
```

```text
malloc (reserva, vazio) → fread (preenche) → qsort (organiza) → fwrite (salva) → free (libera)
```

### `sizeof`

```text
sizeof(Pessoa)         → bytes de UMA Pessoa (ex.: 52)
1000 * sizeof(Pessoa)  → bytes de 1000 Pessoas (52000)
sizeof(Endereco)       → UM registro, NÃO o arquivo
```

### `memset` e inicialização

```c
memset(p, 0, 1000 * sizeof(Pessoa));  // (endereço, valor, QTD DE BYTES)
memset(p, 0, sizeof(p));              // p é array local → sizeof(p) = bytes do array todo
Pessoa p[1000] = {0};                 // forma mais simples de zerar
```

⚠️ Array local **não vem zerado** — pode ter lixo de memória.
`memset` = preenche qualquer região · `= {0}` = inicialização do array.

### `strcpy` — não se atribui array

```c
strcpy(p[0].nome, "Renato Mauro");   // ✅
p[0].nome = "Renato Mauro";          // ❌ nome é char[], não se atribui array
fgets(p[0].nome, 40, stdin);         // ler do teclado
```

---

## 7. `argc` e `argv`

```bash
./programa arquivo.txt saida.txt
```

```text
argc = 3          ← o nome do programa CONTA
argv[0] = "./programa"
argv[1] = "arquivo.txt"
argv[2] = "saida.txt"
```

⚠️ Verificar `argc` **antes** de usar `argv[1]`/`argv[2]`:

```c
if (argc != 3) {                             // programa + origem + destino
    fprintf(stderr, "USO: %s origem destino\n", argv[0]);
    return 1;
}
```

`argc != 2` → programa + 1 argumento (ex.: o CEP procurado).

---

## 8. `fseek`, `ftell`, `rewind` e as conversões bytes ↔ registros

Todo arquivo aberto tem uma **posição atual** ("cabeça de leitura") que avança a cada leitura/escrita.

| Função | Faz | ⚠️ Não faz |
| --- | --- | --- |
| `fseek(f, desloc, origem)` | **move** a posição (em **bytes**) | não lê |
| `ftell(f)` | **informa** a posição (bytes desde o início) | não move, não lê |
| `rewind(f)` | volta ao começo | — |
| `fread(...)` | lê a partir da posição e **avança** | — |

```text
SEEK_SET → a partir do início     fseek(f, 300, SEEK_SET)  → byte 300
SEEK_CUR → a partir da atual      fseek(f, -2,  SEEK_CUR)  → volta 2 bytes
SEEK_END → a partir do final      fseek(f, 0,   SEEK_END)  → vai pro fim
```

> **`fseek` escolhe ONDE ler. `fread` lê O QUE está lá.**

### 💻 Descobrir tamanho e quantidade de registros

```c
fseek(f, 0, SEEK_END);
long tamanhoBytes = ftell(f);                  // tamanho do arquivo
long qtd = tamanhoBytes / sizeof(Endereco);    // quantidade de registros
rewind(f);                                     // ⚠️ volta ao começo!
```

🎯 **Esquecer o `rewind`** → o `fread` seguinte começa no final e não lê nada.

### 🎯 As duas conversões fundamentais

```text
            ÷ sizeof(Endereco)
BYTES ───────────────────────────► REGISTROS   "quantos registros cabem?"
            × sizeof(Endereco)
REGISTROS ───────────────────────► BYTES       "quantos bytes até esse registro?"
```

Exemplo (registro de 300 bytes, arquivo de 300.000 bytes):

```text
300.000 / 300 = 1.000 registros
registro 499 → 499 × 300 = 149.700 bytes → fseek(f, 149700, SEEK_SET)
posição 600, lê 300 bytes → posição passa a ser 900
```

---

## 9. Busca binária direto no arquivo

⚠️ **Pré-requisito: o arquivo precisa estar ORDENADO pela chave** (ex.: `cep-ordenado.dat`).
Sem acesso direto não dá: não existe `arquivo[meio]` — é `fseek` + `fread`.

### 🎯 `meio` é número de REGISTRO, não de byte

```text
inicio = 0, fim = qtd - 1       (1000 registros → 0 a 999)
meio = (0 + 999) / 2 = 499      → registro 499
byte = 499 * sizeof(Endereco)   → 149.700
```

⚠️ O primeiro código visto em aula fazia só **um** `fseek` no meio e depois lia sequencialmente — isso **não** é busca binária completa. Na busca binária de verdade, **cada tentativa faz um novo `fseek`**.

### 💻 Busca binária completa

```c
long inicio = 0, fim = qtd - 1;
int achou = 0;

while (inicio <= fim) {
    long meio = (inicio + fim) / 2;

    fseek(f, meio * sizeof(Endereco), SEEK_SET);   // registro → bytes
    fread(&e, sizeof(Endereco), 1, f);

    int r = strncmp(argv[1], e.cep, 8);
    if (r == 0)      { achou = 1; break; }          // encontrou
    else if (r > 0)  inicio = meio + 1;             // procurado é maior → direita
    else             fim = meio - 1;                // procurado é menor → esquerda
}
if (!achou) printf("CEP nao encontrado\n");
```

```text
r == 0 → achou · r > 0 → direita (inicio = meio + 1) · r < 0 → esquerda (fim = meio - 1)
laço acaba quando inicio > fim → chave não existe
```

Custo: 1.000.000 de registros → ~20 comparações (sequencial: até 1.000.000).

---

## 10. Ordenação na memória com `qsort`

```c
qsort(onde, quantidade, tamanho de cada, funcao_compara);
qsort(e, qtd, sizeof(Endereco), compara);
```

⚠️ O `sizeof` precisa ser **do tipo que está sendo ordenado naquela chamada**. Errar corrompe os dados sem aviso:

```c
qsort(e,      qtd, sizeof(Endereco),  comparaEndereco);
qsort(indice, qtd, sizeof(IndiceCep), comparaIndice);
```

### 💻 Função de comparação

```c
int compara(const void *e1, const void *e2) {
    return strncmp(((Endereco*)e1)->cep,
                   ((Endereco*)e2)->cep, 8);
}
```

- `const void *` porque o `qsort` é **genérico** (qualquer tipo).
- `(Endereco*)e1` = casting: "trate como ponteiro para `Endereco`" → depois `->cep`.
- Retorno: `< 0` e1 antes · `= 0` iguais · `> 0` e1 depois (é a convenção do `strncmp`).
- Decrescente: inverter os operandos.

💻 Chave numérica (não dá para usar `strncmp`):

```c
int comparaNumero(const void *a, const void *b) {
    long x = ((Registro*)a)->valor, y = ((Registro*)b)->valor;
    if (x < y) return -1;
    if (x > y) return  1;
    return 0;
}
```

### 🎯 De onde vêm `e1` e `e2`?

Quem chama `compara` é o **`qsort`**, com os pares que ele escolher. Nós só entregamos a função:

```c
qsort(e, qtd, sizeof(Endereco), compara);   // SEM parênteses → passa o endereço da função
compara();                                  // COM parênteses → executaria agora (errado aqui)
```

### 💻 Programa: ordenar o arquivo inteiro

```c
f = fopen("cep.dat", "rb");                 if (!f) return 1;
fseek(f, 0, SEEK_END);
qtd = ftell(f) / sizeof(Endereco);
e = malloc(qtd * sizeof(Endereco));         if (!e) { fclose(f); return 1; }
rewind(f);
fread(e, sizeof(Endereco), qtd, f);         // carrega TUDO
qsort(e, qtd, sizeof(Endereco), compara);   // organiza
saida = fopen("cep-ordenado.dat", "wb");
fwrite(e, sizeof(Endereco), qtd, saida);    // salva
fclose(saida); fclose(f); free(e);
```

> **`fread` carrega → `qsort` organiza → `fwrite` salva.** Exige memória para todos os registros.

---

## 11. Índice (chave → posição)

Atalho para achar um registro **sem varrer o arquivo** e **sem alterar o arquivo original**.

```c
typedef struct indiceCep {
    char cep[8];      // chave
    long posicao;     // número do registro no arquivo ORIGINAL
} IndiceCep;
```

### Passos

```text
fopen → mede qtd → malloc(qtd * sizeof(IndiceCep)) → rewind
→ for: fread(&e) + strncpy(chave) + posicao = i
→ qsort(indice, ..., sizeof(IndiceCep), compara)
→ busca binária NO ÍNDICE (memória)
→ fseek(f, posicao * sizeof(Endereco)) → fread(&e) → printf
→ free(indice) + fclose(f)
```

### 🎯 Ordenar o índice NÃO muda as posições

```text
Antes do qsort           Depois do qsort
22222222 → 0             11111111 → 1
11111111 → 1             22222222 → 0   ← continua dizendo "está no registro 0"
55555555 → 2             55555555 → 2
```

Só a **ordem das entradas** muda; `posicao` sempre aponta para o registro original.

### 💻 Comparação do índice (tipo diferente!)

```c
int compara(const void *a, const void *b) {
    return strncmp(((IndiceCep*)a)->cep, ((IndiceCep*)b)->cep, 8);
}
```

### 💻 Busca no índice + acesso direto

```c
long inicio = 0, fim = qtd - 1;
while (inicio <= fim) {
    long meio = (inicio + fim) / 2;
    int r = strncmp(argv[1], indice[meio].cep, 8);   // compara na MEMÓRIA
    if (r == 0) {
        long posicao = indice[meio].posicao;
        fseek(f, posicao * sizeof(Endereco), SEEK_SET);   // em BYTES
        fread(&e, sizeof(Endereco), 1, f);
        printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",
               e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
        break;
    }
    else if (r > 0) inicio = meio + 1;
    else            fim = meio - 1;
}
```

⚠️ **Precisão no `printf` (`%.72s`, `%.8s`)**: os campos são `char[]` de tamanho fixo **sem `'\0'` garantido**. Sem a precisão, o `printf` lê além do campo. Pelo mesmo motivo usamos `strncmp`/`strncpy` com tamanho 8, e não `strcmp`/`strcpy`.

| | Busca direta no arquivo (seção 9) | Busca pelo índice |
| --- | --- | --- |
| Arquivo precisa estar ordenado? | Sim | **Não** |
| Onde é a comparação? | no disco (fseek a cada passo) | na memória |
| `fseek` | a cada tentativa | só 1, no final |

---

## 12. Ordenação externa e intercalação

Usada quando o arquivo **não cabe inteiro na RAM**.

```text
DIVIDIR → ORDENAR cada parte (qsort) → INTERCALAR 2 a 2 → ... → sobra 1 arquivo
```

### Divisão em partes

```c
#define PARTES 8
long divisao = quantidade / PARTES;   // registros por parte
long resto   = quantidade % PARTES;   // sobra
```

100 registros → `divisao = 12`, `resto = 4` → partes 0 a 3 com **13**, partes 4 a 7 com **12**.

```c
long quantidadeParte = divisao;
if (i < resto) quantidadeParte++;     // o resto vai 1 para cada uma das primeiras partes
```

### 🎯 Por que `malloc((divisao + 1) * sizeof(Endereco))`?

Porque a **maior** parte pode ter `divisao + 1` registros (por causa do resto). Um único bloco serve para todas as partes.

### 💻 Gerar as partes

```c
for (int i = 0; i < PARTES; i++) {
    long quantidadeParte = divisao;
    if (i < resto) quantidadeParte++;

    fread(e, sizeof(Endereco), quantidadeParte, cep);   // continua de onde parou
    qsort(e, quantidadeParte, sizeof(Endereco), compara);

    sprintf(nome, "cep_%d.dat", i);                      // cep_0.dat, cep_1.dat...
    FILE *parte = fopen(nome, "wb");
    fwrite(e, sizeof(Endereco), quantidadeParte, parte);
    fclose(parte);                                       // ⚠️ será reaberto depois
}
```

### Intercalação (merge)

Junta **dois arquivos já ordenados** num terceiro ordenado, guardando **só o registro atual de cada um** (`ea`, `eb`):

```text
lê ea de A e eb de B
repete: compara → grava o MENOR → lê o próximo SÓ do arquivo que forneceu o menor
quando um acabar → copia o resto do outro
```

Exemplo: `A: 100 300 500 700` · `B: 200 400 600 800`

```text
ea=100 eb=200 → grava 100, avança A → ea=300
ea=300 eb=200 → grava 200, avança B → eb=400
...                                → 100 200 300 400 500 600 700 800
```

### 💻 Código da aula

```c
void IntercalaArquivos(char *arqA, char *arqB, char *arqSaida) {
    FILE *a, *b, *saida;
    Endereco ea, eb;

    a     = fopen(arqA, "rb");
    b     = fopen(arqB, "rb");
    saida = fopen(arqSaida, "wb");

    fread(&ea, sizeof(Endereco), 1, a);
    fread(&eb, sizeof(Endereco), 1, b);

    while (!feof(a) && !feof(b)) {
        if (compara(&ea, &eb) < 0) {          // ea vem antes?
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread (&ea, sizeof(Endereco), 1, a);
        } else {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread (&eb, sizeof(Endereco), 1, b);
        }
    }
    while (!feof(a)) {                        // sobra de A
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread (&ea, sizeof(Endereco), 1, a);
    }
    while (!feof(b)) {                        // sobra de B
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread (&eb, sizeof(Endereco), 1, b);
    }
    fclose(a); fclose(b); fclose(saida);
}
```

### ⚠️ `EOF` x `feof()`

```text
EOF      → VALOR devolvido por fgetc etc.      if (c == EOF)
feof(f)  → FUNÇÃO que testa o indicador de fim  while (!feof(f))
```

```c
while (!feof(f)) {         
    fread(&e, sizeof(e), 1, f);  
    fwrite(&e, sizeof(e), 1, out); 
}
```

### 🎯 Quantas intercalações? `PARTES - 1`

Cada intercalação transforma 2 arquivos em 1 → reduz o total em 1:
`8 → 7 → 6 → 5 → 4 → 3 → 2 → 1` = **7 intercalações**.

### 🎯 O laço `for (i = 0; i < (PARTES - 1) * 2; i += 2)`

```c
for (int i = 0; i < (PARTES - 1) * 2; i += 2) {
    sprintf(nome1, "cep_%d.dat", i);
    sprintf(nome2, "cep_%d.dat", i + 1);
    sprintf(saida, "cep_%d.dat", PARTES + i / 2);
    IntercalaArquivos(nome1, nome2, saida);
}
```

- `i += 2` → consome **dois arquivos** por vez.
- `PARTES - 1` = nº de intercalações; `* 2` porque cada uma "gasta" 2 unidades de `i`.
- `(8 - 1) * 2 = 14` → `i = 0, 2, 4, 6, 8, 10, 12` → **7 voltas**; em `i = 14`, `14 < 14` é falso.
- Saída `PARTES + i/2` → 8, 9, 10, 11, 12, 13, 14.

⚠️ **Armadilha:** com `quantidadeIntercala = PARTES - 1`, a condição certa é
`i < quantidadeIntercala * 2`. Escrever `i < (quantidadeIntercala - 1) * 2` faz **uma intercalação a menos** e sobram 2 arquivos. NÃO REPETIR DUAS VEZES!

### 💻 Tabela das 7 intercalações (8 partes)

| `i` | Entradas | Saída |
| --- | --- | --- |
| 0 | cep_0 + cep_1 | cep_8 |
| 2 | cep_2 + cep_3 | cep_9 |
| 4 | cep_4 + cep_5 | cep_10 |
| 6 | cep_6 + cep_7 | cep_11 |
| 8 | cep_8 + cep_9 | cep_12 |
| 10 | cep_10 + cep_11 | cep_13 |
| 12 | cep_12 + cep_13 | **cep_14** ← arquivo final ordenado |

---

## 13. Checklist de pegadinhas

- [ ] `f = fopen(...)`, **não** `*f = fopen(...)`; `fclose(f)`, **não** `fclose(*f)`.
- [ ] Verificar `fopen == NULL` e `malloc == NULL`.
- [ ] Segundo `fopen` falhou → `fclose` do primeiro **antes** do `return`.
- [ ] Modo `w`/`wb` **apaga** o arquivo existente. Dados → modo **binário**.
- [ ] `int c` para `fgetc` (precisa caber `EOF`). `EOF` **não** está gravado no arquivo.
- [ ] Nem todo byte é letra → filtrar antes de imprimir com `%c`.
- [ ] `fread`/`fwrite` retornam **itens**, não bytes.
- [ ] `&` só para variável simples/struct; array e ponteiro já são endereço.
- [ ] `.` para struct, `->` para ponteiro.
- [ ] `FILE *` nunca leva `malloc`/`free`; todo `malloc` tem seu `free`.
- [ ] Array não se atribui → `strcpy`/`strncpy`.
- [ ] `argc` conta o nome do programa; checar antes de usar `argv[i]`.
- [ ] `fseek` trabalha em **bytes**: `registro * sizeof(Tipo)`.
- [ ] `meio` é número de **registro**; `sizeof(Tipo)` é **um** registro, não o arquivo.
- [ ] Depois de `fseek(..., SEEK_END)` + `ftell`, fazer **`rewind`**.
- [ ] `fseek` não lê; `ftell` não move; `fread` avança a posição.
- [ ] Busca binária direta: arquivo **ordenado** e **novo `fseek` a cada tentativa**.
- [ ] `qsort`: `sizeof` do tipo **daquela** chamada; função passada **sem parênteses**.
- [ ] Índice ordenado **não** muda `posicao` nem o arquivo original.
- [ ] Campos `char[]` fixos: `strncmp`/`strncpy` e `printf("%.8s")`.
- [ ] Ordenação externa: `malloc(divisao + 1)`, resto nas primeiras partes, `fclose` nas partes.
- [ ] `while(!feof(f)) { fread; fwrite; }` → duplica o último registro.
- [ ] Intercalações = `PARTES - 1`; laço até `(PARTES - 1) * 2` com `i += 2`.

---

## 14. Colinha final

```c
FILE *f = fopen("arq", "rb");     if (!f) return 1;
fclose(f);

int c = fgetc(f);                 fputc(c, f);          // 1 byte

fread (destino, sizeof(T), qtd, f);   // arquivo → memória  (retorna itens)
fwrite(origem,  sizeof(T), qtd, f);   // memória → arquivo

fseek(f, 0, SEEK_END);  long bytes = ftell(f);  rewind(f);
long qtd = bytes / sizeof(T);                    // bytes → registros
fseek(f, n * sizeof(T), SEEK_SET);               // registro → bytes

T *v = malloc(qtd * sizeof(T));   if (!v) {...}   free(v);
qsort(v, qtd, sizeof(T), compara);

int compara(const void *a, const void *b) {
    return strncmp(((T*)a)->chave, ((T*)b)->chave, TAM);
}
```

```text
fread  → ARQUIVO ─► MEMÓRIA        p  → endereço     e.campo  → struct
fwrite → MEMÓRIA ─► ARQUIVO        *p → valor        e->campo → ponteiro

BYTES ──÷ sizeof──► REGISTROS      REGISTROS ──× sizeof──► BYTES

ONDE? · TAMANHO? · QUANTOS? · QUAL ARQUIVO?
```

> **Ideia central:** registros de tamanho fixo permitem **calcular** a posição de qualquer registro. É isso que torna possível o `fseek` direto, a busca binária, o índice e a ordenação externa.
