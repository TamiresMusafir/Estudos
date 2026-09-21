# 🎯 APS — Análise e Projeto de Sistemas (CEFET/RJ)
## Material de prova — conceitos dos slides explicados, com foco em **Diagramas de Interação**

> Baseado nos slides da Profa. Carmen Lucia Asp de Queiroz (APS 1a, 1b, 1c — Classes de Análise; 2 — Transição de Estado; 3a — Diagramas de Interação) e nas provas P1 de 2025.1, 2025.2 e 2026.1.
>
> **Legenda:** ⚠️ **Pegadinha de concurso** · 🎯 **Cai muito** · 📌 **Definição literal do slide** · 🧪 **Já caiu em prova**
> · 💡 **Em português claro** (explicação do que o slide quis dizer) · 🔎 **Exemplo**
>
> 🧵 **Um exemplo acompanha o material inteiro:** uma **loja online** (Cliente, Pedido, ItemPedido, Produto, Pagamento).
> Sempre que um conceito novo aparecer, ele é mostrado nessa mesma loja — assim as peças vão se encaixando em vez de virarem exemplos soltos.

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

💡 **Em português claro — a diferença entre as duas visões:**

```text
ESTRUTURAL (estático)     →  uma FOTOGRAFIA do sistema parado
                             "quais peças existem e como elas se encaixam"

COMPORTAMENTAL (dinâmico) →  um VÍDEO do sistema funcionando
                             "o que acontece, em que ordem, quando alguém usa"
```

🔎 **Exemplo com uma loja online:**

```text
ESTRUTURAL   → existe uma classe Pedido, que tem vários ItemPedido,
                e cada ItemPedido aponta para um Produto.
                (isso é verdade sempre, mesmo sem ninguém usando o sistema)

COMPORTAMENTAL → o cliente clica em "finalizar", a tela chama o controlador,
                 o controlador cria o Pedido, o Pedido calcula o total...
                 (isso só existe enquanto alguém está usando)
```

🎯 **Teste de 5 segundos para saber em qual visão um diagrama está:**

> *"Este diagrama muda se eu apertar um botão?"*
> * **Não muda** → é **estrutural** (Classes, Objetos)
> * **Muda** → é **comportamental** (Sequência, Comunicação, Estados, Atividades, Casos de Uso)

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

💡 **Em português claro — os quatro pedaços da definição, um por um:**

| Pedaço da definição | A pergunta que ele responde | 🔎 No exemplo de uma loja online |
| --- | --- | --- |
| **sequência de mensagens** | *Quais "recados" são trocados, e em que ordem?* | `criarPedido()`, depois `adicionarItem()`, depois `calcularTotal()` |
| **conjunto de objetos** | *Quem participa dessa conversa?* | `:TelaPedido`, `:ControladorPedido`, `:Pedido`, `:ItemPedido` |
| **um contexto** | *Estamos olhando o quê? O sistema todo? Uma operação?* | o cenário do caso de uso **"Finalizar pedido"** |
| **um propósito** | *Para quê essa conversa acontece?* | fechar a compra do cliente |

⚠️ **O mais esquecido é o CONTEXTO.** Um diagrama de interação **não** mostra "o sistema inteiro" — ele mostra **um cenário específico**. Se o caso de uso tem um fluxo principal e três exceções, você pode ter um diagrama para o fluxo principal e outros para as exceções.

📌 O diagrama de interação deve ser usado **quando se deseja visualizar o comportamento de vários objetos dentro do contexto estabelecido**.

📌 **Slide 3:** o conjunto de **todos** os diagramas de interação de um sistema constitui o **modelo de interações** do sistema.

🎯 **Ligação com o diagrama de classes (slide 7):**

> A atividade de modelagem de interações **gera informações para completar o modelo de classes** construído na etapa de análise.

```text
mensagem enviada a um objeto  →  responsabilidade daquele objeto
                              →  vira uma OPERAÇÃO na classe dele
```

Ou seja: os diagramas de interação **descobrem os métodos** das classes. Quem recebe a mensagem é quem precisa ter a operação.

💡 **Em português claro — por que o diagrama de interação "descobre métodos":**

Quando você desenha uma seta apontando para um objeto, você está dizendo *"ei, faça isso"*. Para o objeto **conseguir** fazer, a classe dele precisa ter **um método com aquele nome**. Logo, **toda seta que chega vira uma operação na classe de quem recebeu**.

🔎 **Exemplo — desenhando a interação, os métodos aparecem sozinhos:**

```text
   :ControladorPedido              :Pedido
          ▓───calcularTotal()───────►▓        ← seta CHEGANDO em Pedido
          ▓                          ▓
          ▓───adicionarItem(prod)───►▓        ← outra seta CHEGANDO em Pedido
```

Dessas duas setas você conclui, **sem precisar pensar mais**, que a classe `Pedido` tem:

```text
╔══════════════════════════════╗
║          Pedido              ║
╠══════════════════════════════╣
║ - data                       ║
║ - valorTotal                 ║
╠══════════════════════════════╣
║ + calcularTotal()            ║  ← veio da 1ª seta
║ + adicionarItem(prod)        ║  ← veio da 2ª seta
╚══════════════════════════════╝
```

🎯 **É por isso que a ordem de trabalho na análise é:** primeiro os **casos de uso**, depois o **diagrama de classes** (só com atributos), depois os **diagramas de interação** — e são eles que **preenchem as operações** das classes.

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

💡 **Em português claro — os quatro tipos com uma analogia cada:**

| Diagrama | É como... | Serve para responder |
| --- | --- | --- |
| **Sequência** | o **roteiro de um filme**, cena por cena, de cima para baixo | *"o que acontece primeiro, e o que vem depois?"* |
| **Comunicação** | o **mapa de um escritório**, mostrando quem fala com quem | *"quem conversa com quem nesse sistema?"* |
| **Visão Geral** | um **fluxograma** em que cada caixa é um mini-roteiro | *"que caminho o sistema pode seguir?"* |
| **Temporização** | um **gráfico de osciloscópio**, com o tempo no eixo | *"quantos segundos passam entre uma coisa e outra?"* |

🔎 **A MESMA interação nos dois formatos principais** (o cliente paga um pedido):

```text
DIAGRAMA DE SEQUÊNCIA                 DIAGRAMA DE COMUNICAÇÃO
(enfatiza QUANDO)                     (enfatiza QUEM COM QUEM)

  :Tela      :Contr.    :Pedido              1: pagar()
    ┆          ┆           ┆         :Tela ───────────► :Controlador
    ▓─pagar()─►▓           ┆                                 │
    ┆          ▓─registrar►▓                                 │ 1.1: registrarPagamento()
    ┆          ┆           ┆                                 ▼
                                                          :Pedido

  ↓ o tempo desce                       a posição é livre; a ORDEM está nos NÚMEROS
```

⚠️ Repare: **a informação é a mesma**. O que muda é o que fica fácil de enxergar em cada um.

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

💡 **Em português claro — como ler esse desenho:**

```text
1. Comece pelo TOPO e desça.
2. Cada retângulo lá em cima é um PARTICIPANTE (um objeto ou o ator).
3. A linha TRACEJADA que desce de cada um é a LINHA DE VIDA
   → significa "este objeto existe durante todo esse tempo".
4. O retângulo FINO sobre a linha é o FOCO DE CONTROLE
   → significa "neste intervalo, este objeto está trabalhando".
5. Cada seta horizontal é uma MENSAGEM: quem manda está na origem,
   quem executa está na ponta.
```

🔎 **Exemplo completo — "Finalizar pedido" na loja online:**

```text
   Cliente        :TelaPedido    :ControladorPedido      :Pedido
      │                │                  │                  │
   ╔══╧══╗        ╔════╧════╗        ╔════╧════╗        ╔════╧════╗
   ║     ║        ║         ║        ║         ║        ║         ║
   ╚══╤══╝        ╚════╤════╝        ╚════╤════╝        ╚════╤════╝
      ┆                ┆                  ┆                  ┆
      ┆─finalizar()───►▓                  ┆                  ┆      ← 1º
      ┆                ▓─fecharPedido()──►▓                  ┆      ← 2º
      ┆                ▓                  ▓─calcularTotal()─►▓      ← 3º
      ┆                ▓                  ▓◄- - -valor- - - -▓      ← 4º
      ┆                ▓◄- -confirmacao- -▓                  ┆      ← 5º
      ┆◄- -"Pedido OK"-▓                  ┆                  ┆      ← 6º
      ┆                ┆                  ┆                  ┆
```

**Lendo em voz alta:** *"O cliente clica em finalizar na tela; a tela pede ao controlador para fechar o pedido; o controlador manda o pedido calcular o total; o pedido devolve o valor; o controlador confirma para a tela; a tela avisa o cliente."*

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

💡 **Em português claro — objeto × classe como participante:**

```text
OBJETO  →  é UM pedido específico, o de número 4712.
           "Pedido 4712, calcule o seu total."
           Só esse pedido responde.

CLASSE  →  é a FÁBRICA de pedidos, o conceito.
           "Classe Pedido, quantos pedidos existem hoje?"
           Não faz sentido perguntar isso a UM pedido — é uma
           informação do conjunto. Por isso a mensagem vai para a CLASSE.
```

🔎 **Exemplo prático dos três formatos:**

```text
╔════════════════════╗    ← objeto ANÔNIMO
║   :ItemPedido      ║      "um ItemPedido qualquer"
╚════════════════════╝      use quando não precisa distinguir qual

╔════════════════════╗    ← objeto NOMEADO
║ item1:ItemPedido   ║      "aquele ItemPedido, o item1"
╚════════════════════╝      use quando o MESMO objeto aparece em vários pontos
                            e você precisa deixar claro que é ele

╔════════════════════╗    ← CLASSE (nome NÃO sublinhado)
║    ItemPedido      ║      "a classe em si"
╚════════════════════╝      use para operação ESTÁTICA, ex.: buscarPorCodigo()
```

🎯 **Regra prática:** na prova, **quase tudo é objeto anônimo** (`:Classe`). Só nomeie quando precisar apontar para o mesmo objeto duas vezes.

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

💡 **Em português claro — a diferença na vida real:**

```text
SÍNCRONA   → é como LIGAR para alguém e ficar na linha esperando a resposta.
              Você não faz mais nada até ele responder.

ASSÍNCRONA → é como mandar uma MENSAGEM no WhatsApp e continuar
              fazendo outra coisa. A resposta chega quando chegar.

RETORNO    → é a RESPOSTA voltando.
```

🔎 **Exemplo com os três tipos no mesmo diagrama:**

```text
   :ControladorPedido        :Pedido          :ServicoEmail
          ▓                     ┆                   ┆
          ▓──calcularTotal()───►▓                   ┆   ← SÍNCRONA (ponta cheia)
          ▓                     ▓                   ┆     o controlador PRECISA do valor
          ▓◄- - -1250.00- - - - ▓                   ┆   ← RETORNO (tracejada)
          ▓                     ┆                   ┆
          ▓──enviarConfirmacao()─────────────────► ▓    ← ASSÍNCRONA (ponta aberta)
          ▓ (segue trabalhando sem esperar)        ▓      e-mail pode demorar, e o
          ▓                                        ▓      controlador não precisa esperar
```

🎯 **Como decidir na prova:**

> *"Quem mandou precisa da resposta para continuar?"*
> * **Precisa** → **síncrona** (ponta cheia). É o caso de quase tudo.
> * **Não precisa** → **assíncrona** (ponta aberta). Típico de e-mail, notificação, log, impressão.

⚠️ **O retorno é opcional no desenho.** Se ele não acrescenta informação, pode ser omitido — muitos diagramas só desenham o retorno quando o valor devolvido importa.

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

💡 **Em português claro:** é o objeto **chamando um método dele mesmo**, exatamente como `this.metodo()` em Java ou `self.metodo()` em Python.

🔎 **Exemplo — por que isso aparece:**

```text
   :ControladorPedido          :Pedido
          ▓                       ┆
          ▓───fechar()───────────►▓
          ▓                       ▓──┐
          ▓                       ▓  │ validarEstoque()   ← mensagem REFLEXIVA
          ▓                       ▓◄─┘                      (o Pedido chama a si mesmo)
          ▓                       ▓▓ ← foco de controle EMPILHADO
          ▓                       ▓──┐
          ▓                       ▓  │ calcularTotal()    ← outra reflexiva
          ▓                       ▓◄─┘
          ▓◄- - - - - - - - - - - ▓
```

**Por que desenhar isso?** Porque `validarEstoque()` e `calcularTotal()` são **operações da própria classe `Pedido`** — e o diagrama de interação existe justamente para **descobrir as operações**. Se você não desenhar, elas não aparecem no modelo de classes.

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

🔎 **Exemplo completo com criação E destruição — "adicionar item ao carrinho":**

```text
   :ControladorPedido        :Pedido
          ┆                     ┆
       ╔══╧══╗              ╔═══╧═══╗                       ← estes DOIS já existiam
       ║     ║              ║       ║                         (estão no TOPO)
       ╚══╤══╝              ╚═══╤═══╝
          ▓                     ┆
          ▓──adicionarItem()───►▓
          ▓                     ▓                ╔════════════════╗
          ▓                     ▓───create()────►║  :ItemPedido   ║ ← CRIADO agora
          ▓                     ▓                ╚════════╤═══════╝   (mais ABAIXO)
          ▓                     ▓                         ▓
          ▓                     ▓───setQtd(2)────────────►▓
          ▓                     ┆                         ┆
          ▓──removerItem()─────►▓                         ┆
          ▓                     ▓───destroy()────────────►▓
          ▓                     ┆                         ╳  ← DESTRUÍDO
```

💡 **Em português claro — por que a posição do retângulo importa:**

A **altura** em que o retângulo do objeto aparece é a **linha do tempo do nascimento dele**. Se ele está lá em cima junto com os outros, ele já existia. Se está no meio do desenho, é porque **nasceu naquele instante**.

