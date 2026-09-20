# Diagrama de Transição de Estados — Eventos, Guardas e Junções

## Índice

* [1. Evento de chamada](#1-evento-de-chamada)
* [2. Evento temporal](#2-evento-temporal)
* [3. Evento de mudança](#3-evento-de-mudança)
* [4. Condição de guarda](#4-condição-de-guarda)
* [5. Ponto de junção](#5-ponto-de-junção)
* [6. Diferença rápida](#6-diferença-rápida)
* [7. Como identificar no enunciado](#7-como-identificar-no-enunciado)

---

## 1. Evento de chamada

### O que é?

Acontece quando **outro objeto chama uma operação/serviço** do objeto.

### Quando usar?

Quando o enunciado indica que alguém ou algum objeto **solicita, chama ou executa uma operação**.

### Exemplo

```text
[Cadastrado]
     |
     | realizarInscricao()
     ↓
[Inscrito]
```

**Leia:**

> Alguém chamou `realizarInscricao()` → o objeto muda de estado.

### Palavra-chave

> **"Alguém chamou."**

---

## 2. Evento temporal

### O que é?

A mudança acontece porque **passou determinado tempo**.

### Quando usar?

Quando o enunciado fala que, depois de um intervalo de tempo, o objeto muda de estado.

### Exemplo

```text
[Ativo]
   |
   | after(30 dias)
   ↓
[Expirado]
```

**Leia:**

> Depois de 30 dias → muda para `Expirado`.

### Representação

```text
after(tempo)
```

### Palavra-chave

> **"Passou um tempo."**

---

## 3. Evento de mudança

### O que é?

Uma **condição se torna verdadeira** e isso dispara a transição.

### Quando usar?

Quando o objeto deve mudar de estado **assim que uma determinada condição ficar verdadeira**, sem depender de alguém realizar uma ação.

### Exemplo

```text
[Inscrito]
    |
    | when(hj = dataInicioProvas)
    ↓
[Aguardando avaliação]
```

**Leia:**

> Quando `hj = dataInicioProvas` se tornar verdadeiro → muda de estado.

### Representação

```text
when(condição)
```

### Palavra-chave

> **"Quando isso se tornar verdadeiro..."**

---

## 4. Condição de guarda

### O que é?

É uma condição que precisa ser **verdadeira para a transição acontecer**.

É escrita entre **colchetes `[ ]`**.

### Quando usar?

Quando existe um **"se..."**, ou seja, a transição só pode acontecer caso determinada condição seja satisfeita.

### Exemplo com evento

```text
[Cadastrado]
     |
     | realizarInscricao() [período válido]
     ↓
[Inscrito]
```

Aqui:

```text
realizarInscricao() → evento
[período válido]    → guarda
```

Leia:

> A inscrição foi realizada, **mas só muda para `Inscrito` se o período for válido**.

### A guarda pode aparecer sozinha

```text
[Estado A]
     |
     | [idade >= 18]
     ↓
[Estado B]
```

Não é obrigatório ter um evento escrito antes.

### Palavra-chave

> **"Só se..."**

---

## 5. Ponto de junção

### O que é?

É usado quando existem **vários caminhos possíveis** e precisamos decidir para qual estado o objeto vai.

É representado por um **losango `◇`**.

### Quando usar?

Quando o enunciado apresenta algo como:

* se X → estado A
* caso contrário → estado B
* dependendo de X → estado A ou B

### Exemplo

```text
                         [desclassificado]
                                ↓
[Avaliando] ───────────────→   ◇
                               │
                               │ [else]
                               ↓
                         [Avaliado]
```

O losango representa o **ponto de decisão**.

As condições ficam nas **transições que saem do losango**.

### Palavra-chave

> **"Qual caminho?"**

---

# 6. Diferença rápida

| Elemento              | Significa                                              | Exemplo                   |
| --------------------- | ------------------------------------------------------ | ------------------------- |
| **Evento de chamada** | Alguém/objeto chamou uma operação                      | `realizarInscricao()`     |
| **Evento temporal**   | Passou determinado tempo                               | `after(30 dias)`          |
| **Evento de mudança** | Uma condição se tornou verdadeira e disparou a mudança | `when(dataInicio = hoje)` |
| **Guarda**            | Condição que precisa ser verdadeira                    | `[período válido]`        |
| **Junção**            | Existem vários caminhos possíveis                      | `◇`                       |

### Para decorar

```text
EVENTO DE CHAMADA
→ "Alguém chamou."

EVENTO TEMPORAL
→ "Passou um tempo."

EVENTO DE MUDANÇA
→ "Uma condição ficou verdadeira."

GUARDA
→ "Só se..."

PONTO DE JUNÇÃO
→ "Qual caminho?"
```

---

# 7. Como identificar no enunciado

Quando encontrar uma possível transição, faça estas perguntas:

### 1. Alguém ou outro objeto solicitou uma operação?

```text
realizarInscricao()
registrarAvaliacao()
cancelarAluguel()
```

→ **Evento de chamada**

---

### 2. A mudança acontece depois de um período?

```text
após 30 dias
depois de 24 horas
```

→ **Evento temporal**

```text
after(30 dias)
```

---

### 3. A mudança acontece quando uma condição se torna verdadeira?

```text
quando chegar a data da prova
quando o pagamento for confirmado
quando todos forem avaliados
```

→ **Evento de mudança**

```text
when(condição)
```

---

### 4. Existe um "se" que limita a transição?

```text
se o período estiver válido
se a idade for maior que 18
se o atleta estiver classificado
```

→ **Condição de guarda**

```text
[condição]
```

A guarda pode aparecer **com ou sem evento**.

---

### 5. Existem dois ou mais destinos possíveis?

```text
se desclassificado → Desclassificado
senão → Avaliado
```

→ **Ponto de junção**

```text
             [desclassificado]
                    ↓
Estado ───────────→ ◇
                    ↓
                  [else]
```

---

## ⭐ Regra principal

Não confunda **evento de mudança** com **guarda**:

```text
when(condição)
```

→ **a condição ficar verdadeira é o que DISPARA a transição.**

```text
[condição]
```

→ **a condição precisa ser verdadeira para a transição ser PERMITIDA/ESCOLHIDA.**

### Exemplo final

```text
[Inscrito]
    |
    | when(hj = dataInicioProvas)
    ↓
[Aguardando avaliação]
```

> Quando chegar a data → muda.

Enquanto:

```text
[Cadastrado]
    |
    | realizarInscricao() [período válido]
    ↓
[Inscrito]
```

> Realizou a inscrição → **só muda se** o período for válido.
