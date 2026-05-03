package exercicios.aula4.imovel;
import java.util.Scanner;

public class Corretora {
    Imovel[] imoveis = new Imovel[5];
    Scanner scanner = new Scanner(System.in);

    public void configImoveis(){
        for(int i = 0; i < imoveis.length; i++){

            System.out.println("Digite o tipo de imóvel: 1 - novo, 2 - velho, 3 - comum");
            int tipo = scanner.nextInt();

            if(tipo == 1)
                imoveis[i] = new Novo();
            else if(tipo == 2)
                imoveis[i] = new Velho();
            else
                imoveis[i] = new Imovel();

            System.out.println("Digite o preco do imóvel " + (i+1));
            double valor = scanner.nextDouble(); 

            System.out.println("Digite o endereço do imóvel " + (i+1));
            String endereco = scanner.nextLine();

            imoveis[i].setPreco(valor);
            imoveis[i].setEndereco(endereco);
        }
    }

    public double retornaImovel(){
        double soma = 0;

        for(int i = 0; i < imoveis.length; i++){
            soma += imoveis[i].getPreco();
        }
        return soma;
    }

    public static void main(String args[]){
        Corretora c1 = new Corretora();
        c1.configImoveis();

        System.out.println("O valor na carteira é: R$ " + c1.retornaImovel());
    }
}
