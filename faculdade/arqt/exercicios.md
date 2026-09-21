# 🧮 Arquiteturas Avançadas — Exercícios Resolvidos (P1)

> Todas as questões das **duas provas P1 (Turmas A e B)**, da **Lista de Exercícios 1** e as resolvidas pelo professor no quadro.
>
> Os conceitos estão no arquivo **`ARQ_conceitos_P1.md`**.
>
> **Legenda:** 🧠 **Como pensar** · ✍️ **Resolução** · ✅ **Resposta** · ⚠️ **Erro comum**

---

## 📑 Sumário

* [Bloco A — Diagrama de pipeline e hazards](#bloco-a--diagrama-de-pipeline-e-hazards)
* [Bloco B — Período do clock](#bloco-b--período-do-clock)
* [Bloco C — Speedup](#bloco-c--speedup)
* [Bloco D — Forwarding, stalls e contagem de ciclos](#bloco-d--forwarding-stalls-e-contagem-de-ciclos)
* [Bloco E — Assembly RISC-V](#bloco-e--assembly-risc-v)
* [Bloco F — Questões discursivas de conceito](#bloco-f--questões-discursivas-de-conceito)
* [Bloco G — Objetivas e V/F](#bloco-g--objetivas-e-vf)
* [Bloco H — Gabarito rápido](#bloco-h--gabarito-rápido)

---

# Bloco A — Diagrama de pipeline e hazards

## A1 🧪 P1 Turma B — Questão 1 (2,0 pontos)

> Dadas as instruções abaixo, desenhe o diagrama de pipeline (IF, ID, EX, MEM, WB) e identifique:
> ```asm
> lw  $t3, 8($s2)
> sub $t4, $t3, $s3     # Hazard aqui
> sw  $t4, 12($s2)
> ```
> **a)** (0,5) O tipo de hazard (explique).
> **b)** (0,5) Em qual ciclo ele ocorre.
> **c)** (1,0) Como resolvê-lo com forwarding (indique origem e destino). E quantos stalls seriam necessários SEM forwarding?

### 🧠 Como pensar

```text
1. Ache quem ESCREVE e quem LÊ cada registrador.
     lw  ESCREVE $t3        sub LÊ $t3    → dependência!
     sub ESCREVE $t4        sw  LÊ $t4    → dependência!
2. Meça a DISTÂNCIA entre elas (quantas instruções separam).
3. Se a produtora for um lw e a distância for 1 → LOAD-USE → stall obrigatório.
4. Desenhe a escada e marque em que ciclo o dado é PRODUZIDO e em que ciclo é PRECISO.
```

### ✍️ Resolução

**Diagrama ideal (sem tratar o hazard) — para localizar o problema:**

```text
Ciclo:                C1    C2    C3    C4    C5    C6    C7
──────────────────────────────────────────────────────────────
lw  $t3, 8($s2)       IF    ID    EX   MEM    WB
                                         └── $t3 pronto no FIM do C4
sub $t4, $t3, $s3           IF    ID    EX   MEM    WB
                                         ▲
                                  precisa de $t3 no INÍCIO do C4
sw  $t4, 12($s2)                  IF    ID    EX   MEM    WB
```

**a) Tipo de hazard** ✅

> É um **hazard de DADOS**, do tipo **RAW (*Read After Write* — leitura após escrita)**, e mais especificamente um **load-use hazard**.
>
> A instrução `sub` precisa ler o registrador `$t3`, mas `$t3` está sendo carregado da memória pela instrução `lw` imediatamente anterior. Como o `lw` só obtém o dado no **estágio MEM (4º estágio)** e o `sub` precisa dele no **estágio EX**, a instrução seguinte não pode prosseguir no ciclo de clock seguinte.
>
> Há também uma **segunda dependência de dados** entre `sub` (escreve `$t4`) e `sw` (lê `$t4`), mas essa é **resolvida por forwarding sem custo**.

**b) Em qual ciclo ocorre** ✅

> No **ciclo 4 (C4)**.
>
> É nele que o `sub` entra no estágio **EX** e precisa do valor de `$t3`, enquanto o `lw` só está concluindo o estágio **MEM** — ou seja, o dado só fica disponível **no fim** do mesmo ciclo em que já era necessário **no início**.

**c) Resolvendo com forwarding** ✅

⚠️ **O load-use hazard NÃO é resolvido só com forwarding.** É preciso **1 stall (bolha)** + forwarding:

```text
Ciclo:                C1    C2    C3    C4    C5    C6    C7    C8
──────────────────────────────────────────────────────────────────
lw  $t3, 8($s2)       IF    ID    EX   MEM ──┐ WB
                                             │ (1) forwarding MEM/WB → EX
sub $t4, $t3, $s3           IF    ID   ****  EX ──┐ MEM   WB
                                      bolha       │ (2) forwarding EX/MEM → EX
sw  $t4, 12($s2)                  IF   ****  ID   EX   MEM   WB
```

| # | Dependência | **Origem** | **Destino** | Custo |
| --- | --- | --- | --- | --- |
| 1 | `$t3`: `lw` → `sub` | saída do estágio **MEM** do `lw` (registrador de pipeline **MEM/WB**) | entrada da **ULA** no estágio **EX** do `sub` | **1 stall** |
| 2 | `$t4`: `sub` → `sw` | saída do estágio **EX** do `sub` (registrador de pipeline **EX/MEM**) | entrada do estágio **EX** do `sw` | **0 stall** |

```text
Total com forwarding: 3 + 4 + 1 stall = 8 ciclos
```

**Quantos stalls SEM forwarding?** ✅ → **4 stalls** (2 para cada dependência)

🧠 Sem forwarding, um registrador só pode ser lido no **ID** depois de ter sido escrito no **WB**. Como o banco de registradores escreve na **primeira metade** do ciclo e lê na **segunda**, o WB e o ID podem acontecer no **mesmo ciclo**.

```text
Ciclo:        C1  C2  C3  C4  C5  C6  C7  C8  C9 C10 C11
lw  $t3       IF  ID  EX MEM  WB
                            └── $t3 gravado no C5
sub $t4           IF  **  **  ID  EX MEM  WB      ← 2 stalls (ID foi de C3 para C5)
                                       └── $t4 gravado no C8
sw  $t4               IF  **  **  **  **  ID  EX MEM  WB   ← +2 stalls (ID de C6 para C8)

Total: 3 + 4 + 4 = 11 ciclos
```

⚠️ **Convenção:** se o seu professor **não** admitir escrita e leitura no mesmo ciclo, são **3 stalls por hazard** (6 no total). **Escreva na prova qual convenção você usou** — isso garante o ponto nas duas interpretações.

---

## A2 🧪 P1 Turma A — Questão 1 (2,0 pontos)

> ```asm
> lw  $t1, 0($s0)
> add $t2, $t1, $s1     # Hazard aqui
> sw  $t1, 4($s1)
> ```
> **a)** O tipo de hazard (explique). **b)** Em qual ciclo ocorre. **c)** Como resolvê-lo usando forwarding (indique origem e destino do dado).

