#include <stdio.h>

void mensagens(float media){
    printf("A média do aluno é: %.1f", media);

    if (media > 9.5){
        printf("Parabéns!");
    }
}

int alunos(int qtdAlunos){
    int matricula, nota1, nota2, aprovados = 0;
    float media;

    for(int i = 1; i <= qtdAlunos; i++){
        printf("Digite a matrícula do aluno %d: \n", i);
        scanf("%d", &matricula);

        printf("Digite a primeira nota do aluno %d: \n", i);
        scanf("%d", &nota1);

        printf("Digite a segunda nota do aluno %d: \n", i);
        scanf("%d", &nota2);

        media = (nota1 + nota2) / 2.0;

        printf("A matrícula do aluno é: %d\n", matricula);
        printf("A média do aluno é: %.1f\n", media);

        if(media >= 7){
            printf("O aluno está aprovado!\n");
            aprovados++;
        }else if(media <= 3){
            printf("O aluno está em final!\n");
        }else{
            printf("O aluno está reprovado!\n");
        }
    }

    mensagens(media);

    return aprovados;
}

int main(){
    int qtdAlunos, totalAprovados;

    printf("\nDigite a quantidade de alunos da turma:\n");
    scanf("%d", &qtdAlunos);

    totalAprovados = alunos(qtdAlunos);

    printf("\n O total de alunos aprovados é: %d", totalAprovados);

    return 0;
}