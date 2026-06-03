package banco;

public class Cliente{
    private String nome;
    private String cpf;

    public Cliente(String nome, String cpf){
        this.nome = nome;
        this.cpf = cpf;
    }

    Tributavel[] tributaveis = new Tributavel[10];

    public String getNome(){
        return nome;
    }

    public String getCpf(){
        return cpf;
    }
}