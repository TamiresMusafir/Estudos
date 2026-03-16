import java.util.ArrayList;

public class main {
    public static void main(String[] args) {

        //método. 
        //static significa que pertence a uma classe e não a um objeto.

        //tipos primitivos, execeto string. É uma classe
        byte b = 100;
        short s = 10000;
        int integ = 00000;
        long l = 100000L;
        float f = 10.5f;
        double d = 20.5;
        char c = 'A';
        String str = "Tamires";
        boolean bool = true;

        //casting / conversao de tipos

        double resultado = 8.5;
        int resultadoInt = (int)resultado;

        String meuString = "10"/
        int meuInt = Integer.parseInt(meuString);

        //

        int[] colecao = {1,2,3,4,5};

        ArrayList<String> nomes = new ArrayList<>();
        nomes.add("Tamires");
        nomes.add("Carlos");
        nomes.add("Teste");
        nomes.remove("Teste");

        System.out.println(nomes.get(0));
        
        // equal = str.equals("Tamires")
        // str.isBlank()

        // is
        if(str.isBlank()){
            System.out.println("Verdadeiro");
        }else if(str == "Tamires"){
            System.out.println("Tamires");
        }else{
            System.out.println("Falso");
        }

        System.out.println(colecao[0]);

        for(int i = 0; i < nomes.size(); i++){
            System.out.println(nomes.get(i));
        }

        for(int i = 0; i < colecao.length; i++){
            System.out.println(colecao[i]);
        }
    } 
}
