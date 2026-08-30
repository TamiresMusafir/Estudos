# Estrutura de Arquivos — Anotações

## 1. Ideia geral

Um arquivo pode ser visto como uma sequência de **bytes** armazenados no disco.

O programa pode:

* abrir um arquivo;
* ler dados dele;
* escrever dados nele;
* alterar a posição de leitura/escrita;
* fechar o arquivo.

A biblioteca usada para isso é principalmente:

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

# 2. `FILE`

`FILE` é um **tipo** fornecido pela biblioteca padrão do C.

Ele representa as informações necessárias para o programa trabalhar com um arquivo aberto.

Podemos imaginar, de forma simplificada, que um `FILE` guarda informações como:

* qual arquivo está sendo usado;
* modo de abertura;
* posição atual dentro do arquivo;
* informações de buffer;
* estado de erro;
* indicação de fim de arquivo etc.

Não precisamos conhecer os campos internos de `FILE`.

---

# 3. `FILE *entrada`

Quando fazemos:

```c
FILE *entrada;
```

estamos criando uma variável chamada `entrada` que é um **ponteiro para `FILE`**.

É importante entender:

```text
entrada → endereço de um FILE
```

`entrada` NÃO é o arquivo diretamente.

Ele guarda o endereço de uma estrutura `FILE` usada para controlar o arquivo.

---

## `entrada` x `*entrada`

Essa foi uma das partes mais confusas.

Se:

```c
int x = 10;
int *p = &x;
```

então:

```text
p  → endereço de x
*p → valor de x
```

Por exemplo:

```text
p  = 1000       (endereço)
*p = 10         (valor naquele endereço)
```

A mesma ideia vale para:

```c
FILE *entrada;
```

Podemos imaginar:

```text
entrada
   ↓
 endereço
   ↓
 FILE
```

Então:

```text
entrada   → o endereço armazenado no ponteiro
*entrada  → acessar o FILE que está naquele endereço
```

### Importante

`entrada` **não aponta para si mesma**.

É:

```text
entrada ─────────→ FILE
```

O `*` usado em:

```c
FILE *entrada;
```

indica que `entrada` é um ponteiro.

Já o `*` usado em:

```c
*entrada
```

é o operador de desreferenciação: ele significa "vá até o endereço armazenado no ponteiro".

---

# 4. Por que `fopen()` fica assim?

```c
entrada = fopen(argv[1], "rb");
```

O `fopen()` retorna um `FILE *`.

Portanto:

```text
fopen()
   ↓
 FILE*
   ↓
entrada
```

Estamos guardando em `entrada` o ponteiro retornado por `fopen()`.

Também poderíamos separar:

```c
FILE *entrada;

entrada = fopen("arquivo.txt", "rb");
```

Ou escrever tudo em uma linha:

```c
FILE *entrada = fopen("arquivo.txt", "rb");
```

Os dois são equivalentes.

---

# 5. Por que não `*entrada = fopen(...)`?

Porque:

```text
entrada   → FILE*
*entrada  → FILE
```

Enquanto `fopen()` retorna:

```text
FILE*
```

Então queremos:

```text
FILE* → FILE*
```

por isso:

```c
entrada = fopen(...);
```

E não:

```c
*entrada = fopen(...);
```

---

# 6. `fopen()`

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
       ↓
     fopen()
       ↓
    FILE*
       ↓
       f
