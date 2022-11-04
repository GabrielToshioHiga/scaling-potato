/*
    I'm sowwwy...
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


// Structs.
// Not a programming class, but a class of students.
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

    Class* class;
    Test* test;
    int num_correct;
    float result;
    char* answers;
} Student;


// Functions that will get encapsulated.
// For the Class.
void set_num_students(Class* self, int num_students);
int get_num_students(Class* self);

// For the Test.
void set_num_questions(Test* self, int num_questions);
int get_num_questions(Test* self);
void set_answer_key(Test* self, char* answer_key);
char* get_answer_key(Test* self);

// For the Student.
void set_answers(Student* self, char* answers); 
int get_num_correct(Student* self);
float get_result(Student* self);


int main() {
    Class class = {.set_num_students = &set_num_students, .get_num_students = &get_num_students};
    Test test = {.set_num_questions = &set_num_questions, .set_answer_key = &set_answer_key, .get_answer_key = &get_answer_key, .get_num_questions = &get_num_questions};

    int num_students = 0;
    int num_questions = 0;
    Student* students;

    char* answer_key = (char*) malloc(sizeof(char));

    printf("\nInforme o número de questões da prova: ");
    scanf("%d", &num_questions);
    printf("Número de questões informado: %d.", num_questions);

    test.set_num_questions(&test, num_questions); 

    answer_key = (char*) realloc(answer_key, test.get_num_questions(&test) * sizeof(char));

    if (answer_key == NULL) {
        printf("\nCALLOC for %d questions returned NULL.\n", test.get_num_questions(&test));
        exit(1);
    }

    printf("\nA seguir, precisamos do gabarito.\n");
    for (int i = 0; i < test.get_num_questions(&test); i++) {
        printf("Informe o valor da questão %d: ", i + 1);
        scanf(" %c", &answer_key[i]);
    }

    test.set_answer_key(&test, answer_key);

    free(answer_key);


    printf("\nInsira o número de estudantes: ");
    scanf("%d", &num_students);
    class.set_num_students(&class, num_students);

    students = (Student*) calloc(class.get_num_students(&class), sizeof(Student));
    if (students == NULL) {
        printf("\nCALLOC for %d students returned NULL.\n", class.get_num_students(&class));
        exit(1);
    }
   



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


















