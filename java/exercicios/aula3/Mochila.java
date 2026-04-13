package exercicios.aula3;
import java.util.Scanner;

public class Mochila {
    String cor;
    int anoFabricacao;
    public static void main(String[] args) {
        Mochila[] mochila = new Mochila[4];
        Scanner leitura = new Scanner(System.in);

        for(int i = 0; i < mochila.length; i++){

            mochila[i] = new Mochila();

            System.out.println("Insira o ano de fabricacao: ");
            int lendo = leitura.nextInt();

            mochila[i].anoFabricacao = lendo;
        }
    }
}
