package produtos;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Iterator;
public class Util {
    public static Collection processa(List x) throws ProcessamentoException{

        Collection<Produto> produtos = new ArrayList<>(); 

        Iterator<String> it = x.iterator();

        while(it.hasNext()){
            String linha = it.next();

            String[] partes = linha.split("#");

            if(partes.length != 3)
                throw new ProcessamentoException("Formato incorreto: " + linha);

            String id = partes[0];
            String nome = partes[1];
            double preco = Double.parseDouble(partes[2]);

            Produto p;

            if(id.startsWith("K"))
                p = new ProdutoSimples(id, nome, preco);
            else
                p = new ProdutoEspecial(id, nome, preco);

            produtos.add(p);
        }

        return produtos;
    }
}
