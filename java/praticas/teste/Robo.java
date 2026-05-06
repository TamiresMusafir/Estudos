package teste;

public class Robo {
    private String id;
    private String nome;
    private double peso;

    public Robo(String id){
        this.id = id;
    }

    public String getId(){
        return id;
    }

    public String getNome(){
        return nome;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public double getPeso(){
        return peso;
    } 
    
    public void setPeso(double peso){
        this.peso = peso;
    }

    public String status(){
        return "Nome: " + getNome() + " | Peso: " + getPeso();
    }
}
