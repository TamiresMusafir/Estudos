# UML — COMO ENCONTRAR AS COISAS NO TEXTO

## 📑 Índice

* [1. A ideia principal](#1-a-ideia-principal)
* [2. Como achar as classes](#2-como-achar-as-classes)
* [3. Como achar os atributos](#3-como-achar-os-atributos)
* [4. Verbos: como achar relacionamentos e classes de associação](#4-verbos-como-achar-relacionamentos-e-classes-de-associação)
* [5. Como diferenciar atributo de classe](#5-como-diferenciar-atributo-de-classe)
* [6. Como achar cardinalidades](#6-como-achar-cardinalidades)
* [7. Os símbolos](#7-os-símbolos)
* [8. “Cada X corresponde a um Y” não significa 1 × 1](#8-cada-x-corresponde-a-um-y-não-significa-1--1)
* [9. Palavras que ajudam a encontrar cardinalidade](#9-palavras-que-ajudam-a-encontrar-cardinalidade)
* [10. Regras de negócio não são automaticamente classes](#10-regras-de-negócio-não-são-automaticamente-classes)
* [11. Palavras de alerta](#11-palavras-de-alerta)
* [12. Herança](#12-herança)
* [13. Agregação / composição](#13-agregação--composição)
* [14. Informação do todo × informação de cada item](#14-informação-do-todo--informação-de-cada-item)
* [15. Regra de venda — ItemVenda](#15-regra-de-venda--itemvenda)
* [16. Atenção ao contexto](#16-atenção-ao-contexto)
* [17. Ordem para ler o minimundo](#17-ordem-para-ler-o-minimundo)
* [18. Checklist final para a prova](#18-checklist-final-para-a-prova)
* [19. A regra mais importante](#19-a-regra-mais-importante)

---

# 1. A IDEIA PRINCIPAL

Ao ler um minimundo, não tente imaginar o diagrama inteiro.

Pergunte:

> **“O que o sistema precisa saber e guardar?”**

Depois transforme as informações:

```text
COISA importante          → CLASSE
Informação sobre a coisa  → ATRIBUTO
VERBO / ação              → RELACIONAMENTO
Ação + dados próprios     → CLASSE DE ASSOCIAÇÃO
Quantidade                → CARDINALIDADE
“É um tipo de”            → HERANÇA
“no máximo”, “somente”... → REGRA DE NEGÓCIO
```

---

# 2. COMO ACHAR AS CLASSES

Comece procurando os **substantivos importantes**.

Pergunte:

> **“O sistema precisa guardar informações sobre isso?”**

Se sim, é candidato a classe.

Exemplo:

> “Dos atletas deve-se conhecer nome, número de registro, data de nascimento e país.”

→ `Atleta` é uma classe.

> “Dos campeonatos deve-se conhecer nome, ano e datas.”

→ `Campeonato` é uma classe.

> “Dos países deve-se conhecer nome e sigla.”

→ `País` é uma classe.

### ⚠️ Nem todo substantivo vira classe

Uma palavra aparecer no texto não é suficiente.

Pergunte:

> **“Isso precisa ser representado como uma coisa separada no sistema?”**

---

# 3. COMO ACHAR OS ATRIBUTOS

Depois de encontrar uma classe, procure **as informações sobre ela**.

Fique atenta a frases como:

* “Deve-se conhecer...”
* “Dos X é preciso conhecer...”
* “De cada X deve-se saber...”
* “Possui...”
* “Tem...”

Exemplo:

> “Dos países deve-se conhecer nome e sigla.”

```text
País
- nome
- sigla
```

> “Dos jurados deve-se conhecer nome, registro e país.”

```text
Jurado
- nome
- registro
- país
```

### ⭐ Regra

> **Informação SOBRE uma coisa → atributo.**

---

# 4. VERBOS: COMO ACHAR RELACIONAMENTOS E CLASSES DE ASSOCIAÇÃO

Depois de encontrar as coisas, procure os **VERBOS/AÇÕES**.

Pergunte:

> **“Quem faz o quê com quem?”**

Exemplos:

> Atleta **se inscreve** em campeonato.

→ existe uma relação entre `Atleta` e `Campeonato`.

> Atleta **representa** país.

→ `Atleta — País`.

> Jurado **avalia** o desempenho do atleta.

→ existe uma relação de avaliação.

---

## 🚨 O verbo também pode revelar uma CLASSE

Não pare quando encontrar o relacionamento.

Pergunte:

> **“Essa ação tem informações próprias que precisam ser registradas?”**

Se tiver, pense em **classe de associação**.

### Exemplo: Inscrição

> “O atleta se inscreve no campeonato.”

A princípio:

```text
Atleta ───── Campeonato
```

Mas o texto também informa:

* data da inscrição
* aparelho em que vai competir

Esses dados pertencem à **inscrição**, não simplesmente ao atleta ou ao campeonato.

Então:

```text
Atleta ───── Inscrição ───── Campeonato
                 │
                 └── Aparelho
```

→ `Inscrição` é uma classe de associação.

---

### Exemplo: Avaliação

> “Os jurados avaliam o desempenho do atleta, registrando uma nota para a dificuldade e outra para a execução, podendo desclassificá-lo.”

O verbo é:

**avaliar**

Mas a ação possui dados próprios:

* nota de dificuldade
* nota de execução
* desclassificação

Então:

```text
Jurado ───── Avaliação ───── Atleta/Inscrição
                │
                ├── notaDificuldade
                ├── notaExecução
                └── desclassificado
```

### ⭐ Padrão para decorar

```text
VERBO
  ↓
Quem faz o quê com quem?
  ↓
RELACIONAMENTO
  ↓
Esse relacionamento tem dados próprios?
  ↓
SIM → pensar em CLASSE DE ASSOCIAÇÃO
```

### ⚠️ Não é qualquer verbo que vira classe!

Primeiro o verbo indica um **relacionamento**.

Só pense em classe de associação quando a ação/ocorrência possui **informações próprias**.

---

# 5. COMO DIFERENCIAR ATRIBUTO DE CLASSE

Quando ficar em dúvida, pergunte:

> **“Isso é apenas uma informação ou é algo que o sistema trata como um objeto separado?”**

### Informação → atributo

```text
Jurado
- nome
- númeroRegistro
```

### Objeto/registro próprio → classe

```text
Jurado
Campeonato
Aparelho
Inscrição
Avaliação
```

### ⭐ Outra pergunta útil:

> **“Isso possui informações próprias?”**

Se algo precisa ter seus próprios dados, aumenta a chance de ser uma classe.

Exemplo:

`Inscrição` possui:

```text
- data
- aparelho
```

`Avaliação` possui:

```text
- notaDificuldade
- notaExecução
- desclassificação
```

---

# 6. COMO ACHAR CARDINALIDADES

Depois de descobrir os relacionamentos, faça **duas perguntas**.

### Pergunta 1

> Para **1 objeto de A**, quantos objetos de B existem?

### Pergunta 2

> Para **1 objeto de B**, quantos objetos de A existem?

Só depois coloque os símbolos.

---

# 7. OS SÍMBOLOS

```text
1      = exatamente 1

0..1   = zero ou um

1..*   = um ou mais

0..*   = zero ou vários

*      = abreviação de 0..*
```

Portanto:

> **`*` e `0..*` significam a mesma coisa.**

Se a professora usa `*`, siga a notação dela.

---

# 8. “CADA X CORRESPONDE A UM Y” NÃO SIGNIFICA 1 × 1

Essa é uma pegadinha importante.

Exemplo:

> “Cada inscrição corresponde a um aparelho.”

Isso responde apenas:

**1 inscrição → 1 aparelho**

Ainda precisamos perguntar:

> **1 aparelho → quantas inscrições?**

Várias.

Então:

```text
Inscrição * ───── 1 Aparelho
```

Outro exemplo:

> “De cada inscrição é preciso conhecer a qual campeonato ela se refere.”

→ 1 inscrição → 1 campeonato.

Mas:

→ 1 campeonato → várias inscrições.

Então:

```text
Inscrição * ───── 1 Campeonato
```

### ⭐ Regra

> **“Cada X tem um Y” responde apenas um dos lados.**

Sempre faça a segunda pergunta.

---

# 9. PALAVRAS QUE AJUDAM A ENCONTRAR CARDINALIDADE

Fique atenta a:

### “cada”, “um único”

→ normalmente `1`

### “vários”, “diversos”, “muitos”

→ `*`

### “pode ter”

→ pode indicar `0..*`, se puder não ter nenhum.

### “um ou mais”

→ `1..*`

### “pode não ter”

→ começa com `0`.

---

# 10. REGRAS DE NEGÓCIO NÃO SÃO AUTOMATICAMENTE CLASSES

Algumas frases apenas explicam **regras do sistema**.

Exemplo:

> “O atleta só conhece sua classificação depois que todos os atletas se apresentarem.”

Isso é uma regra.

Não significa automaticamente criar uma classe `Classificação`.

Outro exemplo:

> “Primeiro lugar recebe ouro, segundo prata e terceiro bronze.”

Também pode ser uma regra/resultado derivado.

### ⭐ Pergunte:

> **“O sistema precisa armazenar isso como uma coisa própria?”**

Se não, provavelmente é apenas uma regra.

---

# 11. PALAVRAS DE ALERTA

Quando aparecer:

* **cadastrar**
* **registrar**
* **identificar**
* **armazenar**
* **conhecer**

⚠️ Pare e leia novamente.

Essas palavras frequentemente indicam que o sistema precisa **guardar alguma informação**.

Exemplo:

> “Ao cadastrar um jurado para um campeonato...”

Pergunte:

> **“O que exatamente precisa ser registrado?”**

Nesse caso:

* qual jurado
* para qual campeonato
* quais aparelhos ele pode julgar

### ⚠️ “Registrar” também pode revelar atributos

Exemplo:

> “registrando uma nota para a dificuldade e outra para a execução.”

→ o sistema precisa guardar:

```text
notaDificuldade
notaExecução
```

---

# 12. HERANÇA

Para encontrar herança, faça uma pergunta simples:

> **“X é um tipo de Y?”**

Exemplo:

> Atleta é uma Pessoa?

Sim:

```text
Pessoa
  ▲
  │
Atleta
```

> Jurado é uma Pessoa?

Sim:

```text
Pessoa
  ▲
  │
Jurado
```

Mas:

> País é uma Pessoa?

Não.

Nesse caso:

```text
Atleta ─── representa ─── País
Jurado ─── representa ─── País
```

`País` é uma classe separada.

---

# 13. AGREGAÇÃO / COMPOSIÇÃO

Não use agregação/composição simplesmente porque duas classes possuem uma relação.

Primeiro procure uma relação de:

> **TODO × PARTE**

Pergunte:

> **“Isso faz parte daquilo?”**

Exemplo:

```text
Pedido
 └── ItemPedido
```

O item faz parte daquele pedido.

### ⚠️

> **Ter uma relação ≠ ter composição.**

Primeiro precisa existir a ideia de **todo e parte**.

---

# 14. INFORMAÇÃO DO TODO × INFORMAÇÃO DE CADA ITEM

Quando houver vários itens, pergunte:

> **“Essa informação vale para o conjunto inteiro ou muda para cada item?”**

Exemplo:

```text
Aluguel
- cliente
- loja
- datas gerais
```

Essas informações valem para o aluguel inteiro.

Mas:

```text
ItemSolicitacao
- quantidade
- equipamento
- grupo
```

mudam de item para item.

### ⭐ Regra

> **Informação do conjunto → classe do conjunto.**
>
> **Informação que varia por item → classe do item.**

---

# 15. REGRA DE VENDA — ITEMVENDA

⚠️ **Regra importante da professora:**

Quando o minimundo envolver **venda** e existir uma classe `ItemVenda`, verifique se o `ItemVenda` possui o **valor**.

Isso acontece porque:

> **Valor do produto ≠ valor do produto naquela venda.**

Exemplo:

```text
Produto
- nome
- valor

ItemVenda
- quantidade
- valor
```

O `Produto.valor` representa o valor atual/cadastrado do produto.

O `ItemVenda.valor` representa **o valor pelo qual aquele produto foi vendido naquela venda**.

Isso é importante porque o preço do produto pode mudar depois, mas a venda antiga precisa continuar registrando o valor praticado naquele momento.

### ⭐ Regra para a prova

> **Tem `ItemVenda`? → Verifique o `valor` do `ItemVenda`.**

---

# 16. ATENÇÃO AO CONTEXTO

Uma informação pode parecer simples até você perceber **em qual contexto ela acontece**.

Exemplo:

> “Ao cadastrar um jurado **para um campeonato**...”

O trecho **“para um campeonato”** é importante.

A habilitação não é simplesmente uma característica fixa do jurado.

Outro exemplo:

> “De cada inscrição é preciso conhecer **a qual campeonato ela se refere**.”

“De cada inscrição” mostra que estamos procurando uma informação da `Inscrição`.

### ⭐ Pergunte:

> **Quem?**
>
> **Faz o quê?**
>
> **Com quem?**
>
> **Para quem?**
>
> **Em qual contexto?**
>
> **Essa informação pertence a quem?**

---

# 17. ORDEM PARA LER O MINIMUNDO

Não tente encontrar tudo ao mesmo tempo.

Faça assim:

### ① SUBSTANTIVOS

Circule as coisas importantes.

```text
Atleta
Campeonato
País
Aparelho
Jurado
...
```

→ possíveis **classes**

---

### ② INFORMAÇÕES

Veja o que precisa ser conhecido sobre cada coisa.

```text
nome
data
número
sigla
...
```

→ **atributos**

---

### ③ VERBOS

Procure as ações.

```text
representa
se inscreve
avalia
julga
...
```

Pergunte:

> **Quem faz o quê com quem?**

→ **relacionamentos**

---

### ④ DADOS DA AÇÃO

Quando encontrar um verbo, pergunte:

> **“Essa ação tem informações próprias?”**

Se sim:

→ **classe de associação**

Ex.:

```text
se inscreve
    ↓
Inscrição
- data
- aparelho
```

```text
avalia
   ↓
Avaliação
- nota dificuldade
- nota execução
- desclassificação
```

---

### ⑤ QUANTIDADES

Procure:

```text
cada
um
único
vários
muitos
pode
um ou mais
```

→ **cardinalidades**

---

### ⑥ HERANÇA

Pergunte:

> **“X é um tipo de Y?”**

→ **herança**

---

### ⑦ REGRAS

Procure:

```text
no máximo
somente
caso
depois que
não pode
```

→ **regras de negócio**

---

# 18. CHECKLIST FINAL PARA A PROVA

Depois de ler o minimundo, confira:

```text
CLASSES
□ Circulei as coisas importantes?
□ O sistema precisa guardar informações sobre elas?

ATRIBUTOS
□ O que preciso conhecer sobre cada classe?
□ Essa informação pertence a qual classe?

RELACIONAMENTOS
□ Quais verbos aparecem?
□ Quem faz o quê com quem?

CLASSES DE ASSOCIAÇÃO
□ Algum verbo/ação possui dados próprios?
□ Esses dados precisam ser registrados?

CARDINALIDADES
□ Para 1 A, quantos B?
□ Para 1 B, quantos A?

HERANÇA
□ X é um tipo de Y?

REGRAS
□ Apareceu “no máximo”, “somente”, “caso”, etc.?
□ Isso é uma regra em vez de uma classe?

CONTEXTO
□ Apareceu “para”, “em”, “de cada”, “naquele campeonato”?
□ Essa informação depende de outra entidade?

VENDA
□ Existe `ItemVenda`?
□ Se existe, coloquei/verifiquei o `valor` do `ItemVenda`?
□ Lembrei que valor do produto ≠ valor do item da venda?
```

---

# 19. A REGRA MAIS IMPORTANTE

Não leia o minimundo pensando:

> **“Qual classe a professora quer que eu encontre?”**

Leia pensando:

> **“O que o sistema precisa saber/guardar?”**

E transforme:

```text
COISA
   ↓
CLASSE

INFORMAÇÃO SOBRE A COISA
   ↓
ATRIBUTO

VERBO
   ↓
RELACIONAMENTO

VERBO + DADOS PRÓPRIOS
   ↓
CLASSE DE ASSOCIAÇÃO

QUANTIDADE
   ↓
CARDINALIDADE

“X É UM TIPO DE Y?”
   ↓
HERANÇA

“NO MÁXIMO / SOMENTE / CASO...”
   ↓
REGRA DE NEGÓCIO
```

### ⭐ Em uma frase:

> **Primeiro encontre as coisas, depois as informações, depois as ações, depois veja se alguma ação possui dados próprios e, por fim, descubra quantos de cada lado existem.**
