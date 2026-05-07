package ex.prova2501;

public class Utils {
    public static double[] media(ItemPet[] ped){
        double somaFinal = 0;
        double somaPreco = 0;
        
        for(int i = 0; i < ped.length; i++){
            somaFinal += ped[i].getPrecoFinal();
            somaPreco += ped[i].getPreco();
        }

        double mediaFinal = somaFinal / ped.length;
        double mediaPreco = somaPreco / ped.length;

        double[] medias = new double[2];

        medias[0] = mediaFinal;
        medias[1] = mediaPreco;

        return medias;
    }
}
