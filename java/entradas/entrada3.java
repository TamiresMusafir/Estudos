package entrada;

import java.util.Scanner;

public class entrada3 {
    public static void main(String[] args){
    	double soma = 0;
    	
    	int [] k = new int [3];
    	Scanner scanner = new Scanner(System.in);
    	System.out.println("Insira um número");
    	int lendoInteiro1 = scanner.nextInt();
    	System.out.println("Insira outro número");
    	int lendoInteiro2 = scanner.nextInt();
    	System.out.println("Insira outro número");
    	int lendoInteiro3 = scanner.nextInt();
    	
    	
    	k [0] = lendoInteiro1;
    	k [1] = lendoInteiro2;
    	k [2] = lendoInteiro3;
    	
    	for(int i = 0; i < k.length; i++) {
    		soma += k[i];
    	}
    	System.out.println(soma/k.length);
    }
}
