# Código e árvore de Huffman: guia de estudo

Material de **Organização de Estruturas de Arquivos** (CEFET/RJ). Foco em **conceito**, em **desenhar a árvore**, no **algoritmo guloso** e nas **saídas** (os códigos, o tamanho do arquivo comprimido). O professor disse que não cobra código. Os dois programas de estudo (contar bytes e desenhar o histograma) aparecem só para dar contexto, na [seção 10](#10-ligação-com-os-programas-de-estudo).

> Os exemplos foram conferidos por simulação (algoritmo com heap, em Python). O exercício resolvido é da P2 corrigida. Cada número de exemplo diz de onde vem: veja a [seção 2](#2-convenções-e-origem-dos-números).

## Índice

**Parte 1: Conceito**

- [1. Por que existe](#1-por-que-existe)
- [2. Convenções e origem dos números](#2-convenções-e-origem-dos-números)
- [3. Vocabulário](#3-vocabulário)
- [4. Código de prefixo e a árvore](#4-código-de-prefixo-e-a-árvore)

**Parte 2: Algoritmo**

- [5. O algoritmo passo a passo](#5-o-algoritmo-passo-a-passo)
- [6. Por que é guloso e por que dá o ótimo](#6-por-que-é-guloso-e-por-que-dá-o-ótimo)
- [7. Empates](#7-empates)

**Parte 3: Saídas, heap e programas**

- [8. As saídas: códigos, custo e compressão](#8-as-saídas-códigos-custo-e-compressão)
- [9. O heap](#9-o-heap)
- [10. Ligação com os programas de estudo](#10-ligação-com-os-programas-de-estudo)

**Parte 4: Prova**

- [11. Exercício resolvido: P2 questão 1](#11-exercício-resolvido-p2-questão-1)
- [12. Para treinar](#12-para-treinar)
- [13. Erros comuns](#13-erros-comuns)
- [14. Cola de prova](#14-cola-de-prova)

## Resumo em 30 segundos

- **Huffman** é compressão **sem perda**: dá **código curto** ao símbolo **frequente** e **código longo** ao **raro**.
- O código tem tamanho **variável** e é **livre de prefixo**: nenhum código é o começo de outro. Por isso dá para decodificar sem separador.
- Na **árvore**, os símbolos ficam nas **folhas**. O código é o caminho da raiz até a folha (esquerda = 0, direita = 1).
- O algoritmo é **guloso**: repita "pegue os **dois menores pesos**, junte num nó novo com a **soma** e devolva", até sobrar um nó, que é a raiz.
- Quem entrega os dois menores rapidamente é um **heap** (fila de prioridade mínima).
- **Custo** (bits do arquivo) = soma de frequência × tamanho do código = **soma dos pesos dos nós internos**.
- Em **empate** pode escolher qualquer um: saem árvores diferentes, todas com o **mesmo custo**.

## Como usar este guia

| Se a questão pede... | Vá para |
|---|---|
| Construir a árvore e dar o código de cada símbolo | [seção 5](#5-o-algoritmo-passo-a-passo) e [seção 11](#11-exercício-resolvido-p2-questão-1) |
| Explicar por que é guloso, por que dá o ótimo | [seção 6](#6-por-que-é-guloso-e-por-que-dá-o-ótimo) |
| Codificar ou decodificar uma mensagem | [seção 4](#4-código-de-prefixo-e-a-árvore) e [seção 8](#8-as-saídas-códigos-custo-e-compressão) |
| Tamanho do arquivo comprimido, taxa de compressão | [seção 8](#8-as-saídas-códigos-custo-e-compressão) |
| Por que usar um heap | [seção 9](#9-o-heap) |
| Empates ("escolha qualquer") | [seção 7](#7-empates) |
| Revisar na véspera | [seção 14](#14-cola-de-prova) e [seção 13](#13-erros-comuns) |


---

## 1. Por que existe

Um arquivo de texto guarda cada símbolo com o **mesmo tamanho**: 8 bits por caractere (1 byte). Mas os símbolos não aparecem com a mesma frequência: num texto, o espaço e o "e" aparecem muito mais que o "z".

A ideia de Huffman: **gastar poucos bits nos símbolos que aparecem muito e mais bits nos que aparecem pouco**. O total de bits do arquivo diminui, e nada se perde (dá para recuperar o arquivo original exatamente).

Exemplo ilustrativo (números **inventados** só para mostrar a ideia): um arquivo de 100 símbolos com três tipos, X (70 vezes), Y (20 vezes) e Z (10 vezes).

| Jeito de codificar | Códigos | Bits no arquivo |
|---|---|---|
| Tamanho fixo (3 tipos precisam de 2 bits) | X=00, Y=01, Z=10 | 100 · 2 = **200** |
| Tamanho variável (Huffman) | X=0, Y=10, Z=11 | 70·1 + 20·2 + 10·2 = **130** |

O X, que é o mais comum, ficou com 1 bit só. Essa troca é o que Huffman faz sistematicamente. Ele é usado dentro de formatos como ZIP/gzip e JPEG.

---

## 2. Convenções e origem dos números

- **Esquerda = 0, direita = 1.** Foi escolhido por convenção; trocar não muda o custo.
- **O nó de menor peso vai à esquerda** quando junto dois nós. É a regra deste guia.
- **Empate:** pego primeiro o nó mais antigo (as folhas, na ordem da tabela, antes dos nós criados). Em prova, vale qualquer escolha, desde que a árvore seja ótima (veja a [seção 7](#7-empates)).
- **Origem dos números:** cada exemplo diz de onde vem o seu. "Inventado" ou "exemplo" quer dizer que é só para ter valores pequenos. O exercício principal (símbolos A a H) é da **P2 corrigida**, e em outra prova os números serão outros. O que vale é o **método**, não o número.
- Se só existir **um** símbolo diferente, a árvore é uma folha só, e ele recebe o código `0` (1 bit).

---

## 3. Vocabulário

| Termo | Significado |
|---|---|
| Símbolo | A unidade que se codifica (um caractere, ou, num arquivo qualquer, um byte de 0 a 255) |
| Frequência / peso | Quantas vezes o símbolo aparece no arquivo |
| Código (palavra-código) | A sequência de bits que representa o símbolo |
| Tamanho fixo x variável | Fixo: todos os códigos têm o mesmo número de bits (como o ASCII, 8). Variável: o tamanho depende do símbolo |
| Livre de prefixo | Nenhum código é o começo de outro (veja a [seção 4](#4-código-de-prefixo-e-a-árvore)) |
| Folha | Nó sem filhos. Cada folha é **um símbolo**, com o peso dele |
| Nó interno | Nó com dois filhos. O peso é a **soma dos pesos dos filhos** |
| Raiz | O nó do topo. O peso dela é a soma de **todas** as frequências |
| Profundidade | Número de arestas da raiz até o nó. A profundidade da folha é o **tamanho do código** |
| Árvore cheia | Todo nó interno tem **exatamente 2 filhos** (a de Huffman é sempre assim) |
| Custo | Bits totais do arquivo comprimido: soma de frequência × tamanho do código |
| Guloso | Algoritmo que escolhe a melhor opção local em cada passo e nunca volta atrás |
| Heap mínimo | Estrutura que entrega sempre o **menor** elemento rapidamente (veja a [seção 9](#9-o-heap)) |

### Não confunda com as outras árvores

| | Árvore de Huffman | Árvore B / B+ |
|---|---|---|
| Para que serve | **Comprimir** (menos bits) | **Buscar** em disco (menos leituras) |
| Onde ficam os símbolos/chaves | **Só nas folhas** | B: em todos os nós; B+: dados só nas folhas |
| Balanceada? | **Não**: os frequentes ficam rasos, os raros ficam fundos | **Sim**: todas as folhas no mesmo nível |
| Filhos por nó | Sempre **2** | Vários (até `n`) |

---

## 4. Código de prefixo e a árvore

### Por que o código tem que ser livre de prefixo

Os bits ficam **colados**, sem separador. Se um código for o começo de outro, a leitura fica ambígua.

Exemplo de código **ruim** (inventado): A = `0`, B = `01`, C = `1`. A sequência `01` pode ser "B" ou "A seguido de C". Não dá para decidir.

Exemplo de código **bom** (livre de prefixo): A = `0`, B = `10`, C = `11`. A sequência `0 10 11` só pode ser "A B C", porque cada código termina sem deixar dúvida.

### A árvore garante isso

Se os símbolos ficam **só nas folhas**, o caminho até uma folha nunca passa por outra folha. Logo nenhum código é prefixo de outro.

```
          ( )
        0 /   \ 1
        A     ( )
            0 /   \ 1
            B       C            A = 0     B = 10     C = 11
```

### Como ler e usar a árvore

- **Ler o código de um símbolo:** parta da raiz e anote 0 a cada passo à esquerda e 1 a cada passo à direita, até chegar à folha do símbolo.
- **Decodificar:** parta da raiz e siga os bits da mensagem, um a um (0 desce à esquerda, 1 à direita). Ao chegar a uma folha, escreva o símbolo e **volte à raiz**. Há um exemplo completo na [seção 8](#8-as-saídas-códigos-custo-e-compressão).

---

## 5. O algoritmo passo a passo

**Receita:**

1. **Conte** a frequência de cada símbolo.
2. Crie **uma folha** para cada símbolo, com o peso dele.
3. **Enquanto houver mais de um nó:**
   1. retire os **dois nós de menor peso**;
   2. crie um **nó pai** com peso igual à **soma** dos dois;
   3. ligue os dois como filhos (o menor à esquerda, com 0; o outro à direita, com 1);
   4. **devolva** o nó pai ao conjunto.
4. O nó que sobrar é a **raiz**.
5. **Leia os códigos**: caminho da raiz até cada folha.

### Exemplo completo (P2 corrigida, questão 1)

Os dados vêm do enunciado: um arquivo com os símbolos A a H e as frequências abaixo. A soma é **164** (o total de símbolos do arquivo).

| Símbolo | A | B | C | D | E | F | G | H |
|---|---|---|---|---|---|---|---|---|
| Frequência | 4 | 7 | 10 | 15 | 20 | 28 | 33 | 47 |

Cada passo tira os dois menores e devolve a soma. A coluna da direita mostra o conjunto depois do passo (em ordem de peso):

| Passo | Retira | Cria | Conjunto depois |
|---|---|---|---|
| início | | | A4 B7 C10 D15 E20 F28 G33 H47 |
| 1 | A4 + B7 | AB = 11 | C10 AB11 D15 E20 F28 G33 H47 |
| 2 | C10 + AB11 | CAB = 21 | D15 E20 CAB21 F28 G33 H47 |
| 3 | D15 + E20 | DE = 35 | CAB21 F28 G33 DE35 H47 |
| 4 | CAB21 + F28 | CABF = 49 | G33 DE35 H47 CABF49 |
| 5 | G33 + DE35 | GDE = 68 | H47 CABF49 GDE68 |
| 6 | H47 + CABF49 | HCABF = 96 | GDE68 HCABF96 |
| 7 | GDE68 + HCABF96 | **raiz = 164** | raiz164 |

Nesse exemplo **não há empates** em nenhum passo. A árvore (cada nó interno mostra o peso; as arestas mostram o bit):

```
                               (164)
                       0 /                 \ 1
                    (68)                     (96)
                0 /      \ 1             0 /        \ 1
              G:33       (35)          H:47          (49)
                       0 /   \ 1                  0 /     \ 1
                     D:15    E:20               (21)       F:28
                                              0 /   \ 1
                                            C:10    (11)
                                                  0 /   \ 1
                                                 A:4     B:7
```

Os códigos, lidos da raiz até cada folha:

| Símbolo | Frequência | Código | Tamanho | Bits no arquivo (frequência × tamanho) |
|---|---|---|---|---|
| A | 4 | `11010` | 5 | 20 |
| B | 7 | `11011` | 5 | 35 |
| C | 10 | `1100` | 4 | 40 |
| D | 15 | `010` | 3 | 45 |
| E | 20 | `011` | 3 | 60 |
| F | 28 | `111` | 3 | 84 |
| G | 33 | `00` | 2 | 66 |
| H | 47 | `10` | 2 | 94 |
| **Total** | **164** | | | **444** |

**Conferências rápidas** (faça sempre):

- A raiz pesa **164**, igual à soma das frequências. ✔
- São **15 nós** (8 folhas + 7 internos): `2n − 1` com `n = 8`. E foram **7 junções**: `n − 1`. ✔
- Os mais **frequentes** (H, G) têm os códigos mais **curtos**; os mais raros (A, B), os mais **longos**. ✔
- Nenhum código é começo de outro. ✔
- **Custo = soma dos pesos dos nós internos**: 11 + 21 + 35 + 49 + 68 + 96 + 164 = **444**, igual à soma da coluna da direita. ✔

---

## 6. Por que é guloso e por que dá o ótimo

**Guloso** quer dizer: em cada passo, escolhe-se a melhor opção *naquele momento* (juntar os dois menores) e **nunca se volta atrás** para rever. Isso nem sempre dá o melhor resultado. Exemplo clássico (moedas **inventadas** só para mostrar): com moedas de valor 1, 3 e 4, o troco de 6 pelo método guloso usa 4 + 1 + 1 (3 moedas), mas o ótimo é 3 + 3 (2 moedas).

No Huffman, o guloso **funciona**: está provado que a árvore resultante tem o menor custo possível. A ideia da prova, em três passos:

1. **Na árvore ótima, o símbolo mais raro fica no nível mais fundo.** Se um raro tivesse código mais curto que um frequente, trocar os dois códigos diminuiria o custo. Conta com números inventados: raro com 4 ocorrências e 2 bits, frequente com 47 ocorrências e 5 bits: 4·2 + 47·5 = 243. Trocando: 4·5 + 47·2 = 114. Diminuiu.
2. **Os dois mais raros podem ser irmãos, no nível mais fundo.** Por isso é seguro juntá-los primeiro.
3. **Junte os dois num símbolo novo** (peso = soma) e repita com um problema menor, de um símbolo a menos. Se o problema menor sai ótimo, o todo também sai.

**Intuição do custo:** cada vez que dois nós são juntados, todos os símbolos dentro deles ganham **1 bit** a mais. Por isso o custo total é a **soma dos pesos de todos os nós internos**: cada junção "paga" o peso do nó novo. Juntar sempre os dois menores deixa essas somas as menores possíveis.

**Por que a árvore é cheia:** a cada junção entram sempre dois nós, então todo nó interno tem 2 filhos. Um nó com 1 filho só desperdiçaria um bit e poderia ser removido, encurtando os códigos.

O que costuma ser pedido é só "por que é guloso": porque a cada passo escolhe a melhor opção local (os dois menores pesos) sem rever as decisões anteriores.

---

## 7. Empates

Quando **dois ou mais nós têm o mesmo peso**, o algoritmo não diz qual pegar. Também é livre decidir quem vai à esquerda ou à direita (e qual lado é 0). O enunciado da P2 diz isso: "em caso de empate, escolha qualquer uma das alternativas, desde que a árvore seja ótima".

O que acontece: saem **árvores diferentes**, às vezes com **tamanhos de código diferentes**, mas sempre com o **mesmo custo**.

Exemplo com pesos **inventados** (1, 1, 2, 2) para os símbolos A, B, C, D:

1. Junte A1 + B1 = AB (2). Agora há três nós de peso 2: AB, C e D (empate).
2. **Escolha 1:** junte C + D = 4, depois AB + CD = 6. Todos os símbolos ficam com 2 bits. Custo: 1·2 + 1·2 + 2·2 + 2·2 = **12**.
3. **Escolha 2:** junte AB + C = 4, depois D + ABC = 6. D fica com 1 bit, C com 2, A e B com 3. Custo: 1·3 + 1·3 + 2·2 + 2·1 = **12**.

As duas estão certas. **Para conferir, compare o custo**, não os códigos: o custo é igual à soma dos nós internos (2 + 4 + 6 = 12 nas duas).

---

## 8. As saídas: códigos, custo e compressão

O que a prova pode pedir como "saída" do algoritmo:

1. A **tabela de códigos** (símbolo → bits).
2. A **árvore** desenhada.
3. A mensagem **codificada** (ou **decodificada**).
4. O **tamanho** do arquivo comprimido, em bits ou bytes.
5. A **taxa de compressão** e os **bits médios por símbolo**.

### Codificar uma mensagem

Troque cada símbolo pelo seu código e **cole** os bits. Com a tabela da seção 5, a mensagem **HGDH** (escolhida por mim como exemplo) fica:

```
H   G   D    H
10  00  010  10   →   100001010   (9 bits)
```

Para comparar: em ASCII (8 bits por símbolo) seriam 4 · 8 = 32 bits.

### Decodificar uma mensagem

Parta da raiz e siga os bits. Ao chegar a uma folha, escreva o símbolo e volte à raiz:

```
100001010
1 0       → direita, esquerda  → H
0 0       → esquerda, esquerda → G
0 1 0     → esquerda, direita, esquerda → D
1 0       → direita, esquerda  → H          Resultado: HGDH
```

### Tamanho, média e taxa

Com o exemplo da seção 5 (total de 164 símbolos, custo 444):

| O que | Conta | Resultado |
|---|---|---|
| Custo de Huffman | soma de frequência × tamanho | **444 bits** (55,5 bytes; no arquivo, 56 bytes) |
| Bits médios por símbolo | 444 ÷ 164 | **2,71 bits** |
| Em ASCII (8 bits) | 164 · 8 | 1.312 bits |
| Tamanho fixo mínimo (8 símbolos pedem 3 bits, pois 2³ = 8) | 164 · 3 | 492 bits |
| Taxa contra o ASCII | 444 ÷ 1.312 | **33,8%** (redução de 66,2%) |
| Taxa contra o tamanho fixo de 3 bits | 444 ÷ 492 | 90,2% (redução de 9,8%) |

**Fórmulas:**

- Custo = Σ (frequência × tamanho do código).
- Bits médios = custo ÷ total de símbolos.
- Taxa de compressão = custo ÷ bits do original.
- Bits do original em tamanho fixo = ⌈log₂ n⌉ × total, com `n` símbolos distintos. Em ASCII, 8 × total.

### Na prática (além do que a prova pede)

Num arquivo comprimido de verdade, o decodificador precisa conhecer a árvore. Então o programa grava, no **começo** do arquivo, a **tabela de frequências** (ou a própria árvore). Além disso, a quantidade de bits quase nunca é múltipla de 8, e o **último byte** é completado com bits de enchimento. Por isso o arquivo real é um pouco maior que `custo ÷ 8`.

---

## 9. O heap

A prova pergunta (3c): *por que se usa um heap na construção da árvore de Huffman, e qual operação o torna eficiente?*

**O problema:** em cada passo é preciso pegar os **dois menores pesos** e depois **inserir** o nó novo (a soma) no conjunto.

| Como guardar o conjunto | Pegar o menor | Inserir um nó |
|---|---|---|
| Lista desordenada | percorrer tudo: **O(n)** | **O(1)** |
| Lista ordenada | **O(1)** | achar o lugar e deslocar: **O(n)** |
| **Heap mínimo** | **O(log n)** | **O(log n)** |

**Heap mínimo** (também chamado de fila de prioridade mínima) é uma árvore binária, guardada num vetor, em que **cada pai é menor ou igual aos filhos**. Por isso o **menor elemento está sempre na raiz**. Tirar o menor e inserir um elemento reorganizam o heap em O(log n).

**Custo total:** são `n − 1` junções, e cada uma faz 2 extrações do mínimo e 1 inserção. Dá **O(n log n)**. Com lista, ficaria O(n²).

> **Resposta-modelo:** o heap mínimo (fila de prioridade) permite obter os dois menores pesos e reinserir o nó soma em O(log n) cada, e não em O(n). Como são n − 1 junções, o algoritmo todo custa O(n log n). A operação que o torna eficiente é a **extração do mínimo**, junto com a inserção.

Não confunda: o **heap** é uma estrutura **auxiliar**, usada durante a construção. A **árvore de Huffman** é o **resultado**.

---

## 10. Ligação com os programas de estudo

Os dois programas fazem a **parte de preparação** do Huffman. Os códigos comentados estão nos arquivos `frequencias.c` e `histograma.py`, separados deste guia.

**`frequencias.c`: o passo 1 do algoritmo (contar).** Lê o arquivo byte a byte e conta quantas vezes cada valor, de 0 a 255, aparece. Cada byte é um **símbolo**, e `count[b]` é a **frequência** dele. Esses números são os pesos das folhas.

Teste que fiz com um arquivo de texto de exemplo, contendo `ABRACADABRA` (11 bytes). O programa imprime, entre outras linhas com valor 0:

```
65: 5      ← 'A' (código ASCII 65) aparece 5 vezes
66: 2      ← 'B'
67: 1      ← 'C'
68: 1      ← 'D'
82: 2      ← 'R'
Total de impressões: 11
```

Esses são exatamente os pesos para montar a árvore daquele texto. Só se criam folhas para os símbolos com frequência **maior que 0**.

**`histograma.py`: ver as frequências.** Lê a saída do programa em C e desenha as barras (valor do byte × frequência). Como ler o gráfico:

- **Poucas barras altas e muitas baixas:** frequências **muito desiguais**. Huffman comprime **bem** (um texto em português, por exemplo).
- **Barras todas parecidas:** frequências **iguais**. Huffman quase não ajuda, pois, se os 256 valores tivessem a mesma frequência, todos os códigos teriam 8 bits, como no original. É o caso de arquivos já comprimidos ou aleatórios.

**Fluxo completo:**

```
arquivo → frequencias.c → tabela de frequências → [monta a árvore de Huffman] → códigos → arquivo comprimido
                                  └──→ histograma.py → gráfico (só para olhar)
```

---

## 11. Exercício resolvido: P2 questão 1

**Enunciado (resumido):** um arquivo tem os símbolos A a H com as frequências 4, 7, 10, 15, 20, 28, 33 e 47. Construir a árvore de Huffman e dar o código de cada símbolo. Em caso de empate, qualquer escolha serve, desde que a árvore seja ótima.

**Resposta:** a tabela de passos, a árvore e os códigos estão na [seção 5](#5-o-algoritmo-passo-a-passo). Resumo:

| Símbolo | A | B | C | D | E | F | G | H |
|---|---|---|---|---|---|---|---|---|
| Código | `11010` | `11011` | `1100` | `010` | `011` | `111` | `00` | `10` |

### O que estava errado na resposta da prova

A resposta escrita tinha **todos os códigos com 4 bits** (A = `1001`, B = `1000`, …, H = `0001`). Isso tem três problemas:

1. É um código de **tamanho fixo**, não de Huffman. Em Huffman, o tamanho **varia** conforme a frequência.
2. O **H** (frequência 47, o mais frequente) ficou com 4 bits, o mesmo tamanho do **A** (frequência 4, o mais raro). O mais frequente tem que ter o código mais curto. A anotação manuscrita ao lado da tabela, na prova, parece apontar isso: os menos frequentes devem ter mais bits, e os mais frequentes, menos.
3. O custo seria 164 · 4 = **656 bits**: pior até que o tamanho fixo de 3 bits (492) e bem pior que o de Huffman (444).

**Como se conferir:** some os pesos dos nós internos. Se não der 444, a árvore não é ótima. E olhe os tamanhos: não podem ser todos iguais.

---

## 12. Para treinar

**Exercício 1 (do texto aos códigos).** Considere o texto `ABRACADABRA`. Conte as frequências, monte a árvore, dê os códigos e calcule o custo. Compare com o tamanho fixo de 3 bits (5 símbolos distintos pedem 3 bits).

<details>
<summary>Resposta</summary>

Frequências: A = 5, B = 2, R = 2, C = 1, D = 1 (total 11).

| Passo | Retira | Cria |
|---|---|---|
| 1 | C1 + D1 | CD = 2 |
| 2 | B2 + R2 (há empate entre B, R e CD; tanto faz) | BR = 4 |
| 3 | CD2 + BR4 | CDBR = 6 |
| 4 | A5 + CDBR6 | raiz = 11 |

Códigos possíveis: **A = `0`**, C = `100`, D = `101`, B = `110`, R = `111`.
Custo: 5·1 + 1·3 + 1·3 + 2·3 + 2·3 = **23 bits**. Tamanho fixo de 3 bits: 11 · 3 = 33 bits. Confere pela soma dos internos: 2 + 4 + 6 + 11 = 23.
Com outra escolha no empate dos passos 2 e 3, os códigos mudam, mas o custo é **sempre 23**.

</details>

**Exercício 2 (exemplo clássico de livro, números só para treino).** Símbolos a, b, c, d, e, f com frequências 45, 13, 12, 16, 9 e 5 (total 100). Dê a árvore, os códigos e o custo.

<details>
<summary>Resposta</summary>

| Passo | Retira | Cria |
|---|---|---|
| 1 | f5 + e9 | fe = 14 |
| 2 | c12 + b13 | cb = 25 |
| 3 | fe14 + d16 | fed = 30 |
| 4 | cb25 + fed30 | cbfed = 55 |
| 5 | a45 + cbfed55 | raiz = 100 |

Códigos: a = `0`, c = `100`, b = `101`, f = `1100`, e = `1101`, d = `111`.
Custo: 45·1 + 12·3 + 13·3 + 5·4 + 9·4 + 16·3 = 45 + 36 + 39 + 20 + 36 + 48 = **224 bits**. Soma dos internos: 14 + 25 + 30 + 55 + 100 = 224. Tamanho fixo de 3 bits: 300 bits.

</details>

**Exercício 3 (decodificar).** Use a árvore da seção 5 e decodifique `0001111110`.

<details>
<summary>Resposta</summary>

`00` → G, `011` → E, `111` → F, `10` → H. A mensagem é **GEFH**.

</details>

---

## 13. Erros comuns

- Dar código **do mesmo tamanho** a todos os símbolos (isso é tamanho fixo, não Huffman).
- **Inverter**: o mais frequente com código **longo**. É o contrário: o mais frequente, o mais curto.
- **Não devolver** o nó soma ao conjunto antes de escolher os próximos dois menores.
- Juntar os dois **maiores** em vez dos dois **menores**.
- Errar uma soma no meio e carregar o erro até a raiz. Confira: a raiz tem que valer a **soma das frequências**.
- Gerar uma árvore com nó de **1 filho** só. A de Huffman é sempre **cheia**.
- Colocar símbolos em **nós internos**. Os símbolos ficam **só nas folhas**.
- Gerar códigos em que um é **começo de outro** (não é livre de prefixo).
- Achar que a árvore é **única**. Em empate há várias, todas com o mesmo custo.
- Para conferir, comparar os **códigos** com o gabarito em vez do **custo**. Códigos diferentes podem estar certos.
- Calcular o custo com o **comprimento** sem multiplicar pela **frequência**. O custo é Σ frequência × tamanho.
- Confundir o **heap** (estrutura auxiliar) com a **árvore de Huffman** (o resultado).
- Confundir com a árvore B: Huffman **não é balanceada** e não serve para busca em disco.

---

## 14. Cola de prova

| Quero | Fórmula ou regra |
|---|---|
| Nós totais da árvore | `2n − 1` (n = símbolos distintos) |
| Número de junções | `n − 1` |
| Peso da raiz | soma de **todas** as frequências |
| Tamanho do código de um símbolo | **profundidade** da folha |
| Custo (bits do arquivo) | `Σ frequência × tamanho` = **soma dos pesos dos nós internos** |
| Bits médios por símbolo | custo ÷ total de símbolos |
| Tamanho fixo (bits por símbolo) | `⌈log₂ n⌉` |
| ASCII | 8 bits por símbolo |
| Taxa de compressão | custo ÷ bits do original |
| Heap mínimo | pegar o menor e inserir: `O(log n)` cada; total `O(n log n)` |

**Receita:** (1) conte as frequências; (2) uma folha por símbolo; (3) repita: tire os dois **menores**, junte numa soma, **devolva**; (4) a raiz pesa o total; (5) leia os códigos, esquerda = 0 e direita = 1; (6) **confira** pela soma dos nós internos.

**Em empate:** escolha qualquer, e confira o **custo**, não os códigos.
