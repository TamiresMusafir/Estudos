def main():
	produto = "carro"          # Texto precisa de aspas ("" ou '')
	preco = 10.0               # float
	quantidade = 8             # int
	total = preco * quantidade  # calcula 80.0

	print(f"produto: {produto}: {total}")
	# Saída no terminal: produto: carro: 80.0

	if total > 50.0:
		print("frete gratis")
	else:
		print("Frete: R$ 15,00")

	#--------------------------

	compras = ["pão", "leite", "café"]

	compras.append("suco")

	print(f "{len(compras)} - {compras[-1]}") #imprime o último de trás para frente

	#--------------------------

	notas = [7.5, 4.0, 9.0, 5.5, 8.0]

	for nota in notas:
		if nota >= 6.0:
			print(f"nota: {nota}: Aprovado")
		else:
			print(f"nota: {nota}: Reprovado")

	#--------------------------

	carro = {
		"marca": "Toyota",
		"modelo": "Corolla",
		"ano": 2020
	}

	print(f"Modelo: {carro['modelo']}")
	
	carro["cor"] = "Prata"

	carro["ano"] = 2024

print(f"Modelo: {carro['modelo']} - Ano: {carro['ano']} - Cor: {carro['cor']}")

if __name__ == "__main__":
 	main()

def analisar_pedido(valor_total, cupon, taxa_entrega):
	if cupon == "PROMO10":
		valor_total = -0.10
		if valor_total > 100.0:
			taxa_entrega = 0.0
