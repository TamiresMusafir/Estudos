# REVISÃO DE C — CONCEITOS E LÓGICA

Material de revisão dos conceitos básicos de C e dos principais padrões de lógica usados nos exercícios.

---

# 1. COMO PENSAR ANTES DE PROGRAMAR

Antes de escrever o código, transforme o enunciado em perguntas:

```text
1. O que eu tenho?
2. O que preciso produzir?
3. O que preciso guardar?
4. Preciso percorrer quantas vezes?
5. O que faz a repetição parar?
6. O que preciso comparar?
7. O que preciso atualizar?
```

### Exemplo

> Conte quantos números são positivos, negativos e zeros.

Pensamento:

```text
Tenho → vários números

Preciso produzir → 3 quantidades

Preciso guardar → 3 contadores

Preciso repetir → uma vez para cada número

Preciso classificar:
→ número > 0
→ número == 0
→ número < 0
```

Código:

```c
positivos = negativos = zeros = 0;

for (int i = 0; i < qtd; i++) {

    if (numeros[i] > 0)
        positivos++;

    else if (numeros[i] == 0)
        zeros++;

    else
        negativos++;
}
```

---

# 2. VARIÁVEL E PONTEIRO

## Variável normal

```c
int qtd;
```

Guarda um valor.

```text
qtd   → conteúdo
&qtd  → endereço de qtd
```

## Ponteiro

```c
int *p;
```

Guarda um endereço.

```text
p   → endereço
*p  → conteúdo daquele endereço
```

### Regra

```text
x    → valor
&x   → endereço de x
*x   → valor apontado por x
```

### Passar variável por referência

```c
void funcao(int *qtd)
```

Chamando:

```c
funcao(&qtd);
```

Dentro da função:

```c
(*qtd)++;
```

Isso altera a variável original.

---

# 3. VETORES

Declaração:

```c
int numeros[MAX];
```

Acessos:

```c
numeros[0]
numeros[1]
numeros[i]
```

Estrutura básica para percorrer:

```c
for (int i = 0; i < qtd; i++) {
    // numeros[i]
}
```

### Regra

```text
vetor → v[i]
```

---

# 4. CONTADOR

Quando o enunciado pergunta:

> Quantos...?

Use um contador.

```c
int cont = 0;
```

Quando encontrar algo que deve ser contado:

```c
cont++;
```

### Exemplo

Contar números pares:

```c
int cont = 0;

for (int i = 0; i < qtd; i++) {

    if (numeros[i] % 2 == 0)
        cont++;
}
```

### Padrão

```text
"quantos?" → contador = 0
             ↓
          condição?
             ↓
            sim
             ↓
          contador++
```

---

# 5. ACUMULADOR

## Soma

Quando o enunciado pede uma soma:

```c
int soma = 0;
```

Depois:

```c
soma += valor;
```

Exemplo:

```c
int soma = 0;

for (int i = 0; i < qtd; i++)
    soma += numeros[i];
```

---

## Produto

Para multiplicação:

```c
int produto = 1;
```

Depois:

```c
produto *= valor;
```

### Regra

```text
soma    → começa em 0
produto → começa em 1
```

Exemplo:

```c
int produto = 1;

for (int i = 0; i < qtd; i++) {

    if (numeros[i] % 2 == 0)
        produto *= numeros[i];
}
```

Se nenhum número foi multiplicado, o produto continua `1`.

Se a questão quiser retornar `0` nesse caso:

```c
if (produto == 1)
    produto = 0;
```

---

# 6. MÉDIA

Fórmula:

```text
média = soma / quantidade
```

Em C, para garantir divisão decimal:

```c
media = (float)soma / qtd;
```

Exemplo:

```c
float soma = 0;
float media;

media = soma / qtd;
```

Ou, se `soma` e `qtd` forem inteiros:

```c
media = (float)soma / qtd;
```

---

# 7. IF / ELSE IF / ELSE

Usado para tomar decisões e classificar valores.

```c
if (condicao1)
    ...
else if (condicao2)
    ...
else
    ...
```

### Exemplo

```c
if (numero > 0)
    positivos++;

else if (numero == 0)
    zeros++;

else
    negativos++;
```

Pensamento:

```text
é positivo?
  ↓ não
é zero?
  ↓ não
então é negativo
```

---

# 8. MAIOR E MENOR

