# Guia de Estudo: Intimidade na Internet e Igualdade Algorítmica

*Legislação e Informática · material para entender os temas e elaborar teses com argumentos fortes · prova em 2 dias*

> **Como este guia foi pensado.** Você não precisa decorar redações prontas. Precisa de três coisas: (1) entender cada conceito de verdade, (2) ter repertório (lei, caso real, autor, dado) para provar o que afirma, e (3) ter um esqueleto fixo (o modelo coringa da seção 5) onde encaixar qualquer tema digital. Tudo aqui serve a esses três objetivos.

---

## 0. Antes de começar: o que são os dois temas

*Explicação rápida, em linguagem simples, para entender os dois temas antes de estudar o restante do guia.*

### 0.1 Intimidade na internet

É o direito de manter privadas as coisas pessoais da sua vida, mesmo estando online.

Na internet você deixa rastros o tempo todo:

- o que pesquisa;
- onde está (localização);
- o que compra;
- com quem fala;
- que fotos e posts publica.

Empresas e governos conseguem juntar esses rastros e saber muito sobre você, às vezes mais do que você contou a alguém. O tema pergunta: **até onde eles podem ir?**

**Assuntos que costumam aparecer:**

- anúncios que parecem "ler sua mente";
- termos de uso que ninguém lê (consentimento de fachada);
- vazamento de dados;
- câmeras com reconhecimento facial;
- a **LGPD**, a lei brasileira que protege os dados pessoais.

### 0.2 Igualdade algorítmica

É a ideia de que os sistemas automáticos da internet não podem tratar as pessoas de forma injusta.

**Algoritmo** é uma sequência de regras que decide coisas por você, por exemplo:

- o que aparece no seu feed;
- se um banco libera crédito;
- quais currículos uma empresa seleciona;
- quem a polícia identifica como suspeito.

**O problema:** o algoritmo aprende com dados do passado, e o passado tem preconceito.

> **Exemplo:** se uma empresa contratou mais homens durante anos, o sistema pode concluir que homens "servem mais" para a vaga, sem ninguém ter programado isso.

O tema pergunta: **como evitar que a tecnologia repita e aumente as desigualdades que já existem?**

### 0.3 Como os dois se ligam

- O primeiro tema é sobre **os dados que coletam de você**.
- O segundo é sobre **o que fazem com esses dados para decidir coisas sobre você**.

Quanto mais dados coletados e menos transparência, maior o risco de decisões injustas.

```
Você usa a internet → deixa rastros → coletam seus dados (TEMA 1)
→ montam um perfil → algoritmos decidem com base nele (TEMA 2)
→ se houver viés, a desigualdade se repete
```

### 0.4 Resumo para lembrar

| | Intimidade na internet | Igualdade algorítmica |
| --- | --- | --- |
| **Pergunta central** | O que podem saber e fazer com as minhas informações? | O sistema trata todo mundo de forma justa? |
| **Palavra-chave** | Privacidade | Não discriminação |
| **Problema principal** | Coleta excessiva, exposição e vazamento de dados | Viés nos dados e decisões automáticas injustas |
| **Lei para citar** | LGPD; Constituição, art. 5º, X | LGPD (não discriminação e revisão de decisões automatizadas); Constituição, art. 5º |
| **Solução típica** | Transparência, segurança e fiscalização | Auditoria, transparência e dados mais representativos |

> **Próximo passo:** com isso claro, siga para a seção 1 (mapa geral) e depois para o Tema 1.

---

## 1. Mapa geral: a ideia central em uma página

Os dois temas são dois momentos da mesma cadeia:

```
PESSOA usa a internet
   ↓  deixa rastros (cliques, localização, compras, mensagens)
DADOS PESSOAIS são coletados e armazenados
   ↓  → aqui mora o tema 1: INTIMIDADE / PRIVACIDADE / PROTEÇÃO DE DADOS
PERFILAMENTO: empresas e governos montam um "perfil" da pessoa
   ↓
ALGORITMOS usam o perfil e os dados históricos para decidir
(o que mostrar, quem contratar, quem recebe crédito, quem é suspeito)
   ↓  → aqui mora o tema 2: IGUALDADE ALGORÍTMICA / NÃO DISCRIMINAÇÃO
DECISÕES AUTOMATIZADAS afetam a vida real da pessoa
   ↓
Se os dados ou o modelo carregam preconceito, a desigualdade é reproduzida em escala
```

**Pergunta-chave do tema 1:** o que pode ser feito com as minhas informações, e com que limites?

**Pergunta-chave do tema 2:** como os sistemas automatizados tratam pessoas e grupos diferentes, e isso é justo?

> **Decore (duas frases-âncora).**
> 1. *O direito à intimidade não deixa de existir no ambiente digital; ao contrário, a capacidade de coletar e processar dados em massa torna sua proteção ainda mais necessária.*
> 2. *A tecnologia não é neutra quando aprende com dados produzidos por uma sociedade desigual: sem controle, o algoritmo transforma preconceito histórico em decisão aparentemente objetiva.*

---

## 2. Tema 1: Direito à intimidade no contexto contemporâneo da internet

### 2.1 Conceitos que você precisa dominar

| Conceito | Definição em linguagem simples | Para que serve na redação |
| --- | --- | --- |
| **Intimidade** | Esfera mais interna da pessoa: saúde, sexualidade, convicções, pensamentos, afetos | Mostrar o que há de mais sensível a proteger |
| **Vida privada** | Relações familiares, domésticas e sociais restritas, fora do olhar público | Distinguir de intimidade (a CF cita as duas, no art. 5º, X) |
| **Privacidade** | Termo guarda-chuva: direito de controlar o acesso à própria vida e a informações pessoais | Conceito geral do tema |
| **Proteção de dados** | Regras sobre como dados pessoais são coletados, usados, guardados e compartilhados | Mostrar que o Direito foi além do "ser deixado em paz" |
| **Autodeterminação informativa** | Poder de a pessoa decidir quando, como e por quem seus dados são usados | Conceito central da LGPD (art. 2º, II); muito valorizado |
| **Dado pessoal** | Informação relacionada a pessoa natural identificada ou identificável (LGPD, art. 5º, I) | Base de qualquer argumento sobre a LGPD |
| **Dado pessoal sensível** | Origem racial ou étnica, convicção religiosa, opinião política, filiação sindical, saúde, vida sexual, dado genético ou biométrico (art. 5º, II) | Argumento de maior risco de discriminação |
| **Rastro digital** | Conjunto de vestígios deixados pelo uso da internet (histórico, localização, curtidas) | Explicar de onde vêm os dados |
| **Perfilamento (profiling)** | Montar um perfil de comportamento, consumo, crédito ou personalidade a partir de dados | Ponte para o tema 2 |
| **Consentimento** | Manifestação livre, informada e inequívoca do titular para uma finalidade determinada (art. 5º, XII) | Base do argumento sobre "termos de uso que ninguém lê" |
| **Vigilância** | Monitoramento sistemático de pessoas, por Estado ou empresas | Argumento sobre poder e controle |
| **Anonimização** | Tornar o dado impossível de associar a uma pessoa, por meios técnicos razoáveis | Solução técnica; dado anonimizado sai do alcance da LGPD, salvo reversão |

> **Intimidade × privacidade × proteção de dados (não confunda).** Intimidade e vida privada são o **conteúdo** protegido (o que é só seu). Privacidade é o **gênero** que reúne os dois. Proteção de dados é o **conjunto de regras e de instrumentos** para controlar o uso das informações pessoais, sejam elas íntimas ou não. Hoje o STF e a Constituição tratam a proteção de dados como direito fundamental próprio.

**Teoria das esferas (para quem quiser aprofundar).** Costuma-se imaginar círculos concêntricos: no centro, a **intimidade** (segredo, o que só a pessoa conhece); ao redor, a **vida privada** (família, amigos, casa); e na borda, a **esfera social/pública** (trabalho, atividades abertas). Quanto mais ao centro, mais forte a proteção.

