package getset;

public class main {
    public static void main(String[] args) {
        Leao lambao = new Leao();
        lambao.setNome("Sunga"); // Passando o nome via método
        System.out.println(lambao.getNome());
        
        lambao.setIdade(8); // Passando a idade via método
        System.out.println(lambao.getIdade());
    } 
}