### ✍️ Resolução

**a)** ✅ **Hazard de dados do tipo load-use (RAW).** O `add` precisa de `$t1` no estágio **EX**, mas o `lw` imediatamente anterior só traz `$t1` da memória no estágio **MEM**.

**b)** ✅ **Ciclo 4** — o `add` entra em EX no C4 e o `lw` só termina o MEM no fim do C4.

**c)** ✅ **1 stall + forwarding.**

```text
Ciclo:              C1    C2    C3    C4    C5    C6    C7    C8
──────────────────────────────────────────────────────────────────
lw  $t1, 0($s0)     IF    ID    EX   MEM ──┐ WB
                                           │ forwarding MEM/WB → EX
add $t2, $t1, $s1         IF    ID   ****  EX   MEM   WB
                                     bolha
sw  $t1, 4($s1)                 IF   ****  ID   EX   MEM   WB
```

| Dependência | **Origem** | **Destino** |
| --- | --- | --- |
| `$t1`: `lw` → `add` | registrador de pipeline **MEM/WB** (saída do MEM do `lw`) | entrada da **ULA**, no **EX** do `add` |
| `$t1`: `lw` → `sw` | distância 2 → resolvida naturalmente | sem custo |

```text
Total: 3 + 4 + 1 = 8 ciclos
```

---

## A3 🧪 Lista, Seção 2, Questão 2

> ```asm
> lw  $t0, 0($s1)
> sub $t2, $t0, $s3
> sw  $t2, 4($s1)
> ```
> Identifique o tipo de hazard e indique como resolvê-lo. **a)** Nomeie o hazard.

✅ **Idêntico ao A1.** Hazard de **dados**, do tipo **load-use (RAW)**, entre `lw` e `sub` pelo registrador `$t0`. Resolve-se com **1 stall + forwarding MEM/WB → EX**. A dependência `sub → sw` (`$t2`) é resolvida por **forwarding EX/MEM → EX**, sem stall.

---

# Bloco B — Período do clock

## B1 🧪 P1 Turma B — Questão 3 (1,0 ponto)

> Os cinco estágios têm os tempos: **IF 100 ps · ID 100 ps · EX 300 ps · MEM 500 ps · WB 100 ps**.
> **a)** (0,5) Se implementados em **caminho de dados de ciclo único**, qual deve ser o período do clock?
> **b)** (0,5) Se forem **estágios de pipeline**, qual deve ser o período do clock?

### 🧠 Como pensar

```text
MONOCICLO → a instrução inteira tem que caber em UM ciclo  → SOMA
PIPELINE  → todos os estágios compartilham o MESMO ciclo   → MAIOR
```

### ✍️ Resolução

**a) Monociclo** ✅
```text
Tc = 100 + 100 + 300 + 500 + 100 = 1100 ps
```
> No ciclo único, **uma operação completa** deve terminar dentro de um único ciclo de clock, então o período tem que comportar a **soma** de todos os estágios.

**b) Pipeline** ✅
```text
Tc = máx(100, 100, 300, 500, 100) = 500 ps       ← o estágio MEM é o gargalo
```
> Como todos os estágios executam **simultaneamente** e precisam estar prontos ao mesmo tempo, o período é ditado pelo **estágio mais lento**.

⚠️ Note que **3 dos 5 estágios ficam ociosos** boa parte do ciclo (o IF gasta só 100 dos 500 ps). É o preço do desbalanceamento.

---

## B2 🧪 P1 Turma A — Questão 2 (1,0 ponto)

> **IF 50 ps · ID 50 ps · EX 200 ps · MEM 400 ps · WB 50 ps**

✅ **a) Monociclo:** `50 + 50 + 200 + 400 + 50 = ` **750 ps**
✅ **b) Pipeline:** `máx(50, 50, 200, 400, 50) = ` **400 ps** (gargalo no MEM)

---

# Bloco C — Speedup

## C1 🧪 P1 (nas duas turmas) — Questão de 2,0 pontos

