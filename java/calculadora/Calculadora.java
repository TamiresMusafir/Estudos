package calculadora;

public class Calculadora {
    private String cor;

    // Método STATIC: Você chama direto pela classe (Calculadora.media)
    public static double media(double n1, double n2) {
        return (n1 + n2) / 2;
    }

    // Outro STATIC: Mas agora com 3 números (Sobrecarga)
    public static double media(double n1, double n2, double n3) {
        return (n1 + n2 + n3) / 3;
    }

    // Método NÃO static: Precisa de um "new Calculadora()" para usar
    public void setCor(String c) {
        this.cor = c;
    }

    public String getCor() {
        return this.cor;
    }
}