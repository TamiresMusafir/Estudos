# 🎯 APS — Análise e Projeto de Sistemas (CEFET/RJ)
## Material de prova — conceitos dos slides, com foco em **Diagramas de Interação**

> Baseado nos slides da Profa. Carmen Lucia Asp de Queiroz (APS 1a, 1b, 1c — Classes de Análise; 2 — Transição de Estado; 3a — Diagramas de Interação) e nas provas P1 de 2025.1, 2025.2 e 2026.1.
>
> **Legenda:** ⚠️ **Pegadinha de concurso** · 🎯 **Cai muito** · 📌 **Definição literal do slide** · 🧪 **Já caiu em prova**

---

## 📑 Sumário

* [Parte 0 — Mapa da matéria e o que mais cai](#parte-0--mapa-da-matéria-e-o-que-mais-cai)
* [**Parte 1 — DIAGRAMAS DE INTERAÇÃO (foco da prova)**](#parte-1--diagramas-de-interação-foco-da-prova)
  * [1.1 O que é uma interação](#11-o-que-é-uma-interação)
  * [1.2 Os quatro tipos de diagrama de interação](#12-os-quatro-tipos-de-diagrama-de-interação)
  * [1.3 Diagrama de Sequência — elementos básicos](#13-diagrama-de-sequência--elementos-básicos)
  * [1.4 Mensagens — os três tipos de seta](#14-mensagens--os-três-tipos-de-seta)
  * [1.5 Criação e destruição de objetos](#15-criação-e-destruição-de-objetos)
  * [1.6 Foco de controle (ativação)](#16-foco-de-controle-ativação)
  * [1.7 Sentinelas e marcador de iteração](#17-sentinelas-e-marcador-de-iteração)
  * [1.8 ⭐ Quadros de interação (fragmentos combinados)](#18--quadros-de-interação-fragmentos-combinados)
  * [1.9 Diagrama de Sequência do Sistema (DSS)](#19-diagrama-de-sequência-do-sistema-dss)
  * [1.10 Diagrama de Comunicação](#110-diagrama-de-comunicação)
  * [1.11 Sequência × Comunicação](#111-sequência--comunicação)
  * [1.12 Diagrama de Visão Geral da Interação](#112-diagrama-de-visão-geral-da-interação)
  * [1.13 Diagrama de Temporização](#113-diagrama-de-temporização)
  * [1.14 Pegadinhas de concurso — Interação](#114-pegadinhas-de-concurso--interação)
* [Parte 2 — Diagrama de Transição de Estado (DTE)](#parte-2--diagrama-de-transição-de-estado-dte)
* [Parte 3 — Diagrama de Classes de Análise](#parte-3--diagrama-de-classes-de-análise)
* [Parte 4 — Padrões de Análise (Party e Metamodel)](#parte-4--padrões-de-análise-party-e-metamodel)
* [Parte 5 — GRASP (caiu na prova, não está nos slides)](#parte-5--grasp-caiu-na-prova-não-está-nos-slides)
* [Parte 6 — Questões de provas anteriores, resolvidas](#parte-6--questões-de-provas-anteriores-resolvidas)
* [Parte 7 — Checklist final da véspera](#parte-7--checklist-final-da-véspera)

---

# Parte 0 — Mapa da matéria e o que mais cai

A UML divide os diagramas em duas visões. Saber em qual visão cada diagrama está resolve metade das questões de concurso:

```text
                        DIAGRAMAS DA UML
                               │
          ┌────────────────────┴────────────────────┐
          │                                         │
   ESTRUTURAL (estático)                    COMPORTAMENTAL (dinâmico)
   "como o sistema é feito"                 "como o sistema se comporta"
          │                                         │
   ┌──────┴──────┐                    ┌─────────────┼──────────────┐
   │             │                    │             │              │
Diagrama de   Diagrama de        Casos de Uso   Atividades    Máquina de Estados
 Classes       Objetos                                         (DTE)
                                                 │
                                          DIAGRAMAS DE INTERAÇÃO
                                                 │
                        ┌────────────┬───────────┴────────┬──────────────┐
                    Sequência   Comunicação        Visão Geral      Temporização
                                (colaboração)     da Interação
```

📌 **Slide 2 (Classes):** a colaboração entre objetos pode ser vista sob dois aspectos.

| Aspecto | O que descreve | Diagrama |
| --- | --- | --- |
| **Dinâmico** | a troca de mensagens entre os objetos e a reação a eventos | Diagramas de Interação, DTE |
| **Estrutural estático** | como o sistema está estruturado para produzir as funcionalidades visíveis | **Diagrama de Classes** |

### O que cai, por peso (com base nas 3 provas analisadas)

| Assunto | Formato típico | Peso |
| --- | --- | --- |
| Diagrama de Classes (minimundo) | discursiva — modelo conceitual | ~4 a 5 pontos |
| DTE (minimundo) | discursiva — DTE de uma classe | ~2,5 a 3 pontos |
| **DSS / Diagrama de Sequência** | discursiva — a partir de um caso de uso | ~1,5 ponto |
| Questões de concurso (V/F, múltipla escolha, associação) | objetivas | ~2 a 3 pontos |

---

# Parte 1 — DIAGRAMAS DE INTERAÇÃO (foco da prova)

## 1.1 O que é uma interação

📌 **Definição do slide 2:**

> Diagrama de Interação é um **termo genérico** que se aplica a vários tipos de diagramas que enfatizam **interações de objetos**.
>
> Uma **interação** é uma especificação comportamental que inclui uma **sequência de trocas de mensagens** entre um **conjunto de objetos** dentro de um **contexto** para realizar um **propósito específico**, tal como a realização de um caso de uso.

Quebrando a definição nos quatro elementos que a compõem (isso vira item de prova):

```text
INTERAÇÃO = sequência de mensagens
          + conjunto de objetos
          + um contexto definido
          + um propósito específico (ex.: realizar um caso de uso)
```

Para especificar uma interação é necessário:
1. **definir um contexto** — se é um sistema, um subsistema, uma operação ou um cenário de caso de uso;
2. **estabelecer os objetos** que interagem e seus **relacionamentos**.

📌 O diagrama de interação deve ser usado **quando se deseja visualizar o comportamento de vários objetos dentro do contexto estabelecido**.

📌 **Slide 3:** o conjunto de **todos** os diagramas de interação de um sistema constitui o **modelo de interações** do sistema.

🎯 **Ligação com o diagrama de classes (slide 7):**

> A atividade de modelagem de interações **gera informações para completar o modelo de classes** construído na etapa de análise.

```text
mensagem enviada a um objeto  →  responsabilidade daquele objeto
                              →  vira uma OPERAÇÃO na classe dele
```

Ou seja: os diagramas de interação **descobrem os métodos** das classes. Quem recebe a mensagem é quem precisa ter a operação.

---

## 1.2 Os quatro tipos de diagrama de interação

📌 **Slide 3** — decorar esta tabela, é a que mais cai em associação de colunas:

| Diagrama | A ênfase está em... |
| --- | --- |
| **Sequência** | a **ordem temporal** das mensagens trocadas entre os objetos |
| **Comunicação** (ou colaboração) | os **relacionamentos** entre os objetos que participam da realização de um caso de uso |
| **Visão Geral da Interação** | diagramas de atividades nos quais as **atividades são substituídas por pequenos diagramas de sequência** |
| **Temporização** | as **restrições de temporização** (tempo) |

🎯 **Palavra-chave de cada um** (é assim que a banca pergunta):

```text
Sequência     → TEMPO / ORDEM TEMPORAL / linha de vida
Comunicação   → ESTRUTURA / RELACIONAMENTOS / numeração
Visão Geral   → FLUXO DE CONTROLE / atividades + sequência
Temporização  → RESTRIÇÕES DE TEMPO / engenharia eletrônica
```

⚠️ **Cuidado com o par mais confundido:**

| | Diagrama de Comunicação | Diagrama de **Classes** |
| --- | --- | --- |
| Enfatiza relacionamentos entre... | **objetos** (instâncias) que trocam mensagens | **classes** (estrutura estática) |
| Visão | dinâmica | estática |

⚠️ E o erro clássico: **"retrato, em tempo de execução, dos objetos existentes no software e dos seus relacionamentos"** → isso é o **Diagrama de Objetos**, e **não** o de estados nem o de sequência. Essa frase já foi usada como item **FALSO** em duas provas diferentes.

---

## 1.3 Diagrama de Sequência — elementos básicos

### A dimensão do tempo

📌 **Slide 6:**

> A passagem do tempo é percebida observando-se a **direção vertical, no sentido de cima para baixo**. Quanto mais abaixo uma mensagem aparece, **mais tarde no tempo** ela foi enviada.

```text
        ator          :Objeto1        :Objeto2
         │               │               │
    ╔════╧════╗     ╔════╧════╗     ╔════╧════╗   ← retângulos = objetos
    ║         ║     ║         ║     ║         ║
    ╚════╤════╝     ╚════╤════╝     ╚════╤════╝
         ┆               ┆               ┆
         ┆──msg1()──────►▓               ┆        ↓
         ┆               ▓──msg2()──────►▓        │  T
         ┆               ▓               ▓        │  E
         ┆               ▓◄- - retorno - ▓        │  M
         ┆◄- - - - - - - ▓               ┆        │  P
         ┆               ┆               ┆        ↓  O
      linha de        foco de
        vida          controle
     (tracejada)     (retângulo)
```

⚠️ **Slide 8 — pegadinha certa:**

> A **ordem horizontal** na qual os objetos aparecem no diagrama de sequência **NÃO tem nenhum significado pré-definido**.

Só a **vertical** carrega semântica (tempo). Mesmo assim, o slide 6 recomenda: *"deve-se tentar arrumar os objetos de acordo com a ordem na qual as mensagens são enviadas e **minimizar o cruzamento** de setas de mensagens com linhas de vida"* — é boa prática, não regra.

### Os participantes

| Elemento | Notação | Observação do slide |
| --- | --- | --- |
| **Ator** | boneco palito | **Opcionalmente** os atores que participam da realização do caso de uso podem ser representados |
| **Objeto anônimo** | `:ItemPedido` | usado quando não precisa ser referenciado |
| **Objeto nomeado** | `item:ItemPedido` | usado quando o objeto **precisa ser referenciado em mais de um lugar**; o nome é separado do nome da classe por **dois-pontos** |
| **Classe** | `ItemPedido` (nome **não sublinhado**) | a própria classe (e não o objeto) atende a mensagem |
| **Linha de vida** | linha vertical **tracejada** | cada objeto aparece no topo de uma linha de vida |

🎯 **Objeto × Classe no diagrama de sequência (slide 9):**

```text
Objeto  →  nome SUBLINHADO      → item:ItemPedido
Classe  →  nome NÃO sublinhado  → ItemPedido
```

📌 Por que uma **classe** participaria de um diagrama de interação?

> A participação de uma classe se justifica pelo fato de a **própria classe (e não o objeto)** poder atender a mensagem. Uma mensagem para uma classe dispara a execução de uma **operação estática**.

---

## 1.4 Mensagens — os três tipos de seta

📌 **Slide 10:** a notação para uma mensagem é uma **flecha horizontal** ligando uma linha de vida a outra. **O formato da ponta da seta indica o tipo de mensagem.**

| Tipo | Seta | Significado (literal do slide) |
| --- | --- | --- |
| **Síncrona** | ───────▶ (ponta **cheia/preenchida**) | o chamador **deve esperar** até que a mensagem seja concluída |
| **Assíncrona** | ───────➤ (ponta **aberta**, meia-seta) | o chamador **pode continuar** o processamento e **não precisa esperar** por uma resposta |
| **Retorno** | ‑ ‑ ‑ ‑ ▶ (linha **tracejada**) | especifica o **retorno (término)** de uma mensagem enviada anteriormente |

🎯 **Macete visual:**

```text
ponta CHEIA     = SÍNCRONA   = "eu espero"     (chamada de método normal)
ponta ABERTA    = ASSÍNCRONA = "eu não espero" (dispara e segue)
linha TRACEJADA = RETORNO
```

### Mensagem reflexiva

📌 **Slide 10:**

> Um objeto pode enviar uma mensagem para ativar uma operação **definida em sua própria classe** (ou eventualmente em alguma de suas superclasses). Quando isso ocorre, diz-se que o objeto está enviando uma **mensagem reflexiva**.

```text
    :Pedido
       │
       ▓──┐
       ▓  │ calcularTotal()   ← a seta sai e volta para a MESMA linha de vida
       ▓◄─┘
       ▓▓  ← provoca focos de controle EMPILHADOS
```

⚠️ Não confunda **mensagem reflexiva** (diagrama de sequência, objeto chama a si mesmo) com **associação reflexiva** (diagrama de classes, classe se associa a si mesma).

---

## 1.5 Criação e destruição de objetos

📌 **Slide 11 — Criação:**

> Para criar um objeto você desenha a **seta de mensagem diretamente para a caixa do objeto**. Se o objeto existe desde o início da interação, ele deve ser posicionado **no topo** do diagrama. Se o objeto é criado em um momento posterior, o seu retângulo deve ser posicionado **mais abaixo** no diagrama.

```text
  :Controlador
       │
       ▓                        ╔═══════════╗
       ▓─────create()──────────►║  :Pedido  ║   ← retângulo mais ABAIXO
       ▓                        ╚═════╤═════╝      = objeto criado durante a interação
       ▓                              ┆
```

📌 **Slide 12 — Destruição:**

> A destruição de um objeto é representada por um **X grande**. Um objeto normalmente é destruído quando **não é mais necessário na interação**.

```text
       ▓─────destroy()─────────►▓
                                ▓
                                ╳   ← X grande no fim da linha de vida
```

🎯 **Regra de leitura para prova:**

```text
retângulo do objeto NO TOPO      → o objeto já existia antes da interação começar
retângulo do objeto MAIS ABAIXO  → o objeto FOI CRIADO durante a interação
X no fim da linha de vida        → o objeto foi DESTRUÍDO
```

🧪 Isso já caiu: *"O diagrama apresenta a criação de um objeto"* — a resposta era **FALSA**, porque todos os participantes estavam alinhados no topo.

---

## 1.6 Foco de controle (ativação)

📌 **Slide 13:**

> Focos de controle correspondem a **blocos retangulares** posicionados **sobre a linha de vida** de um objeto. Um foco de controle representa **o tempo em que um objeto realiza uma ação**.
>
> - O **topo** do foco de controle coincide com o **recebimento de uma mensagem**.
> - A **parte de baixo** coincide com o **término de uma operação** realizada pelo objeto.
>
> **Chamadas recursivas provocam barras de foco de controle empilhadas.**

```text
   :Objeto
      ┆
   ───▓  ← topo: chegou a mensagem
      ▓
      ▓▓ ← empilhado: chamada recursiva / reflexiva
      ▓
      ┆  ← fim: a operação terminou
```

---

## 1.7 Sentinelas e marcador de iteração

📌 **Slide 14:**

| Recurso | Notação | Significado |
| --- | --- | --- |
| **Sentinela** (condição de guarda) | `[expressão]` entre **colchetes** | a mensagem **só é enviada se a sentinela for verdadeira** |
| **Marcador de iteração** | `*` antes do nome da mensagem | a mensagem se repete; pode-se acrescentar `[base da iteração]` entre colchetes |

```text
[saldo > 0] sacar(valor)          ← sentinela
*[para cada item] calcular()      ← iteração
```

⚠️ **Observação literal do slide 14, que vira questão:**

> Embora os marcadores de iteração possam ajudar, eles **têm suas fraquezas**. Por esse motivo, a **UML 2 oferece os quadros de interação**.

Ou seja: sentinela + asterisco é a notação **antiga (UML 1)**; a forma moderna é usar **fragmentos combinados** (`alt`, `opt`, `loop`).

---

## 1.8 ⭐ Quadros de interação (fragmentos combinados)

**Este é o tópico que mais cai em questão de concurso sobre diagrama de sequência.**

📌 **Slide 15 — a tabela dos operadores (decorar na íntegra):**

| Operador | Significado (literal do slide) |
| --- | --- |
| **`alt`** | Múltiplos fragmentos **alternativos**; somente aquele cuja condição for verdadeira será executado |
| **`opt`** | **Opcional**; o fragmento é executado **se e somente se** a condição fornecida for verdadeira. **Equivalente a um `alt` com apenas um caminho** |
| **`par`** | **Paralelo**; cada fragmento é executado em paralelo |
| **`loop`** | **Laço**; o fragmento pode ser executado várias vezes e a **sentinela indica a base da iteração** |
| **`sd`** | **Diagrama de sequência**; usado para circundar um diagrama de sequência **inteiro**, se você quiser |
| **`ref`** | **Referência**; refere-se a uma interação definida em **outro diagrama**. O quadro é desenhado de forma a abordar as linhas de vida envolvidas. **Pode definir parâmetros e um valor de retorno** |
| **`break`** | **Interrompe** a execução |

### Como o quadro é desenhado

```text
┌──────────────────────────────────────┐
│ alt ╲                                │  ← operador no canto superior esquerdo,
├──────╲───────────────────────────────┤     dentro do "pentágono"
│  [saldo >= valor]                    │  ← sentinela do 1º fragmento
│       ▓────sacar()────►▓             │
│ - - - - - - - - - - - - - - - - - - -│  ← linha tracejada SEPARA os operandos
│  [else]                              │
│       ▓──recusar()────►▓             │
└──────────────────────────────────────┘
```

🎯 **Os três detalhes que a banca explora:**

1. **`alt` × `opt`** — `alt` tem **vários** caminhos alternativos separados por linha tracejada; `opt` tem **um só** caminho, que executa ou não. Por isso o slide diz que `opt` é *"equivalente a um alt com apenas um caminho"*.
2. **Quadros aninhados** — um `opt` dentro de outro `opt` significa que a mensagem interna só é enviada se **as duas condições forem verdadeiras ao mesmo tempo**.
3. **Quem avalia a condição** — a condição de guarda é avaliada sobre a linha de vida em que o quadro se apoia; a responsabilidade de fornecer aquele valor é do objeto que executa a mensagem anterior.

🧪 **Questão real (FEPESE — adaptada):** um diagrama com dois `opt` aninhados, condições `[conectado]` e `[êxito]`.
→ *"A sexta mensagem só será enviada se 'conectado' e 'êxito' apresentarem (ambos) valor true"* = **VERDADEIRO**, exatamente pelo aninhamento.

---

## 1.9 Diagrama de Sequência do Sistema (DSS)

É o formato cobrado nas questões **discursivas** ("com base na descrição do caso de uso, construa o diagrama de sequência do sistema").

📌 **Slide 5:**

> É uma especificação **do que o sistema faz, sem explicar como** ele o faz. O comportamento é definido como uma **"caixa preta"**. O comportamento é **dependente dos casos de uso**.

📌 **Slide 16:**

> Diagramas de Sequência do Sistema (DSS) mostram um **cenário global** do funcionamento do sistema, dividindo o caso de uso em partes bem definidas denominadas **operações de sistema**, que são executadas **em resposta aos eventos**.
>
> De acordo com o **Processo Unificado**, deve-se criar um **DSS para cada caso de uso relevante**.

### A estrutura do DSS

```text
      Ator                      :Sistema      ← UMA única caixa preta chamada "Sistema"
       │                            │
       ┆───operacaoDeSistema()─────►▓
       ┆◄- - - -resposta- - - - - - ▓
```

| Elemento | No DSS |
| --- | --- |
| Participantes | **o ator** e **`:Sistema`** (só isso — nada de objetos internos) |
| Mensagens do ator → sistema | **operações de sistema**, tiradas dos passos do ator no fluxo principal |
| Mensagens do sistema → ator | **retornos** (linha tracejada), com o que o sistema informa/apresenta |

### 🎯 Receita para montar o DSS a partir do caso de uso

```text
1. Leia o fluxo principal e separe QUEM faz cada passo.
2. Passo do ATOR         → vira uma MENSAGEM  ator ──► :Sistema
   (verbo + dado)          ex.: "O gerente informa o CPF" → identificarConsultor(CPF)
3. Passo do SISTEMA      → vira um RETORNO    :Sistema - -► ator
   (apresenta/informa)     ex.: "O sistema apresenta a lista" → listaPedidos
4. Fluxo de EXCEÇÃO      → vira um quadro opt/alt com a condição NEGADA da exceção
   (FE01, FE02...)         ex.: FE01 "não existem pedidos" → opt [existem pedidos]
5. Passo que se repete   → vira um quadro loop [base da iteração]
   ("para cada...")
```

🧪 **Exemplo real do slide 17 — Caso de uso "Emprestar Livros":**

```text
   Atendente                                   :Sistema
       │                                           │
       ┆──────identificarLeitor(idLeitor)─────────►▓
       ┆◄- - - - - -situacaoLeitor - - - - - - - - ▓
  ┌────────────────────────────────────────────────────┐
  │ opt ╲  [Se situação do leitor = Ok]                │
  │ ┌──────────────────────────────────────────────┐   │
  │ │ loop ╲  [Para cada livro do empréstimo]      │   │
  │ │    ┆───────entrarLivro(idLivro)─────────────►▓   │
  │ │                                                  │
  │ └──────────────────────────────────────────────┘   │
  │      ┆───────encerrarEmprestimo()──────────────►▓   │
  │      ┆◄- - - ReciboEmprestimo, dataDevolucao - -▓   │
  └────────────────────────────────────────────────────┘
```

🧪 **Exemplo real da P1 2025.1 — "Registrar responsabilidade por um pedido de serviço":**

Fluxo: 1) sistema apresenta lista (FE01) · 2) gerente escolhe o pedido · 3) sistema solicita CPF · 4) gerente informa CPF (FE02)(FE03) · 5) gerente confirma · 6) sistema registra.

Gabarito:

```text
   Gerente                                :Sistema
  ┌──────────────────────────────────────────────────┐
  │ opt ╲ [existem pedidos a atribuir responsabilidade]
  │     ┆────1: escolherPedido()───────────────────►▓
  │     ┆────2: identificarConsultor(CPF)──────────►▓
  │  ┌────────────────────────────────────────────┐ │
  │  │ opt ╲ [consultor existente e apto]         │ │
  │  │  ┆────3: confirmar()──────────────────────►▓ │
  │  └────────────────────────────────────────────┘ │
  └──────────────────────────────────────────────────┘
```

⚠️ **Três coisas que o gabarito mostra e que valem pontos:**
1. Os passos **"o sistema solicita o CPF"** e **"o sistema registra"** **não viraram mensagens separadas** — são comportamento interno da caixa preta.
2. Cada **fluxo de exceção** virou um `opt` com a **condição invertida** (FE01 "não existem pedidos" → `opt [existem pedidos]`).
3. As exceções que ocorrem no mesmo passo (FE02 e FE03) foram agrupadas em **um único `opt`** (`[consultor existente e apto]`).

---

## 1.10 Diagrama de Comunicação

Também chamado de **diagrama de colaboração** (nome na UML 1).

📌 **Slide 19** — em vez de desenhar cada participante como uma linha de vida e mostrar a sequência pela direção vertical, o diagrama de comunicação:

* permite **livre posicionamento** dos participantes;
* permite desenhar **vínculos** (links) para mostrar como eles se conectam;
* usa **numeração** para mostrar a sequência das mensagens.

📌 Assim como nos diagramas de sequência, pode conter: objetos nomeados, objetos anônimos, objetos que representam **coleções** e **referências para elementos de uma coleção**.

### ⭐ A numeração das mensagens

📌 **Slide 20 — as duas regras:**

> * **Não numere a mensagem inicial.** É legal fazê-lo, mas simplifica a numeração geral se você não o fizer.
> * Como os diagramas de comunicação **não mostram o tempo como uma dimensão separada**, **TODAS as mensagens devem conter expressões de sequência**.

🎯 A numeração é **decimal aninhada**: `1`, `1.1`, `1.2`, `2`, `2.1`, `2.2`... O nível de aninhamento indica **quem chamou quem**.

🧪 **Exemplo do slide 21 — leia a ordem de execução:**

```text
        msg1               1: msg2
   ──────────► :A ───────────────────► :B
                │                        │
                │                        │ 1.1: msg3  ↓
                │                        │ 2.1: msg5  ↑
                │      2: msg4           │
                └───────────────────────► :C
                                          │
                                          │ 2.2: msg6  ↓
                                         :D
```

| Ordem | Mensagem | Número | Quem chama → quem |
| --- | --- | --- | --- |
| 1º | `msg1` | **sem número** (inicial) | ator → `:A` |
| 2º | `msg2` | `1:` | `:A` → `:B` |
| 3º | `msg3` | `1.1:` | `:B` → (aninhada dentro de msg2) |
| 4º | `msg4` | `2:` | `:A` → `:C` |
| 5º | `msg5` | `2.1:` | aninhada dentro de msg4 |
| 6º | `msg6` | `2.2:` | aninhada dentro de msg4 |

⚠️ **Leitura correta:** `1.1` vem **antes** de `2`, porque `1.1` está **dentro** de `1`. Primeiro termina tudo que está aninhado em `1`, depois começa o `2`.

---

## 1.11 Sequência × Comunicação

📌 **Slide 22 — a frase mais cobrada de todas:**

> Existe uma **equivalência semântica** entre o diagrama de sequência e o diagrama de comunicação (ou colaboração). Como resultado, **o diagrama de uma forma pode ser convertido no outro sem qualquer perda de informação**.
>
> Quando usar um em lugar do outro? Grande parte da decisão é **questão de preferência**. Em geral, a maioria das pessoas prefere o diagrama de sequência.

📌 **Slide 23 — pontos fortes e fracos:**

| Tipo | Pontos fortes | Pontos fracos |
| --- | --- | --- |
| **Sequência** | Mostra com **clareza a sequência ou ordem temporal** das mensagens. Amplo conjunto de opções detalhadas | Deve ser **estendido para a direita** quando são acrescidos novos objetos; **consome espaço na horizontal** |
| **Comunicação** | **Economia de espaço** — flexibilidade de adicionar novos objetos em **duas dimensões** | É **mais difícil ver a sequência** das mensagens. Menos opções de notação. **Não tem qualquer notação precisa para lógica de controle** |

🎯 **Resumo para marcar V/F rápido:**

```text
Sequência   → melhor para ver O QUANDO (tempo)   · gasta espaço horizontal
Comunicação → melhor para ver O QUEM COM QUEM    · não tem alt/opt/loop
São SEMANTICAMENTE EQUIVALENTES → conversão sem perda de informação
```

⚠️ Note a consequência prática: como o diagrama de comunicação **não tem notação para lógica de controle**, os fragmentos combinados (`alt`, `opt`, `loop`) são recurso **do diagrama de sequência**.

---

## 1.12 Diagrama de Visão Geral da Interação

📌 **Slide 25:**

> São uma **mistura de diagramas de atividades e diagramas de sequência**. Pode-se considerá-los como:
> * diagramas de **atividades** nos quais as **atividades são substituídas por pequenos diagramas de sequência**;
> * um **diagrama de sequência fragmentado**, com a notação do diagrama de atividades usada para mostrar o **fluxo de controle**.
>
> É outra abordagem para **modularizar** a construção de diagramas de interação.

```text
        ●  (início — notação de diagrama de atividades)
        │
   ┌────┴─────────────┐
   │ sd Autenticar    │   ← um mini diagrama de sequência dentro do nó
   │  ator ──► :Sist  │
   └────┬─────────────┘
        ◇  [autenticado?]      ← decisão (notação de atividades)
   ┌────┴────┐
   │         │
 ┌─┴──────┐ ┌┴───────┐
 │ sd ... │ │ ref ...│
 └────────┘ └────────┘
```

---

## 1.13 Diagrama de Temporização

📌 **Slide 28:**

> Os diagramas de temporização existem na **engenharia eletrônica** há muito tempo. O foco está nas **restrições de temporização**: ou para um único objeto ou, de forma mais útil, para **vários**.
>
> ⚠️ **Esse diagrama terá pouca utilidade para modelar aplicações comerciais.**

🧪 **Exemplo do slide 29** (cafeteira):
* **Regra 1:** pelo menos **10 s** devem passar entre o acionamento da bomba e o aquecimento da chapa.
* **Regra 2:** quando o reservatório de água se esvazia, a bomba desliga e a chapa **não pode permanecer ligada por mais de 15 s** depois disso.

🎯 Palavras-chave: **tempo absoluto**, **duração**, **restrição temporal**, **sistemas de tempo real / embarcados**.

---

## 1.14 Pegadinhas de concurso — Interação

| ⚠️ Afirmação | Verdade |
| --- | --- |
| "O diagrama de sequência mostra os relacionamentos entre os objetos" | **Falso** — quem enfatiza relacionamentos é o de **comunicação** |
| "A ordem horizontal dos objetos no diagrama de sequência define a ordem das mensagens" | **Falso** — a ordem horizontal **não tem significado pré-definido** |
| "Sequência e comunicação têm poder expressivo diferente" | **Falso** — são **semanticamente equivalentes**, conversão sem perda |
| "O diagrama de comunicação usa fragmentos `alt` e `loop`" | **Falso** — ele **não tem notação precisa para lógica de controle** |
| "Toda mensagem no diagrama de comunicação deve ser numerada" | **Verdadeiro** — todas devem ter expressão de sequência (exceto a inicial, por convenção) |
| "Mensagem assíncrona faz o chamador esperar" | **Falso** — quem espera é a **síncrona** |
| "O objeto criado durante a interação fica no topo do diagrama" | **Falso** — fica **mais abaixo**; no topo ficam os que já existiam |
| "O diagrama de sequência representa um retrato em tempo de execução dos objetos e seus relacionamentos" | **Falso** — isso é o **Diagrama de Objetos** |
| "`opt` equivale a um `alt` com apenas um caminho" | **Verdadeiro** — está literal no slide |
| "O diagrama de temporização é o mais indicado para aplicações comerciais" | **Falso** — o slide diz que tem **pouca utilidade** para elas |
| "Os quadros de interação adicionam lógica processual ao diagrama de sequência" | **Verdadeiro** — já foi item verdadeiro em prova |
| "No DSS, aparecem os objetos internos do sistema" | **Falso** — o sistema é uma **caixa preta**, `:Sistema` |

---
# Parte 2 — Diagrama de Transição de Estado (DTE)

## 2.1 A ideia

📌 **Slide 2:**

> Objetos do mundo real se encontram em **estados particulares** a cada momento (uma jarra está cheia de líquido; um pedido está pago). Um objeto **muda de estado quando acontece um evento** interno ou externo ao sistema. Quando um objeto muda de um estado para outro, diz-se que ele realizou uma **transição** entre estados.

💡 **Em outras palavras:** um **estado é a situação em que o objeto está naquele momento**.

Exemplo:

```text
Pedido
  ↓
Não pago
  ↓ pagar
Pago
  ↓ cancelar
Cancelado
```

O objeto continua sendo o mesmo `Pedido`. O que muda é **a situação dele**.

---

## 2.2 Os seis elementos de um DTE

📌 **Slide 4:** Estado · Transição · Evento (Trigger) · Condição de guarda · Ação · Atividade.
*(Um DTE pode conter ainda transições internas, estados aninhados, estados concorrentes e subestados.)*

### Estado

📌 **Slide 5:**

> Um estado é uma **situação na vida de um objeto** durante a qual ele **satisfaz alguma condição** ou **realiza alguma atividade**. Cada estado é determinado pelos **valores de seus atributos** e (ou) pelas suas **ligações com outros objetos**.
>
> Notação: **retângulo com bordas arredondadas**.

💡 **Pense em estado como “como o objeto está”.**

Exemplo:

```text
Aluguel
→ Confirmado
→ Ativo
→ Atrasado
→ Concluído
```

O `Aluguel` é o objeto. `Confirmado`, `Ativo`, `Atrasado` e `Concluído` são **situações diferentes desse objeto**.

📌 **Slide 6 — regra que cai:**

|              | Estado inicial               | Estado final                       |
| ------------ | ---------------------------- | ---------------------------------- |
| Notação      | círculo preenchido ●         | círculo com anel ◉                 |
| Quantidade   | **só pode haver UM** por DTE | **pode haver MAIS DE UM**          |
| Obrigatório? | sim                          | **não, é opcional**                |
| Significa    | o objeto foi **criado**      | **fim do ciclo de vida** do objeto |

> A restrição de um só estado inicial serve para **definir a partir de que ponto o DTE deve começar a ser lido**. A exceção é quando se trata de estados aninhados, concorrentes ou compostos.

💡 **Cuidado:** estado inicial não significa necessariamente `Cadastrado`.

`Cadastrado` só deve aparecer se fizer parte do **ciclo de vida que está sendo modelado**.

---

### Transição

📌 **Slide 7 — a sintaxe mais cobrada da matéria:**

```text
evento (lista-parâmetro) [guarda] / ação
```

⚠️ **PEGADINHA CLÁSSICA:** a banca inverte para `evento (lista-parâmetros) [ação] / guarda`. Está **errado**.

```text
[ ] entre COLCHETES  → GUARDA   (condição lógica)
 /  depois da BARRA  → AÇÃO     (o que é executado)
```

💡 **Leia da esquerda para a direita:**

```text
evento → guarda → ação
```

Exemplo:

```text
pagar() [valor > 0] / registrarPagamento()
```

* `pagar()` → **evento:** algo aconteceu.
* `[valor > 0]` → **guarda:** condição que precisa ser verdadeira.
* `/ registrarPagamento()` → **ação:** o que será executado.

Se a guarda for falsa, a transição não acontece.

---

### Evento (Trigger)

📌 **Slide 8:** um evento é **algo que acontece em algum ponto no tempo e que pode modificar o estado de um objeto**. Ex.: Realizar pedido, Pagar fatura, Devolver cheque.

💡 **Pense em evento como “alguma coisa aconteceu”.**

Exemplo:

```text
Não pago
   ↓ Pagar fatura
Pago
```

`Pagar fatura` é o **evento** que provoca a mudança.

📌 **Slides 9 e 10 — os quatro tipos de evento:**

| Tipo           | O que é                                                                                      | Cláusula    |
| -------------- | -------------------------------------------------------------------------------------------- | ----------- |
| **De chamada** | recebimento de uma **mensagem** de outro objeto; solicitação de serviço de um objeto a outro | —           |
| **De sinal**   | recebimento de um **sinal** de outro objeto                                                  | —           |
| **Temporal**   | passagem de um **intervalo de tempo** predefinido                                            | **`after`** |
| **De mudança** | uma **condição que se torna verdadeira** (expressão lógica)                                  | **`when`**  |

💡 Para reconhecer rapidamente:

* **Alguém/objeto pediu alguma coisa** → chamada.
* **Recebeu um sinal** → sinal.
* **Passou um tempo** → `after`.
* **Uma condição ficou verdadeira** → `when`.

Exemplos:

```text
after(30 dias)
```

→ passaram 30 dias.

```text
when(hoje = dataFimContrato + 1)
```

→ a condição ficou verdadeira.

⚠️ **Obs. literal do slide 9:** a diferença básica entre sinal e chamada é que **no evento de chamada o objeto que envia a mensagem fica esperando a execução**. O **evento de sinal raramente é utilizado**.

🎯 `after(30 dias)` · `when(hoje = dataFimContrato + 1)` — os gabaritos das provas usam muito o `when`.

---

### Condição de guarda

📌 **Slide 11:**

> Uma condição de guarda (sentinela) é uma **expressão de valor lógico**. Uma transição com guarda é disparada **somente se o evento associado ocorre E a condição de guarda é verdadeira**. Se uma transição **não** tiver guarda, ela **sempre** será disparada quando o evento ocorrer. A expressão é sempre apresentada **entre colchetes**.

💡 **Guarda = “só pode passar se...”**

Exemplo:

```text
pagar() [valor > 0]
```

O evento `pagar()` aconteceu, mas a transição **só acontece se `valor > 0`**.

Portanto:

```text
evento + guarda verdadeira → transição acontece
evento + guarda falsa      → transição NÃO acontece
```

---

### Ação × Atividade

📌 **Slides 12 e 13:**

|                            | **Ação**                                    | **Atividade**                                   |
| -------------------------- | ------------------------------------------- | ----------------------------------------------- |
| Onde fica                  | **na linha da transição**, precedida de `/` | **dentro do estado**, com a cláusula `do`       |
| Duração                    | tempo **insignificante**                    | tem duração                                     |
| **Pode ser interrompida?** | **NÃO**                                     | **SIM**                                         |
| Quando executa             | **só se a transição for disparada**         | continuamente, enquanto o objeto está no estado |

💡 **A maneira mais fácil de diferenciar:**

> **Ação = acontece.**
> **Atividade = fica acontecendo.**

Exemplo de ação:

```text
/ registrarPagamento()
```

Registrar o pagamento é uma operação pontual.

Exemplo de atividade:

```text
do/ processarPagamento()
```

O processamento pode continuar durante algum tempo.

⚠️ Essa é **a** diferença entre ação e atividade: **atividade pode ser interrompida, ação não**.

---

### Ponto de junção

📌 **Slide 14:**

> Em algumas situações, o próximo estado varia de acordo com o valor da condição de guarda. Isso é representado por um **ponto de junção**, desenhado como um **losango** em que chegam uma ou mais transições. A cada transição de **saída** está associada uma condição de guarda, e o objeto segue aquela cuja guarda for **verdadeira**.

💡 **Pense no ponto de junção como uma bifurcação:**

```text
             ┌─ [nota >= 7] ─→ Aprovado
Estado ─→ ◇ ─┤
             └─ [nota < 7] ──→ Reprovado
```

O objeto chega ao losango e verifica as guardas.

* Se `[nota >= 7]` for verdadeira → `Aprovado`.
* Se `[nota < 7]` for verdadeira → `Reprovado`.

---

## 2.3 Cláusulas `entry`, `exit` e `do`

📌 **Slide 17:**

| Cláusula    | Quando executa                                                         | Detalhe                                           |
| ----------- | ---------------------------------------------------------------------- | ------------------------------------------------- |
| **`entry`** | no momento em que o objeto **entra** no estado                         | **independentemente do estado de onde ele veio**  |
| **`exit`**  | no momento em que o objeto **sai** do estado                           | **independentemente do estado para onde ele vai** |
| **`do`**    | **continuamente**, durante o tempo em que o objeto permanece no estado | define uma **atividade em andamento**             |

💡 **Imagine o estado como uma sala:**

```text
ENTROU NA SALA → entry
       ↓
FICOU NA SALA  → do
       ↓
SAIU DA SALA   → exit
```

Então:

* `entry` = **entrou** → executa.
* `do` = **está dentro** → atividade continua enquanto permanece.
* `exit` = **saiu** → executa.

```text
╭──────────────────────────────╮
│  Digitando senha             │
├──────────────────────────────┤
│ entry/ definirEco(cInvisível)│
│ do/ aguardarEntrada()        │
│ exit/ definirEco(cVisível)   │
╰──────────────────────────────╯
```

⚠️ **Slide 18:** a **inexistência de um evento** na transição entre dois estados indica que, **assim que a atividade (`do`) for concluída, a transição ocorrerá automaticamente**.

💡 Ou seja, não é necessário alguém apertar um botão ou ocorrer outro evento. A própria conclusão do `do` permite a transição.

---

## 2.4 ⭐ Transição interna × Autotransição

**Este é o ponto mais cobrado do DTE em concurso.**

📌 **Slide 19 — Transição interna:**

> Os estados podem reagir a eventos **sem transição**, usando atividades internas. Uma transição interna é uma transição que **não faz o objeto mudar de estado**. Coloca-se o evento, a condição de guarda e a atividade **dentro da própria caixa do estado**.
>
> **As atividades internas NÃO disparam atividades de entrada e saída.** Essa é a grande diferença entre as atividades internas e as autotransições.

💡 **Pense na pergunta: “o objeto sai do estado?”**

Na transição interna:

> **Não.**

Exemplo:

```text
╭─────────────────────────╮
│ Digitando senha         │
├─────────────────────────┤
│ entry/ definirEco()     │
│ caractere(c)/tratar(c)  │
│ ajuda/ exibirAjuda()    │
│ exit/ definirEco()      │
╰─────────────────────────╯
```

O evento `caractere(c)` acontece, mas o objeto **continua em `Digitando senha`**.

Não acontece:

```text
sair → entrar novamente
```

Por isso `entry` e `exit` **não executam**.

---

📌 **Slide 20 — Autotransição:**

> Uma autotransição é uma transição onde o **estado de origem e o estado destino são iguais** e suas cláusulas **`entry` e `exit` SÃO executadas**.

💡 Aqui está a pegadinha:

**O estado final tem o mesmo nome, mas o objeto sai e entra novamente nele.**

```text
       evento
    ┌──────────┐
    ↓          │
  [State A] ───┘
```

É:

```text
State A → State A
```

Não significa que ele mudou para outro estado.

Significa que ele:

```text
SAI de State A
      ↓
ENTRA novamente em State A
```

Por isso:

```text
exit  → executa
entry → executa
```

|                           | **Transição interna**                 | **Autotransição**                            |
| ------------------------- | ------------------------------------- | -------------------------------------------- |
| Notação                   | escrita **dentro** da caixa do estado | **seta que sai e volta** para o mesmo estado |
| Muda de estado?           | Não                                   | Sai e volta ao mesmo estado                  |
| Executa `entry` / `exit`? | **NÃO** ❌                             | **SIM** ✅                                    |

```text
TRANSIÇÃO INTERNA                    AUTOTRANSIÇÃO
╭─────────────────────────╮          ╭─────────────────╮◄──┐
│ Digitando senha         │          │ State A         │   │ event/action()
├─────────────────────────┤          ├─────────────────┤───┘
│ entry/ definirEco()     │          │ entry/ doSomething()
│ caractere(c)/tratar(c)  │ ← aqui   ╰─────────────────╯
│ ajuda/ exibirAjuda()    │ ← e aqui
│ exit/ definirEco()      │          entry e exit SÃO executados
╰─────────────────────────╯          a cada disparo do evento
 entry/exit NÃO executam
```

🧠 **Para não confundir:**

```text
TRANSIÇÃO INTERNA
fica dentro do estado
→ não sai
→ não entra novamente
→ não executa entry/exit


AUTOTRANSIÇÃO
sai do estado
→ volta para o mesmo estado
→ executa exit/entry
```

🧪 **Questão CESGRANRIO 2011 (caiu na prova):** *"Os dois diagramas são equivalentes entre si, PORQUE modelar o evento02 com uma transição recursiva é equivalente a modelar o evento02 com uma atividade interna."*
→ Gabarito: **as duas afirmações são FALSAS**. Não são equivalentes, justamente porque a **autotransição dispara `entry`/`exit`** e a **transição interna não**.

---

## 2.5 Estados compostos, aninhados e concorrentes

📌 **Slide 23 — Estados aninhados / compostos:**

> Um estado que contém diversos outros é dito **composto**. **Todos os estados dentro de um estado composto HERDAM qualquer transição deste último.** O uso de estados compostos geralmente torna um DTE **mais legível**.

💡 **Pense em uma caixa grande com caixas menores dentro.**

```text
╭─────────────────────────────╮
│          Ativo              │ ← estado composto
│                             │
│   ╭──────────────╮          │
│   │ Em uso       │          │ ← estado aninhado
│   ╰──────────────╯          │
│                             │
│   ╭──────────────╮          │
│   │ Em manutenção│          │ ← estado aninhado
│   ╰──────────────╯          │
╰─────────────────────────────╯
```

Portanto:

> **Composto = contém outros estados.**

> **Aninhado = está dentro de outro estado.**

📌 **Importante:** os estados internos **herdam as transições do estado composto**.

Isso significa que uma transição definida para o estado composto também pode ser aplicada aos estados que estão dentro dele.

---

📌 **Slides 26 e 27 — Estados concorrentes** (ou paralelos, ou compostos ortogonais):

> Um estado concorrente é um **tipo especial de estado composto**. Um objeto em um estado concorrente pode, na verdade, se encontrar em **dois ou mais estados independentes**.

💡 **Concorrente = situações independentes acontecendo ao mesmo tempo.**

```text
╭─── Weather ──────────────────────────────╮
│  ╭─ Climate ─────────────────────────╮   │
│  │  Day  ──at sunset──►  Night       │   │  ← região 1
│  │       ◄──at sunrise──             │   │
│  ├───────────────────────────────────┤   │  ← linha TRACEJADA separa as regiões
│  │  Warm ──coldFront──►  Cold        │   │  ← região 2
│  │       ◄──warmFront──              │   │
│  ╰───────────────────────────────────╯   │
╰──────────────────────────────────────────╯
   O objeto está em UM estado de CADA região ao mesmo tempo (ex.: Day + Cold)
```

O objeto pode estar, ao mesmo tempo:

```text
Day + Cold
```

porque:

* `Day/Night` pertence à região 1.
* `Warm/Cold` pertence à região 2.

Ele possui **um estado em cada região simultaneamente**.

---

## 2.6 Roteiro de construção de um DTE (slides 28–29)

```text
1.  Identifique as CLASSES que precisam de um DTE.
2.  Identifique os ESTADOS relevantes da classe.
3.  Identifique os EVENTOS relevantes e a transição que cada um ocasiona.
4.  Para cada estado, identifique as TRANSIÇÕES possíveis quando um evento relevante ocorre.
5.  Para cada estado, identifique os EVENTOS INTERNOS e ações correspondentes.
6.  Para cada transição, verifique se há fatores que influenciam no disparo → GUARDA.
    Verifique também se alguma AÇÃO deve ser executada quando a transição é disparada.
7.  Para cada guarda e cada ação, identifique os ATRIBUTOS e LIGAÇÕES envolvidos.
8.  Defina o ESTADO INICIAL e os eventuais ESTADOS FINAIS.
9.  Desenhe: posicione os estados de modo que o ciclo de vida seja lido
    DE CIMA PARA BAIXO e DA ESQUERDA PARA A DIREITA.
```

💡 **A ordem é importante. Não tente descobrir tudo de uma vez.**

Pense:

```text
CLASSE
   ↓
ESTADOS
   ↓
EVENTOS
   ↓
TRANSIÇÕES
   ↓
GUARDAS / AÇÕES
   ↓
DETALHES
   ↓
INÍCIO / FIM
   ↓
DESENHO
```

🎯 **Como o gabarito das provas monta o DTE a partir do minimundo:**

```text
substantivo de SITUAÇÃO no texto  → ESTADO
   "o aluguel está ativo/concluído/atrasado"  → Ativo, Concluído, Atrasado

verbo de AÇÃO do ator             → EVENTO
   "o atendente registra a devolução"          → Registrar devolução

condição de TEMPO/REGRA           → when(...) na transição
   "quando a data prevista for atingida"       → when(hoje > dataPrevista)

"desde que / somente se"          → [guarda]

agrupamento de estados            → ESTADO COMPOSTO
   (P1 2025.1: Livre, Responsável por pedido e Trabalhando
    ficaram dentro do estado composto "Ativo")
```

💡 **Para ler um minimundo rapidamente:**

```text
"está / é / encontra-se em..."
→ provavelmente está descrevendo um ESTADO

"registrar / pagar / devolver / realizar..."
→ provavelmente está descrevendo um EVENTO

"quando..."
→ provavelmente indica um EVENTO DE MUDANÇA / TEMPO

"se / desde que / somente se..."
→ provavelmente indica uma GUARDA
```

⚠️ **Cuidado:** isso é um guia para procurar as informações no texto. Não significa que toda palavra desse tipo obrigatoriamente será um elemento do DTE. É preciso verificar o contexto e o ciclo de vida da classe.

---

# Parte 3 — Diagrama de Classes de Análise

## 3.1 Os três níveis de abstração do modelo de classes

📌 **Slide 3 (1a):**

| Modelo | O que é |
| --- | --- |
| **Domínio** | Representa as classes do **domínio do negócio**. **Não leva em consideração restrições referentes à tecnologia** a ser utilizada |
| **Especificação** | Extensão do de domínio, com **detalhes específicos conforme a solução de software escolhida**; novas classes necessárias são definidas |
| **Implementação** | Extensão do de especificação; corresponde à **implementação em alguma linguagem de programação** |

## 3.2 Identificação de classes

📌 **Slide 4:** duas técnicas — **Análise dos Casos de Uso** e **Análise Textual de Abbott**.

### Análise dos Casos de Uso (Identificação Dirigida por Casos de Uso)

📌 **Slide 5:** a existência de uma classe **só pode se justificar se ela participar de alguma forma do comportamento externamente visível do sistema**.

### ⭐ Categorização BCE (Jacobson)

📌 **Slides 6 e 7:**

| Estereótipo | Notação | Papel (literal do slide) |
| --- | --- | --- |
| **`<<boundary>>` / fronteira** | `Tela de Venda` | **Atores interagem** com esses objetos |
| **`<<control>>` / controle** | `Controlador de Venda` | **Intermediários** entre objetos de fronteira e de entidade, definindo o comportamento de **um caso de uso específico** |
| **`<<entity>>` / entidade** | `Venda` | São, usualmente, **objetos do domínio do problema** |

```text
   Ator ──► <<fronteira>> ──► <<controle>> ──► <<entidade>>
                                   │
                                   └────────► <<entidade>>

A realização de um caso de uso envolve objetos de fronteira, de controle e de entidade.
```

### Análise Textual de Abbott

📌 **Slide 8 — os três passos:**

```text
1º passo: buscar NOMES (substantivos e adjetivos) e locuções equivalentes a substantivos.
2º passo: remover os SINÔNIMOS.
3º passo: cada termo remanescente vira uma de três coisas:
            → uma CLASSE (candidata)
            → um ATRIBUTO
            → nada (não tem relevância)
```

📌 **Slides 9 e 10 — a tabela de tradução:**

| Parte do texto | Componente | Exemplo |
| --- | --- | --- |
| Nome próprio | **Objeto** (instância) | Eduardo Bezerra |
| Nome simples | **Classe** | Aluno |
| Verbo de ação | **Operação** | Registrar |
| Verbo **ser** | **Herança** | "é um" |
| Verbo **ter** | **Todo-parte** (agregação/composição) | "tem um" |

🎯 Verbos como **calcular, cancelar, comprar, fechar** → operações em potencial.

## 3.3 Nomenclatura

📌 **Slide 11:**

```text
Identificadores      → remover espaços em branco e preposições
Classes e            → começar com MAIÚSCULA
relacionamentos        Ex.: Cliente, ItemPedido, Pedido
Atributos e          → 1ª palavra minúscula, demais com inicial maiúscula, sem espaço
operações              Ex.: quantidade, precoUnitario, dataNascimento
                       ⚠️ SIGLAS são mantidas inalteradas → CPF
```

## 3.4 Associações, multiplicidade e conectividade

📌 **Slide 13 — Multiplicidades:** representam os **limites inferior e superior** da quantidade de objetos aos quais outro objeto pode estar associado — **(Mínimo .. Máximo)**.

| Nome | Simbologia |
| --- | --- |
| Apenas um | `1..1` (ou `1`) |
| Zero ou muitos | `0..*` (ou `*`) |
| Um ou muitos | `1..*` |
| Zero ou um | `0..1` |
| Intervalo específico | `Im..In` |

⚠️ **Slide 12 (1b):** *alguns autores consideram que, quando não se informa a multiplicidade, deve-se considerar `1..1`.*

📌 **Slide 14 — Conectividade × Multiplicidade** (a **conectividade leva em consideração a multiplicidade MÁXIMA** de cada participante):

| Conectividade | Multiplicidade de um extremo | Multiplicidade do outro extremo |
| --- | --- | --- |
| **Um para um** | `0..1` ou `1` | `0..1` ou `1` |
| **Um para muitos** | `0..1` ou `1` | `*` ou `1..*` ou `0..*` |
| **Muitos para muitos** | `*` ou `1..*` ou `0..*` | `*` ou `1..*` ou `0..*` |

📌 **Slide 16 — Participação:** indica a **necessidade (ou não) da existência da ligação**.

```text
multiplicidade mínima = 1   → participação OBRIGATÓRIA   (1..1, 1..*)
multiplicidade mínima = 0   → participação OPCIONAL      (0..1, 0..*)
```

📌 **Slide 17 — os três adornos** para adicionar semântica a uma associação:

| Adorno | O que é |
| --- | --- |
| **Nome da associação** | indica o **significado** da associação |
| **Papel** | representa um papel desempenhado por um objeto; **serve como substituto do nome da associação** |
| **Sentido de leitura** (▶) | indica **como a associação deve ser lida**; elimina ambiguidade |

## 3.5 Classes associativas

📌 **Slide 18:**

> Aparece quando se necessita **guardar informações sobre o relacionamento** entre objetos das duas classes.
>
> ⚠️ **Não confunda** uma classe de associação com uma associação que foi **promovida a uma classe**.
> ⚠️ A classe de associação permite **apenas UMA ocorrência para cada par de objetos**.

📌 **Slide 19:** embora seja mais comum em associações **muitos-para-muitos**, classes associativas também podem ocorrer em **um-para-muitos** e **um-para-um**.

```text
   Aluno  ────────────────*──*────────────────  Disciplina
                          ┆
                     ╔════╧═════╗
                     ║ Matricula║   ← notação: linha TRACEJADA ligando à associação
                     ║  nota    ║
                     ╚══════════╝
```

## 3.6 Associação reflexiva

📌 **Slide 20:** associa objetos **da mesma classe**; **cada objeto tem um papel distinto** nessa associação.

```text
        ┌──── supervisiona ────┐
        │  0..*                │
   ╔════╧═════╗                │
   ║ Empregado║────────────────┘
   ╚══════════╝  1  supervisor

"Um empregado é supervisor de zero ou muitos empregados."
"Um empregado é supervisionado por apenas um empregado."
```

## 3.7 Associações ternárias

📌 **Slide 21:**

> Define-se o **grau** de uma associação em função da **quantidade de classes envolvidas**. Na maioria dos casos as associações são **binárias**; quando o grau é **três**, é **ternária**.
>
> Dada uma associação ternária entre A, B e C, **a multiplicidade do extremo C indica quantos objetos de C podem estar associados com um PAR PARTICULAR de objetos (a, b)**.

**Notação: um losango** ligando as três classes.

🧪 Exemplo do slide (Técnico, Projeto, Computador):
* Um técnico, quando trabalha em um projeto, utiliza um **único** computador.
* Um computador, em um projeto, é utilizado por um **único** técnico.
* Um técnico pode utilizar um computador em **vários** projetos.

📌 **Slide 22 — Classe associativa ternária:** os dois conceitos podem ser misturados. Assim como na binária a classe de associação tem apenas **uma ocorrência para cada par**, na ternária tem **uma ocorrência para cada trio de objetos**.

## 3.8 ⭐ Agregação × Composição

**O tema mais cobrado do diagrama de classes em concurso.**

📌 **Slide 2 (1b) — características comuns:**

> * Agregações/composições são **assimétricas**: se um objeto A é parte de um objeto B, **B não pode ser parte de A**.
> * Nas agregações/composições **as partes são normalmente criadas e destruídas pelo todo**. Na **classe todo** são definidas operações para **adicionar e remover** as partes.

| | **Agregação** | **Composição** |
| --- | --- | --- |
| Notação | **losango VAZIO** ◇ | **losango CHEIO** ◆ |
| Força | todo-parte **fraca** | todo-parte **forte** (*"forma mais forte de agregação"*) |
| Destruir o todo destrói a parte? | **Não necessariamente** | **Sim** — tempo de vida coincidente |
| Multiplicidade do lado do TODO | pode ser > 1 | **não excede 1** |
| Pertença | fraca | **forte grau de pertença** das partes ao todo |

📌 **Slide 4 (1b) — a composição é aplicável quando:**
1. existe um **forte grau de pertença** das partes ao todo;
2. **cada parte só pode fazer parte de UM todo** (a multiplicidade do lado do todo **não excede 1**);
3. o todo e as partes têm **tempo de vida coincidente**, ou pelo menos **as partes nascem e morrem dentro de um todo**.

⚠️ **O losango fica SEMPRE do lado do TODO.**

```text
   Todo ◆────── Parte       Todo ◇────── Parte
   composição                agregação
   (a parte depende          (a parte existe
    do todo p/ existir)       independentemente)
```

🧪 **Já caiu assim (IF-SP 2024):** dado `Y ◇── X ──◆ Z`, a resposta é **"a classe Z depende da classe X para existir"** — porque o losango **cheio** está do lado de **X**, logo **X é o todo** e **Z é a parte**.

🧪 **Já caiu assim (FGV 2026):** *"uma Emenda só pode existir se estiver vinculada a um Projeto de Lei, e se o Projeto de Lei for excluído, todas as suas Emendas também o serão"* → **Composição**.

## 3.9 Generalização, especialização e herança

📌 **Slide 6 (1b):**

> A generalização é um relacionamento entre uma classe (**superclasse**) e uma ou mais variações da classe (**subclasses**). Às vezes é chamada de relacionamento **"é um"**, pois **cada instância de uma subclasse também é uma instância da superclasse**.
>
> Os termos **ancestral** e **descendente** referem-se à generalização entre vários níveis. Uma instância de uma subclasse é **simultaneamente uma instância de todas as suas classes ancestrais**.
>
> **Não aninhe classes com muita profundidade.** Dois ou três níveis é certamente aceitável; **dez níveis é provavelmente excessivo**; cinco ou seis pode ou não ser apropriado.

⚠️ **Slide 7 (1b) — detalhe que cai:**

> Não somente **atributos e operações** são herdados, mas **também as ASSOCIAÇÕES** definidas na superclasse.

**Notação:** seta com **triângulo vazio** apontando para a **superclasse**.

```text
        ╔═══════════╗
        ║  Pessoa   ║   ← superclasse (apontada pelo triângulo)
        ╚═════△═════╝
           ╱    ╲
   ╔══════╧═╗  ╔═╧══════╗
   ║ Cliente║  ║Consultor║  ← subclasses
   ╚════════╝  ╚════════╝
```

### Classe abstrata

📌 **Slide 8 (1b):**

> Normalmente utilizada para **organizar a hierarquia** entre classes, ou para fins de modelagem. **Classes abstratas NÃO geram objetos diretamente.** É representada com seu **nome em ITÁLICO**.

🧪 **Já caiu (GUALIMP 2024):** classe `Funcionario` em itálico com `FuncionarioHorista` e `FuncionarioComissionado` abaixo → a resposta é **"A classe Funcionário não pode ser instanciada"**.

### Herança múltipla

📌 **Slide 9 (1b):**

| Vantagens | Desvantagens |
| --- | --- |
| Mais **poder na especificação** de classes e maior oportunidade de **reuso** | **Perda de simplicidade** conceitual e de implementação (**nem todas as linguagens tratam bem disso**) |

⚠️ **Obs. do slide:** sempre que possível devemos distinguir **generalização** (o relacionamento **conceitual**) de **herança** (o **mecanismo da linguagem**) — mas o termo "herança múltipla" é mais usado que "generalização múltipla".

## 3.10 Restrições

📌 **Slide 10 (1b)** — representadas **entre chaves `{ }`**, próximas à linha do relacionamento:

| Restrição | Significado |
| --- | --- |
| **Sobreposta** | podem ser criadas subclasses que **herdem de mais de uma superclasse** — herança múltipla |
| **Disjunta** (ou Separada) | as subclasses são **mutuamente exclusivas**: se uma instância pertence a uma subclasse, **não poderá pertencer a nenhuma das outras** |
| **Completa** | **todas** as subclasses possíveis foram enumeradas |
| **Incompleta** | **nem todas** as subclasses foram enumeradas |

📌 **Slides 11 a 13 — OCL:**

> Restrições definem condições a serem validadas durante a implementação e podem ser usadas para detalhar **requisitos não-funcionais e regras de negócio**.
>
> **OCL (Object Constraint Language)** é a linguagem definida para escrever restrições, **semelhante a uma linguagem de programação**. Duas restrições sobre associações predefinidas pela UML:

| Restrição | Exemplo do slide |
| --- | --- |
| **`{xor}`** | *"Uma conta bancária é de uma pessoa OU de uma instituição, não podendo ser das duas simultaneamente"* |
| **`{subset}`** | *"A pessoa que administra um edifício deve pertencer ao grupo de pessoas que reside no edifício"* |

## 3.11 Identificadores e enumerações

⚠️ **Slide 14 (1b) — regra que vale ponto na discursiva:**

> **NÃO liste identificadores de objetos nos diagramas de classe de análise**, pois eles são **implícitos** nos modelos. Não confunda identificadores **internos** com atributos do **mundo real**: os internos são puramente uma **conveniência de implementação** e **não possuem significado para o negócio**.

🎯 Ou seja: `CPF` e `CNPJ` **entram** (são do mundo real); `idCliente`, `codigoInterno` **não entram** no modelo de análise.

📌 **Slide 15 (1b) — Enumeração:** tipo de dado que possui um **conjunto finito de valores (domínio fechado)**. Notação: `<<enumeration>>`.

🎯 No minimundo, frases como *"forma de pagamento (pix, cartão, dinheiro)"* ou *"nível de proficiência (júnior, pleno, sênior)"* pedem uma **enumeração**.

---

# Parte 4 — Padrões de Análise (Party e Metamodel)

📌 **Slide 3 (1c):**

> Um padrão de análise normalmente é composto de um **fragmento de diagrama de classes que pode ser customizado** para uma situação de modelagem em particular. O que ocorre **não é a identificação de classes propriamente dita**, mas sim a **identificação de PROBLEMAS cujas soluções podem ser encontradas em padrões de análise**.

## 4.1 Padrão Party

📌 **Slides 4 a 6:**

> Normalmente utilizado para representar **componentes de uma organização e os relacionamentos entre eles**. Uma **parte (party)** é uma **generalização de PESSOA ou de ORGANIZAÇÃO** de interesse para a aplicação que está sendo modelada.

```text
              ╔═══════════╗
              ║   Party   ║  (abstrata)
              ╚═════△═════╝
                 ╱     ╲
        ╔═══════╧╗   ╔══╧═════════╗
        ║ Pessoa ║   ║ Organizacao║
        ╚════════╝   ╚════════════╝
```

🎯 **Quando aplicar na prova:** sempre que o minimundo trouxer **dois ou mais participantes com os mesmos atributos** (nome, endereço, e-mail, telefone). É exatamente o caso das provas:

| Prova | Aplicação |
| --- | --- |
| P1 2025.1 (Siscon) | `Pessoa` como superclasse de `Consultor` e `Cliente` — com `Telefone` e `EMail` como classes à parte |
| P1 2026.1 (ginástica) | `Pessoa` (nome, nrRegistroConfed) como superclasse de `Atleta` e `Jurado` |
| P1 2025.2 (locadora) | `Loja` e `Cliente` compartilham nome, endereço completo, e-mail e telefones |

⚠️ **Detalhe dos gabaritos:** endereço, telefone e e-mail viraram **classes separadas** (não atributos), porque o minimundo fala em **"telefones"** no plural e em **endereço decomposto** (tipo do logradouro, nome, número, complemento, CEP).

## 4.2 Padrão Metamodel

📌 **Slide 7 (1c):**

> Considere um conjunto de itens quaisquer, em que **cada item possui várias propriedades** e **as propriedades de cada item podem ser diferentes** das dos outros itens.
>
> Uma solução seria criar **uma subclasse para especializar cada item**, mas isso implicaria criar **uma nova subclasse para cada novo tipo de item**.
>
> O padrão **metamodel** permite a **modificação da estrutura de um modelo de objetos sem que o esquema desses objetos seja realmente modificado**. Propriedades podem ser **adicionadas ou removidas** do metamodelo.

```text
   ╔══════╗ *        * ╔═════════════╗
   ║ Item ║────────────║ Propriedade ║
   ║ nome ║            ║   nome      ║
   ╚══════╝            ╚══════△══════╝
       │                      │
       │   ╔═══════════════╗  │  ╔════════════════╗
       └───║     Valor     ║  ├──║ ValorNumerico  ║
           ║ podeSerNulo   ║  │  ║ dado:TipoNum.  ║
           ╚═══════╤═══════╝  │  ╚════════════════╝
                   │ 0..1     │  ╔════════════════╗
           ╔═══════╧═══════╗  └──║ ValorDiscreto  ║
           ║ UnidadeMedida ║     ║ dado:TipoDisc. ║
           ║     nome      ║     ╚════════════════╝
           ╚═══════════════╝
```

🎯 **Quando aplicar:** quando o minimundo disser que cada **tipo** de coisa tem características próprias e que **novos tipos podem ser cadastrados pelo usuário** — sinal de que não se deve criar uma subclasse por tipo.

---

# Parte 5 — GRASP (caiu na prova, não está nos slides)

⚠️ **Atenção:** este assunto **apareceu numa prova** (questão de 0,9 ponto, V/F) mas **não está nos slides que você tem**. Vale estudar o mínimo.

**GRASP** = *General Responsibility Assignment Software Patterns* (Larman) — padrões para **atribuir responsabilidades** às classes. Conecta-se diretamente com os diagramas de interação: quem **recebe** a mensagem é quem **tem a responsabilidade**.

| Padrão | O que diz |
| --- | --- |
| **Information Expert** (Especialista) | Atribua a responsabilidade a quem **tem a informação necessária** para cumpri-la |
| **Creator** (Criador) | A classe B deve criar objetos de A se B **agrega, contém, registra ou usa** A de perto |
| **Controller** (Controlador) | Atribua a responsabilidade de tratar um **evento de sistema** a uma classe que represente o sistema/cenário de caso de uso. **Coordena o fluxo de eventos, invoca operações no modelo e atualiza a interface**, mantendo o código **modular** |
| **Low Coupling** (Baixo acoplamento) | Minimize as **dependências** entre classes |
| **High Cohesion** (Alta coesão) | Cada classe deve ter responsabilidades **focadas e relacionadas entre si** |
| **Polymorphism** (Polimorfismo) | Quando o comportamento **varia conforme o tipo**, delegue a responsabilidade **ao próprio objeto**, usando polimorfismo — em vez de testar o tipo com `if`/`switch` |
| **Pure Fabrication** (Invenção pura) | Crie uma classe **artificial** (sem correspondente no domínio) para preservar coesão e acoplamento |
| **Indirection** (Indireção) | Use um **intermediário** para evitar acoplamento direto |
| **Protected Variations** | **Encapsule** os pontos de variação previstos atrás de uma interface estável |

⚠️ **PEGADINHA que já caiu — coesão:**

```text
Classe com MUITAS e DIFERENTES responsabilidades  →  BAIXA coesão ❌ (ruim)
Classe com POUCAS responsabilidades RELACIONADAS  →  ALTA coesão  ✅ (bom)
```

🧪 O item *"Um padrão que recomenda que uma classe tenha várias e diferentes responsabilidades, para que se aumente sua reutilização, é caracterizado como de alta coesão"* é **FALSO** — isso descreve **baixa** coesão, e ela **prejudica** o reuso.

🎯 Ligação com BCE: o `<<control>>` de Jacobson é a aplicação do **Controller** do GRASP.

---

# Parte 6 — Questões de provas anteriores, resolvidas

## 6.1 Diagramas de Interação

**🧪 (IF-ES 2023, adaptada) Numere a segunda coluna de acordo com a primeira.**

| # | Diagrama | Descrição |
| --- | --- | --- |
| (1) | Diagrama de Estados | **(2)** É um diagrama de interação com ênfase na **organização estrutural dos objetos** e nas relações entre os objetos e classes que enviam ou recebem mensagens |
| (2) | Diagrama de Comunicação | **(1)** Provê uma **visão dinâmica dos objetos de uma classe**, para modelar o comportamento em **resposta à ocorrência de eventos** |
| (3) | Diagrama de Sequência | **(3)** Modela as interações entre atores e objetos e entre os próprios objetos. Indica as comunicações dinâmicas e mostra a **ordem temporal** na qual as mensagens são enviadas |

→ Gabarito: **2 – 1 – 3**.

---

**🧪 (P1 2025.1) Marque V ou F:**

| Afirmativa | Gabarito | Por quê |
| --- | --- | --- |
| O diagrama de sequência ilustra como objetos interagem entre si, identificando inclusive a **ordem de ocorrência** destas interações | **V** | é a definição |
| No diagrama de sequência, os **quadros de interação** são sequências de processamento executadas sob circunstâncias específicas e funcionam como mecanismos para **adicionar lógica processual** | **V** | é a função de `alt`/`opt`/`loop` |
| O **diagrama de estados** representa um retrato, em tempo de execução, dos objetos existentes no software e dos seus relacionamentos | **F** | ⚠️ isso é o **Diagrama de Objetos** |
| Um diagrama de sequência complementa o caso de uso representando como o sistema reage a **eventos internos** | **F** | ⚠️ o DSS mostra a reação a eventos **externos**, vindos do ator |
| O diagrama de classes inclui atributos e operações de uma classe, **sem apresentar o dinamismo** da comunicação com outras classes | **V** | o de classes é **estrutural estático** |

---

**🧪 (FEPESE 2010, adaptada — diagrama com dois `opt` aninhados)**

| Afirmativa | Gabarito |
| --- | --- |
| O diagrama apresenta **dois fragmentos combinados** (*combined fragments*) opção (*option*) | **V** |
| A **sexta mensagem** só será enviada se `conectado` **e** `êxito` apresentarem **ambos** valor `true` | **V** — consequência do **aninhamento** dos `opt` |
| O diagrama apresenta a **criação de um objeto** | **F** — não há seta apontando para a caixa de um objeto posicionado abaixo |
| A instância da classe `Tabuleiro` tem a responsabilidade de **definir o valor da condição** `conectado` | **V** |

## 6.2 DTE

**🧪 (CETAP 2015) Assinale a alternativa FALSA sobre o DTE:**

| | Alternativa | |
| --- | --- | --- |
| a) | Os estados estão associados a outros pelas transições | V |
| b) | Uma transição é mostrada como uma linha conectando estados, com uma seta apontando para um dos estados | V |
| **c)** | **Uma transição pode ser descrita pela expressão: `evento (lista-parâmetros) [ação]/guarda`** | ❌ **FALSA — é a resposta** |
| d) | Quando uma transição entre estados ocorre, diz-se que a transição foi disparada | V |
| e) | Uma transição sempre possui um evento associado | V |

→ ⚠️ O erro em **(c)**: está **invertido**. A forma correta é **`evento (lista-parâmetro) [guarda] / ação`**.

---

**🧪 (FGV 2021) Assinale o item que é enfatizado pelo Diagrama de Transição de Estados:**

| | Alternativa | |
| --- | --- | --- |
| a) | A dinâmica dos casos de uso | ❌ |
| b) | A ordem temporal das mensagens | ❌ diagrama de **sequência** |
| c) | O fluxo de controle de uma atividade para outra | ❌ diagrama de **atividades** |
| **d)** | **O estado de mudança de um sistema orientado por eventos** | ✅ **resposta** |
| e) | A organização estrutural de objetos que enviam e recebem mensagens | ❌ diagrama de **comunicação** |

🎯 Repare que essa questão é um **mapa de todos os diagramas**: cada alternativa errada é a definição de outro diagrama.

---

**🧪 (P1 2026.1) Marque V ou F sobre o diagrama de estados:**

| Afirmativa | Gabarito | Por quê |
| --- | --- | --- |
| Uma transição só pode ocorrer se houver uma **ação explícita** associada a ela | **F** | a ação é **opcional** |
| Um diagrama de estado modela os **estados** de um objeto, as **ações** executadas dependentes destes estados, e as **transições** entre os estados | **V** | definição correta |
| O diagrama de estados representa um retrato, em tempo de execução, dos objetos existentes e seus relacionamentos | **F** | ⚠️ **Diagrama de Objetos** (repetiu!) |
| Em um diagrama de estados uma transição é a conexão entre objetos no tempo e no espaço | **F** | transição conecta **estados**, não objetos |

---

**🧪 (CESGRANRIO 2011) Asserção–razão sobre máquinas de estado:**

> I. Os dois diagramas de máquinas de estados apresentados são **equivalentes** entre si.
> **PORQUE**
> II. Modelar o evento02 com uma **transição recursiva** é equivalente a modelar o evento02 com uma **atividade interna**.

→ Gabarito: **as duas afirmações são FALSAS**.
⚠️ **Autotransição executa `entry` e `exit`; transição interna NÃO executa.** Logo não são equivalentes.

## 6.3 Diagrama de Classes

**🧪 (FUNCERN 2024) Sobre composição e agregação, é correto afirmar que a composição:**

| | Alternativa | |
| --- | --- | --- |
| a) | é uma relação entre classes, enquanto a agregação é entre objetos | ❌ |
| b) | é representada por linha sólida e a agregação por linha tracejada | ❌ (a diferença é o **losango**, cheio × vazio) |
| **c)** | **é uma relação permanente entre objetos, enquanto a agregação é uma relação temporária** | ✅ **resposta** |
| d) | é entre superclasses e subclasses, enquanto a agregação é entre instâncias | ❌ (isso é generalização) |

---

**🧪 (IF-SP 2024)** Dado `Y ◇── X ──◆ Z`:
→ **d) a classe Z depende da classe X para existir** (losango **cheio** do lado de X ⇒ X é o **todo**, Z é a **parte**).

---

**🧪 (Prefeitura de Vitorino/PR 2024)** Diagrama: `aeronave ◇── piloto`, `aeronave ◇── assento`, `computador △→ piloto`, `humano △→ piloto`.

| Afirmativa | Gabarito | Por quê |
| --- | --- | --- |
| A aeronave é **composta** por um conjunto de assentos | **F** | ⚠️ o losango é **vazio** ⇒ **agregação**, não composição |
| O relacionamento entre aeronave e piloto é uma **associação simples** | **F** | é **agregação** (tem losango) |
| O relacionamento entre computador e piloto é de **generalização** | **V** | triângulo vazio |
| A associação entre piloto e humano significa que **humano herdará** atributos e métodos de piloto | **V** | `humano` é a subclasse |

---

**🧪 (FGV 2026)** *"Uma Emenda só pode existir se estiver vinculada a um Projeto de Lei; se o Projeto de Lei for excluído, todas as suas Emendas também serão."*
→ **e) Composição** (dependência existencial + exclusão em cascata).

