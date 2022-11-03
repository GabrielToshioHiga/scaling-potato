#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>


// ==============================
// Structs.

// This struct represents the grade, the class, the group
// of students, with its 
// many students and the test given.
typedef struct Grade {
    int num_students;
} Grade;


// This struct represents the test.
typedef struct Test {
    int num_questions;
    float question_value;
    char* answer_key;
} Test;


// This struct represents a student.
typedef struct Student {

    Grade* grade;
    Test* test;
    int ra;
    int num_correct;
    float result;
    char* answers;
} Student;


// ==============================
// Functions.
// "Getters", or, in this case, "printers".
void print_gabarito(Grade* grade);
void print_results(Grade* grade);

// Setters.
void set_num_questions(Grade* grade);
void set_question_value(Grade* grade);
void set_num_students(Grade* grade);
void set_gabarito(Grade* grade);
void set_students_data(Grade* grade);
void set_students_results(Grade* grade);


// Utilities.
int valid_answer(char item); 
int valid_ra(int ra);


int main() { 
    Grade grade; 
    grade.test = (Test*) calloc(1, sizeof(Test));

    set_num_questions(&grade);
    set_question_value(&grade);
    printf("A prova tem %d questões.\n", grade.test->num_questions);
    printf("Com %d questões, cada questão vale %.2f.\n", grade.test->num_questions, grade.test->question_value);
    set_gabarito(&grade);

    print_gabarito(&grade);

    set_num_students(&grade);
    printf("Certo. A turma tem %d alunos.\n", grade.num_students);

    grade.students = (Student*) calloc(grade.num_students, sizeof(Student));

    set_students_data(&grade);
    set_students_results(&grade);

    print_results(&grade);


    free(grade.students);
    free(grade.test);

    return 0;
}


void print_gabarito(Grade* grade) {
    printf("\n\t>>>> GABARITO <<<<\n");
    printf("\n\tQuestão\tResposta");
    for (int i = 0; i < grade->test->num_questions; i++) {
        printf("\n\t%d\t%c", i + 1, grade->test->answer_key[i]);
    }

    return;
}


void print_results(Grade* grade) {
    printf("\n\tRA\tAcertos\tResultado"); 
    for (int i = 0; i < grade->num_students; i++) {
        printf("\n\t%d\t%d\t%.2f", grade->students[i].ra, grade->students[i].num_correct, grade->students[i].result);
    }    

    return;
}


void set_num_questions(Grade* grade) {
    int num = 0;

    do {
        printf("Informe o número de questões: ");
        scanf("%d", &num); 

        if (num <= 0) {
            printf("O número de questões deve ser positivo!");
        }

    } while (num <= 0);

    grade->test->num_questions = num;
    
    return;
}


void set_question_value(Grade* grade) {
    grade->test->question_value = 10.0 / grade->test->num_questions;
    return;
}


void set_gabarito(Grade* grade) {
    char* key = (char*) calloc(grade->test->num_questions, sizeof(char));
    int val = 0;
    
    printf("Precisamos do gabarito da prova.\n");
    for (int i = 0; i < grade->test->num_questions; i++) {
        do {
            printf("Informe a resposta da questão %d: ", i + 1);
            scanf(" %c", &key[i]);
            key[i] = tolower(key[i]);
            val = valid_answer(key[i]);
        } while (val == 0);
    }

    grade->test->answer_key = key;

    return;
}


void set_num_students(Grade* grade) {
    int num = 0;
    do {
        printf("\n\nInforme o número de alunos na turma: ");
        scanf("%d", &num);

        if (num <= 0) {
            printf("Você inseriu: %d. O número de alunos deve ser positivo.\n", num);
        }
    } while (num <= 0);

    grade->num_students = num;

    return;
}


void set_students_data(Grade* grade) {
    int val = 0, RA = 0;
    char resposta;

    for (int i = 0; i < grade->num_students; i++) {
        do {
            printf("Informe o RA do aluno: ");
            scanf("%d", &RA);
            val = valid_ra(RA);
        } while (val == 0);

        grade->students[i].ra = RA;
        grade->students[i].answers = (char*) calloc(grade->test->num_questions, sizeof(char));

        for (int j = 0; j < grade->test->num_questions; j++) {
            do {
                printf("Informe a resposta dada pelo aluno (RA %d) para a questão %d: ", grade->students[i].ra, j + 1);
                scanf(" %c", &resposta);
                val = valid_answer(resposta);
            } while (val == 0);
            grade->students[i].answers[j] = resposta;
        }
    }

    return;
}


void set_students_results(Grade* grade) {
    for (int i = 0; i < grade->num_students; i++) {
        grade->students[i].num_correct = 0;
        for (int j = 0; j < grade->test->num_questions; j++) {
            if (grade->students[i].answers[j] == grade->test->answer_key[j]) {
                grade->students[i].num_correct += 1;
            }
        }
        grade->students[i].result = grade->students[i].num_correct * grade->test->question_value;
    }

    return;
}


int valid_answer(char item) {
/*
    This functions validates the answer inputs.

    Params:
        item: the input that must be validated.

    Returns: an integer, 1 for valid and 0 for invalid input.
*/
    char possible_answers[] = {'a', 'b', 'c', 'd', 'e'};
    int is_in = 0;

    for (int i = 0; i < sizeof(possible_answers) / sizeof(possible_answers[0]); i++) {
        if (item == possible_answers[i]) {
            is_in = 1;
            break;
        }
    }

    if (is_in == 0) {
        printf("A resposta informada não é válida.\n");
    }

    return is_in;
}


int valid_ra(int ra) {
    int is_valid = 0;
    if (ra > 0) {
        is_valid = 1;
    }
    return is_valid;
}



















