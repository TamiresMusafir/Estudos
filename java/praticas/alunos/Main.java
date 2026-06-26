package alunos;

import java.util.List;
import java.util.Collection;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Iterator;

public class Main {
    public static void main(String[] args) {
        List<String> linhas = new ArrayList<>();
        Scanner sc = new Scanner(System.in);

        System.out.println("Insira a linha: ");
        String linha = sc.nextLine();

        while(!(linha.equals("Fim"))){
            linhas.add(linha);
            System.out.println("Insira a linha: ");
            linha = sc.nextLine();
        }

        try{
            Collection<Aluno> alunos = ProcessadorNotas.processa(linhas);

            Iterator<Aluno> it = alunos.iterator();

            double soma = 0;

            while(it.hasNext()){
                Aluno a = it.next();
                soma += a.getNota();
            }

            double media = soma/alunos.size();

        }catch(EntradaInvalidaException e){
            System.out.println(e.getMessage());
        }
    }
}
