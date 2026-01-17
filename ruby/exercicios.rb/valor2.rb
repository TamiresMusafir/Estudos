Faça um programa, utilizando as funções abaixo, que leia o valor do gasto de um cliente em um restaurante, calcule e exiba o valor a ser pago ao garçom e o valor total a ser pago pelo cliente, considerando que o valor a ser pago ao garçom é 10% do gasto do cliente. Faça as funções:
a) calculaValorGarcom: recebe como parâmetro o valor do gasto do cliente, calcula, exibe e retorna o valor a ser pago ao garçom.
b) calculaValorTotal: recebe como parâmetro o valor do gasto do cliente, calcula e retorna o valor total a ser pago pelo cliente. Esta função deverá utilizar, obrigatoriamente, a função calculaValorGarcom.

puts "Digite o valor gasto pelo cliente: "
valor = gets.to_f

puts "Valor pago ao garçom: #{garcom}"

def calculaValorGarcom(valor)
    valor * 0.10

    puts
end