### 2.2 Base legal: o que citar e como citar

| Norma | O que diz (essência) | Como usar na redação |
| --- | --- | --- |
| **CF/88, art. 5º, X** | São invioláveis a intimidade, a vida privada, a honra e a imagem das pessoas, assegurado direito a indenização por dano material ou moral | Fundamento constitucional básico |
| **CF/88, art. 5º, XII** | Inviolabilidade do sigilo da correspondência e das comunicações (dados e telefônicas, salvo ordem judicial para investigação criminal) | Comunicações privadas online |
| **CF/88, art. 5º, LXXIX** (EC 115/2022) | Direito fundamental à proteção dos dados pessoais, inclusive nos meios digitais | Proteção de dados é direito fundamental **expresso** desde 2022 |
| **CF/88, art. 5º, LXXII** | *Habeas data*: acesso e retificação de informações da pessoa em bancos de dados públicos | Instrumento clássico de controle |
| **CF/88, art. 22, XXX** (EC 115/2022) | Competência privativa da União para legislar sobre proteção e tratamento de dados pessoais | Uniformidade nacional |
| **Marco Civil da Internet** (Lei 12.965/2014) | Princípios: liberdade de expressão, proteção da privacidade, proteção dos dados pessoais (art. 3º). Direitos do usuário: inviolabilidade da intimidade e da vida privada, sigilo das comunicações, informações claras sobre coleta e uso, consentimento expresso, não fornecimento a terceiros sem consentimento (art. 7º) | A "constituição da internet" no Brasil; aprovado depois do caso Snowden |
| **LGPD** (Lei 13.709/2018) | Disciplina o tratamento de dados pessoais por pessoas e empresas, públicas e privadas, online ou offline | Peça central da redação |
| **Lei 12.737/2012** (Carolina Dieckmann) | Tipifica a invasão de dispositivo informático (CP, art. 154-A) | Crime contra a intimidade digital |
| **Lei 13.718/2018 e Lei 13.772/2018** | Punem a divulgação de nudez/sexo sem consentimento e o registro não autorizado de intimidade sexual | Exposição íntima e vingança pornográfica |
| **Lei 15.211/2025** (ECA Digital) | Proteção de crianças e adolescentes em ambientes digitais; em vigor desde 17/03/2026 | Dados e intimidade de menores |
| **Declaração Universal dos Direitos Humanos, art. 12** | Ninguém será sujeito a interferências arbitrárias na vida privada, na família, no lar ou na correspondência | Repertório internacional |

**Marco Civil: o que lembrar do art. 19.** Originalmente, a plataforma só respondia por conteúdo de terceiros se descumprisse **ordem judicial**. Em junho de 2025, o STF (Tema 987) declarou o art. 19 **parcialmente inconstitucional** e ampliou as hipóteses de responsabilização das plataformas (por exemplo, após notificação, em certos ilícitos, e quando há falha sistêmica em conteúdos graves). Cite com cautela e sem detalhes que você não domina; a ideia-força é que *a plataforma deixou de ser mera espectadora*.

#### LGPD em 8 pontos (o mínimo que rende argumento)

1. **Fundamentos (art. 2º):** respeito à privacidade, **autodeterminação informativa**, liberdade de expressão, inviolabilidade da intimidade, desenvolvimento econômico e inovação, livre iniciativa, direitos humanos, dignidade.
2. **Atores:** **titular** (a pessoa dona dos dados), **controlador** (quem decide o tratamento), **operador** (quem trata em nome do controlador), **encarregado/DPO** (canal de comunicação) e **ANPD** (autoridade fiscalizadora).
3. **Princípios (art. 6º), os 10:** finalidade, adequação, necessidade, livre acesso, qualidade dos dados, **transparência**, **segurança**, prevenção, **não discriminação**, responsabilização e prestação de contas. *Macete: "FANLQ-TSPNR".*
4. **Bases legais (art. 7º):** o consentimento é **uma** das bases (não a única). Há também obrigação legal, execução de contrato, proteção da vida, tutela da saúde, legítimo interesse, proteção ao crédito, entre outras.
5. **Dados sensíveis (art. 11):** proteção reforçada; tratamento só em hipóteses restritas (consentimento específico e destacado, ou situações como obrigação legal e proteção da vida).
6. **Direitos do titular (art. 18):** confirmação do tratamento, acesso, correção, anonimização/bloqueio/eliminação, portabilidade, informação sobre compartilhamento, revogação do consentimento.
7. **Segurança e incidentes (arts. 46 a 48):** o agente deve adotar medidas de segurança e **comunicar** à ANPD e ao titular incidentes que possam causar risco ou dano relevante.
8. **Sanções (art. 52):** advertência, multa de até 2% do faturamento limitada a R$ 50 milhões por infração, publicização da infração, bloqueio e eliminação dos dados, entre outras.

> **Decore.** Princípios da LGPD que mais aparecem em redação: **finalidade** (usar só para o fim informado), **necessidade** (coletar o mínimo), **transparência** (informar de forma clara), **segurança** e **não discriminação**.

### 2.3 Linha do tempo para citar (com segurança)

| Ano | Marco | Por que importa |
| --- | --- | --- |
| 1890 | Warren e Brandeis, *The Right to Privacy*: "direito de ser deixado só" | Origem moderna da ideia de privacidade |
| 1983 | Tribunal Constitucional alemão reconhece a **autodeterminação informativa** (caso do Censo) | Origem do conceito que a LGPD adota |
| 2013 | Revelações de Edward Snowden sobre vigilância em massa pela NSA | Gerou debate global; impulsionou a aprovação do Marco Civil no Brasil |
| 2013 | ONU aprova resolução sobre o direito à privacidade na era digital (proposta por Brasil e Alemanha) | Repertório internacional com protagonismo brasileiro |
| 2014 | Marco Civil da Internet (Lei 12.965) | Direitos e deveres na rede |
| 2018 | Escândalo **Cambridge Analytica / Facebook** (dados de dezenas de milhões de usuários usados para perfilamento político) | Caso clássico de uso indevido de dados |
| 2018 | GDPR (UE) em aplicação; LGPD sancionada no Brasil | Padrão regulatório global |
| 2020 | STF (ADI 6387) suspende MP que obrigava operadoras a repassar dados ao IBGE e reconhece a proteção de dados como direito fundamental autônomo | Jurisprudência de peso |
| 2021 | Sanções da LGPD passam a valer; **megavazamento** de dados de dezenas de milhões de brasileiros (CPFs, dados pessoais) | Exemplo nacional de falha de segurança |
| 2022 | EC 115 inclui a proteção de dados no art. 5º (LXXIX) | Direito fundamental expresso |
| 2026 | ECA Digital em vigor | Proteção reforçada de crianças e adolescentes online |

### 2.4 Por que a intimidade está tão ameaçada hoje (os problemas)

