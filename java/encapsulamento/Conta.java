package encapsulamento;

public class Conta {
    private double saldo; // Valor default é 0
    private String cpf;   // Valor default é null

    public void debitar(double val) {
        if (val == saldo) {
            System.out.println("Meu deus do ceu nao sobrou nada");
            saldo -= val;
        } else if (val <= saldo) {
            System.out.println("Debitando " + val);
            saldo -= val;
        } else {
            // Se tentar sacar mais do que tem, o programa trava de propósito
            throw new RuntimeException();
        }
    }

    public void depositar(double v) {
        saldo += v;
    }

    public void setCpf(String c) {
        cpf = c;
    }

    public double getSaldo() {
        return saldo;
    }
}