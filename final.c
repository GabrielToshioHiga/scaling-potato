/*
    I'm sowwwy...
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>


// Structs.
// A group of students.
typedef struct Class {
    void (*set_num_students)(struct Class* self, int num_students);
    int (*get_num_students)(struct Class* self);

    int num_students;
} Class;


// The test given to the class.
typedef struct Test {
    void (*set_num_questions)(struct Test* self, int num_questions);
    int (*get_num_questions)(struct Test* self);
    void (*set_answer_key)(struct Test* self, char* answer_key);
    char* (*get_answer_key)(struct Test* self);
    void (*print_answer_key)(struct Test* self);

    int num_questions;
    float question_value;
    char* answer_key;
} Test;


// One student.
typedef struct Student {
    void (*set_answers)(struct Student* self, char* answers);
    int (*get_num_correct)(struct Student* self);
    float  (*get_result)(struct Student* self);
    char* (*get_answers)(struct Student* self);
    int* (*reference_ra)(struct Student* self);
    char** (*reference_answers)(struct Student* self);

    Class* class;
    Test* test;
    int num_correct;
    int ra;
    float result;
    char* answers;
} Student;


// Functions to be encapsulated.
// For the Class.
void set_num_students(Class* self, int num_students);
int get_num_students(Class* self);

// For the Test.
void set_num_questions(Test* self, int num_questions);
int get_num_questions(Test* self);
void set_answer_key(Test* self, char* answer_key);
char* get_answer_key(Test* self);
void print_answer_key(Test* self);

// For the Student.
int* reference_ra(Student* self);
char** reference_answers(Student* self);
void set_answers(Student* self, char* answers); 
int get_num_correct(Student* self);
float get_result(Student* self);
char* get_answers(Student* self);


// Utilitary functions.
// For validation.
int valid_number(int number);
int valid_answer(char answer);


// The main function.
int main() {
    Class class = {.set_num_students = &set_num_students, .get_num_students = &get_num_students};
    Test test = {.set_num_questions = &set_num_questions, .set_answer_key = &set_answer_key, .get_answer_key = &get_answer_key, .get_num_questions = &get_num_questions, .print_answer_key = &print_answer_key};
    Student* students;
    int num_students = 0, num_questions = 0;
    char* answer_key = (char*) malloc(sizeof(char));
    char* answers = (char*) malloc(sizeof(char));
    
    do {
        printf("\n==> Informe o número de questões da prova: ");
        scanf("%d", &num_questions);

        if (!valid_number(num_questions)) {
            printf("\nO número de questões deve ser estritamente positivo. Tente novamente.");
        }
    } while (!valid_number(num_questions));
    test.set_num_questions(&test, num_questions); 

    answer_key = (char*) realloc(answer_key, test.get_num_questions(&test) * sizeof(char));
    answers = (char*) realloc(answers, test.get_num_questions(&test) * sizeof(char));
    if (answer_key == NULL || answers == NULL) {
        printf("\nREALLOC for %d questions returned NULL. Memory allocation failed.\n", test.get_num_questions(&test));
        exit(1);
    }

    printf("\n\nA seguir, precisamos do gabarito.\n");
    for (int i = 0; i < test.get_num_questions(&test); i++) {
        do {
            printf("==> Informe o gabarito da questão %d: ", i + 1);
            scanf(" %c", &answer_key[i]);
            answer_key[i] = tolower(answer_key[i]);

            if (!valid_answer(answer_key[i])) {
                printf("\nResposta inválida. Respostas possíveis: [a, b, c, d, e].");
            }
        } while (!valid_answer(answer_key[i]));
    }
    test.set_answer_key(&test, answer_key);
    test.print_answer_key(&test);

    do {
        printf("\nInsira o número de estudantes: ");
        scanf("%d", &num_students);

        if (!valid_number(num_students)) {
            printf("\nO número de estudantes deve ser estritamente positivo. Tente novamente.");
        }
    } while (!valid_number(num_students));
    class.set_num_students(&class, num_students);

    students = (Student*) calloc(class.get_num_students(&class), sizeof(Student));
    if (students == NULL) {
        printf("\nCALLOC for %d students returned NULL. Memory allocation failed.\n", class.get_num_students(&class));
        exit(1);
    }

    for (int i = 0; i < class.get_num_students(&class); i++) {
        students[i].set_answers = &set_answers; 
        students[i].get_num_correct = &get_num_correct;
        students[i].get_result = &get_result;
        students[i].get_answers = &get_answers;
        students[i].reference_ra = &reference_ra;
        students[i].reference_answers = &reference_answers;
        
        students[i].class = &class;
        students[i].test = &test;
        students[i].answers = (char*) malloc(test.get_num_questions(&test) * sizeof(char));
    }
    
    printf("\n\nCerto. Vamos receber os dados dos estudantes.");
    for (int i = 0; i < class.get_num_students(&class); i++) {
        printf("\n==> Informe o RA do estudante %d: ", i + 1);
        scanf("%d", students[i].reference_ra(&students[i]));

        for (int j = 0; j < test.get_num_questions(&test); j++) {
            

        }
    }



   

    free(answer_key);
    free(students);

    return 0;
}

void set_num_students(Class* self, int num_students) {
    self->num_students = num_students;
    return;
}


int get_num_students(Class* self) {
    return self->num_students;
}


void set_num_questions(Test* self, int num_questions) {
    self->num_questions = num_questions;
    self->question_value = 10.0 / num_questions;
    return;
}


int get_num_questions(Test* self) {
    return self->num_questions;
}


void set_answer_key(Test* self, char* answer_key) {
    self->answer_key = answer_key;
    return;
}


char* get_answer_key(Test* self) {
    return self->answer_key;
}


void print_answer_key(Test* self) {
    printf("\n\tGABARITO");
    printf("\n\tQuestão\tResposta");
    for (int i = 0; i < self->get_num_questions(self); i++) {
        printf("\n\t%d\t%c", i + 1, self->get_answer_key(self)[i]);
    }
    
    return;
}


void set_answers (Student* self, char* answers) {
    self->answers = answers;
    int num_correct = 0;

    for (int i = 0; i < self->test->num_questions; i++) {
        if (self->answers[i] == self->test->answer_key[i]) {
            num_correct += 1;
        }
    }
    
    self->num_correct = num_correct;
    self->result = self->test->question_value * self->num_correct;

    return;
}


int get_num_correct(Student* self) {
    return self->num_correct;
}


float  get_result(Student* self) {
    return self->result;
}


char* get_answers(Student* self) {
    return self->answers;
}


int* reference_ra(Student* self) {
    return &self->ra;
}


char** reference_answers(Student* self) {
    return &self->answers;
}


int valid_answer(char answer) {
    char possible_answers[] = {'a', 'b', 'c', 'd', 'e'};
    int is_valid = 0;
    for (int i = 0; i < sizeof(possible_answers) / sizeof(possible_answers[0]); i++) {
        if (answer == possible_answers[i]) {
            is_valid = 1;
            break;
        }
    }
    
    return is_valid;
}


int valid_number(int number) {
    int is_valid = 0;
    if (number > 0) {
        is_valid = 1;
    }
    return is_valid;
}












