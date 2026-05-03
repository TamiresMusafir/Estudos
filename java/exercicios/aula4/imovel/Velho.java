package exercicios.aula4.imovel;

public class Velho extends Imovel {

    public double getPreco(){
        return super.getPreco() - (super.getPreco() * 0.10);
    }
}
