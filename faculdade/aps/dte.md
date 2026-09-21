# Diagrama de Transição de Estados — Eventos, Guardas e Junções

## Índice

* [1. Evento de chamada](#1-evento-de-chamada)
* [2. Evento temporal](#2-evento-temporal)
* [3. Evento de mudança](#3-evento-de-mudança)
* [4. Condição de guarda](#4-condição-de-guarda)
* [5. Ponto de junção](#5-ponto-de-junção)
* [6. Diferença rápida](#6-diferença-rápida)
* [7. Como identificar no enunciado](#7-como-identificar-no-enunciado)
* [8. Exemplo: desclassificação](#8-exemplo-desclassificação)

---

## 1. Evento de chamada

### Identifique quando:

**Alguém/objeto faz alguma coisa → isso provoca a mudança.**

### Palavras comuns

> realizar, registrar, cancelar, solicitar, retirar, devolver...

### Exemplo

```text
[Cadastrado]
     |
     | realizarInscricao()
     ↓
[Inscrito]
```

**Pense:**

> **"Alguém fez alguma coisa."**

→ **EVENTO DE CHAMADA**

---

## 2. Evento temporal

### Identifique quando:

A mudança acontece porque **passou um tempo**.

### Palavras comuns

> após 30 dias, depois de 24 horas, quando acabar o prazo...

### Exemplo

```text
[Ativo]
   |
   | after(30 dias)
   ↓
[Expirado]
```

→ **EVENTO TEMPORAL**

### Pense:

> **"Passou um tempo."**

---

## 3. Evento de mudança

### Identifique quando:

**Uma condição fica verdadeira → isso dispara a mudança.**

### Palavras comuns

> quando chegar..., quando todos..., quando atingir..., assim que...

### Exemplo

```text
[Inscrito]
    |
    | when(hj = dataInicioProvas)
    ↓
[Aguardando avaliação]
```

→ **EVENTO DE MUDANÇA**

### Pense:

> **"Quando isso ficar verdadeiro..."**

### Fórmula

```text
when(condição)
```

---

## 4. Condição de guarda

### Identifique quando:

Existe um **"se"** que diz que a transição **só pode acontecer naquela condição**.

### Palavras comuns

> se, somente se, caso, desde que...

### Exemplo

```text
[Cadastrado]
     |
     | realizarInscricao() [período válido]
     ↓
[Inscrito]
```

```text
realizarInscricao() → EVENTO
[período válido]    → GUARDA
```

### Pense:

> **"Só se..."**

### Fórmula

```text
[condição]
```

---

## 5. Ponto de junção

### Identifique quando:

Existe **mais de um resultado possível**.

> Se X → caminho A
> Senão → caminho B

Representado por:

```text
◇
```

### Exemplo

```text
                 [desclassificação]
                        ↓
[Avaliando] ──────────→ ◇
                        |
                      [else]
                        ↓
                    [Avaliado]
```

→ **PONTO DE JUNÇÃO**

### Pense:

> **"Qual caminho?"**

As condições ficam **depois do losango**:

```text
◇
├── [condição] → Estado A
└── [else]     → Estado B
```

---

# 6. Diferença rápida

| Se o texto diz...                        | Use                          |
| ---------------------------------------- | ---------------------------- |
| alguém **fez alguma coisa**              | **Evento de chamada**        |
| **passou um tempo**                      | **Evento temporal**          |
| **quando** uma condição ficar verdadeira | **Evento de mudança `when`** |
| **se / somente se / caso**               | **Guarda `[ ]`**             |
| existem **vários resultados**            | **Junção `◇`**               |

### COLA:

```text
ALGUÉM FEZ?
→ evento de chamada

PASSOU TEMPO?
→ evento temporal

CONDIÇÃO FICOU VERDADEIRA?
→ when

"SÓ SE..."?
→ [guarda]

VÁRIOS CAMINHOS?
→ ◇ junção
```

---

# 7. Como identificar no enunciado

Não tente classificar o texto inteiro.

Primeiro procure:

> **O objeto mudou de situação?**

Se sim, pergunte:

### ① O que fez mudar?

**Alguém fez algo?**

→ evento

**Passou tempo?**

→ `after`

**Uma condição ficou verdadeira?**

→ `when`

---

### ② Existe um "só se"?

→ `[guarda]`

---

### ③ Existem vários resultados?

→ `◇` **junção**

E coloque uma guarda em cada caminho:

```text
       ◇
      / \
 [condição] [else]
    ↓         ↓
 Estado A   Estado B
```

---

# 8. Exemplo: desclassificação

### Frase do enunciado

> **"Uma desclassificação pode ocorrer, por exemplo, se o atleta abandonar o tablado ou aparelho sem concluir o exercício."**

Aqui tem uma pista MUITO importante:

```text
se o atleta abandonar
       +
sem concluir o exercício
       ↓
DESCLASSIFICADO
```

→ Isso é uma **condição**.

Portanto:

```text
[abandona o aparelho sem concluir]
                ↓
        Desclassificado
```

### No exercício da ginástica:

O atleta é avaliado e existem dois resultados:

```text
              Registrar avaliação
                      ↓
                      ◇
                    /   \
                   /     \
[desclassificação]       [else]
        ↓                   ↓
Desclassificado          Avaliado
```

### Como pensar:

**Abandonou sem concluir?**

→ `[desclassificação]`

**Não?**

→ `[else]` → `Avaliado`

### ⭐ Pista para decorar

> **"Pode ser desclassificado se..."**

O **"se"** é a pista da condição.

---

# ⭐ REGRA MAIS IMPORTANTE

Não confunda:

```text
when(condição)
```

com:

```text
[condição]
```

### `when`

A condição **DISPARA** a mudança:

```text
when(data chegou)
```

> "Quando chegar a data → muda."

### `[condição]`

A condição **DECIDE/PERMITE** o caminho:

```text
[período válido]
```

> "Só pode seguir por aqui se for válido."

---

## 🧠 Mini cola final

```text
EVENTO
→ alguém fez algo

after
→ passou tempo

when
→ condição ficou verdadeira
→ DISPARA

[ ]
→ condição precisa ser satisfeita
→ DECIDE/PERMITE
```
