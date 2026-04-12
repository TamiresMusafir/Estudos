package exercicios.aula2;

public class somanum {
    public static void main(String[] args) {
        int soma = 0;

        for(int i = 1; i <= 50000; i++){
            // if(i >= 100 && <= 137)
            //     continue;
            // soma += i;
            if(i < 100 || i > 137)
                soma += i;
        }
        System.out.println("A soma é: " + soma);
    }
}
