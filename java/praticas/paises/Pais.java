package praticas.paises;

import java.util.List;
import java.util.ArrayList;

public class Pais{
    private String codigo;
    private String nome;
    private int populacao;
    private double dimensao;
    private List<Pais> fronteira = new ArrayList<>();

    public Pais(String codigo){
        this.codigo = codigo.toUpperCase();
    }

    public Pais(String codigo, String nome, double dimensao){
        this(codigo);
        this.nome = nome;
        this.dimensao = dimensao;
    }

    public void setPopulacao(int populacao){
        this.populacao = populacao;
    }

    public int getPopulacao(){
        return populacao;
    }

    public void setDimensao(double dimensao) { 
        this.dimensao = dimensao;
    }

    public double getDimensao(){
        return dimensao;
    }

    public boolean equals(Object o) {
        if (!(o instanceof Pais)) 
            return false;
        Pais outro = (Pais) o;
        return this.codigo.equals(outro.codigo);
    }

    public double densidadePopulacional(){
        return populacao/dimensao;
    }

    public boolean fazFronteira(Pais pais){
        return fronteira.contains(pais);
    }

    public void adicionaFronteira(Pais paisFronteira){
        fronteira.add(paisFronteira);
    }
}