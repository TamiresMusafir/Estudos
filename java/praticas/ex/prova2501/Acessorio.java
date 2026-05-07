package ex.prova2501;

public class Acessorio extends ItemPet{
    public Acessorio(String codigo, double preco){
        super(codigo, preco);
    }

    public double getPrecoFinal(){
        return super.getPrecoFinal() + 7.50;
    }
}