> Calcule o speedup de um pipeline com **5 estágios (200 ps cada)** para **200 instruções**, comparando com **monociclo (800 ps por instrução)**. **Mostre os cálculos.**

### 🧠 Como pensar

```text
1. Tempo monociclo = N × Tc_mono                  (1 instrução por ciclo)
2. Ciclos no pipeline = N + (E − 1)               ← o "+4" é o ENCHIMENTO
3. Tempo pipeline = ciclos × Tc_pipe
4. Speedup = T_mono / T_pipe
5. Compare com o speedup TEÓRICO = Tc_mono / Tc_pipe
```

### ✍️ Resolução

```text
DADOS
  N = 200 instruções        E = 5 estágios
  Tc_pipeline  = 200 ps     Tc_monociclo = 800 ps

MONOCICLO
  ciclos = 200
  T_mono = 200 × 800 ps = 160.000 ps

PIPELINE
  ciclos = N + (E − 1) = 200 + 4 = 204 ciclos
  T_pipe = 204 × 200 ps = 40.800 ps

SPEEDUP
        T_mono      160.000
  S = ─────────  =  ────────  ≈  3,92
        T_pipe       40.800
```

✅ **Resposta:** o pipeline é **≈ 3,92 vezes mais rápido** que o monociclo.

> **Justificativa (escreva isso na prova):** o speedup **teórico** seria `800/200 = 4` (igual ao número de estágios, já que eles estão equilibrados). O valor real fica **ligeiramente abaixo** por causa dos **4 ciclos de enchimento** do pipeline, que não são amortizados totalmente com apenas 200 instruções. Quanto maior o número de instruções, mais o speedup se aproxima de 4.

---

## C2 🧪 Lista, Questão 4 — a conta que o professor fez no quadro

> Calcule o speedup de um pipeline com 5 estágios (**150 ps cada**) para **50 instruções**, comparando com monociclo (**900 ps por instrução**).

```text
T_mono = 50 × 900 = 45.000 ps
ciclos_pipe = 50 + 4 = 54
T_pipe = 54 × 150 = 8.100 ps

        45.000
  SP = ────────  ≈  5,5
         8.100
```

✅ **Resposta: ≈ 5,5×**

⚠️ **Repare:** deu **mais que 5** (o número de estágios)! Isso acontece porque os estágios **não estão equilibrados** com o monociclo: `5 × 150 = 750 ps`, mas o monociclo gasta **900 ps**. O speedup teórico aqui é `900/150 = 6`.

🎯 Esse é o caso em que a frase "o speedup é aproximadamente o número de estágios" **não vale** — ela só vale quando `Tc_mono = E × Tc_pipe`.

---

## C3 🧪 Lista, Questão 5

> Calcule o speedup **teórico** de um pipeline com 5 estágios **equilibrados (200 ps cada)** para **100 instruções**, comparando com monociclo (**800 ps por instrução**).

```text
T_mono = 100 × 800 = 80.000 ps
ciclos_pipe = 100 + 4 = 104
T_pipe = 104 × 200 = 20.800 ps

S = 80.000 / 20.800 ≈ 3,85
Speedup teórico (N → ∞) = 800 / 200 = 4
```

✅ **Resposta: ≈ 3,85×**, com limite teórico de **4×**.

⚠️ Compare C1 (200 instruções → 3,92) com C3 (100 instruções → 3,85): **quanto mais instruções, mais perto de 4**. É exatamente o argumento do slide que usa 1.000.000 de instruções para chegar em 4,00.

---

## C4 🧪 Lista, Questão 6 — alterando o tempo da ALU

> Na tabela abaixo, se o tempo para a operação da ALU puder ser **reduzido em 25%**, responda:
> **a)** Isso afetará o ganho de velocidade obtido pela técnica de pipeline? Caso contrário, por quê?
> **b)** E se a operação da ALU exigir **a mais 25%** do tempo?

| Classe | Busca instr. | Leitura reg. | **ULA** | Acesso dados | Escrita reg. | Total |
| --- | --- | --- | --- | --- | --- | --- |
| `lw` | 200 ps | 100 ps | **200 ps** | 200 ps | 100 ps | 800 ps |
| `sw` | 200 ps | 100 ps | **200 ps** | 200 ps | — | 700 ps |
| R-format | 200 ps | 100 ps | **200 ps** | — | 100 ps | 600 ps |
| `beq` | 200 ps | 100 ps | **200 ps** | — | — | 500 ps |

### 🧠 Como pensar

```text
O Tc do PIPELINE = MAIOR estágio.
Então só importa se a mudança afeta O GARGALO.
Situação inicial: IF = ULA = MEM = 200 ps (empatados no topo).
```

### ✍️ a) ALU **reduzida** em 25% → 200 × 0,75 = **150 ps**

```text
PIPELINE
  Tc = máx(200, 100, 150, 200, 100) = 200 ps    ← NÃO MUDA
  (o gargalo passa a ser apenas IF e MEM, que continuam em 200 ps)

MONOCICLO
  lw = 200 + 100 + 150 + 200 + 100 = 750 ps     ← melhorou

SPEEDUP
  antes: 800 / 200 = 4,00
  agora: 750 / 200 = 3,75
```

✅ **Resposta:** **sim, afeta — mas para PIOR.** O desempenho do **pipeline não muda em nada**, porque a ULA **não era o estágio mais lento sozinha**; o período continua ditado pelo IF e pelo MEM (200 ps). Já o **monociclo melhora** (de 800 para 750 ps). Como o denominador ficou igual e o numerador diminuiu, o **ganho relativo do pipeline cai de 4,00 para 3,75**.

