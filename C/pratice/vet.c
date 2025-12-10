#include <stdio.h>
#include <string.h>

#define REGISTROS 1000
#define NOMEANIMAL 21
#define NOMEPROP 41

struct animal{
    int codigo;
    char nome[NOMEANIMAL];
    char proprietario[NOMEPROP];
    char especie;
    float peso;
};
typedef struct animal animal;

int leitura(animal animais[]){
    int i = 0;
    int codigo;

    printf("Digite o código do animal (0 para encerrar): ");
    scanf("%d", &codigo);

    while(codigo != 0 && codigo < REGISTROS){
        animais[i].codigo = codigo;
        printf("Digite o nome: ");
        scanf(" %[^\n]", animais[i].nome);

        printf("Digite o nome do proprietário: \n");
        scanf(" %[^\n]", animais[i].proprietario);

        printf("Digite a espécie (c, g, a): \n");
        scanf(" %c", &animais[i].especie);

        printf("Digite o peso: \n");
        scanf("%f", &animais[i].peso);

        i++;

        printf("Digite o código do animal (0 para encerrar): ");
        scanf("%d", &codigo);
    }        

    return i;
}

void achaEspecies(animal animais[], int qtd, char especie){
    for(int i = 0; i < qtd; i++){
        if(animais[i].especie == especie){
            printf("Código do animal: %d\n", animais[i].codigo);
            printf("Nome do animal: %s\n", animais[i].nome);
            printf("Nome do proprietário: %s\n", animais[i].proprietario);
            printf("Peso do animal: %.2f\n", animais[i].peso);
        }
    }
}

void busca(animal animais[], int qtd, char procura[]){

    for(int i = 0; i < qtd; i++){
        if(strcmp(animais[i].proprietario, procura) == 0){
            printf("Código do animal: %d\n", animais[i].codigo);
            printf("Nome do animal: %s\n", animais[i].nome);
            printf("Espécie: %c\n", animais[i].especie);
            printf("Peso do animal: %.2f\n", animais[i].peso);
        }
    }
}

void ordena(animal animais[], int qtd){
    int k, i, min;
    animal aux;

    for(k = 0; k < qtd - 1; k++){
        min = k;
        for(i = k + 1; i < qtd; i++){
            if(strcmp(animais[i].nome, animais[min].nome) < 0)
                min = i;
        }
        if(min != k){
            aux = animais[min];
            animais[min] = animais[k];
            animais[k] = aux;
        }
    }
}

int main(){
    int qtd;
    char especie;
    animal animais[REGISTROS];
    char proprietario[NOMEPROP];

    qtd = leitura(animais);
    ordena(animais, qtd);

    printf("Digite a espécie desejada (c, g, a): \n");
    scanf(" %c", &especie);

    achaEspecies(animais, qtd, especie);

    printf("Digite o nome de um proprietário: \n");
    scanf(" %[^\n]", proprietario);

    busca(animais, qtd, proprietario);

    return 0;
}
