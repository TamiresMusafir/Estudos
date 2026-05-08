package ex.teste2;

public class Carro extends Veiculo{
    public Carro(String placa, double valorDiaria){
        super(placa, valorDiaria);
    }

    public double getValorLocacao(int dias){
        return super.getValorLocacao(dias) * 1.05;
    }
}
