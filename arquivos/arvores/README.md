# Árvores B e B+ — guia de estudo

Material de **Organização de Estruturas de Arquivos** (CEFET/RJ). Foco em **conceito** e em **desenhar/calcular** as árvores, que é o que cai na prova. Não há código aqui; a última seção só liga os conceitos ao `ArvoreB.c` de estudo.

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

**Split na B:** a chave do meio **sobe**. **Split de folha na B+:** a primeira da direita é **copiada**. **Split de interno na B+:** a do meio **sobe**.
