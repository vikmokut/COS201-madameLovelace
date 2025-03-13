#ifndef MAIN_H
#define MAIN_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// use this macro def to reference the filename
#define FILE_NAME "students.txt"

// Structure for student record
typedef struct {
    char fname[50];
    char surname[50];
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
void deleteRecords();
void sortedScoreOnly();

#endif