```

Se não conseguir abrir o arquivo, `fopen()` retorna `NULL`.

Por isso verificamos:

```c
if(!f)
{
    printf("Erro ao abrir arquivo");
    return 1;
}
```

`!f` significa que `f` é `NULL`.

---

# 7. Modos do `fopen`

O segundo parâmetro de `fopen()` determina **como o arquivo será aberto**.

## `r` — read

```c
fopen("arquivo.txt", "r");
```

Abre para **leitura**.

O arquivo precisa existir.

Não é usado para escrever.

---

## `w` — write

```c
fopen("arquivo.txt", "w");
```

Abre para **escrita**.

Se o arquivo não existir, ele pode ser criado.

Se já existir, seu conteúdo é **apagado/truncado**.

Cuidado com `w` porque pode destruir o conteúdo existente.

---

## `a` — append

```c
fopen("arquivo.txt", "a");
```

Abre para escrita no **final do arquivo**.

Se o arquivo não existir, pode ser criado.

O conteúdo existente é preservado.

É útil quando queremos adicionar informações sem apagar o que já existe.

---

## `r+` — leitura e escrita

```c
fopen("arquivo.txt", "r+");
```

Permite:

* ler;
* escrever.

O arquivo precisa existir.

O conteúdo existente não é apagado ao abrir.

---

## `w+` — leitura e escrita

```c
fopen("arquivo.txt", "w+");
```

Permite:

* ler;
* escrever.

Pode criar o arquivo se ele não existir.

Se já existir, o conteúdo é **apagado/truncado**.

---

## `rb` — read binary

```c
fopen("arquivo.dat", "rb");
```

É:

```text
r = read
b = binary
```

Ou seja:

> Abrir para leitura em modo binário.

É muito usado quando trabalhamos diretamente com bytes ou arquivos binários.

---

## `r+b`

```c
fopen("arquivo.dat", "r+b");
```

É:

```text
r = leitura
+ = leitura e escrita
b = binário
```

Permite ler e escrever em um arquivo binário existente.

---

# 8. Texto x binário

Os modos podem ter `b`:

```text
r
rb

w
wb

r+
r+b
```

O `b` significa **binary**.

Em sistemas como Windows, existe uma diferença importante entre modo texto e binário, especialmente relacionada à representação de quebras de linha.

Para trabalhar diretamente com arquivos de dados binários, usamos normalmente:

```c
"rb"
"wb"
"r+b"
```

---

# 9. `fclose()`

```c
fclose(f);
```

Fecha o arquivo que foi aberto.

Isso **não significa apertar o X de uma janela**.

É uma operação do programa para informar à biblioteca:

> "Terminei de trabalhar com esse arquivo."

O arquivo deixa de ficar aberto pelo programa.

É importante fechar arquivos que foram abertos.

---

# 10. Por que fechar antes de `return` em alguns casos?

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
    fclose(entrada);
    return 1;
}
```

Se `entrada` abriu corretamente, mas `saida` falhou:

```text
entrada → aberto
saida   → não abriu
```

Como o programa vai sair imediatamente:

```c
return 1;
```

não chegaremos ao:

```c
fclose(entrada);
```

que está no final do programa.

Por isso precisamos fechar `entrada` **antes de sair**.

---

# 11. `fgetc()`

```c
c = fgetc(entrada);
```

Lê **um caractere/byte por vez** do arquivo.

Exemplo de arquivo:

```text
ABC
```

Podemos imaginar:

```text
fgetc() → A
fgetc() → B
fgetc() → C
fgetc() → \n
fgetc() → EOF
```

---

# 12. Por que `fgetc()` retorna `int` e não `char`?

Essa foi outra parte importante.

Embora `fgetc()` leia um caractere/byte, ela precisa conseguir retornar também:

```c
EOF
```

`EOF` significa:

> End Of File — fim do arquivo.

Por isso usamos:

```c
int c;
```

e não:

```c
char c;
```

A variável `int` consegue representar os valores dos bytes e também o valor especial `EOF`.

Por isso o padrão é:

```c
int c;

c = fgetc(entrada);

while(c != EOF)
{
    ...
    c = fgetc(entrada);
}
```

---

# 13. `EOF`

`EOF` significa **End Of File**.

Não é exatamente um caractere armazenado no arquivo.

É um valor especial retornado por funções de leitura para indicar que não existem mais dados para ler.

Por isso:

```c
while(c != EOF)
```

significa:

> Continue enquanto ainda houver dados no arquivo.

---

# 14. `fputc()`

```c
fputc(c, saida);
```

Escreve um caractere/byte no arquivo.

Assim:

```text
fgetc                 fputc

arquivo → programa    programa → arquivo
```

