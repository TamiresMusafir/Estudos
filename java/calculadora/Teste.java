package calculadora;

public class Teste {
    public static int a = 0; // STATIC: Todo mundo divide o mesmo 'a'
    public int b = 0;        // NÃO STATIC: Cada objeto tem o seu 'b' próprio

    public Teste() {
        // Toda vez que faz um "new Teste()", o 'a' aumenta para todos
        a++; 
    }
}