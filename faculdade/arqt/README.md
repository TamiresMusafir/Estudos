# ⚙️ Arquiteturas Avançadas de Computadores (CEFET/RJ) — Conceitos para a P1

> Baseado nos slides do Prof. Ronilson Pereira (aulas 01 a 05) e do Prof. Igor C. G. Ribeiro (RISC-V), nas duas provas P1 (Turmas A e B) e na Lista de Exercícios 1.
>
> **Legenda:** ⚠️ **Pegadinha** · 🎯 **Cai direto na prova** · 📌 **Definição literal do slide** · 🧮 **Conta** · 🧪 **Já caiu**
>
> 📂 Os exercícios resolvidos passo a passo estão no arquivo separado **`ARQ_exercicios_resolvidos.md`**.

---

## 📑 Sumário

* [Parte 0 — O que cai na prova](#parte-0--o-que-cai-na-prova)
* [Parte 1 — Arquitetura, Organização e Microarquitetura](#parte-1--arquitetura-organização-e-microarquitetura)
* [Parte 2 — Desempenho e as fórmulas](#parte-2--desempenho-e-as-fórmulas)
* [Parte 3 — Paralelismo temporal e espacial](#parte-3--paralelismo-temporal-e-espacial)
* [**Parte 4 — Pipeline**](#parte-4--pipeline)
* [**Parte 5 — Hazards**](#parte-5--hazards)
* [Parte 6 — Previsão de desvios](#parte-6--previsão-de-desvios)
* [**Parte 7 — Contas de pipeline (speedup)**](#parte-7--contas-de-pipeline-speedup)
* [Parte 8 — RISC × CISC](#parte-8--risc--cisc)
* [**Parte 9 — Assembly RISC-V**](#parte-9--assembly-risc-v)
* [Parte 10 — Checklist e colinha final](#parte-10--checklist-e-colinha-final)

---

# Parte 0 — O que cai na prova

Comparando as duas P1 aplicadas (Turmas A e B), a estrutura é praticamente idêntica. **As duas provas têm as mesmas 10 questões, só trocando os números.**

| # | Tipo de questão | Pontos | Onde estudar |
| --- | --- | --- | --- |
| 1 | **Diagrama de pipeline + identificar hazard + resolver com forwarding** | 2,0 | Partes 4, 5 |
| 2 | Período do clock: **monociclo × pipeline** (dados os tempos dos estágios) | 1,0 | Parte 7 |
| 3 | **Calcular speedup** (pipeline × monociclo), mostrando os cálculos | 2,0 | Parte 7 |
| 4 | **Compilar C → assembly RISC-V** | 1,0 | Parte 9 |
| 5 | **Cite e explique os três tipos de hazards** | 1,0 | Parte 5 |
| 6 | **Por que RISC-V é mais eficiente para pipelining** (+2 características) | 1,0 | Parte 8 |
| 7 | V/F com justificativa | 0,5 | Partes 1, 5, 8 |
| 8 | Múltipla escolha: forwarding serve para... | 0,5 | Parte 5 |
| 9 | Múltipla escolha: hazard estrutural / de controle ocorre devido a... | 0,5 | Parte 5 |
| 10 | Relacionar colunas (hazard estrutural / predição estática) | 0,5 | Partes 5, 6 |

🎯 **Resumo:** metade da prova é **conta de pipeline**, um quarto é **conceito de hazard** e o resto se divide entre **RISC-V assembly** e **RISC × CISC**.

---

# Parte 1 — Arquitetura, Organização e Microarquitetura

## 1.1 Arquitetura × Organização

📌 **Slide 01:**

| | **Arquitetura** | **Organização** |
| --- | --- | --- |
| Definição | Conjunto de atributos **visíveis ao programador** | Forma como os **componentes internos** são conectados e interagem |
| Inclui | conjunto de instruções (ISA), **modos de endereçamento**, estrutura geral do processador, **número de bits** usados para representar os tipos de dados | barramentos, hierarquia de **memória e cache**, sinais de controle, interface com periféricos, tecnologia de memória |
| Visível ao programador? | **Sim** | **Não** (transparente) |
| Nível | Mais **abstrata**; influencia diretamente o **software** | Mais ligada ao **hardware** e à sua implementação |
| Exemplo | a arquitetura **x86** | o **mesmo processador** em dispositivos diferentes, com **configurações diferentes de memória e cache** |

📌 **Importância de ambos:** o desempenho e a eficiência dependem **tanto da arquitetura quanto da organização**.
> Dois computadores com a **mesma arquitetura** podem ter **desempenhos diferentes** por causa da diferença na **organização** do hardware.

⚠️ **PEGADINHA QUE JÁ CAIU (P1 Turma B, questão 8):**

> *"Arquitetura de computadores define **apenas** o conjunto de instruções, enquanto organização define os detalhes de hardware."* → **FALSO**

O erro está no **"apenas"**. A arquitetura define o conjunto de instruções **e também** os modos de endereçamento, os formatos, o número de bits dos tipos de dados e a estrutura geral visível ao programador.

## 1.2 Microarquitetura

📌 **Slide 05_02:**

| | **Arquitetura (ISA)** | **Microarquitetura** |
| --- | --- | --- |
| O que é | A **visão que os programadores têm** da máquina | A **implementação** da arquitetura |
| Componentes | conjunto de registradores, conjunto de instruções, **ABI** | número e tamanho das **caches**, **período do clock**, **utilização de pipeline** |
| Exemplos | ARM, **RISC-V**, x86, x86-64 | pode ser realizada em **hardware** ou em **software (microcódigo)** |

```text
  Programas de Usuário
  ─────────────────────
  Sistema Operacional
  ─────────────────────
     ARQUITETURA (ISA)      ← o que o programador vê
  ─────────────────────
     MICROARQUITETURA       ← como foi implementado
```

🎯 **Regra para responder "defina com suas palavras":**
```text
ISA / Arquitetura  → O QUÊ a máquina faz (contrato com o software)
Microarquitetura   → COMO ela faz (implementação: pipeline, cache, clock)
Organização        → praticamente sinônimo de microarquitetura nos slides
```

## 1.3 Von Neumann × Harvard

📌 **Slide 01:**

| | **Von Neumann** | **Harvard** |
| --- | --- | --- |
| Memória | **ÚNICA** para instruções e dados | **SEPARADA** para instruções e dados |
| Consequência | conflito de acesso | **melhora a velocidade** |

🧪 **Já caiu como múltipla escolha:** *"Qual arquitetura usa memória única para dados e instruções?"* → **Von Neumann**.

🎯 **Amarração com pipeline (isso é o pulo do gato da matéria):**

> Uma memória **única** (Von Neumann) causa **hazard estrutural**, porque a busca da instrução (IF) e o acesso a dados (MEM) disputam a mesma memória no mesmo ciclo.
> 📌 Slide 04: *"precisamos de memória (ou cache) de dados e instruções **separadas** em fluxo de dados com pipeline"* — ou seja, o pipeline exige um arranjo **tipo Harvard**.

---

# Parte 2 — Desempenho e as fórmulas

## 2.1 Tempo de resposta × Vazão

📌 **Slide 02:**

| | Definição |
| --- | --- |
| **Tempo de resposta** (*response time*) | Quanto tempo leva para realizar **uma** tarefa |
| **Vazão** (*throughput*) | Total de trabalho realizado **por unidade de tempo** (tarefas/hora) |

🎯 **Esta distinção é a chave para entender pipeline:**

```text
O pipeline AUMENTA a VAZÃO (throughput).
O pipeline NÃO reduz a LATÊNCIA de uma instrução individual.
```

📌 **Slide 04, literal:** *"O speedup é devido ao aumento da vazão (throughput). **Contudo, o tempo total do início ao fim da execução de uma instrução, ou a latência, não se altera**."*

⚠️ Uma instrução isolada leva o **mesmo tempo** (ou até mais) com pipeline. O ganho aparece quando há **muitas** instruções.

## 2.2 Desempenho relativo

📌 **Slide 02:**

```text
Desempenho = 1 / Tempo de Execução

"X é n vezes mais rápido que Y":

  Desempenho(X)        Tempo de Execução(Y)
  ───────────────  =  ──────────────────────  =  n
  Desempenho(Y)        Tempo de Execução(X)
```

🧮 **Exemplo do slide:** programa leva 10 s em A e 15 s em B.
```text
15 s / 10 s = 1,5   →   A é 1,5 vezes mais rápido que B
```

## 2.3 Clock

📌 **Slide 02:**

| Termo | Definição | Exemplo |
| --- | --- | --- |
| **Período de clock** (Tc) | duração de **um** ciclo de clock | 250 ps = 0,25 ns = 250 × 10⁻¹² s |
| **Frequência de clock** | ciclos por segundo | 4,0 GHz = 4000 MHz = 4,0 × 10⁹ Hz |

```text
Período = 1 / Frequência        Frequência = 1 / Período

3,57 MHz  →  Tc = 1/3,57×10⁶ ≈ 280 ns
```

## 2.4 ⭐ A equação do tempo de execução

📌 **Slide 05_01 — a fórmula oficial da disciplina:**

```text
              Tp = Ci × Tc × Ni

Tp = tempo de execução do programa
Ci = ciclos por instrução (CPI)
Tc = tempo de cada ciclo (período do clock)
Ni = número de instruções
```

🎯 É a mesma coisa que a fórmula clássica `Tempo = N.º instruções × CPI × Período`. Serve para comparar **RISC × CISC** (Parte 8).

## 2.5 Medição do tempo

📌 **Slide 02:**

| | O que inclui |
| --- | --- |
| **Tempo decorrido** (*elapsed*) | Tempo total de resposta: processamento, **E/S**, sobrecarga do SO, **tempo ocioso**. Determina o desempenho do **sistema** |
| **Tempo de CPU** | Só o tempo de processamento da tarefa. **Exclui E/S** e a parcela de outras tarefas. Compreende o tempo de CPU **do usuário** e **do sistema** |

---

# Parte 3 — Paralelismo temporal e espacial

📌 **Slide 01 — a divisão que abre a ementa:**

| | **Paralelismo TEMPORAL** | **Paralelismo ESPACIAL** |
| --- | --- | --- |
| O que é | O processamento ocorre **ao longo do tempo**, dividindo instruções em **estágios** | **Diferentes partes** de um problema são resolvidas **simultaneamente** |
| Técnica | **Pipelining** | **Multicore**, computação distribuída, GPUs |
| Analogia do slide | uma **linha de montagem industrial**, onde cada etapa realiza uma parte do trabalho | um **grupo de pessoas** dividindo tarefas em uma equipe |

🎯 **Para a questão "dê um exemplo de cada":**

```text
TEMPORAL  → pipeline de 5 estágios do MIPS/RISC-V:
             enquanto a instrução 1 está em MEM, a 2 está em EX, a 3 em ID e a 4 em IF.
             UMA unidade funcional de cada tipo, reaproveitada em sequência.

ESPACIAL  → processador de 4 núcleos rodando 4 threads ao mesmo tempo;
             ou uma GPU somando 1024 elementos de um vetor de uma só vez.
             VÁRIAS unidades funcionais iguais, trabalhando em paralelo.
```

⚠️ A diferença essencial: no **temporal** as instruções estão em **estágios diferentes** do **mesmo** hardware; no **espacial** elas estão em **hardwares diferentes**, no **mesmo estágio**.

---

# Parte 4 — Pipeline

## 4.1 Definição e objetivo

📌 **Slides 02 e 03:**

> **Definição:** técnica que **divide a execução de instruções em etapas sequenciais**. Várias instruções são processadas **simultaneamente em estágios diferentes**.
>
> **Analogia:** o pipeline se assemelha a uma **linha de produção**, onde cada unidade executa a sua função e passa para a unidade seguinte.
>
> **Objetivo:** aumentar o **throughput** (n.º de instruções concluídas por ciclo).

📌 Cada etapa é chamada **estágio de pipe** ou **segmento de pipe**. Os estágios são conectados para formar uma *pipe*: as instruções entram numa ponta, seguem pelos estágios e saem na outra.

📌 **Analogia da lavanderia** (slide 03 — as 4 etapas):
```text
1. Colocar a roupa suja na lavadora
2. Transferir a roupa lavada da lavadora para a secadora
3. Levar a roupa seca para a mesa de passar
4. Guardar a roupa no armário
```
> Quatro lotes: **Speedup = 8/3,5 = 2,3**. Primeiro lote após 4 estágios, **lote seguinte após 1 estágio**. **Speedup ≈ número de estágios.**

## 4.2 ⭐ Os 5 estágios (MIPS / RISC-V)

📌 **Decorar com a sigla e o nome completo — cai em toda prova:**

| # | Sigla | Nome | O que faz |
| --- | --- | --- | --- |
| 1 | **IF** | *Instruction Fetch* | **Busca** a instrução na memória |
| 2 | **ID** | *Instruction Decode* | **Decodifica** e **lê os registradores** |
| 3 | **EX** | *Execute* | **Executa** a operação (ULA) ou **calcula o endereço** |
| 4 | **MEM** | *Memory Access* | **Acesso à memória** (só load/store) |
| 5 | **WB** | *Write Back* | **Escreve** o resultado no registrador de destino |

```text
IF  →  ID  →  EX  →  MEM  →  WB
```

## 4.3 O diagrama de pipeline (como desenhar na prova)

```text
Instrução      C1   C2   C3   C4   C5   C6   C7   C8   C9
─────────────────────────────────────────────────────────
1: lw          IF   ID   EX  MEM   WB
2: sub              IF   ID   EX  MEM   WB
3: sw                    IF   ID   EX  MEM   WB
4: add                        IF   ID   EX  MEM   WB
5: or                              IF   ID   EX  MEM   WB
```

🎯 **Regras de leitura:**
```text
· Cada instrução começa UM ciclo depois da anterior (escada).
· A instrução N começa no ciclo N e termina no ciclo N + 4.
· A partir do ciclo 5, UMA instrução é concluída por ciclo.
· O pipeline está "cheio" do ciclo 5 até o ciclo N.
```

📌 **Slides 02/03 — "Vantagens do Sistema":**
```text
Sem pipeline: 5 instruções = 25 ciclos      (5 × 5)
Com pipeline: 5 instruções =  9 ciclos      (5 + 4)
```
> Rápido: até **5× mais veloz**. Eficiente: **nenhum estágio fica ocioso**. Previsível: sempre sabemos onde cada parte está.

## 4.4 ⭐ Ciclo do processador

📌 **Slide 02 — a regra que resolve a questão 2 da prova:**

> A vazão de um pipeline é dada pela **frequência com que uma instrução é terminada**. Como os estágios são conectados, **todos precisam estar prontos para executar ao mesmo tempo**, logo **todos têm o mesmo intervalo** para executar suas tarefas. Esse tempo é o **Ciclo do Processador**.
>
> ⭐ **A duração do ciclo do processador deve ser o tempo necessário para o ESTÁGIO MAIS LENTO ser executado.**

🧮 **A regra de ouro das contas:**

```text
MONOCICLO  →  Tc = SOMA de todos os estágios
PIPELINE   →  Tc = MAIOR estágio (o gargalo)
```

🧪 **P1 Turma B, questão 3:** IF 100, ID 100, EX 300, MEM 500, WB 100 ps.
```text
a) Monociclo:  100 + 100 + 300 + 500 + 100 = 1100 ps
b) Pipeline:   max(100, 100, 300, 500, 100) =  500 ps    ← o MEM é o gargalo
```

🧪 **P1 Turma A, questão 2:** IF 50, ID 50, EX 200, MEM 400, WB 50 ps.
```text
a) Monociclo:  50 + 50 + 200 + 400 + 50 = 750 ps
b) Pipeline:   max(...)                  = 400 ps
```

## 4.5 A tabela oficial dos slides (decore os números)

📌 **Slides 03 e 04** — os tempos usados em quase todos os exercícios:

| Classe de instrução | Busca instr. | Leitura reg. | ULA | Acesso dados | Escrita reg. | **Total** |
| --- | --- | --- | --- | --- | --- | --- |
| **Load word (`lw`)** | 200 ps | 100 ps | 200 ps | 200 ps | 100 ps | **800 ps** |
| **Store word (`sw`)** | 200 ps | 100 ps | 200 ps | 200 ps | — | **700 ps** |
| **R-format** (`add`,`sub`,`AND`,`OR`,`slt`) | 200 ps | 100 ps | 200 ps | — | 100 ps | **600 ps** |
| **Branch (`beq`)** | 200 ps | 100 ps | 200 ps | — | — | **500 ps** |

```text
Monociclo → Tc = 800 ps  (tem que caber a instrução mais lenta, o lw)
Pipeline  → Tc = 200 ps  (o maior estágio: IF = ULA = MEM = 200 ps)
```

⚠️ **No monociclo, o clock é ditado pela instrução MAIS LENTA (`lw`, 800 ps)**, mesmo que um `beq` só precisasse de 500 ps. É isso que torna o monociclo ineficiente.

## 4.6 Speedup do pipeline — o exemplo dos slides

📌 **Slide 03:**
> O tempo entre a primeira e a quarta instrução foi de 600 ps, **4 vezes menos** que no ciclo único. O tempo total não reduziu 4 vezes (de 2400 para 1400) **porque o número de instruções é pequeno**.
>
> Acrescentando 1.000.000 de instruções:
> ```text
> Monociclo: 1.000.000 × 800 + 2400 = 800.002.400 ps
> Pipeline:  1.000.000 × 200 + 1400 = 200.001.400 ps
> Speedup ≈ 4
> ```

🎯 **Conclusão que cai em V/F:** o speedup **só se aproxima do número de estágios quando o número de instruções é grande**. Com poucas instruções, o enchimento do pipeline pesa.

## 4.7 Por que o MIPS/RISC-V facilita o pipeline

📌 **Slide 03 — "Projetando o conjunto de instruções" (esta lista é a resposta da questão 6 da prova):**

```text
1. Instruções de MESMO TAMANHO.
2. POUCOS FORMATOS de instruções e SIMETRIA.
   → Permite, por exemplo, LER OS REGISTRADORES ANTES de ter decodificado a instrução.
3. Somente LOAD ou STORE acessam a memória.
   → Se um add acessasse a memória, teriam que ser adicionados novos estágios.
4. Transferências sempre em UM ÚNICO CICLO (dados alinhados).
```

---

# Parte 5 — Hazards

## 5.1 Definição

📌 **Slide 04:**

> **Hazards** são situações em que a **próxima instrução não pode ser executada no ciclo de clock seguinte**.

⚠️ Note a definição: hazard **não é erro**, é uma situação que **obriga o pipeline a parar ou a usar hardware extra**.

## 5.2 ⭐ Os três tipos (questão de 1,0 ponto em toda prova)

| Tipo | 📌 Causa (literal do slide) | Exemplo | Solução |
| --- | --- | --- | --- |
| **Estrutural** | **Conflito de unidades funcionais** — um **recurso** necessário está **ocupado** | IF e MEM disputam a **mesma memória** no mesmo ciclo | **Duplicar o recurso**: memórias/caches separadas de dados e instruções (Harvard) |
| **De dados** | Ocorre quando uma etapa precisa **esperar até que outra seja executada** — uma instrução **depende** do resultado de outra | `add x1,x2,x3` seguido de `sub x4,x1,x5` | **Forwarding**; se for load-use, **stall + forwarding**; **reordenação de código** |
| **De controle** | O que ocorre em **desvios condicionais e incondicionais** | `beq` — não se sabe qual é a próxima instrução | **Previsão de desvio** (estática ou dinâmica); antecipar a decisão para o estágio **ID** |

🧪 **Múltipla escolha que já caiu nas duas provas:**

| Pergunta | Resposta |
| --- | --- |
| "Um hazard **estrutural** ocorre devido a:" | **Conflito por uso de recursos** |
| "Um hazard **de controle** ocorre devido a:" | **Desvios condicionais não previstos** |
| "Em pipelines, **forwarding** é usado para:" | **Evitar stalls causados por hazards de dados** |

## 5.3 Hazard estrutural em detalhe

📌 **Slide 04:**

> Conflito para o uso de recurso. No MIPS pipeline com uma **única memória**:
> * instrução de **load/store** → acesso de dados;
> * a **busca de instrução** deveria parar (**stall**) naquele ciclo;
> * causaria uma **"bolha"** no pipeline.
>
> Portanto, precisamos de **memória (ou cache) de dados e instruções separadas**.

```text
Ciclo:        C1   C2   C3   C4   C5
lw            IF   ID   EX  MEM   WB      ← MEM usa a memória no C4
add                IF   ID   EX  MEM
sub                     IF   ID   EX
or                           IF ← quer usar a memória no C4 também!
                                 ▲
                          CONFLITO: memória única
```

🧪 **Relacionar colunas (caiu nas duas provas):**
> **(1) Hazard estrutural** → *"Conflito por uso simultâneo da memória de dados e instruções."*

## 5.4 ⭐ Hazard de dados e forwarding

📌 **Slide 04 — Forwarding** (ou *bypassing*, ou *encaminhamento*):

> **Utiliza o resultado quando é calculado!**
> * **Não espera** pelo armazenamento no registrador.
> * Requer **conexões extras** no fluxo de dados.

### Sem forwarding

```text
Ciclo:        C1   C2   C3   C4   C5   C6   C7   C8
add x1,x2,x3  IF   ID   EX  MEM   WB
                              │     └── x1 só fica pronto no WB (C5)
sub x4,x1,x5       IF   ID   EX ←── mas precisa de x1 no EX (C4)!
                             ▲
                        HAZARD DE DADOS
```

### Com forwarding

```text
add x1,x2,x3  IF   ID   EX ──┐ MEM   WB
                             │ x1 já existe no FIM do EX (C3)
                             ▼
sub x4,x1,x5       IF   ID   EX   MEM   WB
                             ▲
                  entra direto na ULA no C4 → SEM STALL
```

🎯 **Como nomear os caminhos de forwarding na prova** (a questão pede "indique origem e destino"):

| Distância entre as instruções | Caminho | Funciona? |
| --- | --- | --- |
| 1 instrução (consecutivas) | **EX/MEM → EX** | ✅ sem stall |
| 2 instruções | **MEM/WB → EX** | ✅ sem stall |
| 3 ou mais | nenhum (o banco de registradores já resolve) | ✅ sem hazard |
| `lw` seguido de uso imediato | **MEM/WB → EX**, mas **só depois de 1 stall** | ⚠️ **1 bolha obrigatória** |

## 5.5 ⭐ Load-use hazard — o caso que forwarding NÃO resolve

📌 **Slide 04, literal:**

> **Nem sempre é possível evitar a parada com encaminhamento.** Se o valor não estiver disponível quando necessário, **não é possível voltar no tempo!**
>
> O hazard de dados é **mais grave no caso do uso da instrução `load`**. No caso do load, **o dado só está disponível após o 4º estágio** (MEM). Neste caso o **"stall" é inevitável**.

```text
Ciclo:        C1   C2   C3   C4   C5   C6   C7
lw  x1,0(x2)  IF   ID   EX  MEM   WB
                              └── x1 só existe no FIM do C4 (MEM)
sub x4,x1,x5       IF   ID   EX ←── precisa de x1 no INÍCIO do C4
                             ▲
              ⚠️ teria que "voltar no tempo" → IMPOSSÍVEL
```

**Com 1 stall (bolha):**

```text
Ciclo:        C1   C2   C3   C4   C5   C6   C7
lw  x1,0(x2)  IF   ID   EX  MEM ──┐WB
                                  │ x1 pronto no fim do C4
sub x4,x1,x5       IF   ID  ****  EX   MEM   WB
                            bolha  ▲
                                   └── forwarding MEM/WB → EX no C5
```

⚠️ **PEGADINHA CERTA (caiu como V/F na Turma A):**
> *"Forwarding elimina **todos** os hazards de dados."* → **FALSO**, por causa do **load-use**, que sempre exige **pelo menos 1 stall**.

## 5.6 Stall (bolha) e reordenação de código

📌 **Slide 04:**
> Uma solução é o chamado **"stall"** (ou **bolha**), onde se deixa o pipeline vazio até o conflito ser resolvido. Porém isso é feito **em conjunto com a técnica de forwarding**.

📌 **Reordenação de código:**
> Outra forma de combater os hazards é a **reordenação do código**, que pode **evitar a espera pelos dados após o load**.

🧮 **Exemplo:**

```text
CÓDIGO ORIGINAL (1 stall)        CÓDIGO REORDENADO (0 stall)
lw   x1, 0(x2)                   lw   x1, 0(x2)
add  x3, x1, x4   ← stall        lw   x5, 8(x2)        ← instrução independente no meio
lw   x5, 8(x2)                   add  x3, x1, x4       ← agora x1 já está pronto
```

🎯 A reordenação é feita pelo **compilador**, não pelo hardware.

## 5.7 Hazard de controle

📌 **Slide 04:**

> Desvios (**branch**) determinam o **fluxo de controle** (qual é a próxima instrução a ser executada).
> * Recuperar a próxima instrução **depende do resultado do desvio**.
> * **Não é possível sempre recuperar a instrução correta com pipeline** (pois o desvio ainda estará na fase **ID**).
>
> No pipeline MIPS:
> * precisa **comparar registradores (estágio EX)** e **calcular o endereço alvo**;
> * **adicionar hardware para fazer isso na etapa ID** (mais cedo) → reduz a penalidade.

```text
Ciclo:         C1   C2   C3   C4   C5
beq x1,x2,L    IF   ID   EX ←── só aqui se sabe se desvia
???                 IF ←── qual instrução buscar?! 
```

---

# Parte 6 — Previsão de desvios

📌 **Slide 04:**

> Pipelines **mais longos** não podem determinar prontamente o resultado do desvio antecipadamente — as **penalidades de stall tornam-se inaceitáveis**. A solução é **prever** a saída do desvio: **o stall acontece apenas quando erra**.
>
> No pipeline MIPS é possível **predizer que o desvio não é tomado** e recuperar a instrução **depois** do desvio.

## Os dois tipos

| | **Predição ESTÁTICA** | **Predição DINÂMICA** |
| --- | --- | --- |
| Base | o **comportamento típico** (laços e condicionais) | o **hardware mede o comportamento atual** dos desvios |
| Como funciona | regras fixas, definidas em projeto | **grava o histórico recente** de cada desvio e assume que o **comportamento futuro seguirá a tendência** |
| 📌 Regras do slide | **"Prediz que o desvio *para trás* é tomado"** · "Prediz que o fluxo normal não é tomado" | quando erra, faz um **stall** enquanto recupera a nova instrução e **atualiza o histórico** |

🎯 **Por que o desvio "para trás" é predito como tomado?** Porque um desvio para trás quase sempre é o **fim de um laço (loop)**, que se repete muitas vezes — então "tomado" acerta na grande maioria das iterações.

🧪 **Relacionar colunas (caiu nas duas provas):**
> **(2) Predição estática de branch** → *"Assume que um branch 'para trás' (loop) é sempre tomado."*

```text
Previsão CORRETA   → nenhuma penalidade, o pipeline segue cheio
Previsão INCORRETA → descarta as instruções buscadas e faz stall
```

---

# Parte 7 — Contas de pipeline (speedup)

**Esta é a parte que mais vale pontos (até 3,0 entre as questões 2 e 3).**

## 7.1 ⭐ As quatro fórmulas

```text
┌──────────────────────────────────────────────────────────────┐
│ 1) PERÍODO DO CLOCK                                          │
│    Monociclo: Tc = SOMA dos estágios                         │
│    Pipeline:  Tc = MAIOR estágio                             │
│                                                              │
│ 2) CICLOS                                                    │
│    Monociclo: ciclos = N                       (1 por instr.)│
│    Pipeline:  ciclos = N + (E − 1) + stalls                  │
│                       onde E = nº de estágios (normalmente 5)│
│                                                              │
│ 3) TEMPO TOTAL = ciclos × Tc                                 │
│    Monociclo: T = N × Tc_mono                                │
│    Pipeline:  T = (N + E − 1) × Tc_pipe                      │
│                                                              │
│ 4) SPEEDUP = T_monociclo / T_pipeline                        │
│    Speedup TEÓRICO (N → ∞) = Tc_mono / Tc_pipe               │
└──────────────────────────────────────────────────────────────┘
```

⚠️ **O `+ (E − 1)` é o enchimento do pipeline** — os 4 ciclos extras até a primeira instrução sair. É o que os alunos mais esquecem.

## 7.2 🧮 Modelo resolvido (o formato exato da questão 3 da prova)

> **Calcule o speedup de um pipeline com 5 estágios (200 ps cada) para 200 instruções, comparando com monociclo (800 ps por instrução). Mostre os cálculos.**

```text
DADOS
  N  = 200 instruções
  E  = 5 estágios
  Tc_pipeline  = 200 ps
  Tc_monociclo = 800 ps

MONOCICLO
  ciclos = N = 200
  T_mono = 200 × 800 = 160.000 ps

PIPELINE
  ciclos = N + (E − 1) = 200 + 4 = 204
  T_pipe = 204 × 200 = 40.800 ps

SPEEDUP
  S = 160.000 / 40.800 ≈ 3,92

SPEEDUP TEÓRICO (limite)
  S = 800 / 200 = 4
```

**Resposta:** o pipeline é **≈ 3,92 vezes mais rápido**. O valor fica **um pouco abaixo de 4** (o speedup ideal) por causa dos **4 ciclos de enchimento** do pipeline.

🎯 **Sempre feche a resposta com essa frase.** É o que o professor quer ver.

## 7.3 🧮 A conta feita no quadro pelo professor

> **Pipeline de 5 estágios (150 ps cada), 50 instruções, monociclo de 900 ps por instrução.**

```text
T_mono = 50 × 900 = 45.000 ps
T_pipe = (50 + 4) × 150 = 54 × 150 = 8.100 ps

SP = 45.000 / 8.100 ≈ 5,5
```

⚠️ Repare que aqui o speedup deu **5,5 — MAIOR que o número de estágios (5)**. Isso acontece porque os estágios **não estavam equilibrados**: o monociclo gastava 900 ps, mas o pipeline só 150 ps por estágio (5 × 150 = 750 < 900). O speedup teórico aqui é `900/150 = 6`.

## 7.4 A regra do equilíbrio

📌 **Slide 04, literal:**

> * Se todos os estágios estiverem **equilibrados** (levam o mesmo tempo) → o speedup tende ao **número de estágios**.
> * **Se não estiverem balanceados, então o speedup é MENOR.**

```text
Estágios equilibrados  →  Speedup ≈ nº de estágios
Estágios desbalanceados →  Speedup < nº de estágios
                            (o gargalo dita o clock e desperdiça os estágios rápidos)
```

## 7.5 🧮 Contando ciclos com stalls

```text
ciclos totais = N + 4 + (nº de stalls)
tempo total   = ciclos × Tc
```

🧮 **Exemplo:** 4 instruções, 1 load-use hazard, Tc = 200 ps.
```text
ciclos = 4 + 4 + 1 = 9 ciclos
tempo  = 9 × 200 = 1800 ps
```

## 7.6 🧮 Alterando o tempo de um estágio (questão 6 da lista)

> **Se o tempo da operação da ALU for reduzido em 25%, isso afetará o ganho do pipeline? E se aumentar 25%?**

Partindo da tabela oficial (IF 200, Reg 100, **ALU 200**, MEM 200, WB 100):

**(a) ALU reduzida em 25% → 200 × 0,75 = 150 ps**

```text
Pipeline:  Tc = max(200, 100, 150, 200, 100) = 200 ps   ← NÃO MUDA!
           (o gargalo continua sendo IF e MEM, com 200 ps)
Monociclo: lw = 200 + 100 + 150 + 200 + 100 = 750 ps    ← melhorou

Speedup: antes 800/200 = 4,00
         agora 750/200 = 3,75   →  o ganho do pipeline DIMINUIU
```

🎯 **Resposta:** o pipeline **não melhora nada**, porque a ALU **não era o gargalo**. Só o monociclo melhora, então o **speedup cai**.

**(b) ALU aumentada em 25% → 200 × 1,25 = 250 ps**

```text
Pipeline:  Tc = max(200, 100, 250, 200, 100) = 250 ps   ← AGORA a ALU é o gargalo
Monociclo: lw = 200 + 100 + 250 + 200 + 100 = 850 ps

Speedup: 850/250 = 3,40   →  o ganho cai ainda mais
```

⚠️ **A lição:** num pipeline, **melhorar um estágio que não é o gargalo não adianta nada**. Só vale a pena acelerar **o estágio mais lento**.

---

# Parte 8 — RISC × CISC

## 8.1 O contexto histórico

📌 **Slide 05_01:**

> Até o fim da década de 1970: memórias **muito lentas** e **caras** → ler instruções era lento → criar instruções que **faziam várias coisas ao mesmo tempo** → operações complexas com **menos bytes**.
>
> Mais para a frente: instruções complexas são **pouco usadas**, o processador ficava **mais lento** em geral, **porque é complexo implementar pipeline**.

📌 A nova proposta surgiu **no início dos anos 80**, nas universidades americanas de **Berkeley e Stanford**.

## 8.2 ⭐ Tabela comparativa

| | **CISC** (*Complex Instruction Set Computer*) | **RISC** (*Reduced Instruction Set Computer*) |
| --- | --- | --- |
| **Instruções** | complexas, demandando número **grande e VARIÁVEL** de ciclos | simples, demandando número **FIXO** de ciclos |
| **Modos de endereçamento** | **diversos** | **poucos e simples** |
| **Formatos de instrução** | **irregular** (tamanho variável) | **regular** (todas do **mesmo tamanho**, ex.: 32 bits) |
| **Acesso à memória** | **diferentes tipos** de instrução podem referenciar a memória | **apenas `load` e `store`** referenciam a memória |
| **Duração de cada fase** | **variável**, em função da complexidade | **fixa**, igual a **um ciclo de máquina** |
| **Pipeline** | **difícil** de implementar | **implementadas com o uso do pipeline** |
| **CPI médio** | **bastante superior a 1** | **próximo de 1** |
| **Unidade de controle** | em geral **microprogramada** | cabeada (hardwired) |
| **Tamanho do código** | **compacto** (poucas instruções) | **maior** (mais instruções) |
| **Exemplos** | Intel 8080, x86 (8088, 80386, Pentium), IBM 360, IBM System/370, DEC VAX, Motorola 68030/68k | Alpha, ARC, **ARM**, AVR, **MIPS**, PA-RISC, PIC, Power Architecture, **SPARC**, RS/6000, **RISC-V** |

📌 **Exemplos de instruções CISC citados no slide:**
```text
CAS  – compare and swap operands
RTR  – return and restore codes
SWAP – swap register words
```

⚠️ **Obs. importante do slide:** *"o número de instruções **não é uma métrica de desempenho**"*. O código RISC tem **mais** instruções, mas cada uma é **muito mais rápida**.

## 8.3 ⭐ Por que RISC-V é melhor para pipelining (questão de 1,0 ponto)

🎯 **Resposta modelo, com as quatro características dos slides:**

> O RISC-V é mais eficiente para pipelining porque foi projetado para que **todos os estágios tenham duração fixa e previsível**, o que é exatamente o que o pipeline exige (todos os estágios precisam caber no mesmo ciclo de clock). As características que permitem isso são:
>
> 1. **Instruções de tamanho fixo** (32 bits): o estágio **IF** sempre busca a mesma quantidade de bytes, em um único ciclo. Em CISC, uma instrução pode ter de 1 a 15 bytes, e o processador só descobre o tamanho **depois** de começar a decodificar.
> 2. **Poucos formatos e campos simétricos**: os registradores ficam sempre na **mesma posição** dentro da instrução, o que permite **ler os registradores antes mesmo de terminar a decodificação** — ID vira um estágio de duração fixa.
> 3. **Arquitetura load/store**: **só `ld`/`sd`/`lw`/`sw` acessam a memória**, então basta **um único estágio MEM**. Se um `add` pudesse acessar a memória, seriam necessários estágios adicionais.
> 4. **Modos de endereçamento simples** (apenas base + deslocamento): o cálculo do endereço é **uma soma**, que cabe no estágio EX.
>
> Consequência: o **CPI fica próximo de 1**, enquanto em CISC fica bem acima de 1.

🎯 **Dois exemplos de instruções RISC-V que facilitam isso** (a prova pede):

```text
add x1, x2, x3     → tipo R, 3 operandos, todos em REGISTRADORES,
                      tamanho fixo, 1 ciclo de ULA, não toca na memória

ld  x9, 64(x22)    → tipo I, ÚNICO modo de endereçamento (base + deslocamento),
                      o acesso à memória fica isolado no estágio MEM
```

## 8.4 🧮 A conta de comparação RISC × CISC

📌 **Slide 05_01 — exercício proposto:**

```text
Tp = Ci × Tc × Ni

Processadores de 3,57 MHz → Tc ≈ 280 ns
CPI do CISC: 10 ciclos por instrução
CPI do RISC:  1 ciclo por instrução

Código CISC: 1.283 instruções
Código RISC: 10.243 instruções (equivalente)
```

**Resolvendo:**

```text
T_cisc = 10 × 280 ns × 1.283  = 3.592.400 ns ≈ 3,59 ms
T_risc =  1 × 280 ns × 10.243 = 2.868.040 ns ≈ 2,87 ms

Speedup (como o slide define):
S = 100 × (T_cisc − T_risc) / T_risc
S = 100 × (3.592.400 − 2.868.040) / 2.868.040
S = 100 × 724.360 / 2.868.040 ≈ 25,3 %
```

**Resposta:** o RISC é cerca de **25% mais rápido**, mesmo executando **8 vezes mais instruções** — porque o CPI é **10 vezes menor**.

⚠️ Note que a fórmula de speedup **deste slide** é diferente da fórmula de speedup de pipeline: aqui o resultado sai em **porcentagem de vantagem**, e não em "quantas vezes mais rápido".

## 8.5 Processadores híbridos

📌 **Slide 05_01:**
> Muitos processadores atuais **misturam** as arquiteturas RISC e CISC, criando o conceito de **arquitetura híbrida**. Alguns são criados em arquitetura **CISC**, mas incorporam **características RISC**.

📌 **Resumo do slide:** *"A arquitetura CISC era dominante inicialmente. Com a melhoria das memórias, as vantagens da CISC se perderam. Uma vez que RISC facilita a melhoria das CPUs, ela é a base de todas as CPUs modernas."*

## 8.6 ISA e RISC-V

📌 **Slide 05_01:**

> **ISA = Instruction Set Architecture** — é o **repertório de instruções** de um computador. Diferentes computadores possuem ISAs diferentes, **mas com muitos aspectos em comum**.
>
> **RISC-V:** ISA RISC **moderna**, introduzida em **2011**.
> * ISA **ABERTA** (uso livre);
> * desenvolvida com base nos **acertos e erros** de ISAs no mercado há mais de 30 anos (x86 e ARM);
> * **mais simples** do que ARM e x86.

---

# Parte 9 — Assembly RISC-V

## 9.1 Registradores

📌 **Slide 05_02:**

> Registradores são **memórias internas ao processador com baixíssimo tempo de acesso**. A arquitetura RISC-V (**RV64I**) provê um conjunto com **32 registradores de 64 bits** cada, para inteiros com e sem sinal.
>
> * ⚠️ O registrador **`x0` é atrelado fisicamente ao valor ZERO**.
> * Além dos de uso geral, há o registrador **`pc`** (armazena o **endereço da próxima instrução**).

## 9.2 ⭐ Instruções aritméticas

| Mnemônico | Instrução | Tipo | Descrição |
| --- | --- | --- | --- |
| `add rd, rs1, rs2` | Soma | **R** | `rd ← rs1 + rs2` |
| `sub rd, rs1, rs2` | Subtração | **R** | `rd ← rs1 − rs2` |
| `addi rd, rs1, imm12` | Soma imediato | **I** | `rd ← rs1 + imm12` |

📌 **Regras de ouro do slide:**

```text
· Cada instrução aritmética executa SOMENTE UMA operação.
· Deve ter EXATAMENTE 3 OPERANDOS.
· O PRIMEIRO operando é SEMPRE o registrador de DESTINO.
```

### ⚠️ Não existe `subi`

📌 **Slide:** *"Não há necessidade de instrução `subi`, pois o imediato em `add` é representado em **complemento a 2** (pode ser negativo)."*

```text
subi rd, rs1, imm12   ≡   addi rd, rs1, -imm12
```

🎯 Para fazer `c = a - 5`:
```c
addi x3, x1, -5     // e NÃO "subi"
```

### Somar mais de 2 operandos

📌 **Exemplo do slide** — `x1 = x2 + x3 + x4 + x5`:
```asm
add x1, x2, x3     // x1 = x2 + x3
add x6, x4, x5     // x6 = x4 + x5
add x1, x1, x6     // x1 = os quatro somados
```

📌 O texto após `//` é um **comentário**, ignorado durante a montagem.

## 9.3 Instruções lógicas e de deslocamento

| Mnemônico | Instrução | Tipo |
| --- | --- | --- |
| `and rd, rs1, rs2` / `andi rd, rs1, imm12` | AND | R / I |
| `or  rd, rs1, rs2` / `ori  rd, rs1, imm12` | OR | R / I |
| `xor rd, rs1, rs2` / `xori rd, rs1, imm12` | XOR | R / I |
| `sll` / `slli` | *Shift Left Logical* | R / I |
| `srl` / `srli` | *Shift Right Logical* | R / I |
| `sra` / `srai` | *Shift Right **Arithmetic*** | R / I |

⚠️ **Obs. do slide:** como o alvo do deslocamento está em um registrador de **64 bits**, não faz sentido permitir `n > 63`. Por isso **somente os primeiros 6 bits do imediato** são realmente utilizados.

🎯 `srl` (lógico) preenche com **zeros**; `sra` (aritmético) **replica o bit de sinal** — usado para dividir números negativos.

## 9.4 ⭐ Acesso à memória

📌 **Slide:** na arquitetura RISC-V a memória é um **grande array de bytes**, onde **cada byte possui seu próprio endereço** de 64 bits.

📌 Como os operandos das operações aritméticas **devem estar em registradores**, precisamos de instruções para movimentar dados entre memória e registradores.

### Tipos de dados

| Nome | Tamanho | Sufixo |
| --- | --- | --- |
| Byte | 1 byte | `b` |
| **Halfword** | 16 bits (2 bytes) | `h` |
| **Word** | 32 bits (4 bytes) | `w` |
| **Doubleword** | 64 bits (8 bytes) | `d` |

### Instruções

📌 Os endereços são expressos na forma **base + deslocamento**, onde a base é um **registrador** e o deslocamento é um **imediato de 12 bits**.

| Mnemônico | Instrução | Tipo | Descrição |
| --- | --- | --- | --- |
| `ld rd, imm12(rs1)` | Load doubleword | I | `rd ← M[rs1 + imm12]` (64 bits) |
| `sd rs2, imm12(rs1)` | Store doubleword | **S** | `M[rs1 + imm12] ← rs2` |
| `lw rd, imm12(rs1)` | Load word | I | `rd ← SE64(M[rs1 + imm12])` (32 bits, **com extensão de sinal**) |
| `lwu rd, imm12(rs1)` | Load word unsigned | I | sem extensão de sinal |
| `sw rs2, imm12(rs1)` | Store word | S | grava os 32 bits menos significativos |
| `lh` / `lhu` / `sh` | Halfword | I / S | 16 bits |

```text
ld x9, 64(x22)     →   x9 = conteúdo da memória no endereço (x22 + 64)
sd x9, 96(x22)     →   memória[x22 + 96] = x9
```

⚠️ **`SE64` = extensão de sinal.** `lw` estende o sinal; `lwu` não. Isso importa para números negativos.

### ⭐ Arrays — a pegadinha do deslocamento

📌 **Exemplo do slide:** `g = h + a[8]`, com `h` em `x21` e a **base do array `a` de doublewords** em `x22`.

❌ **Errado:**
```asm
ld  x9, 8(x22)       // isso acessa o BYTE 8, não o ELEMENTO 8!
add x20, x21, x9
```

✅ **Certo:**
```asm
ld  x9, 64(x22)      // 8 elementos × 8 bytes = 64
add x20, x21, x9
```

📌 **Explicação literal do slide:**
> Cada elemento do array é um **doubleword**. Do elemento `a[7]` para `a[8]` temos uma distância de **8 endereços (8 bytes)**. Portanto, de `a[0]` para `a[8]` temos **8 × 8 = 64 endereços**.

🎯 **A regra:**
```text
deslocamento = índice × tamanho do elemento em BYTES

doubleword (ld/sd) → índice × 8
word       (lw/sw) → índice × 4
halfword   (lh/sh) → índice × 2
byte                → índice × 1
```

### Endianness

📌 **Slide:**
> * **Big-endian:** os bytes **mais** significativos são armazenados nos endereços **mais baixos**.
> * **Little-endian:** os bytes **menos** significativos são armazenados nos endereços mais baixos.
>
> ⭐ **A arquitetura RISC-V segue a abordagem *little-endian*, assim como a x86-64.**

```text
Valor 10 = 0x000000000000000A

  BIG-ENDIAN                      LITTLE-ENDIAN
  end. 0x00 → 00                  end. 0x00 → 0A   ← o byte menos significativo
  end. 0x01 → 00                  end. 0x01 → 00      vem primeiro
  ...                             ...
  end. 0x07 → 0A                  end. 0x07 → 00
```

## 9.5 Instruções de decisão (branches)

| Instrução | Condição | Tipo | Descrição |
| --- | --- | --- | --- |
| `beq rs1, rs2, L1` | `rs1 == rs2` | SB | desvia para `L1` se **iguais** |
| `bne rs1, rs2, L1` | `rs1 != rs2` | SB | desvia se **diferentes** |
| `blt rs1, rs2, L1` | `rs1 < rs2` | SB | desvia se **menor** |
| `bltu rs1, rs2, L1` | `rs1 < rs2` | SB | idem, valores **sem sinal** |
| `bge rs1, rs2, L1` | `rs1 >= rs2` | SB | desvia se **maior ou igual** |
| `bgeu rs1, rs2, L1` | `rs1 >= rs2` | SB | idem, **sem sinal** |

⚠️ Não existem `bgt` nem `ble` no conjunto básico — **inverta a ordem dos operandos**:
```text
"rs1 > rs2"  →  blt rs2, rs1, L1
"rs1 <= rs2" →  bge rs2, rs1, L1
```

## 9.6 ⭐ Receita para compilar C → RISC-V

```text
1. Identifique QUAL registrador guarda cada variável (o enunciado sempre diz).
2. Quebre a expressão em operações de NO MÁXIMO 2 operandos cada.
3. Resolva PRIMEIRO os parênteses, guardando cada resultado em um
   registrador TEMPORÁRIO (use os registradores livres, ex.: x5, x6, x7...).
4. A última instrução é a que escreve no registrador de DESTINO final.
5. Constante no código?  →  use addi (e para subtrair, addi com NEGATIVO).
6. Array?  →  ld/sd, com deslocamento = índice × tamanho do elemento.
```

🧪 **Exemplo do slide:** `f = (g + h) − (i + j)`, com `f,g,h,i,j` = `x1,x2,x3,x4,x5`:
```asm
add x6, x2, x3     // x6 = g + h
add x7, x4, x5     // x7 = i + j
sub x1, x6, x7     // f  = x6 − x7
```

🧪 **Questão que caiu nas DUAS provas:** `p = (q + r) − (s + t)`, com `p,q,r,s,t` = `x6,x7,x8,x9,x10`:
```asm
add x11, x7, x8     // x11 = q + r
add x12, x9, x10    // x12 = s + t
sub x6,  x11, x12   // p   = (q+r) − (s+t)
```

🧪 **Lista, Seção 3:** `a = b + c; c = a − 5;` com `a,b,c` = `x1,x2,x3`:
```asm
add  x1, x2, x3     // a = b + c
addi x3, x1, -5     // c = a - 5   (addi com imediato NEGATIVO)
```

---

# Parte 10 — Checklist e colinha final

## ✅ Checklist da véspera

**Conceitos**
- [ ] **Arquitetura** = visível ao programador (ISA, modos de endereçamento, n.º de bits); **Organização/Microarquitetura** = implementação (cache, clock, pipeline).
- [ ] ⚠️ "Arquitetura define **apenas** o conjunto de instruções" é **FALSO**.
- [ ] **Von Neumann** = memória única; **Harvard** = memórias separadas (necessário para o pipeline).
- [ ] **Paralelismo temporal** = pipeline (mesmo hardware, estágios diferentes); **espacial** = multicore/GPU.
- [ ] Pipeline aumenta a **VAZÃO**, **não** reduz a **latência** de uma instrução.

**Pipeline**
- [ ] Os 5 estágios: **IF · ID · EX · MEM · WB**.
- [ ] `IF` busca · `ID` decodifica e **lê registradores** · `EX` ULA/endereço · `MEM` só load/store · `WB` escreve no registrador.
- [ ] **Monociclo: Tc = SOMA** dos estágios. **Pipeline: Tc = MAIOR** estágio.
- [ ] No monociclo, o clock é ditado pela instrução **mais lenta** (`lw` = 800 ps na tabela padrão).
- [ ] `ciclos_pipeline = N + 4 + stalls`.
- [ ] `Speedup = T_mono / T_pipe`; o **teórico** é `Tc_mono / Tc_pipe`.
- [ ] Estágios **equilibrados** → speedup ≈ n.º de estágios. **Desbalanceados** → speedup **menor**.
- [ ] Melhorar um estágio que **não é o gargalo** não muda o Tc do pipeline.

**Hazards**
- [ ] **Estrutural** → conflito de **recurso** (memória única) → solução: **duplicar o recurso**.
- [ ] **De dados** → instrução depende do resultado de outra → solução: **forwarding**.
- [ ] **De controle** → **desvio** (branch) → solução: **previsão de desvio**.
- [ ] **Forwarding** = usar o resultado **assim que é calculado**, sem esperar o WB.
- [ ] ⚠️ **Forwarding NÃO elimina o load-use hazard** → sempre **1 stall**.
- [ ] No `lw`, o dado só existe **depois do 4º estágio (MEM)**.
- [ ] **Reordenação de código** (feita pelo compilador) também evita stalls.
- [ ] Distância 1 → `EX/MEM → EX`. Distância 2 → `MEM/WB → EX`. Distância ≥ 3 → sem hazard.

**Previsão de desvios**
- [ ] **Estática** = regra fixa; **"desvio para trás (loop) é tomado"**.
- [ ] **Dinâmica** = hardware **grava o histórico** de cada desvio.
- [ ] Acertou → sem penalidade. Errou → **stall** e atualiza o histórico.

**RISC × CISC**
- [ ] RISC: instruções **simples**, tamanho **fixo**, **poucos formatos**, **só load/store** acessam memória, fase de **duração fixa**, **CPI ≈ 1**, feito **para pipeline**.
- [ ] CISC: instruções **complexas**, tamanho **variável**, **muitos** modos de endereçamento, **CPI >> 1**, controle **microprogramado**, pipeline **difícil**.
- [ ] Código RISC tem **mais instruções**, mas o **n.º de instruções não é métrica de desempenho**.
- [ ] `Tp = Ci × Tc × Ni`.
- [ ] RISC-V: ISA **aberta**, de **2011**, **RV64I** com **32 registradores de 64 bits**, **`x0` = zero**.

**Assembly**
- [ ] Aritmética: **exatamente 3 operandos**, o **primeiro é o destino**.
- [ ] **Não existe `subi`** → use `addi` com imediato **negativo**.
- [ ] `ld`/`sd` = doubleword (8 bytes) · `lw`/`sw` = word (4 bytes).
- [ ] Endereço = **base(registrador) + deslocamento(imediato de 12 bits)**.
- [ ] Array: **deslocamento = índice × tamanho do elemento em bytes**.
- [ ] RISC-V é **little-endian**.

---

## 🧭 Colinha final

```text
═══ PIPELINE ═══════════════════════════════════════════════════
IF → ID → EX → MEM → WB

Tc monociclo = SOMA dos estágios      Tc pipeline = MAIOR estágio
ciclos pipeline = N + (E − 1) + stalls        (E = 5 → N + 4)
Tempo = ciclos × Tc
Speedup = T_mono / T_pipe         Speedup teórico = Tc_mono / Tc_pipe

Tabela padrão:  IF 200 · Reg 100 · ULA 200 · MEM 200 · WB 100
  lw 800 · sw 700 · R-format 600 · beq 500     → mono 800, pipe 200

═══ HAZARDS ════════════════════════════════════════════════════
ESTRUTURAL → recurso ocupado (memória única)  → duplicar recurso
DE DADOS   → depende de resultado anterior     → FORWARDING
DE CONTROLE→ desvio (branch)                   → PREVISÃO

forwarding: dist 1 → EX/MEM→EX · dist 2 → MEM/WB→EX · dist 3+ → ok
LOAD-USE   → 1 STALL obrigatório (+ forwarding MEM/WB→EX)
sem forwarding → 2 stalls por hazard

═══ RISC vs CISC ═══════════════════════════════════════════════
RISC: tamanho FIXO · poucos formatos · só load/store na memória
      fase de duração FIXA · CPI ≈ 1 · feito para PIPELINE
CISC: tamanho VARIÁVEL · muitos modos · CPI >> 1 · microprogramado

Tp = Ci × Tc × Ni        S% = 100 × (Tcisc − Trisc) / Trisc

═══ RISC-V ═════════════════════════════════════════════════════
32 registradores de 64 bits · x0 = ZERO · little-endian
add/sub rd,rs1,rs2 · addi rd,rs1,imm (sem subi: use imm negativo)
ld/sd (8 bytes) · lw/sw (4 bytes) · desloc = índice × tamanho
beq bne blt bge (bltu bgeu sem sinal) · não há bgt/ble

(g+h)−(i+j):   add x6,x2,x3 / add x7,x4,x5 / sub x1,x6,x7
```

---

## 📚 Bibliografia dos slides

* **PATTERSON, D. A.; HENNESSY, J.** *Arquitetura de Computadores — Uma Abordagem Quantitativa.* 5ª ed. Campus/Elsevier, 2013. — **a fonte das tabelas de pipeline e dos exercícios de speedup**
* **HENNESSY, J.; PATTERSON, D. A.** *Organização e Projeto de Computadores: A Interface Hardware/Software.* 5ª ed. Elsevier, 2017. — **a fonte do assembly RISC-V**
* **STALLINGS, W.** *Arquitetura e Organização de Computadores.* 8ª ed. Pearson, 2010. — **Capítulo 1 é leitura recomendada pelo professor**
* TANENBAUM, A. S. *Organização Estruturada de Computadores.* 5ª ed. Prentice-Hall, 2006.
* MURDOCCA, M. J.; HEURING, V. P. *Introdução à Arquitetura de Computadores.* Campus/Elsevier, 2000.
