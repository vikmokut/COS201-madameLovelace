#include "main.h"

void greetUser() {
    char fname[50];
    printf("Welcome to the Student Record System!\n");
    printf("Enter your name: ");
    fgets(fname, 50, stdin);
    fname[strcspn(fname, "\n")] = 0;
    printf("Hello, %s!\n", fname);
}

void registration() {
    Student student;
    printf("Enter Student First Name: ");
    fgets(student.fname, 50, stdin);
    student.fname[strcspn(student.fname, "\n")] = 0;
    printf("Enter Student Surname Name: ");
    fgets(student.surname, 50, stdin);
    student.surname[strcspn(student.surname, "\n")] = 0; // watch this line
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
    fprintf(file, "%s %s %s %d %.2f %c\n", student.fname, student.surname, student.student_id, student.level, student.score, student.grade);
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
    while (fscanf(file, "%s %s %s %d %f %c", student.fname, student.surname, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
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
    while (fscanf(file, "%s %s %s %d %f %c", student.fname, student.surname, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
        if (strcmp(student.student_id, student_id) == 0) {
            printf("\nStudent Name: %s %s\nStudent ID: %s\nLevel: %d\nScore: %.2f\nGrade: %c\n", student.fname, student.surname, student.student_id, student.level, student.score, student.grade);
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
    while (fscanf(file, "%s %s %s %d %f %c", student.fname, student.surname, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
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

    while (fscanf(file, "%s %s %s %d %f %c", students[count].fname, students[count].surname, students[count].student_id,
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
        printf("%s (ID: %s) - Score: %.2f\n", students[i].fname, students[i].student_id, students[i].score);
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

    while (fscanf(file, "%s %s %s %d %f %c", student.fname, student.surname, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
        if (strcmp(student.student_id, student_id) == 0) {
            found = 1;
            int choice;

            printf("\nEditing Student: %s\n", student.fname);
            do {
                printf("\nChoose a field to edit:\n");
                printf("1. First Name\n2. Surname\n3. Level\n4. Score\n5. Exit Editing\nEnter your choice: "); // keep an eye
                scanf("%d", &choice);
                getchar(); // Clear buffer after number input

                switch (choice) {
                    case 1:
                        printf("Enter New First Name: ");
                        fgets(student.fname, sizeof(student.fname), stdin);
                        student.fname[strcspn(student.fname, "\n")] = 0; // Remove newline
                        break;
                    case 2:
                        printf("Enter New Surname: ");
                        fgets(student.surname, sizeof(student.surname), stdin);
                        student.surname[strcspn(student.surname, "\n")] = 0; // Remove newline
                        break;
                    case 3:
                        printf("Enter New Level: ");
                        scanf("%d", &student.level);
                        break;
                    case 4:
                        printf("Enter New Score: ");
                        scanf("%f", &student.score);
                        student.grade = (student.score >= 40) ? 'P' : 'F'; // Update grade
                        break;
                    case 5:
                        printf("Exiting editing...\n");
                        break;
                    default:
                        printf("Invalid choice! Try again.\n");
                }
            } while (choice != 5);
        }
        fprintf(temp, "%s %s %s %d %.2f %c\n", student.fname, student.surname, student.student_id, student.level, student.score, student.grade);
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

void deleteRecords() {
    char student_id[20], choice;
    Student student;
    int found = 0;

    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID to delete: ");
    scanf("%s", student_id);
    getchar(); // Clear buffer

    while (fscanf(file, "%s %s %s %d %f %c", student.fname, student.surname, student.student_id, &student.level, &student.score, &student.grade) != EOF) {
        if (strcmp(student.student_id, student_id) == 0) {
            found = 1;

            // Confirmation Prompt
            printf("\nAre you sure you want to delete the record for:\n");
            printf("Name: %s\nStudent ID: %s\nLevel: %d\nScore: %.2f\nGrade: %c\n",
                   student.fname, student.student_id, student.level, student.score, student.grade);
            printf("Enter 'Y' to confirm or 'N' to cancel: ");
            scanf(" %c", &choice); // Notice the space before %c to catch any whitespace
            getchar(); // Clear buffer

            if (choice == 'Y' || choice == 'y') {
                printf("Record for Student ID %s deleted successfully!\n", student.student_id);
                continue; // Skip writing this record to temp file (delete it)
            } else {
                printf("Deletion canceled.\n");
            }
        }
        fprintf(temp, "%s %s %s %d %.2f %c\n", student.fname, student.surname, student.student_id, student.level, student.score, student.grade);
    }

    fclose(file);
    fclose(temp);

    // Replace old file with the updated file only if deletion occurred
    if (found) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
    } else {
        printf("Student ID not found!\n");
    }
}

#include <stdio.h>
#include <stdlib.h>

void sortedScoreOnly() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    float *scores = NULL; // Dynamic array for scores
    int count = 0; // Number of scores

    // Read scores from the file
    char fname[50], surname[50], student_id[20];
    int level;
    float score;
    char grade;

    while (fscanf(file, "%s %s %s %d %f %c", fname, surname, student_id, &level, &score, &grade) != EOF) {
        // Expand memory dynamically
        float *temp = realloc(scores, (count + 1) * sizeof(float));
        if (!temp) {
            printf("Memory allocation failed!\n");
            free(scores); // Free allocated memory before exiting
            fclose(file);
            return;
        }
        scores = temp; // Assign new block
        scores[count++] = score; // Store the score
    }
    fclose(file);

    // Ask user for sorting order
    int choice;
    printf("\nChoose sorting order:\n1. Ascending\n2. Descending\nEnter choice: ");
    scanf("%d", &choice);

    // Sorting logic (Bubble Sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((choice == 1 && scores[j] > scores[j + 1]) ||
                (choice == 2 && scores[j] < scores[j + 1])) {
                float temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }

    // Display sorted scores
    printf("\nSorted Scores:\n");
    for (int i = 0; i < count; i++) {
        printf("%.2f\n", scores[i]);
    }

    free(scores); // Free dynamically allocated memory
}
