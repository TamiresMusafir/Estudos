package exercicios.aula3;

public class Aluno {
    private String nome;
    private double nota1;
    private double nota2;

    public String getNome(){
        return this.nome;
    }

    public void setNome(String nome){
        this.nome = nome;   
    }

    public double getNota1(){
        return this.nota1;
    }

    public void setNota1(double nota1){
        if(nota1 < 0)
            this.nota1 = 0;
        else if(nota1 > 10)
            this.nota1 = 10;
        else
            this.nota1 = nota1;
    }

    public double getNota2(){
        return this.nota2;
    }

    public void setNota2(double nota2){
        if(nota2 < 0)
            this.nota2 = 0;
        else if(nota2 > 10)
            this.nota2 = 10;
        else
            this.nota2 = nota2;
    }

    public double getMedia(){
        double media = (nota1 + nota2) / 2;
        return media;
    }

    public String getResultado(){
        double media = getMedia();

        if(media >= 4 && media <= 5.9)
            return "Em recuperação";
        else if(media < 4)
            return "Reprovado";
        else
            return "Aprovado";
    }

    public static void main(String[] args){
        Aluno a1 = new Aluno();

        a1.setNome("Carlos");
        a1.setNota1(5);
        a1.setNota2(7);

        System.out.println("Aluno: " + a1.getNome());
        System.out.println("A nota da P1 foi: " + a1.getNota1());
        System.out.println("A nota da P2 foi: " + a1.getNota2());
        System.out.println("A média foi: " + a1.getMedia());
        System.out.println("O resultado foi: " + a1.getResultado());
    }
}
