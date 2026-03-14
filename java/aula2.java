package aula2;

public class aula2{
    public static void main(String[] args){
        long k = 13382216899L;
        byte b1 = 127;
        System.out.println(b1);
        short b2 = 128;
        short c1 = 811;
        byte b3 = (byte) c1;
        System.out.println(b3);
        System.out.println(k); 

        //Condições

        int count = 4;

        if(count < 0){

        } else if (count > 10){

        } else {

        }

        // Loopings

        for (int i = 0; i < 10; i++){
            System.out.println("rodada" + i);
        }
        System.out.println("Finalmente!");

        for(int i = 0; i < 10; i++){
            if(i==3){
                continue;
            }
            System.out.println(i);
        }

    }
}