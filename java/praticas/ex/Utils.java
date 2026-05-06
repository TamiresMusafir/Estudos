package ex;

public class Utils {
    public static void testarSantuario(Animal[] animais){
        for(int i = 0; i < animais.length; i++){
            if(animais[i] != null){
                animais[i].emitirSom();

                if(animais[i] instanceof Leao)
                    System.out.println("Cuidado: Animal de grande porte!");

                System.out.println(animais[i]);
            }
        }
    }
}