### ✍️ b) ALU **aumentada** em 25% → 200 × 1,25 = **250 ps**

```text
PIPELINE
  Tc = máx(200, 100, 250, 200, 100) = 250 ps    ← AGORA a ULA é o gargalo

MONOCICLO
  lw = 200 + 100 + 250 + 200 + 100 = 850 ps

SPEEDUP
  850 / 250 = 3,40
```

✅ **Resposta:** o ganho **cai ainda mais, para 3,40**. Agora a ULA **virou o gargalo** e passa a penalizar **todos** os estágios do pipeline, inclusive os que só precisariam de 100 ps.

🎯 **A lição das duas letras:**
```text
Num pipeline, só adianta acelerar O ESTÁGIO MAIS LENTO.
Melhorar um estágio que não é o gargalo não muda o clock — só desperdiça projeto.
```

---

# Bloco D — Forwarding, stalls e contagem de ciclos

## D1 🧪 Lista, Seção 2, Questões 1 e 7

> Mostre os **stalls** e os **caminhos de forwarding** necessários para executar as quatro instruções:
> ```asm
> add $3, $4, $6
> sub $5, $3, $2
> lw  $7, 100($5)
> add $8, $7, $2
> ```

### ✍️ Mapa das dependências

| Produtora | Consumidora | Registrador | Distância | Situação |
| --- | --- | --- | --- | --- |
| (1) `add $3` | (2) `sub` lê `$3` | `$3` | 1 | ✅ forwarding **EX/MEM → EX** |
| (2) `sub $5` | (3) `lw` lê `$5` | `$5` | 1 | ✅ forwarding **EX/MEM → EX** |
| (3) `lw $7` | (4) `add` lê `$7` | `$7` | 1 | ⚠️ **LOAD-USE → 1 stall** + forwarding **MEM/WB → EX** |

### ✍️ Diagrama

```text
Ciclo:            C1    C2    C3    C4    C5    C6    C7    C8    C9
────────────────────────────────────────────────────────────────────
add $3,$4,$6      IF    ID    EX ─┐ MEM   WB
                                  │ (a) $3: EX/MEM → EX
sub $5,$3,$2            IF    ID  └►EX ─┐ MEM   WB
                                        │ (b) $5: EX/MEM → EX
lw  $7,100($5)                IF    ID  └►EX   MEM ─┐ WB
                                                    │ (c) $7: MEM/WB → EX
add $8,$7,$2                        IF    ID  ****  └►EX   MEM   WB
                                              bolha
```

✅ **Resultado:**
* **2 caminhos de forwarding EX/MEM → EX** (sem custo);
* **1 caminho MEM/WB → EX** com **1 stall obrigatório** (load-use).

---

## D2 🧪 Lista, Seção 2, Questão 8

> Encontre as **dependências de dados** no código abaixo. Quais são resolvidas por **forwarding**? Quais geram **stall**?
> ```asm
> add $3, $4, $2
> sub $5, $3, $1
> lw  $6, 200($3)
> add $7, $3, $6
> ```

### ✍️ Mapa das dependências

| Produtora | Consumidora | Reg. | Distância | Situação |
| --- | --- | --- | --- | --- |
| (1) `add $3` | (2) `sub` lê `$3` | `$3` | 1 | ✅ forwarding **EX/MEM → EX** |
| (1) `add $3` | (3) `lw` lê `$3` | `$3` | 2 | ✅ forwarding **MEM/WB → EX** |
| (1) `add $3` | (4) `add` lê `$3` | `$3` | 3 | ✅ **sem hazard** — o WB de (1) e o ID de (4) caem no mesmo ciclo |
| (3) `lw $6` | (4) `add` lê `$6` | `$6` | 1 | ⚠️ **LOAD-USE → 1 stall** + forwarding **MEM/WB → EX** |

✅ **Resposta:**
* **Resolvidas por forwarding (sem stall):** as três dependências de `$3`.
* **Gera stall:** apenas a de `$6` (`lw` → `add`), porque é **load-use**: **1 bolha**.

---

## D3 🧪 Lista, Seção 2, Questão 9

> Quantos **ciclos de clock totais** serão gastos nos códigos das questões 7 e 8?

### 🧠 Fórmula

```text
ciclos = N + (E − 1) + stalls  =  N + 4 + stalls
```

### ✍️ Resolução

| Código | N | Stalls | Conta | **Total** |
| --- | :-: | :-: | --- | :-: |
| **Questão 7** (D1) | 4 | 1 (load-use em `$7`) | `4 + 4 + 1` | **9 ciclos** |
| **Questão 8** (D2) | 4 | 1 (load-use em `$6`) | `4 + 4 + 1` | **9 ciclos** |

✅ **Os dois gastam 9 ciclos.** Sem o hazard seriam 8; a bolha acrescenta 1.

🧮 **Se o enunciado pedir o tempo** e o clock for de 200 ps:
```text
9 ciclos × 200 ps = 1.800 ps
```

---

## D4 🧪 Lista, Seção 2, Questão 3 — as três sequências

> Para cada sequência de código abaixo, indique se **deverá haver stall**, se o hazard pode ser **resolvido somente com forwarding**, ou se **não há hazard algum**.

### Sequência 1
```asm
lw  $t0, 0($t0)
add $t1, $t0, $t0
```

