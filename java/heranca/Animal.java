package heranca;

public class Animal {
    private String cor;
    private int idade;
    private double peso;
    private String nome;

    public void setCor(String d) { cor = d; }
    public String getCor() { return cor; }

    public void setIdade(int i) { idade = i; }
    public int getIdade() { return idade; }

    public void setPeso(double p) { peso = p; }
    public double getPeso() { return peso; }

    public void setNome(String n) { nome = n; }
    public String getNome() { return nome; }

    public void correr() {
        System.out.println("Animal " + nome + " correndo");
    }
}