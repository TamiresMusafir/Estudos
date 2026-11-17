# Árvores B e B+ — guia de estudo

Material de **Organização de Estruturas de Arquivos** (CEFET/RJ). Foco em **conceito** e em **desenhar/calcular** as árvores, que é o que cai na prova, mais o uso da árvore B em código (você **não** implementa a árvore, só chama as funções dela). O código aparece em dois lugares: a [seção 15](#15-ligação-com-o-código-de-estudo) liga os conceitos ao `ArvoreB.c` de estudo, e a [seção 18](#18-código-da-p2-usar-a-árvore-b-como-caixa-preta) mostra como **usar** uma árvore B pronta (a P2 pede isso).

> Os exemplos foram conferidos por simulação. Os exercícios resolvidos vêm da P2 de 2023.1 (Prof. Renato Mauro). Convenções de desenho variam de professor para professor: veja a [seção 2](#2-convenções-usadas-aqui) e confirme as do seu.

## Índice

1. [Por que existem](#1-por-que-existem)
2. [Convenções usadas aqui](#2-convenções-usadas-aqui)
3. [Vocabulário](#3-vocabulário)
4. [Árvore B: propriedades](#4-árvore-b-propriedades)
5. [Árvore B: busca](#5-árvore-b-busca)
6. [Árvore B: inserção](#6-árvore-b-inserção)
7. [Árvore B: remoção](#7-árvore-b-remoção)
8. [Árvore B+: estrutura e operações](#8-árvore-b-estrutura-e-operações)
9. [Comparação entre B e B+](#9-comparação-entre-b-e-b)
10. [Dimensionamento pelo bloco de disco](#10-dimensionamento-pelo-bloco-de-disco)
11. [Ocupação média, níveis e altura](#11-ocupação-média-níveis-e-altura)
12. [Exercícios resolvidos](#12-exercícios-resolvidos)
13. [Para treinar](#13-para-treinar)
14. [Erros comuns](#14-erros-comuns)
15. [Ligação com o código de estudo](#15-ligação-com-o-código-de-estudo)
16. [Cola de prova](#16-cola-de-prova)
17. [Teoria cobrada na P2: respostas-modelo](#17-teoria-cobrada-na-p2-respostas-modelo)
18. [Código da P2: usar a árvore B como caixa-preta](#18-código-da-p2-usar-a-árvore-b-como-caixa-preta)

---

## 1. Por que existem

No disco, o que custa caro é **ler um bloco**. Comparar chaves na memória é quase de graça. Então o custo de uma busca se mede em **quantos blocos são lidos**.

| Estrutura (700 mil registros) | Leituras de disco por busca |
|---|---|
| Árvore binária balanceada (1 chave por nó) | ≈ 20 (log₂ 700.000) |
| Árvore B com ~300 chaves por nó | 2 ou 3 |

A ideia: **um nó = um bloco de disco**, com muitas chaves e muitos filhos. A árvore fica **baixa e larga**, e a altura é o número de leituras.

---

## 2. Convenções usadas aqui

- **Ordem/grau `n`** = número **máximo de ponteiros de bloco (filhos)** por nó. Logo, no máximo **n − 1 chaves**. (Alguns livros usam "ordem" de outro jeito; na dúvida, siga o enunciado.)
- **Altura** = número de níveis. A raiz é o **nível 1**.
- **Split (divisão):** o nó estoura quando passa de n − 1 chaves. Com `k` chaves após o estouro, **sobe a chave de índice ⌊(k−1)/2⌋** (contando de 0). Se `k` é ímpar, é a do meio exato; se é par, é a **do meio-esquerda**. Outro professor pode subir a do meio-direita: o desenho muda, a lógica não.
- **Split de folha na B+:** a metade esquerda fica com ⌈k/2⌉ chaves.
- Em prova, **escreva a convenção que usou** em uma linha.

---

## 3. Vocabulário

| Termo | Significado |
|---|---|
| Nó / página / bloco | A mesma coisa: a unidade lida do disco |
| Chave (`V`) | O valor de busca (ex.: um CEP) |
| Ponteiro de dados (`Pr`) | Aponta para o **registro** no arquivo de dados |
| Ponteiro de bloco (`Pb`) | Aponta para um **filho** (outro nó da árvore) |
| Raiz / interno / folha | Topo / nó com filhos / nó sem filhos |
| Overflow | Nó com chaves demais após uma inserção |
| Underflow | Nó com chaves de menos após uma remoção |
| Split | Dividir um nó que estourou em dois |
| Merge (fusão) | Juntar dois nós irmãos que ficaram pequenos |
| Fator de ocupação | Quanto do nó está preenchido, em média (ex.: 70%) |

---

## 4. Árvore B: propriedades

Cada nó guarda, no máximo: **n ponteiros de bloco**, **n − 1 chaves** e **n − 1 ponteiros de dados** (um por chave).

```
┌────┬─────┬────┬─────┬────┬─────┬────┐
│ P0 │ K1  │ P1 │ K2  │ P2 │ ... │ Pn │   P = ponteiro para filho
└────┴─────┴────┴─────┴────┴─────┴────┘   K = chave (+ ponteiro para o registro)
```

Regras:

1. As chaves do nó estão **em ordem**. O filho `Pi` guarda só chaves entre `Ki` e `Ki+1`.
2. **Todas as folhas estão no mesmo nível** (a árvore é sempre balanceada).
3. Cada chave aparece **uma única vez** em toda a árvore (nó interno ou folha).
4. Limites por nó:

| Tipo de nó | Chaves | Filhos |
|---|---|---|
| Qualquer nó | no máximo **n − 1** | no máximo **n** |
| Nó que **não é raiz** | no mínimo **⌈n/2⌉ − 1** | no mínimo **⌈n/2⌉** |
| **Raiz** | no mínimo **1** | no mínimo **2** (se não for folha) |

Exemplo, n = 24: máximo 23 chaves; mínimo em nó não raiz ⌈24/2⌉ − 1 = **11** chaves.

---

## 5. Árvore B: busca

1. Comece na raiz.
2. Compare a chave procurada com as do nó, em ordem:
   - **igual** → achou (pode ser em qualquer nível), use o ponteiro de dados;
   - **menor que `Ki`** → desça pelo filho à esquerda de `Ki`;
   - **maior que todas** → desça pelo último filho.
3. Se chegar a uma folha sem achar, a chave **não existe**.

Na árvore abaixo, buscando o **5**: raiz `[4]` → 5 > 4, vai à direita → `[6]` → 5 < 6, vai à esquerda → folha `[5]`. Achou, em 3 leituras.

```
                 [ 4 ]
               /       \
          [ 2 ]         [ 6 ]
         /     \       /     \
      [1]      [3]   [5]      [7]
```

---

## 6. Árvore B: inserção

Regras:

1. **Desça** até a folha onde a chave deve ficar (como na busca).
2. **Insira em ordem** na folha.
3. Se a folha **não estourou**, acabou.
4. Se **estourou**, faça o **split**: a chave escolhida (ver [seção 2](#2-convenções-usadas-aqui)) **sobe** para o pai, e o resto se divide em dois nós.
5. O pai recebe a chave. Se ele também estourar, repete o split nele, subindo.
6. Se a **raiz** estourar, nasce uma **raiz nova** com 1 chave, e a **altura aumenta em 1**. A árvore cresce **por cima**, e é por isso que continua balanceada.

### Exemplo: n = 3 (máximo 2 chaves por nó), inserindo 1, 2, 3, 4, 5, 6, 7

| Insere | O que acontece | Árvore (nível por nível) |
|---|---|---|
| 1 | cabe | `[1]` |
| 2 | cabe | `[1,2]` |
| 3 | `[1,2,3]` **estoura**: o 2 sobe, nasce raiz nova | `[2]` / `[1] [3]` |
| 4 | cabe na folha da direita | `[2]` / `[1] [3,4]` |
| 5 | `[3,4,5]` estoura: o 4 sobe para a raiz | `[2,4]` / `[1] [3] [5]` |
| 6 | cabe | `[2,4]` / `[1] [3] [5,6]` |
| 7 | `[5,6,7]` estoura: o 6 sobe e a raiz `[2,4,6]` **também estoura**: o 4 sobe, nasce raiz nova | `[4]` / `[2] [6]` / `[1] [3] [5] [7]` |

Resultado: **altura 3** (o desenho está na seção 5). Dica de prova: **escreva o nó estourado** (ex.: `[3,4,5]`) antes de dividir, para o corretor ver o raciocínio.

---

## 7. Árvore B: remoção

O objetivo é nunca deixar um nó (que não é a raiz) abaixo do mínimo ⌈n/2⌉ − 1 chaves.

1. **Chave em nó interno:** troque-a pelo **predecessor** (maior chave da subárvore esquerda) ou pelo **sucessor** (menor da direita) e remova esse valor da folha.
2. **Remova da folha.** Se ela ainda tem o mínimo, acabou.
3. **Underflow** (ficou abaixo do mínimo):
   - se um **irmão tem chave sobrando**, faça uma **redistribuição**: uma chave do irmão sobe para o pai, e a chave do pai que separava os dois desce para o nó pequeno;
   - se **nenhum irmão tem sobra**, faça a **fusão (merge)**: junte o nó, o irmão e a chave do pai que os separa. O pai perde uma chave e pode entrar em underflow, então repita subindo.
4. Se a raiz ficar **sem chaves**, o filho único vira a raiz e a **altura diminui em 1**.

(A remoção costuma cair menos que a inserção; confirme com o professor.)

---

## 8. Árvore B+: estrutura e operações

### Estrutura

- **Nó interno:** só **chaves-guia** e **ponteiros de bloco**. **Sem ponteiros de dados.**
- **Folha:** **todas** as chaves, cada uma com seu **ponteiro de dados**, mais um ponteiro para a **próxima folha**.
- As folhas formam uma **lista encadeada em ordem**.
- Uma chave que aparece num nó interno **também está numa folha** (é uma cópia usada como guia).
- Regra de descida usada aqui: chaves **menores que `K`** vão à esquerda; **maiores ou iguais a `K`** vão à direita.

```
Nó interno:  P0 | K1 | P1 | K2 | P2 ...            (só guia)
Folha:       [ K1 K2 K3 ... ] ──► próxima folha    (cada Ki aponta para seu registro)
```

### Busca

- **Sempre desce até a folha**, mesmo que ache a chave igual num nó interno (lá ela é só guia).
- Custo: **sempre igual à altura**.
- **Busca por faixa** (ex.: CEPs entre A e B): ache a primeira chave da faixa e **siga a lista de folhas**. Isso é muito melhor que na árvore B.

### Inserção

Igual à B, com **uma diferença no split**:

- **Split de folha:** a chave **continua na folha**. A **primeira chave da folha da direita é copiada** para o pai (**copia**).
- **Split de nó interno:** a chave do meio **sobe e sai do nó**, como na árvore B (**sobe**).

### Exemplo: folhas com até 2 chaves, nós internos com até 2 chaves, inserindo 1 a 7

| Insere | O que acontece | Árvore (nível por nível) |
|---|---|---|
| 1, 2 | cabem | `[1,2]` |
| 3 | folha `[1,2,3]` estoura: `[1,2]` e `[3]`; o **3 é copiado** para a raiz nova | `[3]` / `[1,2] [3]` |
| 4 | cabe | `[3]` / `[1,2] [3,4]` |
| 5 | folha `[3,4,5]` estoura: `[3,4]` e `[5]`; o **5 é copiado** | `[3,5]` / `[1,2] [3,4] [5]` |
| 6 | cabe | `[3,5]` / `[1,2] [3,4] [5,6]` |
| 7 | folha `[5,6,7]` estoura: `[5,6]` e `[7]`; o **7 é copiado** e o interno `[3,5,7]` estoura: o **5 sobe** (sai do nó) | `[5]` / `[3] [7]` / `[1,2] [3,4] [5,6] [7]` |

```
                   [ 5 ]
                /          \
           [ 3 ]            [ 7 ]
          /     \          /     \
     [1,2] ──► [3,4] ──► [5,6] ──► [7]        folhas encadeadas
```

Repare: o 3, o 5 e o 7 aparecem **duas vezes** (como guia em cima e como chave na folha). Na árvore B do mesmo exemplo, cada chave aparece uma vez só.

### Remoção

Remova da **folha**. Se houver underflow, redistribua ou funda com o irmão, como na B. A chave-guia do nó interno **pode continuar lá**, pois ainda serve de guia; atualizá-la é opcional.

---

## 9. Comparação entre B e B+

| | Árvore B | Árvore B+ |
|---|---|---|
| Ponteiros de dados | em **todos** os nós | **só nas folhas** |
| Chave repetida | nunca | guias dos internos repetem chaves das folhas |
| Chaves por nó interno | menos (cada chave carrega um ponteiro de dados) | **mais** (só chave + ponteiro de bloco) |
| Altura | maior | **menor** (nós internos mais largos) |
| Busca | pode terminar num nó interno | **sempre até a folha** |
| Busca por faixa | ruim (percorrer em ordem pela árvore toda) | **ótima** (lista de folhas) |
| Split de folha | a chave do meio sobe | a primeira da direita é **copiada** |
| Folhas | independentes | **encadeadas** em lista (simples ou dupla) |

Por que a B+ é mais eficiente para arquivos indexados: (1) nós internos só com chave e ponteiro de bloco → mais filhos por bloco → **árvore mais baixa**; (2) as folhas encadeadas permitem **varrer em ordem** e responder **faixas** sem subir e descer pela árvore. A [seção 17](#17-teoria-cobrada-na-p2-respostas-modelo) tem a resposta-modelo.

---

## 10. Dimensionamento pelo bloco de disco

Dados: tamanho do bloco `B`, da chave `V`, do ponteiro de dados `Pr` e do ponteiro de bloco `Pb`. O nó tem que **caber em um bloco**.

| Nó | Condição | Resolver para |
|---|---|---|
| **B** (qualquer) | `n·Pb + (n−1)·(Pr + V) ≤ B` | `n` |
| **B+ interno** | `n·Pb + (n−1)·V ≤ B` | `n` |
| **B+ folha** | `k·(V + Pr) + Pb ≤ B` (o `Pb` é o ponteiro da próxima folha) | `k` chaves |

Passo a passo para não errar:

1. Substitua os números.
2. **Distribua o `(n−1)`**: `22n − 16 ≤ 512`. É o erro mais comum esquecer o `−16`.
3. Isole `n` e **arredonde para baixo** (precisa caber).

---

## 11. Ocupação média, níveis e altura

### Ocupação média (ex.: 70%)

1. Ponteiros por nó: `f = 0,7 · n`, arredondado (ex.: 0,7 × 24 = 16,8 → **17**).
2. Chaves por nó: `f − 1`.
3. Nível `k` (a raiz é o nível 1):
   - nós no nível `k` = `f^(k−1)`
   - chaves no nível `k` = `f^(k−1) · (f−1)`
4. Total de chaves até a altura `h` = `f^h − 1`.

### Limites pela altura `h` (árvore B de ordem `n`)

| | Fórmula |
|---|---|
| **Máximo** de chaves | `n^h − 1` |
| **Mínimo** de chaves | `2 · ⌈n/2⌉^(h−1) − 1` |

Para **n = 3**:

| h | 1 | 2 | 3 | 4 |
|---|---|---|---|---|
| mínimo | 1 | 3 | **7** | 15 |
| máximo | 2 | 8 | 26 | 80 |

Como obter o mínimo para a altura `h`: a raiz tem 1 chave e 2 filhos; todos os outros nós têm o **mínimo** de chaves (⌈n/2⌉ − 1) e de filhos (⌈n/2⌉).

Observação: em simulação, o mínimo calculado pela fórmula coincidiu com o que a **inserção em ordem crescente** produz para n = 3 e n = 5 (ordens ímpares). Para ordem **par** (ex.: 4), a inserção com a convenção desta seção 2 precisou de mais chaves (10, e não 7) para chegar a altura 3. Se a prova pedir isso, veja se o enunciado fala em "inserir" (depende da convenção do split) ou só em "estrutura mínima".

---

## 12. Exercícios resolvidos

### P2 2023.1, questão 2

Dados: campo de busca `V = 9` bytes, bloco `B = 512` bytes, ponteiro de dados `Pr = 7` bytes, ponteiro de bloco `Pb = 6` bytes.

**(a) Valor de n (árvore B).**
`n·6 + (n−1)·(7+9) ≤ 512` → `22n − 16 ≤ 512` → `22n ≤ 528` → **n = 24**.

**(b) Chaves máx. e mín. em nó não raiz.**
Máximo: `n − 1` = **23**. Mínimo: `⌈24/2⌉ − 1` = **11**.

**(c) Ocupação média de 70%: chaves no 3º nível.**
`f = 0,7 × 24 = 16,8 ≈ 17` ponteiros; **16 chaves por nó**.
Nível 1 (raiz): 1 nó. Nível 2: 17 nós. Nível 3: 17² = **289 nós** × 16 = **4.624 chaves**.
(Com arredondamento para 16 ponteiros e 15 chaves: 256 × 15 = 3.840. Confirme a regra de arredondamento do professor.)

**(d) n em árvore B+ (nó interno).**
Sem ponteiros de dados: `n·6 + (n−1)·9 ≤ 512` → `15n ≤ 521` → **n = 34**.
(Para as **folhas**: `k·(9+7) + 6 ≤ 512` → **31 chaves** por folha.)

### P2 2023.1, questão 3(c)

*Quantas chaves, no mínimo, para uma árvore B de grau 3 atingir altura 3?*

Estrutura mínima: raiz com 1 chave + 2 filhos com 1 chave + 4 folhas com 1 chave = 1 + 2 + 4 = **7 chaves**. Confirma-se inserindo 1 a 7 (tabela da [seção 6](#6-árvore-b-inserção)). Pela fórmula: `2 · ⌈3/2⌉² − 1 = 2·4 − 1 = 7`.

### Exercício extra, com outros números

Dados: `B = 1024`, `V = 12`, `Pr = 8`, `Pb = 4`.

| Pergunta | Conta | Resposta |
|---|---|---|
| n da árvore B | `4n + 20(n−1) ≤ 1024` → `24n ≤ 1044` | **43** |
| Chaves máx./mín. (não raiz) | `n − 1` e `⌈43/2⌉ − 1` | **42** e **21** |
| n da B+ (interno) | `4n + 12(n−1) ≤ 1024` → `16n ≤ 1036` | **64** |
| Chaves por folha da B+ | `20k + 4 ≤ 1024` | **51** |
| 70% de ocupação | `0,7 × 43 = 30,1 ≈ 30` ponteiros, 29 chaves | — |
| Nível 3 | 30² = 900 nós × 29 | **26.100 chaves** |

---

## 13. Para treinar

Insira **10, 20, 30, 40, 50, 60, 70, 80, 90**, nesta ordem, e desenhe a árvore final:

- **(a)** Árvore B de ordem 4 (máximo 3 chaves por nó).
- **(b)** Árvore B+ com folhas de até 3 chaves e nós internos de até 3 chaves.

<details>
<summary>Resposta</summary>

Primeiro estouro, no 40: `[10,20,30,40]` tem 4 chaves, sobe a de índice ⌊(4−1)/2⌋ = 1, ou seja, o **20**.

**(a) Árvore B (altura 2):**

```
            [ 20 | 40 | 60 ]
           /    |     |     \
        [10]  [30]  [50]  [70,80,90]
```

**(b) Árvore B+ (altura 2):** a folha que estoura fica com 2 + 2 chaves e a primeira da direita é copiada.

```
              [ 30 | 50 | 70 ]
             /     |     |     \
     [10,20] ──► [30,40] ──► [50,60] ──► [70,80,90]
```

Se o seu professor subir a chave do **meio-direita**, os desenhos mudam (por exemplo, a raiz da (a) começaria com o 30), mas as regras são as mesmas.

</details>

---

## 14. Erros comuns

- Tratar `n` como número de **chaves**. `n` é o número de **ponteiros**; chaves = `n − 1`.
- Esquecer de distribuir o `(n−1)` na conta do bloco (`22n − 16`, e não `22n`).
- Usar `Pr` no nó **interno** da B+ (ele não tem ponteiro de dados).
- Na B+, **mover** a chave no split de folha. Na folha ela é **copiada**; só no nó interno ela sobe.
- Esquecer que a **raiz** pode ter só 1 chave, e que o mínimo de ⌈n/2⌉ − 1 vale para os **outros** nós.
- Esquecer de **reordenar** as chaves ao inserir no meio do nó.
- Esquecer que, se a raiz estoura, **nasce uma raiz nova** e a altura sobe.
- Contar a altura começando em 0 numa prova que conta níveis (ou ao contrário). Declare o que usou.
- Na B+, parar a busca ao achar a chave num nó interno. É só guia: desça até a folha.
- Chamar de "B+" uma estrutura em que **cada nó tem ponteiro de dados**: isso é árvore **B**.
- No código: guardar na árvore o **número** do registro (`posicao++`). A prova pede o **offset em bytes**; use `ftell` **antes** do `fread` (ou `i * sizeof(Registro)`).
- No código: escrever `1004` ou `1008` no lugar de `sizeof(Registro)`. Com o padding o tamanho pode não ser `8 + 1000`.
- Esquecer de **fechar a árvore** (`closeTree`) depois de usar: sem isso o índice pode não ser gravado.
- Dizer que o custo de `diferencaArquivos` é só `log n`. Faltou o fator **m** (uma busca por registro do arquivo2).

---

## 15. Ligação com o código de estudo

O `ArvoreB.h`/`ArvoreB.c` implementam uma árvore **B** (cada elemento tem `posicaoRegistro`, em todas as páginas).

| Conceito | No código |
|---|---|
| Nó / bloco | `ArvoreB_Pagina` (7.216 bytes no Linux 64 bits) |
| Chave + ponteiro de dados | `chave` + `posicaoRegistro` no `ArvoreB_Elemento` |
| Ponteiros de bloco | offsets em bytes no arquivo: `paginaEsquerda` e `paginaDireita` |
| Máximo de chaves | `TAM_PAG` = 300 (logo, **n = 301 ponteiros**: 1 `paginaEsquerda` + 300 `paginaDireita`) |
| Ponteiro nulo / folha | offset 0; folha quando `paginaEsquerda == 0` |
| Split | `ArvoreB_Split`: sobe o elemento de índice `TAM_PAG/2` |
| Raiz nova | `ArvoreB_Insere` cria a raiz e atualiza o cabeçalho |
| Ponteiro de dados | número do registro no arquivo de dados (CEP) |

---

## 16. Cola de prova

| Quero | Fórmula |
|---|---|
| Ordem `n` da B | `n·Pb + (n−1)·(Pr+V) ≤ B` |
| Ordem `n` da B+ (interno) | `n·Pb + (n−1)·V ≤ B` |
| Chaves por folha da B+ | `k·(V+Pr) + Pb ≤ B` |
| Chaves máx. por nó | `n − 1` |
| Chaves mín. (não raiz) | `⌈n/2⌉ − 1` |
| Ponteiros médios | `f = ocupação × n` |
| Nós no nível `k` (raiz = 1) | `f^(k−1)` |
| Chaves no nível `k` | `f^(k−1) · (f−1)` |
| Chaves até a altura `h` | `f^h − 1` |
| Máx. de chaves, altura `h` | `n^h − 1` |
| Mín. de chaves, altura `h` | `2·⌈n/2⌉^(h−1) − 1` |
| Mín. após split (n ponteiros) | `⌊(n−1)/2⌋ = ⌈n/2⌉ − 1` |
| Offset em bytes (registro fixo) | `i · sizeof(Registro)`, ou `ftell` antes do `fread` |
| Custo de `m` buscas na árvore | `m · log n` (≈ `m · altura` leituras de bloco) |

**Split na B:** a chave do meio **sobe**. **Split de folha na B+:** a primeira da direita é **copiada**. **Split de interno na B+:** a do meio **sobe**.

---

## 17. Teoria cobrada na P2: respostas-modelo

Essas são as perguntas de teoria de uma P2 corrigida (questão 3, 0,3 ponto cada). Respostas curtas, no tamanho que cabe na prova.

### 3(a) Diferença entre árvore B e B+

> Na **árvore B**, chaves e ponteiros para os dados ficam em **todos os nós**, e cada chave aparece uma única vez. Na **B+**, os dados (ou ponteiros para eles) ficam **só nas folhas**; os nós internos guardam apenas **chaves-guia** (cópias) e ponteiros para filhos, só para direcionar a busca. A B+ é mais eficiente para arquivos indexados porque (1) os nós internos, sem ponteiros de dados, comportam **mais filhos por bloco**, o que diminui a altura, e (2) as **folhas são encadeadas**, o que permite percorrer em ordem e fazer consultas por intervalo sem voltar pela árvore.

### 3(b) Hash como índice

| | Hash | Árvore B+ |
|---|---|---|
| Consulta por **igualdade** | **O(1)** médio | O(log n) |
| Consulta por **intervalo** | **não serve** (a função espalha as chaves) | **ótima**: desce uma vez e segue as folhas |
| **Ordenação** das chaves | não mantém | mantém (folhas em ordem) |
| Colisões | existem; degradam a busca (listas longas) | não há |
| Crescimento | tabela fixa; exige **rehash** para crescer | cresce sozinha por splits |

> Resumo: hash é ótimo para **igualdade**, ruim para **intervalo e ordenação**; a B+ é boa nas duas, com custo um pouco maior por busca.

### 3(d) Como o split garante os 50% mínimos

> Um nó só é dividido quando **estoura**: ao inserir numa página cheia (máximo `n − 1` chaves), ela passa a ter `n` chaves. A chave do **meio sobe** para o pai e as outras `n − 1` se repartem em duas páginas com `⌊(n−1)/2⌋` e `⌈(n−1)/2⌉` chaves, ou seja, **pelo menos `⌈n/2⌉ − 1`**, que é o mínimo exigido (metade da capacidade). Como nenhuma página é dividida antes de encher, nenhuma nasce abaixo disso. A **raiz** é exceção, pois pode ter menos.

Conferência numérica: `n = 24` → estoura com 24 chaves, 1 sobe, sobram 23 → **12 e 11**; o mínimo é `⌈24/2⌉ − 1 = 11`. ✔ Com `n = 3`: 3 chaves, 1 sobe, sobram 2 → 1 e 1; mínimo `⌈3/2⌉ − 1 = 1`. ✔

Se a raiz estoura, nasce uma **raiz nova** com a chave que subiu e a árvore cresce em altura (é assim que ela cresce: **por cima**, sempre balanceada).

---

## 18. Código da P2: usar a árvore B como caixa-preta

A questão 4 (2,8 pontos, a de maior peso) **não pede para implementar a árvore**. O enunciado dá a árvore pronta e quatro funções:

| Função | O que faz |
|---|---|
| `void* openTree(const char* nomeArquivo)` | abre (ou cria) o arquivo de índice e devolve a árvore |
| `bool findKey(void* tree, long key, long* offset)` | busca a chave; se achar, devolve `true` e grava o offset em `*offset` |
| `void insertKey(void* tree, long key, long offset)` | insere o par chave → offset |
| `void closeTree(void* tree)` | fecha a árvore |

O registro tem tamanho fixo:

```c
typedef struct { long chave; char dados[1000]; } Registro;
```

### A ideia

O **arquivo de dados** guarda os registros; a **árvore** é um índice **chave → offset em bytes** (onde o registro começa no arquivo de dados). Para ler um registro: busca a chave na árvore, recebe o offset, faz `fseek(f, offset, SEEK_SET)` e `fread`. Mesma ideia do índice no fim de um livro.

Cuidados:
- O offset é em **bytes**, não o número do registro. Pegue com `ftell(f)` **antes** do `fread`.
- Use sempre `sizeof(Registro)`. Aqui ele vale **1008** (8 + 1000), mas não escreva o número.
- `dados[1000]` pode não ter `'\0'`: imprima com `%.1000s`.
- Abra os arquivos em modo **binário** (`"rb"`, `"wb"`).

### (a) Construir o índice

```c
void indexaArquivo(const char* nomeDados, const char* nomeIndice) {
    FILE* f = fopen(nomeDados, "rb");
    if (!f) { printf("Erro ao abrir %s\n", nomeDados); return; }
    void* arv = openTree(nomeIndice);
    Registro r;
    long offset = ftell(f);                       // ftell ANTES do fread
    while (fread(&r, sizeof(Registro), 1, f) == 1) {
        insertKey(arv, r.chave, offset);
        offset = ftell(f);                        // início do próximo registro
    }
    closeTree(arv);
    fclose(f);
}
```

### (b) Buscar uma chave e imprimir `dados`

```c
void imprimeDados(const char* nomeDados, const char* nomeIndice, long chave) {
    void* arv = openTree(nomeIndice);
    long offset;
    if (!findKey(arv, chave, &offset)) {
        printf("Chave %ld nao encontrada\n", chave);
        closeTree(arv);
        return;
    }
    FILE* f = fopen(nomeDados, "rb");
    if (f) {
        Registro r;
        fseek(f, offset, SEEK_SET);
        if (fread(&r, sizeof(Registro), 1, f) == 1)
            printf("%.1000s\n", r.dados);
        fclose(f);
    }
    closeTree(arv);
}
```

### (c) Registros que estão no arquivo2 e **não** no arquivo1

A assinatura já recebe `indiceArquivo1`, ou seja, o índice do arquivo1 **já existe**. Percorre-se o arquivo2 sequencialmente e, para cada registro, pergunta-se à árvore se a chave existe.

```c
void diferencaArquivos(const char* arquivo1, const char* arquivo2,
                       const char* indiceArquivo1, const char* arquivoSaida) {
    FILE* f2  = fopen(arquivo2, "rb");
    FILE* out = fopen(arquivoSaida, "wb");
    if (!f2 || !out) {
        printf("Erro ao abrir arquivos\n");
        if (f2) fclose(f2);
        if (out) fclose(out);
        return;
    }
    void* arv = openTree(indiceArquivo1);
    Registro r;
    long offset;                                  // não é usado: só interessa se achou
    while (fread(&r, sizeof(Registro), 1, f2) == 1)
        if (!findKey(arv, r.chave, &offset))      // não está no arquivo1
            fwrite(&r, sizeof(Registro), 1, out);
    closeTree(arv);
    fclose(f2);
    fclose(out);
}
```

O parâmetro `arquivo1` não é lido: só o seu índice. Se o enunciado dissesse que o índice **não existe**, chame antes `indexaArquivo(arquivo1, indiceArquivo1)`.

Esse código foi compilado e testado com uma árvore "de mentira" (lista em arquivo) no lugar da árvore B. Teste: arquivo1 = 10, 20, …, 100; arquivo2 = 5, 10, …, 100. A saída foi 5, 15, 25, …, 95 (os 10 que não estão no arquivo1), e a busca por uma chave ausente imprimiu a mensagem.

### (d) Custo

Seja `n` o número de registros do arquivo1 e `m` o do arquivo2.

> Lê-se o arquivo2 **uma vez**, sequencialmente (`m` registros), e faz-se **uma busca na árvore por registro**: **O(m · log n)**. Cada busca custa a **altura** da árvore em leituras de bloco (poucas, pois a árvore é baixa e larga). O arquivo1 **não** é lido, só o índice. Se o índice precisasse ser construído, somaria **O(n · log n)**.

Compare com a alternativa sem índice: para cada registro do arquivo2, varrer o arquivo1 inteiro daria **O(m · n)**.

Erro comum nessa resposta: escrever só `O(log n)` ou `O(2·log n)`. Falta o fator **m**: o `log n` é o custo de **uma** busca, e são `m` buscas.
