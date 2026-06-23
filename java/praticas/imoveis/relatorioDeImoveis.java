package praticas.imoveis;

import java.util.HashMap;
import java.util.Iterator;;

public class relatorioDeImoveis {
    public static void relatorioDeImoveis(HashMap mapa){
        Iterator<Pessoa> it = mapa.values().iterator();
    
        while (it.hasNext()) {
        
        // 3. Pegamos o objeto Pessoa atual e avançamos o ponteiro
            Pessoa pessoa = it.next();
            
            double totalPreco = 0.0;
            
            Iterator<Imovel> itImoveis = pessoa.getImoveis().iterator();
        
            while (itImoveis.hasNext()) {
                Imovel imovel = itImoveis.next(); // Pega o imóvel atual
                totalPreco += imovel.getPreco();  // Soma o preço
            }
            
            System.out.println(pessoa.getNome() + " - " + totalPreco);
        }
    }
}
