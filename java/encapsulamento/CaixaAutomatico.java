package encapsulamento;

import java.util.Scanner;

public class CaixaAutomatico {
    public static void main(String[] args) {
        Conta blungs = new Conta();
        blungs.setCpf("080");
        blungs.depositar(100);

        Scanner sc = new Scanner(System.in);
        System.out.println("Quanto quer sacar?");
        int valor = sc.nextInt();

        blungs.debitar(valor);
        System.out.println("Liberando " + valor + " na pontinha");
    }
}