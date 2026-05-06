package teste;

public class Sumo extends Robo {
    double forcaEmpuxo;

    public Sumo(String id){
        super(id);
    }

    public Sumo(String id, String nome){
        super(id);
        setNome(nome);
        setPeso(1.0);
    }
        

    public String status(){
        return super.status() + " | Força do empuxo: " + forcaEmpuxo;
    }
}