1. **Coleta massiva e capitalismo de vigilância.** O modelo de negócios de muitas plataformas depende de coletar dados para vender publicidade direcionada. Shoshana Zuboff chama isso de *capitalismo de vigilância*: a experiência humana vira matéria-prima gratuita para prever e influenciar comportamentos.
2. **Consentimento de fachada.** O usuário "aceita" termos longos e técnicos sem ler. Existe consentimento formal, mas pouco consciente. Soma-se o uso de *dark patterns* (desenhos de interface que empurram o usuário a aceitar tudo) e a ausência de alternativa real (ou aceita, ou não usa o serviço).
3. **Inferência e perfilamento.** O risco não é só a empresa saber o que você informou; é ela **deduzir** o que você não informou (saúde, orientação sexual, renda, humor) cruzando localização, buscas, compras e horários.
4. **Vazamentos e falhas de segurança.** Dados expostos viram golpe, fraude, extorsão, roubo de identidade e perseguição. Proteger intimidade também é **segurança da informação**.
5. **Exposição por terceiros e autoexposição.** Fotos, prints, vídeos íntimos e mensagens circulam sem controle. Há ainda o chamado *paradoxo da privacidade*: as pessoas dizem se importar com privacidade, mas compartilham muito.
6. **Vigilância estatal e tecnologias biométricas.** Câmeras com reconhecimento facial, monitoramento de comunicações e bancos de dados governamentais interligados. A pergunta é sempre: há finalidade legítima, necessidade, proporcionalidade e controle?
7. **Vulneráveis: crianças e adolescentes.** Menores têm menos capacidade de compreender riscos. A LGPD exige consentimento específico dos responsáveis (art. 14) e o ECA Digital reforça a proteção.
8. **Permanência do dado.** Na internet, o que é publicado tende a ficar. Sobre o "direito ao esquecimento", o STF (Tema 786, 2021) entendeu que ele **não** é compatível com a Constituição como direito geral; excessos devem ser tratados caso a caso, com análise de abuso e de dano.

### 2.5 Argumentos prontos (com a fórmula Afirmação → Explicação → Exemplo → Consequência)

**Argumento 1: A coleta e o perfilamento transformam a intimidade em mercadoria.**

*Afirmação:* os dados pessoais se tornaram a principal moeda da economia digital.

*Explicação:* plataformas gratuitas financiam-se com publicidade segmentada, e por isso incentivam a coleta máxima de informações.

*Exemplo:* o caso Cambridge Analytica, em que dados de milhões de usuários do Facebook foram usados para montar perfis psicológicos e direcionar mensagens políticas.

*Consequência:* a pessoa perde o controle sobre quem a conhece e para que, o que fere a autodeterminação informativa.

**Argumento 2: O consentimento é formal, mas raramente é livre e informado.**

*Afirmação:* aceitar "termos de uso" não equivale a compreender o que se autoriza.

*Explicação:* os textos são extensos e técnicos; a recusa implica ficar sem o serviço; interfaces induzem ao "aceitar todos".

*Exemplo:* aplicativos que pedem acesso a contatos, câmera e localização sem relação com sua função (violação do princípio da necessidade).

*Consequência:* a LGPD exige consentimento livre, informado e inequívoco e finalidade determinada; sem isso, o tratamento pode ser invalidado.

**Argumento 3: Os vazamentos mostram que dados mal protegidos expõem a vida inteira da pessoa.**

*Afirmação:* proteger a intimidade exige segurança técnica, não só boa intenção.

*Explicação:* bases de dados concentradas atraem ataques; senhas fracas e falhas de gestão ampliam o dano.

*Exemplo:* o megavazamento de 2021, com dados pessoais de dezenas de milhões de brasileiros, alimentando golpes e fraudes.

*Consequência:* risco de roubo de identidade, extorsão e perseguição; a LGPD impõe segurança, comunicação de incidentes e responsabilização.

**Argumento 4: A vigilância estatal, sem controle, ameaça liberdades.**

*Afirmação:* a segurança pública não autoriza vigilância ilimitada.

*Explicação:* tecnologias como o reconhecimento facial permitem monitorar multidões; sem finalidade clara e controle, o risco é de abuso e de efeito inibidor sobre a liberdade.

*Exemplo:* o STF, na ADI 6387, barrou o repasse em massa de dados de usuários de telefonia ao IBGE por falta de garantias adequadas.

*Consequência:* a exigência de finalidade, necessidade e proporcionalidade é limite ao poder do Estado, não obstáculo à segurança.

**Argumento 5: Há um problema de assimetria de poder.**

*Afirmação:* o usuário individual não negocia em igualdade com grandes plataformas.

*Explicação:* quem coleta conhece o fluxo dos dados; quem fornece, não. Essa assimetria de informação e de poder justifica regulação e fiscalização.

*Exemplo:* o usuário não sabe com quem seus dados são compartilhados nem por quanto tempo são mantidos.

*Consequência:* o Estado precisa fiscalizar (ANPD), e as empresas precisam adotar transparência e *privacy by design* (privacidade desde a concepção do produto).

**Argumento 6: A intimidade é condição para outras liberdades.**

*Afirmação:* sem espaço privado, a pessoa se autocensura.

*Explicação:* quem se sabe vigiado tende a moderar opiniões, buscas e relações (efeito inibidor, ligado à ideia do Panóptico de Bentham e Foucault).

*Exemplo:* o debate gerado pelas revelações de Snowden sobre vigilância em massa.

*Consequência:* a proteção da privacidade é pressuposto da liberdade de expressão e da democracia.

### 2.6 Contra-argumentos e como rebatê-los

| Objeção comum | Como rebater |
| --- | --- |
| "Quem não deve não teme." | Privacidade não é esconder crime; é controlar quem sabe o quê. Todos têm informações legítimas que não querem expor (saúde, finanças, afetos). Além disso, dados podem ser usados contra pessoas inocentes (golpes, discriminação). |
| "O usuário aceitou os termos; o problema é dele." | Consentimento exige ser livre, informado e inequívoco (LGPD). Termos ilegíveis e opções do tipo "tudo ou nada" não cumprem esse padrão. |
| "Coleta de dados melhora serviços e gera inovação." | Verdade, e a LGPD reconhece isso (art. 2º, V). Mas inovação não dispensa finalidade, necessidade e transparência. A proteção de dados **equilibra**, não impede. |
| "A segurança pública exige monitoramento." | Segurança é legítima, mas deve respeitar legalidade, necessidade e proporcionalidade, com controle externo. O STF já vem exigindo garantias (ADI 6387). |
| "Privacidade atrapalha a liberdade de expressão." | São direitos que se limitam mutuamente: a CF protege ambos. A solução é a ponderação caso a caso, e o Marco Civil já faz esse equilíbrio. |
| "A pessoa se expõe voluntariamente nas redes." | Autoexposição não é renúncia: expor uma foto não autoriza usar dados para perfilamento ou vazamento. Além disso, há dados coletados sem que a pessoa saiba. |

### 2.7 Teses: cinco modelos com posições diferentes

> Escolha **uma** posição, mantenha-a do início ao fim e deixe claros os dois eixos que serão desenvolvidos.

1. **Tese do desequilíbrio de poder.** *Embora a internet tenha democratizado o acesso à informação, a coleta massiva de dados por plataformas e governos ocorre em um cenário de assimetria entre quem coleta e quem fornece, o que fragiliza a intimidade e exige regulação efetiva e fiscalização.* (Eixos: assimetria informacional; fiscalização insuficiente.)
2. **Tese do consentimento aparente.** *A proteção da intimidade na rede é comprometida porque o consentimento do usuário, na prática, é formal e pouco consciente, resultado de termos extensos, interfaces induzidas e falta de educação digital.* (Eixos: desenho das plataformas; letramento digital.)
3. **Tese da segurança e da responsabilização.** *A intimidade digital depende não apenas de leis, mas de segurança da informação e de responsabilização efetiva de quem trata dados, como mostram os vazamentos que expõem milhões de brasileiros.* (Eixos: falhas técnicas; sanções frouxas ou tardias.)
4. **Tese do equilíbrio de direitos.** *O desafio contemporâneo não é escolher entre privacidade e inovação, mas garantir que a inovação ocorra com finalidade, transparência e limites, de modo que a coleta de dados sirva à pessoa e não a controle.* (Eixos: lado benéfico dos dados; limites legais.)
5. **Tese da liberdade em risco.** *A vigilância digital, estatal ou privada, ameaça a intimidade e, por consequência, a própria liberdade, pois quem se sabe monitorado tende a autocensurar-se.* (Eixos: vigilância; efeito inibidor sobre a democracia.)

### 2.8 Repertório sociocultural para o tema 1

