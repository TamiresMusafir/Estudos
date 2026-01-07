#Faça um programa, utilizando a função abaixo, que processe um aluno de uma turma. O programa deverá ler as seguintes informações do aluno: matrícula, nota da primeira prova, nota da segunda prova, nota do primeiro trabalho e nota do segundo trabalho. Este programa deverá calcular a média das provas, a média dos trabalhos e a média final e exibir a matrícula, a média das provas, a média dos trabalhos e a média final.
#Todas as médias são aritméticas. Faça a seguinte função:
#a) calculaMedia: esta função deverá receber como parâmetros os dois valores para o cálculo da média aritmética, calcular e retornar a média aritmética.

def calculaMedia(valor1, valor2)
    (valor1 + valor2) / 2
end

puts "Digite seu nome: "
nome = gets.chomp

puts "Digite sua matrícula: "
matricula = gets.to_i

puts "Digite sua nota da primeira prova: "
prova1 = gets.to_f

puts "Digite sua nota da segunda prova: "
prova2 = gets.to_f

puts "Digite sua nota do primeiro trabalho: "
trabalho1 = gets.to_f

puts "Digite sua nota da segunda prova: "
trabalho2 = gets.to_f

mediaProva =  calculaMedia(prova1, prova2)
mediaTrabalho =  calculaMedia(trabalho1, trabalho2)
mediaFinal = calculaMedia(mediaProva, mediaTrabalho)

puts "Nome do aluno: #{nome}"
puts "Matrícula: #{matricula}"
puts "Média das provas: #{mediaProva}"
puts "Média dos Trabalhos: #{mediaTrabalho}"
puts "Média Final: #{mediaFinal}"