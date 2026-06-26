package pesquisa;

import java.util.HashMap;
import java.util.Iterator;

public class SistemaPesquisa {
    public static void main(String[] args) {
        HashMap grupos = new HashMap();

        GrupoPesquisa g1 = new GrupoPesquisa("#1", "OsKu");
        GrupoPesquisa g2 = new GrupoPesquisa("G2", "KaraDeKao");

        Projeto p1 = new Projeto("StarLabs", 50000);
        Projeto p2 = new Projeto("SHIELD", 50000);
        Projeto p3 = new Projeto("KUZIN", 50000);
        Projeto p4 = new Projeto("BUCEPAU", 50000);

        g1.getProjetos().add(p1);
        g1.getProjetos().add(p2);
        g2.getProjetos().add(p3);
        g2.getProjetos().add(p4);

        grupos.put(g1.getCodigo(), g1);
        grupos.put(g2.getCodigo(), g2);

        relatorioDeFinanciamento(grupos);
    }

    public static void relatorioDeFinanciamento(HashMap mapa){

        Iterator it = mapa.keySet().iterator(); // ESQUECE SEMPRE

        while(it.hasNext()){
            double soma = 0;

            String codigo = (String) it.next();

            GrupoPesquisa grupo = (GrupoPesquisa) mapa.get(codigo);

            Iterator it = grupo.iterator();
        }

    }
}
