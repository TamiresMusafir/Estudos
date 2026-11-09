
import java.io.*; // Importa as classes necessárias para trabalhar com arquivos e escrita de dados.

public class Misterio
{
    // Recebe um inteiro e escreve seus 4 bytes na ordem invertida (little-endian).
    public static void escreveIntInvertido(DataOutputStream dout, int x) throws IOException
    {
        // Separa os 4 bytes do inteiro usando máscaras (&) e deslocamentos (>>).
        int b4 = ( x & 0xff000000 ) >> 24;
        int b3 = ( x & 0x00ff0000 ) >> 16;
        int b2 = ( x & 0x0000ff00 ) >> 8;
        int b1 = ( x & 0x000000ff );

        // Escreve os bytes do menos significativo para o mais significativo.
        dout.write(b1);
        dout.write(b2);
        dout.write(b3);
        dout.write(b4);
    }

    // Recebe um inteiro e escreve apenas seus 2 bytes na ordem invertida.
    public static void escreveInt2Invertido(DataOutputStream dout, int x) throws IOException
    {
        int b2 = ( x & 0x0000ff00 ) >> 8;
        int b1 = ( x & 0x000000ff );

        dout.write(b1);
        dout.write(b2);
    }

    public static void main(String args[])
    {
        // Declara os objetos responsáveis pela escrita no arquivo.
        OutputStream saida = null;
        DataOutputStream dout = null;

        try
        {
            // Cria o arquivo teste.bmp para escrita.
            saida = new FileOutputStream("teste.bmp");

            // Permite escrever dados primitivos e bytes no arquivo.
            dout = new DataOutputStream(saida);

            // Escreve a identificação do formato BMP: as letras B e M.
            dout.write((byte)'B');
            dout.write((byte)'M');

            // Cabeçalho do BMP:
            escreveIntInvertido(dout,800*600*3+54); // Tamanho total do arquivo: pixels + cabeçalho.
            dout.writeInt(0);                      // Campo reservado (valor zero).
            escreveIntInvertido(dout,54);          // Posição onde começa a imagem (54 bytes).

            escreveIntInvertido(dout,40);          // Tamanho do segundo cabeçalho.
            escreveIntInvertido(dout,800);         // Largura: 800 pixels.
            escreveIntInvertido(dout,600);         // Altura: 600 pixels.
            escreveInt2Invertido(dout,1);           // Número de planos de cor.
            escreveInt2Invertido(dout,24);          // Bits por pixel: 24 bits (3 bytes).
            escreveIntInvertido(dout,0);            // Compressão: nenhuma.
            escreveIntInvertido(dout,800*600*3);    // Tamanho dos dados da imagem.
            escreveIntInvertido(dout,0);            // Resolução horizontal.
            escreveIntInvertido(dout,0);            // Resolução vertical.
            escreveIntInvertido(dout,0);            // Número de cores da paleta.
            escreveIntInvertido(dout,0);            // Número de cores importantes.

            // Percorre as 600 linhas da imagem.
            for(int i = 0; i < 600; i++)
            {
                // Calcula a intensidade da cor para a linha atual.
                // O valor varia de aproximadamente 255 até 0.
                int cor = ((600-i)*0xff)/600;

                // Percorre os 800 pixels de cada linha.
                for(int j = 0; j < 800; j++)
                {
                    // Escreve os 3 componentes de cor de cada pixel.
                    // A ordem BMP de 24 bits é B (azul), G (verde), R (vermelho).
                    dout.write(cor); // Azul.
                    dout.write(cor); // Verde.
                    dout.write(0);   // Vermelho.
                }
            }

            // Fecha os fluxos e finaliza a escrita do arquivo.
            dout.close();
            saida.close();
        }
        catch(IOException ex)
        {
            // Exibe detalhes caso ocorra algum erro de entrada/saída.
            ex.printStackTrace();
        }
    }
}
