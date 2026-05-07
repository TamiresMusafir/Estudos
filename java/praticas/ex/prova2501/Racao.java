package ex.prova2501;

public class Racao extends ItemPet {
    public Racao(String codigo, double preco){
        super(codigo, preco);
    }

    public double getPrecoFinal(){
        return super.getPrecoFinal() + (super.getPrecoFinal() * 0.03);
    }
}
