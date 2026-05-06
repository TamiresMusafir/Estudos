package ex;

public class Animal {
    private String nome;
    private int idade;

    public Animal(String nome){
        this.nome = nome;
    }

    public Animal(String nome, int idade){
        this.nome = nome;
        this.idade = idade;
    }

    public void emitirSom(){
        System.out.println("Animal emitindo som");
    }

    public String toString(){
        return "[Nome: " + this.nome + " | Idade: " + this.idade + "]";
    }
}