- **George Orwell, *1984*:** o "Grande Irmão", vigilância total do Estado. Serve para comparar com o monitoramento digital atual.
- **Michel Foucault / Jeremy Bentham, o Panóptico:** quem pode ser observado a qualquer momento passa a se autodisciplinar.
- **Zygmunt Bauman:** "vigilância líquida" e a sociedade em que as pessoas entregam a própria intimidade voluntariamente.
- **Byung-Chul Han, *Sociedade da Transparência*:** a exposição permanente é vendida como liberdade.
- **Shoshana Zuboff, *A Era do Capitalismo de Vigilância*.**
- **Stefano Rodotà** e **Danilo Doneda:** referências do Direito sobre proteção de dados (Doneda é um dos nomes ligados ao desenho da LGPD no Brasil).
- **Série *Black Mirror*:** várias tramas sobre exposição e monitoramento (use só se fizer sentido no argumento).
- **Documentário *Privacidade Hackeada* (Netflix):** sobre o caso Cambridge Analytica.

---

## 3. Tema 2: Igualdade algorítmica no contexto contemporâneo da internet

### 3.1 Conceitos que você precisa dominar

| Conceito | Definição em linguagem simples | Para que serve na redação |
| --- | --- | --- |
| **Algoritmo** | Sequência de instruções para resolver um problema ou executar uma tarefa | Ponto de partida |
| **Aprendizado de máquina (machine learning)** | Sistemas que "aprendem" padrões a partir de dados, em vez de serem programados regra a regra | Explicar por que o viés dos dados importa |
| **Dados de treinamento** | Conjunto de exemplos usado para o sistema aprender | Origem do viés |
| **Viés algorítmico** | Resultado sistematicamente distorcido que favorece ou prejudica certos grupos | Conceito central |
| **Discriminação algorítmica** | Tratamento desvantajoso e injustificado de pessoas ou grupos por decisão automatizada | Efeito concreto do viés |
| **Discriminação direta × indireta** | Direta: usa explicitamente a característica (raça, sexo). Indireta: critério aparentemente neutro que prejudica um grupo | Muito útil: a maioria dos casos de IA é indireta |
| **Variável proxy** | Dado "neutro" que funciona como substituto de uma característica protegida (ex.: CEP como proxy de raça ou renda) | Explicar como o viés entra sem ser programado |
| **Caixa-preta (black box)** | Sistema cujo funcionamento interno é opaco, mesmo para quem o usa | Argumento sobre transparência |
| **Explicabilidade / transparência** | Capacidade de entender e justificar por que o sistema decidiu algo | Solução |
| **Auditoria algorítmica** | Avaliação independente do sistema para detectar vieses e riscos | Solução |
| **Decisão automatizada** | Decisão tomada (ou fortemente influenciada) por sistema, sem revisão humana relevante | Tema do art. 20 da LGPD |
| **Igualdade formal × material** | Formal: todos iguais perante a lei. Material: considerar desigualdades reais para alcançar justiça efetiva | Dá profundidade jurídica |
| **Racismo algorítmico** | Reprodução ou ampliação de desigualdades raciais por sistemas digitais (termo difundido no Brasil por Tarcízio Silva) | Repertório brasileiro |
| **Bolha de filtro / câmara de eco** | Algoritmos de recomendação mostram o que reforça o que você já pensa | Igualdade de acesso à informação e polarização |
| **Retroalimentação (feedback loop)** | O resultado do algoritmo gera novos dados que reforçam o próprio viés | Mostra o efeito "bola de neve" |

> **Igualdade algorítmica não é "resultado idêntico para todos".** Um sistema pode (e deve) tratar casos diferentes de modo diferente. O ponto é que a diferença de tratamento tenha **justificativa legítima** e não decorra, direta ou indiretamente, de característica protegida (raça, gênero, origem, orientação, deficiência, religião, idade, classe social). Essa nuance costuma ser o que separa uma redação mediana de uma excelente.

### 3.2 Base legal: o que citar

| Norma | O que diz (essência) | Como usar |
| --- | --- | --- |
| **CF/88, art. 5º, caput** | Todos são iguais perante a lei, sem distinção de qualquer natureza | Princípio da igualdade como fundamento geral |
| **CF/88, art. 3º, IV** | Objetivo da República: promover o bem de todos, sem preconceitos de origem, raça, sexo, cor, idade e quaisquer outras formas de discriminação | Mostra que combater discriminação é objetivo constitucional, inclusive no digital |
| **CF/88, art. 5º, XLI** | A lei punirá qualquer discriminação atentatória dos direitos e liberdades fundamentais | Reforço da punição |
| **LGPD, art. 6º, IX** | Princípio da **não discriminação**: proibido tratar dados para fins discriminatórios ilícitos ou abusivos | A norma mais direta sobre o tema |
| **LGPD, art. 20** | Direito de **solicitar revisão de decisões tomadas unicamente com base em tratamento automatizado** que afetem seus interesses (inclusive perfis pessoal, profissional, de consumo e de crédito); o controlador deve informar de forma clara os critérios e procedimentos; se negar por segredo comercial, a ANPD pode **auditar** para verificar aspectos discriminatórios | Citação de ouro para "transparência e auditoria" |
| **LGPD, art. 38** | A ANPD pode exigir **relatório de impacto à proteção de dados pessoais** (RIPD) | Prevenção de riscos |
| **LGPD, art. 11** | Regras mais rígidas para dados sensíveis | Evitar uso discriminatório |
| **Lei 7.716/1989 e Lei 9.029/1995** | Crimes de racismo; proíbe práticas discriminatórias no acesso ao emprego | Efeito concreto em seleção por IA |
| **CDC, art. 43 e Súmula 550 do STJ** | Bancos de dados de consumidores; o *credit scoring* é lícito, mas o consumidor pode pedir esclarecimentos sobre as informações e fontes usadas | Exemplo de decisão automatizada com transparência exigível |
| **Resolução CNJ 332/2020** | Ética, transparência e governança no uso de IA no Poder Judiciário, com vedação a vieses discriminatórios (o CNJ editou norma mais recente sobre o tema em 2025; **confira** antes de citar o número) | Exemplo de regulação setorial brasileira |
| **PL 2338/2023** (Marco Legal da IA) | Aprovado no Senado em dezembro de 2024; trata de classificação de riscos, direitos das pessoas afetadas, avaliação de impacto e governança. Na Câmara, estava em tramitação; **confira o status atual antes de citar como lei** | Mostra que há movimento legislativo; nunca diga que já é lei sem conferir |
| **Regulamento da UE sobre IA (AI Act, 2024)** | Abordagem por níveis de risco; proíbe certos usos e exige requisitos para sistemas de alto risco | Comparação internacional |
| **GDPR, art. 22 (UE)** | Direito de não ser submetido a decisões exclusivamente automatizadas com efeitos relevantes | Inspirou o art. 20 da LGPD |

### 3.3 De onde vem o viés: três etapas

1. **Dados.** Dados históricos refletem uma sociedade desigual. Se um grupo foi historicamente excluído de determinadas vagas, o sistema "aprende" que aquele grupo não combina com a vaga. Dados incompletos ou pouco representativos (por exemplo, poucos rostos de pessoas negras em bases de treino) geram erros maiores para esses grupos.
2. **Desenvolvimento.** Escolhas humanas definem o que o sistema deve otimizar, quais variáveis usa e o que é "sucesso". Ao escolher variáveis (como CEP, escola, horário de acesso), pode-se incluir *proxies* de características protegidas sem querer.
3. **Uso e implementação.** Mesmo um sistema razoável pode causar danos se aplicado fora do contexto para o qual foi criado, sem supervisão humana, ou se as pessoas confiarem cegamente no resultado (viés de automação).

**O ciclo vicioso (retroalimentação):**

