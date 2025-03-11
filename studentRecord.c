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

void sortedScores() {
    Student students[100];  // Adjust based on max expected records
    int count = 0, i, j, choice;
    FILE *file = fopen(FILE_NAME, "r");

    if (!file) {
        printf("No records found!\n");
        return;
    }

    while (fscanf(file, "%s %s %d %f %c", students[count].name, students[count].student_id,
                  &students[count].level, &students[count].score, &students[count].grade) != EOF) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No student records available.\n");
        return;
    }

    printf("Sort by:\n1. Ascending Order\n2. Descending Order\nEnter choice: ");
    scanf("%d", &choice);

    // Bubble Sort (Simple Sorting Algorithm)
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if ((choice == 1 && students[j].score > students[j + 1].score) ||
                (choice == 2 && students[j].score < students[j + 1].score)) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // Display sorted scores
    printf("\nSorted Student Scores:\n");
    for (i = 0; i < count; i++) {
        printf("%s (ID: %s) - Score: %.2f\n", students[i].name, students[i].student_id, students[i].score);
    }
}

void editRecords() {
    char student_id[20];
    Student student;
    int found = 0;
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID to edit: ");
    scanf("%s", student_id);
    getchar(); // Clear buffer

    while (fscanf(file, "%s %s %d %f %c", student.name, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
        if (strcmp(student.student_id, student_id) == 0) {
            found = 1;
            int choice;

            printf("\nEditing Student: %s\n", student.name);
            do {
                printf("\nChoose a field to edit:\n");
                printf("1. Name\n2. Level\n3. Score\n4. Exit Editing\nEnter your choice: ");
                scanf("%d", &choice);
                getchar(); // Clear buffer after number input

                switch (choice) {
                    case 1:
                        printf("Enter New Name: ");
                        fgets(student.name, sizeof(student.name), stdin);
                        student.name[strcspn(student.name, "\n")] = 0; // Remove newline
                        break;
                    case 2:
                        printf("Enter New Level: ");
                        scanf("%d", &student.level);
                        break;
                    case 3:
                        printf("Enter New Score: ");
                        scanf("%f", &student.score);
                        student.grade = (student.score >= 40) ? 'P' : 'F'; // Update grade
                        break;
                    case 4:
                        printf("Exiting editing...\n");
                        break;
                    default:
                        printf("Invalid choice! Try again.\n");
                }
            } while (choice != 4);
        }
        fprintf(temp, "%s %s %d %.2f %c\n", student.name, student.student_id, student.level, student.score, student.grade);
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Record updated successfully!\n");
    else
        printf("Student ID not found!\n");
}