🧠 O `lw` escreve `$t0`; o `add` seguinte lê `$t0`. Distância **1** e a produtora é um **load**.

✅ **STALL.** É um **load-use hazard**: exige **1 bolha** e depois um forwarding **MEM/WB → EX**. Não há como resolver só com forwarding.

---

### Sequência 2
```asm
add  $t1, $t0, $t0
addi $t2, $t0, #5
addi $t4, $t1, #5
```

🧠 Quem escreve o quê:
```text
(1) escreve $t1      (3) lê $t1   → distância 2
(2) escreve $t2      ninguém lê
$t0 é só LIDO, nunca escrito → sem dependência
```

✅ **SOMENTE FORWARDING**, sem stall. A dependência de `$t1` tem distância 2, resolvida pelo caminho **MEM/WB → EX**.

```text
Ciclo:              C1   C2   C3   C4   C5   C6   C7
add  $t1,$t0,$t0    IF   ID   EX  MEM ─┐ WB
                                       │ $t1: MEM/WB → EX
addi $t2,$t0,#5          IF   ID   EX  │MEM   WB
addi $t4,$t1,#5               IF   ID  └►EX   MEM   WB
```

---

### Sequência 3
```asm
addi $t1, $t0, #1
addi $t2, $t0, #2
addi $t3, $t0, #2
addi $t3, $t0, #4
addi $t5, $t0, #5
```

🧠 **Todas** leem `$t0` e **nenhuma** escreve em `$t0`. Os destinos (`$t1`, `$t2`, `$t3`, `$t5`) **nunca são lidos** por nenhuma instrução seguinte.

✅ **NÃO HÁ HAZARD ALGUM.** O pipeline roda cheio, sem bolha.

> *Observação:* `$t3` é escrito duas vezes (instruções 3 e 4) — isso seria um **WAW (*Write After Write*)**, mas num pipeline **em ordem** de 5 estágios os WB acontecem na ordem do programa, então **não é um hazard** aqui.

---

# Bloco E — Assembly RISC-V

## E1 🧪 P1 (nas duas turmas) — Questão de 1,0 ponto

> Compile para assembly RISC-V o seguinte código em C, supondo que as variáveis **p, q, r, s, t** estão associadas aos registradores **x6, x7, x8, x9, x10**, respectivamente:
> ```c
> p = (q + r) - (s + t);
> ```

### 🧠 Como pensar

```text
1. Mapeie:  p→x6   q→x7   r→x8   s→x9   t→x10
2. Toda instrução aritmética faz UMA operação com 3 operandos.
   → não dá para fazer tudo numa linha.
3. Resolva os PARÊNTESES primeiro, em registradores TEMPORÁRIOS livres.
4. A ÚLTIMA instrução escreve no destino final (x6).
```

### ✍️ Resolução

```asm
add x11, x7,  x8      # x11 = q + r
add x12, x9,  x10     # x12 = s + t
sub x6,  x11, x12     # p   = (q + r) - (s + t)
```

✅ **Resposta acima.** Os registradores `x11` e `x12` são temporários — **qualquer par de registradores livres serve** (`x5`, `x28`, `x29`...), desde que não sejam `x6` a `x10`, que já estão ocupados.

⚠️ **Erros comuns:**
```asm
sub x6, (x7+x8), (x9+x10)   # ❌ não existe: só 3 operandos, todos registradores
add x6, x7, x8              # ❌ destruiria p antes de usá-lo... e o resultado fica errado
sub x6, x6, x12             #    porque x6 ainda não continha (q+r) na hora certa
```

🎯 **Modelo do slide** (`f = (g+h) − (i+j)` com `f..j` = `x1..x5`), que é o mesmo padrão:
```asm
add x6, x2, x3
add x7, x4, x5
sub x1, x6, x7
```

---

## E2 🧪 Lista, Seção 3, Questão 1

> Traduza o código C abaixo para assembly RISC-V, usando os registradores **x1 (a), x2 (b), x3 (c)**:
> ```c
> a = b + c;
> c = a - 5;
> ```

### ✍️ Resolução

```asm
add  x1, x2, x3      # a = b + c
addi x3, x1, -5      # c = a - 5
```

✅ **Resposta acima.**

⚠️ **A pegadinha:** **NÃO EXISTE a instrução `subi`** no RISC-V.

📌 Explicação do slide: *"Não há necessidade de instrução `subi`, pois o imediato em `add` é representado em **complemento a 2** (pode ser negativo). Assim `subi rd, rs1, imm` é equivalente a `addi rd, rs1, -imm`."*

```asm
subi x3, x1, 5      # ❌ NÃO EXISTE
addi x3, x1, -5     # ✅ forma correta
```

---

## E3 🧪 Exercícios de array (padrão dos slides)

> `g = h + a[8]`, com `h` em `x21` e o endereço base do array `a` de **doublewords** em `x22`. `g` em `x20`.

```asm
ld  x9,  64(x22)     # x9 = a[8]   →  8 elementos × 8 bytes = 64
add x20, x21, x9     # g  = h + a[8]
```

⚠️ **O erro clássico é escrever `ld x9, 8(x22)`** — isso acessaria o **byte 8**, não o **elemento 8**.

---

> `a[12] = h + a[8]`, com `h` em `x21` e base de `a` em `x22`.

```asm
ld  x9, 64(x22)      # x9 = a[8]         (8 × 8 = 64)
add x9, x21, x9      # x9 = h + a[8]
sd  x9, 96(x22)      # a[12] = x9        (12 × 8 = 96)
```

