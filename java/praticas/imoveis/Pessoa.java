package praticas.imoveis;

import java.util.ArrayList;

public class Pessoa {
    private String cpf;
    private String nome;
    private ArrayList<Imovel> imoveis;

    public Pessoa(String cpf, String nome){
        this.cpf = cpf;
        this.nome = nome;
        this.imoveis = new ArrayList<>();
    }

    public String getCpf(){
        return cpf;
    }

    public void setCpf(String cpf){
        this.cpf = cpf;
    }
    
    public String getNome(){
        return nome;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public ArrayList<Imovel> getImoveis(){
        return imoveis;
    }

    public void setImoveis(ArrayList<Imovel> imoveis){
        this.imoveis = imoveis;
    }

    public void addImoveis(Imovel imovel){
        imoveis.add(imovel);
    }
}
