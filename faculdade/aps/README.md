# Guia de Estudo — APS (Análise e Projeto de Sistemas)
### Diagrama de Classes, Diagrama de Transição de Estados e Diagramas de Interação

> Organizado por slide/tema, com foco em definições, regras e pontos que costumam cair em **questões de concurso**.

---
# PARTE 1 — DIAGRAMA DE CLASSES DE ANÁLISE

## 1.1 Modelagem de Classes — conceitos básicos

* **Diagrama de Classes** representa o aspecto **estrutural e estático** do sistema: quais classes existem, seus atributos e como se relacionam.
* O aspecto **dinâmico** mostra o comportamento: eventos, mensagens e mudanças ao longo do tempo.

### 3 níveis de abstração

| Nível                        | O que representa                                              |
| ---------------------------- | ------------------------------------------------------------- |
| **Classes de domínio**       | Conceitos do problema, **sem tecnologia**                     |
| **Classes de especificação** | Domínio + detalhes necessários para a **solução do software** |
| **Classes de implementação** | Especificação adaptada para uma **linguagem de programação**  |

🧠 **Ordem:** domínio → especificação → implementação.

---

## 1.2 Técnicas de identificação de classes

Duas técnicas principais:

* **Análise dos Casos de Uso** — identifica classes a partir do comportamento que o sistema precisa oferecer externamente.
* **Análise Textual de Abbott** — procura termos importantes no texto do problema.

### Categorização BCE (Jacobson)

| Estereótipo    | Função                                                                 |
| -------------- | ---------------------------------------------------------------------- |
| `<<boundary>>` | Interface entre **ator e sistema**                                     |
| `<<control>>`  | Coordena o comportamento do **caso de uso**                            |
| `<<entity>>`   | Representa objetos do **domínio do problema**, geralmente persistentes |

🧠 **Fluxo típico:** `ator → boundary → control → entity`

### Análise Textual de Abbott

1. Procurar **substantivos/adjetivos**.
2. Remover **sinônimos**.
3. Classificar os termos: **classe, atributo ou irrelevante**.

* Verbo de **ação** → operação: `calcular`, `cancelar`, `registrar`.
* Verbo **"ter"** → relação **todo-parte**: agregação/composição.
* Verbo **"ser"** → **generalização**: "Aluno é uma Pessoa".

### Tabela rápida

| Texto            | Pode indicar      | Exemplo            |
| ---------------- | ----------------- | ------------------ |
| Nome próprio     | **Objeto**        | João               |
| Nome comum       | **Classe**        | Aluno              |
| Verbo de ação    | **Operação**      | Registrar          |
| "É um" / "é uma" | **Generalização** | Aluno é uma Pessoa |
| "Tem / possui"   | **Todo-parte**    | Pedido tem Itens   |

---

## 1.3 Nomenclatura

* **Classes e relacionamentos:** começam com letra maiúscula: `Cliente`, `ItemPedido`.
* **Atributos e operações:** começam com minúscula e usam `camelCase`: `quantidade`, `precoUnitario`, `dataNascimento`.
* **Identificadores:** removem espaços e preposições.

---

## 1.4 Associações, multiplicidade e conectividade

### Multiplicidade

Indica **quantos objetos** podem estar associados a um objeto do outro lado.

| Multiplicidade | Significado    |
| -------------- | -------------- |
| `1` ou `1..1`  | exatamente um  |
| `0..1`         | zero ou um     |
| `0..*` ou `*`  | zero ou muitos |
| `1..*`         | um ou muitos   |
| `m..n`         | entre m e n    |

🧠 **Mínimo = é obrigatório ou opcional?**
🧠 **Máximo = quantos podem existir?**

* Mínimo `1` → participação **obrigatória**.
* Mínimo `0` → participação **opcional**.

### Conectividade

Indica se a relação é **1:1, 1:N ou N:N**.

⚠️ **Pegadinha:** conectividade considera a **multiplicidade máxima**, enquanto multiplicidade mostra o intervalo completo (`mínimo..máximo`).

### Adornos de associação

Recursos usados para deixar a associação mais clara:

* **nome da associação**
* **papel (role)**
* **sentido de leitura**

---

## 1.5 Classes associativas

Usadas quando é necessário guardar **informações sobre a própria associação** entre objetos.

Exemplo:

```text
Aluno ───── Matrícula ───── Disciplina
              |
           dataMatrícula
           nota
```

`dataMatrícula` e `nota` pertencem à **relação**, não diretamente a Aluno ou Disciplina.

* Mais comum em associações **muitos-para-muitos**.
* ⚠️ Não é exclusiva de muitos-para-muitos: pode aparecer em outros tipos de associação.
* Uma classe associativa permite **uma ocorrência por combinação de objetos** envolvidos na associação.

---

## 1.6 Associações reflexivas e ternárias

### Reflexiva (auto-associação)

Uma classe se relaciona **com ela mesma**.

Exemplo:

```text
Empregado ───── supervisiona ───── Empregado
```

