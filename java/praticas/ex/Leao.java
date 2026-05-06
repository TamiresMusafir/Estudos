package ex;

public class Leao extends Animal{
    public Leao(String nome, int idade){
        super(nome, idade);
    }

    public void emitirSom(){
        System.out.println("Rugido: ROAARR!");
    }

    public String toString(){
        return "[Tipo: Leao " + super.toString();
    }
}
