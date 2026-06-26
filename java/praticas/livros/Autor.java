package livros;

import java.util.ArrayList;

public class Autor {
    private String nome;
    private String email;
    private ArrayList<Livro> livros;

    public Autor(String nome, String email){
        this.nome = nome;
        this.email = email;
        livros = new ArrayList<>();
    }

    public String getNome(){
        return nome;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public String getEmail(){
        return email;
    }

    public void setEmail(String email){
        this.email = email;
    }

    public ArrayList<Livro> getLivros(){
        return livros;
    }

    public void setLivros(ArrayList<Livro> livros){
        this.livros = livros;
    }
}
