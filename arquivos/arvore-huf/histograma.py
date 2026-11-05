
import sys
import matplotlib.pyplot as plt

# Recebe o arquivo de resultado como argumento
nome_arquivo = sys.argv[1]

valores = []
frequencias = []

# Abre e lê o arquivo gerado pelo programa C
with open(nome_arquivo, "r") as arquivo:
    for linha in arquivo:

        # Ignora a linha do total de bytes
        if ":" in linha and linha.split(":")[0].strip().isdigit():

            valor, frequencia = linha.strip().split(":")

            valores.append(int(valor))
            frequencias.append(int(frequencia))

# Cria o histograma
plt.figure(figsize=(14, 6))

plt.bar(valores, frequencias, width=1.0, color="steelblue")

plt.title(f"Histograma - {nome_arquivo}")
plt.xlabel("Valor do byte (0 a 255)")
plt.ylabel("Quantidade de ocorrências")

plt.xlim(0, 255)
plt.grid(axis="y", alpha=0.3)

plt.tight_layout()

# Salva o gráfico como imagem
nome_saida = "histograma_" + nome_arquivo.replace(".txt", ".png")
plt.savefig(nome_saida)

print(f"Histograma salvo em: {nome_saida}")
