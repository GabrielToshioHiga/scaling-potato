#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int num_questoes = 0, num_alunos = 0, num_corretas = 0;
    float valor_questao = 0;

    char saudacoes[][100] = {"Olá, seja bem-vindo ao nosso software\n",
                            "Para iniciarmos, informe o número de questões da prova: "};
    
    for (int i = 0; i < sizeof(saudacoes) / sizeof(saudacoes[0]); i++) {
        printf("%s", saudacoes[i]);
    }

    system("clear");
    
    scanf("%d", &num_questoes);
    valor_questao = 10.0 / num_questoes;
    printf("\nCom %d questões, cada questão vale %.2f.\n", num_questoes, valor_questao);

    printf("\nAgora, precisamos do gabarito das questões...\n\n");

    char gabarito[num_questoes];

    for (int i = 0; i < num_questoes; i++) {
        printf("Informe a resposta da questão %d: ", i + 1);
        scanf(" %c", &gabarito[i]);        
    }

    system("clear");

    printf("O gabarito da prova, então, é: ");
    printf("\nQuestão\tResposta");

    for (int i = 0; i < num_questoes; i++) {
        printf("\n%d\t%c", i + 1, gabarito[i]);
    }

    printf("\nQuantos alunos fizeram a prova? ");
    scanf("%d", &num_alunos);

    printf("Ok... A seguir, receberemos os RAs as respostas de cada um dos %d alunos.\n", num_alunos);

    char respostas_alunos[num_alunos][num_questoes];
    int ras_alunos[num_alunos];
    float resultados_alunos[num_alunos];

    for (int aluno = 0; aluno <  num_alunos; aluno++) {
        num_corretas = 0;
        printf("Informe o RA do aluno %d: ", aluno + 1);
        scanf("%d", &ras_alunos[aluno]);

        for (int questao = 0; questao < num_questoes; questao++) {
            printf("\nQual a resposta dada ao item %d? ", questao + 1);
            scanf(" %c", &respostas_alunos[aluno][questao]);
        }

        for (int questao = 0; questao < num_questoes; questao++) {
            if (respostas_alunos[aluno][questao] == gabarito[questao]) {
                num_corretas += 1;
            }
        }

        resultados_alunos[aluno] = num_corretas * valor_questao;
    }

    system("clear");

    for (int aluno = 0; aluno < num_alunos; aluno++) {
        printf("\nResultado do aluno RA %d:\t%.2f.", ras_alunos[aluno], resultados_alunos[aluno]);
    }






    printf("\n");
    return 0;
}