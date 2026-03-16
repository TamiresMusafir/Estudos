import java.util.Scanner;

public class entrada2 {
    double soma = 0;
    	
    int [] k = new int [3]
    
    k [0] = 8;
    k [1] = 3;
    k [2] = 4;
    
    for(int i = 0; i < k.length; i++) {
        soma += k[i];
    }
    System.out.println(soma/k.length);
}
