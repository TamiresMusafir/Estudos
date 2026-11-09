import struct

hashFormat = struct.Struct("i1000l1000l")

def unpackLinha(linha):
    tupla = hashFormat.unpack(linha)
    n = tupla[0]
    chaves = []
    posicoes = []
    for i in range(1,n+1):
        chaves.append(tupla[i])
    for i in range(1001,1001+n):
        posicoes.append(tupla[i])
    return chaves, posicoes

def packLinha(chaves, posicoes):
    n = len(chaves)
    parametros = [n]
    for i in range(0,1000):
        if i < n:
            parametros.append(chaves[i])
        else:
            parametros.append(0)
    for i in range(0,1000):
        if i < n:
            parametros.append(posicoes[i])
        else:
            parametros.append(0)
    return hashFormat.pack(*parametros)



Estrutura vazio;
vazio.N = 0;
for()
{ 
    vazio.chaves[i] = 0
    vazio.posicoes[i] = 0
}
fwrite numero magico vezes;


abrir o arquivo de cep
ler linha a linha (cola processamento sequencial)
x = 0
para cada registro do cep

   p = hash(e.cep);
   seek no indice na posicao p
   le do indice a entrada tabela da posicao p
   ve se cabe (n < 1000) insere e.cep, posicao no arq de dados(x)
    x++

# Escolher um numero magico >> 700
# vazio = packLinha([],[])
# escreve em um arquivo binario numero magico vezes vazio
# reabre leitura escrita o indice. Abre o arquivo de dados
# Para cada endereco no arquivo de dados.
# p = h(cep)
# seek no arquivo de indice
# le linha
# seek denovo
# chaves, posicoes = unpack(linha)
# se len(chaves) == 1000 -> Ignora.
# senao chaves.append(cep), posicoes.append(numero do registro)
# escreve no indice packLinha(chaves, posicoes)
# Fim do for e tchau

chaves = []
posicoes = []
binario = packLinha(chaves,posicoes)
print(binario)
chaves2, posicoes2 = unpackLinha(binario)
print(chaves2)
print(posicoes2)


        