🎯 **Tabela de deslocamento:**

| Tipo | Instrução | Bytes | Deslocamento de `a[i]` |
| --- | --- | :-: | --- |
| doubleword | `ld` / `sd` | 8 | `i × 8` |
| word | `lw` / `sw` | 4 | `i × 4` |
| halfword | `lh` / `sh` | 2 | `i × 2` |
| byte | `lb` / `sb` | 1 | `i × 1` |

---

# Bloco F — Questões discursivas de conceito

## F1 🧪 P1 (nas duas turmas) — "Cite e explique os três tipos de hazards" (1,0 ponto)

### ✅ Resposta modelo

> **Hazards** são situações em que a **próxima instrução não pode ser executada no ciclo de clock seguinte**. Existem três tipos:
>
> **1. Hazard ESTRUTURAL — conflito de recursos.**
> Ocorre quando **duas instruções precisam do mesmo recurso físico (unidade funcional) no mesmo ciclo**. O caso clássico é o de uma **memória única** (Von Neumann): no mesmo ciclo, uma instrução de `load`/`store` está no estágio **MEM** acessando dados, enquanto outra instrução precisa do estágio **IF** para buscar sua instrução. Um dos dois tem que parar (**stall**), criando uma **bolha**.
> **Como afeta a execução:** insere bolhas e reduz a vazão.
> **Solução:** **duplicar o recurso** — usar **caches/memórias separadas de instruções e de dados** (organização tipo Harvard).
>
> **2. Hazard DE DADOS — dependência entre instruções.**
> Ocorre quando uma instrução **precisa do resultado de outra que ainda não terminou**. Exemplo: `add x1,x2,x3` seguido de `sub x4,x1,x5` — o `sub` precisa de `x1` no estágio **EX**, mas o `add` só grava `x1` no estágio **WB**, dois ciclos depois.
> **Como afeta a execução:** a instrução dependente teria que esperar até 3 ciclos.
> **Solução:** **forwarding (encaminhamento/bypassing)** — usar o resultado **assim que ele é calculado**, sem esperar o WB. No caso especial do **load-use** (a produtora é um `lw`), o forwarding **não basta** e é preciso **1 stall**, porque o dado só existe após o estágio MEM. Também é possível usar **reordenação de código** pelo compilador.
>
> **3. Hazard DE CONTROLE — desvios.**
> Ocorre em **desvios condicionais e incondicionais** (`beq`, `bne`, `jal`). O processador **não sabe qual será a próxima instrução** até que o desvio seja resolvido, mas o pipeline já teria buscado as instruções seguintes.
> **Como afeta a execução:** as instruções buscadas erroneamente precisam ser **descartadas**, e o pipeline sofre uma **penalidade de stalls**.
> **Solução:** **antecipar a decisão do desvio** para o estágio **ID** (adicionando hardware para comparar os registradores mais cedo) e usar **previsão de desvio**, **estática** (ex.: "desvio para trás é sempre tomado") ou **dinâmica** (o hardware grava o **histórico recente** de cada desvio). Com previsão, **o stall só acontece quando a previsão erra**.

---

## F2 🧪 P1 (nas duas turmas) — "Por que RISC-V é mais eficiente para pipelining que CISC?" (1,0 ponto)

### ✅ Resposta modelo

> O pipeline exige que **todos os estágios tenham duração fixa e previsível**, porque todos compartilham o mesmo período de clock e precisam estar prontos ao mesmo tempo. A arquitetura RISC-V foi projetada exatamente com essa restrição em mente, enquanto a CISC não.
>
> **Duas características do RISC-V que facilitam o pipelining:**
>
> **1. Instruções de tamanho fixo e poucos formatos.** Todas as instruções têm o **mesmo tamanho** e os campos ficam **sempre nas mesmas posições**. Isso torna o estágio **IF** uma operação de duração constante e permite **ler os registradores antes mesmo de terminar a decodificação**, deixando o **ID** também com duração fixa. Em CISC, as instruções têm **tamanho variável** e o processador só descobre onde a instrução termina **depois** de começar a decodificá-la.
>
> **2. Arquitetura load/store, com poucos modos de endereçamento.** Apenas as instruções `ld`/`sd`/`lw`/`sw` **acessam a memória**, e sempre no modo **base + deslocamento**. Assim, basta **um único estágio MEM** no pipeline. Em CISC, uma instrução aritmética pode buscar operandos na memória, o que exigiria **estágios adicionais** e faria a duração da instrução variar.
>
> **Consequência:** no RISC-V o **CPI fica próximo de 1**, enquanto em CISC a taxa média de ciclos por instrução é **bastante superior a 1**, e a unidade de controle precisa ser **microprogramada**.

### ✅ Dois exemplos de instruções RISC-V (a prova pede)

```asm
add x1, x2, x3     # tipo R: 3 operandos, TODOS em registradores.
                   # Tamanho fixo, uma única operação de ULA, não toca na memória.
                   # Cabe inteira no estágio EX.

ld  x9, 64(x22)    # tipo I: ÚNICO modo de endereçamento (base + deslocamento).
                   # O cálculo do endereço é uma soma simples (EX) e o acesso
                   # fica isolado em um único estágio MEM.
```

---

## F3 🧪 Lista, Seção 1, Questão 1a — "Microarquitetura vs. ISA"

### ✅ Resposta modelo

