package exercicios.aula2;

public class impares {
    public static void main(String[] args) {
        int soma = 0;

        for(int i = 1; i <= 10000; i++){
            if(i % 2 != 0)
                soma += i;
        }

        System.out.println("A soma é: " + soma);
    }
}
