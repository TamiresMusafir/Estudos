hash = {nome: "Diego", idade: 16}
hash[:altura] = 1.73
puts hash
puts hash[:nome]
puts hash.has_value?("Diego") #verifica o valor
puts hash.has_key?(:nome) #verifica a chave
puts hash.keys #mostra as chaves existentes
puts hash.values #mostra os valores existentes
puts hash.size #mostra o tamanho
puts has.length
hash.delete (:altura)


hash.clear #apaga toda a hash


hash1 = {:um => 1, :dois => 2, :tres => 3}
hash2 = {:tres => 3, :quatro => 4, :cinco => 5}

puts hash1 == hash2