🎯 **Como responder rápido a esse tipo de questão:** olhe **só a linha de cima do desenho**. Se todos os retângulos estão alinhados ali, **não há criação**. Se algum está mais baixo, **há**.

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

💡 **Em português claro:** o foco de controle é a **barra de "ocupado"** do objeto. Enquanto o retângulo está desenhado, aquele objeto **está executando alguma coisa**. Quando a barra acaba, ele terminou e voltou a ficar parado.

```text
LINHA TRACEJADA fina  →  o objeto EXISTE, mas está parado, esperando
RETÂNGULO sobre ela   →  o objeto está TRABALHANDO neste intervalo
```

🔎 **Exemplo — por que as barras têm tamanhos diferentes:**

```text
   :Tela        :Controlador        :Pedido
     ┆               ┆                 ┆
     ▓──fechar()────►▓                 ┆        ┐
     ▓               ▓──calcular()────►▓        │ o Controlador fica ocupado
     ▓               ▓                 ▓        │ o TEMPO INTEIRO, porque está
     ▓               ▓◄- -valor- - - - ▓        │ esperando o Pedido responder
     ▓               ▓                 ┆        │ (mensagem SÍNCRONA)
     ▓◄- - ok - - - -▓                 ┆        ┘
     ┆               ┆                 ┆
```

A barra do `:Controlador` é **mais alta** que a do `:Pedido` porque ele começou antes e só terminou depois que o Pedido devolveu o valor.

💡 **Sobre as barras empilhadas:** quando um objeto chama a si mesmo (mensagem reflexiva) ou uma chamada recursiva acontece, ele fica "ocupado dentro de ocupado" — por isso desenha-se **uma barra ligeiramente deslocada sobre a outra**.

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

🔎 **Exemplo — a mesma ideia nas duas notações:**

```text
NOTAÇÃO ANTIGA (UML 1)              NOTAÇÃO MODERNA (UML 2)

  :Contr.        :Conta               ┌───────────────────────────────┐
     ▓              ┆                 │ opt ╲ [saldo > 0]             │
     ▓─[saldo>0]───►▓                 │   ▓───sacar(valor)───►▓       │
     ▓  sacar()     ┆                 └───────────────────────────────┘

  :Contr.        :Item                ┌───────────────────────────────┐
     ▓              ┆                 │ loop ╲ [para cada item]       │
     ▓─*[p/ cada]──►▓                 │   ▓───calcular()─────►▓       │
     ▓  calcular()  ┆                 └───────────────────────────────┘
```

💡 **Por que a UML 2 trocou?** Porque o asterisco e os colchetes **não mostram até onde vai a repetição**. Se o laço tem 5 mensagens, você não consegue indicar isso com um `*`. O quadro `loop` **desenha uma caixa em volta** das 5 mensagens, deixando o escopo explícito.

⚠️ **Na prova:** se aparecer `*` ou `[condição]` solto numa mensagem, **não está errado** — é a notação antiga, ainda aceita. Mas se perguntarem qual é a forma recomendada pela UML 2, a resposta é **fragmento combinado**.

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

💡 **Em português claro — cada operador traduzido para programação:**

| Operador | É o mesmo que, em código... | 🔎 Exemplo na loja online |
| --- | --- | --- |
| **`alt`** | `if / else if / else` | se pagou com PIX → confirma na hora; **senão** (cartão) → manda para a operadora |
| **`opt`** | `if` **sem** `else` | **se** o cliente marcou "quero nota fiscal", emite a nota |
| **`par`** | duas *threads* ao mesmo tempo | ao mesmo tempo: manda o e-mail **e** atualiza o estoque |
| **`loop`** | `for` / `while` | **para cada** item do carrinho, calcula o subtotal |
| **`ref`** | chamar **outra função** | *"aqui entra o diagrama `Autenticar cliente`, que está em outra folha"* |
| **`break`** | `break` / `return` antecipado | se o cartão for recusado, **interrompe** e sai do fluxo |
| **`sd`** | o nome do arquivo | a moldura que envolve o diagrama inteiro |

🔎 **Os quatro principais desenhados, na loja online:**

```text
┌───────────────────────────────────────────┐   ┌───────────────────────────────┐
│ alt ╲                                     │   │ opt ╲  [quer nota fiscal]     │
├───────────────────────────────────────────┤   ├───────────────────────────────┤
│  [forma = PIX]                            │   │   ▓───emitirNota()───►▓       │
│    ▓──confirmarNaHora()───►▓              │   └───────────────────────────────┘
│ - - - - - - - - - - - - - - - - - - - - - │      só executa SE a condição
│  [else]                                   │      for verdadeira; não tem "senão"
│    ▓──enviarParaOperadora()───►▓          │
└───────────────────────────────────────────┘

┌───────────────────────────────────────────┐   ┌───────────────────────────────┐
│ loop ╲  [para cada item do carrinho]      │   │ par ╲                         │
├───────────────────────────────────────────┤   ├───────────────────────────────┤
│    ▓──calcularSubtotal()───►▓             │   │   ▓──enviarEmail()───►▓       │
└───────────────────────────────────────────┘   │ - - - - - - - - - - - - - - - │
   repete a mensagem várias vezes               │   ▓──baixarEstoque()─►▓       │
                                                └───────────────────────────────┘
                                                   os dois ao MESMO TEMPO
```

🎯 **A diferença `alt` × `opt` em uma frase:**

```text
alt →  tem linha TRACEJADA dividindo a caixa (dois ou mais caminhos)
opt →  NÃO tem divisão (um caminho só, que roda ou não roda)
```

💡 **Sobre o aninhamento (o que caiu na FEPESE):** quando um quadro está **dentro** do outro, para chegar na mensagem de dentro você precisa **passar pelas duas portas**:

```text
┌─────────────────────────────────────────────┐
│ opt ╲  [conectado]                          │  ← 1ª porta: precisa estar conectado
│  ┌────────────────────────────────────────┐ │
│  │ opt ╲  [êxito]                         │ │  ← 2ª porta: E precisa ter dado êxito
│  │   ▓────6: mensagem()────►▓             │ │
│  └────────────────────────────────────────┘ │
└─────────────────────────────────────────────┘

Para a mensagem 6 acontecer:  conectado = true  E  êxito = true
```

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

💡 **Em português claro — a diferença entre DSS e diagrama de sequência comum:**

```text
DIAGRAMA DE SEQUÊNCIA COMUM        DIAGRAMA DE SEQUÊNCIA DO SISTEMA (DSS)
"como funciona por dentro"          "o que o usuário vê acontecer"

 Ator  :Tela  :Contr.  :Pedido       Ator          :Sistema
  ┆      ┆      ┆        ┆            ┆                ┆
  ┆─────►▓                            ┆───finalizar()─►▓
  ┆      ▓─────►▓                     ┆◄- -"Pedido OK"-▓
  ┆      ┆      ▓───────►▓            ┆                ┆
                                      ↑
 vários objetos INTERNOS         UMA caixa preta só
```

⚠️ **No DSS você NÃO desenha objetos internos.** O sistema é **uma caixa só**, chamada `:Sistema`. Desenhar `:Tela`, `:Controlador` etc. num DSS é erro — isso pertence ao diagrama de sequência de projeto, que vem depois.

🎯 **Por que existe esse formato?** Porque na **análise** você ainda não decidiu quais classes vão existir. O DSS registra apenas **o que entra e o que sai do sistema**, que é o que o caso de uso já diz. As classes internas aparecem depois.

🔎 **Passo a passo, traduzindo um caso de uso linha por linha:**

| Linha do caso de uso | Quem faz | Vira o quê no DSS |
| --- | --- | --- |
| "O sistema apresenta a lista de pedidos" | sistema | **retorno** `- -listaPedidos- -►` |
| "O gerente escolhe o pedido" | ator | **mensagem** `escolherPedido()` |
| "O sistema solicita o CPF" | sistema | ⚠️ **nada** — é comportamento interno da tela |
| "O gerente informa o CPF" | ator | **mensagem** `identificarConsultor(CPF)` |
| "O gerente confirma" | ator | **mensagem** `confirmar()` |
| "O sistema registra a responsabilidade" | sistema | ⚠️ **nada** — é o efeito interno da confirmação |

⚠️ **A regra que mais vale ponto:** nem todo passo do caso de uso vira mensagem. Só viram mensagem os passos em que o **ator entrega alguma coisa ao sistema**, e só viram retorno os passos em que o **sistema mostra alguma coisa ao ator**. "O sistema solicita", "o sistema registra", "o sistema valida" **não viram nada** — são o que acontece **dentro** da caixa preta.

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

💡 **Em português claro — a numeração é igual a um sumário de livro:**

```text
Capítulo 1              ← mensagem 1
  Seção 1.1             ← mensagem 1.1  (acontece DENTRO da 1)
  Seção 1.2             ← mensagem 1.2
Capítulo 2              ← mensagem 2    (só começa depois que a 1 TERMINOU inteira)
  Seção 2.1             ← mensagem 2.1
```

Você lê o capítulo 1 **inteiro** (com todas as seções dele) **antes** de começar o capítulo 2. É exatamente assim que se lê a numeração do diagrama de comunicação.

🎯 **Como numerar do zero, em 4 regras:**

```text
1. A mensagem que vem DE FORA (do ator) NÃO recebe número.
2. As mensagens que saem do PRIMEIRO objeto são 1, 2, 3...
3. Se o objeto B, ao tratar a mensagem 1, precisa chamar alguém,
   essa chamada é 1.1 — ganha o número da "mãe" mais um nível.
4. Cada nível de profundidade acrescenta um ponto: 1 → 1.1 → 1.1.1
```

🔎 **Convertendo um diagrama de sequência em comunicação, passo a passo:**

```text
SEQUÊNCIA (a ordem está na vertical)

  Cliente   :Tela     :Contr.    :Pedido    :Estoque
     ┆        ┆          ┆          ┆           ┆
     ┆──────►▓                                         ← inicial (sem número)
     ┆        ▓────────►▓                              ← 1
     ┆        ┆          ▓────────►▓                   ← 1.1
     ┆        ┆          ▓                  ▓          ← 1.2
     ┆        ▓────────►▓                              ← 2


COMUNICAÇÃO (a ordem está nos NÚMEROS)

   Cliente ──finalizar()──► :Tela
                              │
                              │ 1: fecharPedido()
                              │ 2: gerarRecibo()
                              ▼
                        :ControladorPedido
                          ╱            ╲
            1.1: calcular()            1.2: baixar()
                    ╱                      ╲
              :Pedido                    :Estoque
```

⚠️ **Repare no ganho e na perda:** o diagrama de comunicação **ocupa muito menos espaço** (cresce em duas direções), mas para saber a ordem você **tem que ler os números** — não dá para "ver" olhando.

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

💡 **Em português claro — "equivalência semântica" quer dizer o quê?**

Quer dizer que os dois **carregam exatamente a mesma informação**. É como a mesma música escrita em partitura ou em cifra: muda o jeito de anotar, **não muda a música**. Por isso um programa consegue converter um no outro **automaticamente, sem perder nada**.

⚠️ **A pegadinha:** se a banca disser *"o diagrama de sequência é mais poderoso / expressa mais coisas que o de comunicação"*, isso é **FALSO**. Eles têm o **mesmo poder de expressão**. O que muda é a **facilidade de leitura**, não o conteúdo.

🎯 **Quando escolher cada um, na prática:**

```text
Poucos objetos, muitas mensagens em ordem complicada  →  SEQUÊNCIA
   (a ordem é o que importa, e ela fica óbvia na vertical)

Muitos objetos, poucas mensagens                      →  COMUNICAÇÃO
   (o desenho da sequência ficaria larguíssimo)

Precisa de if / laço / paralelo                       →  SEQUÊNCIA, obrigatoriamente
   (o de comunicação não tem notação para isso)
```

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

💡 **Em português claro:** imagine que você tem **cinco diagramas de sequência** separados (autenticar, escolher produto, pagar, emitir nota, enviar). O diagrama de visão geral é a **folha de rosto** que mostra **em que ordem e sob quais condições** cada um desses cinco acontece.

```text
É um FLUXOGRAMA onde cada caixa, em vez de conter um texto,
contém um MINI DIAGRAMA DE SEQUÊNCIA (ou uma referência a um).
```

🔎 **Exemplo — a compra na loja online vista de cima:**

```text
                    ●
                    │
          ┌─────────┴──────────┐
          │ ref  Autenticar    │        ← "o diagrama Autenticar está em outra folha"
          └─────────┬──────────┘
                    ◇  [autenticado?]
              ┌─────┴──────┐
        [não] │            │ [sim]
              ▼            ▼
      ┌──────────────┐  ┌──────────────────────┐
      │ sd Recusar   │  │ sd Processar pedido  │   ← mini diagrama de sequência
      │  ▓──erro()──►│  │  ▓──calcular()──►▓   │      desenhado dentro da caixa
      └──────┬───────┘  └──────────┬───────────┘
             │                     │
             └──────────┬──────────┘
                        ▼
                        ◉
```

🎯 **Para que serve:** para **modularizar**. Em vez de um diagrama de sequência gigante com 40 mensagens e 6 quadros `alt` aninhados, você quebra em pedaços pequenos e usa a visão geral para amarrar tudo.

⚠️ **O que a banca pergunta sobre ele:** basicamente uma coisa só — que ele é a **mistura de diagrama de ATIVIDADES com diagrama de SEQUÊNCIA**. A notação de fluxo (início, decisão, fim) vem das **atividades**; o conteúdo das caixas vem da **sequência**.

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

💡 **Em português claro:** nos outros diagramas, o tempo é só uma **ordem** ("isto vem antes daquilo"). No diagrama de temporização, o tempo é uma **medida**: quantos segundos, quantos milissegundos.

🔎 **O exemplo da cafeteira, desenhado:**