---

**🧪 (GUALIMP 2024)** `Funcionario` em **itálico**, com `FuncionarioHorista` e `FuncionarioComissionado`:
→ **a) A classe Funcionário não pode ser instanciada** (nome em itálico ⇒ **classe abstrata**).

---

**🧪 (FUNDATEC 2025)** Descrição correta sobre associação, agregação e composição:
→ **e) Associação representa uma relação estrutural entre objetos, agregação indica uma relação "todo-parte" FRACA e composição representa uma relação "todo-parte" FORTE e com ciclo de vida compartilhado.**

---

**🧪 (FUNDEP 2025)** Asserção–razão:
> I. O diagrama de classes utiliza a notação de herança para representar a relação de especialização ("é um").
> **PORQUE**
> II. O diagrama de classes busca representar a **estrutura estática** de um sistema.

→ **b) As afirmativas I e II são verdadeiras, mas a II não é uma justificativa da I.**
🎯 Nesse formato de questão, sempre avalie **três** coisas separadamente: I é verdadeira? II é verdadeira? II **explica** I?

---

# Parte 7 — Checklist final da véspera

## 🔵 Diagramas de Interação

- [ ] Interação = **sequência de mensagens** + **objetos** + **contexto** + **propósito**.
- [ ] Os 4 tipos: **Sequência** (tempo) · **Comunicação** (relacionamentos) · **Visão Geral** (fluxo de controle) · **Temporização** (restrições de tempo).
- [ ] O conjunto de todos os diagramas de interação = **modelo de interações**.
- [ ] No diagrama de sequência, o **tempo é a vertical**; a **horizontal não tem significado**.
- [ ] Linha de vida = linha **tracejada**; foco de controle = **retângulo** sobre ela.
- [ ] Seta **cheia** = síncrona (espera) · **aberta** = assíncrona (não espera) · **tracejada** = retorno.
- [ ] Objeto **nomeado** é sublinhado; **classe** não é sublinhada (operação estática).
- [ ] Objeto criado durante a interação fica **abaixo**; destruído termina com **X**.
- [ ] Sentinela entre **colchetes**; iteração com **asterisco** (notação antiga).
- [ ] Operadores: **`alt`** (vários caminhos) · **`opt`** (um caminho; = `alt` de um só) · **`par`** · **`loop`** · **`sd`** · **`ref`** · **`break`**.
- [ ] `opt` aninhado ⇒ a mensagem interna exige **todas** as condições verdadeiras.
- [ ] **DSS** = ator + `:Sistema` (**caixa preta**); um DSS **por caso de uso relevante** (Processo Unificado).
- [ ] No DSS: passo do ator → **mensagem**; passo do sistema → **retorno**; exceção → **`opt`/`alt`**; repetição → **`loop`**.
- [ ] Diagrama de comunicação: **numeração decimal aninhada**; **não numere a inicial**; **todas** as demais precisam de número.
- [ ] Sequência e comunicação são **semanticamente equivalentes** — conversão **sem perda**.
- [ ] O de comunicação **não tem notação precisa para lógica de controle**.
- [ ] Diagrama de temporização tem **pouca utilidade para aplicações comerciais**.
- [ ] "Retrato em tempo de execução dos objetos e seus relacionamentos" = **Diagrama de Objetos**.

