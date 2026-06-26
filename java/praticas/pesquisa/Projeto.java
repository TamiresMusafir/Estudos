package pesquisa;

public class Projeto {
    private String titulo;
    private double valorFinanciamento;

    public Projeto(String titulo, double valorFinanciamento){
        this.titulo = titulo;
        this.valorFinanciamento = valorFinanciamento;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public double getValorFinanciamento() {
        return valorFinanciamento;
    }

    public void setValorFinanciamento(double valorFinanciamento) {
        this.valorFinanciamento = valorFinanciamento;
    }
}
