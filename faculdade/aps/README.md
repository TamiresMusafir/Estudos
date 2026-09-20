# Guia de Estudo — APS (Análise e Projeto de Sistemas)
### Diagrama de Classes, Diagrama de Transição de Estados e Diagramas de Interação

> Organizado por slide/tema, com foco em definições, regras e pontos que costumam cair em **questões de concurso**.

---

## PARTE 1 — DIAGRAMA DE CLASSES DE ANÁLISE

### 1.1 Modelagem de Classes — conceitos básicos
- Objetos colaboram sob dois aspectos: **dinâmico** (troca de mensagens/eventos) e **estrutural estático** (como o sistema está organizado).
- O diagrama UML que representa o aspecto **estrutural estático** é o **Diagrama de Classes**.
- **3 níveis de abstração do modelo de classes** (pegadinha clássica de prova — saber a ordem e a diferença):
  1. **Classes de domínio** — não considera tecnologia.
  2. **Classes de especificação** — extensão do domínio + detalhes da solução de software + novas classes.
  3. **Classes de implementação** — extensão da especificação, já em linguagem de programação.

### 1.2 Técnicas de identificação de classes
- **Análise dos Casos de Uso** (Identificação Dirigida por Casos de Uso) e **Análise Textual de Abbott** são as duas técnicas citadas.
- Regra da Análise de Casos de Uso: uma classe só se justifica se participar do **comportamento externamente visível** do sistema.

**Categorização BCE (Jacobson) — MUITO cobrada em concurso:**
| Estereótipo | Papel |
|---|---|
| `<<boundary>>` (fronteira) | Interface entre o sistema e os atores |
| `<<control>>` (controle) | Intermediário entre fronteira e entidade; define o comportamento do caso de uso |
| `<<entity>>` (entidade) | Objetos do domínio do problema, geralmente persistentes |
- Atores interagem com objetos de **fronteira**.
- Decore: fronteira → controle → entidade (fluxo típico de uma interação).

**Análise Textual de Abbott — passo a passo (decore a ordem):**
1. Busca por substantivos/adjetivos (nomes e locuções).
2. Remoção de sinônimos.
3. Classificação de cada termo: **classe candidata**, **atributo** ou **irrelevante**.
- Verbos de ação (calcular, cancelar, comprar) → **operações**.
- Verbos com sentido de "ter" → **agregação/composição**.
- Verbos com sentido de "ser" → **generalização**.

**Tabela de correspondência Abbott (decorar — cai muito):**
| Parte do texto | Componente | Exemplo |
|---|---|---|
| Nome próprio | Objeto | Eduardo Bezerra |
| Nome simples | Classe | Aluno |
| Verbo de ação | Operação | Registrar |
| Verbo "ser" | Herança | É um |
| Verbo "ter" | Todo-parte | Tem um |

### 1.3 Nomenclatura (convenções — clássico de prova de "está certo/errado")
- **Classes e relacionamentos**: começam com letra **maiúscula** (ex.: `Cliente`, `ItemPedido`).
- **Atributos e operações**: primeira palavra minúscula, demais em CamelCase interno, sem espaços; **siglas mantidas** (ex.: `quantidade`, `precoUnitario`, `CPF`, `dataNascimento`).
- **Identificadores**: removem-se espaços e preposições.

### 1.4 Associações, multiplicidade e conectividade
- **Multiplicidade**: limites mínimo e máximo de objetos associados (Min..Max).

| Nome | Notação |
|---|---|
| Apenas um | 1..1 (ou 1) |
| Zero ou muitos | 0..* (ou *) |
| Um ou muitos | 1..* |
| Zero ou um | 0..1 |
| Intervalo específico | Im..In |

- **Conectividade** leva em conta a **multiplicidade MÁXIMA** de cada lado (pegadinha: não confundir multiplicidade com conectividade).

| Conectividade | Mult. de um lado | Mult. do outro lado |
|---|---|---|
| Um para um | 0..1 ou 1 | 0..1 ou 1 |
| Um para muitos | 0..1 ou 1 | * / 1..* / 0..* |
| Muitos para muitos | * / 1..* / 0..* | * / 1..* / 0..* |

- **Participação obrigatória** = multiplicidade mínima 1 (ou mais); **opcional** = mínimo 0.
- **Adornos de associação** (recursos de notação): **nome da associação**, **papel (role)** e **sentido de leitura** — servem para tirar ambiguidade.

### 1.5 Classes associativas
- Usadas quando é preciso guardar **informações sobre o relacionamento** entre duas classes.
- **Não confundir** classe associativa com uma associação "promovida" a classe.
- Permite **apenas uma ocorrência por par de objetos** (ou por trio, no caso ternário).
- Mais comum em relações muitos-para-muitos, mas pode ocorrer em 1-para-muitos e 1-para-1 também (pegadinha: não é exclusiva do muitos-para-muitos).