```text
                 0s      10s     20s     30s     40s
                 │        │       │       │       │
        ╭────────┴────────┴───────┴───────┴───────┴───╮
BOMBA   │ ligada ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔╲              │
        │ deslig ___________________________▁▁▁▁▁▁▁▁▁ │
        ╰──────────────────────────────────────────────╯
                 ├──10s──┤            ├────15s────┤
                 (regra 1)              (regra 2)
        ╭──────────────────────────────────────────────╮
CHAPA   │ ligada ________▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔╲        │
        │ deslig ▔▔▔▔▔▔▔▔                      ▁▁▁▁▁▁ │
        ╰──────────────────────────────────────────────╯

Regra 1: a chapa só pode acender 10s DEPOIS da bomba ligar.
Regra 2: acabou a água → bomba desliga → a chapa tem no MÁXIMO 15s de vida.
```

⚠️ **Por que o slide diz que tem "pouca utilidade para aplicações comerciais"?** Porque num sistema de loja, banco ou RH **ninguém se importa se a operação levou 200 ms ou 300 ms**. Já num **marca-passo**, num **freio ABS** ou numa **cafeteira**, milissegundos são requisito de segurança — e aí o diagrama faz sentido.

🎯 **Na prova ele quase não cai**, e quando cai é para você reconhecer que: (a) veio da **engenharia eletrônica**; (b) o foco é **restrição de tempo**; (c) tem **pouca utilidade comercial**.

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

> **Como ler esta parte:** o texto dos slides está preservado, marcado com 📌.
> O que foi acrescentado para facilitar vem marcado com 💡 (**em português claro**) e 🔎 (**exemplo**).
>
> 🧵 **Exemplo que vai acompanhar a parte inteira:** um **Pedido** de uma loja online. Cada elemento novo será mostrado nesse mesmo pedido, para você ver tudo se encaixando.

## 2.1 A ideia

📌 **Slide 2:**

> Objetos do mundo real se encontram em **estados particulares** a cada momento (uma jarra está cheia de líquido; um pedido está pago). Um objeto **muda de estado quando acontece um evento** interno ou externo ao sistema. Quando um objeto muda de um estado para outro, diz-se que ele realizou uma **transição** entre estados.

💡 **Em português claro:**

O DTE responde a uma única pergunta: **"por quais situações este objeto passa ao longo da vida dele, e o que faz ele pular de uma para outra?"**

```text
        ESTADO           EVENTO            ESTADO
   "como a coisa está"  "o que aconteceu"  "como ela ficou"

   Aguardando pagamento  ──pagar()──►      Pago
   (situação)            (o gatilho)       (nova situação)
```

Três palavras resolvem quase tudo:

| Palavra | Pergunta que ela responde | Exemplo no Pedido |
| --- | --- | --- |
| **Estado** | *Como a coisa **está** agora?* | O pedido **está pago** |
| **Evento** | *O que **aconteceu**?* | O cliente **pagou** |
| **Transição** | *Para onde ela **foi**?* | De `Aguardando pagamento` para `Pago` |

🔎 **O DTE completo do nosso Pedido** (guarde esta figura, ela vai reaparecer):

```text
  ●
  │
  ▼
╭──────────────────────╮  registrarPagamento()  ╭────────╮
│ Aguardando pagamento │ ─────────────────────► │  Pago  │
╰──────────┬───────────╯                        ╰───┬────╯
           │                                        │ despachar()
           │ cancelar()                             ▼
           │                                   ╭──────────╮
           │                                   │ Enviado  │
           ▼                                   ╰───┬──────╯
     ╭────────────╮                                │ confirmarEntrega()
     │ Cancelado  │                                ▼
     ╰─────┬──────╯                           ╭──────────╮
           │                                  │ Entregue │
           ▼                                  ╰────┬─────╯
           ◉                                       ▼
                                                   ◉
```

⚠️ **O erro número 1 de quem está começando:** confundir **estado** com **evento**.

```text
ESTADO  → adjetivo / particípio → "Pago", "Enviado", "Cancelado", "Ativo", "Atrasado"
          (é uma SITUAÇÃO que DURA no tempo)

EVENTO  → verbo no infinitivo   → "Pagar", "Enviar", "Cancelar", "Registrar devolução"
          (é um ACONTECIMENTO instantâneo)
```

Teste rápido: se você consegue dizer *"o objeto **está** ___"*, é **estado**. Se você diz *"alguém **fez** ___"*, é **evento**.

## 2.2 Os seis elementos de um DTE

📌 **Slide 4:** Estado · Transição · Evento (Trigger) · Condição de guarda · Ação · Atividade.
*(Um DTE pode conter ainda transições internas, estados aninhados, estados concorrentes e subestados.)*

💡 **Em português claro — o que cada um dos seis faz:**

| Elemento | Em uma frase | No Pedido |
| --- | --- | --- |
| **Estado** | a situação em que o objeto está | `Pago` |
| **Transição** | a seta que liga dois estados | de `Aguardando pagamento` para `Pago` |
| **Evento** | o acontecimento que dispara a seta | `registrarPagamento()` |
| **Condição de guarda** | um "só se..." que trava a seta | `[valorPago >= total]` |
| **Ação** | algo rápido feito **durante** a seta | `/ darBaixaNoEstoque()` |
| **Atividade** | algo demorado feito **dentro** do estado | `do/ separarItens()` |

```text
        ╭──────────────────────╮
        │ Aguardando pagamento │
        ╰──────────┬───────────╯
                   │
     registrarPagamento(valorPago) [valorPago >= total] / darBaixaNoEstoque()
     └──── EVENTO ──────────────┘  └──── GUARDA ─────┘   └───── AÇÃO ──────┘
                   │
                   ▼
        ╭─────────────────────────╮
        │ Em separação            │
        ├─────────────────────────┤
        │ do/ separarItens()      │  ← ATIVIDADE
        ╰─────────────────────────╯

     ← tudo isso junto é UMA TRANSIÇÃO →
```

### Estado

📌 **Slide 5:**

> Um estado é uma **situação na vida de um objeto** durante a qual ele **satisfaz alguma condição** ou **realiza alguma atividade**. Cada estado é determinado pelos **valores de seus atributos** e (ou) pelas suas **ligações com outros objetos**.
>
> Notação: **retângulo com bordas arredondadas**.

💡 **Em português claro — o que significa "determinado pelos valores dos atributos e pelas ligações":**

O estado **não é um campo mágico** que alguém preenche. Ele é a **consequência** do que está guardado no objeto. Existem duas formas de o objeto "saber" em que estado está:

**1. Pelos valores dos ATRIBUTOS** — olhando os campos do próprio objeto:

```text
Pedido
├── dataPagamento = (vazio)   ┐
└── dataEnvio     = (vazio)   ┘→ estado: Aguardando pagamento

Pedido
├── dataPagamento = 21/09     ┐
└── dataEnvio     = (vazio)   ┘→ estado: Pago

Pedido
├── dataPagamento = 21/09     ┐
└── dataEnvio     = 22/09     ┘→ estado: Enviado
```

**2. Pelas LIGAÇÕES com outros objetos** — olhando com quem o objeto está associado:

🔎 É exatamente o caso do gabarito da prova da `Siscon`:

```text
Consultor SEM ligação com nenhum PedidoServico     → estado: Livre
Consultor COM ligação de responsabilidade          → estado: Responsável por pedido
Consultor COM ligação de trabalho                  → estado: Trabalhando em um pedido
```

Nada mudou **dentro** do consultor — o que mudou foi **com quem ele está ligado**. Isso também é um estado.

📌 **Slide 6 — regra que cai:**

| | Estado inicial | Estado final |
| --- | --- | --- |
| Notação | círculo preenchido ● | círculo com anel ◉ |
| Quantidade | **só pode haver UM** por DTE | **pode haver MAIS DE UM** |
| Obrigatório? | sim | **não, é opcional** |
| Significa | o objeto foi **criado** | **fim do ciclo de vida** do objeto |

> A restrição de um só estado inicial serve para **definir a partir de que ponto o DTE deve começar a ser lido**. A exceção é quando se trata de estados aninhados, concorrentes ou compostos.

💡 **Em português claro — três coisas que confundem aqui:**

**1. O ● NÃO é um estado.** É só um marcador de "a leitura começa aqui". O primeiro estado de verdade é aquele para onde a seta do ● aponta.

```text
  ●  ──────► ╭──────────────────────╮
  ▲          │ Aguardando pagamento │  ← ESTE é o primeiro estado
  │          ╰──────────────────────╯
  └── isto é só o "você está aqui" do diagrama
```

**2. Por que só pode haver UM ● ?** Porque se houvesse dois, quem lê o diagrama não saberia por onde começar. É uma regra de **legibilidade**, não de lógica.

**3. Por que o ◉ é opcional, e pode ter vários?**

* **Opcional:** muitos objetos **nunca morrem**. Um `Cliente` cadastrado fica no sistema para sempre — o DTE dele não precisa de fim.
* **Vários:** um objeto pode acabar de **maneiras diferentes**, e fica mais legível desenhar um ◉ para cada final do que puxar setas longas para um único ponto.

```text
        ╭────────────╮                  ╭──────────╮
        │ Cancelado  │                  │ Entregue │
        ╰─────┬──────╯                  ╰─────┬────╯
              ▼                               ▼
              ◉                               ◉
          (fim ruim)                      (fim bom)

        DOIS estados finais no mesmo DTE → permitido e comum
```

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

💡 **Em português claro — lendo a sintaxe pedaço por pedaço:**

🔎 Um rótulo completo de transição no nosso Pedido:

```text
registrarPagamento(valorPago) [valorPago >= total] / darBaixaNoEstoque()
└──────┬──────────┘└───┬────┘ └────────┬────────┘   └────────┬────────┘
       │               │               │                     │
    EVENTO         PARÂMETRO         GUARDA                 AÇÃO
  "o que          "o dado que      "só passa se          "o que o sistema
  aconteceu"      veio junto"       isso for              faz no caminho"
                                    verdade"
```

**Lendo em voz alta:**

> *"**Quando** o pagamento for registrado, **se** o valor pago for maior ou igual ao total, **então** o pedido vai para `Pago`, e **no caminho** o sistema dá baixa no estoque."*

🎯 **Macete para nunca inverter guarda e ação:**

```text
[  ]  são colchetes  →  parecem uma PORTA fechada  →  é a CONDIÇÃO (guarda)
 /    é uma barra    →  parece um RISCO de caneta  →  é o que se FAZ (ação)
```

Outro jeito de lembrar: a ordem no rótulo é a **ordem do tempo**.

```text
1º o evento acontece   →  2º testa-se a condição  →  3º executa-se a ação
   registrarPagamento()      [valorPago >= total]      / darBaixaNoEstoque()
```

💡 **Todas as partes, menos o evento, são opcionais:**

```text
pagar()                                    → só evento (o mais comum nas provas)
pagar() [valorPago >= total]               → evento + guarda
pagar() / darBaixa()                       → evento + ação
pagar(v) [v >= total] / darBaixa()         → tudo
[estoqueDisponivel]                        → só guarda (usado depois do ponto de junção)
(rótulo vazio)                             → transição automática (ver 2.3)
```

### Evento (Trigger)

📌 **Slide 8:** um evento é **algo que acontece em algum ponto no tempo e que pode modificar o estado de um objeto**. Ex.: Realizar pedido, Pagar fatura, Devolver cheque.

💡 **Em português claro:** evento é o **gatilho**. É instantâneo — acontece e pronto. *Trigger*, em inglês, é literalmente "gatilho".

📌 **Slides 9 e 10 — os quatro tipos de evento:**

| Tipo | O que é | Cláusula |
| --- | --- | --- |
| **De chamada** | recebimento de uma **mensagem** de outro objeto; solicitação de serviço de um objeto a outro | — |
| **De sinal** | recebimento de um **sinal** de outro objeto | — |
| **Temporal** | passagem de um **intervalo de tempo** predefinido | **`after`** |
| **De mudança** | uma **condição que se torna verdadeira** (expressão lógica) | **`when`** |

💡 **Em português claro — os quatro tipos com exemplo de cada:**

| Tipo | A pergunta que ele responde | 🔎 Exemplo no Pedido | Como se escreve |
| --- | --- | --- | --- |
| **De chamada** | *alguém **pediu** para fazer isso?* | o atendente clica em "Confirmar pagamento" | `registrarPagamento()` |
| **De sinal** | *chegou um **aviso** de fora?* | a transportadora avisa que entregou | `entregaConfirmada` |
| **Temporal** | *passou **tempo** suficiente?* | 7 dias sem pagar → cancela sozinho | `after(7 dias)` |
| **De mudança** | *uma **condição** virou verdade?* | passou da data-limite de pagamento | `when(hoje > dataLimite)` |

⚠️ **Obs. literal do slide 9:** a diferença básica entre sinal e chamada é que **no evento de chamada o objeto que envia a mensagem fica esperando a execução**. O **evento de sinal raramente é utilizado**.

💡 **Em português claro — chamada × sinal:**

É **exatamente** a mesma diferença de mensagem **síncrona × assíncrona** do diagrama de sequência:

```text
EVENTO DE CHAMADA  =  mensagem SÍNCRONA   → quem chamou FICA ESPERANDO
   é como ligar para alguém e ficar na linha até ele responder

EVENTO DE SINAL    =  mensagem ASSÍNCRONA → quem mandou SEGUE A VIDA
   é como mandar uma mensagem no WhatsApp e continuar fazendo outra coisa
```

🎯 Como o slide diz que o **evento de sinal raramente é utilizado**, na prática quase todo evento que você vai escrever é **de chamada** (um verbo simples), **temporal** (`after`) ou **de mudança** (`when`).

🎯 `after(30 dias)` · `when(hoje = dataFimContrato + 1)` — os gabaritos das provas usam muito o `when`.

💡 **Como decidir entre `after` e `when`:**

