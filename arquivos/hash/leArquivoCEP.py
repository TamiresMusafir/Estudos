
import struct
import codecs
import sys

# Caminho do arquivo que contém os registros de CEP
fileName = "data/cep.dat"

# Formato dos registros armazenados no arquivo
# Cada registro possui 300 bytes, divididos em 7 campos
cepFormat = "72s72s72s72s2s8s2s"

# Codificação utilizada para interpretar os textos do arquivo
encoding = "latin1"

# Calcula o tamanho de cada registro em bytes (300 bytes)
recordSize = struct.calcsize(cepFormat)

# Verifica se o CEP foi informado como argumento no terminal
if len(sys.argv) >= 2:
    cepProcurado = sys.argv[1]
else:
    # Caso contrário, solicita o CEP ao usuário
    cepProcurado = input("Entre com o cep: ")

# Converte o CEP digitado de texto para bytes,
# permitindo compará-lo com os dados binários do arquivo
cepProcurado = cepProcurado.encode('latin1')

# Abre o arquivo em modo de leitura binária
f = open(fileName, "rb")

# Inicia a busca sequencial: percorre o arquivo registro por registro
while True:

    # Lê o próximo registro (300 bytes)
    line = f.read(recordSize)

    # Verifica se chegou ao final do arquivo (EOF)
    if line == b"":
        break

    # Separa os 300 bytes nos 7 campos definidos em cepFormat
    record = struct.unpack(cepFormat, line)

    # Compara o CEP do registro (posição 5) com o CEP procurado
    if record[5] == cepProcurado:

        # Se encontrar, decodifica os campos de bytes para texto
        # e imprime as informações do endereço
        print(codecs.decode(record[0], encoding))  # Logradouro
        print(codecs.decode(record[1], encoding))  # Bairro
        print(codecs.decode(record[2], encoding))  # Cidade
        print(codecs.decode(record[4], encoding))  # UF

# Fecha o arquivo após terminar a busca
f.close()
