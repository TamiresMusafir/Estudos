# 🎓 Arquitetura de Computadores — Aprendendo do Zero

> **Este arquivo é para APRENDER**, não para revisar. Ele constrói cada ideia do começo, com desenhos e simulações passo a passo.
> Para revisar na véspera, use os outros dois: `ARQ_conceitos_P1.md` e `ARQ_exercicios_resolvidos.md`.
>
> **Como usar:** leia na ordem, sem pular. Cada aula depende da anterior. Quando aparecer 🛑 **PARE E PENSE**, tente responder **antes** de ler a resposta — é aí que o aprendizado acontece.

---

## 📑 As aulas

| # | Aula | O que você vai entender |
| --- | --- | --- |
| **0** | [O problema](#aula-0--o-problema-por-que-tudo-isso-existe) | Por que essa matéria existe |
| **1** | [Como uma instrução é executada](#aula-1--como-uma-instrução-é-executada-de-verdade) | O que o processador realmente faz |
| **2** | [Monociclo](#aula-2--monociclo-a-primeira-tentativa) | A solução ingênua e por que ela é ruim |
| **3** | [A grande ideia: pipeline](#aula-3--a-grande-ideia-pipeline) | Como se ganha velocidade de graça |
| **4** | [As contas](#aula-4--as-contas-construídas-do-zero) | De onde saem as fórmulas |
| **5** | [Quando o pipeline quebra](#aula-5--quando-o-pipeline-quebra-hazards) | Os três hazards |
| **6** | [Forwarding](#aula-6--forwarding-o-atalho) | O atalho que salva o pipeline |
| **7** | [O caso perdido](#aula-7--load-use-o-caso-que-não-tem-jeito) | Por que às vezes não tem jeito |
| **8** | [Desvios](#aula-8--desvios-e-o-problema-de-adivinhar-o-futuro) | Adivinhar o futuro |
| **9** | [RISC × CISC](#aula-9--risc--cisc-por-que-a-arquitetura-importa) | Por que o RISC-V venceu |
| **10** | [Assembly RISC-V](#aula-10--assembly-risc-v-do-zero) | Escrever código de máquina |
| **11** | [Os conceitos abstratos](#aula-11--os-conceitos-abstratos-finalmente-concretos) | Arquitetura × organização, Von Neumann × Harvard, throughput × latência |
| **12** | [Juntando tudo](#aula-12--juntando-tudo) | Um programa completo, do C ao speedup |
| **13** | [Exercícios comentados](#aula-13--exercícios-progressivos) | Treinar em 5 níveis |

---

# AULA 0 — O problema: por que tudo isso existe

## A pergunta que originou a matéria

Você tem um processador. Ele executa um programa em **10 segundos**. Você quer que execute em **2 segundos**.

🛑 **PARE E PENSE:** quais são as formas possíveis de conseguir isso?

<br>

**Só existem três caminhos.** E a matéria inteira é sobre eles:

```text
        PROGRAMA DEMORA DEMAIS
                  │
    ┌─────────────┼─────────────┐
    │             │             │
    ▼             ▼             ▼
1. Fazer cada   2. Executar   3. Fazer VÁRIAS
   passo mais      MENOS         coisas AO MESMO
   rápido          passos        TEMPO
    │             │             │
    ▼             ▼             ▼
 clock mais    instruções    PIPELINE  ·  MULTICORE
 alto          melhores      (temporal)   (espacial)
    │             │
    ▼             ▼
 esbarra no    é o debate
 CALOR ☠️      RISC × CISC
```

**Caminho 1 — aumentar o clock.** Funcionou até ~2005. Depois os processadores começaram a **derreter**: mais clock = mais calor. Hoje estamos travados em torno de 3–5 GHz.

**Caminho 2 — instruções melhores.** É o debate **RISC × CISC** (Aula 9).

**Caminho 3 — fazer várias coisas ao mesmo tempo.** É o **paralelismo**, e ele se divide em dois:

```text
PARALELISMO TEMPORAL              PARALELISMO ESPACIAL
= PIPELINE                        = MULTICORE / GPU

"vou dividir cada tarefa em        "vou colocar VÁRIOS
 etapas e sobrepor as etapas        trabalhadores fazendo
 de tarefas diferentes"             tarefas diferentes"

  UM trabalhador,                   VÁRIOS trabalhadores,
  várias tarefas em                 cada um com sua tarefa
  fases diferentes
```

⭐ **A P1 de vocês é quase toda sobre o PIPELINE** (paralelismo temporal). Por isso vamos entrar fundo nele.

## A fórmula que resume tudo

Existe uma equação que amarra os três caminhos:

```text
     Tempo do programa  =  N.º de instruções  ×  CPI  ×  Período do clock
                                    │            │            │
                                    │            │            └─ caminho 1
                                    │            └────────────── caminho 3 (pipeline!)
                                    └─────────────────────────── caminho 2
```

📌 Nos slides, ela aparece assim: **`Tp = Ci × Tc × Ni`**

| Símbolo | Nome | Significa |
| --- | --- | --- |
| `Tp` | tempo do programa | o que queremos diminuir |
| `Ni` | número de instruções | quantas instruções o programa tem |
| `Ci` | **CPI** = ciclos por instrução | quantos ciclos de clock cada instrução gasta |
| `Tc` | período do clock | quanto tempo dura um ciclo |

🔎 **Exemplo numérico:**

```text
Um programa com 1.000 instruções, CPI = 5, clock de 1 GHz (Tc = 1 ns)

Tp = 1.000 × 5 × 1 ns = 5.000 ns = 5 μs
```

🛑 **PARE E PENSE:** se o pipeline faz o CPI cair de 5 para 1, o programa fica quantas vezes mais rápido?

<br>

```text
Tp = 1.000 × 1 × 1 ns = 1.000 ns    →   5 vezes mais rápido ✅
```

⭐ **É EXATAMENTE isso que o pipeline faz: leva o CPI de ~5 para ~1.** Guarde essa ideia; vamos construí-la nas próximas aulas.

---

# AULA 1 — Como uma instrução é executada (de verdade)

Antes de falar em pipeline, você precisa saber **o que acontece por dentro** quando o processador executa uma linha de código.

## A instrução não é "uma coisa só"

Quando você escreve:

```asm
add x1, x2, x3      # x1 = x2 + x3
```

o processador **não faz isso de uma vez**. Ele passa por **cinco etapas obrigatórias**:

```text
┌──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐
│      IF      │      ID      │      EX      │     MEM      │      WB      │
│              │              │              │              │              │
│  Instruction │  Instruction │    Execute   │    Memory    │  Write Back  │
│     Fetch    │    Decode    │              │    Access    │              │
├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
│   BUSCAR     │  ENTENDER    │    FAZER     │   ACESSAR    │   GUARDAR    │
│ a instrução  │  o que fazer │    a conta   │   a memória  │ o resultado  │
│ na memória   │ e pegar os   │              │ (só lw e sw) │              │
│              │ registradores│              │              │              │
└──────────────┴──────────────┴──────────────┴──────────────┴──────────────┘
```

💡 **A analogia do pedido no restaurante:**

```text
IF  → o garçom PEGA o papel do pedido            ("busca a instrução")
ID  → ele LÊ o pedido e separa os ingredientes   ("decodifica e lê registradores")
EX  → o cozinheiro COZINHA                       ("executa a operação")
MEM → alguém vai à DESPENSA buscar/guardar algo  ("acessa a memória")
WB  → o prato é COLOCADO na mesa                 ("escreve o resultado")
```

## Vendo cada estágio de perto

Vamos acompanhar **de verdade** a instrução `add x1, x2, x3`, supondo que `x2 = 10` e `x3 = 7`.

### Estágio 1 — IF (*Instruction Fetch*)

```text
       MEMÓRIA DE INSTRUÇÕES
       ┌────────────────────────────┐
       │ endereço 100: add x1,x2,x3 │ ◄──── o PC aponta para cá
       │ endereço 104: sub x4,x1,x5 │
       │ endereço 108: sw  x4,0(x6) │
       └────────────────────────────┘
                     │
                     ▼
              ┌─────────────┐
              │ PC = 100    │  →  busca a instrução do endereço 100
              └─────────────┘     e depois faz  PC = PC + 4
```

**O que acontece:** o processador olha o registrador **`pc`** (*program counter*), vai até aquele endereço na memória e **traz a instrução**. Depois incrementa o `pc` para apontar para a próxima.

⚠️ Note que nesse ponto o processador **ainda não sabe** que a instrução é um `add`. Ele só tem um monte de bits.

### Estágio 2 — ID (*Instruction Decode*)

```text
   Os bits da instrução chegam:   0000000 00011 00010 000 00001 0110011
                                   └──┬──┘ └─┬─┘ └─┬─┘     └─┬─┘  └──┬──┘
                                      │     │     │          │       │
                                    func7  rs2   rs1        rd    opcode
                                            x3    x2        x1     "é um add"

   ┌───────────────────────────────────────┐
   │    BANCO DE REGISTRADORES             │
   │  x0 = 0 (sempre)                      │
   │  x1 = ?                               │
   │  x2 = 10  ──────────┐                 │  ← lê rs1
   │  x3 = 7   ──────────┼──┐              │  ← lê rs2
   │  ...                │  │              │
   └─────────────────────┼──┼──────────────┘
                         ▼  ▼
                        10  7    (prontos para a ULA)
```

**O que acontece:** o processador **descobre** que é uma soma, **descobre** quais registradores usar, e **lê os valores** deles.

⭐ **É aqui que entra a primeira grande vantagem do RISC-V:** como todas as instruções têm o **mesmo formato**, os campos `rs1` e `rs2` ficam **sempre na mesma posição**. Por isso dá para **começar a ler os registradores antes mesmo de terminar de decodificar**. Em CISC isso é impossível.

### Estágio 3 — EX (*Execute*)

```text
              10 ───┐
                    │  ┌──────────┐
                    ├─►│   ULA    │────► 17
                    │  │  (soma)  │
               7 ───┘  └──────────┘
```

**O que acontece:** a **ULA** (Unidade Lógica e Aritmética) faz a conta. Aqui é onde acontece `+`, `-`, `AND`, `OR`, comparações...

💡 **Para `lw` e `sw`, este estágio faz outra coisa:** calcula o **endereço de memória**.

```text
lw x1, 64(x22)   →   EX calcula:  x22 + 64  =  endereço a ser lido
```

### Estágio 4 — MEM (*Memory Access*)

```text
   Para add:                     Para lw x1, 64(x22):
   ┌───────────────┐             ┌──────────────────────────┐
   │  NÃO FAZ NADA │             │   MEMÓRIA DE DADOS       │
   │  (passa reto) │             │   endereço 1064 → 42     │──► 42
   └───────────────┘             └──────────────────────────┘
```

⭐ **Este é o estágio que SÓ o `lw` e o `sw` usam.** Um `add` passa por ele sem fazer nada — mas **passa**, porque todas as instruções percorrem os cinco estágios.

🛑 **PARE E PENSE:** por que o `add` não pula o estágio MEM, já que não precisa dele?

<br>

**Resposta:** porque se cada instrução tivesse um caminho diferente, elas poderiam **ultrapassar umas às outras** e chegar fora de ordem no WB. Manter todo mundo no mesmo trilho, com o mesmo número de estágios, é o que garante que os resultados sejam gravados **na ordem do programa**.

### Estágio 5 — WB (*Write Back*)

```text
                  17
                   │
                   ▼
   ┌───────────────────────────────────────┐
   │    BANCO DE REGISTRADORES             │
   │  x1 = 17  ◄───── gravado agora        │
   │  x2 = 10                              │
   │  x3 = 7                               │
   └───────────────────────────────────────┘
```

**O que acontece:** o resultado é **gravado no registrador de destino**.

⚠️ **Guarde essa informação, ela é a raiz de todos os hazards de dados:**

```text
O resultado de uma instrução SÓ FICA VISÍVEL no banco de registradores
no ÚLTIMO estágio (WB).
```

## Resumo da Aula 1

```text
add x1, x2, x3    com x2=10, x3=7

IF  → busca os bits da instrução na memória
ID  → descobre "é add", lê x2=10 e x3=7
EX  → ULA calcula 10 + 7 = 17
MEM → não faz nada (só passa)
WB  → grava 17 em x1
```

| Instrução | IF | ID | EX | MEM | WB |
| --- | :-: | :-: | :-: | :-: | :-: |
| `add`, `sub`, `and`, `or` (tipo R) | ✅ | ✅ | ✅ calcula | ⬜ nada | ✅ grava |
| `lw` (load) | ✅ | ✅ | ✅ calcula endereço | ✅ **lê** | ✅ grava |
| `sw` (store) | ✅ | ✅ | ✅ calcula endereço | ✅ **escreve** | ⬜ nada |
| `beq` (desvio) | ✅ | ✅ | ✅ compara | ⬜ nada | ⬜ nada |

⭐ **Repare:** o `lw` é a **única** instrução que **lê** da memória **e** grava num registrador. É por isso que ele usa **os cinco estágios** e é o mais lento. **Guarde isso — vai explicar quase tudo daqui para frente.**

---

# AULA 2 — Monociclo: a primeira tentativa

## A ideia mais simples possível

**Monociclo** = "uma instrução por ciclo de clock". Cada instrução entra, percorre os cinco estágios, e só então a próxima começa.

```text
     ◄──────────── 1 ciclo de clock ────────────►
     ┌────┬────┬────┬─────┬────┐
  1: │ IF │ ID │ EX │ MEM │ WB │
     └────┴────┴────┴─────┴────┘
                                ┌────┬────┬────┬─────┬────┐
  2:                            │ IF │ ID │ EX │ MEM │ WB │
                                └────┴────┴────┴─────┴────┘
                                                             ┌────┬───
  3:                                                         │ IF │ ...
                                                             └────┴───
```

## O problema nº 1: o clock tem que caber a instrução inteira

Se o ciclo de clock tem que comportar os **cinco estágios**, então:

```text
Tc (monociclo) = IF + ID + EX + MEM + WB    ← a SOMA
```

🔎 **Com os tempos reais dos slides:**

| Estágio | Tempo |
| --- | --- |
| IF (busca da instrução) | 200 ps |
| ID (leitura dos registradores) | 100 ps |
| EX (ULA) | 200 ps |
| MEM (acesso aos dados) | 200 ps |
| WB (escrita no registrador) | 100 ps |

```text
Tc = 200 + 100 + 200 + 200 + 100 = 800 ps
```

## O problema nº 2 (o pior): o clock é ditado pela instrução mais lenta

🛑 **PARE E PENSE:** um `beq` não usa o MEM nem o WB. Ele só precisa de 200 + 100 + 200 = 500 ps. Então ele pode rodar em 500 ps?

<br>

**NÃO.** E é aqui que mora o desperdício.

```text
O CLOCK É ÚNICO para o processador inteiro. Ele não muda de instrução
para instrução. Então tem que ser grande o suficiente para caber a
instrução MAIS LENTA — que é o lw, com 800 ps.
```

```text
             ◄────────── 800 ps (o clock) ──────────►

 lw    ┌──────┬────┬──────┬──────┬────┐
       │  IF  │ ID │  EX  │ MEM  │ WB │  usa tudo ✅
       └──────┴────┴──────┴──────┴────┘

 beq   ┌──────┬────┬──────┐▒▒▒▒▒▒▒▒▒▒▒▒
       │  IF  │ ID │  EX  │▒ DESPERDÍCIO ▒   300 ps jogados fora ❌
       └──────┴────┴──────┘▒▒▒▒▒▒▒▒▒▒▒▒

 add   ┌──────┬────┬──────┬──────┐▒▒▒▒▒▒
       │  IF  │ ID │  EX  │  WB  │▒ LIXO ▒    200 ps jogados fora ❌
       └──────┴────┴──────┴──────┘▒▒▒▒▒▒
```

⭐ **A conclusão que vale ponto na prova:**

> No monociclo, **todas** as instruções gastam o tempo da **mais lenta** (`lw`, 800 ps), mesmo as que precisariam de menos. É isso que torna o monociclo ineficiente.

## O problema nº 3: o hardware fica parado

Olhe de novo o desenho do monociclo:

```text
     ┌────┬────┬────┬─────┬────┐
  1: │ IF │ ID │ EX │ MEM │ WB │
     └────┴────┴────┴─────┴────┘

   Enquanto a instrução está em EX, o que a unidade de IF está fazendo?
```

🛑 **PARE E PENSE.**

<br>

**NADA.** Ela fica **parada**, esperando. O mesmo vale para ID, MEM e WB.

```text
     Ciclo 1 (800 ps)
     │
     ├─ IF  trabalha por 200 ps, depois fica OCIOSO por 600 ps  💤
     ├─ ID  fica ocioso 200 ps, trabalha 100, ocioso 500        💤
     ├─ EX  fica ocioso 300 ps, trabalha 200, ocioso 300        💤
     ├─ MEM fica ocioso 500 ps, trabalha 200, ocioso 100        💤
     └─ WB  fica ocioso 700 ps, trabalha 100                    💤

     Cada unidade trabalha só ~25% do tempo!
```

⭐ **E é exatamente esse desperdício que o PIPELINE vai atacar.**

---

# AULA 3 — A grande ideia: pipeline

## Primeiro, a lavanderia

Você tem 4 cestos de roupa para lavar. Cada cesto passa por 4 etapas, **30 minutos cada**:

```text
🧺 LAVAR  →  🌀 SECAR  →  👔 PASSAR  →  🗄️ GUARDAR
```

### Jeito 1 — sequencial (o "monociclo" da lavanderia)

Você espera o cesto 1 terminar **tudo** antes de começar o cesto 2.

```text
Hora:  0    30   60   90   120  150  180  210  240  270  300  330  360  390  420  450  480
       │    │    │    │    │    │    │    │    │    │    │    │    │    │    │    │    │
Cesto1 ├LAV─┼SEC─┼PAS─┼GUA─┤
Cesto2                     ├LAV─┼SEC─┼PAS─┼GUA─┤
Cesto3                                         ├LAV─┼SEC─┼PAS─┼GUA─┤
Cesto4                                                             ├LAV─┼SEC─┼PAS─┼GUA─┤

TOTAL: 4 cestos × 4 etapas × 30 min = 480 minutos (8 horas)
```

🛑 **PARE E PENSE:** enquanto o cesto 1 está na secadora, o que a **lavadora** está fazendo?

<br>

**Nada.** E é aí que está o desperdício — o mesmo do monociclo.

### Jeito 2 — pipeline

Assim que o cesto 1 sai da lavadora e vai para a secadora, você **já coloca o cesto 2 na lavadora**.

```text
Hora:  0    30   60   90   120  150  180  210
       │    │    │    │    │    │    │    │
Cesto1 ├LAV─┼SEC─┼PAS─┼GUA─┤
Cesto2      ├LAV─┼SEC─┼PAS─┼GUA─┤
Cesto3           ├LAV─┼SEC─┼PAS─┼GUA─┤
Cesto4                ├LAV─┼SEC─┼PAS─┼GUA─┤

TOTAL: 210 minutos (3,5 horas)
```

📌 **É o exemplo do slide:** `Speedup = 8 / 3,5 = 2,3`

### 🔑 As três lições da lavanderia

Olhe o desenho de novo e repare em três coisas:

```text
1. O PRIMEIRO cesto demorou o MESMO TEMPO que antes: 120 minutos.
   → o pipeline NÃO acelera uma tarefa individual (LATÊNCIA não muda)

2. A partir do minuto 120, sai UM CESTO PRONTO a cada 30 minutos.
   → o pipeline acelera a VAZÃO (throughput)

3. No começo (0 a 90 min) e no fim, algumas máquinas ficam paradas.
   → é o ENCHIMENTO e o ESVAZIAMENTO do pipeline
```

⭐ **Essas três frases são a matéria inteira.** Se você entendeu a lavanderia, entendeu o pipeline.

## Agora, com instruções

Exatamente a mesma ideia, trocando os cestos por instruções e as máquinas pelos cinco estágios:

```text
Ciclo:          C1    C2    C3    C4    C5    C6    C7    C8    C9
─────────────────────────────────────────────────────────────────────
1: lw           IF    ID    EX   MEM    WB
2: sub                IF    ID    EX   MEM    WB
3: add                      IF    ID    EX   MEM    WB
4: sw                             IF    ID    EX   MEM    WB
5: or                                   IF    ID    EX   MEM    WB
```

**Leia na VERTICAL, para ver o que acontece em cada ciclo:**

```text
No ciclo C5, o processador está fazendo CINCO COISAS AO MESMO TEMPO:

   ┌──────────────────────────────────────────────────┐
   │  A unidade de  IF  está buscando a instrução 5   │
   │  A unidade de  ID  está decodificando a 4        │
   │  A unidade de  EX  está calculando a 3           │
   │  A unidade de MEM  está acessando memória p/ a 2 │
   │  A unidade de  WB  está gravando o resultado da 1│
   └──────────────────────────────────────────────────┘

   NENHUMA unidade está parada. É isso que o pipeline resolve.
```

## A segunda grande vantagem: o clock encolhe

🛑 **PARE E PENSE:** no pipeline, o ciclo de clock precisa caber a instrução inteira?

<br>

**NÃO!** E essa é a sacada.

```text
No pipeline, cada ciclo executa só UM ESTÁGIO.
Então o clock só precisa caber o ESTÁGIO MAIS LENTO.
```

```text
MONOCICLO                          PIPELINE
Tc = SOMA dos estágios             Tc = MAIOR estágio

  200+100+200+200+100 = 800 ps       max(200,100,200,200,100) = 200 ps

  ◄──────── 800 ps ────────►         ◄─200─►
  ┌────┬──┬────┬────┬──┐             ┌─────┐
  │ IF │ID│ EX │MEM │WB│             │ IF  │  ← um estágio por ciclo
  └────┴──┴────┴────┴──┘             └─────┘
```

⭐ **O clock ficou 4 vezes mais rápido.** De 800 ps para 200 ps.

## Por que "o maior estágio"?

💡 Porque **todos os estágios trabalham ao mesmo tempo, e todos têm que terminar antes do próximo ciclo começar**. É como uma equipe em que todos passam o bastão junto: o ritmo é o do **mais lento**.

```text
   ◄─────── 200 ps (um ciclo) ───────►
   ┌──────────────────────────────────┐
IF │████████████████████████████████  │  200 ps  ← o gargalo
   ├──────────────────────────────────┤
ID │████████████                      │  100 ps (sobra tempo, espera)
   ├──────────────────────────────────┤
EX │████████████████████████████████  │  200 ps  ← o gargalo
   ├──────────────────────────────────┤
MEM│████████████████████████████████  │  200 ps  ← o gargalo
   ├──────────────────────────────────┤
WB │████████████                      │  100 ps (sobra tempo, espera)
   └──────────────────────────────────┘
                                      ▲
                          todos só passam o bastão AQUI
```

⚠️ **Consequência prática que já caiu na prova:** se você **acelerar o ID** (de 100 para 50 ps), o clock **não muda nada** — ele continua 200 ps, ditado por IF/EX/MEM. **Só adianta acelerar o gargalo.**

## Os registradores de pipeline (isso quase ninguém explica)

Entre um estágio e outro existe um **registrador** que guarda o resultado parcial:

```text
        ┌────┐      ┌────┐      ┌────┐      ┌─────┐      ┌────┐
        │ IF │      │ ID │      │ EX │      │ MEM │      │ WB │
        └──┬─┘      └──┬─┘      └──┬─┘      └───┬─┘      └────┘
           │           │           │            │
        ┌──▼──┐     ┌──▼──┐     ┌──▼───┐    ┌───▼──┐
        │IF/ID│     │ID/EX│     │EX/MEM│    │MEM/WB│
        └─────┘     └─────┘     └──────┘    └──────┘
         ▲                          ▲            ▲
         │                          │            │
    "gavetinhas" que seguram    ⭐ ESTES DOIS NOMES vão aparecer
    o trabalho de um estágio       na questão de FORWARDING
    até o próximo pegar
```

⭐ **Por que isso importa:** quando a prova pede *"indique a ORIGEM e o DESTINO do forwarding"*, a resposta é o **nome dessas gavetinhas**: `EX/MEM` e `MEM/WB`. Agora você sabe o que elas são — não é sigla decorada, é o **registrador entre dois estágios**.

## Resumo da Aula 3

```text
┌─────────────────────────────────────────────────────────────┐
│  O PIPELINE GANHA DE DOIS JEITOS AO MESMO TEMPO:            │
│                                                             │
│  1) O CLOCK ENCOLHE                                         │
│     de "soma dos estágios" para "o maior estágio"           │
│     800 ps  →  200 ps                                       │
│                                                             │
│  2) AS INSTRUÇÕES SE SOBREPÕEM                              │
│     sai uma instrução pronta POR CICLO                      │
│     CPI vai de 5 para ~1                                    │
│                                                             │
│  O QUE NÃO MUDA:                                            │
│  · a LATÊNCIA de uma instrução (continua 5 estágios)        │
│  · aliás, pode até PIORAR um pouco                          │
└─────────────────────────────────────────────────────────────┘
```

🛑 **PARE E PENSE:** uma instrução sozinha, isolada, é mais rápida no monociclo ou no pipeline?

<br>

```text
MONOCICLO: 1 ciclo × 800 ps                    = 800 ps
PIPELINE:  5 ciclos × 200 ps                   = 1000 ps  ← MAIS LENTO!
```

⭐ **Uma instrução sozinha é MAIS LENTA no pipeline.** O ganho só aparece quando há **muitas** instruções. É por isso que o slide insiste: *"a latência não se altera"* (ou até piora) — **o ganho é de VAZÃO**.

---

# AULA 4 — As contas, construídas do zero

Aqui você vai **deduzir** as fórmulas em vez de decorá-las. Depois disso, nenhuma questão de conta vai te pegar.

## Passo 1 — a conta do monociclo

```text
Cada instrução gasta 1 ciclo. O ciclo é grande (a soma dos estágios).

    T_mono  =  N  ×  Tc_mono
                │       │
                │       └─ SOMA de todos os estágios
                └───────── número de instruções
```

🔎 **Exemplo (é a questão do quadro do professor):**

```text
N = 200 instruções
estágios: 5, de 200 ps cada  →  Tc_mono = 5 × 200 = 1000 ps?
```

⚠️ **CUIDADO — a pegadinha mais comum da prova.** O enunciado normalmente **já te dá** o `Tc` do monociclo, e ele **não é** a soma simples. No enunciado do professor:

```text
"5 estágios de 200 ps, monociclo com ciclo de 800 ps"
```

💡 **Por que 800 e não 1000?** Porque os estágios **não são todos de 200 ps**. Os tempos reais são 200/100/200/200/100:

```text
SOMA   = 200+100+200+200+100 = 800 ps   ← este é o Tc do MONOCICLO
MAIOR  = max(200,100,200,200,100) = 200 ps  ← este é o Tc do PIPELINE
```

⭐ **Regra de ouro:** **use sempre o número que o enunciado dá.** Se ele diz "monociclo de 800 ps", é 800. Não recalcule.

```text
T_mono = 200 × 800 = 160.000 ps ✅
```

## Passo 2 — a conta do pipeline

Aqui é onde quase todo mundo erra. Vamos **construir** a fórmula olhando o desenho.

```text
5 estágios, 3 instruções:

Ciclo:      C1   C2   C3   C4   C5   C6   C7
─────────────────────────────────────────────
1:          IF   ID   EX  MEM   WB
2:               IF   ID   EX  MEM   WB
3:                    IF   ID   EX  MEM   WB
                                         ▲
                                    termina no ciclo 7
```

🛑 **PARE E PENSE:** 3 instruções, mas 7 ciclos. Por quê?

<br>

Olhe o desenho de novo, separando em duas fases:

```text
Ciclo:      C1   C2   C3   C4   C5   C6   C7
─────────────────────────────────────────────
1:          IF   ID   EX  MEM   WB
2:               IF   ID   EX  MEM   WB
3:                    IF   ID   EX  MEM   WB
            └────────────────┘  └────────┘
              ENCHIMENTO         REGIME
            a 1ª instrução      a partir daqui sai
            leva 5 ciclos       1 instrução POR CICLO
            para sair            (as 2 restantes)

            5 ciclos       +     2 ciclos      =  7 ciclos
            (para a 1ª)          (para as outras 2)
```

⭐ **A fórmula sai daí:**

```text
ciclos = 5 (a primeira instrução)  +  (N − 1) (as demais, 1 por ciclo)

      = E + (N − 1)        ou, na forma mais comum:

      = N + (E − 1)        ← MESMA COISA, só reorganizada
        │      │
        │      └─ o "custo de enchimento" do pipeline
        └──────── uma instrução por ciclo, no regime
```

📌 **A fórmula final:**

```text
   ┌──────────────────────────────────────┐
   │  T_pipe = [ N + (E − 1) ] × Tc_pipe  │
   └──────────────────────────────────────┘
        N  = número de instruções
        E  = número de estágios
        Tc = o MAIOR estágio
```

🔎 **Aplicando ao exemplo do quadro:**

```text
N = 200, E = 5, Tc_pipe = 200 ps

ciclos  = 200 + (5 − 1) = 204
T_pipe  = 204 × 200 = 40.800 ps ✅
```

## Passo 3 — speedup

```text
   ┌────────────────────────────┐
   │  Speedup = T_antes / T_depois │
   └────────────────────────────┘
```

```text
Speedup = 160.000 / 40.800 = 3,92 ✅
```

🛑 **PARE E PENSE:** por que 3,92 e não 4,00 exatos?

<br>

**Por causa do enchimento** — aqueles 4 ciclos extras (`E − 1`) que o pipeline gasta antes de entrar em regime. Eles são um **imposto fixo** que você paga uma vez.

```text
    ┌─────────────────────────────────────────────────┐
    │  SPEEDUP TEÓRICO (ideal)  =  E  = 5?            │
    │                                                 │
    │  NÃO! Nesse caso o teórico é 4, não 5.          │
    └─────────────────────────────────────────────────┘
```

💡 **Por que o teórico é 4?** Porque o teórico é a razão entre os **clocks**:

```text
Speedup teórico = Tc_mono / Tc_pipe = 800 / 200 = 4,00
```

⭐ **O speedup teórico só é igual a `E` quando os estágios são todos iguais.** Aqui eles não são (200/100/200/200/100), então o teórico é 4, não 5.

```text
   ESTÁGIOS IGUAIS (ex: 5 × 200 ps)     ESTÁGIOS DIFERENTES (200/100/200/200/100)
   Tc_mono = 1000                       Tc_mono = 800
   Tc_pipe =  200                       Tc_pipe = 200
   teórico = 5 = E ✅                   teórico = 4 ≠ E ⚠️
```

## Passo 4 — o desenho que explica o speedup

```text
      MONOCICLO (200 instruções × 800 ps)
      ████████████████████████████████████████  160.000 ps


      PIPELINE (204 ciclos × 200 ps)
      ██████████  40.800 ps
      ▲▲
      ││
      └┴─ o "imposto" de enchimento: 4 ciclos = 800 ps
           (0,5% do total — quase nada quando N é grande)
```

⭐ **Quanto MAIOR o N, mais o speedup real se aproxima do teórico:**

| N | ciclos | T_pipe | Speedup | Quão perto de 4,00 |
| --- | --- | --- | --- | --- |
| 1 | 5 | 1.000 | **0,80** | pior que o monociclo! |
| 5 | 9 | 1.800 | 2,22 | longe |
| 50 | 54 | 10.800 | 3,70 | perto |
| 200 | 204 | 40.800 | 3,92 | bem perto |
| 10.000 | 10.004 | 2.000.800 | 3,998 | praticamente 4 |

💡 **Em português claro:** o pipeline é como aquecer um forno. A primeira pizza demora porque você espera o forno aquecer. Da segunda em diante sai rápido. **Se você for assar uma pizza só, nem vale a pena ligar o forno.**

## Passo 5 — as três contas prontas para copiar

Todas as contas do seu curso saem deste roteiro de 4 linhas:

```text
① Tc_mono  = a SOMA dos estágios (ou o que o enunciado disser)
② Tc_pipe  = o MAIOR estágio
③ T_mono   = N × Tc_mono
④ T_pipe   = [N + (E−1)] × Tc_pipe
⑤ Speedup  = T_mono / T_pipe
```

🧮 **As três provas do seu professor, resolvidas com esse roteiro:**

```text
╔═══════════════════════════════════════════════════════════════════╗
║ CASO 1 — N=200, 5 estágios de 200 ps, monociclo 800 ps            ║
║   T_mono = 200 × 800           = 160.000 ps                       ║
║   T_pipe = (200+4) × 200       =  40.800 ps                       ║
║   Speedup = 160.000 / 40.800   = 3,92   (teórico 800/200 = 4,00)  ║
╠═══════════════════════════════════════════════════════════════════╣
║ CASO 2 — N=50, 5 estágios de 150 ps, monociclo 900 ps             ║
║   T_mono = 50 × 900            = 45.000 ps                        ║
║   T_pipe = (50+4) × 150        =  8.100 ps                        ║
║   Speedup = 45.000 / 8.100     = 5,55   (teórico 900/150 = 6,00)  ║
╠═══════════════════════════════════════════════════════════════════╣
║ CASO 3 — N=100, 5 estágios de 200 ps, monociclo 800 ps            ║
║   T_mono = 100 × 800           = 80.000 ps                        ║
║   T_pipe = (100+4) × 200       = 20.800 ps                        ║
║   Speedup = 80.000 / 20.800    = 3,85   (teórico 800/200 = 4,00)  ║
╚═══════════════════════════════════════════════════════════════════╝
```

## Passo 6 — a pegadinha do "mexer num estágio"

Uma questão clássica: *"o que acontece se a ULA ficar 25% mais rápida / mais lenta?"*

🛑 **PARE E PENSE** antes de olhar a tabela: acelerar a ULA **sempre** melhora o desempenho?

<br>

```text
Estágios originais:  IF=200  ID=100  EX=200  MEM=200  WB=100
```

| Cenário | EX | Tc_mono (soma) | Tc_pipe (maior) | Speedup |
| --- | --- | --- | --- | --- |
| original | 200 | 800 | **200** (IF/EX/MEM empatam) | **4,00** |
| ULA **−25%** = 150 ps | 150 | 750 | **200** (IF/MEM continuam 200) | **3,75** ⬇️ |
| ULA **+25%** = 250 ps | 250 | 850 | **250** (EX virou o gargalo) | **3,40** ⬇️ |

⭐ **O resultado que parece absurdo mas é correto:**

> **Acelerar a ULA PIOROU o speedup** (4,00 → 3,75).

💡 **Por quê?** Porque o `Tc_pipe` **não mudou** — continuou 200 ps, ditado por IF e MEM. Mas o `Tc_mono` **caiu** (800 → 750). Ou seja: o monociclo melhorou e o pipeline ficou igual, então a **vantagem relativa** do pipeline diminuiu.

```text
        Tc_mono         Tc_pipe        Speedup
        ───────         ───────        ───────
orig:     800      ÷      200     =     4,00
−25%:     750 ⬇️    ÷      200 =      =     3,75 ⬇️
                          ▲
                   NÃO MUDOU! IF e MEM
                   continuam sendo 200 ps
```

⚠️ **A lição:** em pipeline, **só adianta acelerar o estágio que é o gargalo**. Acelerar qualquer outro é dinheiro jogado fora (e, na métrica de *speedup*, chega a parecer prejuízo).

---

# AULA 5 — Quando o pipeline quebra: hazards

Até agora desenhamos o pipeline num mundo perfeito. Na vida real ele **engasga**. Os engasgos se chamam **hazards** (ou *conflitos*).

📌 **Definição:** *hazard* é uma situação em que a próxima instrução **não pode ser executada no ciclo seguinte**.

💡 **A analogia da lavanderia:** você montou o esquema perfeito, mas:
- **hazard estrutural** → você só tem **uma** máquina que lava *e* seca. Duas roupas querem usá-la no mesmo minuto.
- **hazard de dados** → o cesto 2 tem a camisa que precisa ser passada **junto** com a calça do cesto 1. Ele tem que esperar.
- **hazard de controle** → você não sabe se o cesto 3 vai para "roupa branca" ou "roupa colorida" até abrir. Você chuta e, se errar, refaz.

```text
                    OS TRÊS HAZARDS
                          │
        ┌─────────────────┼─────────────────┐
        ▼                 ▼                 ▼
  ESTRUTURAL          DE DADOS          DE CONTROLE
  (recurso)           (dependência)     (desvio)
        │                 │                 │
  duas instruções    uma precisa do    não se sabe qual
  querem o MESMO     RESULTADO da      a PRÓXIMA instrução
  hardware           anterior          até o beq decidir
        │                 │                 │
  SOLUÇÃO:          SOLUÇÃO:           SOLUÇÃO:
  duplicar o        FORWARDING         PREVISÃO DE
  hardware          (adiantamento)     DESVIOS
  (Harvard!)             │                  │
                    se não der:        se errar:
                    STALL              descartar
```

## 5.1 — Hazard ESTRUTURAL

**O problema:** duas instruções precisam do **mesmo pedaço de hardware** no mesmo ciclo.

🔎 **O caso clássico — uma única memória:**

```text
Ciclo:      C1   C2   C3   C4   C5   C6
────────────────────────────────────────
lw          IF   ID   EX  [MEM] WB       ← quer LER DADOS da memória
add              IF   ID   EX  MEM  WB
sub                   IF   ID   EX  MEM
or                        [IF]  ID  EX   ← quer BUSCAR INSTRUÇÃO da memória
                           ▲
                     ┌─────┴─────┐
                     │  CONFLITO │  ambos no ciclo C4,
                     │     💥    │  e só existe UMA memória
                     └───────────┘
```

⭐ **A solução: separar as memórias. Isso é exatamente a arquitetura HARVARD.**

```text
VON NEUMANN                          HARVARD
(uma memória só)                     (duas memórias separadas)

   ┌─────────────┐                   ┌──────────┐   ┌──────────┐
   │  MEMÓRIA    │                   │  MEM DE  │   │  MEM DE  │
   │ instruções  │                   │  INSTR.  │   │  DADOS   │
   │  + dados    │                   └────┬─────┘   └────┬─────┘
   └──────┬──────┘                        │              │
          │  ← UM barramento              │              │  ← DOIS
          ▼                               ▼              ▼
   ┌─────────────┐                   ┌─────────────────────────┐
   │     CPU     │                   │          CPU            │
   └─────────────┘                   └─────────────────────────┘

   ❌ IF e MEM colidem              ✅ IF e MEM ao mesmo tempo
      (hazard estrutural)              SEM conflito
```

⭐ **Por isso todo processador com pipeline usa Harvard (ao menos nas caches L1).** Você agora sabe **o motivo** — não é capricho, é para eliminar o hazard estrutural.

## 5.2 — Hazard de DADOS

**O problema:** uma instrução precisa de um resultado que **ainda não foi gravado**.

🔎 **O exemplo mínimo:**

```asm
add x1, x2, x3      # calcula x1
sub x4, x1, x5      # PRECISA de x1
```

Vamos desenhar e ver **exatamente** onde está o problema:

```text
Ciclo:      C1   C2   C3   C4   C5   C6
──────────────────────────────────────────
add x1..    IF   ID   EX  MEM  [WB]
                                 ▲
                          x1 é GRAVADO aqui (C5)

sub ..x1..       IF  [ID]  EX  MEM   WB
                      ▲
               x1 é LIDO aqui (C3)
```

```text
             ┌───────────────────────────────────────┐
             │  O sub quer LER x1 no ciclo 3         │
             │  O add só GRAVA x1 no ciclo 5         │
             │                                       │
             │      LÊ ANTES DE ESCREVER  💥         │
             │  → o sub leria o valor VELHO de x1    │
             └───────────────────────────────────────┘
```

💡 **A analogia:** você pede ao colega o relatório que ele **ainda está digitando**. Se você simplesmente abrir a pasta agora, vai pegar a versão de ontem.

### A solução ingênua: STALL (bolha)

Parar o pipeline até o dado estar pronto.

```text
Ciclo:      C1   C2   C3   C4   C5   C6   C7   C8
──────────────────────────────────────────────────
add x1..    IF   ID   EX  MEM   WB
sub ..x1..       IF  ███  ███  ███   ID   EX  MEM
                      ▲▲▲▲▲▲▲▲▲▲
                     3 BOLHAS (stalls)
                     3 ciclos perdidos 😩
```

⚠️ **Custo: 3 ciclos perdidos por dependência.** Como quase toda instrução depende da anterior, isso **destruiria** o ganho do pipeline.

🛑 **PARE E PENSE:** o valor de `x1` já existe em algum lugar antes do ciclo 5?

<br>

**SIM!** E essa é a sacada da próxima aula.

## 5.3 — Hazard de CONTROLE

**O problema:** depois de um `beq`, qual é a próxima instrução?

```asm
beq x1, x2, PULA    # se x1 == x2, salta para PULA
add x3, x4, x5      # esta executa OU não?
sub x6, x7, x8      # esta também?
PULA:
or  x9, x10, x11
```

🛑 **PARE E PENSE:** no ciclo em que o `beq` está no IF, qual instrução o processador deve buscar em seguida?

<br>

**Ele não sabe.** O resultado da comparação só sai no **EX**.

```text
Ciclo:      C1   C2   C3   C4   C5
───────────────────────────────────
beq         IF   ID  [EX] MEM   WB
                      ▲
              só AQUI se sabe se desvia!

 ???             IF    ?              ← mas o IF da próxima
                 ▲                      tem que acontecer em C2!
                 │
        ┌────────┴──────────────────────┐
        │  Preciso decidir em C2 algo   │
        │  que só vou saber em C3   💥  │
        └───────────────────────────────┘
```

💡 **A analogia:** você está dirigindo e chegando numa bifurcação, mas a placa só aparece **depois** da curva. Você tem que escolher um lado **antes** de saber qual é o certo. Se errar, volta.

**As duas saídas** (detalhadas na Aula 8):
1. **Parar** e esperar → perde ciclos sempre.
2. **Chutar** e continuar → acerta na maioria das vezes; quando erra, **descarta** o que entrou errado.

## 5.4 — Tabela-resumo dos três hazards

| | **Estrutural** | **De dados** | **De controle** |
| --- | --- | --- | --- |
| **Causa** | mesmo hardware disputado | resultado ainda não pronto | não se sabe o próximo PC |
| **Exemplo** | `lw` em MEM + `or` em IF | `add x1` → `sub ..x1..` | `beq` |
| **Solução principal** | duplicar hardware (**Harvard**) | **forwarding** | **previsão de desvios** |
| **Quando a solução não basta** | — | `lw` → uso imediato (**1 stall**) | previsão errada (**descarte**) |

---

# AULA 6 — Forwarding: o atalho

## A pergunta que resolve tudo

```asm
add x1, x2, x3      # x1 = x2 + x3
sub x4, x1, x5      # precisa de x1
```

🛑 **PARE E PENSE:** em que momento o **valor** de `x1` passa a existir dentro do processador?

<br>

```text
Ciclo:      C1   C2   C3   C4   C5
──────────────────────────────────────
add         IF   ID  [EX] MEM   WB
                      ▲          ▲
                      │          └─ aqui ele é GRAVADO no registrador
                      │
             ⭐ MAS O VALOR JÁ EXISTE AQUI!
                A ULA terminou de somar no fim do EX.
                O resultado está parado no registrador EX/MEM.
```

⭐ **A ideia do forwarding:** *"se o valor já existe, por que esperar que ele dê a volta inteira até o banco de registradores? Puxa ele direto por um fio."*

📌 **Nome formal:** *forwarding* = **adiantamento** ou *bypassing* (desvio de caminho).

## O desenho do atalho

```text
                                    ┌──────────────────────────┐
                                    │  O FIO DO FORWARDING     │
                                    │  ◄─────────────────────  │
                                    ▼                          │
       ┌────┐    ┌────┐    ┌─────────────┐    ┌─────┐    ┌────┐│
       │ IF │───►│ ID │───►│     EX      │───►│ MEM │───►│ WB ││
       └────┘    └────┘    │   ┌─────┐   │    └──┬──┘    └──┬─┘│
                           │   │ ULA │   │       │          │  │
                           │   └──┬──┘   │       │          │  │
                           └──────┼──────┘       │          │  │
                                  │              │          │  │
                             ┌────▼───┐      ┌───▼──┐       │  │
                             │ EX/MEM │──────┴──────┴───────┘  │
                             └────────┘                        │
                                  └────────────────────────────┘
                                   o valor volta para a entrada
                                   da ULA no ciclo seguinte
```

## Os dois caminhos de forwarding (isso cai na prova)

### Caminho 1 — `EX/MEM → EX` (dependência de distância 1)

Quando as instruções são **vizinhas**:

```asm
add x1, x2, x3
sub x4, x1, x5      ← imediatamente depois
```

```text
Ciclo:      C1   C2   C3   C4   C5   C6
──────────────────────────────────────────
add         IF   ID   EX  MEM   WB
                       │
                       │  ⚡ EX/MEM → EX
                       └──────┐
                              ▼
sub              IF   ID    [EX]  MEM   WB
                             ▲
                    o sub PRECISA de x1 aqui (C4)
                    e o add TERMINOU o EX em C3 ✅

              → ZERO STALLS. O pipeline não para. 🎉
```

**Origem:** registrador **EX/MEM** &nbsp;&nbsp;|&nbsp;&nbsp; **Destino:** entrada da ULA no estágio **EX**

### Caminho 2 — `MEM/WB → EX` (dependência de distância 2)

Quando há **uma instrução no meio**:

```asm
add x1, x2, x3
or  x7, x8, x9      ← não usa x1
sub x4, x1, x5      ← usa x1, duas depois
```

```text
Ciclo:      C1   C2   C3   C4   C5   C6   C7
───────────────────────────────────────────────
add         IF   ID   EX  MEM   WB
                            │
                            │  ⚡ MEM/WB → EX
or               IF   ID   EX  MEM   WB
                            │
                            └────┐
                                 ▼
sub                   IF   ID  [EX]  MEM   WB
                                ▲
                       o sub precisa de x1 em C5
                       e o valor está no MEM/WB ✅

              → ZERO STALLS também. 🎉
```

**Origem:** registrador **MEM/WB** &nbsp;&nbsp;|&nbsp;&nbsp; **Destino:** entrada da ULA no estágio **EX**

### A tabela para decorar (agora entendendo)

| Distância | Código | Forwarding | Stalls |
| --- | --- | --- | --- |
| **1** (vizinhas) | `add x1..` → `sub ..x1..` | **EX/MEM → EX** | **0** ✅ |
| **2** (uma no meio) | `add x1..` → `or` → `sub ..x1..` | **MEM/WB → EX** | **0** ✅ |
| **3** ou mais | `add x1..` → 2 instr. → `sub ..x1..` | **nem precisa** (o WB já aconteceu) | **0** ✅ |

⭐ **Conclusão poderosa:** com forwarding, **todo hazard de dados entre instruções de ULA é resolvido sem perder nenhum ciclo.**

🛑 **PARE E PENSE:** então o forwarding resolve **todos** os hazards de dados?

<br>

**Não.** Existe **um** caso que ele não resolve. É a Aula 7.

## 6.1 — Por que os nomes são "EX/MEM" e "MEM/WB"?

💡 Porque são os **nomes dos registradores de pipeline** que você viu na Aula 3:

```text
   ┌────┐  ┌─────┐  ┌────┐  ┌─────┐  ┌────┐  ┌──────┐  ┌─────┐  ┌──────┐  ┌────┐
   │ IF │─►│IF/ID│─►│ ID │─►│ID/EX│─►│ EX │─►│EX/MEM│─►│ MEM │─►│MEM/WB│─►│ WB │
   └────┘  └─────┘  └────┘  └─────┘  └────┘  └──────┘  └─────┘  └──────┘  └────┘
                                                ▲                   ▲
                                          ┌─────┘                   │
                                          │     ┌───────────────────┘
                                          │     │
                                      as DUAS fontes possíveis
                                      de forwarding
```

⭐ **Por isso as origens são sempre `EX/MEM` e `MEM/WB`, e o destino é sempre `EX`.** Não é arbitrário: são os **únicos dois lugares** onde o resultado já existe antes do WB, e o **único lugar** onde ele é necessário é na entrada da ULA.

---

# AULA 7 — Load-use: o caso que não tem jeito

## O único hazard que o forwarding não resolve

```asm
lw  x1, 0(x2)       # LÊ x1 da memória
sub x4, x1, x5      # usa x1 imediatamente
```

🛑 **PARE E PENSE:** no `lw`, em que estágio o valor de `x1` passa a existir?

<br>

**No MEM** — porque o dado vem **da memória**, não da ULA.

```text
Ciclo:      C1   C2   C3   C4   C5   C6
──────────────────────────────────────────
lw x1       IF   ID   EX  [MEM]  WB
                            ▲
                  o valor de x1 só EXISTE no FIM do MEM (C4)

sub ..x1..       IF   ID  [EX]  MEM   WB
                           ▲
                  mas o sub PRECISA de x1 no INÍCIO do EX (C3)

        ┌──────────────────────────────────────────────┐
        │   O valor nasce em C4.                       │
        │   É necessário em C3.                        │
        │                                              │
        │   ⏰ ISSO EXIGIRIA VOLTAR NO TEMPO. 💥       │
        └──────────────────────────────────────────────┘
```

⭐ **O forwarding pode encurtar o caminho, mas não pode viajar no tempo.**

💡 **A analogia:** o colega pode te **mostrar a tela** em vez de salvar o arquivo (é o forwarding — atalho de caminho). Mas ele não pode te mostrar **o que ainda não digitou** (é o load-use — atalho de tempo, impossível).

## A solução: 1 stall obrigatório + forwarding

```text
Ciclo:      C1   C2   C3   C4   C5   C6   C7
───────────────────────────────────────────────
lw x1       IF   ID   EX  MEM   WB
                            │
                            │ ⚡ MEM/WB → EX
                            └────┐
                                 ▼
sub ..x1..       IF   ID  ████  [EX]  MEM   WB
                           ▲▲▲▲
                        1 BOLHA
                        (1 stall)

        agora o EX do sub caiu em C5,
        e o valor está pronto desde o fim de C4 ✅
```

📌 **O nome formal: LOAD-USE HAZARD** (ou *load-use data hazard*).

⭐ **A regra para a prova:**

```text
┌────────────────────────────────────────────────────────────┐
│  lw seguido IMEDIATAMENTE por quem usa o registrador       │
│  carregado  =  1 STALL OBRIGATÓRIO                         │
│                                                            │
│  Nem o forwarding salva. É o ÚNICO caso assim.             │
└────────────────────────────────────────────────────────────┘
```

## Como o compilador escapa: reordenar

🛑 **PARE E PENSE:** este código tem load-use hazard?

```asm
lw  x1, 0(x2)
lw  x3, 8(x2)
add x4, x1, x3
```

<br>

```text
Ciclo:      C1   C2   C3   C4   C5   C6   C7
───────────────────────────────────────────────
lw x1       IF   ID   EX  MEM   WB
lw x3            IF   ID   EX  MEM   WB
                                 │
add x4,x1,x3          IF   ID  [EX]  MEM   WB
                                ▲
              precisa de x1 (pronto desde C4 ✅)
                    e de x3 (pronto no fim de C5)
                    ────────────────────────────
                    O add está no EX em C5.
                    x3 sai no FIM de C5.  💥 AINDA DÁ CONFLITO
```

⚠️ Sim, há **1 stall** — por causa do **segundo** `lw`, que é o vizinho imediato do `add`.

⭐ **É por isso que compiladores reordenam instruções:** eles colocam alguma instrução independente entre o `lw` e o uso, transformando distância 1 em distância 2 — e aí o forwarding `MEM/WB → EX` resolve com **zero stalls**.

```text
ANTES (1 stall)               DEPOIS (0 stalls)
─────────────────             ─────────────────
lw  x1, 0(x2)                 lw  x1, 0(x2)
add x4, x1, x5     ───►       or  x7, x8, x9   ← instrução independente
or  x7, x8, x9                add x4, x1, x5      "enfiada" no meio
```

## Contando stalls num trecho — o método

Faça **sempre** nesta ordem:

```text
① Para cada instrução, anote qual registrador ela ESCREVE (rd)
② Para cada instrução, anote quais registradores ela LÊ (rs1, rs2)
③ Procure: alguém lê um registrador escrito por uma instrução anterior?
④ Se sim, meça a DISTÂNCIA:
     · distância 1 e a anterior é de ULA  → forwarding EX/MEM, 0 stall
     · distância 2 e a anterior é de ULA  → forwarding MEM/WB, 0 stall
     · distância 1 e a anterior é lw      → 1 STALL ⚠️
     · distância ≥ 2 e a anterior é lw    → forwarding MEM/WB, 0 stall
     · distância ≥ 3                       → nada, o WB já passou
⑤ ciclos = N + (E − 1) + total de stalls
```

🔎 **Exemplo completo:**

```asm
1: lw   x1, 0(x10)
2: add  x2, x1, x3      ← lê x1 (escrito em 1, distância 1, e 1 é lw)
3: sub  x4, x2, x5      ← lê x2 (escrito em 2, distância 1, e 2 é ULA)
4: sw   x4, 8(x10)      ← lê x4 (escrito em 3, distância 1, e 3 é ULA)
```

```text
① e ②
   instr  escreve  lê
   1 lw     x1     x10
   2 add    x2     x1, x3
   3 sub    x4     x2, x5
   4 sw     —      x4, x10

③ e ④
   1→2: x1, dist 1, 1 é LW   →  ⚠️ 1 STALL
   2→3: x2, dist 1, 2 é ULA  →  forwarding EX/MEM, 0 stall
   3→4: x4, dist 1, 3 é ULA  →  forwarding EX/MEM, 0 stall

⑤ ciclos = 4 + (5−1) + 1 = 9 ciclos
```

```text
Ciclo:      C1   C2   C3   C4   C5   C6   C7   C8   C9
─────────────────────────────────────────────────────────
1: lw       IF   ID   EX  MEM   WB
2: add           IF   ID  ███   EX  MEM   WB
3: sub                IF  ███   ID   EX  MEM   WB
4: sw                      ▲    IF   ID   EX  MEM   WB
                           │
                    a bolha empurra
                    TODO MUNDO para frente
```

⚠️ **Detalhe importante:** o stall **atrasa todas as instruções seguintes**, não só a que dependia. A bolha é uma "rolha" no tubo.

---

# AULA 8 — Desvios e o problema de adivinhar o futuro

## O problema, desenhado

```asm
beq x1, x2, PULA
add x3, x4, x5      ← busco esta?
sub x6, x7, x8      ← ou vou direto para PULA?
PULA:
or  x9, x10, x11
```

```text
Ciclo:      C1   C2   C3
─────────────────────────
beq         IF   ID   EX  ← só aqui a comparação termina
                 ▲
                 │
        no ciclo C2 o IF já tem que estar
        buscando a PRÓXIMA instrução.
        Mas qual?  🤷
```

💡 **A analogia do GPS:** você está a 200 m de uma bifurcação e o GPS só vai falar quando você chegar nela. Se você **parar** o carro e esperar, perde tempo **sempre**. Se **chutar** um lado e continuar acelerando, você acerta a maior parte das vezes; nas outras, dá a volta.

## As três estratégias

```text
                    O QUE FAZER COM O beq?
                            │
          ┌─────────────────┼─────────────────┐
          ▼                 ▼                 ▼
    ① PARAR            ② PREVISÃO        ③ PREVISÃO
      e esperar           ESTÁTICA          DINÂMICA
          │                 │                 │
    perde ciclos       chuta sempre       APRENDE com
    SEMPRE             a mesma coisa      o histórico
          │                 │                 │
      ❌ ruim           razoável          ⭐ o que se usa
                                            hoje (>90% acerto)
```

### ① Parar (stall)

```text
beq         IF   ID   EX  MEM   WB
próxima          ███  ███   IF   ID  ...
                  ▲▲▲▲▲▲
             perde ciclos SEMPRE,
             mesmo quando o desvio não é tomado
```

❌ **Descartado na prática** — é o pior dos mundos.

### ② Previsão estática

📌 **Definição:** a decisão é **fixa**, definida em tempo de projeto ou de compilação. **Não muda durante a execução.**

```text
REGRA "NUNCA DESVIA" (predict not taken)
  → continua buscando as instruções em sequência

REGRA "SEMPRE DESVIA" (predict taken)
  → vai direto para o alvo do desvio
```

💡 **Qual funciona melhor?** Depende do tipo de desvio:

```text
   LOOP (desvio para TRÁS)              IF (desvio para FRENTE)
   ─────────────────────────            ───────────────────────
   for (i=0; i<1000; i++) {             if (erro) {
       ...                                  tratar();
   }   ← desvia 999 vezes,              }   ← geralmente NÃO desvia
       não desvia 1

   → "SEMPRE DESVIA" acerta 99,9%       → "NUNCA DESVIA" acerta muito
```

⭐ **A heurística clássica usada em previsão estática:**

```text
┌─────────────────────────────────────────────────────────┐
│  desvio para TRÁS  → prevê TOMADO    (é loop)           │
│  desvio para FRENTE → prevê NÃO TOMADO (é if)           │
└─────────────────────────────────────────────────────────┘
```

### ③ Previsão dinâmica

📌 **Definição:** a decisão é tomada **em tempo de execução**, com base no **histórico** daquele desvio específico.

💡 **A ideia:** o processador mantém uma tabelinha na memória — *"da última vez que passei por este `beq`, ele desviou?"* — e repete o comportamento.

```text
   TABELA DE HISTÓRICO DE DESVIOS (BHT)
   ┌────────────────────┬──────────────────┐
   │ endereço do desvio │ última decisão   │
   ├────────────────────┼──────────────────┤
   │      0x1004        │  DESVIOU ✅      │  ← então prevê DESVIAR de novo
   │      0x2010        │  não desviou ❌  │  ← então prevê NÃO desviar
   │      0x3044        │  DESVIOU ✅      │
   └────────────────────┴──────────────────┘
```

🔎 **Por que funciona tão bem?** Porque desvios são **extremamente repetitivos**. Num loop de 1000 iterações, o mesmo `beq` é executado 1000 vezes e se comporta igual em 999 delas.

```text
Loop com 1000 iterações, previsão dinâmica:

iteração    1: prevê "não desvia" (não sei ainda) → ERRA ❌  (aprende)
iteração  2-999: prevê "desvia"                    → ACERTA ✅✅✅
iteração  1000: prevê "desvia"                     → ERRA ❌  (o loop acabou)

Acerto: 998 / 1000 = 99,8% 🎉
```

⭐ **Preditores reais** usam contadores de 2 bits (para não mudar de opinião por causa de um único erro) e chegam a **mais de 90% de acerto** em código real.

## O custo de errar

```text
PREVI que NÃO desvia, mas DESVIOU:

Ciclo:      C1   C2   C3   C4   C5
─────────────────────────────────────
beq         IF   ID   EX  ← descobre em C3 que ERROU
add              IF   ID  ✖️ ← esta instrução era ERRADA
sub                   IF  ✖️ ← esta também
                          │
                    ┌─────▼────────────────────────┐
                    │  DESCARTAR (flush)           │
                    │  as instruções erradas       │
                    │  = 2 ciclos perdidos         │
                    └──────────────────────────────┘
or (o certo)               IF   ID   EX  ...
```

⭐ **A conta da penalidade:**

```text
penalidade de erro = número de estágios ANTES da decisão do desvio

Se a decisão sai no EX (3º estágio) → perde 2 ciclos por erro
Se a decisão sai no ID (2º estágio) → perde 1 ciclo por erro
```

⚠️ **Por isso processadores reais movem a comparação do desvio para o ID** — para reduzir a penalidade de 2 para 1.

## 8.1 — Tabela-resumo de previsão

| | **Estática** | **Dinâmica** |
| --- | --- | --- |
| **Quando decide** | em projeto/compilação | em execução |
| **Muda durante a execução?** | ❌ não | ✅ sim |
| **Usa histórico?** | ❌ não | ✅ sim |
| **Exemplos** | "sempre desvia", "nunca desvia", "trás=tomado" | tabela de histórico, contador de 2 bits |
| **Taxa de acerto típica** | 60–80% | **> 90%** |

⚠️ **A pegadinha clássica de prova:** *"previsão estática pode se adaptar ao comportamento do programa?"* → **NÃO.** Estática é **fixa**. Só a dinâmica se adapta.

---

# AULA 9 — RISC × CISC: por que a arquitetura importa

## A pergunta de projeto

Você está desenhando um processador. Vem a pergunta:

> *"As instruções devem ser POUCAS e SIMPLES, ou MUITAS e PODEROSAS?"*

```text
        CISC                                RISC
  Complex Instruction Set            Reduced Instruction Set

  "quero UMA instrução que            "quero instruções SIMPLES,
   faça muita coisa"                   mesmo que precise de várias"

  ┌────────────────────────┐          ┌────────────────────────┐
  │ MULT [end1], [end2]    │          │ lw  x1, 0(x10)         │
  │                        │          │ lw  x2, 0(x11)         │
  │ (busca 2 operandos da  │          │ mul x3, x1, x2         │
  │  memória, multiplica,  │          │ sw  x3, 0(x10)         │
  │  grava de volta)       │          └────────────────────────┘
  └────────────────────────┘
      1 instrução                          4 instruções
      MUITOS ciclos                        1 ciclo cada (pipeline!)
```

## A comparação item por item

| | **CISC** | **RISC** |
| --- | --- | --- |
| **Número de instruções** | centenas / milhares | poucas (~50 básicas) |
| **Tamanho da instrução** | ⚠️ **variável** (1 a 15 bytes) | ✅ **fixo** (4 bytes) |
| **Ciclos por instrução** | variável (1 a 100+) | ✅ ~1 (constante) |
| **Acesso à memória** | qualquer instrução pode | ✅ **só `lw` e `sw`** |
| **Registradores** | poucos (8 no x86) | ✅ muitos (32 no RISC-V) |
| **Complexidade do hardware** | ⚠️ alta (microcódigo) | ✅ baixa |
| **Complexidade do compilador** | baixa | ⚠️ alta (tem que otimizar) |
| **Serve para pipeline?** | ⚠️ **difícil** | ✅ **feito para isso** |
| **Exemplos** | x86, x86-64, IBM 370 | RISC-V, ARM, MIPS |

## ⭐ A razão nº 1: tamanho fixo × tamanho variável

Esta é **a** resposta para *"por que RISC é melhor para pipeline?"*

```text
RISC — instruções de 4 bytes, SEMPRE
┌──────┬──────┬──────┬──────┬──────┐
│  4B  │  4B  │  4B  │  4B  │  4B  │
└──────┴──────┴──────┴──────┴──────┘
   ✅ O estágio IF sabe EXATAMENTE onde cada
      instrução começa e termina.
      É só fazer PC = PC + 4.
   ✅ Pode buscar a próxima SEM ter decodificado a atual.
      → O PIPELINE FLUI.

CISC — instruções de tamanho variável
┌──┬──────┬───┬──────────┬─┬────────┐
│1B│  3B  │2B │    5B    │1│   4B   │
└──┴──────┴───┴──────────┴─┴────────┘
   ❌ Para saber onde a PRÓXIMA começa, você precisa
      DECODIFICAR a atual primeiro.
   ❌ O IF depende do ID.
      → O PIPELINE TRAVA.
```

💡 **Em português claro:** é a diferença entre uma fila de caixas **todas iguais** numa esteira (você sabe de cara onde uma acaba e a outra começa) e uma esteira com **caixas de tamanhos variados** (você tem que medir cada uma para saber onde começa a próxima).

## A razão nº 2: só `lw`/`sw` mexem na memória

🛑 **PARE E PENSE:** por que restringir o acesso à memória ajuda o pipeline?

<br>

```text
No RISC, apenas lw e sw usam o estágio MEM.
Então TODAS as instruções têm o mesmo formato de 5 estágios,
e nenhuma precisa de "dois acessos à memória" ou "mais um EX".

┌────────────────────────────────────────────────────────┐
│  RISC:  todas as instruções têm a MESMA "forma"        │
│         → cabem todas no mesmo pipeline                │
│                                                        │
│  CISC:  MULT [end1],[end2] precisaria de:              │
│         IF ID EX MEM EX MEM WB ← forma DIFERENTE!      │
│         → não cabe no pipeline de 5 estágios           │
└────────────────────────────────────────────────────────┘
```

## A conta RISC × CISC (já caiu na prova)

O enunciado típico dá o número de instruções e o CPI de cada arquitetura:

```text
                 CISC              RISC
   instruções:   ?                 ? (mais, porque cada uma faz menos)
   CPI:          ? (alto)          ? (baixo, ~1)
   clock:        ?                 ?
```

E você usa a fórmula da Aula 0:

```text
T = Ni × Ci × Tc
```

🧮 **O resultado da prova do seu professor:**

```text
T_cisc = 3.592.400 ns
T_risc = 2.868.040 ns

Speedup = 3.592.400 / 2.868.040 = 1,2526

Ganho percentual = (1,2526 − 1) × 100 = 25,26%
```

⚠️ **Duas formas de responder "quanto é o ganho" — não confunda:**

```text
"Quantas vezes mais rápido?"  →  1,25 vezes      (é o speedup)
"Qual o ganho percentual?"    →  25,26%          (é speedup − 1, em %)
```

## ⚠️ A grande pegadinha do RISC

🛑 **PARE E PENSE:** se RISC precisa de MAIS instruções para fazer a mesma coisa, como ele pode ser mais rápido?

<br>

```text
   Ni × Ci × Tc
   ▲    ▲    ▲
   │    │    └── RISC tem clock MAIOR (hardware simples = mais rápido) ✅
   │    └─────── RISC tem CPI ~1, CISC tem CPI alto               ✅✅
   └──────────── RISC tem MAIS instruções                          ❌

   O RISC PERDE num fator e GANHA nos outros dois — com folga.
```

⭐ **A resposta:** o RISC executa mais instruções, mas **cada uma custa muito menos**. É melhor dar 4 passos pequenos e rápidos que 1 passo grande e lento.

## 9.1 — E na prática hoje?

💡 **Detalhe que impressiona na prova discursiva:** os processadores x86 modernos (Intel/AMD) são **CISC por fora e RISC por dentro**. Eles têm um decodificador que quebra cada instrução CISC complexa em várias **micro-operações** (μops) simples, do tipo RISC, e essas μops é que entram no pipeline.

```text
   instrução x86 (CISC)
   ADD [mem], eax
          │
          ▼  DECODIFICADOR
   ┌──────────────────┐
   │ load  tmp, [mem] │  ← μops estilo RISC
   │ add   tmp, eax   │
   │ store [mem], tmp │
   └──────────────────┘
          │
          ▼
   pipeline RISC interno
```

⭐ **Ou seja: a filosofia RISC ganhou o debate.** O x86 sobrevive por **compatibilidade de software**, não por mérito arquitetural.

---

# AULA 10 — Assembly RISC-V do zero

Esta aula assume que você **nunca escreveu assembly**. Vamos do absoluto zero.

## 10.1 — Por que registradores?

```text
                    ONDE OS DADOS FICAM
   ┌──────────────────────────────────────────────────────┐
   │  REGISTRADORES   ~1 ciclo      32 deles, 8 bytes cada│  ⚡ rapidíssimo
   ├──────────────────────────────────────────────────────┤
   │  CACHE           ~10 ciclos    alguns MB             │
   ├──────────────────────────────────────────────────────┤
   │  MEMÓRIA RAM     ~200 ciclos   alguns GB             │  🐌 lento
   ├──────────────────────────────────────────────────────┤
   │  DISCO           ~1.000.000 ciclos   TB              │  🐢
   └──────────────────────────────────────────────────────┘
```

⭐ **A regra de ouro do assembly RISC-V:**

> **A ULA só trabalha com registradores.** Se um dado está na memória, você **primeiro traz para um registrador** (`lw`), depois calcula, depois **devolve** (`sw`).

💡 **A analogia da bancada:** a memória é o **depósito** e os registradores são a **bancada de trabalho**. Você não monta nada dentro do depósito. Você **busca as peças** (load), **monta na bancada** (ULA), e **guarda o produto** (store).

## 10.2 — Os 32 registradores

```text
   x0   ⭐ SEMPRE ZERO. Escrever nele não faz nada.
   x1   ra   endereço de retorno
   x2   sp   ponteiro de pilha
   x3   gp   ponteiro global
   x4   tp   ponteiro de thread
   x5-x7    t0-t2    temporários
   x8-x9    s0-s1    salvos
   x10-x17  a0-a7    argumentos / retorno
   x18-x27  s2-s11   salvos
   x28-x31  t3-t6    temporários
```

⭐ **O `x0` é a sacada mais elegante do RISC-V.** Com ele você **não precisa** de instruções extras:

```text
   quero fazer           escrevo                     porque
   ─────────────────     ─────────────────────       ─────────────────────
   x5 = 0                add x5, x0, x0              0 + 0 = 0
   x5 = x6  (copiar)     add x5, x6, x0              x6 + 0 = x6
   x5 = 42               addi x5, x0, 42             0 + 42 = 42
   nada (nop)            add x0, x0, x0              grava em x0 = descartado
```

## 10.3 — Aprendendo as instruções uma por uma

### Grupo 1 — aritmética entre registradores

```asm
add x5, x6, x7      # x5 = x6 + x7
sub x5, x6, x7      # x5 = x6 − x7
```

```text
   FORMA:   OP   destino, fonte1, fonte2
                    ▲
            O DESTINO VEM PRIMEIRO. Sempre.
```

⚠️ **O erro nº 1 de quem está começando:** escrever `add x6, x7, x5` querendo dizer `x5 = x6 + x7`. **O primeiro registrador é sempre o que RECEBE.**

### Grupo 2 — aritmética com constante

```asm
addi x5, x6, 100    # x5 = x6 + 100
addi x5, x6, -1     # x5 = x6 − 1   ⭐ é assim que se subtrai constante
```

🛑 **PARE E PENSE:** por que não existe `subi`?

<br>

**Porque `addi` com número negativo já faz isso.** O RISC-V **não desperdiça** uma instrução para algo que já é possível. É a filosofia RISC em ação.

### Grupo 3 — memória

```asm
lw x5, 8(x6)        # x5 = memória[x6 + 8]      LOAD  (memória → registrador)
sw x5, 8(x6)        # memória[x6 + 8] = x5      STORE (registrador → memória)
```

```text
   FORMA:   lw  reg, deslocamento(base)
                 │        │         │
                 │        │         └─ registrador com o ENDEREÇO
                 │        └─────────── constante somada ao endereço
                 └──────────────────── registrador de destino
```

⭐ **Desenho para nunca mais confundir a direção:**

```text
              lw  x5, 0(x10)                    sw  x5, 0(x10)

   ┌──────────┐            ┌────┐      ┌────┐            ┌──────────┐
   │ MEMÓRIA  │───────────►│ x5 │      │ x5 │───────────►│ MEMÓRIA  │
   └──────────┘   carrega  └────┘      └────┘   guarda   └──────────┘

        "Load = carrega PARA o registrador"
        "Store = armazena NA memória"
```

💡 **Truque de memorização:** em **`lw`** o registrador é o **destino** (como em `add`). Em **`sw`** o registrador é a **fonte** — é a única instrução em que o primeiro registrador **não** recebe nada.

### Tamanhos: `lw` × `ld`

```text
   lb / sb   →  1 byte   (8 bits)
   lh / sh   →  2 bytes  (half word, 16 bits)
   lw / sw   →  4 bytes  (word, 32 bits)      ← int
   ld / sd   →  8 bytes  (double word, 64 bits) ← long, ponteiro
```

⭐ **No RV64I** (o que vocês estudam), os registradores têm **64 bits = 8 bytes**. Então:
- para `int` (4 bytes) → use `lw` / `sw`
- para `long` e **ponteiros** (8 bytes) → use `ld` / `sd`

### Grupo 4 — desvios condicionais

```asm
beq x5, x6, RÓTULO  # Branch if EQual:        se x5 == x6, salta
bne x5, x6, RÓTULO  # Branch if Not Equal:    se x5 != x6, salta
blt x5, x6, RÓTULO  # Branch if Less Than:    se x5 <  x6, salta
bge x5, x6, RÓTULO  # Branch if Greater/Equal:se x5 >= x6, salta
```

```text
   ┌─────────────────────────────────────────────────────┐
   │  beq = ==        bne = !=                           │
   │  blt = <         bge = >=                           │
   │                                                     │
   │  ⚠️ NÃO EXISTEM  bgt (>)  nem  ble (<=)             │
   │     → você INVERTE a ordem dos registradores:       │
   │        "x5 > x6"   escreve-se   blt x6, x5, RÓTULO  │
   └─────────────────────────────────────────────────────┘
```

### Grupo 5 — salto incondicional

```asm
j RÓTULO            # jump: salta sempre, sem condição
```

## 10.4 — Traduzindo C para assembly, passo a passo

### Exemplo 1 — a expressão mais simples

```c
a = b + c;          // a→x5, b→x6, c→x7
```

```asm
add x5, x6, x7
```

### Exemplo 2 — expressão com temporário

```c
a = (b + c) - (d + e);   // a→x5, b→x6, c→x7, d→x28, e→x29
```

🛑 **PARE E PENSE:** você precisa de mais registradores. Quantos?

<br>

```asm
add x30, x6, x7      # x30 = b + c      ← temporário 1
add x31, x28, x29    # x31 = d + e      ← temporário 2
sub x5,  x30, x31    # a = x30 − x31
```

⭐ **A lição:** cada operação da expressão em C virou **uma instrução**, e os resultados intermediários precisam de **registradores temporários**. É exatamente o que o compilador faz.

### Exemplo 3 — acessando um vetor ⭐ (isso cai)

```c
A[3] = A[2] + 5;     // A é um vetor de long (8 bytes); x10 tem o endereço de A
```

🛑 **PARE E PENSE:** qual é o endereço de `A[2]`?

<br>

```text
   ⭐ A FÓRMULA MAIS IMPORTANTE DE VETORES EM ASSEMBLY:

        endereço de A[i]  =  endereço base  +  (i × tamanho do elemento)

   Para long (8 bytes):        A[2] → base + 16
   Para int  (4 bytes):        A[2] → base + 8
```

```text
   MEMÓRIA (elementos de 8 bytes)
   x10 →  ┌──────────┐  deslocamento 0    ← A[0]
          ├──────────┤  deslocamento 8    ← A[1]
          ├──────────┤  deslocamento 16   ← A[2]
          ├──────────┤  deslocamento 24   ← A[3]
          └──────────┘
```

```asm
ld   x5, 16(x10)     # x5 = A[2]        (2 × 8 = 16)
addi x5, x5, 5       # x5 = x5 + 5
sd   x5, 24(x10)     # A[3] = x5        (3 × 8 = 24)
```

⚠️ **A pegadinha:** o índice **NÃO** é o deslocamento. `A[2]` **não** é `2(x10)`, é `16(x10)`. Quem escreve `2(x10)` está acessando **o meio do A[0]** e corrompe tudo.

### Exemplo 4 — vetor com índice variável

```c
A[i] = A[i] + 1;     // i está em x11 (não é constante!)
```

🛑 **PARE E PENSE:** agora não dá para calcular `i × 8` na mão. Como fazer?

<br>

```asm
slli x12, x11, 3     # x12 = i × 8      (deslocar 3 bits à esquerda = ×8)
add  x12, x10, x12   # x12 = endereço de A[i]
ld   x5,  0(x12)     # x5 = A[i]
addi x5,  x5, 1      # x5 = x5 + 1
sd   x5,  0(x12)     # A[i] = x5
```

💡 **`slli x12, x11, 3` = shift left logical immediate.** Deslocar 3 bits à esquerda **multiplica por 2³ = 8**.

```text
   i = 5    em binário:  0000 0101       = 5
   slli 3 →              0010 1000       = 40  ✅  (5 × 8)
```

⭐ **Por que não usar `mul`?** Porque deslocar é **muito mais rápido** que multiplicar, e potências de 2 aparecem em todo acesso a vetor. Compiladores fazem isso automaticamente.

### Exemplo 5 — `if` ⭐

```c
if (a == b)
    c = c + 1;
d = d + 1;          // a→x5, b→x6, c→x7, d→x28
```

🛑 **PARE E PENSE:** a condição em C é `a == b`. Qual desvio você usa?

<br>

⚠️ **CUIDADO — a inversão é o erro nº 1 dos alunos:**

```text
   Em C você diz:              "SE a == b, FAÇA o corpo"
   Em assembly você diz:       "SE a != b, PULE o corpo"

                  ⭐ A CONDIÇÃO SE INVERTE!
```

```asm
        bne  x5, x6, FIM_IF    # se a != b, PULA o corpo
        addi x7, x7, 1         # c = c + 1     (corpo do if)
FIM_IF: addi x28, x28, 1       # d = d + 1     (depois do if)
```

```text
   ┌──────────────────┐
   │  a == b ?        │
   └────┬────────┬────┘
    sim │        │ não
        ▼        └────────┐
   ┌─────────┐            │
   │ c = c+1 │            │
   └────┬────┘            │
        │  ◄──────────────┘  ← FIM_IF
        ▼
   ┌─────────┐
   │ d = d+1 │
   └─────────┘
```

### Exemplo 6 — `if / else`

```c
if (a == b)  c = c + 1;
else         c = c - 1;
```

```asm
        bne  x5, x6, SENAO     # se a != b, vai para o else
        addi x7, x7, 1         # THEN: c = c + 1
        j    FIM               # ⭐ NÃO ESQUEÇA: pular o else!
SENAO:  addi x7, x7, -1        # ELSE: c = c − 1
FIM:
```

⚠️ **O erro clássico:** esquecer o `j FIM`. Sem ele, depois de executar o `then` o programa **cai dentro do else** e executa os dois.

### Exemplo 7 — `while` ⭐

```c
while (a != b)
    a = a + 1;          // a→x5, b→x6
```

```asm
LOOP:   beq  x5, x6, FIM     # ⭐ testa no INÍCIO, com a condição INVERTIDA
        addi x5, x5, 1       # corpo
        j    LOOP            # ⭐ volta para testar de novo
FIM:
```

```text
   ┌──── LOOP: ◄────────────────┐
   │        │                   │
   │        ▼                   │
   │   ┌──────────┐             │
   │   │ a == b ? │             │
   │   └──┬────┬──┘             │
   │  sim │    │ não            │
   │      │    ▼                │
   │      │ ┌─────────┐         │
   │      │ │ a = a+1 │         │
   │      │ └────┬────┘         │
   │      │      └──────────────┘
   │      ▼
   └─►  FIM:
```

⭐ **O molde de qualquer loop, para decorar:**

```text
LOOP:   <desvio com a condição INVERTIDA>  FIM
        <corpo do loop>
        j LOOP
FIM:
```

### Exemplo 8 — `for` somando um vetor ⭐⭐ (o mais provável de cair)

```c
soma = 0;
for (i = 0; i < n; i++)
    soma = soma + A[i];
// A→x10, n→x11, soma→x5, i→x6
```

Vamos montar **por partes**:

```asm
        # ① inicialização
        add  x5, x0, x0        # soma = 0
        add  x6, x0, x0        # i = 0

        # ② teste do loop (condição INVERTIDA: sai quando i >= n)
LOOP:   bge  x6, x11, FIM      # se i >= n, sai

        # ③ calcular o endereço de A[i]
        slli x7, x6, 3         # x7 = i × 8
        add  x7, x10, x7       # x7 = &A[i]

        # ④ corpo: soma = soma + A[i]
        ld   x28, 0(x7)        # x28 = A[i]
        add  x5, x5, x28       # soma = soma + A[i]

        # ⑤ incremento e volta
        addi x6, x6, 1         # i++
        j    LOOP

FIM:
```

⭐ **Este programa contém TODO o vocabulário da prova:** inicialização com `x0`, teste invertido com `bge`, `slli` para o índice, `add` para o endereço, `ld` para carregar, `addi` para incrementar, `j` para voltar. **Se você souber escrever este, sabe escrever qualquer um.**

## 10.5 — Simulando o código: o estado passo a passo

Vamos rodar o programa acima com `A = [10, 20, 30]` e `n = 3`, acompanhando os registradores.

```text
Início:  x10 = 1000 (endereço de A),  x11 = 3
         MEMÓRIA: [1000]=10  [1008]=20  [1016]=30
```

| Momento | x5 (soma) | x6 (i) | x7 (&A[i]) | x28 (A[i]) | O que aconteceu |
| --- | --- | --- | --- | --- | --- |
| início | 0 | 0 | — | — | inicializou |
| iter 1 | 0 | 0 | 1000 | 10 | carregou A[0] |
| iter 1 fim | **10** | 1 | 1000 | 10 | somou, i++ |
| iter 2 | 10 | 1 | 1008 | 20 | carregou A[1] |
| iter 2 fim | **30** | 2 | 1008 | 20 | somou, i++ |
| iter 3 | 30 | 2 | 1016 | 30 | carregou A[2] |
| iter 3 fim | **60** | 3 | 1016 | 30 | somou, i++ |
| teste | 60 | 3 | | | `bge 3, 3` → **sai** ✅ |

⭐ **Resultado: `x5 = 60` = 10 + 20 + 30.** ✅

💡 **Faça isso na prova.** Rodar a tabela com 2 ou 3 elementos é a maneira mais rápida de descobrir se seu código tem erro — principalmente erro de **um a mais / um a menos** no teste do loop.

## 10.6 — Detalhe que cai: little-endian

📌 O RISC-V é **little-endian**: o byte **menos significativo** fica no endereço **menor**.

```text
   Valor 0x12345678 (4 bytes) guardado no endereço 100:

   endereço:   100   101   102   103
              ┌────┬────┬────┬────┐
              │ 78 │ 56 │ 34 │ 12 │     ← LITTLE-endian (o "little" primeiro)
              └────┴────┴────┴────┘

   (Big-endian seria:  12  34  56  78)
```

💡 **Como lembrar:** *little*-endian = o dígito **menos** importante vem **primeiro**.

## 10.7 — Erros mais comuns (revise antes da prova)

```text
❌ add x6, x7, x5        querendo "x5 = x6 + x7"
✅ add x5, x6, x7        o DESTINO vem primeiro

❌ ld x5, 2(x10)         para acessar A[2] de long
✅ ld x5, 16(x10)        índice × tamanho!

❌ beq x5, x6, CORPO     para traduzir "if (a==b)"
✅ bne x5, x6, FIM       a condição se INVERTE

❌ esquecer o j FIM      no if/else
✅ sempre pular o else

❌ esquecer o j LOOP     no while
✅ senão o loop roda uma vez só

❌ bgt x5, x6, L         (não existe!)
✅ blt x6, x5, L         inverta a ordem dos registradores

❌ addi x5, x0, x6       (o terceiro campo do addi é CONSTANTE)
✅ add  x5, x0, x6       ou  addi x5, x6, 0
```

---

# AULA 11 — Os conceitos abstratos, finalmente concretos

A Parte 1 da matéria é a mais **abstrata**, e por isso a mais difícil de decorar. Agora que você conhece o pipeline, ela fica fácil — porque você tem exemplos concretos para pendurar em cada palavra.

## 11.1 — Arquitetura × Organização × Microarquitetura

💡 **A analogia do carro:**

```text
   ARQUITETURA          =  o MANUAL DO MOTORISTA
                           "tem volante, 3 pedais, câmbio"
                           É o que o motorista precisa saber para dirigir.

   ORGANIZAÇÃO          =  o DIAGRAMA DO MOTOR
                           "motor 1.0 turbo, 4 cilindros, injeção eletrônica"
                           É como o carro cumpre o que o manual promete.

   MICROARQUITETURA     =  o PROJETO DETALHADO DE CADA PEÇA
                           "a válvula tem 3 cm, o pistão é de liga X"
                           É a implementação concreta daquela organização.
```

⭐ **E a sacada:** dois carros podem ter **o mesmo manual do motorista** (volante, 3 pedais) e **motores completamente diferentes**. O motorista dirige os dois sem reaprender nada.

```text
   MESMA ARQUITETURA, ORGANIZAÇÕES DIFERENTES
   ┌─────────────────────────────────────────────────────┐
   │  Arquitetura x86-64                                 │
   │      ├── Intel Core i9      (uma organização)       │
   │      ├── AMD Ryzen 9        (outra organização)     │
   │      └── Intel Celeron      (outra ainda)           │
   │                                                     │
   │  ✅ O MESMO programa .exe roda nos três             │
   │  ✅ Por dentro são hardwares totalmente diferentes  │
   └─────────────────────────────────────────────────────┘
```

| | **Arquitetura (ISA)** | **Organização** | **Microarquitetura** |
| --- | --- | --- | --- |
| **Responde** | *o QUE o processador faz* | *COMO ele faz* | *com QUAIS circuitos* |
| **Quem vê** | o **programador** | o **projetista** | o **engenheiro de hardware** |
| **Inclui** | conjunto de instruções, registradores visíveis, modos de endereçamento, tipos de dados | barramentos, caches, unidades funcionais, **pipeline** | número de estágios, tamanho das caches, preditor de desvios |
| **Exemplo** | x86-64, RISC-V, ARMv8 | ter ou não ter pipeline | pipeline de 5 ou de 14 estágios |

⭐ **A frase-chave para a prova:**

> **O pipeline é uma decisão de ORGANIZAÇÃO/MICROARQUITETURA, não de arquitetura.** Ele é **invisível** para o programador — o mesmo código roda com ou sem pipeline. O programador só nota que ficou **mais rápido**.

⚠️ **Pegadinha frequente:** *"acrescentar pipeline muda a arquitetura?"* → **NÃO.** Muda a organização. A arquitetura (o conjunto de instruções) fica **idêntica**.

## 11.2 — Von Neumann × Harvard

Você já viu o desenho na Aula 5, quando falamos de hazard estrutural. Aqui é o conceito formal.

```text
   VON NEUMANN                          HARVARD
   ┌────────────────────┐               ┌──────────┐  ┌──────────┐
   │      MEMÓRIA       │               │  MEM DE  │  │  MEM DE  │
   │  instruções +      │               │ INSTRUÇ. │  │  DADOS   │
   │      dados         │               └────┬─────┘  └─────┬────┘
   │  (MESMO espaço)    │                    │              │
   └─────────┬──────────┘                    │              │
             │ UM barramento                 │ DOIS barramentos
             ▼                               ▼              ▼
   ┌────────────────────┐               ┌───────────────────────┐
   │        CPU         │               │         CPU           │
   └────────────────────┘               └───────────────────────┘

   ⚠️ IF e MEM competem              ✅ IF e MEM simultâneos
      → HAZARD ESTRUTURAL               → SEM hazard estrutural
   ✅ mais simples e flexível         ⚠️ mais hardware
   ✅ código pode ser tratado         ⚠️ código e dado são
      como dado (compiladores,           mundos separados
      código automodificável)
```

⭐ **O que acontece de verdade nos processadores modernos:** eles são **híbridos**.

```text
   ┌──────────────────────────────────────────────────────┐
   │   MEMÓRIA PRINCIPAL (RAM)     → VON NEUMANN          │
   │   instruções e dados juntos, um espaço de endereços   │
   └───────────────────────┬──────────────────────────────┘
                           │
              ┌────────────┴────────────┐
              ▼                         ▼
       ┌─────────────┐          ┌─────────────┐
       │ CACHE L1-I  │          │ CACHE L1-D  │   → HARVARD
       │ (instruções)│          │   (dados)   │      caches SEPARADAS
       └─────────────┘          └─────────────┘
              │                         │
              └────────────┬────────────┘
                           ▼
                      ┌─────────┐
                      │   CPU   │
                      └─────────┘
```

💡 **Por quê?** Porque assim você tem **as duas vantagens**: a flexibilidade de Von Neumann na memória principal, e a ausência de hazard estrutural de Harvard exatamente onde o pipeline precisa (nas caches L1, que é de onde o IF e o MEM realmente leem).

## 11.3 — Throughput × Latência (a confusão mais comum)

Estes dois conceitos são **a chave** para entender por que o pipeline "funciona". E são constantemente trocados.

```text
   LATÊNCIA                            THROUGHPUT (VAZÃO)
   "quanto tempo UMA tarefa leva"       "quantas tarefas por unidade de tempo"

   mede TEMPO POR TAREFA                mede TAREFAS POR TEMPO
   (ps, ns, segundos)                   (instruções/segundo, MIPS, cestos/hora)

   quanto MENOR, melhor                 quanto MAIOR, melhor
```

💡 **A analogia definitiva — a autoestrada:**

```text
   LATÊNCIA  = quanto tempo VOCÊ leva para ir de casa ao trabalho
   THROUGHPUT = quantos CARROS passam pelo pedágio por hora

   ┌────────────────────────────────────────────────────────────┐
   │  Acrescentar uma FAIXA na estrada:                         │
   │    · a sua viagem continua durando o mesmo  (latência =)   │
   │    · passam MAIS carros por hora        (throughput ⬆️)     │
   │                                                            │
   │  AUMENTAR O LIMITE DE VELOCIDADE:                          │
   │    · a sua viagem fica mais curta        (latência ⬇️)      │
   │    · e também passam mais carros      (throughput ⬆️)       │
   └────────────────────────────────────────────────────────────┘
```

⭐ **A frase mais importante de toda a Aula:**

> **O PIPELINE É UMA FAIXA A MAIS, NÃO UM LIMITE DE VELOCIDADE MAIOR.**
> Ele aumenta o **throughput** sem melhorar a **latência** (e pode até piorá-la um pouco).

🔎 **Comprovando com números** (do exemplo da Aula 4):

```text
                       MONOCICLO        PIPELINE
   LATÊNCIA            800 ps           1000 ps   ⬆️ PIOROU 25%
   (uma instrução)      (1×800)          (5×200)

   THROUGHPUT          1,25 G instr/s   5 G instr/s  ⬆️ MELHOROU 4×
   (em regime)          (1/800ps)        (1/200ps)
```

⚠️ **A pegadinha literal do slide:** *"a latência não se altera, ou até aumenta"*. Se a prova perguntar *"o pipeline reduz o tempo de execução de uma instrução?"* → **NÃO.** Ele reduz o tempo do **programa**, não o de uma instrução.

## 11.4 — Paralelismo temporal × espacial

```text
   PARALELISMO TEMPORAL              PARALELISMO ESPACIAL
   = PIPELINE                        = REPLICAÇÃO DE HARDWARE

   UMA linha, VÁRIAS etapas          VÁRIAS linhas completas
   sobrepostas no tempo              trabalhando ao mesmo tempo

   ┌──┬──┬──┬──┐                     ┌──┬──┬──┬──┐
   │IF│ID│EX│WB│ instr 1             │IF│ID│EX│WB│ ← núcleo 1
   └──┴──┴──┴──┘                     └──┴──┴──┴──┘
      ┌──┬──┬──┬──┐                  ┌──┬──┬──┬──┐
      │IF│ID│EX│WB│ instr 2          │IF│ID│EX│WB│ ← núcleo 2
      └──┴──┴──┴──┘                  └──┴──┴──┴──┘
         ┌──┬──┬──┬──┐               ┌──┬──┬──┬──┐
         │IF│ID│EX│WB│ instr 3       │IF│ID│EX│WB│ ← núcleo 3
         └──┴──┴──┴──┘               └──┴──┴──┴──┘

   1 conjunto de hardware            3 conjuntos de hardware
   Exemplos: PIPELINE                Exemplos: MULTICORE, GPU,
                                     SIMD, superescalar
```

💡 **A analogia da lanchonete:**

```text
   TEMPORAL (pipeline)          ESPACIAL (replicação)
   ─────────────────────        ──────────────────────
   UM balcão com 3 pessoas:     TRÊS balcões completos,
   uma monta o pão,             cada um com uma pessoa
   outra põe a carne,           fazendo o sanduíche
   outra embala                 inteiro
```

⭐ **Os dois se combinam.** Um processador moderno tem **4 núcleos** (espacial), cada um com um **pipeline de 14 estágios** (temporal), e cada pipeline é **superescalar** (espacial de novo — várias ULAs por núcleo).

---

# AULA 12 — Juntando tudo

Vamos pegar **um programa real** e passar por **tudo** que você aprendeu.

## O programa

```c
// soma A[0] + A[1] e guarda em A[2]
long A[3];
A[2] = A[0] + A[1];
```

## Passo 1 — traduzir para RISC-V

```asm
ld  x5, 0(x10)      # x5 = A[0]
ld  x6, 8(x10)      # x6 = A[1]
add x7, x5, x6      # x7 = A[0] + A[1]
sd  x7, 16(x10)     # A[2] = x7
```

## Passo 2 — identificar as dependências

```text
   instr        escreve    lê
   1: ld x5       x5       x10
   2: ld x6       x6       x10
   3: add x7      x7       x5, x6   ← depende de 1 e de 2
   4: sd          —        x7, x10  ← depende de 3
```

```text
   DIAGRAMA DE DEPENDÊNCIAS

   ① ld x5 ──────────┐
                     ├──► ③ add x7 ──────► ④ sd
   ② ld x6 ──────────┘
```

## Passo 3 — analisar os hazards

```text
   1 → 3 (x5):  distância 2, e a 1 é lw  →  forwarding MEM/WB, 0 stall ✅
   2 → 3 (x6):  distância 1, e a 2 é lw  →  ⚠️ LOAD-USE! 1 STALL
   3 → 4 (x7):  distância 1, e a 3 é ULA →  forwarding EX/MEM, 0 stall ✅
```

## Passo 4 — desenhar o pipeline com o stall

```text
Ciclo:      C1   C2   C3   C4   C5   C6   C7   C8   C9
─────────────────────────────────────────────────────────
1: ld x5    IF   ID   EX  MEM   WB
                            │
                            └──⚡ MEM/WB → EX (x5)
                                 │
2: ld x6         IF   ID   EX   MEM   WB
                                  │
                                  └──⚡ MEM/WB → EX (x6)
                                       │
3: add x7             IF   ID  ███    EX   MEM   WB
                                ▲      │
                            1 STALL    └──⚡ EX/MEM → EX (x7)
                           (load-use)       │
4: sd                      IF   ███    ID   EX   MEM   WB
```

## Passo 5 — contar os ciclos

```text
   ciclos = N + (E − 1) + stalls
          = 4 + (5 − 1) + 1
          = 9 ciclos ✅
```

## Passo 6 — calcular o tempo e o speedup

```text
   Estágios: IF=200  ID=100  EX=200  MEM=200  WB=100

   ① Tc_mono = 200+100+200+200+100 = 800 ps
   ② Tc_pipe = max(...)            = 200 ps

   ③ T_mono  = 4 × 800             = 3.200 ps
   ④ T_pipe  = 9 × 200             = 1.800 ps

   ⑤ Speedup = 3.200 / 1.800       = 1,78
```

🛑 **PARE E PENSE:** por que o speedup ficou só 1,78 e não perto de 4,00?

<br>

**Por duas razões:**

```text
① N é MUITO pequeno (só 4 instruções).
   O "imposto" de enchimento (4 ciclos) é gigante em relação a isso.

② Tem 1 stall, que representa 11% dos ciclos.
```

⭐ **O speedup se aproxima do teórico quando `N` é grande e os stalls são raros.** Em programas reais, com milhões de instruções e forwarding funcionando, o speedup fica muito perto do ideal.

## Passo 7 — otimizar reordenando ⭐

🛑 **PARE E PENSE:** dá para eliminar aquele stall sem mudar o resultado do programa?

<br>

**Trocar a ordem dos dois `ld` não resolve** — qualquer um deles que ficar em segundo lugar continua vizinho do `add`. O que resolve é **enfiar uma instrução independente no meio**, transformando a distância 1 em distância 2:

```text
ANTES (9 ciclos, 1 stall)        DEPOIS (9 ciclos, 0 stalls)
──────────────────────────       ──────────────────────────────
ld  x5, 0(x10)                   ld  x5, 0(x10)
ld  x6, 8(x10)                   ld  x6, 8(x10)
add x7, x5, x6   ← stall         addi x28, x0, 1  ← trabalho útil
sd  x7, 16(x10)                  add x7, x5, x6   ← agora dist. 2 ✅
                                 sd  x7, 16(x10)
```

💡 **Repare:** ficaram **9 ciclos nos dois casos** — mas no segundo o processador executou **5 instruções** em vez de 4. O ciclo que era bolha passou a fazer trabalho útil. **É exatamente isso que um compilador otimizador faz.**

---

# AULA 13 — Exercícios progressivos

Faça **na ordem**. Tente antes de ver a resposta.

## Nível 1 — conceitos

**1.1** Um pipeline tem os estágios 150 / 80 / 200 / 190 / 90 ps. Qual é o `Tc` do monociclo e o do pipeline?

<details><summary>Resposta</summary>

```text
Tc_mono  = 150+80+200+190+90 = 710 ps   (a SOMA)
Tc_pipe  = max(150,80,200,190,90) = 200 ps   (o MAIOR)
```
</details>

**1.2** No exercício anterior, se você acelerar o estágio de 80 ps para 40 ps, o `Tc_pipe` muda?

<details><summary>Resposta</summary>

**Não.** Continua 200 ps, porque o gargalo é o terceiro estágio. Só adianta acelerar **o gargalo**.
</details>

**1.3** O pipeline reduz a latência de uma instrução?

<details><summary>Resposta</summary>

**Não.** Ele aumenta o **throughput**. A latência fica igual ou **piora** (porque agora são 5 ciclos em vez de 1, mesmo que cada ciclo seja menor).
</details>

**1.4** Acrescentar pipeline a um processador muda sua **arquitetura**?

<details><summary>Resposta</summary>

**Não.** Muda a **organização/microarquitetura**. O conjunto de instruções (arquitetura) continua idêntico — o mesmo programa roda sem recompilar.
</details>

**1.5** Por que processadores com pipeline usam Harvard?

<details><summary>Resposta</summary>

Para eliminar o **hazard estrutural**: com uma única memória, o estágio **IF** de uma instrução colidiria com o estágio **MEM** de outra no mesmo ciclo. Duas memórias (ou duas caches L1) permitem os dois acessos simultâneos.
</details>

**1.6** Previsão **estática** pode se adaptar ao comportamento do programa em execução?

<details><summary>Resposta</summary>

**Não.** Estática é **fixa**, definida em projeto/compilação. Só a **dinâmica** usa histórico e se adapta.
</details>

## Nível 2 — contas de pipeline

**2.1** `N = 300` instruções, 5 estágios de 250 ps, monociclo de 1.000 ps. Calcule `T_mono`, `T_pipe` e o speedup.

<details><summary>Resposta</summary>

```text
T_mono = 300 × 1000            = 300.000 ps
ciclos = 300 + (5−1)           = 304
T_pipe = 304 × 250             =  76.000 ps
Speedup = 300.000 / 76.000     = 3,95
Teórico = 1000/250             = 4,00
```
</details>

**2.2** Mesmo processador, mas `N = 5`. Qual o speedup? Comente.

<details><summary>Resposta</summary>

```text
T_mono = 5 × 1000        =  5.000 ps
ciclos = 5 + 4           =      9
T_pipe = 9 × 250         =  2.250 ps
Speedup = 5.000/2.250    =  2,22
```

**Comentário:** muito longe do teórico (4,00) porque o **custo de enchimento** (4 ciclos) é quase tão grande quanto o programa (5 instruções). **O pipeline só compensa com muitas instruções.**
</details>

**2.3** Estágios: IF=200, ID=150, EX=250, MEM=300, WB=100. Qual estágio você deveria otimizar primeiro, e por quê?

<details><summary>Resposta</summary>

O **MEM (300 ps)**, porque ele é o **gargalo** — é ele que define o `Tc_pipe`. Otimizar qualquer outro **não mexe no clock**.

Se MEM cair para 250: `Tc_pipe` vai de 300 para **250** (novo gargalo = EX).
Se MEM cair para 200: `Tc_pipe` vai para **250** ainda (EX virou o gargalo) — ou seja, **não vale a pena baixar MEM abaixo de 250**.
</details>

## Nível 3 — hazards

**3.1** Quantos stalls neste trecho (com forwarding)?

```asm
add x1, x2, x3
sub x4, x1, x5
or  x6, x4, x7
```

<details><summary>Resposta</summary>

```text
1→2: x1, dist 1, ULA  →  forwarding EX/MEM  →  0 stall
2→3: x4, dist 1, ULA  →  forwarding EX/MEM  →  0 stall

TOTAL: 0 stalls.  ciclos = 3 + 4 = 7
```
</details>

**3.2** E aqui?

```asm
lw  x1, 0(x2)
add x3, x1, x4
```

<details><summary>Resposta</summary>

**1 stall** — é **load-use hazard**. O `lw` só tem o valor de `x1` no fim do **MEM**, e o `add` precisa dele no início do **EX**. Nem o forwarding resolve.

```text
ciclos = 2 + 4 + 1 = 7
```
</details>

**3.3** E aqui?

```asm
lw  x1, 0(x2)
sub x5, x6, x7
add x3, x1, x4
```

<details><summary>Resposta</summary>

**0 stalls.** A distância entre o `lw` e o uso de `x1` é **2**, então o forwarding `MEM/WB → EX` resolve.

```text
ciclos = 3 + 4 = 7
```

⭐ Note que **3.2 e 3.3 gastam os mesmos 7 ciclos**, mas 3.3 executou **uma instrução a mais**. É a reordenação do compilador em ação.
</details>

**3.4** Indique a **origem** e o **destino** do forwarding em cada dependência:

```asm
add x1, x2, x3
or  x9, x8, x7
sub x4, x1, x5
```

<details><summary>Resposta</summary>

```text
Só há uma dependência: 1 → 3 (registrador x1), distância 2.

ORIGEM:  registrador de pipeline MEM/WB
DESTINO: entrada da ULA, no estágio EX (da instrução sub)
```
</details>

## Nível 4 — assembly

**4.1** Traduza: `x5 = x6 - 20`

<details><summary>Resposta</summary>

```asm
addi x5, x6, -20
```
(não existe `subi` — usa-se `addi` com negativo)
</details>

**4.2** Traduza, sabendo que `A` (vetor de `long`) está em `x10`:

```c
A[5] = A[1];
```

<details><summary>Resposta</summary>

```asm
ld x5, 8(x10)       # A[1]  →  1 × 8 = 8
sd x5, 40(x10)      # A[5]  →  5 × 8 = 40
```
</details>

**4.3** Traduza:

```c
if (a < b)  c = a;
else        c = b;
// a→x5, b→x6, c→x7
```

<details><summary>Resposta</summary>

```asm
        bge  x5, x6, SENAO     # se a >= b (condição INVERTIDA), vai p/ else
        add  x7, x5, x0        # c = a
        j    FIM               # ⭐ pula o else
SENAO:  add  x7, x6, x0        # c = b
FIM:
```
</details>

**4.4** Traduza:

```c
while (i < n)  i = i + 2;
// i→x5, n→x6
```

<details><summary>Resposta</summary>

```asm
LOOP:   bge  x5, x6, FIM     # condição invertida: sai se i >= n
        addi x5, x5, 2       # i = i + 2
        j    LOOP
FIM:
```
</details>

**4.5** ⭐ Traduza — este é o mais provável de cair:

```c
// conta quantos elementos de A são iguais a zero
cont = 0;
for (i = 0; i < n; i++)
    if (A[i] == 0)
        cont = cont + 1;
// A→x10, n→x11, cont→x5, i→x6
```

<details><summary>Resposta</summary>

```asm
        add  x5, x0, x0        # cont = 0
        add  x6, x0, x0        # i = 0

LOOP:   bge  x6, x11, FIM      # se i >= n, sai

        slli x7, x6, 3         # x7 = i × 8
        add  x7, x10, x7       # x7 = &A[i]
        ld   x28, 0(x7)        # x28 = A[i]

        bne  x28, x0, PROX     # se A[i] != 0, pula o corpo do if
        addi x5, x5, 1         # cont = cont + 1

PROX:   addi x6, x6, 1         # i++
        j    LOOP

FIM:
```

⭐ Repare nas **duas** inversões de condição: `bge` para sair do `for`, e `bne` para pular o `if`.
</details>

**4.6** Simule o exercício 4.5 com `A = [0, 7, 0]` e `n = 3`. Qual o valor final de `x5`?

<details><summary>Resposta</summary>

| iter | i (x6) | A[i] (x28) | A[i]==0? | cont (x5) |
| --- | --- | --- | --- | --- |
| início | 0 | — | — | 0 |
| 1 | 0 | 0 | ✅ sim | **1** |
| 2 | 1 | 7 | ❌ não | 1 |
| 3 | 2 | 0 | ✅ sim | **2** |
| teste | 3 | | `bge 3,3` → sai | **2** |

**`x5 = 2`** ✅
</details>

## Nível 5 — questão integrada (o estilo da P1)

**5.1** Dado o trecho abaixo, num pipeline de 5 estágios (IF=200, ID=100, EX=200, MEM=200, WB=100) **com forwarding**:

```asm
1: lw   x1, 0(x10)
2: lw   x2, 8(x10)
3: add  x3, x1, x2
4: sw   x3, 16(x10)
5: addi x10, x10, 24
```

**(a)** Identifique todas as dependências de dados.
**(b)** Quantos stalls?
**(c)** Quantos ciclos no total?
**(d)** Qual o tempo no pipeline e no monociclo?
**(e)** Qual o speedup?

<details><summary>Resposta completa</summary>

**(a) Dependências**

```text
   instr     escreve   lê
   1: lw       x1      x10
   2: lw       x2      x10
   3: add      x3      x1, x2
   4: sw       —       x3, x10
   5: addi     x10     x10

   1 → 3  (x1),  distância 2, origem é lw
   2 → 3  (x2),  distância 1, origem é lw   ⚠️
   3 → 4  (x3),  distância 1, origem é ULA
```

**(b) Stalls**

```text
   1→3: dist 2, lw   →  forwarding MEM/WB      →  0
   2→3: dist 1, lw   →  ⚠️ LOAD-USE            →  1 STALL
   3→4: dist 1, ULA  →  forwarding EX/MEM      →  0

   TOTAL: 1 stall
```

**(c) Ciclos**

```text
   ciclos = N + (E−1) + stalls = 5 + 4 + 1 = 10 ciclos
```

**(d) Tempos**

```text
   Tc_pipe = max(200,100,200,200,100) = 200 ps
   Tc_mono = 200+100+200+200+100      = 800 ps

   T_pipe  = 10 × 200 = 2.000 ps
   T_mono  =  5 × 800 = 4.000 ps
```

**(e) Speedup**

```text
   Speedup = 4.000 / 2.000 = 2,00
```

**Diagrama:**

```text
Ciclo:      C1   C2   C3   C4   C5   C6   C7   C8   C9   C10
──────────────────────────────────────────────────────────────
1: lw x1    IF   ID   EX  MEM   WB
2: lw x2         IF   ID   EX  MEM   WB
3: add x3             IF   ID  ███   EX  MEM   WB
4: sw                      IF  ███   ID   EX  MEM   WB
5: addi                         IF   ID   EX  MEM   WB
```
</details>

---

# 🎯 O mapa mental final

Se você entendeu estas nove caixas, você entendeu a matéria:

```text
┌─────────────────────────────────────────────────────────────────────┐
│ 1. Toda instrução passa por 5 estágios: IF ID EX MEM WB             │
│    (só lw e sw usam o MEM de verdade; o lw é o mais lento)          │
├─────────────────────────────────────────────────────────────────────┤
│ 2. MONOCICLO: Tc = SOMA dos estágios     (todos pagam pelo mais     │
│    PIPELINE:  Tc = MAIOR estágio          lento; é o desperdício)   │
├─────────────────────────────────────────────────────────────────────┤
│ 3. Pipeline melhora o THROUGHPUT, não a LATÊNCIA                    │
│    (é uma faixa a mais na estrada, não um limite maior)             │
├─────────────────────────────────────────────────────────────────────┤
│ 4. ciclos = N + (E − 1) + stalls                                    │
│    Speedup = T_mono / T_pipe                                        │
│    O (E−1) é o "imposto de enchimento": só importa se N é pequeno   │
├─────────────────────────────────────────────────────────────────────┤
│ 5. TRÊS HAZARDS:                                                    │
│    estrutural → Harvard        dados → forwarding                   │
│    controle   → previsão de desvios                                 │
├─────────────────────────────────────────────────────────────────────┤
│ 6. FORWARDING: EX/MEM → EX  (distância 1)                           │
│                MEM/WB → EX  (distância 2)                           │
│    (são os REGISTRADORES DE PIPELINE; destino é sempre a ULA)        │
├─────────────────────────────────────────────────────────────────────┤
│ 7. LOAD-USE: lw + uso imediato = 1 STALL OBRIGATÓRIO                │
│    (é o ÚNICO caso que o forwarding não resolve)                    │
├─────────────────────────────────────────────────────────────────────┤
│ 8. RISC ganha do CISC no pipeline por causa do TAMANHO FIXO         │
│    (o IF não precisa esperar o ID para saber onde a próxima começa) │
├─────────────────────────────────────────────────────────────────────┤
│ 9. ASSEMBLY: destino primeiro · índice × tamanho · condição         │
│    INVERTIDA no if/while · x0 é sempre zero                         │
└─────────────────────────────────────────────────────────────────────┘
```

---

# 📚 Continue estudando

| Para... | Use... |
| --- | --- |
| revisar rápido na véspera | `ARQ_conceitos_P1.md` |
| treinar as questões que já caíram | `ARQ_exercicios_resolvidos.md` |
| aprender / reaprender do zero | **este arquivo** |

**Bibliografia:**
- Patterson & Hennessy, *Organização e Projeto de Computadores: A Interface Hardware/Software* (RISC-V Edition) — caps. 2 (assembly) e 4 (pipeline)
- Stallings, *Arquitetura e Organização de Computadores* — cap. 14 (pipeline)
- Tanenbaum, *Organização Estruturada de Computadores* — cap. 2