> **Arquitetura do Conjunto de Instruções (ISA)** é a **visão que o programador tem da máquina** — o "contrato" entre o hardware e o software. Define **o que** a máquina faz: o conjunto de instruções, o conjunto de registradores visíveis, os modos de endereçamento e a ABI. Exemplos: **ARM, RISC-V, x86, x86-64**.
>
> **Microarquitetura** é a **implementação** daquela ISA — define **como** a máquina faz. Inclui o **número e o tamanho das caches**, o **período do clock**, a **utilização (ou não) de pipeline**, e pode ser realizada em **hardware** ou em **software (microcódigo)**.
>
> **A relação entre as duas:** uma **mesma ISA** pode ter **várias microarquiteturas** diferentes. Dois processadores x86 de gerações distintas executam exatamente os mesmos programas (mesma ISA), mas têm desempenhos muito diferentes por causa da microarquitetura.

---

## F4 🧪 Lista, Seção 1, Questão 1b — "Paralelismo temporal e espacial"

### ✅ Resposta modelo

> **Paralelismo TEMPORAL:** o processamento é dividido **ao longo do tempo**, em **estágios**, e várias instruções ocupam **estágios diferentes do mesmo hardware** simultaneamente. É a técnica de **pipelining**. A analogia é uma **linha de montagem industrial**, em que cada etapa realiza uma parte do trabalho.
> **Exemplo:** num pipeline de 5 estágios, enquanto a instrução 1 está no estágio MEM, a instrução 2 está em EX, a 3 em ID e a 4 em IF — quatro instruções em andamento ao mesmo tempo, com **uma única** unidade de cada tipo.
>
> **Paralelismo ESPACIAL:** **diferentes partes de um problema** são resolvidas **simultaneamente**, em **unidades de hardware distintas**. A analogia é um **grupo de pessoas dividindo tarefas** em uma equipe.
> **Exemplo:** um processador **multicore** de 4 núcleos executando 4 threads ao mesmo tempo, ou uma **GPU** somando centenas de elementos de um vetor de uma só vez.
>
> **A diferença essencial:** no temporal, as instruções estão em **estágios diferentes** do **mesmo** hardware; no espacial, estão em **hardwares diferentes**, podendo estar no **mesmo** estágio.

---

# Bloco G — Objetivas e V/F

## G1 🧪 "Em pipelines, forwarding é usado para:" (0,5 — caiu nas duas turmas)

| | Alternativa | |
| --- | --- | --- |
| a) | Reduzir o CPI / Reduzir o tempo de clock | ❌ |
| b) | Eliminar hazards de controle | ❌ (isso é previsão de desvio) |
| **c)** | ✅ **Evitar stalls causados por hazards de dados** | ✅ **RESPOSTA** |
| d) | Simplificar a decodificação de instruções | ❌ |

---

## G2 🧪 "Um hazard ESTRUTURAL ocorre devido a:" (0,5)

| | Alternativa | |
| --- | --- | --- |
| **a)** | ✅ **Conflito por uso de recursos** | ✅ **RESPOSTA** |
| b) | Desvios condicionais não previstos | ❌ hazard de **controle** |
| c) | Dependência de dados não resolvida | ❌ hazard de **dados** |
| d) | Acesso à memória lento | ❌ não é hazard |

---

## G3 🧪 "Um hazard DE CONTROLE ocorre devido a:" (0,5)

| | Alternativa | |
| --- | --- | --- |
| a) | Conflito de unidades funcionais | ❌ hazard **estrutural** |
| b) | Dependência de dados entre instruções | ❌ hazard de **dados** |
| **c)** | ✅ **Desvios condicionais não previstos** | ✅ **RESPOSTA** |
| d) | Acesso à memória lento | ❌ |

🎯 **G2 e G3 são a mesma questão com as alternativas embaralhadas.** Decore o trio:
```text
recurso  → estrutural
dados    → de dados
desvio   → de controle
```

---

## G4 🧪 "Qual arquitetura usa memória única para dados e instruções?" (0,5)

| | Alternativa | |
| --- | --- | --- |
| a) | Harvard | ❌ memórias **separadas** |
| **b)** | ✅ **Von Neumann** | ✅ **RESPOSTA** |
| c) | RISC-V | ❌ é uma ISA, não um modelo de memória |
| d) | CISC | ❌ é um estilo de conjunto de instruções |

---

## G5 🧪 "Relacione as colunas" (0,5 — caiu nas duas turmas)

| Coluna 1 | Coluna 2 |
| --- | --- |
| **(1)** Hazard estrutural | **( 1 )** Conflito por uso simultâneo da memória de dados e instruções |
| **(2)** Predição estática de branch | **( 2 )** Assume que um branch "para trás" (loop) é sempre tomado |

✅ **Gabarito: 1 – 2**

🎯 **Por que "para trás" é predito como tomado?** Um desvio para trás quase sempre fecha um **laço**, que se repete muitas vezes. Prever "tomado" acerta na grande maioria das iterações.

---

## G6 🧪 P1 Turma B, Questão 8 — V/F com justificativa (0,5)

| Afirmativa | Gabarito | Justificativa |
| --- | :-: | --- |
| Hazards estruturais ocorrem quando **duas instruções precisam do mesmo recurso físico no mesmo ciclo** | **V** | É exatamente a definição: conflito de unidades funcionais |
| No modelo de processamento temporal (pipeline), **múltiplas instruções estão em estágios diferentes simultaneamente** | **V** | É a definição de paralelismo temporal / pipelining |
| Arquitetura de computadores define **apenas** o conjunto de instruções, enquanto organização define os detalhes de hardware | **F** | ⚠️ O erro é o **"apenas"**. A arquitetura define **também** os modos de endereçamento, os formatos de instrução, o número de bits dos tipos de dados e a estrutura geral visível ao programador |