Exemplo:

```c
c = fgetc(entrada);
fputc(c, saida);
```

Lê um byte da entrada e escreve esse byte na saída.

---

# 15. Programa de cópia usando `fgetc` e `fputc`

A ideia:

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

O programa faz isso repetidamente até `EOF`.

---

# 16. `fread()` e `fwrite()`

Essas funções permitem trabalhar com **blocos de dados**, em vez de um byte por vez.

### `fwrite`

```text
MEMÓRIA → ARQUIVO
```

### `fread`

```text
ARQUIVO → MEMÓRIA
```

Essa é uma das coisas mais importantes para memorizar.

---

# 17. Parâmetros do `fwrite`

Formato:

```c
fwrite(dados, tamanho, quantidade, arquivo);
```

Pode pensar:

```text
fwrite(
    ONDE ESTÃO OS DADOS,
    TAMANHO DE CADA ITEM,
    QUANTOS ITENS,
    ARQUIVO
);
```

Exemplo:

```c
fwrite(p, sizeof(Pessoa), 1000, f);
```

Significa:

> Grave 1000 estruturas `Pessoa`, cada uma ocupando `sizeof(Pessoa)` bytes, começando em `p`, no arquivo `f`.

---

# 18. Parâmetros do `fread`

Formato:

```c
fread(destino, tamanho, quantidade, arquivo);
```

Pode pensar:

```text
fread(
    ONDE COLOCAR OS DADOS,
    TAMANHO DE CADA ITEM,
    QUANTOS ITENS,
    ARQUIVO
);
```

Exemplo:

```c
fread(p, sizeof(Pessoa), 1000, f);
```

Significa:

> Leia até 1000 estruturas `Pessoa` do arquivo `f` e coloque os dados em `p`.

---

# 19. `fwrite` x `fread`

| Função   | Direção           |
| -------- | ----------------- |
| `fwrite` | memória → arquivo |
| `fread`  | arquivo → memória |

Uma forma de lembrar:

```text
WRITE = ESCREVER NO ARQUIVO
READ  = LER DO ARQUIVO
```

---

# 20. `sizeof`

```c
sizeof(Pessoa)
```

pergunta:

> Quantos bytes uma `Pessoa` ocupa?

Se:

```text
sizeof(Pessoa) = 48
```

então:

```text
1 Pessoa = 48 bytes
```

Se temos:

```c
Pessoa p[1000];
```

o espaço total é:

```c
1000 * sizeof(Pessoa)
```

Ou seja:

> tamanho de uma Pessoa × quantidade de Pessoas.

---

# 21. `1000 * sizeof(Pessoa)`

Isso aparece, por exemplo, em:

```c
memset(p, 0, 1000 * sizeof(Pessoa));
```

Significa:

> A quantidade total de bytes ocupados pelas 1000 estruturas `Pessoa`.

Exemplo fictício:

```text
sizeof(Pessoa) = 48

1000 * 48 = 48000 bytes
```

Então estamos falando de 48000 bytes de memória.

---

# 22. `memset()`

`memset()` trabalha diretamente com uma região da memória.

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

---

## Por que usar `memset`?

Quando fazemos:

```c
Pessoa p[1000];
```

a memória pode conter valores que já estavam naquele espaço.

Não devemos assumir que tudo começa em zero.

Podemos então fazer:

```c
memset(p, 0, sizeof(p));
```

para zerar a região.

---

## Outra forma neste caso

Também podemos escrever:

```c
Pessoa p[1000] = {0};
```

Isso já inicializa o array com zero.

Para esse caso específico, é mais simples.

`memset()` é útil de conhecer porque é uma função geral para preencher uma região da memória.

---

# 23. `struct Pessoa`

Podemos criar uma estrutura:

```c
struct _Pessoa {
    char nome[40];
    int idade;
    float altura;
};
```

E criar um apelido:

```c
typedef struct _Pessoa Pessoa;
```

Assim podemos escrever:

```c
Pessoa p;
```

em vez de:

```c
struct _Pessoa p;
```

---