Esse é um dos principais padrões de lógica.

A ideia é guardar o:

> maior encontrado até agora

ou:

> menor encontrado até agora

## Maior

```c
int maior;

scanf("%d", &maior);

for (int i = 1; i < qtd; i++) {

    int x;
    scanf("%d", &x);

    if (x > maior)
        maior = x;
}
```

### Pensamento

```text
primeiro valor
     ↓
maior por enquanto
     ↓
próximo valor
     ↓
é maior?
  ↓ sim
substitui
```

---

## Menor

```c
int menor;

scanf("%d", &menor);

for (int i = 1; i < qtd; i++) {

    int x;
    scanf("%d", &x);

    if (x < menor)
        menor = x;
}
```

---

# 9. MAIOR/MENOR COM STRUCT

Uma `struct` também pode ser usada como uma variável inteira.

Exemplo:

```c
typedef struct Pagamento {
    char cpf[12];
    char nome[80];
    int mes;
    int ano;
    float valor;
} Pagamento;
```

Podemos criar:

```c
Pagamento p;
Pagamento maior;
Pagamento menor;
```

`maior` é uma variável que consegue guardar **um Pagamento inteiro**:

```text
maior
├── cpf
├── nome
├── mes
├── ano
└── valor
```

## Copiar uma struct

```c
maior = p;
```

Isso copia todos os campos de `p` para `maior`.

Não estamos dizendo que `maior` guarda somente o valor.

Estamos dizendo:

> "O registro `p` é o maior que encontrei até agora."

Depois:

```c
if (p.valor > maior.valor)
    maior = p;
```

### Padrão

```text
primeiro registro
       ↓
maior = primeiro
menor = primeiro
       ↓
próximo registro
       ↓
valor > maior.valor?
       ↓ SIM
maior = registro atual
       ↓
próximo...
```

---

# 10. POR QUE INICIALIZAR MAIOR E MENOR COM O PRIMEIRO?

No início, ainda não sabemos qual é o maior ou o menor.

Se o primeiro registro for:

```text
Ana — R$ 500
```

Podemos começar com:

```c
maior = p;
menor = p;
```

Agora:

```text
maior → Ana R$500
menor → Ana R$500
```

Isso é provisório.

Se aparecer:

```text
Bruno — R$800
```

temos:

```c
if (p.valor > maior.valor)
    maior = p;
```

Agora:

```text
maior → Bruno R$800
menor → Ana R$500
```

Se aparecer:

```text
Carlos — R$300
```

temos:

```c
if (p.valor < menor.valor)
    menor = p;
```

Agora:

```text
maior → Bruno R$800
menor → Carlos R$300
```

### IMPORTANTE

```c
maior = p;
menor = p;
```

no início = **inicialização**

```c
if (...)
    maior = p;
```

depois = **atualização**

---

# 11. STRUCT

Uma `struct` agrupa vários dados relacionados.

```c
struct cliente {
    int conta;
    float saldo;
};
```

Criando uma variável:

```c
struct cliente c;
```

Com `typedef`:

```c
typedef struct cliente Tcliente;
```

Podemos usar:

```c
Tcliente c;
```

Acessando campos:

```c
c.conta
c.saldo
```

---

# 12. VETOR DE STRUCT

```c
Tcliente clientes[MAX];
```

Cada posição é uma struct:

```text
clientes[0]
clientes[1]
clientes[2]
...
```

Acessando um campo:

```c
clientes[i].conta
clientes[i].saldo
```

Percorrendo:

```c
for (int i = 0; i < qtd; i++) {

    printf("%d", clientes[i].conta);
    printf("%.2f", clientes[i].saldo);
}
```

### Regra

```text
vetor normal:
v[i]

vetor de struct:
v[i].campo
```

---

# 13. COPIAR STRUCT

Struct pode ser atribuída diretamente:

```c
Pagamento a;
Pagamento b;

b = a;
```

Todos os campos são copiados.

Isso também permite trocar duas structs:

```c
livro aux;

aux = livros[min];
livros[min] = livros[k];
livros[k] = aux;
```

Padrão:

```text
aux = A
A = B
B = aux
```

---

# 14. FOR

Use `for` quando a repetição tem uma quantidade conhecida ou controlada por um contador.

```c
for (int i = 0; i < qtd; i++) {
    ...
}
```

Exemplos:

