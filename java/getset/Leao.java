package getset;

public class Leao {
    private int idade;
    private String nome;

    public Leao() {
        System.out.println("Criando um leao");
    }

    public int getIdade() {
        return idade;
    }

    public void setIdade(int i) {
        idade = i;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String n) {
        nome = n;
    }
}
