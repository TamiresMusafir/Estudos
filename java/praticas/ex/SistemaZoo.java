package ex;

public class SistemaZoo {
    public static void main(String[] args){
        Animal[] animais = new Animal[3];

        animais[0] = new Leao("Tom", 13);
        animais[1] = new Gato("Garfiel", 18);
        animais[2] = new Gato("Cat Noir", 15);

        Utils.testarSantuario(animais);
    }
}
