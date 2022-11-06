/*
    I'm sowwwy...
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>


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
    float (*get_question_value)(struct Test* self);

    int num_questions;
    float question_value;
    char* answer_key;
} Test;


// One student.
typedef struct Student {
    int (*get_ra)(struct Student* self);
    int (*get_num_correct)(struct Student* self);
    float (*get_result)(struct Student* self);

    Class* class;
    Test* test;
    int ra;
    char* answers;
} Student;


// Initializers.
Class class_init();
Test test_init();
Student student_init(Class* class, Test* test, int ra, char* answers);

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
float get_question_value(Test* self);

// For the Student.
int get_ra(Student* self);
int get_num_correct(Student* self);
float get_result(Student* self);


// Utilitary functions.
// For validation.
int valid_number(int number);
int valid_answer(char answer);

void print_welcome();

// The main function.
int main() {
    // Set the language to use portuguese symbols.
    setlocale(LC_ALL, "Portuguese");

    // Initialize the first structs.
    Class class = class_init();
    Test test = test_init();

    // Initialize a pointer to the students.
    Student* students = (Student*) malloc(sizeof(Student));

    // Initialize variables.
    int num_students = 0, num_questions = 0, ra = 0;
    char* answer_key = (char*) malloc(sizeof(char));
    char* answers = (char*) malloc(sizeof(char));

    // Print the welcome message and the instructions.
    print_welcome();
    
    // Get the number of questions, validate it and store it in the test struct.
    do {
        printf("\n==> Informe o número de questões da prova: ");
        scanf("%d", &num_questions);

        if (!valid_number(num_questions)) {
            printf("\nO número de questões deve ser estritamente positivo. Tente novamente.");
        }
    } while (!valid_number(num_questions));
    test.set_num_questions(&test, num_questions); 

    // Reallocate memory for both the answer key and the answers of the students, according to the number of questions.
    answer_key = (char*) realloc(answer_key, test.get_num_questions(&test) * sizeof(char));
    answers = (char*) realloc(answers, test.get_num_questions(&test) * sizeof(char));
    if (answer_key == NULL || answers == NULL) {
        printf("\nREALLOC for %d questions returned NULL. Memory allocation failed.\n", test.get_num_questions(&test));
        exit(1);
    }

    // Get the answer key, bring each input to lowercase, validate it and store it in the test struct.
    printf("\nA seguir, precisamos do gabarito.\n");
    for (int i = 0; i < test.get_num_questions(&test); i++) {
        do {
            printf("==> Informe o gabarito da questão %d: ", i + 1);
            scanf(" %c", &answer_key[i]);
            answer_key[i] = tolower(answer_key[i]);

            if (!valid_answer(answer_key[i])) {
                printf("\nResposta inválida. Respostas possíveis: [a, b, c, d, e].\n");
            }
        } while (!valid_answer(answer_key[i]));
    }
    test.set_answer_key(&test, answer_key);
    // Print the answer key.
    printf("\n");
    test.print_answer_key(&test);

    // Get the number of students, validate it and store it in the class struct.
    do {
        printf("\nInsira o número de estudantes: ");
        scanf("%d", &num_students);

        if (!valid_number(num_students)) {
            printf("\nO número de estudantes deve ser estritamente positivo. Tente novamente.");
        }
    } while (!valid_number(num_students));
    class.set_num_students(&class, num_students);

    // Allocate memory according to the number of students.
    students = (Student*) realloc(students, class.get_num_students(&class) * sizeof(Student));
    if (students == NULL) {
        printf("\nCALLOC for %d students returned NULL. Memory allocation failed.\n", class.get_num_students(&class));
        exit(1);
    }

    // Get the RA and the answers for each student. Each student is represented by a struct, 
    // initialized at the end of the outermost for loop.
    printf("\n\nCerto. Vamos receber os dados dos %d estudantes.", class.get_num_students(&class));
    for (int i = 0; i < class.get_num_students(&class); i++) {
        do {
            printf("\n==> Informe o RA do estudante %d: ", i + 1);
            scanf("%d", &ra);

            if (!valid_number(ra)) {
                printf("\nO RA deve ser estritamente positivo. Tente novamente.");
            }
        } while (!valid_number(ra));

        for (int j = 0; j < test.get_num_questions(&test); j++) {
            do {
                printf("\n==> Informe a resposta dada à questão %d: ", j + 1);
                scanf(" %c", &answers[j]);
                answers[j] = tolower(answers[j]);

                if (!valid_answer(answers[j])) {
                    printf("\nResposta inválida. Respostas possíveis: [a, b, c, d, e].");
                }
            } while(!valid_answer(answers[j]));
        }

        students[i] = student_init(&class, &test, ra, answers);
        
    }


    printf("\n\nOk. Vamos aos resultados.");
    printf("\n\tRA\tAcertos\tNota");
    for (int i = 0; i < class.get_num_students(&class); i++) {
        printf("\n\t%d\t%d\t%.2f", students[i].get_ra(&students[i]), students[i].get_num_correct(&students[i]), students[i].get_result(&students[i]));
    }

    printf("\n");   

    // Free allocated memory.
    for (int i = 0; i < class.get_num_students(&class); i++) {
        free(students[i].answers);
    }
    free(answer_key);
    free(answers);
    free(students);

    return 0;
}


void print_welcome() {
    char welcome_message[] = "\n=================================================================================\n"
                             "Olá, seja bem-vindo ao software de correção de provas objetivas da Espartana!\n"
                             "Primeiramente, você deverá informar o número de questões da prova.\n"
                             "Consideramos que a prova vale 10.0 pontos.\n"
                             "Além disso, todas as questões tem o mesmo valor.\n"
                             "Em seguida, receberemos o gabarito da prova.\n"
                             "Com o gabarito, podemos começar a receber as respostas dos alunos.\n"
                             "Ao final, informaremos o resultado obtido por cada aluno.\n"
                             ">> Vamos começar! <<\n"
                             "=================================================================================\n\n";

    printf("%s", welcome_message);
    return;
}


Class class_init() {
    Class class = {.set_num_students = &set_num_students, .get_num_students = &get_num_students, .num_students = 0};
    return class;
}


Test test_init() {
    Test test = {.set_num_questions = &set_num_questions, .set_answer_key = &set_answer_key, .get_answer_key = &get_answer_key, .get_num_questions = &get_num_questions, .get_question_value = &get_question_value, .print_answer_key = &print_answer_key};
    return test;
}


Student student_init(Class* class, Test* test, int ra, char* answers) {
    Student student;

    student.get_num_correct = &get_num_correct;
    student.get_result = &get_result;
    student.get_ra = &get_ra;
        
    student.class = class;
    student.test = test;
    student.ra = ra;
    student.answers = (char*) malloc(student.test->get_num_questions(student.test) * sizeof(char));
    if (student.answers == NULL) {
        printf("\nMALLOC for %d students failed during Student struct instantiation. Memory allocation failed.", student.class->get_num_students(student.class));
        exit(1);
    }
    
    for (int i = 0; i < student.test->get_num_questions(student.test); i++) {
        student.answers[i] = answers[i];
    }

    return student;
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


float get_question_value(Test* self) {
    return 10.0 / self->get_num_questions(self);
}


int get_num_correct(Student* self) {
    int num_correct = 0;
    for (int i = 0; i < self->test->get_num_questions(self->test); i++) {
        if (self->answers[i] == self->test->get_answer_key(self->test)[i]) {
            num_correct += 1;
        }
    }
    return num_correct;
}


int get_ra(Student* self) {
    return self->ra;
}


float get_result(Student* self) {
    return self->get_num_correct(self) * self->test->get_question_value(self->test);
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