```
Sociedade desigual → Dados históricos desiguais → Algoritmo aprende o padrão
→ Decisões reproduzem a desigualdade → Novos dados "confirmam" o padrão → ...
```

> **Decore.** O problema raramente está no algoritmo isolado; está **no ciclo inteiro**: dados, decisões de projeto, uso e falta de controle.

### 3.4 Casos reais (use 2 ou 3 por redação)

| Caso | O que aconteceu | Lição para a tese |
| --- | --- | --- |
| **Ferramenta de recrutamento da Amazon (reportada em 2018)** | Sistema treinado com currículos históricos, majoritariamente de homens, passou a penalizar currículos com termos associados a mulheres; a empresa abandonou a ferramenta | Dados históricos reproduzem a desigualdade de gênero |
| **COMPAS (EUA, investigação da ProPublica, 2016)** | Software de previsão de reincidência criminal errava mais ao classificar réus negros como de alto risco do que réus brancos | Decisão automatizada em contexto de justiça exige transparência e controle |
| **Estudo Gender Shades (MIT, 2018; Joy Buolamwini e Timnit Gebru)** | Sistemas comerciais de reconhecimento facial tinham taxas de erro muito maiores para mulheres negras do que para homens brancos | Base de dados pouco representativa gera erro desigual |
| **Algoritmo de saúde (estudo publicado na *Science*, 2019)** | Sistema usava gastos prévios com saúde como indicador de necessidade; como pessoas negras recebiam menos atendimento, o sistema subestimava a gravidade delas | O uso de um *proxy* aparentemente neutro pode gerar discriminação |
| **Anúncios no Facebook (EUA)** | Ferramentas de segmentação permitiram excluir grupos de anúncios de moradia e emprego; a Meta firmou acordo com o governo americano em 2022 | Publicidade direcionada pode ferir a igualdade de oportunidades |
| **Google Fotos (2015)** | Sistema de rotulagem classificou erroneamente pessoas negras com um termo ofensivo | Falha na representatividade dos dados e na testagem |
| **Reconhecimento facial no Brasil** | Levantamentos da Rede de Observatórios da Segurança apontaram que a grande maioria das pessoas presas com apoio dessa tecnologia em alguns estados era negra | Risco de reforço do racismo estrutural na segurança pública |
| **Escândalo dos benefícios sociais na Holanda (*toeslagenaffaire*)** | Algoritmo e práticas de fiscalização marcaram injustamente milhares de famílias, com viés ligado à origem; o governo renunciou em 2021 | Decisão automatizada sem transparência pode destruir vidas e derrubar governos |
| **Caso ViaQuatro (São Paulo)** | Portas interativas do Metrô coletavam imagens/emoções de passageiros para publicidade, sem consentimento; a Justiça condenou a concessionária (2021) | Ponto de encontro entre **intimidade e não discriminação** |
| **Bolhas de recomendação** | Redes mostram conteúdo que reforça crenças, o que pode polarizar e restringir o acesso a pontos de vista diferentes | Igualdade no acesso à informação e à esfera pública |

> **Cuidado ao citar números.** Se não lembrar o número exato, use formulações seguras: "taxas de erro significativamente maiores", "a maioria dos casos monitorados". Número errado custa mais do que ausência de número.

### 3.5 Argumentos prontos

**Argumento 1: O algoritmo aprende com dados históricos e, por isso, tende a reproduzir desigualdades.**

*Afirmação:* sistemas automatizados não são neutros.

*Explicação:* são treinados com dados produzidos por uma sociedade desigual e, sem correção, perpetuam esses padrões.

*Exemplo:* a ferramenta de recrutamento da Amazon, que penalizava currículos de mulheres.

*Consequência:* a desigualdade ganha aparência técnica e objetiva, o que a torna mais difícil de contestar.

**Argumento 2: A opacidade impede a contestação.**

*Afirmação:* quem sofre a decisão muitas vezes não sabe que ela foi automatizada nem por quê.

*Explicação:* o funcionamento é tratado como segredo comercial ou é complexo demais ("caixa-preta").

*Exemplo:* decisões sobre crédito, seleção de candidatos ou risco criminal tomadas por pontuações que o interessado não consegue conhecer.

*Consequência:* sem transparência não há ampla defesa nem correção; por isso o art. 20 da LGPD garante o direito à revisão e permite à ANPD auditar.

**Argumento 3: A discriminação pode ser indireta, via variáveis aparentemente neutras.**

*Afirmação:* não é preciso que o sistema use "raça" para discriminar por raça.

*Explicação:* CEP, escola, histórico de navegação e consumo podem funcionar como *proxies*.

*Exemplo:* o algoritmo de saúde que usava custo prévio como medida de necessidade e subestimava pacientes negros.

*Consequência:* a análise precisa ser de **resultado** (quem é afetado), não só de intenção.

**Argumento 4: Algoritmos de recomendação podem desigualar o acesso à informação e às oportunidades.**

*Afirmação:* o que cada pessoa vê online é filtrado.

*Explicação:* a lógica de engajamento privilegia o que prende a atenção, formando bolhas; a segmentação de anúncios pode excluir grupos.

*Exemplo:* exclusão de grupos em anúncios de moradia e emprego; bolhas de polarização política.

*Consequência:* risco para a igualdade de oportunidades e para o debate democrático.

**Argumento 5: A responsabilidade não pode se diluir ("foi o algoritmo").**

*Afirmação:* sistemas não têm responsabilidade jurídica; pessoas e empresas têm.

*Explicação:* quem desenvolve, treina e utiliza o sistema decide sobre dados e finalidades, e deve responder pelos danos (princípio da responsabilização e prestação de contas, LGPD, art. 6º, X).

*Exemplo:* o caso holandês, em que o erro sistêmico teve consequências políticas e financeiras graves.

*Consequência:* a exigência de auditoria, relatórios de impacto e supervisão humana nos casos de maior risco.

**Argumento 6: Igualdade material exige olhar para desigualdades reais.**

*Afirmação:* tratar todos "igualmente" pode aprofundar desigualdades se o ponto de partida é desigual.

*Explicação:* sistemas "cegos" a diferenças podem punir quem já é vulnerável.

*Exemplo:* o reconhecimento facial com mais erros para determinados grupos, aplicado em segurança pública.

*Consequência:* é preciso testar o desempenho por grupo e corrigir antes do uso.

### 3.6 Contra-argumentos e como rebatê-los

| Objeção comum | Como rebater |
| --- | --- |
| "Algoritmo é matemática, logo é neutro." | O código é neutro; o sistema não é. Escolhas humanas definem dados, variáveis e metas, e os dados de treino refletem a sociedade. |
| "Algoritmos são menos enviesados do que humanos." | Podem ser, quando bem projetados. Mas reproduzem viés em **escala** e com aparência de objetividade, o que dificulta a contestação. A solução é auditar e corrigir, não renunciar à tecnologia. |
| "Regulamentar freia a inovação." | Regras claras dão segurança jurídica e confiança. A regulação por **níveis de risco** (como na UE) protege sem proibir a inovação. |
| "Segredo industrial impede abrir o algoritmo." | A LGPD (art. 20) admite o segredo comercial, mas permite à ANPD auditar. Transparência pode ser feita sem expor o código inteiro: critérios, impactos e testes. |
| "Personalizar é diferente de discriminar." | Correto, e vale ressaltar na redação. A personalização é legítima; vira discriminação quando gera **desvantagem injustificada** com base em característica protegida, direta ou indiretamente. |
| "Se houver revisão humana, o problema acaba." | Não necessariamente: humanos tendem a confiar demais na máquina (viés de automação). A revisão precisa ser **significativa**, com autonomia e informação. |

### 3.7 Teses: cinco modelos com posições diferentes

