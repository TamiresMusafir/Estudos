package exercicios.aula1.casa;

public class TestaCasaJanela {
    
    public static void main(String[] args) {
        Janela janela1 = new Janela();
        janela1.cor = "cinza";
        janela1.material = "madeira";

        Casa casa1 = new Casa();
        casa1.cor = "amarela";
        casa1.numero = 46;
        casa1.janela = janela1;

        System.out.println(casa1.cor);
        System.out.println(casa1.numero);
        System.out.println(casa1.janela.cor);
        System.out.println(casa1.janela.material);
    }
}