```text
after(...) →  conta um PRAZO a partir de quando o objeto ENTROU no estado
              "after(7 dias)" = 7 dias depois de chegar aqui

when(...)  →  vigia uma CONDIÇÃO o tempo todo, não importa há quanto tempo está no estado
              "when(hoje > dataLimite)" = no instante em que isso virar verdade
```

🔎 No gabarito da prova: `when(hoje = dataFimContrato + 1)` significa *"no dia seguinte ao fim do contrato, o consultor vira inativo automaticamente"*. Ninguém clica em nada — o sistema percebe sozinho que a condição ficou verdadeira.

### Condição de guarda

📌 **Slide 11:**

> Uma condição de guarda (sentinela) é uma **expressão de valor lógico**. Uma transição com guarda é disparada **somente se o evento associado ocorre E a condição de guarda é verdadeira**. Se uma transição **não** tiver guarda, ela **sempre** será disparada quando o evento ocorrer. A expressão é sempre apresentada **entre colchetes**.

💡 **Em português claro:** a guarda é o **porteiro** da transição. O evento **bate na porta**; a guarda decide **se deixa passar**.

```text
evento acontece  +  guarda VERDADEIRA  →  ✅ transição dispara
evento acontece  +  guarda FALSA       →  ❌ nada acontece, o objeto FICA onde está
evento NÃO acontece + guarda verdadeira →  ❌ nada acontece (a guarda sozinha não dispara nada)
SEM guarda + evento acontece            →  ✅ dispara SEMPRE
```

⚠️ **O ponto mais importante:** a guarda **não dispara nada sozinha**. Ela só **libera ou bloqueia** um evento que já aconteceu. Quem dispara é sempre o evento.

🔎 **Exemplo no Pedido:**

```text
                            registrarPagamento(v) [v >= total]
   Aguardando pagamento  ───────────────────────────────────────►  Pago
```

```text
Cliente paga R$ 100 de um pedido de R$ 100  →  [100 >= 100] é VERDADE  → vai para Pago ✅
Cliente paga R$  60 de um pedido de R$ 100  →  [ 60 >= 100] é FALSO    → continua Aguardando ❌
```

### Ação × Atividade

📌 **Slides 12 e 13:**

| | **Ação** | **Atividade** |
| --- | --- | --- |
| Onde fica | **na linha da transição**, precedida de `/` | **dentro do estado**, com a cláusula `do` |
| Duração | tempo **insignificante** | tem duração |
| **Pode ser interrompida?** | **NÃO** | **SIM** |
| Quando executa | **só se a transição for disparada** | continuamente, enquanto o objeto está no estado |

⚠️ Essa é **a** diferença entre ação e atividade: **atividade pode ser interrompida, ação não**.

💡 **Em português claro:**

```text
AÇÃO       →  acontece NA SETA, é instantânea, ninguém consegue parar no meio
              é como apertar um interruptor: ou apertou, ou não apertou

ATIVIDADE  →  acontece DENTRO DO ESTADO, demora, e PODE ser cancelada no meio
              é como uma máquina de lavar rodando: dá para abrir e parar
```

🔎 **Os dois no nosso Pedido:**

```text
                registrarPagamento() / darBaixaNoEstoque()
                                       └──── AÇÃO ────┘
                                       instantâneo: subtrai 1 do estoque e acabou
    Aguardando pagamento ──────────────────────────────────►  ╭─────────────────────────╮
                                                              │ Em separação            │
                                                              ├─────────────────────────┤
                                                              │ do/ separarItens()      │ ← ATIVIDADE
                                                              ╰─────────────────────────╯
                                                                demora: o funcionário anda
                                                                pelo estoque pegando cada item.
                                                                Se o cliente cancelar no meio,
                                                                a separação PARA.
```

🎯 **Teste para decidir se é ação ou atividade:**

> *"Faz sentido alguém **cancelar isso no meio**?"*
> * **Não faz sentido** (é rápido demais) → **AÇÃO**, na seta, com `/`
> * **Faz sentido** (demora) → **ATIVIDADE**, dentro do estado, com `do/`

### Ponto de junção

📌 **Slide 14:**

> Em algumas situações, o próximo estado varia de acordo com o valor da condição de guarda. Isso é representado por um **ponto de junção**, desenhado como um **losango** em que chegam uma ou mais transições. A cada transição de **saída** está associada uma condição de guarda, e o objeto segue aquela cuja guarda for **verdadeira**.

💡 **Em português claro:** o ponto de junção é o **"se/senão"** do DTE. Um evento acontece e o objeto pode ir para **dois destinos diferentes** — o losango é a bifurcação que decide qual.

🔎 **Exemplo no Pedido:** depois de pagar, o pedido vai para separação **se houver estoque**; senão, fica aguardando reposição.

```text
                          registrarPagamento()
   Aguardando pagamento ─────────────────────────►  ◇
                                                   ╱ ╲
                              [tem estoque]       ╱   ╲       [else]
                                                 ▼     ▼
                                    ╭──────────────╮  ╭──────────────────────╮
                                    │ Em separação │  │ Aguardando reposição │
                                    ╰──────────────╯  ╰──────────────────────╯
```

🎯 **Como usar corretamente:**

```text
· O evento fica na seta que ENTRA no losango.
· As guardas ficam nas setas que SAEM do losango.
· As guardas de saída têm que cobrir TODOS os casos — por isso
  costuma-se usar [else] em uma delas (era assim no gabarito do Atleta).
· Se você repetir o evento em cada saída, fica poluído. O losango existe
  justamente para escrever o evento UMA vez só.
```

⚠️ Sem o losango, você teria que desenhar **duas setas completas**, repetindo o evento nas duas:

```text
SEM losango (funciona, mas fica poluído):
   Aguardando ──registrarPagamento() [tem estoque]──► Em separação
   Aguardando ──registrarPagamento() [else]─────────► Aguardando reposição

COM losango (mais limpo, é o que o gabarito faz):
   Aguardando ──registrarPagamento()──► ◇ ──[tem estoque]──► Em separação
                                          ──[else]─────────► Aguardando reposição
```

## 2.3 Cláusulas `entry`, `exit` e `do`

📌 **Slide 17:**

| Cláusula | Quando executa | Detalhe |
| --- | --- | --- |
| **`entry`** | no momento em que o objeto **entra** no estado | **independentemente do estado de onde ele veio** |
| **`exit`** | no momento em que o objeto **sai** do estado | **independentemente do estado para onde ele vai** |
| **`do`** | **continuamente**, durante o tempo em que o objeto permanece no estado | define uma **atividade em andamento** |

```text
╭──────────────────────────────╮
│  Digitando senha             │
├──────────────────────────────┤
│ entry/ definirEco(cInvisível)│
│ do/ aguardarEntrada()        │
│ exit/ definirEco(cVisível)   │
╰──────────────────────────────╯
```

💡 **Em português claro — pense em entrar e sair de uma sala:**

```text
entry/  →  o que você faz SEMPRE ao ENTRAR na sala   (acender a luz)
do/     →  o que você fica fazendo DENTRO da sala    (trabalhar)
exit/   →  o que você faz SEMPRE ao SAIR da sala     (apagar a luz)
```

O **"independentemente de onde veio / para onde vai"** é o detalhe que importa: **não interessa por qual porta você entrou** — a luz acende do mesmo jeito.

🔎 **Entendendo o exemplo do slide (`Digitando senha`):**

É a tela de digitar senha de um caixa eletrônico.

| Cláusula | O que faz ali | Por que |
| --- | --- | --- |
| `entry/ definirEco(cInvisível)` | ao entrar, os caracteres passam a ser exibidos como `••••` | é senha, ninguém pode ver |
| `do/ aguardarEntrada()` | enquanto está ali, fica esperando você digitar | é a atividade contínua |
| `exit/ definirEco(cVisível)` | ao sair, volta a exibir os caracteres normalmente | as próximas telas não são sigilosas |

🎯 **A vantagem prática:** se cinco transições diferentes chegam nesse estado, você **não precisa repetir** `definirEco(cInvisível)` em cada uma das cinco setas. Escreve **uma vez** como `entry/` e pronto.

🔎 **A mesma ideia no nosso Pedido:**

```text
╭─────────────────────────────╮
│ Em separação                │
├─────────────────────────────┤
│ entry/ imprimirEtiqueta()   │  ← ao entrar, sempre imprime a etiqueta
│ do/   separarItens()        │  ← enquanto está aqui, separa os itens
│ exit/ fecharCaixa()         │  ← ao sair, sempre fecha a caixa
╰─────────────────────────────╯
```

⚠️ **Slide 18:** a **inexistência de um evento** na transição entre dois estados indica que, **assim que a atividade (`do`) for concluída, a transição ocorrerá automaticamente**.

💡 **Em português claro:** uma seta **sem rótulo nenhum** quer dizer *"quando o `do/` terminar, vá sozinho para o próximo estado"*. Ninguém precisa clicar em nada.

🔎 **Exemplo:**

```text
╭─────────────────────────────╮                    ╭──────────────────╮
│ Em separação                │ ─────────────────► │ Pronto p/ envio  │
├─────────────────────────────┤     (seta SEM      ╰──────────────────╯
│ do/ separarItens()          │      rótulo)
╰─────────────────────────────╯

Leitura: "quando terminar de separar os itens, o pedido vira
          'Pronto para envio' automaticamente."
```

🎯 Compare as duas situações:

```text
COM evento na seta  →  alguém precisa FAZER alguma coisa para mudar de estado
SEM evento na seta  →  o estado muda SOZINHO quando a atividade do/ acaba
```

## 2.4 ⭐ Transição interna × Autotransição

**Este é o ponto mais cobrado do DTE em concurso.**

📌 **Slide 19 — Transição interna:**

> Os estados podem reagir a eventos **sem transição**, usando atividades internas. Uma transição interna é uma transição que **não faz o objeto mudar de estado**. Coloca-se o evento, a condição de guarda e a atividade **dentro da própria caixa do estado**.
>
> **As atividades internas NÃO disparam atividades de entrada e saída.** Essa é a grande diferença entre as atividades internas e as autotransições.

📌 **Slide 20 — Autotransição:**

> Uma autotransição é uma transição onde o **estado de origem e o estado destino são iguais** e suas cláusulas **`entry` e `exit` SÃO executadas**.

💡 **Em português claro — a analogia do quarto:**

Volte à ideia de "entrar e sair de uma sala", em que `entry/` **acende a luz** e `exit/` **apaga a luz**.

```text
TRANSIÇÃO INTERNA
   Você está no quarto e o telefone toca. Você atende, conversa e desliga.
   → Você REAGIU ao evento, mas NÃO SAIU do quarto.
   → A luz NUNCA foi apagada nem acesa.          entry/exit NÃO executam ❌

AUTOTRANSIÇÃO
   Você sai do quarto (APAGA a luz), fecha a porta, abre de novo
   e entra (ACENDE a luz).
   → Você terminou no MESMO quarto, mas passou pela porta DUAS vezes.
   → A luz foi apagada e acesa.                  entry/exit EXECUTAM ✅
```

⭐ **O resultado final é o mesmo (você está no quarto), mas o caminho é diferente — e é por isso que os dois NÃO são equivalentes.**

| | **Transição interna** | **Autotransição** |
| --- | --- | --- |
| Notação | escrita **dentro** da caixa do estado | **seta que sai e volta** para o mesmo estado |
| Muda de estado? | Não | Sai e volta ao mesmo estado |
| Executa `entry` / `exit`? | **NÃO** ❌ | **SIM** ✅ |

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

💡 **Lendo o exemplo `Digitando senha` linha por linha:**

```text
╭──────────────────────────────────╮
│ Digitando senha                  │
├──────────────────────────────────┤
│ entry/ definirEco(cInvisível)    │ ← só ao ENTRAR na tela
│ caractere(c) / tratarCaracter(c) │ ← TRANSIÇÃO INTERNA: a cada tecla digitada
│ ajuda / exibirAjuda(invisível)   │ ← TRANSIÇÃO INTERNA: se apertar F1
│ exit/ definirEco(cVisível)       │ ← só ao SAIR da tela
╰──────────────────────────────────╯
```

🔎 **Simulando o que acontece quando você digita a senha `123`:**

```text
Você entra na tela      →  entry/ definirEco(cInvisível)   ← executa UMA vez
Você digita "1"         →  tratarCaracter('1')             ← só a transição interna
Você digita "2"         →  tratarCaracter('2')             ← só a transição interna
Você digita "3"         →  tratarCaracter('3')             ← só a transição interna
Você aperta ENTER       →  exit/ definirEco(cVisível)      ← executa UMA vez
```

⚠️ **Repare:** o `definirEco` executou **exatamente uma vez** na entrada e **uma vez** na saída, mesmo você tendo digitado 3 teclas.

**Se `caractere(c)` fosse uma AUTOTRANSIÇÃO em vez de transição interna**, o resultado seria absurdo:

```text
Você entra na tela      →  entry/ definirEco(cInvisível)
Você digita "1"         →  exit/ definirEco(cVisível)      ← a senha APARECE na tela!
                           tratarCaracter('1')
                           entry/ definirEco(cInvisível)   ← e some de novo
Você digita "2"         →  exit/ definirEco(cVisível)      ← aparece de novo!
                           ...
```

🎯 **É por isso que a diferença existe:** a senha ficaria **piscando na tela a cada tecla**. A transição interna existe exatamente para o objeto **reagir sem sair do estado**.

🧪 **Questão CESGRANRIO 2011 (caiu na prova):** *"Os dois diagramas são equivalentes entre si, PORQUE modelar o evento02 com uma transição recursiva é equivalente a modelar o evento02 com uma atividade interna."*
→ Gabarito: **as duas afirmações são FALSAS**. Não são equivalentes, justamente porque a **autotransição dispara `entry`/`exit`** e a **transição interna não**.

💡 **Traduzindo o enunciado dessa questão:**

