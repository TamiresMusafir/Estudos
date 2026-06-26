package energia;

public class MedicaoEnergia {
    private String id;
    private String nome;
    private double energiaGerada;

    public MedicaoEnergia(String id, String nome, double energiaGerada) {
        this.id = id;
        this.nome = nome;
        this.energiaGerada = energiaGerada;
    }

    // Getters
    public String getId() {
        return id;
    }

    public String getNome() {
        return nome;
    }

    public double getEnergiaGerada() {
        return energiaGerada;
    }

    // Setters
    public void setId(String id) {
        this.id = id;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setEnergiaGerada(double energiaGerada) {
        this.energiaGerada = energiaGerada;
    }
}
