import sys
import matplotlib.pyplot as plt     # biblioteca de gráficos

# Lê a saída do frequencias.c e desenha o histograma: eixo x = valor do byte (0 a 255),
# eixo y = quantas vezes ele aparece. Barras muito desiguais = Huffman comprime bem.
# Uso:  python3 histograma.py resultado.txt

# Recebe o arquivo de resultado como argumento
nome_arquivo = sys.argv[1]          # sys.argv[0] é o nome do script; [1] é o primeiro argumento

valores = []                        # eixo x: o valor do byte
frequencias = []                    # eixo y: a frequência dele

# Abre e lê o arquivo gerado pelo programa C
with open(nome_arquivo, "r") as arquivo:     # "with" fecha o arquivo sozinho no fim
    for linha in arquivo:

        # Ignora a linha do total de bytes
        # (só serve linha "NÚMERO: NÚMERO"; "Total de impressões: ..." não começa com dígito)
        if ":" in linha and linha.split(":")[0].strip().isdigit():

            valor, frequencia = linha.strip().split(":")   # separa "65: 120" em "65" e " 120"

            valores.append(int(valor))               # int() converte o texto em número
            frequencias.append(int(frequencia))

# Cria o histograma
plt.figure(figsize=(14, 6))         # tamanho da figura, em polegadas (largura, altura)

plt.bar(valores, frequencias, width=1.0, color="steelblue")   # width=1.0: barras coladas, 1 por valor

plt.title(f"Histograma - {nome_arquivo}")
plt.xlabel("Valor do byte (0 a 255)")
plt.ylabel("Quantidade de ocorrências")

plt.xlim(0, 255)                    # limita o eixo x ao intervalo dos bytes
plt.grid(axis="y", alpha=0.3)       # linhas de grade horizontais, bem fraquinhas

plt.tight_layout()                  # ajusta as margens para nada ficar cortado

# Salva o gráfico como imagem
nome_saida = "histograma_" + nome_arquivo.replace(".txt", ".png")   # resultado.txt -> histograma_resultado.png
plt.savefig(nome_saida)

print(f"Histograma salvo em: {nome_saida}")
