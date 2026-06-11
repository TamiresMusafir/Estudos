package praticas.paises;

import java.util.ArrayList;
import java.util.List;

public class CriaPaises{
    public List<Pais> retornaPaises(){
        Pais canada = new Pais("CAN", "Canada", 998467.0); 
        Pais eua = new Pais("EUA", "Estados Unidos da América", 9371174.0);
        Pais mexico = new Pais("MEX", "Estados Unidos do México", 197255.0);

        List<Pais> paises = new ArrayList<>();
        paises.add(canada);
        paises.add(eua);
        paises.add(mexico);

        canada.adicionaFronteira(eua);
        eua.adicionaFronteira(canada);
        eua.adicionaFronteira(mexico);
        mexico.adicionaFronteira(eua);

        return paises;
    }

    public List<Pais> retornaPaises(String[] dados){
        
    }
}