### 1.6 Associações reflexivas e ternárias
- **Reflexiva (auto-associação)**: associa objetos da **mesma classe**, cada um com papel distinto (ex.: empregado supervisiona empregado).
- **Grau de associação** = nº de classes envolvidas; a maioria é **binária**; grau 3 = **ternária**.
- Numa associação ternária A-B-C, a multiplicidade do extremo C indica quantos objetos de C se associam a **cada par (a,b)**.

### 1.7 Agregação e Composição (tema clássico de concurso — decore as diferenças!)
- Ambas representam relações **todo-parte**, são **assimétricas** (se A é parte de B, B não é parte de A).

| | Agregação | Composição |
|---|---|---|
| Notação | Losango **vazio** | Losango **cheio** |
| Força do vínculo | Mais fraca | Mais forte |
| Destruição do todo | **Não** implica destruição da parte | Parte é destruída junto (tempo de vida coincidente) |
| Multiplicidade do lado "todo" | Pode ser >1 | Não excede 1 (a parte pertence a um único todo) |

### 1.8 Generalização / Especialização
- Relação entre **superclasse** e **subclasses**; também chamada relação **"é um"**.
- Uma subclasse herda **atributos, operações E associações** da superclasse.
- Termos **ancestral/descendente**: generalização entre vários níveis.
- Regra de bom senso citada nos slides: hierarquias de 2-3 níveis são aceitáveis; 10 níveis é excessivo.
- **Classe abstrata**: não gera objetos diretamente; nome em **itálico**; serve para organizar hierarquia.
- **Herança múltipla**: uma classe com mais de uma superclasse.
  - Vantagem: mais reuso e poder de especificação.
  - Desvantagem: perda de simplicidade conceitual/implementação.
  - Diferença conceitual (pegadinha de prova): **generalização** = relacionamento conceitual; **herança** = mecanismo de linguagem.

**Restrições sobre generalização (tabela decorável — cai muito em concurso):**
| Restrição | Significado |
|---|---|
| Sobreposta | Subclasses podem herdar de mais de uma superclasse (herança múltipla) |
| Disjunta (separada) | Subclasses mutuamente exclusivas |
| Completa | Todas as subclasses possíveis foram enumeradas |
| Incompleta | Nem todas as subclasses foram enumeradas |

### 1.9 Restrições (constraints) e OCL
- Restrições = informações extras que validam condições durante implementação (métodos, associações, atributos).
- Representadas entre **chaves { }**.
- Usadas para representar **regras de negócio** e requisitos não funcionais.
- **OCL (Object Constraint Language)**: linguagem para escrever restrições complexas, parecida com linguagem de programação.
- Restrições predefinidas pela UML para associações: **subset** e **xor** (exemplo clássico: conta bancária é de uma pessoa OU de uma instituição, nunca as duas → **xor**).

### 1.10 Identificadores de objetos e Enumerações
- **Não devem** ser listados em diagramas de classe de análise (são implícitos).
- Não confundir identificador interno (conveniência de implementação) com atributo do mundo real.
- **Enumeração**: tipo de dado com conjunto finito de valores (domínio fechado).

### 1.11 Padrões de Análise (Party e Metamodel)
- Um padrão de análise fornece um **fragmento de diagrama de classes reutilizável**; o trabalho de análise passa a ser **identificar o problema**, não identificar classes do zero.
- **Padrão Party**: representa **pessoas e organizações** e seus relacionamentos (ex.: `Pessoa` e `Organização` generalizam de `Parte`).
- **Padrão Metamodel**: usado quando itens de um conjunto têm **propriedades variáveis entre si**; permite mudar a estrutura do modelo **sem alterar o esquema** das classes (evita criar uma subclasse para cada tipo de item).

---

## PARTE 2 — DIAGRAMA DE TRANSIÇÃO DE ESTADOS (DTE)

### 2.1 Conceitos básicos
- Objetos assumem **estados** ao longo do tempo; mudança de estado = **transição**, disparada por **evento**.

**Elementos de um DTE (decorar a lista):**
Estado, Transição, Evento (trigger), Condição de guarda, Ação, Atividade — (elementos menos comuns: transições internas, estados aninhados, concorrentes, subestados).

### 2.2 Estado
- Situação em que o objeto satisfaz uma condição ou realiza uma atividade; determinado pelos valores de atributos e/ou ligações com outros objetos.
- Notação: retângulo de bordas arredondadas.
- **Estado inicial**: só pode haver **um** por DTE (exceto em estados aninhados/concorrentes/compostos) — pegadinha comum.
- **Estado final**: **opcional**, pode haver **mais de um**.

