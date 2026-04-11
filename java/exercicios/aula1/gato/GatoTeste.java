package exercicios.aula1.gato;

public class GatoTeste {

    public static void main(String[] args){

        Gato miau = new Gato();
        miau.vivo = true;
        miau.cor = "laranja";
        miau.idade = 5;
        miau.nome = "miau";

        Gato gatin = new Gato();
        gatin.vivo = true;
        gatin.cor = "branco";
        gatin.idade = 5;
        gatin.nome = "gatin";

        Gato catnoir = new Gato();
        catnoir.vivo = true;
        catnoir.cor = "preto";
        catnoir.idade = 5;
        catnoir.nome = "Adrien";

        System.out.println("Gato: " + miau.nome);
        System.out.println("Vivo: " + miau.vivo);
        System.out.println("Cor: " + miau.cor);
        System.out.println("Idade: " + miau.idade);

        System.out.println("Gato: " + gatin.nome);
        System.out.println("Vivo: " + gatin.vivo);
        System.out.println("Cor: " + gatin.cor);
        System.out.println("Idade: " + gatin.idade);

        System.out.println("Gato: " + catnoir.nome);
        System.out.println("Vivo: " + catnoir.vivo);
        System.out.println("Cor: " + catnoir.cor);
        System.out.println("Idade: " + catnoir.idade);
    }
}
