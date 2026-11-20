# BUSCA SEQUENCIAL DE CEP
#
# Percorre o arquivo cep.dat registro por registro,
# comparando o CEP de cada registro com o CEP procurado.
# Não utiliza Hash nem índice auxiliar.

# BIBLIOTECAS:
import struct   # Interpreta dados binários e separa os campos dos registros.
import codecs   # Converte bytes em texto (decode).
import sys      # Permite receber o CEP como argumento pelo terminal.


# CONFIGURAÇÕES DO ARQUIVO:
fileName = "data/cep.dat"             # Caminho do arquivo de CEPs.
cepFormat = "72s72s72s72s2s8s2s"     # Formato dos 7 campos de cada registro.
encoding = "latin1"                   # Codificação dos textos armazenados.

recordSize = struct.calcsize(cepFormat)  # Calcula o tamanho de cada registro (300 bytes).


# ENTRADA DO CEP:
if len(sys.argv) >= 2:
    cepProcurado = sys.argv[1]  # Recebe o CEP informado pelo terminal.
else:
    cepProcurado = input("Entre com o cep: ")  # Solicita o CEP ao usuário.

# Converte o CEP de texto para bytes, permitindo compará-lo
# com o CEP armazenado no arquivo binário.
cepProcurado = cepProcurado.encode('latin1')


# BUSCA SEQUENCIAL:
f = open(fileName, "rb")  # Abre o arquivo em modo de leitura binária.

while True:
    line = f.read(recordSize)  # Lê o próximo registro (300 bytes).

    if line == b"":  # Verifica se chegou ao final do arquivo (EOF).
        break         # Encerra o laço quando não existem mais registros.

    # Separa os 300 bytes nos 7 campos definidos em cepFormat.
    record = struct.unpack(cepFormat, line)

    # Compara o CEP do registro (posição 5) com o CEP procurado.
    if record[5] == cepProcurado:

        # Se encontrar, decodifica os bytes para texto e imprime os dados.
        print(codecs.decode(record[0], encoding))  # Logradouro
        print(codecs.decode(record[1], encoding))  # Bairro
        print(codecs.decode(record[2], encoding))  # Cidade
        print(codecs.decode(record[4], encoding))  # UF

# Fecha o arquivo após terminar a busca.
f.close()
