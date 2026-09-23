#include <stdio.h>

struct Registro{
    int id;
    char nome[31];
    char especie[21];
    int idade;
    float peso;
};
typedef struct Registro Registro;

void buscarRegistro(FILE *f, int id){
    Registro r;

    while(fread(&r, sizeof(Registro), 1, f) == 1){

        if(id == r.id){
            printf("ID: %d - Nome: %s - Especie: &s - Idade: %d - Peso: %f", r.id, r.nome, r.especie, r.idade, r.peso);
            return;
        }
    }
    printf("ID não encontrado");
}

void incluirRegistro(FILE *f){
    Registro p, r;

    printf("Informe o id: \n");
    scanf("%d", &r.id);

    printf("Informe o nome: \n");
    scanf("%s", &r.nome);

    printf("Informe a espécie: \n");
    scanf("%s", &r.especie);

    printf("Informe a idade: \n");
    scanf("%d", &r.idade);

    printf("Informe o peso: \n");
    scanf("%f", &r.peso);

    while(fread(&p, sizeof(Registro), 1, f) == 1){
        if(r.id == p.id){
            printf("ID repetido. Insira outro.");
            return;
        }
    }
    fseek(f, 0, SEEK_END);
    fwrite(&r, sizeof(Registro), 1, f);
}

void alterarRegistro(FILE *f){
    Registro r;
    int id;

    printf("Digite o ID correspondente à alteração: ");
    scanf("%d", &id);

    while(fread(&r, sizeof(Registro), 1, f) == 1){

        if(id == r.id){
            r.id = id;
            printf("ID: %d - Nome: %s - Especie: &s - Idade: %d - Peso: %f", r.id, r.nome, r.especie, r.idade, r.peso);
            printf("Digite os novos dados: \n");

            printf("Informe o nome: \n");
            scanf("%s", &r.nome);

            printf("Informe a espécie: \n");
            scanf("%s", &r.especie);

            printf("Informe a idade: \n");
            scanf("%d", &r.idade);

            printf("Informe o peso: \n");
            scanf("%f", &r.peso);

            fseek(f, -sizeof(Registro), SEEK_CUR);
            fwrite(&r, sizeof(Registro), 1, f);

            return;
        }
    }
    printf("ID não encontrado");
}

int main(){
    FILE *f = fopen("registros.dat", "r+b");
    int id;

    printf("Informe o id para procurar: ");
    scanf("%d", &id);

    buscarRegistro(f, id);
    incluirRegistro(f);
    alterarRegistro(f);

    return 0;
}