## 🟢 DTE

- [ ] Sintaxe: **`evento (lista-parâmetro) [guarda] / ação`** — nunca `[ação]/guarda`.
- [ ] **Um** estado inicial (obrigatório) · **vários** estados finais (opcionais).
- [ ] Eventos: **chamada** · **sinal** (raro) · **temporal (`after`)** · **mudança (`when`)**.
- [ ] Sem guarda ⇒ a transição **sempre** dispara quando o evento ocorre.
- [ ] **Ação** não pode ser interrompida; **atividade** pode.
- [ ] `entry` (entrando, de onde quer que venha) · `exit` (saindo, para onde quer que vá) · `do` (contínua).
- [ ] **Transição interna NÃO dispara `entry`/`exit`; autotransição DISPARA.**
- [ ] Transição sem evento ⇒ dispara **automaticamente** ao fim da atividade `do`.
- [ ] Estados dentro de um estado composto **herdam as transições** dele.
- [ ] Estado **concorrente** = objeto em **dois ou mais estados independentes** ao mesmo tempo.
- [ ] Ponto de junção = **losango**; cada saída tem uma guarda.

## 🟡 Diagrama de Classes

- [ ] Três níveis: **domínio** → **especificação** → **implementação**.
- [ ] **BCE**: fronteira (ator interage) · controle (intermediário, um caso de uso) · entidade (domínio).
- [ ] Abbott: nome próprio→objeto · nome simples→classe · verbo de ação→operação · **ser**→herança · **ter**→todo-parte.
- [ ] Multiplicidade = **(mínimo..máximo)**; mínimo 1 ⇒ **obrigatória**, mínimo 0 ⇒ **opcional**.
- [ ] Conectividade usa a multiplicidade **máxima**.
- [ ] Adornos: **nome** · **papel** · **sentido de leitura**.
- [ ] Classe associativa = **uma ocorrência por par** (ou por trio, na ternária).
- [ ] **Agregação = losango VAZIO** (fraca) · **Composição = losango CHEIO** (forte, todo com multiplicidade ≤ 1, vida coincidente).
- [ ] O losango fica **do lado do TODO**.
- [ ] Herança também herda **associações**, não só atributos e operações.
- [ ] Classe abstrata = **nome em itálico**, **não instanciável**.
- [ ] Restrições entre **chaves**: sobreposta · disjunta · completa · incompleta · `{xor}` · `{subset}` (OCL).
- [ ] **Não** liste identificadores internos no modelo de análise (mas **CPF/CNPJ sim**).
- [ ] Domínio fechado de valores ⇒ **`<<enumeration>>`**.
- [ ] Padrão **Party** ⇒ participantes com os mesmos atributos viram subclasses de `Pessoa`/`Party`.
- [ ] Padrão **Metamodel** ⇒ itens com propriedades variáveis, sem criar subclasse por tipo.

