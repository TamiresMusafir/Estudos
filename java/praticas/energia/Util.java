package energia;

import java.util.Collection;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

public class Util {
    public static Collection processa(List linhas) throws ProcessamentoException{
        Collection medicoes = new ArrayList();

        Iterator it = linhas.iterator();

        while(it.hasNext()){
            String linha = (String) it.next(); // FAZER CASTING

            int count = 0;

            for(int i = 0; linhas.lenth; i++){
                if(linha.chatAt[i] == '#')
                    count++;
            }

            if(count != 2)
                throw new ProcessamentoException("Formato incorreto: " + linha);

            String[] partes = linha.split("#");
            
            String id = partes[0];
            String nome = partes[1];
            double energiaGerada = Double.parseDouble(partes[2]); // ESQUECENDO
            
            MedicaoEnergia m;

            if(id.startsWith("S"))
                m = new MedicaoSolar(id, nome, energiaGerada);
            else
                m = new MedicaoEolica(id, nome, energiaGerada);

            medicoes.add(m);

        }
        return medicoes;
    }
}
