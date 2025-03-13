#include <stdio.h>
#include "main.h"
#include <stdlib.h>

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
        printf("6. Sorted Scores Detailed\n");
        printf("7. Sorted Scores Only\n");
	printf("8. Delete Records\n");
	printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: registration(); break;
            case 2: resultChecker(); break;
            case 3: displayRecords(); break;
            case 4: analyze(); break;
            case 5: editRecords(); break;
            case 6: sortedScores(); break;
            case 7: sortedScoreOnly(); break;
	    case 8: deleteRecords(); break;
	    case 9: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