# 24. Array de estruturas

```c
Pessoa p[1000];
```

significa:

> Crie espaço para 1000 estruturas `Pessoa`.

Visualmente:

```text
p[0]     → Pessoa
p[1]     → Pessoa
p[2]     → Pessoa
...
p[999]   → Pessoa
```

Cada posição possui:

```text
nome
idade
altura
```

---

# 25. `strcpy()`

```c
strcpy(p[0].nome, "Renato Mauro");
```

Copia uma string para o array de caracteres `nome`.

```text
"Renato Mauro"
       ↓
p[0].nome
```

Não podemos fazer:

```c
p[0].nome = "Renato Mauro";
```

porque `nome` é um array de `char`.

Para colocar dados digitados pelo usuário, podemos usar, por exemplo:

```c
fgets(p[0].nome, 40, stdin);
```

Assim o nome pode vir do teclado.

---

# 26. `p` x `p[0]`

Se:

```c
Pessoa p[1000];
```

então:

```text
p       → endereço/início do array
p[0]    → primeira Pessoa
p[1]    → segunda Pessoa
p[2]    → terceira Pessoa
```

Por isso:

```c
fwrite(p, sizeof(Pessoa), 1000, f);
```

usa `p` como o ponto inicial dos dados.

---

# 27. Exemplo de `fwrite` com Pessoas

```c
Pessoa p[1000];

fwrite(p, sizeof(Pessoa), 1000, f);
```

Podemos interpretar:

```text
              tamanho      quantidade
                  ↓             ↓

fwrite(         p,       sizeof(Pessoa),   1000,   f);
                ↑                                  ↑
          início dos dados                       arquivo
```

Ou:

> Comece em `p`, pegue 1000 itens, considerando que cada item tem tamanho `sizeof(Pessoa)`, e grave no arquivo `f`.

---

# 28. Exemplo de `fread`

```c
Pessoa p[1000];

int qt = fread(p, sizeof(Pessoa), 1000, f);
```

Aqui os dados vão:

```text
ARQUIVO
   ↓
 fread()
   ↓
 MEMÓRIA
   ↓
p[0], p[1], p[2]...
```

`fread()` retorna a quantidade de **itens completos** que conseguiu ler.

Se:

```c
int qt = fread(p, sizeof(Pessoa), 1000, f);
```

e o arquivo possui 300 Pessoas:

```text
qt = 300
```

---

# 29. `fread` não retorna necessariamente bytes

Isso é importante.

Se fizermos:

```c
fread(p, sizeof(Pessoa), 1000, f);
```

o retorno representa quantas estruturas `Pessoa` foram lidas.

Se:

```text
sizeof(Pessoa) = 48
```

e foram lidas 300 Pessoas:

```text
retorno = 300
```

e não:

```text
14400
```

O tamanho e a quantidade foram informados separadamente.

---

# 30. `argc` e `argv`

Quando o programa recebe argumentos pelo terminal:

```c
./programa arquivo.txt saida.txt
```

temos:

```text
argc = 3
```

Porque o próprio nome do programa conta.

```text
argv[0] → ./programa
argv[1] → arquivo.txt
argv[2] → saida.txt
```

---

## `argc`

É:

> argument count

Quantidade de argumentos.

## `argv`

É:

> argument vector

Array de strings contendo os argumentos.

---

# 31. Por que verificar `argc`?

Se o programa espera:

```text
programa + arquivo
```

então:

```c
if(argc != 2)
```

Se espera:

```text
programa + origem + destino
```

então:

```c
if(argc != 3)
```

Isso evita tentar acessar:

```c
argv[1]
argv[2]
```

quando esses argumentos não foram fornecidos.

---

# 32. Contando linhas

Para contar linhas:

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

A ideia é simples:

> Cada ocorrência de `'\n'` representa uma quebra de linha.

Então:

```text
linha 1\n
linha 2\n
linha 3\n
```

possui 3 caracteres `'\n'`.

Logo:

```text
count = 3
```

---

# 33. Contando ocorrências de bytes