```text
"transição recursiva"  =  AUTOTRANSIÇÃO  (a seta que sai e volta)
"atividade interna"    =  TRANSIÇÃO INTERNA (escrita dentro da caixa)

A banca quis saber se você sabe que uma DISPARA entry/exit e a outra NÃO.
Como não disparam a mesma coisa, os diagramas NÃO são equivalentes
→ a afirmação I é falsa, e a razão II também é falsa.
```

## 2.5 Estados compostos, aninhados e concorrentes

📌 **Slide 23 — Estados aninhados / compostos:**

> Um estado que contém diversos outros é dito **composto**. **Todos os estados dentro de um estado composto HERDAM qualquer transição deste último.** O uso de estados compostos geralmente torna um DTE **mais legível**.

💡 **Em português claro — o que significa "herdar as transições":**

Se o estado composto tem uma seta saindo dele, essa seta vale para **todos os estados de dentro**, sem que você precise desenhar uma seta para cada um.

🔎 **Exemplo real — é exatamente o que o gabarito da prova da `Siscon` fez:**

**SEM estado composto** — três setas idênticas, poluindo o diagrama:

```text
   ╭───────────────────────────╮ ──registrarAfastamento()──┐
   │ Livre                     │                           │
   ╰───────────────────────────╯                           │
   ╭───────────────────────────╮ ──registrarAfastamento()──┤
   │ Responsável por pedido    │                           ├──► ╭──────────╮
   ╰───────────────────────────╯                           │    │ Afastado │
   ╭───────────────────────────╮ ──registrarAfastamento()──┘    ╰──────────╯
   │ Trabalhando em um pedido  │
   ╰───────────────────────────╯
```

**COM estado composto** — uma seta só:

```text
   ╭─── Ativo ──────────────────────────────╮
   │  ╭───────╮   ╭────────────────────╮    │
   │  │ Livre │   │ Responsável p/ ped.│    │ ──registrarAfastamento()──► ╭──────────╮
   │  ╰───────╯   ╰────────────────────╯    │                            │ Afastado │
   │  ╭──────────────────────────╮          │                            ╰──────────╯
   │  │ Trabalhando em um pedido │          │
   │  ╰──────────────────────────╯          │
   ╰────────────────────────────────────────╯
```

**Leitura:** *"de **qualquer** subestado de `Ativo` — esteja o consultor livre, responsável ou trabalhando — o evento `registrarAfastamento()` leva para `Afastado`."*

🎯 **Quando usar na prova:** sempre que você perceber que **várias setas iguais** saem de estados diferentes para o mesmo destino, **agrupe** esses estados num composto. Além de economizar desenho, é o que o gabarito faz.

📌 **Slides 26 e 27 — Estados concorrentes** (ou paralelos, ou compostos ortogonais):

> Um estado concorrente é um **tipo especial de estado composto**. Um objeto em um estado concorrente pode, na verdade, se encontrar em **dois ou mais estados independentes**.

💡 **Em português claro:** o objeto está em **dois estados ao mesmo tempo**, porque são **dois assuntos que não interferem um no outro**.

🔎 **Exemplo fácil — um carro:**

```text
╭─── Carro ligado ─────────────────────────────╮
│  ╭─ Motor ────────────────────────────────╮  │
│  │  Marcha lenta ──acelerar──► Acelerando │  │  ← assunto 1: velocidade
│  │              ◄──frear─────             │  │
│  ├────────────────────────────────────────┤  │  ← linha TRACEJADA
│  │  Faróis apagados ──ligarFarol──► Acesos│  │  ← assunto 2: iluminação
│  │                 ◄──desligarFarol──     │  │
│  ╰────────────────────────────────────────╯  │
╰──────────────────────────────────────────────╯

O carro pode estar:  Acelerando + Faróis acesos
                  ou Acelerando + Faróis apagados
                  ou Marcha lenta + Faróis acesos
                  ou Marcha lenta + Faróis apagados
```

⭐ **Por que separar em duas regiões?** Porque acender o farol **não tem nada a ver** com acelerar. Se você colocasse tudo numa região só, precisaria de **4 estados** (`AcelerandoComFarol`, `AcelerandoSemFarol`, `LentaComFarol`, `LentaSemFarol`) — e com um terceiro assunto viraria 8. As regiões evitam essa explosão.

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

💡 **Traduzindo o exemplo do slide:** é o tempo (clima). A **região 1** cuida da hora do dia (`Day` ↔ `Night`, mudando ao pôr do sol e ao nascer do sol). A **região 2** cuida da temperatura (`Warm` ↔ `Cold`, mudando com a frente fria e a frente quente). São independentes: pode estar **de dia e frio**, **de noite e quente**, e assim por diante.

🎯 **Composto × Concorrente — a diferença:**

```text
COMPOSTO simples  →  o objeto está em UM subestado por vez
                     (Livre OU Responsável OU Trabalhando)

CONCORRENTE       →  o objeto está em UM subestado DE CADA REGIÃO ao mesmo tempo
                     (Day E Cold)   ← repare no "E", e na linha tracejada no desenho
```

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

💡 **Em português claro — o mesmo roteiro em linguagem de prova:**

```text
1. QUAL classe? → a que o enunciado mandou ("faça o DTE da classe Aluguel").
2. Quais SITUAÇÕES essa classe atravessa? → grife os adjetivos no minimundo.
3. Quais ACONTECIMENTOS fazem ela pular de uma situação para outra? → grife os verbos.
4. De cada estado, para onde dá para ir? → desenhe as setas.
5. Tem evento que acontece SEM mudar de estado? → transição interna (raro nas provas).
6. Tem algum "somente se"? → guarda. Tem algo a executar no caminho? → ação.
7. Confira se os atributos/ligações que você citou existem no diagrama de classes.
8. Ponha o ● no começo e o(s) ◉ no(s) final(is).
9. Desenhe de cima para baixo, da esquerda para a direita.
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

🔎 **Exemplo completo, do texto ao desenho** — aplicando o roteiro a um trecho no estilo dos minimundos da prova:

> *"O aluguel é **confirmado** quando o cliente registrar o pagamento. Diz-se que um aluguel está **ativo** quando o equipamento foi retirado pelo cliente. Um aluguel é dito **concluído** quando o atendente registrar a devolução. Porém, podem ocorrer atrasos na devolução, fazendo com que o aluguel esteja **atrasado** — isso é verificado quando a data prevista para a devolução foi atingida e o aluguel não foi concluído. Caso o cliente registre o **cancelamento**, o equipamento volta a estar disponível. Isso pode ocorrer mesmo que o aluguel já tenha sido pago."*

**Passo 2 — grife os adjetivos/particípios → viram ESTADOS:**

```text
"confirmado"  "ativo"  "concluído"  "atrasado"  "cancelamento"
     ↓           ↓          ↓            ↓             ↓
 Confirmado    Ativo    Concluído    Atrasado     Cancelado
 (+ Solicitado, o estado inicial, porque o aluguel nasce quando é solicitado)
```

**Passo 3 — grife os verbos do ator → viram EVENTOS:**

```text
"registrar o pagamento"      →  Registrar pagamento
"o equipamento foi retirado" →  Registrar retirada
"registrar a devolução"      →  Registrar devolução
"registre o cancelamento"    →  Registrar cancelamento
```

**Passo 6 — procure condições de tempo/regra → viram `when(...)`:**

```text
"quando a data prevista para a devolução foi atingida
 e o aluguel não foi concluído"   →   when(hoje > dataPrevistaDevolucao)
```

**Passo 9 — o desenho:**

```text
    ●
    │
    ▼
╭─────────────╮  Registrar pagamento   ╭─────────────╮  Registrar retirada  ╭────────╮
│ Solicitado  │ ─────────────────────► │ Confirmado  │ ───────────────────► │ Ativo  │
╰──────┬──────╯                        ╰──────┬──────╯                      ╰───┬────╯
       │                                      │                                 │
       │ Registrar                            │ Registrar                       │
       │ cancelamento                         │ cancelamento                    │
       │                                      │              ┌──────────────────┤
       ▼                                      ▼              │                  │
    ╭────────────╮◄───────────────────────────┘              │   when(hoje >    │ Registrar
    │ Cancelado  │                                           │  dataPrevista)   │ devolução
    ╰──────┬─────╯                                           ▼                  ▼
           │                                          ╭────────────╮     ╭─────────────╮
           ▼                                          │  Atrasado  │     │  Concluído  │
           ◉                                          ╰──────┬─────╯     ╰──────┬──────╯
                                                             │ Registrar        │
                                                             │ devolução        │
                                                             └────────►─────────┤
                                                                                ▼
                                                                                ◉
```

⚠️ **Três detalhes desse desenho que valem ponto:**

1. **`Cancelado` recebe setas de dois estados diferentes** (`Solicitado` e `Confirmado`), porque o texto diz que o cancelamento pode ocorrer *"mesmo que o aluguel já tenha sido pago"*. Se aparecessem mais estados canceláveis, valeria agrupá-los num **estado composto**.
2. **`Atrasado` é alcançado por um `when(...)`**, e não por um verbo de ator. Ninguém clica em "atrasar" — o sistema percebe sozinho que a data passou. É o padrão que mais aparece nos gabaritos.
3. **Tanto `Atrasado` quanto `Ativo` vão para `Concluído`** pelo mesmo evento `Registrar devolução`. Um aluguel atrasado também pode ser devolvido.

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

💡 **Em português claro:** é o **mesmo modelo ficando mais detalhado** três vezes. Cada nível acrescenta coisas ao anterior — nada é jogado fora.

🔎 **A MESMA classe `Cliente` nos três níveis:**

```text
NÍVEL 1 — DOMÍNIO                 "o que o NEGÓCIO tem"
╔══════════════════════╗           Sem tipos, sem visibilidade, sem métodos técnicos.
║      Cliente         ║           Só o que um gerente da loja reconheceria.
╠══════════════════════╣
║ nome                 ║
║ CPF                  ║
║ dataNascimento       ║
╚══════════════════════╝

NÍVEL 2 — ESPECIFICAÇÃO           "como o SOFTWARE vai resolver"
╔══════════════════════════════╗   Aparecem tipos, visibilidade (+/-) e operações.
║      Cliente                 ║   Aparecem classes NOVAS que o negócio não tem,
╠══════════════════════════════╣   como ClienteDAO ou ControladorCliente.
║ - nome : String              ║
║ - CPF : String               ║
║ - dataNascimento : Date      ║
╠══════════════════════════════╣
║ + calcularIdade() : int      ║
║ + validarCPF() : boolean     ║
╚══════════════════════════════╝

NÍVEL 3 — IMPLEMENTAÇÃO           "o código de verdade"
public class Cliente {
    private String nome;
    private String cpf;
    private LocalDate dataNascimento;
    public int calcularIdade() { ... }
}
```

🎯 **A frase que mais cai:** o modelo de **domínio NÃO leva em conta a tecnologia**. Se aparecer `ClienteDAO`, `ClienteRepository` ou `String`/`int` num diagrama, ele **já não é mais de domínio**.

⚠️ **Na prova de vocês, o enunciado pede "o modelo CONCEITUAL de dados"** — isso é o **nível de domínio**. Por isso os gabaritos não têm tipos técnicos nem classes de infraestrutura.

## 3.2 Identificação de classes

📌 **Slide 4:** duas técnicas — **Análise dos Casos de Uso** e **Análise Textual de Abbott**.

### Análise dos Casos de Uso (Identificação Dirigida por Casos de Uso)

📌 **Slide 5:** a existência de uma classe **só pode se justificar se ela participar de alguma forma do comportamento externamente visível do sistema**.

💡 **Em português claro:** se você não consegue apontar **um caso de uso** em que a classe é usada, ela **não deveria existir** no modelo.

🔎 **Exemplo — o teste aplicado:**

```text
Classe "Pedido"      → aparece nos casos de uso "Fazer pedido",
                        "Consultar pedido", "Cancelar pedido"      ✅ fica

Classe "LogAuditoria"→ nenhum ator interage com ela; é decisão técnica  ❌ não é
                        classe de ANÁLISE (pode virar de projeto depois)

Classe "CorFavorita" → ninguém nunca consulta, cadastra nem usa       ❌ fora
```

🎯 **Use isso para cortar classes inventadas na discursiva.** Antes de desenhar uma classe, pergunte: *"em qual funcionalidade do minimundo ela aparece?"* Se não tiver resposta, não desenhe.

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

💡 **Em português claro — a analogia do restaurante:**

```text
<<boundary>> FRONTEIRA →  o GARÇOM
                          é quem fala com o cliente (o ator).
                          Só anota o pedido; não cozinha nada.

<<control>>  CONTROLE  →  o MAÎTRE / o gerente do salão
                          recebe do garçom, organiza a ordem das coisas,
                          decide o que mandar para a cozinha.
                          É o ÚNICO que conhece o passo a passo do atendimento.

<<entity>>   ENTIDADE  →  a COMIDA e o CARDÁPIO
                          são as coisas do negócio, que existem
                          independentemente de quem está atendendo.
                          Normalmente ficam guardadas (persistentes).
```

🔎 **Exemplo na loja online — o caso de uso "Finalizar pedido":**

```text
                 ╔═════════════════════╗
    Cliente ────►║  <<boundary>>       ║   a TELA que o cliente vê
                 ║  TelaFinalizarPedido║   (botões, campos, mensagens)
                 ╚══════════╤══════════╝
                            │
                 ╔══════════▼══════════╗
                 ║  <<control>>        ║   quem sabe a ORDEM dos passos:
                 ║  ControladorPedido  ║   1) validar 2) calcular 3) cobrar 4) baixar estoque
                 ╚═══╤══════════════╤══╝
                     │              │
          ╔══════════▼═══╗   ╔══════▼════════╗
          ║ <<entity>>   ║   ║ <<entity>>    ║   os DADOS do negócio
          ║   Pedido     ║   ║   Produto     ║
          ╚══════════════╝   ╚═══════════════╝
