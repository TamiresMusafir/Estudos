#Estudando sobre varáveis e strings.


puts "Digite seu nome:" #diferente do print, pula a linha automaticamente.
nome = gets.chomp #gets lê o valor digitado com \n no final. O chomps remove o \n

puts "Digite sua idade:"
idade = gets.to_i #converte para inteiro. to_f converteria para float.

if idade >= 18
  puts "Olá, #{nome}! Você é maior de idade."
else
  puts "Olá, #{nome}! Você é menor de idade."
end

#para rodar: ruby arquivo.rb