```text
6 anos
12 meses
1000 produtos
15 candidatos
```

Padrão:

```c
for (inicialização; condição; incremento) {
    ...
}
```

---

# 15. WHILE

Use `while` quando a repetição depende de uma condição.

```c
while (condicao) {
    ...
}
```

Exemplo:

```c
while (codigo != 0) {
    ...
}
```

Significa:

> continue enquanto o usuário não digitar 0.

Outro exemplo:

```c
while (fread(&p, sizeof(Pagamento), 1, f) == 1) {
    ...
}
```

Significa:

> continue enquanto conseguir ler um registro.

### Regra mental

```text
quantidade conhecida → for

repetir enquanto uma condição for verdadeira
→ while
```

---

# 16. WHILE COM QUANTIDADE DESCONHECIDA

Padrão muito importante:

```c
int i = 0;

leia();

while (condicao && i < MAX) {

    vetor[i] = ...;

    i++;

    leia();
}

return i;
```

Exemplo:

```c
int i = 0;

scanf("%d", &codigo);

while (codigo != 0 && i < MAX) {

    clientes[i].conta = codigo;

    scanf("%f", &clientes[i].saldo);

    i++;

    scanf("%d", &codigo);
}

return i;
```

### Por que `i++`?

Porque cada vez que um registro é armazenado:

```text
i = 0 → primeira posição
i = 1 → segunda posição
i = 2 → terceira posição
```

No final, `i` representa a quantidade de registros armazenados.

---

# 17. BREAK

```c
break;
```

Sai **completamente** do loop.

Exemplo:

```c
while (...) {

    if (valor > limite)
        break;
}
```

Pensamento:

```text
break → "PARA o loop inteiro"
```

---

# 18. CONTINUE

```c
continue;
```

Abandona somente a **iteração atual** e vai para a próxima.

Exemplo:

```c
while (...) {

    if (valor < 0)
        continue;

    printf("%d\n", valor);
}
```

Se `valor < 0`:

```text
continue
   ↓
pula o restante dessa volta
   ↓
próxima volta
```

### Diferença

```text
break
→ sai do loop

continue
→ pula esta volta e continua o loop
```

---

# 19. BUSCA SEQUENCIAL

Para procurar um elemento em um vetor:

```c
int busca(Tpro v[], int codigo)
{
    for (int i = 0; i < TOT; i++) {

        if (v[i].cod == codigo)
            return i;
    }

    return -1;
}
```

### Lógica

```text
percorre
   ↓
achou?
 ↓     ↓
sim    não
 ↓      ↓
return  continua
posição
         ↓
fim do vetor
         ↓
return -1
```

### Regra

```text
return i  → encontrou na posição i

return -1 → não encontrou
```

---

# 20. BUSCA EM STRUCT

Se o vetor é de struct:

```c
if (v[i].cod == codigo)
```

Não esquecer o campo:

```text
v[i].cod
```

e não apenas:

```text
v[i]
```

---

# 21. BUSCA POR STRING

Para comparar strings:

```c
strcmp(a, b) == 0
```

Significa:

> strings iguais.

Exemplo:

```c
if (strcmp(v[i].nome, nome) == 0)
    return i;
```

Não usar:

```c
a == b
```

para comparar conteúdo de strings.

### Resumo

```text
strcmp(a, b) == 0 → iguais
strcmp(a, b) != 0 → diferentes
```

---

# 22. STRINGS — LEITURA

Para uma string simples:

```c
scanf("%s", nome);
```

Para ler uma linha com espaços:

```c
scanf(" %[^\n]", nome);
```

O vetor de `char` já representa um endereço, então normalmente:

```c
scanf("%s", nome);
```

e não:

```c
scanf("%s", &nome);
```

---

# 23. BUSCA BINÁRIA

Só funciona corretamente com o vetor **ordenado**.

Variáveis:

```c
int ini = 0;
int fim = qtd - 1;
int pos = -1;
```

Loop:

```c
while (pos == -1 && ini <= fim)
```

Pega o meio:

```c
int med = (ini + fim) / 2;
```

Compara:

```c
if (v[med].codigo == codigo)
    pos = med;
```

Se o meio é menor que o procurado:

```c
ini = med + 1;
```

Procura na metade direita.

Se o meio é maior:

```c
fim = med - 1;
```

Procura na metade esquerda.

