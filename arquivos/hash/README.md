# Hash: guia de estudo

Material de **Organização de Estruturas de Arquivos** (CEFET/RJ). Foco em **conceito**, em **montar a tabela de hash com encadeamento externo** (como na P2), em **contar colisões e acessos** e em entender os **scripts do trabalho dos CEPs**. O professor disse que não cobra código: os scripts aparecem para dar contexto, na [seção 12](#12-ligação-com-os-programas-de-estudo).

> Os exemplos foram conferidos por simulação, e os scripts do trabalho foram rodados com dados de teste. Os exercícios resolvidos vêm da P2 corrigida e da P2 de 2023.1. Cada número de exemplo diz de onde vem: veja a [seção 2](#2-convenções-e-origem-dos-números).

## Índice

**Parte 1: Conceito**

- [1. Por que existe](#1-por-que-existe)
- [2. Convenções e origem dos números](#2-convenções-e-origem-dos-números)
- [3. Vocabulário](#3-vocabulário)
- [4. A função de hash](#4-a-função-de-hash)
- [5. Hash em arquivo (disco)](#5-hash-em-arquivo-disco)

**Parte 2: Colisões**

- [6. Colisões e como tratá-las](#6-colisões-e-como-tratá-las)
- [7. Encadeamento externo](#7-encadeamento-externo)
- [8. Exemplo completo: P2 questão 2](#8-exemplo-completo-p2-questão-2)
- [9. Baldes](#9-baldes)

**Parte 3: Desempenho e comparação**

- [10. Fator de carga e acessos](#10-fator-de-carga-e-acessos)
- [11. Hash x B+ x busca sequencial](#11-hash-x-b-x-busca-sequencial)

**Parte 4: Programas de estudo**

- [12. Ligação com os programas de estudo](#12-ligação-com-os-programas-de-estudo)

**Parte 5: Prova**

- [13. Exercício resolvido: P2 2023.1 questão 3(a)](#13-exercício-resolvido-p2-20231-questão-3a)
- [14. Para treinar](#14-para-treinar)
- [15. Erros comuns](#15-erros-comuns)
- [16. Cola de prova](#16-cola-de-prova)

## Resumo em 30 segundos

- **Hash** é um jeito de achar um registro **calculando** onde ele está, em vez de procurar: `posição = h(chave)`.
- Com registros de tamanho fixo, o arquivo é acessado direto: `seek(posição × tamanho da entrada)`. Em média, **cerca de 1 acesso** por busca.
- **Colisão** é quando duas chaves caem na mesma posição. Não dá para evitar, só **tratar**.
- **Encadeamento externo** (o da P2): a chave que colide vai para uma **área de colisão**, e o campo **Próximo** liga as entradas de uma mesma posição em uma **lista**. `Próximo = 0` quer dizer "fim da lista".
- **Fator de carga** `α = n ÷ m` (registros ÷ posições). Quanto menor, menos colisões. Busca com sucesso: cerca de `1 + α/2` acessos.
- **Hash x B+:** hash é ótimo para **igualdade**; não serve para **intervalo** nem mantém **ordem**. A B+ faz as três coisas.

## Como usar este guia

| Se a questão pede... | Vá para |
|---|---|
| Montar a tabela de hash com encadeamento externo | [seção 7](#7-encadeamento-externo) e [seção 8](#8-exemplo-completo-p2-questão-2) |
| Contar colisões | [seção 2](#2-convenções-e-origem-dos-números), [seção 8](#8-exemplo-completo-p2-questão-2) e [seção 13](#13-exercício-resolvido-p2-20231-questão-3a) |
| Maior lista encadeada e onde ela começa | [seção 8](#8-exemplo-completo-p2-questão-2) |
| Vantagens e desvantagens do hash como índice | [seção 11](#11-hash-x-b-x-busca-sequencial) |
| Calcular acessos médios, fator de carga | [seção 10](#10-fator-de-carga-e-acessos) |
| Entender os scripts do trabalho (CEP) | [seção 12](#12-ligação-com-os-programas-de-estudo) |
| Revisar na véspera | [seção 16](#16-cola-de-prova) e [seção 15](#15-erros-comuns) |

---

## 1. Por que existe

Para achar um CEP num arquivo sem índice, é preciso **ler registro por registro** até encontrar: a **busca sequencial**. Se o arquivo tem `n` registros, são cerca de `n ÷ 2` leituras em média quando a chave existe.

| Jeito de buscar | Leituras de registro por busca (caso médio) |
|---|---|
| Sequencial | cerca de `n ÷ 2` |
| Árvore B+ | cerca de `log n` (a altura da árvore) |
| **Hash** | **cerca de 1 a 2** |

O hash faz a "mágica" de **calcular o endereço** a partir da chave, sem comparar com nada. É como um prédio em que o apartamento de cada pessoa é calculado pelo nome: você vai direto lá.

Exemplo do trabalho da disciplina: o arquivo de CEPs tem **cerca de 700 mil registros** (valor aproximado: o comentário do script de baldes pede um número mágico ">> 700", e 700 é 700 mil ÷ 1000 chaves por balde). A busca sequencial leria, em média, uns **350 mil** registros. Com hash, são pouco mais de 1 acesso.

---

## 2. Convenções e origem dos números

- **Posições numeradas a partir de 0.** Uma tabela com `m` posições primárias tem as posições `0` a `m − 1`.
- **Área de colisão:** fica depois da tabela primária, a partir da posição `m` (na P2: a partir da posição 11, pois a tabela tem 11 posições, de 0 a 10).
- **`Próximo = 0` significa "fim da lista".** Pode ser usado como "nulo" porque nenhuma entrada da área de colisão fica na posição 0 (a posição 0 é primária).
- **Colisão:** conta-se **uma colisão** cada vez que uma chave nova cai numa posição primária **já ocupada**. Exemplo: três chaves na mesma posição geram **2 colisões** (a primeira ocupa, as outras duas colidem).
- **Tamanho da lista:** conta a **entrada primária** mais as da área de colisão. Uma posição com a primária e mais duas entradas na área tem lista de tamanho 3.
- **Encadear logo após a primária:** a entrada nova vai para a **primeira posição livre** da área e é ligada **imediatamente depois** da primária. As mais antigas ficam depois dela.
- **Acesso:** cada **entrada lida** do arquivo de índice conta como 1 acesso.
- **Origem dos números dos exemplos:** cada exemplo diz de onde vem o seu. "Inventado" ou "exemplo" quer dizer que é só para ter valores pequenos. Os de prova (P2 corrigida, P2 2023.1) foram dados no enunciado e **mudam** em outra prova. O que vale é o **método**.

---

## 3. Vocabulário

| Termo | Significado |
|---|---|
| Chave | O valor usado para buscar (ex.: o CEP) |
| Função de hash `h` | Fórmula que transforma a chave numa posição da tabela |
| Tabela de hash | O vetor de posições (no nosso caso, um **arquivo** de índice) |
| Posição primária (endereço-base) | A posição que `h(chave)` indica |
| Colisão | Duas chaves diferentes com a mesma posição primária |
| Sinônimos | As chaves que colidem entre si |
| Área de colisão (overflow) | Região do arquivo, depois da tabela, onde ficam as chaves que colidiram |
| Encadeamento | Ligar as entradas de uma mesma posição por um campo `Próximo` |
| Lista encadeada | A sequência de entradas ligadas: primária, depois as da área de colisão |
| Balde (bucket) | Posição que guarda **várias** chaves de uma vez (veja a [seção 9](#9-baldes)) |
| Fator de carga `α` | `n ÷ m`: registros guardados ÷ posições da tabela |
| Acesso | Uma leitura de entrada no arquivo (é o que custa caro no disco) |

---

## 4. A função de hash

Uma boa função de hash:

1. É **determinística**: a mesma chave dá sempre a mesma posição.
2. **Espalha** as chaves por toda a tabela, sem acumular.
3. É **rápida**.

### Resto da divisão

Para chaves numéricas, a função mais comum é `h(k) = k mod m`, o resto da divisão da chave por `m` (o tamanho da tabela). O resultado vai sempre de `0` a `m − 1`, que são exatamente as posições.

Na P2 corrigida: `h(k) = k mod 11`. Para a chave 29: 29 = 2 · 11 + 7, então `h(29) = 7`.

### Por que `m` costuma ser primo

Se `m` e as chaves têm fator em comum, as chaves se amontoam. Exemplo **inventado**: chaves que são sempre múltiplas de 10, com `m = 10`: todas dão resto 0 e caem na posição 0. Com `m` primo (11, por exemplo), isso não acontece. Os valores dos exemplos são primos: 11 (P2) e 900.001 (nos scripts; conferi que é primo).

### Chaves que não são número

Para texto ou CEP com 8 caracteres, os scripts do trabalho usam o **SHA-1**, que transforma a chave num número enorme, e depois tiram o resto por `m`: `h(chave) = SHA-1(chave) mod m`. O SHA-1 espalha bem, mas é mais lento que um simples `k mod m`. Em prova, use o que o enunciado dá.

---

## 5. Hash em arquivo (disco)

No trabalho há **dois arquivos**:

- o de **dados** (`cep.dat`): os registros, de tamanho fixo;
- o de **índice** (`cep-hash.dat`): a tabela de hash, também de tamanho fixo por entrada.

A ideia: o endereço de uma entrada no arquivo de índice é calculado, não procurado.

```
offset da entrada p  =  p × tamanho da entrada
```

Com `p = h(chave)`, faz-se um `seek` direto para essa posição e lê-se a entrada. Isso só funciona porque **todas as entradas têm o mesmo tamanho** (as vazias também).

### Os tamanhos nos scripts

Esses números vêm do **formato** que os scripts usam (calculei com `struct.calcsize`):

| O que | Formato | Tamanho |
|---|---|---|
| Registro de CEP (dados) | `72s72s72s72s2s8s2s` | 72·4 + 2 + 8 + 2 = **300 bytes** |
| Entrada do índice | `8sLL` (chave de 8 bytes, posição, próximo) | **24 bytes** (8 + 8 + 8) |
| Tabela de 900.001 posições, vazia | 900.001 × 24 | **21.600.024 bytes** (cerca de 20,6 MiB) |

A tabela é **criada cheia de entradas vazias** antes de inserir qualquer coisa. Por isso o arquivo de índice já nasce do tamanho final da parte primária, e só cresce depois pela área de colisão.

O campo `posição` da entrada guarda o **número do registro** no arquivo de dados (o 1º, o 2º…), e não o byte. Para ler o registro, multiplica-se: `seek(posição × 300)`.

---

## 6. Colisões e como tratá-las

Duas chaves diferentes podem cair na mesma posição, e isso **vai acontecer**: com `n` próximo de `m`, quase sempre há colisões. O que se escolhe é como tratá-las.

| Método | Como funciona | Onde aparece |
|---|---|---|
| **Encadeamento externo** | A chave que colidiu vai para uma **área de colisão**, e o `Próximo` liga as entradas | **P2**; script do índice |
| **Baldes** | Cada posição guarda **várias** chaves (até um limite) | script de baldes (`i1000l1000l`) |
| Endereçamento aberto (sondagem linear) | A chave que colidiu vai para a **próxima posição livre da própria tabela** | só conceito, não está nos scripts |

Encadeamento externo e baldes são os que importam para a prova e para os scripts.

---

## 7. Encadeamento externo

### Estrutura

Cada entrada tem três campos:

| Campo | O que guarda |
|---|---|
| **Chave** | a chave |
| **Valor** | o dado associado (ou a posição do registro no arquivo de dados) |
| **Próximo** | a posição da próxima entrada da lista, ou **0** se for a última |

A tabela tem as posições **primárias** (`0` a `m − 1`) e, depois, a **área de colisão** (a partir de `m`).

### Inserir uma chave `k`

1. Calcule `p = h(k)`.
2. Se a posição **primária `p` está livre**: grave a entrada nela, com `Próximo = 0`. Fim.
3. Se está **ocupada** (colisão):
   1. escolha a **primeira posição livre** da área de colisão (`q`);
   2. grave a entrada nova em `q`, com `Próximo` = o `Próximo` que a primária tinha;
   3. altere o `Próximo` da primária para `q`.

Assim, a entrada nova fica **logo depois da primária**, e as antigas ficam adiante.

### Buscar uma chave `k`

1. Calcule `p = h(k)` e **leia a entrada `p`** (1 acesso).
2. Se a chave é a procurada, **achou**.
3. Senão, vá para a posição `Próximo` e leia (mais 1 acesso). Repita.
4. Se chegar a `Próximo = 0` sem achar, a chave **não existe**.

O número de acessos é a **posição da chave na lista** (a primária é a 1ª).

### Remover (pouco cobrado)

Ache a chave na lista e ajuste o `Próximo` da entrada anterior para pular a removida. Se for a **primária**, a entrada seguinte da lista é copiada para a posição primária (ou marca-se a posição como vazia, se não houver seguinte).

---

## 8. Exemplo completo: P2 questão 2

**Enunciado (resumido):** tabela de hash com **11 posições primárias** (0 a 10). Colisões por **encadeamento externo**, com a área de colisão no mesmo arquivo, **a partir da posição 11**. Cada entrada tem **Chave, Valor e Próximo** (`Próximo` = índice da próxima entrada, ou 0). Função `h(k) = k mod 11`. Em colisão, o novo registro vai para a **próxima posição livre da área de colisão** e é encadeado **logo após a entrada primária**. Inserir, nesta ordem: **18, 29, 40, 63, 24, 35, 46, 10, 21, 32**. (a) Apresentar a tabela final. (b) Quantas colisões ocorreram. (c) Tamanho da maior lista encadeada e em que posição primária começa.

### Passo a passo

| Ordem | Chave | `k mod 11` | O que acontece | Colisão? |
|---|---|---|---|---|
| 1 | 18 | 18 = 11·1 + **7** | posição 7 livre: grava em 7 | não |
| 2 | 29 | 29 = 11·2 + **7** | 7 ocupada. Grava na 1ª livre da área: **11**. `7.Próximo = 11` | **sim (1)** |
| 3 | 40 | 40 = 11·3 + **7** | 7 ocupada. Grava em **12**, com `Próximo = 11` (o antigo da primária). `7.Próximo = 12` | **sim (2)** |
| 4 | 63 | 63 = 11·5 + **8** | posição 8 livre | não |
| 5 | 24 | 24 = 11·2 + **2** | posição 2 livre | não |
| 6 | 35 | 35 = 11·3 + **2** | 2 ocupada. Grava em **13**. `2.Próximo = 13` | **sim (3)** |
| 7 | 46 | 46 = 11·4 + **2** | 2 ocupada. Grava em **14**, com `Próximo = 13`. `2.Próximo = 14` | **sim (4)** |
| 8 | 10 | 10 = 11·0 + **10** | posição 10 livre | não |
| 9 | 21 | 21 = 11·1 + **10** | 10 ocupada. Grava em **15**. `10.Próximo = 15` | **sim (5)** |
| 10 | 32 | 32 = 11·2 + **10** | 10 ocupada. Grava em **16**, com `Próximo = 15`. `10.Próximo = 16` | **sim (6)** |

### (a) Tabela final

O campo **Valor** é inventado, como o enunciado pede ("invente valores"); por isso mostro só **Chave** e **Próximo**.

| Posição | Chave | Próximo | | Posição | Chave | Próximo |
|---|---|---|---|---|---|---|
| 0 | | | | 9 | | |
| 1 | | | | **10** | **10** | **16** |
| **2** | **24** | **14** | | *11* | *29* | *0* |
| 3 | | | | *12* | *40* | *11* |
| 4 | | | | *13* | *35* | *0* |
| 5 | | | | *14* | *46* | *13* |
| 6 | | | | *15* | *21* | *0* |
| **7** | **18** | **12** | | *16* | *32* | *15* |
| **8** | **63** | **0** | | 17 | | |

As posições 0 a 10 (primárias) e 11 a 16 (*área de colisão*) são as usadas. A 17 em diante está livre.

As listas, seguindo o `Próximo`:

```
posição 2:   24 → 46 (pos 14) → 35 (pos 13) → fim
posição 7:   18 → 40 (pos 12) → 29 (pos 11) → fim
posição 8:   63 → fim
posição 10:  10 → 32 (pos 16) → 21 (pos 15) → fim
```

### (b) Colisões

**6** (as chaves 29, 40, 35, 46, 21 e 32 caíram em posições já ocupadas).

### (c) Maior lista

O tamanho é **3**. Mas há **empate**: as listas das posições **2, 7 e 10** têm 3 entradas cada. A resposta é "3, começando em qualquer uma delas" (a resposta escrita na prova, "3, posição 10", está certa e foi aceita). Se o enunciado pedisse uma só, indique todas as que empatam.

**Conferência rápida:** 10 chaves = 4 posições primárias ocupadas + 6 na área de colisão. As 6 na área são as 6 colisões. ✔

---

## 9. Baldes

Em vez de ligar entradas, cada posição da tabela é um **balde** que guarda **várias** chaves de uma vez. Um `seek` traz o balde inteiro; a busca dentro dele é feita **na memória**.

No script de baldes, cada balde (uma "linha") guarda **até 1000 chaves** e suas posições:

| Parte do balde | Quantidade | Tamanho |
|---|---|---|
| `n` (quantas chaves o balde tem agora) | 1 | 4 bytes (mais 4 de alinhamento) |
| chaves | 1000 | 8 bytes cada |
| posições no arquivo de dados | 1000 | 8 bytes cada |
| **Linha inteira** | | **16.008 bytes** (conferido com `struct.calcsize`) |

**Inserir:** calcula `p = h(chave)`, lê a linha `p`, se `n < 1000` acrescenta a chave e a posição e regrava a linha. Se `n == 1000` o balde está **cheio**: o pseudocódigo do script diz "ignora", o que **perde** o registro. Num sistema de verdade seria preciso tratar o estouro (por exemplo, com um balde de overflow).

**O "número mágico" (`>> 700`):** é a quantidade de baldes. Com cerca de 700 mil registros e 1000 por balde, o mínimo seriam 700 baldes, se o hash espalhasse **perfeitamente**. Como não espalha, alguns baldes enchem antes dos outros. Por isso se escolhe um número bem maior que 700. Mais baldes = menos chance de estourar, mas mais **espaço em disco**, pois cada linha ocupa 16.008 bytes, mesmo vazia.

| | Encadeamento externo | Baldes |
|---|---|---|
| Entrada | 1 chave | até 1000 chaves |
| Colisão | vai para a área e se encadeia | cabe no mesmo balde, até lotar |
| Acessos por busca | 1 a poucos | **1** (e busca na memória) |
| Desperdício de espaço | menor | **maior** (baldes vazios ocupam 16.008 bytes) |
| Problema | listas longas em posições azaradas | **balde cheio** |

---

## 10. Fator de carga e acessos

### Fator de carga

```
α = n ÷ m          (n = registros guardados, m = posições primárias)
```

Quanto **menor** o `α`, menos colisões e menos acessos. Se `α` passa de 1, há mais registros que posições, e as listas crescem.

### Colisões e tamanho das listas

- `colisões = n − (posições primárias ocupadas)`.
- Cada **lista** tem tamanho `k` = quantas chaves caíram naquela posição. A maior lista é o pior caso de busca.

### Acessos médios na busca **com sucesso**

Uma chave que está numa lista de tamanho `k` é achada em 1 a `k` acessos, e **em média `(k + 1) ÷ 2`**. Então, se `C[k]` é o número de posições com lista de tamanho `k`:

```
acessos médios  =  soma de  C[k] · k · (k+1)/2   ÷   n
```

E há uma **aproximação** pelo fator de carga: **`1 + α ÷ 2`**.

**Exemplo (P2 corrigida, seção 8):** as listas têm tamanhos 3, 3, 1 e 3. A soma é 6 + 6 + 1 + 6 = 19, e o total de chaves é `n = 10`. Acessos médios = 19 ÷ 10 = **1,9**.

### Acessos na busca **sem sucesso** (chave que não existe)

Lê-se a posição primária e depois a lista inteira. Se a posição está vazia, custa 1 leitura.

```
acessos médios  =  soma de  C[k] · máximo(k, 1)   ÷   m
```

### Exemplo com os scripts (dados de teste)

Rodei o script do índice (versão corrigida) com dados **inventados**: 20.000 registros numa tabela de **30.011 posições** (no lugar de 900.001, só para rodar rápido). O fator de carga foi `α = 20.000 ÷ 30.011 ≈ 0,67`. Os tamanhos das listas (`C[k]`, de `k = 0` a 7) foram `[15443, 10227, 3415, 786, 118, 20, 1, 1]`, com 5.432 colisões e maior lista de 7.

| Medida | Resultado |
|---|---|
| Acessos médios, busca com sucesso (fórmula) | 26.717 ÷ 20.000 = **1,336** (aproximação `1 + α/2` = 1,333) |
| Acessos médios, busca sem sucesso (fórmula) | 35.443 ÷ 30.011 = **1,181** |

Conferi os dois valores medindo as buscas de verdade, na versão **corrigida** do script (veja a [seção 12.2](#122-indexador-cria-o-índice-de-hash)), com todas as chaves e com 30.000 chaves ausentes: deu 1,336 e 1,181.

---

## 11. Hash x B+ x busca sequencial

**Pergunta da P2 (3b):** *explique vantagens e desvantagens de usar uma estrutura de hash como índice. Relacione com consultas por igualdade, consultas por intervalo e manutenção da ordenação.*

| | Hash | Árvore B+ | Sequencial |
|---|---|---|---|
| Consulta por **igualdade** | **O(1) médio** (cerca de 1 acesso) | O(log n) | O(n) |
| Consulta por **intervalo** | **não serve** (a função espalha as chaves, vizinhas não ficam juntas) | **ótima** (desce uma vez e anda pelas folhas) | lê tudo |
| Mantém a **ordem** das chaves | **não** | **sim** (folhas em ordem) | só se o arquivo estiver ordenado |
| Colisões | existem; listas longas pioram a busca | não há | não há |
| Crescimento | **tabela de tamanho fixo**; para crescer é preciso refazer tudo (rehash) | cresce sozinha por splits | não precisa |
| Pior caso | O(n) (tudo na mesma posição) | O(log n) | O(n) |

> **Resposta-modelo:** a vantagem do hash como índice é a **busca por igualdade em tempo praticamente constante**, com cerca de 1 acesso. As desvantagens: como a função de hash espalha as chaves, **não suporta consulta por intervalo** (chaves próximas não ficam em posições próximas) e **não mantém a ordenação**; além disso há **colisões**, e a tabela tem **tamanho fixo**, exigindo rehash para crescer. Para intervalos e ordem, a B+ é a melhor escolha.

**Quando usar:**

- Só **igualdade** ("dê o CEP X"), arquivo grande, muitas buscas: **hash**.
- **Intervalo** ("CEPs de X a Y") ou listar **em ordem**: **B+**.
- Arquivo pequeno ou busca rara: a **sequencial** basta.

---

## 12. Ligação com os programas de estudo

São cinco programas. Todos usam os formatos da [seção 5](#5-hash-em-arquivo-disco).

### 12.1 Busca sequencial

Abre o arquivo de dados e lê **um registro de 300 bytes por vez**, comparando o campo do CEP (a 6ª coluna, `record[5]`) com o procurado. Serve de **referência**: é o que o hash tenta evitar.

### 12.2 Indexador (cria o índice de hash)

Passos:

1. Cria o arquivo de índice com **900.001 entradas vazias** (a tabela primária).
2. Lê o arquivo de dados **registro a registro**, guardando o número do registro (`recordNumber`: 0, 1, 2…).
3. Para cada registro: `p = h(CEP)`, faz `seek(p × 24)` e lê a entrada.
4. Se a entrada estava **vazia**, grava ali (chave, número do registro, próximo = 0).
5. Se estava **ocupada** (colisão), grava a nova entrada **no fim do arquivo** (a área de colisão) e encadeia: a primária passa a apontar para ela, e ela aponta para o que a primária apontava antes. É o mesmo "logo após a primária" da P2.

Nesse script o `Próximo` guarda o **offset em bytes** no arquivo de índice (e não o número da entrada, como na P2). É só outra forma de apontar. O `0` também serve de "fim", pois o offset 0 é a posição primária 0, que nunca é alvo de um encadeamento.

**Pegadinha confirmada por teste:** o `if` que decide se a posição está vazia é

```python
if cep[0] == b"\0":
```

No Python 3, `cep[0]` em bytes devolve um **número inteiro** (0 se o byte é nulo), e um inteiro **nunca é igual** a `b"\0"` (bytes). Então a condição é **sempre falsa**, e **todo** registro cai no ramo "ocupada". Com os dados de teste (20.000 registros, 30.011 posições):

| Versão | Posições primárias com chave | Entradas na área de colisão |
|---|---|---|
| Como está (`== b"\0"`) | **0** | **20.000** (todos) |
| Corrigida (`== 0`) | 14.568 | 5.432 (= as colisões) |

O programa **funciona** mesmo assim (a primária fica "vazia" apontando para a lista), mas **desperdiça um acesso por busca**, pois a primária nunca guarda a chave. A correção é comparar com `0`.

### 12.3 Busca no índice

1. Calcula `p = h(CEP procurado)` e o offset `p × 24`.
2. **Laço:** lê a entrada, compara a chave. Se bate, faz `seek(posição × 300)` no arquivo de dados e lê o registro. Se não, vai para `Próximo`, até chegar a 0 ("não está no arquivo").
3. A variável `i` conta os **acessos** (é o que a seção 10 calcula).

### 12.4 Estatística (colisões e acessos)

Não cria índice. Só **simula** a inserção, contando quantas chaves caem em cada posição (`counts[p]`):

- `colisoes`: soma 1 sempre que `counts[p] > 1`, ou seja, a chave caiu numa posição já ocupada (é a definição da seção 2).
- `tamanhoMaiorLista`: o maior `counts[p]`.
- `countOfCounts[k]`: quantas posições têm lista de tamanho `k` (é o `C[k]` da seção 10).

**Atenção ao bloco final**, que calcula `Media acesso`. Ele tem `c += 1` duas vezes por volta do laço, e a conta não corresponde à fórmula da seção 10. Rodando com os dados de teste (20.000 registros, 30.011 posições), ele imprimiu **15,37**, que é impossível (a maior lista tem 7). O valor correto é **1,336**, pela fórmula da seção 10. Para estudar, use a fórmula, não esse bloco.

### 12.5 Baldes

O script define `packLinha` e `unpackLinha`, que convertem um balde (listas de chaves e posições) para bytes e de volta. Como a linha tem sempre o mesmo tamanho (16.008 bytes), os baldes vazios são preenchidos com zeros. O pseudocódigo em comentário descreve o fluxo da [seção 9](#9-baldes). Testei o `pack` e o `unpack`: ida e volta devolvem as mesmas listas.

### Fluxo completo

```
cep.dat (dados) ──► indexador ──► cep-hash.dat (índice de hash)
                                        │
          busca por CEP:  h(CEP) ─► seek(p × 24) ─► lê entrada ─► segue Próximo ─► seek(pos × 300) ─► registro
```

---

## 13. Exercício resolvido: P2 2023.1 questão 3(a)

**Enunciado:** *em uma tabela de hash onde `h(chave) = chave % 11`, ao inserir as chaves 10, 33, 85, 43, 27, 63, 95, 88 e 32, quantas colisões ocorrem?* (Li as chaves da prova escaneada.)

| Ordem | Chave | `k mod 11` | Posição já ocupada? |
|---|---|---|---|
| 1 | 10 | 10 | não |
| 2 | 33 | 0 | não |
| 3 | 85 | 8 (85 = 77 + 8) | não |
| 4 | 43 | 10 (43 = 33 + 10) | **sim** (pela 10): colisão 1 |
| 5 | 27 | 5 | não |
| 6 | 63 | 8 (63 = 55 + 8) | **sim** (pela 85): colisão 2 |
| 7 | 95 | 7 (95 = 88 + 7) | não |
| 8 | 88 | 0 | **sim** (pela 33): colisão 3 |
| 9 | 32 | 10 (32 = 22 + 10) | **sim** (pela 10 e pela 43): colisão 4 |

**Resposta: 4 colisões.** Quando uma posição já tem duas chaves (a 10, com 10 e 43), a terceira que chega (32) conta como **mais uma** colisão.

Conferência: 9 chaves, 5 posições primárias ocupadas (0, 5, 7, 8, 10). 9 − 5 = **4**. ✔

---

## 14. Para treinar

**Exercício 1 (monte a tabela).** Tabela de hash com **7 posições primárias** (0 a 6), `h(k) = k mod 7`, encadeamento externo com área de colisão **a partir da posição 7**. Em colisão, a nova entrada vai para a próxima posição livre da área e é encadeada **logo após a primária**. Insira, nesta ordem: **24, 37, 18, 11, 30, 33, 45, 26, 17** (valores **inventados** só para treino). Informe: (a) a tabela final (Chave e Próximo); (b) quantas colisões; (c) tamanho da maior lista e onde começa.

<details>
<summary>Resposta</summary>

| Chave | `k mod 7` | O que acontece |
|---|---|---|
| 24 | 3 | grava em 3 |
| 37 | 2 | grava em 2 |
| 18 | 4 | grava em 4 |
| 11 | 4 | colisão: grava em **7**; `4.Próximo = 7` |
| 30 | 2 | colisão: grava em **8**; `2.Próximo = 8` |
| 33 | 5 | grava em 5 |
| 45 | 3 | colisão: grava em **9**; `3.Próximo = 9` |
| 26 | 5 | colisão: grava em **10**; `5.Próximo = 10` |
| 17 | 3 | colisão: grava em **11** com `Próximo = 9`; `3.Próximo = 11` |

| Posição | Chave | Próximo |
|---|---|---|
| 2 | 37 | 8 |
| 3 | 24 | 11 |
| 4 | 18 | 7 |
| 5 | 33 | 10 |
| 7 | 11 | 0 |
| 8 | 30 | 0 |
| 9 | 45 | 0 |
| 10 | 26 | 0 |
| 11 | 17 | 9 |

(b) **5 colisões** (11, 30, 45, 26 e 17).
(c) A maior lista tem **3** entradas e começa na posição **3**: 24 → 17 (pos 11) → 45 (pos 9). As outras listas têm 2.

</details>

**Exercício 2 (acessos).** Com a tabela do exercício 1: quantos acessos para achar a chave **17**? E a **45**? E para buscar a chave **99**, que não existe? Qual o número médio de acessos, com sucesso?

<details>
<summary>Resposta</summary>

- **17:** 17 mod 7 = 3. Lê a posição 3 (24), segue para a 11 (17): **2 acessos**.
- **45:** lê a 3 (24), a 11 (17), a 9 (45): **3 acessos**.
- **99:** 99 mod 7 = 1. A posição 1 está vazia: **1 acesso** (e conclui que não existe).
- **Média com sucesso:** as listas têm tamanhos 2, 3, 2 e 2: (3 + 6 + 3 + 3) ÷ 9 chaves = 15 ÷ 9 = **1,67**.

</details>

**Exercício 3 (offset).** Num índice em que cada entrada ocupa **24 bytes** (o tamanho da entrada `8sLL` dos scripts), qual o offset em bytes da posição primária **5**? E da primeira posição da área de colisão, se a tabela tem **7** posições primárias?

<details>
<summary>Resposta</summary>

Offset = posição × tamanho da entrada. Posição 5: 5 × 24 = **120 bytes**. Primeira posição da área (a 7): 7 × 24 = **168 bytes**.

</details>

---

## 15. Erros comuns

- Colocar a área de colisão **dentro** das posições primárias. Ela começa **depois** (na P2, a partir da posição 11).
- Esquecer o **`mod`** ou trocar o divisor: use sempre o `m` do enunciado (11, não 10).
- **Contar a colisão errada:** a primeira chave de uma posição **não** é colisão. Três chaves na mesma posição são **2** colisões.
- Encadear a entrada nova **no fim** da lista. A regra da P2 é **logo após a primária**.
- Esquecer de **atualizar o `Próximo` da primária** ao inserir na área de colisão.
- Colocar a nova entrada numa posição **não livre** da área (a próxima livre é a menor posição ainda sem uso).
- Dizer que a maior lista é a de uma posição só, quando há **empate**. Cite todas as que empatam.
- **Contar a primária fora do tamanho da lista.** O tamanho inclui a primária.
- Confundir **`Próximo = 0`** com "aponta para a posição 0": zero quer dizer **fim da lista**.
- Esquecer de que o hash **não faz intervalo nem ordem**. É a desvantagem que a prova pergunta.
- Dizer que o hash "não tem colisão". Tem: o que existe é o tratamento.
- Calcular o offset sem multiplicar pelo **tamanho da entrada** (`p × tamanho`).
- No Python 3: comparar `cep[0]` com `b"\0"`. Indexar bytes devolve **número**, então compare com `0`.

---

## 16. Cola de prova

| Quero | Fórmula ou regra |
|---|---|
| Posição primária | `p = k mod m` |
| Offset da entrada `p` | `p × tamanho da entrada` |
| Área de colisão | começa na posição `m` |
| `Próximo` | posição da próxima entrada; **0 = fim** |
| Colisões | `n − posições primárias ocupadas` (cada chave que cai em posição já ocupada) |
| Tamanho da lista | entradas da posição, **incluindo a primária** |
| Fator de carga | `α = n ÷ m` |
| Acessos médios, com sucesso | `soma de C[k]·k·(k+1)/2 ÷ n`, aprox. `1 + α/2` |
| Acessos médios, sem sucesso | `soma de C[k]·máximo(k,1) ÷ m` |
| Pior caso da busca | `n` (tudo na mesma posição) |

**Inserir (encadeamento externo):** `p = k mod m`. Livre? Grava em `p`. Ocupada? Grava na **1ª livre da área**, com o `Próximo` antigo da primária, e a primária passa a apontar para ela.

**Hash x B+:** igualdade: hash. Intervalo e ordem: B+.