1. **Tese do viés herdado.** *Embora os algoritmos tornem os serviços digitais mais eficientes e personalizados, sua dependência de dados históricos faz com que reproduzam desigualdades sociais, o que torna indispensáveis a diversidade nos dados e a auditoria dos sistemas.* (Eixos: dados enviesados; falta de auditoria.)
2. **Tese da opacidade.** *A igualdade algorítmica é ameaçada pela opacidade dos sistemas, pois, sem transparência e possibilidade de contestação, o cidadão não consegue identificar nem corrigir decisões discriminatórias.* (Eixos: caixa-preta; direito à revisão.)
3. **Tese da discriminação indireta.** *A discriminação digital raramente é explícita; ela se manifesta por variáveis aparentemente neutras, exigindo que a proteção da igualdade avalie os efeitos dos sistemas sobre grupos vulneráveis, e não apenas as intenções de quem os projeta.* (Eixos: *proxies*; análise de impacto.)
4. **Tese da responsabilidade compartilhada.** *Garantir a igualdade na era dos algoritmos exige responsabilidade compartilhada: o Estado deve regular e fiscalizar, as empresas devem projetar sistemas justos, e a sociedade deve desenvolver letramento digital.* (Eixos: papel do Estado; papel das empresas.)
5. **Tese da igualdade material.** *Tratar todos de forma idêntica pelo código não basta: sem considerar as desigualdades reais da sociedade brasileira, a automação aprofunda exclusões históricas e fere o princípio constitucional da igualdade material.* (Eixos: desigualdade estrutural; dever de correção.)

### 3.8 Repertório sociocultural para o tema 2

- **Cathy O'Neil, *Algoritmos de Destruição em Massa* (*Weapons of Math Destruction*):** modelos opacos, em larga escala e com efeitos danosos.
- **Frank Pasquale, *The Black Box Society*:** a opacidade de algoritmos que decidem sobre crédito, reputação e informação.
- **Safiya Noble, *Algorithms of Oppression*:** buscadores e estereótipos.
- **Virginia Eubanks, *Automating Inequality*:** automação em serviços sociais prejudicando os mais pobres.
- **Ruha Benjamin, *Race After Technology*:** o conceito de "New Jim Code" (tecnologias que reproduzem hierarquias raciais).
- **Tarcízio Silva:** pesquisador brasileiro do racismo algorítmico.
- **Silvio Almeida, *Racismo Estrutural*:** o racismo como parte da organização social, o que ajuda a explicar por que os dados refletem desigualdades.
- **Eli Pariser, *O Filtro Invisível*:** a "bolha de filtro".
- **Documentário *Coded Bias* (Netflix):** a pesquisa de Joy Buolamwini sobre reconhecimento facial.
- **Aristóteles / Rui Barbosa:** "tratar igualmente os iguais e desigualmente os desiguais, na medida de sua desigualdade" (ideia clássica de igualdade material, citação célebre em *Oração aos Moços*).

---

## 4. Ponte entre os temas (para enunciados que misturam assuntos)

**Como a privacidade alimenta a discriminação:** os dados coletados (tema 1) são a matéria-prima dos perfis que os algoritmos usam para classificar pessoas (tema 2). Quanto mais dados e menos transparência, maior o risco de decisões injustas e invisíveis.

**Teses de interseção (prontas para usar):**

1. *A coleta indiscriminada de dados e a opacidade dos algoritmos formam um mesmo problema: o poder de classificar pessoas sem que elas saibam, possam contestar ou escapar, o que ameaça simultaneamente a intimidade e a igualdade.*
2. *A LGPD oferece o ponto de encontro entre os dois temas ao unir princípios como finalidade, transparência e não discriminação; sua efetividade, porém, depende de fiscalização da ANPD e de conscientização dos usuários.*
3. *Proteger a intimidade digital é condição para garantir a igualdade algorítmica: dados minimizados e bem controlados reduzem o risco de perfis discriminatórios.*

**Quadro de comparação (para memorizar):**

| Tema | Palavra-chave | Pergunta central | Principal problema | Soluções clássicas |
| --- | --- | --- | --- | --- |
| Intimidade na internet | Privacidade | O que pode ser feito com meus dados? | Coleta, exposição e vazamento | Transparência, consentimento real, segurança, fiscalização |
| Igualdade algorítmica | Não discriminação | Como o sistema trata grupos diferentes? | Viés, opacidade, discriminação indireta | Auditoria, explicabilidade, dados representativos, revisão humana |

---

## 5. Modelo coringa

### 5.1 Esqueleto de 4 parágrafos (preencha os colchetes)

**Parágrafo 1: Introdução (5 a 7 linhas)**

1. **Contextualização:** [fato histórico, dado, citação, referência cultural ou constitucional ligados ao tema].
2. **Problematização:** [mostrar que o avanço digital trouxe benefícios, **mas** criou um problema: ...].
3. **Tese + eixos:** [posição clara] + [argumento 1] + [argumento 2].

**Parágrafo 2: Desenvolvimento 1 (7 a 9 linhas)**

- **Tópico frasal:** [primeiro eixo da tese].
- **Argumento:** [explicação com lógica].
- **Repertório:** [lei, caso, autor ou dado].
- **Fechamento:** [consequência e retomada da tese].

**Parágrafo 3: Desenvolvimento 2 (7 a 9 linhas)**

- **Tópico frasal:** [segundo eixo, com conectivo de adição ou contraste em relação ao parágrafo anterior].
- **Argumento + repertório + consequência**, na mesma lógica.

**Parágrafo 4: Conclusão (5 a 7 linhas)**

- **Retomada da tese** em uma frase.
- **Proposta de intervenção** com os 5 elementos: **quem** + **ação** + **meio** + **finalidade** + **detalhamento**.
- **Fechamento** opcional: retomar o repertório da introdução.

### 5.2 Seis fórmulas de abertura

1. **Constitucional/legal:** "A Constituição Federal de 1988 assegura, em seu artigo 5º, [direito]. No entanto, [problema digital] evidencia que [o princípio ainda não é plenamente efetivo]."
2. **Histórica:** "Desde [momento histórico], [tema] passou por transformações. Na era digital, contudo, [novo desafio]."
3. **Literária/filosófica:** "Na obra [*1984*], George Orwell retrata [vigilância total]. Fora da ficção, [paralelo com a internet atual]."
4. **Dados/fatos:** "Em [ano], o caso [Cambridge Analytica / vazamento / COMPAS] revelou que [fato]. Esse episódio demonstra que [tese]."
5. **Conceitual:** "A ideia de [autodeterminação informativa / igualdade material] pressupõe que [definição]. Contudo, [obstáculo atual]."
6. **Contraste:** "Se, por um lado, a internet [benefício], por outro, [problema], o que torna necessário [posição]."

### 5.3 Fórmulas de tese (encaixe tema + problema + solução)

- "Embora [benefício da tecnologia], [problema] persiste em razão de [causa 1] e de [causa 2]."
- "O desafio de [tema] decorre, sobretudo, de [causa 1] e de [causa 2], o que exige [solução geral]."
- "A efetivação de [direito] no ambiente digital é comprometida por [obstáculo 1], bem como por [obstáculo 2]."
- "Apesar dos avanços normativos, como [LGPD / Marco Civil], a garantia de [direito] ainda esbarra em [obstáculo 1] e [obstáculo 2]."

### 5.4 Fórmula do parágrafo de desenvolvimento (T-A-R-C)

| Etapa | O que escrever | Exemplo de abertura |
| --- | --- | --- |
| **T**ópico frasal | A ideia do parágrafo em 1 frase | "Em primeiro lugar, a coleta massiva de dados..." |
| **A**rgumentação | Explique **por que** isso é um problema | "Isso ocorre porque o modelo de negócios..." |
| **R**epertório | Prove com lei, caso, autor ou dado | "Nesse sentido, o caso Cambridge Analytica..." |
| **C**onsequência/conexão | Mostre o efeito e volte à tese | "Dessa forma, a intimidade é fragilizada, o que..." |

