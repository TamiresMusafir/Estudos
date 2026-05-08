package ex.teste2;
import java.util.Scanner;

public class Principal {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Veiculo[] veiculos = new Veiculo[4];

        for(int i = 0; i < veiculos.length; i++){
            System.out.println("Carro: ");

            System.out.println("Digite a placa do veículo: ");
            String placa = sc.nextLine();

            System.out.println("Digite o valor da diária: ");
            double valorDiaria = sc.nextDouble();

            veiculos[i] = new Carro(placa, valorDiaria);
        }

        for(int i = 2; i < veiculos.length; i++){
            System.out.println("Moto: ");

            System.out.println("Digite a placa do veículo: ");
            String placa = sc.nextLine();

            System.out.println("Digite o valor da diária: ");
            double valorDiaria = sc.nextDouble();

            veiculos[i] = new Moto(placa, valorDiaria);
        }

        System.out.println("Digite a quantidade de dias de alocação: ");
        int dias = sc.nextInt();

        for(int i = 0; i < veiculos.length; i++){
            System.out.println(veiculos[i]);
        }

        double[] somas = CalculadoraLocacao.processarLocacoes(veiculos, dias);

        double soma = somas[0];
        double mediaDiaria = somas[1];
   
        System.out.println("Total a ser pago: " + soma);
        System.out.println("Média das diárias: " + mediaDiaria);

        sc.close();
    }
}