Um arquivo pode conter 256 valores diferentes de byte:

```text
0 até 255
```

Podemos criar:

```c
int contador[256] = {0};
```

Cada posição representa um byte.

```text
contador[0]   → quantidade de bytes 0
contador[1]   → quantidade de bytes 1
contador[2]   → quantidade de bytes 2
...
contador[65]  → quantidade do byte 65
...
contador[255] → quantidade do byte 255
```

---

# 34. Por que `contador[c]++`?

```c
c = fgetc(entrada);

while(c != EOF)
{
    contador[c]++;
    c = fgetc(entrada);
}
```

Suponha que `c` seja:

```text
65
```

Então:

```c
contador[65]++;
```

Aumenta a contagem daquele byte.

Como o valor 65 corresponde ao caractere `'A'` em ASCII:

```text
65 → 'A'
```

podemos depois mostrar:

```text
A: quantidade
```

---

# 35. Bytes e caracteres

Um `char` normalmente representa um byte.

Em ASCII, por exemplo:

```text
'A' → 65
'B' → 66
'C' → 67
'a' → 97
'b' → 98
'0' → 48
```

Por isso um valor numérico pode representar um caractere.

Exemplo:

```c
printf("%c", 65);
```

produz:

```text
A
```

Enquanto:

```c
printf("%d", 65);
```

produz:

```text
65
```

O valor é o mesmo; o formato de impressão muda.

---

# 36. Atenção ao imprimir bytes como `%c`

No exercício:

```c
printf("%c: %d\n", i, contador[i]);
```

isso mostra o byte como caractere.

Mas nem todos os 256 valores representam letras imprimíveis.

Alguns representam:

* controle;
* quebra de linha;
* tabulação;
* outros valores não visíveis.

Por isso, se o exercício pede **apenas letras**, pode ser necessário filtrar os valores para imprimir somente os caracteres desejados.

---

# 37. Arquivo binário com estruturas

Podemos gravar diretamente uma estrutura:

```c
fwrite(&p, sizeof(Pessoa), 1, f);
```

ou várias:

```c
fwrite(p, sizeof(Pessoa), 1000, f);
```

Nesse caso, o arquivo contém os bytes da representação da estrutura na memória.

Isso é muito útil para trabalhar com **registros**.

Por exemplo:

```text
pessoas.dat

[Pessoa 0]
[Pessoa 1]
[Pessoa 2]
...
```

Cada registro possui tamanho:

```c
sizeof(Pessoa)
```

Isso permite localizar um registro pelo seu número.

---

# 38. Por que arquivos binários são importantes em Estrutura de Arquivos?

Porque podemos organizar um arquivo como uma sequência de **registros de tamanho conhecido**.

Por exemplo:

```text
Arquivo:

registro 0
registro 1
registro 2
registro 3
registro 4
...
```

Se cada registro tiver 100 bytes:

```text
registro 0 → posição 0
registro 1 → posição 100
registro 2 → posição 200
registro 3 → posição 300
```

Isso permite usar funções como:

```c
fseek()
ftell()
```

e posteriormente fazer coisas como **acesso direto e busca binária em arquivos**.

---

# 39. `fseek()` e `ftell()` — ideia inicial

`ftell()` informa a posição atual dentro do arquivo.

```c
long pos = ftell(f);
```

`fseek()` muda a posição:

```c
fseek(f, posicao, SEEK_SET);
```

Por exemplo:

```c
fseek(f, 300, SEEK_SET);
```

significa:

> Vá para o byte 300 do arquivo.

Isso é diferente de ler tudo desde o começo.

É chamado de **acesso direto**.

---

# 40. Relação com busca binária

Em um arquivo de registros ordenados, podemos calcular:

```text
início
fim
meio
```

e usar:

```c
fseek()
```

para ir diretamente ao registro do meio.

Assim podemos fazer uma busca binária sem precisar ler o arquivo inteiro.

Exemplo conceitual:

```text
Arquivo ordenado por CEP

[00001]
[00002]
[00003]
[00004]
[00005]
[00006]
[00007]

              ↑
             meio

fseek() → vai diretamente até o registro
```