### 2.3 Transição
- Forma geral: `Evento(lista-parâmetro) [guarda] / ação`
- Componentes: evento, condição de guarda (entre colchetes) e ação (precedida de `/`).

### 2.4 Evento (Trigger) — classificação (tema forte de concurso)
| Tipo | Descrição |
|---|---|
| **Evento de chamada** | Recebimento de mensagem; o emissor **espera** a execução |
| **Evento de sinal** | Recebimento de sinal; emissor **não espera**; raramente usado |
| **Evento temporal** | Passagem de intervalo de tempo; cláusula **`after`** |
| **Evento de mudança** | Condição lógica se torna verdadeira; cláusula **`when`** |

### 2.5 Condição de guarda e Ação x Atividade
- **Guarda**: expressão lógica entre colchetes; transição só dispara se o evento ocorrer **E** a guarda for verdadeira. Sem guarda → dispara sempre que o evento ocorrer.
- **Ação**: executada instantaneamente (não pode ser interrompida), ligada à transição, precedida de `/`.
- **Atividade**: pode ser **interrompida** — diferença fundamental entre ação e atividade (cai muito em prova).

### 2.6 Ponto de junção
- Desenhado como **losango**; usado quando o próximo estado depende do valor de uma condição de guarda; cada transição de saída tem sua própria guarda.

### 2.7 Cláusulas entry, exit, do (dentro do próprio estado)
| Cláusula | Quando ocorre |
|---|---|
| `entry` | Ao **entrar** no estado, independente de onde veio |
| `exit` | Ao **sair** do estado, independente de para onde vai |
| `do` | Atividade **contínua** enquanto o objeto permanece no estado |

### 2.8 Transições internas x Autotransições (**clássica pegadinha de concurso**)
- **Transição interna**: NÃO muda de estado; NÃO dispara `entry`/`exit`.
- **Autotransição**: origem = destino, mas **dispara `entry` e `exit`** normalmente.
- É exatamente essa diferença (disparo ou não de entry/exit) que costuma ser cobrada.

### 2.9 Estados aninhados, compostos e concorrentes
- **Estado composto**: contém outros estados; todos os subestados **herdam** as transições do estado composto.
- Símbolo no canto inferior direito indica estado composto (detalhes escondidos).
- **Estado concorrente**: tipo especial de estado composto onde o objeto está em **dois ou mais estados independentes simultaneamente** (também chamado paralelo ou composto ortogonal).

### 2.10 Roteiro para construção de um DTE (decore a sequência — pode virar questão de ordenação)
1. Identificar classes que precisam de DTE.
2. Identificar estados relevantes.
3. Identificar eventos relevantes e as transições que eles causam.
4. Para cada estado, identificar as transições possíveis.
5. Identificar eventos internos e ações correspondentes.
6. Definir condições de guarda e ações associadas às transições.
7. Identificar atributos/ligações envolvidos em guardas e ações.
8. Definir estado inicial e estado(s) final(is).
9. Desenhar o diagrama (de cima para baixo, esquerda para direita).

---

## PARTE 3 — DIAGRAMAS DE INTERAÇÃO
### (segundo você, cai **só teoria** — resumo conceitual completo abaixo)

### 3.1 Definição geral
- **Diagrama de Interação**: termo genérico para diagramas que enfatizam **interação entre objetos**.
- **Interação**: especificação comportamental = sequência de troca de mensagens entre objetos em um contexto, com um propósito (ex.: realizar um caso de uso).
- Requer definir: **contexto** (sistema, subsistema, operação, cenário de caso de uso) + objetos que interagem + seus relacionamentos.

**4 tipos de Diagrama de Interação (decore os 4 — pode cair pergunta "quais são"):**
1. **Diagrama de Sequência** — ênfase na ordem temporal.
2. **Diagrama de Comunicação (ou colaboração)** — ênfase nos relacionamentos entre objetos.
3. **Diagrama de Visão Geral da Interação** — mistura diagrama de atividades + pequenos diagramas de sequência.
4. **Diagrama de Temporização** — foco nas restrições de tempo.

### 3.2 Diagrama de Sequência
- É uma especificação de **o quê** o sistema faz, não **como** ("caixa preta"); comportamento depende do caso de uso.
- Tempo é lido na **direção vertical de cima para baixo**: quanto mais abaixo, mais tarde.

**Elementos básicos (lista decorável):**
- **Objeto**: anônimo (`:Classe`) ou nomeado (`nome:Classe`) — nomeado é usado quando referenciado em mais de um lugar.
- **Classe**: mesma notação do objeto, mas nome **não sublinhado**; mensagem para classe dispara **operação estática**.
- **Ator**: participação opcional no diagrama.
- **Linha de vida**: linha vertical tracejada abaixo do objeto.
- **Ordem horizontal dos objetos não tem significado** — pegadinha comum.

