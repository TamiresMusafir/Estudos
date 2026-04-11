package heranca;

public class teste {
    public static void main(String[] args){}

        Animal X [] = new Animal[3];
        x[0] = new Leao();
        x[0].correr();
        x[1] = new Urso();
        x[1].correr();
        x[2] = x[1]
        x[2].correr();
        if(x[0] instanceof Leao){
            Leao U = (Leao) x[0];
            U.rugir();
        }

        //saida

        //leao correndo
        //animal correndo pois urso nao tem correr
        //animal correndo pois urso nao tem correr
        //leao rugir
    }
}