Isso conecta a parte de **manipulação de arquivos** com a parte de **busca binária e ordenação**.

---

# 41. Visão geral do que estou aprendendo

## Manipulação básica

```text
fopen()
   ↓
abre arquivo

fgetc() / fread()
   ↓
lê

fputc() / fwrite()
   ↓
escreve

fclose()
   ↓
fecha
```

## Memória

```text
struct
arrays
ponteiros
sizeof
memset
```

## Arquivos binários

```text
bytes
registros
fread
fwrite
```

## Acesso direto

```text
fseek
ftell
```

## Algoritmos sobre arquivos

```text
ordenação
      ↓
arquivo ordenado
      ↓
busca binária
```

---

# 42. O que realmente preciso saber de cada função

### `fopen`

```c
FILE *f = fopen("arquivo", "rb");
```

> Abre o arquivo e retorna um `FILE *`.

### `fclose`

```c
fclose(f);
```

> Fecha o arquivo aberto.

### `fgetc`

```c
c = fgetc(f);
```

> Lê um byte/caractere.

### `fputc`

```c
fputc(c, f);
```

> Escreve um byte/caractere.

### `fread`

```c
fread(destino, tamanho, quantidade, f);
```

> Lê um bloco do arquivo para a memória.

### `fwrite`

```c
fwrite(origem, tamanho, quantidade, f);
```

> Grava um bloco da memória no arquivo.

### `fseek`

```c
fseek(f, posicao, SEEK_SET);
```

> Move a posição atual dentro do arquivo.

### `ftell`

```c
ftell(f);
```

> Descobre a posição atual dentro do arquivo.

---

# 43. Mapa mental

```text
                 ESTRUTURA DE ARQUIVOS
                         │
             ┌───────────┴───────────┐
             │                       │
          MEMÓRIA                 ARQUIVO
             │                       │
        ┌────┴────┐             ┌────┴────┐
        │         │             │         │
      struct    array          texto    binário
        │         │                       │
        └────┬────┘                       │
             │                            │
          ponteiros                   registros
             │                            │
          sizeof                     fread/fwrite
             │                            │
          memset                         │
             │                            │
             └────────────┬───────────────┘
                          │
                     acesso direto
                          │
                    fseek / ftell
                          │
                  ┌───────┴───────┐
                  │               │
              ordenação      busca binária
```

---

# 44. As principais coisas que não posso confundir

### `FILE *f`

`f` é um **ponteiro para `FILE`**.

### `f`

É o endereço armazenado no ponteiro.

### `*f`

É acessar o `FILE` naquele endereço.

### `fopen()`

Retorna um `FILE *`.

### `fclose()`

Recebe um `FILE *`.

Por isso:

```c
fclose(f);
```

e não:

```c
fclose(*f);
```

---

### `fwrite`

```text
MEMÓRIA → ARQUIVO
```

### `fread`

```text
ARQUIVO → MEMÓRIA
```

### `fgetc`

Lê **um byte por vez**.

### `fread`

Lê **vários itens de uma vez**.

### `fputc`

Escreve **um byte por vez**.

### `fwrite`

Escreve **vários itens de uma vez**.

### `EOF`

Não é um caractere comum do arquivo.

É um valor especial usado para indicar que a leitura chegou ao fim.

### `int c`

`fgetc()` usa `int` porque precisa conseguir representar tanto os valores dos bytes quanto `EOF`.

### `sizeof(Pessoa)`

É o tamanho de uma `Pessoa` em bytes.

### `1000 * sizeof(Pessoa)`

É o tamanho total de 1000 Pessoas em bytes.

### `memset`

Manipula/preenche diretamente uma região da memória.

### `Pessoa p[1000]`

Array contendo 1000 estruturas `Pessoa`.

---

# 45. Frase para lembrar `fread` e `fwrite`

```text
fread:
ARQUIVO → MEMÓRIA

fwrite:
MEMÓRIA → ARQUIVO
```

E:

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
