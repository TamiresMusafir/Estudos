package arrays;

import java.util.Scanner;

public class Main {
    // Método para calcular a média de idade de um array de gatos
    public static double media(Gato[] blauer) {
        double somaIdades = 0;
        for (int i = 0; i < blauer.length; i++) {
            somaIdades += blauer[i].idade;
        }
        return somaIdades / blauer.length;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        // Criando uma "lista" para 1000 gatos
        Gato blauer[] = new Gato[1000];

        for (int i = 0; i < blauer.length; i++) {
            blauer[i] = new Gato();
            blauer[i].nome = "ID" + (i + 1);
            System.out.println("Insira a idade do gato " + blauer[i].nome);
            blauer[i].idade = sc.nextInt();
        }

        System.out.println("A média das idades dos gatos é: " + media(blauer));
    }
}