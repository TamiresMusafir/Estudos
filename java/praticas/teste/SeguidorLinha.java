package teste;

public class SeguidorLinha extends Robo{
    int numSensores;

    public SeguidorLinha(String id){
        super(id);
    }

    public String status(){
        return super.status() + " | Número de sensores: " + numSensores;
    }
}
