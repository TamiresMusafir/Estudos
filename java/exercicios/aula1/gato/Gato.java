package exercicios.aula1.gato;

public class Gato {
    boolean vivo;
    String cor;
    int idade;
    String nome;

    public void miar(){
        System.out.println("gato miando");
    }

    public static void main(String[] args){
        Gato garfield = new Gato();
        garfield.miar();
    }
}