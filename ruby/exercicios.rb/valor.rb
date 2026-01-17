Faça um programa, utilizando as funções abaixo, que leia o valor do gasto de um cliente em um restaurante, calcule e exiba o valor a ser pago ao garçom e o valor total a ser pago pelo cliente, considerando que o valor a ser pago ao garçom é 10% do gasto do cliente. Faça as funções:
a) calculaValorGarcom: recebe como parâmetro o valor do gasto do cliente, calcula e retorna o valor a ser pago ao garçom.
b) calculaValorTotal: recebe como parâmetros o valor do gasto do cliente e o valor a ser pago ao garçom, calcula e retorna o valor total a ser pago pelo cliente.

puts "Digite o valor gasto pelo cleinte: "
valor = gets.to_f

def calculaValorGarcom(valor)
    valor * 0.10
end

def calculaValorTotal(valor, pago)
    valor + pago
end

pago  = calculaValorGarcom(valor)
total = calculaValorTotal(valor, pago) 

puts "O valor a ser pago pelo garçom é: #{pago}"
puts "O valor total a ser pago pelo cliente é: #{total}"
