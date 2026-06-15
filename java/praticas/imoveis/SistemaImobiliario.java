package praticas.imoveis;

import java.util.Map;
import java.util.HashMap;

public class SistemaImobiliario {
    public static void main(String[] args){
        Map<String, Pessoa> pessoas = new HashMap<>();

        Pessoa p1 = new Pessoa("14869535798", "Rachel");
        Pessoa p2 = new Pessoa("14512952774", "Jake");

        Imovel i1 = new Imovel("Travessa dos Pombos", 60000);
        Imovel i2 = new Imovel("Travessa dos Patos", 90000);
        Imovel i3 = new Imovel("Avenida das Formigas", 70000);
        Imovel i4 = new Imovel("Avenida das Abelhas", 80000);

        p1.addImoveis(i1);
        p1.addImoveis(i2);
        p2.addImoveis(i3);
        p2.addImoveis(i4);

        pessoas.put(p1.getCpf(), p1);
        pessoas.put(p2.getCpf(), p2);

        relatorioDeImoveis(pessoas);
    }
}
