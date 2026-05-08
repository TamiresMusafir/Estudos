package ex.teste2;

public class Moto extends Veiculo{
    public Moto(String placa, double valorDiario){
        super(placa, valorDiario);
    }

    public double getValorLocacao(int dias){
        return super.getValorLocacao(dias) - 10.0;
    }
}
