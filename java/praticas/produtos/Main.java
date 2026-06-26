package produtos;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Collection;
import java.util.Iterator;

public class Main {
    public static void main(String[] args){
        List<String> lista = new ArrayList<>();

        Scanner sc = new Scanner(System.in);

        System.out.println("Digite uma linha");
        String linha = sc.nextLine();

        while(!(linha.equals("fim"))){
            lista.add(linha);
            System.out.println("Digite uma linha");
            linha = sc.nextLine();
        }

        try{
            Collection<Produto> produtos = Util.processa(lista);

            double soma = 0;

            Iterator<Produto> it = produtos.iterator();
            while(it.hasNext()){
                Produto p = it.next();
                soma += p.getPreco();
            }

            double media = soma/produtos.size();

            System.out.println("Media dos valores: " + media);
        }catch (ProcessamentoException e){
            System.out.println(e.getMessage());
        }

        sc.close();
    }
}
