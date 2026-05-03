package exercicios.aula3;

public class Utils {
    public static double calculaMedia(double a, double b){
        double media;

        media = (a + b) / 2;

        return media;
    }

    public static double calculaMedia(double a, double b, double c){
        double media;

        media = (a + b + c) / 3;

        return media;
    }

    public static double calculaMedia(double a, double b, double c, double d){
        double media;

        media = (a + b + c + d) / 4;

        return media;
    }

    public static void main(String[] args){
        double media1 = calculaMedia(5,6);
        double media2 = calculaMedia(5,6, 7);
        double media3 = calculaMedia(5,6, 7, 9);

        System.out.println("A média 1 foi:" + media1);
        System.out.println("A média 2 foi:" + media2);
        System.out.println("A média 3 foi:" + media3);
    }
}

