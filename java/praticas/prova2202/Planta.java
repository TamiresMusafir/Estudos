package prova2202;

public class Planta {
    private String id;
    private String nome;
    private double tamanho;

    public Planta(String id){
        this.id = id;
    }

    public String getId(){
        return this.id;
    }

    public String getNome(){
        return this.nome;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public double getTamanho(){
        return this.tamanho;
    }

    public void setTamanho(double tamanho){
        this.tamanho = tamanho;
    }
}
