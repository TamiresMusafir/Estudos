#serve para criar uma nova lista sem alterar a lista do qual recebeu os valores

nomes = ["maria", "joão", "juca"]

nomes_completos = nomes.map do |nome_completo|
	nome_completo + " sobrenome"
end

puts nomes
puts "-----------"
puts nomes_completos

#para sobrescrever a lista: 

nomes.map! do |nome_completo|
	nome_completo + " sobrenome"
end

puts nomes
