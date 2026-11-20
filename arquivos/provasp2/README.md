# P2 — Organização de Estruturas de Arquivos

Matéria da P2: **árvore B/B+, hash e árvore de Huffman**. O que é de P1 (arquivos em C, `fseek`, busca binária, índice, ordenação externa) está nas outras pastas e no [README geral](../README.md).

## Índice

- [Provas desta pasta](#provas-desta-pasta)
- [Mapa da prova P2 2026.1: questão → onde estudar](#mapa-da-prova-p2-20261-questão--onde-estudar)
- [Guias de estudo](#guias-de-estudo)

## Provas desta pasta

| Arquivo | O que é |
|---|---|
| [`p2-2026.1.pdf`](p2-2026.1.pdf) | P2 2026.1 (Prof. Renato Mauro), prova de base: 4 questões, 6,0 pontos |
| [`p2-2023.1.pdf`](p2-2023.1.pdf) | P2 2023.1, usada nos exercícios resolvidos dos guias |

## Mapa da prova P2 2026.1: questão → onde estudar

| Questão | Valor | Assunto | Onde estudar |
|---|---|---|---|
| 1 | 1,0 | Construir a árvore de Huffman (A–H) e dar o código de cada símbolo | [Huffman, seção 11](../arvore-huf/README.md#11-exercício-resolvido-p2-questão-1) |
| 2 | 1,0 | Tabela de hash com 11 posições, encadeamento externo, colisões e maior lista | [Hash, seção 8](../hash/README.md#8-exemplo-completo-p2-questão-2) |
| 3(a) | 0,3 | Diferença entre árvore B e B+ | [B/B+, seção 14](../arvores/README.md#14-teoria-cobrada-na-p2-respostas-modelo) |
| 3(b) | 0,3 | Hash como índice: igualdade x intervalo x ordem | [B/B+, seção 14](../arvores/README.md#14-teoria-cobrada-na-p2-respostas-modelo) e [Hash, seção 11](../hash/README.md#11-hash-x-b-x-busca-sequencial) |
| 3(c) | 0,3 | Por que usar heap no Huffman | [Huffman, seção 9](../arvore-huf/README.md#9-o-heap) |
| 3(d) | 0,3 | Como o split garante 50% de ocupação | [B/B+, seção 14](../arvores/README.md#14-teoria-cobrada-na-p2-respostas-modelo) |
| 4 | 2,8 | Código: indexar arquivo, buscar por chave, diferença entre arquivos, custo (árvore B pronta) | [B/B+, seção 15](../arvores/README.md#15-código-da-p2-usar-a-árvore-b-como-caixa-preta) |

## Guias de estudo

| Pasta | Conteúdo |
|---|---|
| [`../arvores/`](../arvores/README.md) | Guia de árvore B e B+, mais `ArvoreB.c` e `ArboreB.h` |
| [`../hash/`](../hash/README.md) | Guia de hash e os scripts do trabalho dos CEPs |
| [`../arvore-huf/`](../arvore-huf/README.md) | Guia de Huffman, contador de bytes e histograma |
