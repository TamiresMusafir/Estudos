package banco;

public class ContaCorrente extends Conta implements Tributavel{
     public double calculaTributos(){
        return saldo *  0.01;
     } 
}