### Visualização

```text
[ esquerda | meio | direita ]

meio == procurado
→ achou

meio < procurado
→ procura direita

meio > procurado
→ procura esquerda
```

---

# 24. ORDENAÇÃO — SELECTION SORT

Ideia:

```text
procura o menor
      ↓
guarda a posição
      ↓
troca com a posição atual
      ↓
repete
```

Código:

```c
for (int k = 0; k < qtd - 1; k++) {

    int min = k;

    for (int i = k + 1; i < qtd; i++) {

        if (livros[i].codigo < livros[min].codigo)
            min = i;
    }

    if (min != k) {

        livro aux;

        aux = livros[min];
        livros[min] = livros[k];
        livros[k] = aux;
    }
}
```

### O que `min` guarda?

Não guarda o menor valor.

Guarda a **posição do menor**.

```text
min → índice
```

---

# 25. MATRIZ

Uma matriz:

```c
int matriz[6][12];
```

possui:

```text
6 linhas
12 colunas
```

Acesso:

```c
matriz[i][k]
```

onde:

```text
i → linha
k → coluna
```

---

# 26. SOMAR CADA LINHA

Exemplo:

```c
for (int i = 0; i < 6; i++) {

    int soma = 0;

    for (int k = 0; k < 12; k++)
        soma += matriz[i][k];

    printf("%d\n", soma);
}
```

Pensamento:

```text
fixa a linha
     ↓
percorre todas as colunas
     ↓
soma a linha
```

---

# 27. SOMAR CADA COLUNA

```c
for (int k = 0; k < 12; k++) {

    int soma = 0;

    for (int i = 0; i < 6; i++)
        soma += matriz[i][k];

    printf("%d\n", soma);
}
```

Pensamento:

```text
fixa a coluna
     ↓
percorre todas as linhas
     ↓
soma a coluna
```

### Regra

```text
cada linha
→ primeiro índice fica fixo

cada coluna
→ segundo índice fica fixo
```

---

# 28. MATRIZ — PRODUTO/VALOR TOTAL

Se cada posição possui quantidade e preço:

```c
total += quantidade[i][k] * preco[i][k];
```

Se precisa calcular por linha:

```c
for (int i = 0; i < linhas; i++) {

    float total = 0;

    for (int k = 0; k < colunas; k++)
        total += quantidade[i][k] * preco[i][k];

    printf("%.2f\n", total);
}
```

### Atenção

Se o total é calculado separadamente para cada linha, inicialize dentro do primeiro `for`:

```c
for (...) {
    float total = 0;
    ...
}
```

Senão a soma continua acumulando o valor da linha anterior.

---

# 29. INICIALIZAÇÃO

Antes de usar uma variável como contador ou acumulador:

```c
int cont = 0;
int soma = 0;
int produto = 1;
float total = 0;
```

Para structs:

```c
Pagamento maior = p;
Pagamento menor = p;
```

Para vetor:

```c
for (int i = 0; i < MAX; i++)
    registro[i] = 0;
```

### Regra

Sempre pergunte:

> "Essa variável precisa começar com algum valor conhecido?"

---

# 30. FUNÇÕES

Uma função recebe dados e pode:

- retornar um valor;
- modificar valores através de ponteiros;
- trabalhar com vetores/structs.

Exemplo:

```c
int busca(int v[], int qtd, int procurado)
```

Retorna uma posição.

Exemplo:

```c
void calcula(int v[], int qtd, int *resultado)
```

Não retorna diretamente, mas pode alterar `resultado`.

---

# 31. `RETURN`

Quando a função retorna um valor:

```c
int busca(...)
{
    ...
    return i;
}
```

Quando a função é `void`:

```c
void exibe(...)
{
    ...
}
```

Não precisa retornar um valor.

### Em `main`

```c
return 0;
```

Normalmente indica execução bem-sucedida.

---

# 32. PADRÕES DE LÓGICA — FOLHA RÁPIDA

