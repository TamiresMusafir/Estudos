#não altera o externo. Só a variável dentro do bloco recebe os valores

nomes = ["maria", "joão", "juca"]

dict = {nome: "Ku", idade: 45, altura: 1.73}

nomes.each do |nome|
  puts nome
end

dict.each do |k, v|
  puts "#{k}: #{v}"
end
