#syntax em ruby

nome = "Tamires"
n = 5

if nome == "Tamires"
  puts "estudante"
else
  puts "nemnem"
end

if nome.eql?("Tamires")
  puts "estudante"
else
  puts "nemnem"
end

#condição ? verdadeiro : falso

resultado = nome.eql?("Tamires") ? "estudante" : "nemnem"

soma = n.eql?(r) ? n + 10 : n -1
puts soma