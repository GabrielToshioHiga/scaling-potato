#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void print_saudacoes(); 
int get_num_questoes();
float get_valor_questao(int num_questoes);
char* get_gabarito(int num_questoes);
void mostra_gabarito(char* gabarito, int num_questoes);
int get_num_alunos();
void pega_respostas_alunos(int num_alunos, int num_questoes, float valor_questao, char* respostas_alunos, int* ras_alunos, float* resultados_alunos, char* gabarito);

void realoca_memoria(void** ptr, int novo_tamanho);
int char_in_vetor(char item, char vetor[], int num_itens_validos);

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Portuguese");

    // Declaração das variáveis necessárias.
    int num_questoes = 0, num_alunos = 0, num_corretas = 0;
    float valor_questao = 0;
    int* ras_alunos;
    float* resultados_alunos;
    char* gabarito;
    char* respostas_alunos;

    // Dá um bem-vindo pro usuário e explica como o programa funciona.
    print_saudacoes();
    
    // Pega o número de questões.
    num_questoes = get_num_questoes();
    
    // Limpa a tela (funciona em alguns SOs, acho que não no Windows).
    // system("clear");

    // Calcula o valor de cada questão.
    valor_questao = get_valor_questao(num_questoes);

    // Pega o gabarito.
    printf("\nAgora, precisamos do gabarito das questões...\n\n");
    gabarito = get_gabarito(num_questoes);

    // system("clear");

    // Mostra o gabarito informado pelo usuário.
    mostra_gabarito(gabarito, num_questoes);

    // Pega o número de alunos que fizeram a prova.
    num_alunos = get_num_alunos();

    printf("Ok... A seguir, receberemos os RAs as respostas de cada um dos %d alunos.\n", num_alunos);

    // char respostas_alunos[num_alunos][num_questoes];
    // int ras_alunos[num_alunos];
    // float resultados_alunos[num_alunos];

    pega_respostas_alunos(num_alunos, num_questoes, valor_questao, respostas_alunos, ras_alunos, resultados_alunos, gabarito);



    // system("clear");

    for (int aluno = 0; aluno < num_alunos; aluno++) {
        printf("\nResultado do aluno RA %d:\t%.2f.", ras_alunos[aluno], resultados_alunos[aluno]);
    }






    printf("\n");
    free(gabarito);
    return 0;
}


void print_saudacoes() {
    char mensagem_boas_vindas[] = "=================================================================================\n"
                                  "Olá, seja bem-vindo ao software de correção de provas objetivas da Espartana!\n"
                                  "Primeiramente, você deverá informar o número de questões da prova.\n"
                                  "Consideramos que a prova vale 10.0 pontos.\n"
                                  "Além disso, todas as questões tem o mesmo valor.\n"
                                  "Em seguida, receberemos o gabarito da prova.\n"
                                  "Com o gabarito, podemos começar a receber as respostas dos alunos.\n"
                                  "Ao final, informaremos o resultado obtido por cada aluno.\n"
                                  ">> Vamos começar! <<\n"
                                  "=================================================================================\n\n";

    printf("%s", mensagem_boas_vindas);
    return;
}


int get_num_questoes() {
/* 
    Função para pegar o número de questões como entrada do usuário.

    Retorna: um número inteiro positivo, o número de questões da prova.
*/
    int num_questoes = 0;
    
    // Repetir o loop até que o número de questões
    // informado pelo usuário seja positivo.
    while (num_questoes <= 0) {
        // Pede e recebe a entrada.
        printf("Informe o número de questões da prova: ");
        scanf("%d", &num_questoes);
    }

    return num_questoes;
}


float get_valor_questao(int num_questoes) {
/*
    Esta função calcula o valor de cada questão.
    
    Params:
        num_questoes: o número de questões na prova.

    Retorna: um float, o valor de cada questão.
*/
    // Calcula o valor de cada questão.
    float valor_questao = 10.0 / num_questoes;
    // Mostra o valor de cada questão para o usuário.
    printf("Com %d questões, cada questão vale %.2f.\n", num_questoes, valor_questao);

    return valor_questao;
}