São dois objetos diferentes da mesma classe, com papéis diferentes.

### Grau da associação

É o **número de classes envolvidas**:

* 2 classes → **binária** (mais comum)
* 3 classes → **ternária**

Em uma associação ternária `A-B-C`, a multiplicidade de `C` indica quantos objetos de `C` podem se associar a **cada combinação de um objeto de A + um objeto de B**.

---

## 1.7 Agregação e Composição

As duas representam relação **todo-parte**.

### Símbolos

|                   | Agregação                      | Composição                              |
| ----------------- | ------------------------------ | --------------------------------------- |
| Símbolo           | `◇` losango vazio              | `◆` losango cheio                       |
| Vínculo           | mais fraco                     | mais forte                              |
| Todo é destruído  | parte pode continuar existindo | parte deixa de existir junto com o todo |
| Um todo por parte | pode haver mais de um          | uma parte pertence a no máximo um todo  |

🧠 **Decore pelo símbolo:**

`◇` = **agregação**
`◆` = **composição**

⚠️ A palavra "composta" no enunciado **não significa automaticamente composição**. Quem define é o **símbolo UML**.

---

## 1.8 Generalização / Especialização

Representa uma relação de **"é um"** entre uma classe mais geral e classes mais específicas.

Exemplo:

```text
        Pessoa
          △
         / \
    Aluno  Professor
```

* `Pessoa` = **superclasse**
* `Aluno` e `Professor` = **subclasses**
* A subclasse herda **atributos, operações e associações** da superclasse.

### Classe abstrata

* Serve como **base para outras classes**.
* Não gera objetos diretamente.
* Nome aparece em **itálico**.

### Herança múltipla

Uma classe possui **mais de uma superclasse**.

* Vantagem: mais reuso.
* Desvantagem: maior complexidade.

🧠 **Pegadinha:**

* **Generalização** = relacionamento conceitual da UML.
* **Herança** = mecanismo de implementação em uma linguagem.

### Restrições de generalização

| Restrição      | Significado                                                |
| -------------- | ---------------------------------------------------------- |
| **Sobreposta** | Um mesmo objeto pode pertencer a **mais de uma subclasse** |
| **Disjunta**   | Um objeto só pode pertencer a **uma subclasse**            |
| **Completa**   | Todas as subclasses possíveis foram **enumeradas**         |
| **Incompleta** | Ainda podem existir outras subclasses                      |

⚠️ **Sobreposta ≠ herança múltipla.**

* **Sobreposta:** um objeto pode acumular subclasses.
* **Herança múltipla:** uma classe possui várias superclasses.

---

## 1.9 Restrições (Constraints) e OCL

**Restrição (constraint)** = regra que precisa ser respeitada pelo modelo/sistema.

* Representada entre **chaves `{ }`**.
* Pode representar **regras de negócio** e outras condições do modelo.
* **OCL (Object Constraint Language)** é uma linguagem usada para escrever restrições de forma precisa.

### Restrições UML comuns

* **`subset`** → uma associação/conjunto deve estar contido em outro.
* **`xor`** → uma opção **OU** outra, mas **nunca as duas**.

Exemplo:

```text
Conta pertence a Pessoa XOR Instituição
```

→ pertence a uma ou à outra, **não às duas**.

---

## 1.10 Identificadores de objetos e Enumerações

### Identificador

* Identificadores internos usados apenas para facilitar a implementação normalmente são **implícitos** no diagrama de classes de análise.
* Não confundir com atributos reais do domínio.

Exemplo:

`CPF` pode ser um atributo importante do domínio, enquanto um `id` criado apenas pelo banco pode ser detalhe de implementação.

### Enumeração

É um tipo com **conjunto fechado de valores possíveis**.

Exemplo:

```text
Status = {ATIVO, INATIVO, CANCELADO}
```

🧠 **Enumeração = lista fechada de opções.**

---

## 1.11 Padrões de Análise — Party e Metamodel

### O que é um padrão de análise?

É uma **solução/modelo reutilizável** para problemas que aparecem com frequência.

Em vez de criar toda a estrutura do zero, o analista pode reutilizar um padrão conhecido.

### Party

**Party é um padrão de análise para representar quem participa de relações**, principalmente **pessoas e organizações**.

Exemplo:

```text
              Parte
             /     \
        Pessoa    Organização
```

Aqui:

* `Parte` é uma classe mais geral.
* `Pessoa` e `Organização` são especializações.
* A relação entre elas é uma **generalização**.

⚠️ **Party não é a generalização.**
**Party é o padrão; a generalização é uma relação UML usada dentro do padrão.**

### Metamodel

Usado quando existem itens de um mesmo conjunto, mas suas **propriedades/tipos podem variar**.

Em vez de criar uma nova subclasse para cada tipo, o tipo pode ser tratado como **dados do modelo**.

🧠 **Metamodel = permite variar a estrutura/tipos sem precisar alterar as classes toda vez.**


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