```text
┌─────────────────────────────────────────────┐
│ PADRÕES DE LÓGICA                           │
├─────────────────────────────────────────────┤
│ "quantos?"                                  │
│ → contador = 0                              │
│ → condição → contador++                     │
│                                             │
│ "soma?"                                     │
│ → soma = 0                                  │
│ → soma += valor                             │
│                                             │
│ "produto?"                                  │
│ → produto = 1                               │
│ → produto *= valor                          │
│                                             │
│ "maior?"                                    │
│ → maior = primeiro                          │
│ → se atual > maior → maior = atual          │
│                                             │
│ "menor?"                                    │
│ → menor = primeiro                          │
│ → se atual < menor → menor = atual          │
│                                             │
│ "procurar?"                                 │
│ → percorre                                  │
│ → achou → return posição                    │
│ → não achou → return -1                    │
│                                             │
│ quantidade conhecida → for                  │
│ condição/quantidade desconhecida → while   │
│                                             │
│ break → sai do loop                         │
│ continue → próxima iteração                 │
│                                             │
│ vetor → v[i]                                │
│ struct → v.campo                            │
│ vetor de struct → v[i].campo                │
│ matriz → m[linha][coluna]                   │
│                                             │
│ struct a = b → copia a struct inteira      │
└─────────────────────────────────────────────┘
```

---

# 33. COMO QUEBRAR UM EXERCÍCIO DE LÓGICA

Quando travar, **não tente imaginar o código inteiro**.

Faça:

```text
ENUNCIADO
    ↓
O que preciso descobrir?
    ↓
O que preciso guardar?
    ↓
O que preciso comparar?
    ↓
Quando preciso atualizar?
    ↓
Quantas vezes preciso repetir?
    ↓
Quando paro?
    ↓
AGORA escrevo o código
```

### Exemplo: maior benefício de cada ano

```text
O que preciso descobrir?
→ maior e menor

O que preciso guardar?
→ Pagamento maior
→ Pagamento menor

O que comparo?
→ p.valor

Quando atualizo?
→ p.valor > maior.valor
→ p.valor < menor.valor

Como separo os anos?
→ p.ano

O arquivo está ordenado?
→ sim

Então:
→ processo todos do mesmo ano
→ quando muda o ano, finalizo aquele grupo
→ começo o próximo
```

---

# 34. PADRÃO "GRUPOS"

Esse padrão é importante para arquivos ordenados.

Exemplo:

```text
2023
2023
2023
2024
2024
2025
2025
2025
```

A ideia é:

```text
pega o ano atual
      ↓
processa todos os registros desse ano
      ↓
ano mudou?
      ↓
finaliza o grupo
      ↓
começa o próximo ano
```

Visualmente:

```text
┌──────────────┐
│ GRUPO 2023   │
│ 2023         │
│ 2023         │
│ 2023         │
└──────────────┘
       ↓
   processa
       ↓
┌──────────────┐
│ GRUPO 2024   │
│ 2024         │
│ 2024         │
└──────────────┘
       ↓
   processa
       ↓
┌──────────────┐
│ GRUPO 2025   │
│ 2025         │
│ 2025         │
│ 2025         │
└──────────────┘
```

Esse padrão aparece quando o arquivo está ordenado por alguma chave, como:

```text
ano
mês
código
CPF
```

---

# 35. RESUMO FINAL — O QUE RECONHECER NO ENUNCIADO

```text
"quantos"
→ contador

"somatório", "total"
→ acumulador

"produto"
→ acumulador começando em 1

"média"
→ soma / quantidade

"maior"
→ maior até agora

"menor"
→ menor até agora

"procurar"
→ busca + índice

"não encontrado"
→ -1

"para cada"
→ geralmente for

"enquanto"
→ while

"até digitar 0"
→ while

"pare"
→ break

"ignore este"
→ continue

"por ano", "por departamento", "por categoria"
→ provavelmente processamento por grupos

"ordenado"
→ pode permitir parar mais cedo ou usar busca binária

"struct"
→ agrupa informações relacionadas

"Pagamento maior"
→ variável capaz de guardar um registro Pagamento

"maior = p"
→ copia o registro inteiro
```

---

# 36. REGRA MAIS IMPORTANTE

Quando a lógica não estiver óbvia, **não tente inventar o código**.

Volte para:

```text
O QUE EU TENHO?
        ↓
O QUE EU QUERO?
        ↓
O QUE PRECISO GUARDAR?
        ↓
O QUE PRECISO COMPARAR?
        ↓
O QUE FAÇO QUANDO A CONDIÇÃO ACONTECE?
        ↓
COMO REPITO?
```

A lógica vai ficando automática conforme esses padrões aparecem várias vezes.