## 🔴 GRASP (fora dos slides, mas já caiu)

- [ ] Muitas e diferentes responsabilidades = **BAIXA** coesão (ruim), não alta.
- [ ] **Polimorfismo**: comportamento que varia por tipo ⇒ delegar ao próprio objeto.
- [ ] **Controller**: coordena eventos, invoca o modelo, mantém o código modular.

---

## 🧭 Estratégia para a discursiva do minimundo

```text
1. GRIFE o texto:  substantivos → classes/atributos
                   verbos de ação → operações
                   "tem/possui/composto por" → agregação ou composição
                   "é um/tipo de" → generalização
                   plurais ("telefones", "e-mails") → classe separada, mult. *
                   listas fechadas ("pix, cartão, dinheiro") → <<enumeration>>

2. APLIQUE os padrões: atributos repetidos em 2+ classes → Party (superclasse Pessoa)
                       tipos cadastráveis com propriedades próprias → Metamodel

3. INFORMAÇÃO SOBRE O RELACIONAMENTO → classe associativa
   ("da inscrição é preciso conhecer a data" → Inscricao entre Atleta e Campeonato)

4. MULTIPLICIDADES: leia CADA lado em voz alta, na forma
   "um X está associado a ___ Y" e "um Y está associado a ___ X".

5. NÃO coloque: identificadores internos · atributos derivados desnecessários
   COLOQUE: CPF, CNPJ, códigos do mundo real (ex.: código do equipamento)

6. Para o DTE: procure no texto os adjetivos de SITUAÇÃO
   ("ativo", "concluído", "atrasado", "cancelado", "confirmado")
   → cada um é um ESTADO; o verbo que leva a ele é o EVENTO.
```