```

⚠️ **As três regras que a banca cobra:**

```text
1. O ATOR só fala com a FRONTEIRA.   (nunca direto com entidade)
2. A FRONTEIRA não fala com ENTIDADE. (passa pelo controle)
3. Existe UM controle por CASO DE USO. (não um controle para o sistema todo)
```

🎯 **Regra prática de nomes:** fronteira costuma ter nome de **tela/janela/formulário**; controle costuma ser **"Controlador de + nome do caso de uso"**; entidade tem nome de **coisa do negócio** (substantivo puro).

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

💡 **Em português claro:** a Análise Textual de Abbott é literalmente **grifar o texto do minimundo com dois marca-textos**: um para substantivos, outro para verbos.

🔎 **Exemplo — aplicando os 3 passos a um trecho real de minimundo:**

> *"É responsabilidade do **cliente** realizar o próprio **cadastro** e alterá-lo sempre que necessário. Do cliente é preciso conhecer: o **nome**, **endereço** completo, **e-mail**, **CPF**, **data de nascimento** e **telefones**."*

**Passo 1 — grifar os substantivos:**

```text
cliente · cadastro · nome · endereço · e-mail · CPF · data de nascimento · telefone
```

**Passo 2 — remover sinônimos:**

```text
"cadastro" é sinônimo do ato de criar o Cliente → sai da lista
```

**Passo 3 — classificar cada termo que sobrou:**

| Termo | Vira o quê | Por quê |
| --- | --- | --- |
| **cliente** | **CLASSE** | é uma coisa do negócio, com vários dados próprios |
| **nome** | **ATRIBUTO** de Cliente | é um valor simples, não tem vida própria |
| **CPF** | **ATRIBUTO** de Cliente | idem (e é do mundo real, então entra) |
| **data de nascimento** | **ATRIBUTO** de Cliente | idem |
| **endereço** | **CLASSE** | ⚠️ o minimundo detalha em tipo do logradouro, número, complemento, CEP → virou coisa com estrutura própria |
| **telefone** | **CLASSE** | ⚠️ está no **plural** → o cliente tem vários → vira classe com multiplicidade `*` |
| **e-mail** | **CLASSE** | mesma razão do telefone, se estiver no plural |
| **cadastro** | **nada** | é o nome da ação, não uma coisa |

🎯 **Os dois sinais que transformam um "atributo óbvio" em CLASSE:**

```text
1. Está no PLURAL no texto              ("telefones", "e-mails")
2. O texto DECOMPÕE ele em partes       ("endereço completo: logradouro, número, CEP")
```

**Agora os verbos:**

| Verbo no texto | Vira o quê | Resultado |
| --- | --- | --- |
| "realizar o cadastro", "alterá-lo" | **OPERAÇÃO** | `cadastrar()`, `alterar()` |
| "o cliente **tem** telefones" | **todo-parte** | agregação/composição |
| "o consultor **é uma** pessoa" | **herança** | generalização |

⚠️ **Cuidado com o verbo "ter".** Nem todo "ter" é agregação: *"o cliente tem um nome"* é **atributo**, não composição. Use a regra: se o que ele "tem" é um **valor simples**, é atributo; se é uma **coisa com estrutura própria**, é todo-parte.

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

🔎 **Exemplos certos e errados, lado a lado:**

| Conceito no texto | ❌ Errado | ✅ Certo | Regra |
| --- | --- | --- | --- |
| item do pedido (classe) | `item pedido`, `itempedido`, `ItemDePedido` | **`ItemPedido`** | maiúscula em cada palavra, sem espaço, **sem preposição** |
| preço unitário (atributo) | `Preco Unitario`, `preco_unitario` | **`precoUnitario`** | 1ª minúscula, demais maiúsculas, colado |
| data de nascimento (atributo) | `DataDeNascimento` | **`dataNascimento`** | o "de" **sai** |
| CPF (atributo) | `cpf`, `Cpf` | **`CPF`** | ⚠️ sigla fica **como é** |
| CNPJ da loja (atributo) | `cnpj` | **`CNPJ`** | idem |
| calcular o total (operação) | `CalcularTotal`, `calcular_total` | **`calcularTotal()`** | mesma regra de atributo |

⚠️ **A pegadinha das siglas** é a que mais aparece: `CPF`, `CNPJ`, `CEP` e `UF` **não viram** `cpf` nem `Cpf`. Ficam em maiúsculas.

🎯 Repare que **classes começam com maiúscula** e **atributos com minúscula** — é assim que, olhando um nome solto numa alternativa, você já sabe do que ela está falando.

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

💡 **Em português claro — a multiplicidade se lê do LADO OPOSTO:**

Esta é a maior fonte de erro do diagrama de classes. O número fica **do lado da classe que você está CONTANDO**, e você lê **partindo da outra**.

```text
     ╔═════════╗  1        *  ╔═════════╗
     ║ Cliente ║──────────────║ Pedido  ║
     ╚═════════╝              ╚═════════╝
                 ▲            ▲
                 │            └─ o "*" está do lado de PEDIDO
                 │               → "UM CLIENTE tem MUITOS pedidos"
                 └─ o "1" está do lado de CLIENTE
                    → "UM PEDIDO pertence a UM cliente"
```

🎯 **A técnica infalível: leia em voz alta nos DOIS sentidos.**

```text
"Um Cliente está associado a quantos Pedidos?"  → MUITOS  → põe * do lado do Pedido
"Um Pedido está associado a quantos Clientes?"  → UM      → põe 1 do lado do Cliente
```

🔎 **Exemplos prontos, para calibrar:**

| Situação do minimundo | Desenho | Leitura |
| --- | --- | --- |
| "um cliente faz vários pedidos" | `Cliente 1 ── * Pedido` | 1 cliente, muitos pedidos |
| "um pedido tem no mínimo um item" | `Pedido 1 ── 1..* ItemPedido` | pedido vazio não existe |
| "um funcionário pode ou não ter um crachá" | `Funcionario 1 ── 0..1 Cracha` | o `0` permite não ter |
| "um aluno cursa várias disciplinas e uma disciplina tem vários alunos" | `Aluno * ── * Disciplina` | muitos-para-muitos |
| "uma loja tem exatamente 3 caixas" | `Loja 1 ── 3 Caixa` | intervalo fixo |

⚠️ **O `0` e o `1` do lado esquerdo do `..` não são decoração:**

```text
0..*  →  pode ter NENHUM         (o cliente pode nunca ter comprado)
1..*  →  tem que ter PELO MENOS UM (o pedido tem que ter algum item)
0..1  →  pode não ter, e no máximo um
1..1  →  tem que ter exatamente um
```

📌 **Slide 14 — Conectividade × Multiplicidade** (a **conectividade leva em consideração a multiplicidade MÁXIMA** de cada participante):

| Conectividade | Multiplicidade de um extremo | Multiplicidade do outro extremo |
| --- | --- | --- |
| **Um para um** | `0..1` ou `1` | `0..1` ou `1` |
| **Um para muitos** | `0..1` ou `1` | `*` ou `1..*` ou `0..*` |
| **Muitos para muitos** | `*` ou `1..*` ou `0..*` | `*` ou `1..*` ou `0..*` |

💡 **Em português claro — conectividade × multiplicidade:**

```text
MULTIPLICIDADE →  os números EXATOS que você escreve   (0..1, 1..*, 3..5)
CONECTIVIDADE  →  a CLASSIFICAÇÃO grosseira da associação
                  (1-para-1, 1-para-muitos, muitos-para-muitos)
```

⚠️ **A regra que cai:** para achar a conectividade, você **só olha o número MÁXIMO** de cada lado. O mínimo é ignorado.

🔎 **Exemplo — classifique estas três:**

```text
Funcionario 0..1 ────── 1 Cracha
   máximos:    1   e    1        →  conectividade UM PARA UM
   (o 0 não muda nada: continua "um para um")

Cliente 1 ────── 0..* Pedido
   máximos:  1   e    *          →  conectividade UM PARA MUITOS

Aluno 1..* ────── 1..* Disciplina
   máximos:  *    e    *         →  conectividade MUITOS PARA MUITOS
```

🎯 **Macete:** tape com o dedo tudo o que vem **antes** do `..` e olhe só o que sobrou. `0..1` e `1..1` são ambos "**um**"; `0..*` e `1..*` são ambos "**muitos**".

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

💡 **Em português claro — os três adornos servem para tirar dúvida de quem lê o desenho.** Uma linha entre duas classes, sozinha, não diz **o que** liga uma à outra.

🔎 **A mesma associação, com cada adorno:**

```text
SEM NADA — ambíguo
   ╔═════════╗          ╔═════════╗
   ║ Pessoa  ║──────────║ Empresa ║     "Pessoa e Empresa... o quê? Trabalha? É dona? Compra?"
   ╚═════════╝          ╚═════════╝

COM NOME DA ASSOCIAÇÃO
   ╔═════════╗  trabalha em  ╔═════════╗
   ║ Pessoa  ║───────────────║ Empresa ║     agora sabemos O QUE liga os dois
   ╚═════════╝               ╚═════════╝

COM SENTIDO DE LEITURA (o triângulo ▶)
   ╔═════════╗  trabalha em ▶ ╔═════════╗
   ║ Pessoa  ║────────────────║ Empresa ║     lê-se "PESSOA trabalha em EMPRESA"
   ╚═════════╝                ╚═════════╝     e não "Empresa trabalha em Pessoa"

COM PAPÉIS (role)
   ╔═════════╗                     ╔═════════╗
   ║ Pessoa  ║─────────────────────║ Empresa ║
   ╚═════════╝ empregado  empregador ╚═══════╝
                   ▲          ▲
        "a Pessoa faz o papel  "a Empresa faz o
         de empregado"          papel de empregador"
```

🎯 **Quando usar PAPEL em vez de NOME:** quando a mesma classe aparece **duas vezes** na associação (é o caso da **associação reflexiva**, seção 3.6), o nome não resolve — só o papel deixa claro quem é quem.

⚠️ O slide diz que o **papel serve como substituto do nome** da associação: use **um ou outro**, não os dois ao mesmo tempo.

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

💡 **Em português claro — quando você PRECISA de uma classe associativa:**

Quando existe um dado que **não pertence a nenhuma das duas classes**, e sim **ao encontro das duas**.

🔎 **Exemplo — onde guardar a nota do aluno?**

```text
A nota 8,5 pertence ao Aluno?      ❌ Não. O mesmo aluno tem notas diferentes
                                       em disciplinas diferentes.
A nota 8,5 pertence à Disciplina?  ❌ Não. A mesma disciplina tem notas
                                       diferentes para alunos diferentes.
A nota pertence ao PAR (aluno, disciplina)?  ✅ SIM.
                                   → precisa de CLASSE ASSOCIATIVA
```

🔎 **Outro exemplo, na loja online — `ItemPedido` é uma classe associativa:**

```text
   ╔═════════╗  *                  *  ╔═════════╗
   ║ Pedido  ║─────────────────────────║ Produto ║
   ╚═════════╝            ┆            ╚═════════╝
                     ╔════╧═════════╗
                     ║  ItemPedido  ║
                     ║  quantidade  ║   ← "2 unidades" é do PEDIDO? não.
                     ║ precoUnitario║      é do PRODUTO? não.
                     ╚══════════════╝      é DAQUELE produto NAQUELE pedido.
```

⚠️ **"Apenas UMA ocorrência para cada par" — o que isso significa na prática:**

```text
Pedido 100 + Produto "Teclado"  →  só pode existir UMA linha de ItemPedido
                                    (se comprar 2 teclados, é quantidade = 2,
                                     e NÃO duas linhas)
```

Se o minimundo permitir **duas ocorrências para o mesmo par**, a classe associativa **não serve** — aí você precisa de uma **classe normal** no meio.

💡 **A diferença que o slide manda não confundir:**

```text
CLASSE ASSOCIATIVA           →  é A PRÓPRIA associação que virou classe.
   (linha tracejada)             Um par só pode aparecer UMA vez.

ASSOCIAÇÃO PROMOVIDA A CLASSE →  é uma classe NORMAL no meio, com duas
   (duas linhas cheias)          associações comuns. O mesmo par PODE
                                 aparecer várias vezes.

   ╔═══════╗ * ╔═════════════╗ * ╔═════════╗
   ║Pedido ║───║ ItemPedido  ║───║ Produto ║   ← classe normal no meio:
   ╚═══════╝   ╚═════════════╝   ╚═════════╝     aqui o MESMO produto PODE
                                                  aparecer 2x no mesmo pedido
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

💡 **Em português claro:** é uma classe se ligando a **ela mesma**. Acontece sempre que os objetos de uma classe se relacionam **entre si**.

⚠️ **Por que os PAPÉIS são obrigatórios aqui:** as duas pontas da linha chegam na **mesma classe**. Sem os papéis (`supervisor` / `supervisionado`), é impossível saber qual ponta é qual.

🔎 **Como isso fica com objetos reais:**

```text
              ╔═══════════════╗
              ║  Ana (chefe)  ║
              ╚═══╤═══════╤═══╝
                  │       │        Ana é SUPERVISORA de Bruno e Carla
        ┌─────────┘       └─────────┐
        ▼                           ▼
╔══════════════╗            ╔══════════════╗
║    Bruno     ║            ║    Carla     ║
╚══════════════╝            ╚══════════════╝
   supervisionado               supervisionado

Os três são objetos da MESMA classe Empregado.
```

🔎 **Outros exemplos clássicos:**

| Minimundo | Papéis | Multiplicidade |
| --- | --- | --- |
| "uma pasta pode conter outras pastas" | `pastaPai` / `subpasta` | `0..1` ── `*` |
| "uma pessoa é casada com outra pessoa" | `cônjuge` / `cônjuge` | `0..1` ── `0..1` |
| "um produto pode ter produtos similares" | `produto` / `similar` | `*` ── `*` |
| "um item de menu tem submenus" | `menuPai` / `submenu` | `0..1` ── `*` |

🎯 **Como reconhecer no texto:** procure frases em que **a mesma palavra aparece dos dois lados** — *"um empregado supervisiona empregados"*, *"uma pasta contém pastas"*.

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

