package energia;

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class Principal {
    public static void main(String[] args) {
        List linhas = new ArrayList();
        Scanner sc = new Scanner(System.in);

        System.out.println("Digite a linha");
        String linha = sc.nextLine();

        while(!(linha.equals("Fim"))){
            linhas.add(linha);
            System.out.println("Digite a linha");
            linha = sc.nextLine();
        }

        try{
            Collection medicoes = Util.processa(linhas);

            Iterator it = medicoes.iterator();

            double soma = 0;

            while(it.hasNext()){
                MedicaoEnergia energia = (MedicaoEnergia) it.next();
                soma += energia.getEnergiaGerada();
            }

            double media = soma / medicoes.size();

            System.out.println("Média de energia gerada: " + media);
        }catch(ProcessamentoException e){
            System.out.println(e.getMessage());
        }
    }
}
