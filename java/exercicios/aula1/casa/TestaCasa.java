package exercicios.aula1.casa;

public class TestaCasa {
    
    public static void main(String[] args){
        Casa pequena = new Casa();
        pequena.cor = "amarela";
        pequena.numero = 46;

        Casa grande = new Casa();
        grande.cor = "branca";
        grande.numero = 145;

        System.out.println("A casa de número " + pequena.numero + " tem a cor " + pequena.cor);
        System.out.println("A casa de número " + grande.numero + " tem a cor " + grande.cor);
    }
}