**Mensagens — tipos (muito cobrado):**
| Tipo | Característica |
|---|---|
| **Síncrona** | Chamador **espera** a conclusão |
| **Assíncrona** | Chamador **continua** sem esperar resposta |
| **De retorno** | Especifica o término de uma mensagem anterior |
| **Reflexiva** | Objeto envia mensagem para si mesmo (própria classe ou superclasse) |

- **Criação de objeto**: seta de mensagem apontando direto para a caixa do objeto; se criado depois, o retângulo fica mais abaixo no diagrama.
- **Destruição de objeto**: representada por um **X grande**.
- **Foco de controle**: bloco retangular sobre a linha de vida; topo = recebimento da mensagem; base = fim da operação; **chamadas recursivas** → focos empilhados.
- **Sentinela (guarda)**: expressão condicional entre colchetes — mensagem só é enviada se verdadeira.
- **Marcador de iteração**: asterisco (`*`) no nome da mensagem; tem limitações, por isso a UML 2 criou os **quadros de interação**.

**Operadores de quadros de interação (tabela decorável — cai muito):**
| Operador | Significado |
|---|---|
| `alt` | Fragmentos alternativos; só o de condição verdadeira executa |
| `opt` | Opcional; executa só se condição verdadeira (equivale a `alt` com 1 caminho) |
| `par` | Execução em paralelo |
| `loop` | Execução repetida (laço) |
| `sd` | Envolve um diagrama de sequência inteiro |
| `ref` | Referência a interação definida em outro diagrama |
| `break` | Interrompe a execução |

### 3.3 Diagrama de Sequência do Sistema (DSS)
- Mostra cenário **global** do sistema, dividindo o caso de uso em **operações de sistema** (executadas em resposta a eventos).
- Segundo o **Processo Unificado**: deve-se criar **um DSS para cada caso de uso relevante**.

### 3.4 Diagrama de Comunicação
- Alternativa ao diagrama de sequência: permite **livre posicionamento** dos participantes, desenha vínculos, e usa **numeração** para indicar a sequência das mensagens.
- Pode conter objetos nomeados, anônimos, coleções e referências a elementos de coleção (igual ao de sequência).
- **Regras de numeração**: mensagem inicial **não** é numerada (opcional numerá-la); como não há eixo de tempo, **todas** as mensagens precisam de número de sequência.

**Sequência x Comunicação (tabela clássica de concurso — equivalência semântica):**
| Tipo | Pontos fortes | Pontos fracos |
|---|---|---|
| Sequência | Mostra claramente a ordem temporal; muitas opções de notação | Cresce para a direita (consome espaço horizontal) |
| Comunicação | Economiza espaço; fácil adicionar objetos em 2D | Difícil ver a sequência; menos notações; sem notação precisa para lógica de controle |
- Existe **equivalência semântica** entre os dois: um pode ser convertido no outro **sem perda de informação**.
- Na prática, a maioria prefere o diagrama de **sequência**.

### 3.5 Diagrama de Visão Geral da Interação
- Mistura de **diagrama de atividades** + **diagrama de sequência**.
- Pode ser visto como: (a) diagrama de atividades onde atividades viram pequenos diagramas de sequência; ou (b) diagrama de sequência fragmentado usando notação de fluxo de controle do diagrama de atividades.
- Serve para **modularizar** a construção de diagramas de interação.

### 3.6 Diagrama de Temporização
- Origem na **engenharia eletrônica**.
- Foco: **restrições de temporização** de um ou vários objetos.
- Observação dos slides: **pouca utilidade para aplicações comerciais** (ponto que costuma virar pegadinha de "verdadeiro/falso").

---

## Resumo rápido — pares que mais confundem em prova
- **Agregação vs. Composição** → força do vínculo e tempo de vida da parte.
- **Ação vs. Atividade** → ação não pode ser interrompida; atividade pode.
- **Transição interna vs. Autotransição** → autotransição dispara entry/exit, interna não.
- **Multiplicidade vs. Conectividade** → conectividade usa a multiplicidade máxima.
- **Evento de chamada vs. Evento de sinal** → chamada espera resposta, sinal não.
- **Mensagem síncrona vs. assíncrona** → espera ou não espera resposta.
- **Diagrama de Sequência vs. Comunicação** → equivalentes semanticamente, mas sequência mostra tempo melhor, comunicação economiza espaço.
- **Classe associativa vs. associação promovida a classe** → não são a mesma coisa.