### 5.5 Proposta de intervenção coringa

**Fórmula:** *[QUEM] deve [AÇÃO], por meio de [MEIO], a fim de [FINALIDADE]. [DETALHAMENTO]*

| Quem | Ação | Meio | Finalidade |
| --- | --- | --- | --- |
| **ANPD / Poder Público** | Ampliar a fiscalização e aplicar as sanções da LGPD | Auditorias periódicas e publicização de infrações | Coibir o uso abusivo de dados e práticas discriminatórias |
| **Poder Legislativo** | Aprovar e aperfeiçoar o marco regulatório da IA | Regras de transparência, avaliação de impacto e responsabilização por nível de risco | Garantir segurança jurídica e proteção de direitos |
| **Empresas de tecnologia** | Adotar *privacy by design* e programas de integridade | Termos claros, opções de configuração e testes de viés antes do uso | Reduzir riscos à intimidade e à igualdade |
| **Ministério da Educação / escolas** | Incluir educação digital no currículo | Aulas sobre privacidade, segurança e pensamento crítico sobre algoritmos | Formar usuários conscientes de seus direitos |
| **Mídia e campanhas públicas** | Informar a população | Campanhas sobre direitos do titular e golpes digitais | Aumentar a participação cidadã e a prevenção |
| **Poder Judiciário** | Aplicar com rigor a LGPD e o Marco Civil | Decisões que garantam reparação e criem precedentes | Responsabilizar quem viola direitos |
| **Desenvolvedores e equipes de dados** | Usar bases de dados representativas e documentadas | Testes por grupo, revisão humana significativa e registro de decisões | Evitar vieses e permitir contestação |
| **Governo e Ministério Público** | Controlar o uso estatal de tecnologias de vigilância | Relatórios de impacto, controle externo e limites legais ao reconhecimento facial | Conciliar segurança pública e direitos fundamentais |

**Modelo pronto de conclusão:**

> "Portanto, [retomar a tese]. Para superar esse cenário, [o Poder Público/a ANPD], na qualidade de [fiscalizador/regulador], deve [ação], por meio de [meio], a fim de [finalidade]. Ademais, [as empresas de tecnologia] devem [ação], de modo que [consequência positiva]. Assim, será possível [fechamento retomando a introdução]."

### 5.6 Conectivos por função

| Função | Opções |
| --- | --- |
| **Adição** | Além disso; ademais; outrossim; soma-se a isso; não bastasse |
| **Oposição/contraste** | No entanto; contudo; todavia; entretanto; em contrapartida; embora; ainda que |
| **Causa** | Visto que; uma vez que; haja vista; em razão de; devido a |
| **Consequência** | Dessa forma; por conseguinte; assim; logo; em decorrência disso |
| **Exemplificação** | Nesse sentido; a exemplo de; como evidencia; tal como |
| **Conclusão** | Portanto; diante do exposto; em suma; por fim; dessa maneira |
| **Ênfase** | Sobretudo; principalmente; especialmente; vale ressaltar que |

### 5.7 Repertório coringa (serve para quase qualquer tema digital)

- **Constituição (arts. 1º, III; 3º, IV; 5º, caput, X, XII e LXXIX):** dignidade, igualdade, intimidade e dados.
- **Marco Civil da Internet** e **LGPD**: as duas leis centrais.
- **DUDH, art. 12:** proteção contra interferências arbitrárias na vida privada.
- **Zygmunt Bauman:** modernidade líquida e vigilância líquida.
- **Byung-Chul Han:** sociedade da transparência, da exposição e do desempenho.
- **Michel Foucault:** o Panóptico, a vigilância como forma de poder.
- **Hannah Arendt:** distinção entre esfera pública e privada.
- **George Orwell, *1984*** e **Aldous Huxley, *Admirável Mundo Novo*:** controle por vigilância e por entretenimento.
- **Shoshana Zuboff:** capitalismo de vigilância.
- **Cambridge Analytica, Snowden, megavazamento de 2021:** casos de dados.
- **Amazon, COMPAS, Gender Shades:** casos de algoritmos.

### 5.8 Duas redações-modelo (para ver o esqueleto funcionando)

> Use como **estudo de estrutura**. Na prova, reescreva com suas palavras e seu repertório.

#### Modelo A: Direito à intimidade no contexto contemporâneo da internet

A Constituição Federal de 1988 assegura, em seu artigo 5º, a inviolabilidade da intimidade e da vida privada, e a Emenda Constitucional 115/2022 elevou a proteção de dados pessoais à condição de direito fundamental. Contudo, em uma sociedade na qual cada clique deixa um rastro, a efetividade desses direitos esbarra em obstáculos novos. Nesse cenário, a intimidade na internet é fragilizada pela coleta massiva de dados por parte de plataformas e governos e pelo caráter meramente formal do consentimento dos usuários.

Em primeiro lugar, a lógica econômica de boa parte das plataformas transforma dados pessoais em mercadoria. Como serviços aparentemente gratuitos são financiados por publicidade segmentada, há um incentivo à coleta máxima de informações e à construção de perfis detalhados. O caso Cambridge Analytica, no qual dados de milhões de usuários foram utilizados para direcionar mensagens políticas, ilustra como informações privadas podem ser empregadas para fins que o titular jamais imaginou. Dessa forma, a autodeterminação informativa, fundamento da Lei Geral de Proteção de Dados, é esvaziada.

Ademais, o consentimento, apresentado como garantia do usuário, é frequentemente aparente. Termos longos e técnicos, interfaces que induzem ao "aceitar tudo" e a ausência de alternativa real de uso fazem com que a autorização seja concedida sem compreensão. Soma-se a isso a fragilidade da segurança, evidenciada por vazamentos que expõem dados de milhões de brasileiros e alimentam golpes e fraudes. Assim, a mera existência da lei não impede que a intimidade seja violada na prática.

Portanto, é necessário reforçar a proteção da intimidade digital. A Autoridade Nacional de Proteção de Dados deve ampliar a fiscalização e a aplicação das sanções previstas na LGPD, por meio de auditorias periódicas e da publicização das infrações, a fim de coibir o uso abusivo de dados. Paralelamente, as empresas devem adotar a privacidade desde a concepção de seus produtos, com termos claros e opções de configuração, enquanto as escolas devem incluir a educação digital no currículo. Dessa maneira, a intimidade deixará de ser moeda de troca para voltar a ser um direito exercido.

#### Modelo B: Igualdade algorítmica no contexto contemporâneo da internet

O princípio da igualdade, consagrado no artigo 5º da Constituição Federal, foi pensado para um mundo em que decisões eram tomadas por pessoas. Hoje, porém, sistemas automatizados decidem o que cada indivíduo vê na internet, se recebe crédito e até quem é considerado suspeito. Embora esses algoritmos tornem os serviços mais eficientes, sua dependência de dados históricos e sua falta de transparência fazem com que reproduzam desigualdades, exigindo auditoria e controle.

Primeiramente, os algoritmos aprendem com dados produzidos por uma sociedade desigual e, por isso, tendem a perpetuar seus preconceitos. Em 2018, noticiou-se que uma ferramenta de recrutamento da Amazon, treinada com currículos de um histórico majoritariamente masculino, passou a penalizar candidatas mulheres. Esse exemplo evidencia que a discriminação não precisa ser programada: basta que o sistema aprenda o padrão. Como resultado, a desigualdade ganha aparência técnica e objetiva, o que dificulta sua contestação.

Em segundo lugar, a opacidade dos sistemas impede que as pessoas afetadas identifiquem e corrijam decisões injustas. Quando um cidadão tem o crédito negado ou é classificado como risco por uma pontuação que desconhece, a ampla defesa é comprometida. Embora o artigo 20 da LGPD garanta o direito à revisão de decisões automatizadas e permita à ANPD realizar auditorias, a aplicação desse dispositivo ainda depende de maior fiscalização e de regras mais claras sobre o uso de inteligência artificial.

