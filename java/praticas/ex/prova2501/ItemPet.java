package ex.prova2501;

public class ItemPet {
    private String codigo;
    private double preco;

    public ItemPet(String codigo, double preco){
        this.codigo = codigo;
        this.preco = preco;
    }

    public String getCodigo(){
        return codigo;
    }

    public double getPreco(){
        return preco;
    }

    public double getPrecoFinal(){
        return preco + (preco * 0.10); 
    }

    public String toString(){
        String precoFormatado = String.format("%.2f", preco);
        return codigo + "#" + precoFormatado;
    }
}
