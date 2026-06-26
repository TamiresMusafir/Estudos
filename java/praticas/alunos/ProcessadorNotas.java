package alunos;

import java.util.Collection;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

public class ProcessadorNotas {
    public static Collection processa(List lista) throws EntradaInvalidaException{
        Collection<Aluno> alunos = new ArrayList<>();

        Iterator<String> it = lista.iterator();

        while(it.hasNext()){
            String linha = it.next();

            String[] partes = linha.split("#");

            if(partes.length != 3){
                throw new EntradaInvalidaException("Formato Inválido");
            }

            String id = partes[0];
            String nome = partes[1];
            double nota = Double.parseDouble(partes[2]);

            Aluno a;

            if(id.startsWith("A"))
                a = new AlunoRegular(id, nome, nota);
            else
                a = new AlunoEspecial(id, nome, nota);

            alunos.add(a);
        }

        return alunos;
    }
}