Diante disso, cabe ao Poder Legislativo aprovar um marco regulatório da inteligência artificial com avaliação de impacto, transparência e responsabilização proporcionais ao risco, de modo a garantir segurança jurídica e proteção de direitos. Cabe, ainda, às empresas desenvolvedoras testar seus sistemas por grupos populacionais e manter revisão humana significativa, a fim de evitar vieses. Assim, a tecnologia poderá ampliar oportunidades sem aprofundar as exclusões históricas da sociedade brasileira.

### 5.9 Checklist antes de entregar (erros que derrubam nota)

- [ ] A **tese** está explícita na introdução e tem **dois eixos** claros?
- [ ] Cada desenvolvimento tem **repertório** (lei, caso, autor ou dado) e **consequência**?
- [ ] Não confundi **intimidade/privacidade** com **proteção de dados** nem **igualdade formal** com **material**?
- [ ] Citei lei com **número e artigo corretos**? (Na dúvida, cite só "a LGPD" ou "a Constituição", sem número de artigo.)
- [ ] Evitei afirmar que o PL 2338 "já é lei"?
- [ ] A conclusão tem proposta com **quem, ação, meio, finalidade e detalhamento**?
- [ ] Mantive **posição** do início ao fim, sem "por um lado... por outro" sem conclusão?
- [ ] Evitei generalizações como "todos", "ninguém", "sempre"?
- [ ] Reconheci o **lado positivo** da tecnologia antes de criticar? (Mostra equilíbrio e maturidade.)
- [ ] Revisei **concordância, crase e vírgulas** nos conectivos?

---

## 6. Parte de Informática e Legislação: o essencial em um quadro

### 6.1 Conceitos técnicos que sustentam os argumentos

| Termo | Em uma frase | Onde aparece |
| --- | --- | --- |
| **Tríade CID** (Confidencialidade, Integridade, Disponibilidade) | Os três pilares da segurança da informação | Argumento sobre vazamentos |
| **Criptografia** | Codifica dados para que só quem tem a chave os leia | Solução técnica de proteção |
| **Autenticação em dois fatores (2FA/MFA)** | Exige duas provas de identidade para acessar uma conta | Prevenção a invasões |
| **Anonimização × pseudonimização** | Anonimizar impede a identificação; pseudonimizar a dificulta, mas ainda é possível reverter com informação adicional | Tema da LGPD |
| **Cookies** | Arquivos que registram a navegação, usados para personalizar e rastrear | Perfilamento |
| **Privacy by design / by default** | Privacidade embutida desde a concepção e ativada por padrão | Solução para empresas |
| **Minimização de dados** | Coletar apenas o necessário | Princípio da necessidade |
| **RIPD** | Relatório de impacto à proteção de dados pessoais | Prevenção de riscos |
| **Engenharia social / phishing** | Golpes que enganam a pessoa para obter dados | Vazamentos e golpes |
| **Inteligência artificial / aprendizado de máquina** | Sistemas que aprendem padrões em dados | Tema 2 |
| **Dados enviesados × amostra representativa** | Se a base não representa a população, o sistema erra mais para certos grupos | Tema 2 |

### 6.2 Cola das leis em uma página

| Quando o tema for... | Cite principalmente... |
| --- | --- |
| Intimidade, vida privada | CF art. 5º, X; Marco Civil art. 7º; LGPD |
| Proteção de dados | CF art. 5º, LXXIX; LGPD arts. 2º, 6º, 7º, 18 |
| Consentimento | LGPD art. 5º, XII, e art. 7º; Marco Civil art. 7º, IX |
| Dados sensíveis, saúde, biometria | LGPD arts. 5º, II, e 11 |
| Crianças e adolescentes | LGPD art. 14; ECA Digital (Lei 15.211/2025) |
| Vazamentos, segurança | LGPD arts. 46 a 48 e 52; Lei 12.737/2012 |
| Responsabilidade de plataformas | Marco Civil arts. 19 e 21; STF, Tema 987 |
| Discriminação, igualdade | CF arts. 3º, IV, e 5º, caput; LGPD art. 6º, IX |
| Decisões automatizadas e IA | LGPD art. 20; PL 2338/2023 (tramitação); Resolução CNJ 332/2020 |
| Crédito e scoring | CDC art. 43; Súmula 550 do STJ |
| Estado e vigilância | STF ADI 6387; princípios de finalidade, necessidade e proporcionalidade |

---

## 7. Autoteste (responda em voz alta e confira)

1. **Qual a diferença entre intimidade e vida privada?** *Intimidade é a esfera mais interna (segredos, saúde, sexualidade, convicções); vida privada abrange relações familiares e sociais restritas. Ambas estão no art. 5º, X.*
2. **Por que a proteção de dados virou direito fundamental autônomo?** *Porque o tratamento de dados em massa permite controlar e discriminar pessoas mesmo sem expor "segredos" tradicionais; foi reconhecido pelo STF (ADI 6387) e inserido na CF pela EC 115/2022 (art. 5º, LXXIX).*
3. **Cite três princípios da LGPD relevantes para ambos os temas.** *Finalidade, transparência e não discriminação.*
4. **O consentimento é a única base legal da LGPD?** *Não. O art. 7º traz diversas bases, como obrigação legal, execução de contrato e legítimo interesse.*
5. **O que é autodeterminação informativa?** *Poder de a pessoa decidir sobre o uso de seus dados.*
6. **O que é viés algorítmico e de onde vem?** *Distorção sistemática do resultado; vem dos dados, das escolhas de projeto e do uso do sistema.*
7. **O que é variável proxy?** *Dado aparentemente neutro que substitui uma característica protegida (ex.: CEP).*
8. **Qual artigo da LGPD trata de decisões automatizadas?** *O art. 20 (direito à revisão e à informação sobre critérios; auditoria pela ANPD).*
9. **Igualdade algorítmica significa resultados idênticos?** *Não; significa que as diferenças de tratamento sejam justificáveis e não discriminatórias.*
10. **Cite dois casos reais de discriminação algorítmica.** *Recrutamento da Amazon e COMPAS (ou Gender Shades, anúncios do Facebook, caso holandês).*
11. **Quem deve fiscalizar o cumprimento da LGPD?** *A ANPD, sem prejuízo do Judiciário, do Ministério Público e dos órgãos de defesa do consumidor.*
12. **O que o STF decidiu em 2025 sobre o art. 19 do Marco Civil?** *Declarou-o parcialmente inconstitucional e ampliou as hipóteses de responsabilidade das plataformas (Tema 987).*

---

## 8. Observações finais e fontes de conferência

> **Verifique antes de citar na prova.** Os fatos e as datas deste guia foram revisados, mas legislação e jurisprudência mudam. Dois pontos pedem conferência: o **status do PL 2338/2023** (Marco Legal da IA), que dependia de votação na Câmara dos Deputados, e os **detalhes da tese do STF no Tema 987**. Se tiver dúvida, escreva de forma genérica ("o Supremo ampliou a responsabilização das plataformas") em vez de entrar em detalhes.

**Se a prova for de concurso ou tiver edital específico**, envie o edital ou a lista de normas cobradas, e adapto o material (por exemplo, com foco em artigos específicos, em questões de múltipla escolha ou em legislação da sua carreira).

**Fontes de consulta rápida:**

- Constituição Federal de 1988 (art. 3º, 5º e 22): planalto.gov.br
- Lei 13.709/2018 (LGPD); Lei 12.965/2014 (Marco Civil); Lei 15.211/2025 (ECA Digital): planalto.gov.br
- Autoridade Nacional de Proteção de Dados (ANPD): gov.br/anpd
- Tema 987 do STF e ADI 6387: portal.stf.jus.br
- Tramitação do PL 2338/2023: camara.leg.br
