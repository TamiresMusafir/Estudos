package exercicios.aula3.conta;

public class ContaBancaria {
    private double saldo = 0.0;
    private Data dataAbertura;

    public double getSaldo(){
        return this.saldo;
    }

    public void setSaldo(double saldo){
        this.saldo = saldo;
    }

    public Data getAbertura(){
        return this.dataAbertura;
    }

    public void setAbertura(Data dataAbertura){
        this.dataAbertura = dataAbertura;
    }

    public String getDataAberturaFormatada(){
        return String.format("%02d/%02d/%04d",
        dataAbertura.getDia(),
        dataAbertura.getMes(),
        dataAbertura.getAno()
        );
    }

    public String getSaldoFormatado(){
        String valor = String.format("%.2f", saldo);
        valor = valor.replace('.', ',');
        return "R$ " + valor;
    }

    public void depositar(double valor){
        saldo += valor;
    }

    public void sacar(double valor){
        if(saldo > 0)
            saldo -= valor;
    }
}
