package livros;

import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;

public class CatalogoLivros {
    public static void main(String[] args){
        Map<String, Autor> autores = new HashMap<>();

        Autor a1 = new Autor("JK Rowling", "jkrowling@gmail.com");
        Autor a2 = new Autor("Tamires Barbosa", "autoratamiresbarbosa@gmail.com");

        Livro l1 = new Livro("Harry Potter e a Pedra Filosofal", 60);
        Livro l2 = new Livro("Harry Potter e a Câmara Secreta", 65);
        Livro l3 = new Livro("A Viajante: O Outro Mundo", 65);
        Livro l4 = new Livro("A Viajante: A Ordem de Mercúrio", 70);

        a1.getLivros().add(l1);
        a1.getLivros().add(l2);
        a2.getLivros().add(l3);
        a2.getLivros().add(l4);

        autores.put(a1.getNome(), a1);
        autores.put(a2.getNome(), a2);

        relatorioDeLivros(autores);
    }

    public static void relatorioDeLivros(HashMap mapa){

        Iterator<Autor> it = mapa.values().iterator();
        while(it.hasNext()){
            Autor autor = it.next();

            double soma = 0;

            Iterator<Livro> itLivros = autor.getLivros().iterator();

            while(itLivros.hasNext()){
                Livro livros = itLivros.next();

                soma += livros.getPreco();
            }

            System.out.println(autor.getNome() + " - " + soma);
        }
    }
}
