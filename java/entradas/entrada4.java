import java.util.Scanner;

public class entrada4 {
    public static void main(String[] args){
    	double soma = 0;
    	
    	int [] k = new int [3];
    	
    	Scanner scanner = new Scanner(System.in);
    	for(int i = 0; i < k.length; i++) {
    		k[i] = scanner.nextInt();
    	}
    	
    	for(int i = 0; i < k.length; i++) {
    		soma += k[i];
    	}
    	System.out.println(soma/k.length);
    }
}
//calcular media de cada idade dos gatos;
