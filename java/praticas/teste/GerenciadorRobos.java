package teste;
import java.util.Scanner;

public class GerenciadorRobos {
    
    public Robo[] preocessarDados(String[] entradas){
        Robo[] robos = new Robo[entradas.length];
        Scanner sc = new Scanner(System.in);

        for(int i = 0; i < robos.length; i++){

            System.out.println("DIgite o tipo do robô: 1-Seguidor, 2-Sumô");
            int tipo = sc.nextInt();
            sc.nextLine();

            System.out.println("Digite o id do robô: ");
            String id = sc.nextLine();

            switch(tipo){
                case 1:
                    robos[i] = new SeguidorLinha(id);
                    break;
                case 2:
                    robos[i] = new Sumo(id);
                    break;
                default:
                    System.out.println("Tipo inválido, criando robô padrão");
                    robos[i] = new Robo(id);
            }

            System.out.println("Digite o nome do robô: ");
            String nome = sc.nextLine();

            robos[i].setNome(nome);

            System.out.println("Digite o peso do robo: ");
            double peso = sc.nextDouble();
            sc.nextLine();

            robos[i].setPeso(peso);
        }

        return robos;
    }
}