💡 **Em português claro — por que não resolver com três associações binárias?**

Porque **três associações binárias perdem informação**. Elas dizem que o técnico trabalha em projetos, que o técnico usa computadores e que computadores são usados em projetos — mas **não dizem QUAL computador em QUAL projeto**.

```text
❌ TRÊS BINÁRIAS (perde a informação)
   Tecnico ──── Projeto        "João trabalha nos projetos A e B"
   Tecnico ──── Computador     "João usa os computadores PC1 e PC2"
   Projeto ──── Computador     "os projetos A e B usam PC1 e PC2"

   → Não dá para saber se João usa PC1 no projeto A ou no projeto B!

✅ UMA TERNÁRIA (guarda o trio)
                ╔═════════╗
                ║ Tecnico ║
                ╚════╤════╝
                     │
         ╔═══════╗   ◇   ╔════════════╗
         ║Projeto║───────║ Computador ║
         ╚═══════╝       ╚════════════╝

   → cada ligação é um TRIO: (João, Projeto A, PC1)
```

🔎 **Os trios possíveis, segundo as regras do slide:**

```text
(João, Projeto A, PC1)   ✅
(João, Projeto B, PC2)   ✅   um técnico pode usar computador diferente em
                               cada projeto
(João, Projeto A, PC2)   ❌   "um técnico, quando trabalha em um projeto,
                               utiliza um ÚNICO computador"
(Maria, Projeto A, PC1)  ❌   "um computador, em um projeto, é utilizado
                               por um ÚNICO técnico"
```

💡 **Como ler a multiplicidade na ternária:** o número em `C` responde *"fixando UM objeto de A e UM de B, quantos C cabem?"*.

```text
Tecnico ──◇── Projeto
          │
      Computador  [1]     →  "para o par (João, Projeto A), há 1 computador"
```

⚠️ **Na prova de vocês a ternária é rara**, mas se aparecer, o desenho é sempre o **losango ligando as três classes**. Não confunda com o losango de agregação/composição, que fica **na ponta da linha**, não no meio.

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

💡 **Em português claro — o teste de uma pergunta só:**

> **"Se eu destruir o TODO, a PARTE continua existindo sozinha e fazendo sentido?"**
>
> * **Continua existindo** → **AGREGAÇÃO** (losango **vazio** ◇)
> * **Morre junto** → **COMPOSIÇÃO** (losango **cheio** ◆)

🔎 **Exemplos calibrados, dos dois tipos:**

| Todo ── Parte | Se o todo morrer... | Tipo |
| --- | --- | --- |
| `Pedido ── ItemPedido` | o item não faz sentido sem o pedido | **Composição ◆** |
| `Time ── Jogador` | o jogador continua existindo, vai para outro time | **Agregação ◇** |
| `Livro ── Capitulo` | o capítulo morre com o livro | **Composição ◆** |
| `Playlist ── Musica` | a música continua no acervo | **Agregação ◇** |
| `Casa ── Comodo` | o cômodo não existe sem a casa | **Composição ◆** |
| `Curso ── Aluno` | o aluno continua matriculado em outros cursos | **Agregação ◇** |
| `NotaFiscal ── ItemNota` | some junto | **Composição ◆** |

🔎 **O desenho, com as multiplicidades que denunciam cada caso:**

```text
COMPOSIÇÃO                                AGREGAÇÃO
╔═════════╗ 1        1..* ╔═══════════╗   ╔═══════╗ *        * ╔═════════╗
║ Pedido  ║◆──────────────║ ItemPedido║   ║ Time  ║◇───────────║ Jogador ║
╚═════════╝               ╚═══════════╝   ╚═══════╝            ╚═════════╝
             ▲                                        ▲
   do lado do TODO a multiplicidade            aqui o lado do TODO PODE
   NUNCA passa de 1                            ser * (o jogador já jogou
   (um item pertence a UM pedido só)            em vários times)
```

🎯 **Atalho de prova:** se a multiplicidade do lado do **todo** for maior que 1, **não pode ser composição** — é agregação. Composição exige `1` (ou `0..1`) do lado do todo.

⚠️ **O erro mais comum na leitura do desenho** é olhar o losango e pensar que ele marca a *parte*. Ele marca o **TODO**:

```text
   Y ◇──── X ────◆ Z

   losango do lado de X nas DUAS  →  X é o TODO nas duas associações
   → X é feito de Y (fraco) e de Z (forte)
   → Z depende de X para existir   ← foi essa a resposta da questão IF-SP 2024
```

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

💡 **Em português claro — o teste do "é um":**

> Escreva a frase: *"todo **[subclasse]** é um **[superclasse]**"*.
> Se a frase for **verdadeira sempre**, é generalização.

```text
"todo Cliente é uma Pessoa"        ✅ verdade  → generalização
"todo Consultor é uma Pessoa"      ✅ verdade  → generalização
"todo Pedido é um Cliente"         ❌ falso    → NÃO é generalização (é associação)
"todo ItemPedido é um Pedido"      ❌ falso    → é COMPOSIÇÃO, não herança
```

⚠️ **O erro clássico:** usar herança onde cabe **todo-parte**. *"Um pedido **tem** itens"* é composição; *"um cliente **é** uma pessoa"* é herança. **TER ≠ SER.**

🔎 **O que exatamente a subclasse recebe (os três tipos de coisa):**

```text
                  ╔══════════════════════════╗
                  ║        Pessoa            ║
                  ╠══════════════════════════╣
                  ║ nome                     ║  ← 1. ATRIBUTOS
                  ║ CPF                      ║
                  ╠══════════════════════════╣
                  ║ calcularIdade()          ║  ← 2. OPERAÇÕES
                  ╚═══════════╤══════════════╝
                              │ 1
                              │                  ← 3. ASSOCIAÇÕES ⚠️
                              │ *
                        ╔═════╧══════╗
                        ║  Telefone  ║
                        ╚════════════╝
                              △
                  ┌───────────┴───────────┐
          ╔═══════╧═══╗           ╔═══════╧════╗
          ║  Cliente  ║           ║ Consultor  ║
          ╠═══════════╣           ╠════════════╣
          ║ CNPJ      ║           ║ nivel      ║   ← só o que é ESPECÍFICO
          ╚═══════════╝           ╚════════════╝      de cada uma
```

**Cliente e Consultor, sem escrever nada, já têm:** `nome`, `CPF`, `calcularIdade()` **e a ligação com Telefone**.

⚠️ **É esse terceiro item que a prova cobra:** *"não somente atributos e operações são herdados, mas **também as ASSOCIAÇÕES**"*. No exemplo do slide, se `Empregado` está alocado em um `Departamento`, então **`Assessor` (subclasse) também poderá estar** — sem redesenhar a linha.

🎯 **Na discursiva, é isso que economiza desenho:** em vez de ligar `Telefone` a `Cliente` E a `Consultor`, você liga **uma vez só** a `Pessoa`. Foi exatamente o que o gabarito da Siscon fez.

### Classe abstrata

📌 **Slide 8 (1b):**

> Normalmente utilizada para **organizar a hierarquia** entre classes, ou para fins de modelagem. **Classes abstratas NÃO geram objetos diretamente.** É representada com seu **nome em ITÁLICO**.

🧪 **Já caiu (GUALIMP 2024):** classe `Funcionario` em itálico com `FuncionarioHorista` e `FuncionarioComissionado` abaixo → a resposta é **"A classe Funcionário não pode ser instanciada"**.

💡 **Em português claro:** classe abstrata é um **conceito que só existe através das filhas**. Ela agrupa o que é comum, mas **nenhum objeto dela sozinha pode ser criado**.

🔎 **Exemplo — por que `Pagamento` seria abstrata:**

```text
                ╔═══════════════════════╗
                ║     *Pagamento*       ║   ← nome em ITÁLICO = abstrata
                ╠═══════════════════════╣
                ║ valor                 ║
                ║ data                  ║
                ╚═══════════△═══════════╝
                   ┌────────┴────────┐
          ╔════════╧═══╗      ╔══════╧═══════╗
          ║ PagtoPix   ║      ║ PagtoCartao  ║
          ╠════════════╣      ╠══════════════╣
          ║ chavePix   ║      ║ numeroCartao ║
          ╚════════════╝      ╚══════════════╝

"Me faça um pagamento."  →  de QUE tipo? PIX? cartão?
                             A pergunta não faz sentido sozinha.
                             Por isso Pagamento é ABSTRATA.
```

⚠️ **Como identificar no desenho:** o **nome em itálico** é a única marca. Alguns autores também escrevem `{abstract}` embaixo do nome.

🎯 **O que a banca pergunta sobre classe abstrata é sempre a mesma coisa:** *"ela pode ser instanciada?"* → **NÃO**. Só as filhas concretas podem.

💡 **Sobre a frase do slide** *("para que um objeto de Conta seja instanciado será necessário que um objeto de Poupança ou de Corrente seja instanciado")*: quando você cria uma `Poupanca`, ela **também é** uma `Conta` — os atributos de `Conta` existem dentro dela. O que não dá é criar uma `Conta` **pura**, que não seja nem poupança nem corrente.

### Herança múltipla

📌 **Slide 9 (1b):**

| Vantagens | Desvantagens |
| --- | --- |
| Mais **poder na especificação** de classes e maior oportunidade de **reuso** | **Perda de simplicidade** conceitual e de implementação (**nem todas as linguagens tratam bem disso**) |

⚠️ **Obs. do slide:** sempre que possível devemos distinguir **generalização** (o relacionamento **conceitual**) de **herança** (o **mecanismo da linguagem**) — mas o termo "herança múltipla" é mais usado que "generalização múltipla".

🔎 **Exemplo de herança múltipla:**

```text
   ╔═══════════╗          ╔═══════════════╗
   ║  Pessoa   ║          ║   Funcionario ║
   ╚═════△═════╝          ╚═══════△═══════╝
         │                        │
         └────────┬───────────────┘
                  │
         ╔════════╧═══════════╗
         ║ ProfessorPesquisador║   herda de PESSOA (nome, CPF)
         ╚════════════════════╝    e de FUNCIONARIO (matrícula, salário)
```

⚠️ **O problema prático (o "diamante"):** se as duas superclasses tiverem um atributo com o **mesmo nome**, qual vale? É por isso que **Java não permite** herança múltipla de classes (só de interfaces), e por isso o slide fala em **"perda de simplicidade"**.

💡 **Generalização × herança, em uma frase:**

```text
GENERALIZAÇÃO →  é o CONCEITO, no modelo:  "cliente é um tipo de pessoa"
HERANÇA       →  é o MECANISMO, no código: "class Cliente extends Pessoa"
```

🎯 É a mesma distinção de **análise × implementação**. Na prova de modelagem, o nome correto é **generalização**; na prova de programação, **herança**.

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

💡 **Em português claro — as quatro restrições de generalização, aos pares:**

Elas respondem **duas perguntas independentes** sobre a hierarquia:

```text
PERGUNTA 1: "um objeto pode pertencer a DUAS subclasses ao mesmo tempo?"
   NÃO pode  →  {disjunta}     (as subclasses se excluem)
   PODE      →  {sobreposta}   (herança múltipla)

PERGUNTA 2: "eu já listei TODAS as subclasses possíveis?"
   SIM  →  {completa}
   NÃO  →  {incompleta}        (podem surgir outras)
```

⚠️ Como são duas perguntas diferentes, elas **se combinam**: `{disjunta, completa}`, `{sobreposta, incompleta}` etc.

🔎 **Exemplos de cada combinação:**

| Hierarquia | Restrição | Por quê |
| --- | --- | --- |
| `Pessoa` → `Homem`, `Mulher` | `{disjunta, completa}` | não dá para ser os dois, e não há terceira opção no modelo |
| `Pessoa` → `Aluno`, `Professor` | `{sobreposta, incompleta}` | alguém pode ser **aluno e professor**; e ainda existem funcionários, terceirizados... |
| `Conta` → `Poupanca`, `Corrente` | `{disjunta, completa}` | o banco só tem esses dois tipos, e a conta é um ou outro |
| `Veiculo` → `Carro`, `Moto` | `{disjunta, incompleta}` | um veículo não é carro e moto ao mesmo tempo, mas faltam caminhão, ônibus... |

🔎 **Como aparece no desenho:**

```text
              ╔═══════════╗
              ║   Conta   ║
              ╚═════△═════╝
                    │ {disjunta, completa}   ← as chaves ficam PERTO DA LINHA
            ┌───────┴───────┐
     ╔══════╧═══╗     ╔═════╧════╗
     ║ Poupanca ║     ║ Corrente ║
     ╚══════════╝     ╚══════════╝
```

💡 **Em português claro — as duas restrições de ASSOCIAÇÃO (OCL):**

```text
{xor}    →  "OU um, OU outro, NUNCA os dois"
{subset} →  "este grupo está DENTRO daquele grupo"
```

🔎 **`{xor}` desenhado:**

```text
        ╔═════════╗
        ║ Pessoa  ║────────────┐
        ╚═════════╝            │
                          {xor}│      ╔═══════════════╗
        ╔═════════════╗        ├──────║ ContaBancaria ║
        ║ Instituicao ║────────┘      ╚═══════════════╝
        ╚═════════════╝

Leitura: "a conta é de uma PESSOA ou de uma INSTITUIÇÃO,
          jamais das duas ao mesmo tempo."
```

🔎 **`{subset}` desenhado:**

```text
        ╔═════════╗  reside em    ╔══════════╗
        ║ Pessoa  ║───────────────║ Edificio ║
        ║         ║       *     1 ║          ║
        ║         ║───────────────║          ║
        ╚═════════╝  administra   ╚══════════╝
                     1         1
                          ▲
                     {subset}

Leitura: "quem ADMINISTRA tem que estar dentro do grupo de
          quem RESIDE no edifício."
```

