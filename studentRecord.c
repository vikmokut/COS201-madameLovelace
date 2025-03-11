#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

// Structure for student record
typedef struct {
    char name[50];
    char student_id[20];
    int level;
    float score;
    char grade;
} Student;

// Function prototypes
void registration();
void save(Student student);
void resultChecker();
void displayRecords();
void analyze();
void editRecords();
void sortedScores();
void greetUser();

int main() {
    greetUser();
    int choice;
    
    while (1) {
        printf("\nStudent Record System\n");
        printf("1. Register Student\n");
        printf("2. Check Result\n");
        printf("3. Display Student Records\n");
        printf("4. Analyze Scores\n");
        printf("5. Edit Student Records\n");
        printf("6. Sort Scores\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: registration(); break;
            case 2: resultChecker(); break;
            case 3: displayRecords(); break;
            case 4: analyze(); break;
//            case 5: editRecords(); break;
//            case 6: sortedScores(); break;
            case 7: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void greetUser() {
    char name[50];
    printf("Welcome to the Student Record System!\n");
    printf("Enter your name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Hello, %s!\n", name);
}

void registration() {
    Student student;
    printf("Enter Student Name: ");
    fgets(student.name, 50, stdin);
    student.name[strcspn(student.name, "\n")] = 0;
    printf("Enter Student ID: ");
    scanf("%s", student.student_id);
    printf("Enter Level: ");
    scanf("%d", &student.level);
    printf("Enter Score: ");
    scanf("%f", &student.score);
    student.grade = (student.score >= 40) ? 'P' : 'F';
    save(student);
    printf("Student registered successfully!\n");
}

void save(Student student) {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s %s %d %.2f %c\n", student.name, student.student_id, student.level, student.score, student.grade);
    fclose(file);
}

void resultChecker() {
    char student_id[20];
    Student student;
    int found = 0;
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }
    printf("Enter Student ID: ");
    scanf("%s", student_id);
    while (fscanf(file, "%s %s %d %f %c", student.name, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
        if (strcmp(student.student_id, student_id) == 0) {
            printf("Result: %s\n", (student.grade == 'P') ? "PASS" : "FAILED");
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) printf("Student ID not found!\n");
}

void displayRecords() {
    char student_id[20];
    Student student;
    int found = 0;
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }
    printf("Enter Student ID: ");
    scanf("%s", student_id);
    while (fscanf(file, "%s %s %d %f %c", student.name, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
        if (strcmp(student.student_id, student_id) == 0) {
            printf("\nStudent Name: %s\nStudent ID: %s\nLevel: %d\nScore: %.2f\nGrade: %c\n", student.name, student.student_id, student.level, student.score, student.grade);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) printf("Student ID not found!\n");
}

void analyze() {
    Student student;
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }
    float total = 0, count = 0;
    while (fscanf(file, "%s %s %d %f %c", student.name, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
        total += student.score;
        count++;
    }
    fclose(file);
    if (count == 0) {
        printf("No records found!\n");
    } else {
        printf("Mean Score: %.2f\n", total / count);
    }
}

// Additional functions (editRecords, sortedScores) will be implemented later.

