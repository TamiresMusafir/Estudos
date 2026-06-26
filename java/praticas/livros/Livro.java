package livros;

public class Livro {
    private String titulo;
    private double preco;

    public Livro(String titulo, double preco){
        this.titulo = titulo;
        this.preco = preco;
    }

    public String getTtitulo(){
        return titulo;
    }

    public void setTitulo(String titulo){
        this.titulo = titulo;
    }

    public double getPreco(){
        return preco;
    }

    public void setPreco(double preco){
        this.preco = preco;
    }
}