🎯 **Sobre OCL:** você **não precisa saber escrever OCL** na prova. Precisa saber que (a) é a **linguagem de restrições da UML**, (b) é **parecida com uma linguagem de programação**, (c) as restrições ficam **entre chaves `{ }`**, e (d) `{xor}` e `{subset}` são **predefinidas pela UML**.

## 3.11 Identificadores e enumerações

⚠️ **Slide 14 (1b) — regra que vale ponto na discursiva:**

> **NÃO liste identificadores de objetos nos diagramas de classe de análise**, pois eles são **implícitos** nos modelos. Não confunda identificadores **internos** com atributos do **mundo real**: os internos são puramente uma **conveniência de implementação** e **não possuem significado para o negócio**.

🎯 Ou seja: `CPF` e `CNPJ` **entram** (são do mundo real); `idCliente`, `codigoInterno` **não entram** no modelo de análise.

📌 **Slide 15 (1b) — Enumeração:** tipo de dado que possui um **conjunto finito de valores (domínio fechado)**. Notação: `<<enumeration>>`.

🎯 No minimundo, frases como *"forma de pagamento (pix, cartão, dinheiro)"* ou *"nível de proficiência (júnior, pleno, sênior)"* pedem uma **enumeração**.

💡 **Em português claro — a regra dos identificadores:**

```text
O modelo de ANÁLISE descreve o NEGÓCIO, não o banco de dados.
Um "idCliente" auto-incremento não existe no negócio — existe porque
o programador precisou de uma chave. Então ele NÃO entra.
```

🔎 **O que entra e o que não entra:**

| Atributo | Entra? | Por quê |
| --- | :-: | --- |
| `CPF` | ✅ | existe no mundo real; o cliente tem CPF mesmo sem o sistema |
| `CNPJ` | ✅ | idem |
| `matricula` do aluno | ✅ | a faculdade usa a matrícula no dia a dia, no papel |
| `codigoEquipamento` (ex.: `L1_012`) | ✅ | está escrito na etiqueta do equipamento |
| `idCliente` | ❌ | número interno do banco; ninguém do negócio conhece |
| `codigoInterno` | ❌ | idem |
| `pk`, `fk`, `rowid` | ❌ | conceitos de banco de dados, não de negócio |

🎯 **O teste:** *"se eu apagar o sistema e ficar só com papel, esse número ainda existiria?"* Se sim, é do mundo real e **entra**.

🔎 **Enumeração — como desenhar:**

```text
╔═══════════════════════╗        ╔═══════════════════════════╗
║      Pagamento        ║        ║   <<enumeration>>         ║
╠═══════════════════════╣        ║     FormaPagamento        ║
║ data                  ║───────►╠═══════════════════════════╣
║ hora                  ║        ║  PIX                      ║
║ forma : FormaPagamento║        ║  CARTAO                   ║
╚═══════════════════════╝        ║  DINHEIRO                 ║
                                 ╚═══════════════════════════╝
```

⚠️ **Como identificar no minimundo:** procure **uma lista fechada entre parênteses**.

```text
"forma de pagamento (pix, cartão, dinheiro)"       → <<enumeration>> FormaPagamento
"nível de proficiência (júnior, pleno, sênior)"    → <<enumeration>> NivelProficiencia
"status (ativo, inativo, suspenso)"                → <<enumeration>> Status
```

💡 **Por que não deixar como texto livre?** Porque "domínio fechado" significa que **só aqueles valores são válidos**. Se fosse um `String` comum, alguém poderia gravar "pics" ou "cartaum". A enumeração **trava** as opções.

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

💡 **Em português claro — o problema que o padrão Party resolve:**

Você lê o minimundo e percebe que **duas ou três classes pedem exatamente os mesmos dados**. Se você desenhar do jeito literal, o diagrama fica com tudo repetido.

🔎 **ANTES do padrão (o jeito errado — tudo repetido):**

```text
╔══════════════════════╗     ╔══════════════════════╗
║      Cliente         ║     ║     Consultor        ║
╠══════════════════════╣     ╠══════════════════════╣
║ nome                 ║     ║ nome                 ║  ← repetido
║ endereco             ║     ║ endereco             ║  ← repetido
║ email                ║     ║ email                ║  ← repetido
║ telefone             ║     ║ telefone             ║  ← repetido
║ CNPJ                 ║     ║ CPF                  ║
╚══════════════════════╝     ╚══════════════════════╝
   e as ligações com Telefone e EMail teriam que ser desenhadas DUAS vezes
```

🔎 **DEPOIS do padrão Party (o jeito do gabarito):**

```text
                ╔══════════════════════╗ 1      * ╔════════════╗
                ║      *Pessoa*        ║──────────║  Telefone  ║
                ╠══════════════════════╣          ╚════════════╝
                ║ nome                 ║ 1      *
                ║ endereco             ║──────────╔════════════╗
                ╚══════════△═══════════╝          ║   EMail    ║
                     ┌─────┴─────┐                ╚════════════╝
            ╔════════╧═╗     ╔═══╧═══════╗
            ║ Cliente  ║     ║ Consultor ║
            ╠══════════╣     ╠═══════════╣
            ║ CNPJ     ║     ║ CPF       ║   ← só o que é ESPECÍFICO
            ╚══════════╝     ╚═══════════╝
```

⭐ **O ganho:** as ligações com `Telefone` e `EMail` são desenhadas **uma vez só**, em `Pessoa` — e **Cliente e Consultor herdam as associações** (é a regra da seção 3.9).

🎯 **Como reconhecer que é hora de aplicar Party:**

```text
1. Leia os parágrafos que descrevem CADA participante do minimundo.
2. Se dois ou mais pedirem os MESMOS atributos (nome, endereço, e-mail, telefone),
   → crie a superclasse Pessoa (ou Party) com a parte comum.
3. Se um deles for uma EMPRESA e outro for uma PESSOA FÍSICA,
   → o nome canônico da superclasse é Party, com Pessoa e Organizacao abaixo.
```

⚠️ **Não force.** Se as classes só compartilham **um** atributo (só o nome, por exemplo), criar a superclasse pode complicar mais do que ajudar. O padrão vale quando a repetição é **grande**.

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

💡 **Em português claro — o problema que o Metamodel resolve:**

Imagine uma loja que vende **de tudo**. Cada tipo de produto tem características diferentes:

```text
Camiseta   →  tamanho, cor, tecido
Notebook   →  processador, memória, tela
Livro      →  autor, editora, ISBN
Geladeira  →  capacidade, voltagem, consumo
```

🔎 **A solução ERRADA — uma subclasse por tipo:**

```text
                    ╔═══════════╗
                    ║  Produto  ║
                    ╚═════△═════╝
        ┌───────┬─────────┼─────────┬───────────┐
   ╔════╧═══╗ ╔═╧══════╗ ╔╧═════╗ ╔═╧════════╗ ╔╧═══════╗
   ║Camiseta║ ║Notebook║ ║Livro ║ ║ Geladeira║ ║  ...   ║
   ╚════════╝ ╚════════╝ ╚══════╝ ╚══════════╝ ╚════════╝

⚠️ PROBLEMA: para vender um novo tipo (perfume), é preciso
   CRIAR UMA CLASSE NOVA e RECOMPILAR o sistema.
   A loja não consegue cadastrar um tipo novo sozinha.
```

🔎 **A solução do padrão Metamodel:**

```text
   ╔══════════════╗ *          * ╔══════════════════╗
   ║     Item     ║──────────────║   Propriedade    ║
   ║     nome     ║              ║      nome        ║
   ╚══════════════╝              ╚══════════════════╝

Agora os TIPOS viram DADOS, não classes:

   Item: "Camiseta Preta M"
      ├── Propriedade "tamanho"      → Valor "M"
      ├── Propriedade "cor"          → Valor "Preta"
      └── Propriedade "tecido"       → Valor "Algodão"

   Item: "Notebook X"
      ├── Propriedade "processador"  → Valor "i7"
      ├── Propriedade "memoria"      → Valor 16 (UnidadeMedida: GB)
      └── Propriedade "tela"         → Valor 15.6 (UnidadeMedida: polegadas)
```

⭐ **O ganho:** para vender perfume, **ninguém mexe no código**. A loja cadastra um `Item` e as `Propriedades` que quiser. É isso que o slide chama de *"modificar a estrutura do modelo sem que o esquema dos objetos seja realmente modificado"*.

💡 **Entendendo as classes do diagrama do slide:**

| Classe | Para que serve | 🔎 Exemplo |
| --- | --- | --- |
| **`Item`** | a coisa em si | "Notebook X" |
| **`Propriedade`** | o **nome** da característica | "memória" |
| **`Valor`** | o **conteúdo** daquela característica naquele item | 16 |
| **`ValorNumerico`** | quando o valor é um **número** | 16, 15.6 |
| **`ValorDiscreto`** | quando o valor é de uma **lista fechada** | "Preta", "M" |
| **`UnidadeMedida`** | a unidade do número (`0..1`, porque nem todo valor tem) | "GB", "polegadas" |

⚠️ **A `UnidadeMedida` é `0..1`** porque "cor = Preta" não tem unidade, mas "memória = 16" tem (GB).

🎯 **Como reconhecer no minimundo:** procure frases como *"os tipos devem ser **cadastrados pelo gerente**"*, *"cada categoria tem **características próprias**"*, *"o administrador pode **criar novos tipos**"*. Se o **usuário** pode inventar tipos novos, é Metamodel.

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

💡 **Em português claro — o que GRASP resolve:**

Você já desenhou as classes. Agora chega a pergunta: **"qual classe deve ter qual método?"** O GRASP é uma lista de conselhos para responder isso sem chutar.

🔎 **Os cinco que caem, com exemplo na loja online:**

**1. `Information Expert` (Especialista) — dê a tarefa a quem tem os dados.**

```text
Pergunta: quem deve ter o método calcularTotal()?

❌ ControladorPedido.calcularTotal()
   → ele teria que PEDIR a lista de itens ao Pedido, depois pedir o preço
     a cada item... muita conversa (alto acoplamento).

✅ Pedido.calcularTotal()
   → o Pedido JÁ TEM a lista de itens. Ele é o "especialista na informação".

   ╔═══════════════════╗
   ║      Pedido       ║   tem a lista de ItemPedido
   ╠═══════════════════╣   → logo, é ELE que sabe somar
   ║ + calcularTotal() ║
   ╚═══════════════════╝
```

**2. `Creator` (Criador) — quem contém, cria.**

```text
Pergunta: quem deve criar um ItemPedido?

✅ Pedido.adicionarItem()
   → porque o Pedido CONTÉM os itens (é uma composição ◆).
     Quem agrega, contém ou registra X é quem deve criar X.
```

**3. `Controller` (Controlador) — uma classe recebe os eventos do sistema.**

```text
A TELA não deve conter a regra de negócio. Ela repassa para o CONTROLADOR,
que coordena a ordem dos passos:

   TelaPedido ──finalizar()──► ControladorPedido
                                     │ 1) validar estoque
                                     │ 2) calcular total
                                     │ 3) registrar pagamento
                                     │ 4) baixar estoque

⭐ É EXATAMENTE o <<control>> do BCE (seção 3.2).
```

**4. `Low Coupling` / `High Cohesion` (acoplamento e coesão) — os dois andam juntos.**

```text
ACOPLAMENTO = quantas OUTRAS classes uma classe precisa conhecer
   BAIXO é bom → se eu mudar uma classe, poucas quebram

COESÃO = quão RELACIONADAS entre si são as responsabilidades de uma classe
   ALTA é boa → a classe faz uma coisa, e faz bem
```

```text
❌ BAIXA COESÃO (ruim)              ✅ ALTA COESÃO (boa)
╔════════════════════════╗          ╔═══════════════════╗ ╔═══════════════╗
║      Pedido            ║          ║      Pedido       ║ ║ ServicoEmail  ║
╠════════════════════════╣          ╠═══════════════════╣ ╠═══════════════╣
║ calcularTotal()        ║          ║ calcularTotal()   ║ ║ enviar()      ║
║ enviarEmail()          ║ ← ?!     ║ adicionarItem()   ║ ╚═══════════════╝
║ gerarPDF()             ║ ← ?!     ╚═══════════════════╝ ╔═══════════════╗
║ conectarBanco()        ║ ← ?!                           ║ GeradorPDF    ║
╚════════════════════════╝                                ╚═══════════════╝
  faz coisa demais,                    cada uma faz UMA coisa
  sem relação entre si
```

**5. `Polymorphism` (Polimorfismo) — troque o `if` por subclasses.**

```text
❌ SEM polimorfismo (o if cresce para sempre)
   if (forma == "PIX")          { ... }
   else if (forma == "CARTAO")  { ... }
   else if (forma == "BOLETO")  { ... }
   → para cada forma nova, é preciso MEXER nesse método

✅ COM polimorfismo
              ╔═══════════════════╗
              ║   *Pagamento*     ║
              ║  + processar()    ║
              ╚═════════△═════════╝
           ┌────────────┼────────────┐
    ╔══════╧═══╗  ╔═════╧═════╗ ╔════╧══════╗
    ║ PagtoPix ║  ║PagtoCartao║ ║PagtoBoleto║
    ║processar()║ ║processar()║ ║processar()║
    ╚══════════╝  ╚═══════════╝ ╚═══════════╝

   → cada um sabe se processar. Para uma forma nova, basta
     CRIAR UMA SUBCLASSE, sem tocar no código existente.
```

⚠️ **A pegadinha da coesão, explicada:** a banca disse que "muitas e diferentes responsabilidades aumentam o reuso". É o **contrário**: quanto mais coisas desconexas uma classe faz, **mais difícil** é reaproveitá-la em outro sistema, porque você teria que levar junto tudo o que não precisa.

```text
Uma classe que SÓ calcula total  →  dá para reusar em qualquer sistema de vendas ✅
Uma classe que calcula total E envia e-mail E gera PDF E conecta no banco
                                 →  não dá para reusar em lugar nenhum ❌
```

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
