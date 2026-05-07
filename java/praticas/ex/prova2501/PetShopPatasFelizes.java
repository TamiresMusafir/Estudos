package ex.prova2501;
import java.util.Scanner;

public class PetShopPatasFelizes{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        ItemPet[] itens = new ItemPet[5]; 

        for(int i = 0; i < 3; i++){
            System.out.println("Ração " + (i+1) + ":");

            System.out.println("Digite o código: ");
            String codigo = sc.nextLine();

            System.out.println("Digite o preco");
            double preco = sc.nextDouble();
            sc.nextLine();

            itens[i] = new Racao(codigo, preco);
        }

        for(int i = 0; i < 2; i++){
            System.out.println("Acessório " + i+1 + ":");

            System.out.println("Digite o código: ");
            String codigo = sc.nextLine();

            System.out.println("Digite o preco: ");
            double preco = sc.nextDouble();
            sc.nextLine();

            itens[i+3] = new Acessorio(codigo, preco);
        }

        System.out.println("\n--- Lista de Itens Cadastrados ---");
        
        for (int i = 0; i < itens.length; i++) {
            System.out.println(itens[i]); 
        }

        double[] resultado = Utils.media(itens);
        
        double mediaFinal = resultado[0];
        double mediaBase = resultado[1];
        double diferenca = mediaFinal - mediaBase;

        System.out.println("Média dos preços finais: " );

        System.out.println("Média dos preços finais: " + mediaFinal);
        System.out.println("Média dos preços base: " + mediaBase);
        System.out.println("Diferença entre as médias: " + diferenca);

        sc.close();
    }
}
