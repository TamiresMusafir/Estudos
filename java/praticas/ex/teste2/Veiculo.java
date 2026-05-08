package ex.teste2;

public class Veiculo {
    private String placa;
    private double valorDiaria;

    public Veiculo(String placa, double valorDiaria){
        this.placa = placa;
        this.valorDiaria = valorDiaria;
    }

    public String getPlaca(){
        return placa;
    }

    public double getValorDiaria(){
        return valorDiaria;
    }

    public double getValorLocacao(int dias){
        return valorDiaria * dias;
    }

    public String toString(){
        String valorFormtado = String.format("%.2f", valorDiaria);
        return placa + ":" + valorFormtado;
    }
}
