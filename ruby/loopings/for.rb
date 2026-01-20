nomes = ["maria", "joão", "juca"]

dict = {nome: "Ku", idade: 45, altura: 1.73}

for nome in nomes do
  puts nome
end

for k, v in dict do
  puts "#{k}: #{v}"
end