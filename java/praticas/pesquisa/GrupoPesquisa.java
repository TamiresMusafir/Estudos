package pesquisa;

import java.util.ArrayList;

public class GrupoPesquisa {
    private String codigo;
    private String nome;
    private ArrayList projetos;

    public GrupoPesquisa(String codigo, String nome){
        this.codigo = codigo;
        this.nome = nome;
        projetos = new ArrayList();
    }

     public String getCodigo() {
        return codigo;
    }

    public void setCodigo(String codigo) {
        this.codigo = codigo;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public ArrayList getProjetos(){
        return projetos;
    }

    public void setProjetos(ArrayList projetos){
        this.projetos = projetos;
    }
}
