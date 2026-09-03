### Criação e pesquisa utilizando arquivo de índice

1. **Abrir o arquivo de dados** e descobrir a quantidade de registros existentes.

2. **Alocar memória** para armazenar todos os registros, utilizando `sizeof` para determinar o espaço necessário.

3. Fazer uma **leitura sequencial do arquivo**:

   * Ler cada registro do arquivo.
   * Guardar os registros no `array` criado.
   * Armazenar também as informações necessárias para o índice, como o **CEP** e o **endereço/posição do registro no arquivo**.

4. **Ordenar o array de índice pelo CEP**, para que seja possível realizar uma busca binária.

5. **Criar e salvar um arquivo de índice**, contendo, para cada registro, o CEP e sua posição/endereço correspondente no arquivo de dados.

6. Criar um segundo programa para realizar a **pesquisa por CEP**:

   * Abrir o arquivo de índice.
   * Realizar uma **busca binária no arquivo de índice** pelo CEP informado.
   * Encontrar, no índice, a posição/endereço correspondente ao registro.
   * Utilizar `fseek` no **arquivo de dados principal** para ir diretamente até essa posição.
   * Ler o registro associado àquele CEP e exibi-lo.

### Objetivo

O arquivo de dados principal **não será pesquisado diretamente de forma sequencial**. A pesquisa será feita primeiro no **arquivo de índice ordenado por CEP**, utilizando busca binária. Depois que o registro for localizado no índice, seu endereço será utilizado com `fseek` para acessar diretamente o registro correspondente no arquivo de dados.
struct indiceCep{
	char cep[8];
	long pos;
};