---

## G7 🧪 P1 Turma A, Questão 4 — V/F com justificativa (0,5)

| Afirmativa | Gabarito | Justificativa |
| --- | :-: | --- |
| **RISC-V usa apenas `load`/`store` para acesso à memória** | **V** | É a característica **load/store architecture**, e é justamente o que permite **um único estágio MEM** no pipeline |
| **CISC tem instruções de tamanho variável** | **V** | Formato **irregular** é característica listada nos slides; é por isso que o pipeline em CISC é difícil |
| **Forwarding elimina TODOS os hazards de dados** | **F** | ⚠️ Não elimina o **load-use hazard**. No `lw` o dado só fica disponível **após o 4º estágio (MEM)**, e não é possível "voltar no tempo" — **1 stall é inevitável** |

---

# Bloco H — Gabarito rápido

## Objetivas

| Questão | Resposta |
| --- | --- |
| Forwarding é usado para... | **Evitar stalls causados por hazards de dados** |
| Hazard **estrutural** ocorre devido a... | **Conflito por uso de recursos** |
| Hazard **de controle** ocorre devido a... | **Desvios condicionais não previstos** |
| Memória única para dados e instruções | **Von Neumann** |
| Relacionar colunas | **(1)** estrutural → memória compartilhada · **(2)** predição estática → branch para trás é tomado |

## V/F

| Afirmativa | |
| --- | :-: |
| Hazard estrutural = mesmo recurso no mesmo ciclo | **V** |
| Pipeline = múltiplas instruções em estágios diferentes | **V** |
| Arquitetura define **apenas** o conjunto de instruções | **F** |
| RISC-V usa apenas load/store para memória | **V** |
| CISC tem instruções de tamanho variável | **V** |
| Forwarding elimina **todos** os hazards de dados | **F** |

## Contas

| Enunciado | Resposta |
| --- | --- |
| Monociclo com IF 100, ID 100, EX 300, MEM 500, WB 100 | **1100 ps** |
| Pipeline com os mesmos estágios | **500 ps** |
| Monociclo com IF 50, ID 50, EX 200, MEM 400, WB 50 | **750 ps** |
| Pipeline com os mesmos estágios | **400 ps** |
| Speedup: 200 instr., 5 est. de 200 ps, mono 800 ps | **≈ 3,92×** (teórico 4) |
| Speedup: 50 instr., 5 est. de 150 ps, mono 900 ps | **≈ 5,5×** (teórico 6) |
| Speedup: 100 instr., 5 est. de 200 ps, mono 800 ps | **≈ 3,85×** (teórico 4) |
| ALU −25% (200→150 ps) | pipeline **não muda** (200 ps); speedup cai de **4,00 → 3,75** |
| ALU +25% (200→250 ps) | pipeline vai a **250 ps**; speedup cai para **3,40** |
| Ciclos: 4 instruções com 1 load-use | **9 ciclos** |

## Assembly

| Enunciado | Resposta |
| --- | --- |
| `p = (q+r) − (s+t)` · `p..t = x6..x10` | `add x11,x7,x8` / `add x12,x9,x10` / `sub x6,x11,x12` |
| `a = b+c; c = a−5` · `a,b,c = x1,x2,x3` | `add x1,x2,x3` / `addi x3,x1,-5` |
| `g = h + a[8]` (doublewords, base `x22`) | `ld x9,64(x22)` / `add x20,x21,x9` |
| `a[12] = h + a[8]` | `ld x9,64(x22)` / `add x9,x21,x9` / `sd x9,96(x22)` |

## Hazards dos códigos da lista

| Código | Hazards | Stalls | Ciclos |
| --- | --- | :-: | :-: |
| `add $3` / `sub $5,$3` / `lw $7,100($5)` / `add $8,$7` | 2 por forwarding EX/MEM→EX + 1 load-use | **1** | **9** |
| `add $3` / `sub $5,$3` / `lw $6,200($3)` / `add $7,$3,$6` | 3 de `$3` por forwarding + 1 load-use em `$6` | **1** | **9** |
| Seq 1: `lw $t0,0($t0)` / `add $t1,$t0,$t0` | load-use | **1** | **6** |
| Seq 2: `add $t1` / `addi $t2` / `addi $t4,$t1` | distância 2 → só forwarding | **0** | **7** |
| Seq 3: cinco `addi` lendo `$t0` | **nenhum hazard** | **0** | **9** |

---

## ⏱️ Estratégia de prova

```text
1. COMECE pelas contas (questões 2 e 3) — são as mais rápidas e valem 3,0 pontos.
   Monociclo = SOMA · Pipeline = MAIOR · ciclos = N + 4 · S = T_mono / T_pipe

2. Depois o ASSEMBLY (1,0) — é mecânico: parênteses primeiro, temporários, destino por último.

3. Depois as OBJETIVAS (2,0 somadas) — recurso/dados/desvio resolve quase todas.

4. Deixe por último a questão 1 (diagrama, 2,0) e as discursivas —
   são as que consomem tempo.

5. Na questão do diagrama, SEMPRE escreva:
   · o tipo do hazard COM o nome técnico (load-use / RAW)
   · o CICLO exato do conflito
   · origem e destino do forwarding pelo nome do registrador de pipeline
     (EX/MEM ou MEM/WB) → é isso que o professor quer ver
   · a convenção que você usou para contar os stalls sem forwarding
```
