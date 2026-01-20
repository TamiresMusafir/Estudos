#arrays e vetores são o mesmo

lista []
lista ["isso", "aquilo", "nisso"]

lista.push("Nome", "Nome2")
lista.push "Nome", "Nome2" #parenteses sao opicionais, da no mesmo
lista << "Maria" #coloca na última posição

lista.insert(0, "Fulano") #substitui a posição 0
puts lista[1] #acessa o conteudo na posição
puts lista[1..4] #acessa até a posição 4

lista.delete("Siclano") #deleta
puts lista

puts lista.lenght #quantidade na lista
puts lista.sort #organiza em ordem alfabetica
puts list.first #primeiro elemento
puts list.last #ultimo elemento

puts list.sort.last #ja na lista organizada

lista_organizada = lista.sort

puts lista_organizada
puts lista_organizada.first
puts lista_organizada.last



numeros = [1, 2, 3]

numeros.push(4) # push → adiciona no FINAL. Agora o array é: [1, 2, 3, 4]

numeros << 5 # << → adiciona no FINAL (atalho de push). Agora o array é: [1, 2, 3, 4, 5]

numeros.unshift(0) # unshift → adiciona no INÍCIO. Agora o array é: [0, 1, 2, 3, 4, 5]

ultimo = numeros.pop # pop → remove do FINAL
# ultimo = 5
# Agora o array é: [0, 1, 2, 3, 4]

# -------------------------
# shift → remove do INÍCIO
# -------------------------
primeiro = numeros.shift
# primeiro = 0
# Agora o array é: [1, 2, 3, 4]

# -------------------------
# Exemplo real (Rails / validação)
# -------------------------
errors = []

errors << "Email inválido"        # adiciona no final
errors.push("Senha muito curta")  # mesmo efeito

# errors agora é:
# ["Email inválido", "Senha muito curta"]
