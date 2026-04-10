package calculadora;

public class Main {
    public static void main(String[] args) {
        // Usando coisas prontas do Java (Static)
        System.out.println(Math.random());
        System.out.println(Math.sqrt(500));

        // Calculadora: Usando o método static sem dar 'new'
        System.out.println(Calculadora.media(3, 4));
        System.out.println(Calculadora.media(8, 7, 9));

        // Calculadora: Usando objetos para definir cores
        Calculadora c1 = new Calculadora();
        Calculadora c2 = new Calculadora();
        c1.setCor("Azul");
        c2.setCor("Verde");
        System.out.println(c1.getCor());
        System.out.println(c2.getCor());

        // Testando o Static vs Não Static
        Teste t = new Teste();
        t.b = 3; // O 'b' só muda no objeto 't'
        
        new Teste(); // Criando objetos sem nome só para ativar o construtor
        new Teste();

        System.out.println("Valor de t.b: " + t.b);
        System.out.println("Valor de Teste.a: " + Teste.a); // Deve mostrar 3, pois criou 3 objetos
    }
}