---

## 📚 Bibliografia citada nos slides

* **BEZERRA, Eduardo.** *Princípios da Análise e Projeto de Sistemas com UML.* Rio de Janeiro: Elsevier, 2015. — **a principal referência da disciplina**
* BOOCH, Grady; RUMBAUGH, James; JACOBSON, Ivar. *UML — Guia do Usuário.* Rio de Janeiro: Campus, 2000.
* FOWLER, Martin. *UML Essencial: um breve guia para a linguagem-padrão de modelagem de objetos.* Porto Alegre: Bookman, 2005. — **origem da tabela de operadores e da numeração do diagrama de comunicação**
* GUEDES, Gilleanes T. A. *UML 2: uma abordagem prática.* São Paulo: Novatec, 2011.
* LARMAN, Craig. *Utilizando UML e Padrões.* Porto Alegre: Bookman, 2007. — **origem do GRASP**
* MELO, Ana Cristina. *Desenvolvendo aplicações com UML 2.2.* Rio de Janeiro: Brasport, 2010.
* PAULA FILHO, Wilson de Pádua. *Engenharia de Software.* Rio de Janeiro: LTC, 2003.
* WAZLAWICK, Raul Sidnei. *Análise e Projeto de Sistemas de Informação Orientado a Objetos.* Rio de Janeiro: Elsevier, 2004.
* WEILKIENS, Tim; OESTEREICH, Bernd. *UML 2 Certification Guide.* Elsevier, 2007.