char* get_gabarito(int num_questoes) {
/*
    Esta função recebe o gabarito da prova.

    Params:
        num_questoes: a quantidade de questões na prova.

    Retorna: um ponteiro para o vetor que contém o gabarito. 
*/

    // Aloca memória com o tamanho necessário.
    char* gabarito = (char*) calloc(num_questoes, sizeof(char));
    
    int resposta_valida = 0;

    // Vetor com as respostas consideradas válidas.
    char respostas_validas[] = {'a', 'b', 'c', 'd', 'e'};
    
    // Loop para pegar os itens de gabarito.
    for (int i = 0; i < num_questoes; i++) {
        // do-while para validação.
        do {
            // Pede e recebe a resposta da questão.
            printf("Informe a resposta da questão %d: ", i + 1);
            scanf(" %c", &gabarito[i]);        

            // Verifica se a resposta informada é uma das respostas válidas.
            resposta_valida = char_in_vetor(gabarito[i], respostas_validas, sizeof(respostas_validas) / sizeof(respostas_validas[0]));

            // Se a resposta for inválida, avisa o usuário.
            if (!resposta_valida) {
                printf("Cada questão deve ter uma resposta de 'a' a 'e'!\n");
            }
        } while (!resposta_valida);
        
    }
    
    // Retorna um ponteiro para o gabarito obtido.
    return gabarito;
}


void mostra_gabarito(char* gabarito, int num_questoes) {
    
    // Mostra o gabarito informado pelo usuário.
    
    printf("O gabarito da prova, então, é: ");
    printf("\n\tQuestão\tResposta");

    for (int i = 0; i < num_questoes; i++) {
        printf("\n\t%d\t%c", i + 1, gabarito[i]);
    }


    return;
}


int get_num_alunos() {
/*
    Esta função pega o número de alunos.

    Retorna: o número de alunos.
*/
    int num_alunos = 0;

    do {
        printf("\nQuantos alunos fizeram a prova? ");
        scanf("%d", &num_alunos);

        if (num_alunos <= 0) {
            printf("O número de alunos deve ser positivo!\n");
        }

    } while (num_alunos <= 0);

    return num_alunos;
}


int char_in_vetor(char item, char vetor[], int num_itens_validos) {
/*
    Esta função verifica se um determinado caracter está ou não em um array de caracteres.

    Parametros:
        resultado: ponteiro de inteiro, a variável de controle usada para validação.
        item: o elemento cuja existência no array se quer verificar.
        vetor: o array em questão.
        num_itens_validos: a quantidade de elementos em 'vetor'.

    Retorna: nada, mas está preparada para modificar uma variável de validação cujo endereço deve ser passado.
*/
    int resultado = 0;
    printf("%d", num_itens_validos);
    for (int i = 0; i < num_itens_validos; i++) {
        if (item == vetor[i]) {
            resultado = 1;
            break;
        }
    }
    return resultado;
}

void pega_respostas_alunos(int num_alunos, int num_questoes, float valor_questao, char* respostas_alunos, int* ras_alunos, float* resultados_alunos, char* gabarito) {
    void* aux_1 = &respostas_alunos;
    void* aux_2 = &ras_alunos;
    void* aux_3 = &resultados_alunos;
    
    realoca_memoria(aux_1, num_alunos * num_questoes * sizeof(char));
    realoca_memoria(aux_2, num_alunos * sizeof(int));
    realoca_memoria(aux_3, num_alunos * sizeof(float));

    int num_corretas = 0;

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


    return;
}

void realoca_memoria(void** ptr, int novo_tamanho) {
    void* ptr_aux;

    ptr_aux = realloc(*ptr, novo_tamanho);

    if (ptr_aux == NULL) {
        exit(1);
    } else {
        *ptr = ptr_aux;
    }

}













