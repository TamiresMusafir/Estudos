package ex.teste2;

public class CalculadoraLocacao {
    public static double[] processarLocacoes(Veiculo[] frota, int dias){
        double soma = 0;
        double somaDiaria = 0;

        for(int i = 0; i < frota.length; i++){
            soma += frota[i].getValorLocacao(dias); 
            somaDiaria += frota[i].getValorDiaria();
        }

        double mediaDiaria = somaDiaria / frota.length;

        double[] somas = new double[2];

        somas[0] = soma;
        somas[1] = mediaDiaria;

        return somas;
    }
}
